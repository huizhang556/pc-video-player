#include "Worker.h"
#include <QDebug>

Worker::Worker(QObject *parent)
{
    m_netManager = new QNetworkAccessManager(this);
}

Worker::~Worker()
{

}

bool Worker::isDirExist(QString fullpath)
{
    QDir dir(fullpath);
    if(dir.exists())
    {
        return true;
    }
    else
    {
        bool ok = dir.mkpath(fullpath);//创建多级目录
        return ok;
    }
}

//网页下载链接
void Worker::slot_receiveData_accept(QWebEngineDownloadItem *item, QString filename, QString savepath)
{
    item->setPath(savepath + filename);//保存路径是路径+文件名
    qDebug() << QString::fromLocal8Bit("线程中收到的保存路径数据：") << savepath+filename;
    item->accept();
    connect(item,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(slot_receiveData_progressbar(qint64,qint64)));
    connect(item,SIGNAL(finished()),this,SLOT(slot_receiveData_finished()));
}

void Worker::slot_receiveData_pause(QWebEngineDownloadItem *item)
{
    item->pause();
    qDebug() <<QString::fromLocal8Bit("暂停");
}

void Worker::slot_receiveData_cancel(QWebEngineDownloadItem *item)
{
    item->cancel();
    qDebug() <<QString::fromLocal8Bit("取消");
}

void Worker::slot_receiveData_resume(QWebEngineDownloadItem *item)
{
    item->resume();
    qDebug() <<QString::fromLocal8Bit("继续");
}

//自建下载链接
void Worker::slot_receiveData_accept(QUrl url,QString filename, QString savepath)
{
    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply *reply = m_netManager->get(request);
    QString fileSavePath = QDir::toNativeSeparators(savepath + "/" + filename);
    qDebug() << QString::fromLocal8Bit("线程接收到的指定保存路径：") << fileSavePath ;
    if(isDirExist(savepath))//路径要存在才执行,savepath没有 / 分割符号
    {
        qDebug() << QString::fromLocal8Bit("存储路径 %1 已经存在！").arg(savepath);
    }

    //关于QFile报错打不开磁盘的问题
    //00.构造QFile时，如果指定文件名，则先创建一个大小为0size的空文件，之后再往里面写数据；如果没有指定文件名称，则在工作目录下建立默认的文件
    //01.QFile需要注意，报错not open device，先检查文件权限问题，再检查打开方式；
    //02.QFile请求下载的文件内容，先存储在缓存中，存储到一定大小，缓存内容才被写入文件中，除非每次调用flush刷新；
    //03.如果QFile没有close,直到程序关闭，文件才从缓存中被写入。
    //04.readyRead信号的触发速度，比downloadProgress触发的频繁；
    //05.如果存在一个一模一样已经存在的下载文件，会在原文件追加，不会新建；
    //数据可读

    connect(reply, &QNetworkReply::readyRead,[=](){
        if(reply == nullptr) return;
        if(!m_file.isOpen())//文件没打开
        {
            m_file.setFileName(fileSavePath);
            //断点续传的时候，需要使用size()计算已经下载的大小；采用append的形式继续写入；下载新文件则不需要
            m_file.open(QIODevice::WriteOnly);
        }
            m_array.append(reply->readAll());
//            m_file.write(reply->readAll());//先存储在缓存中，然后缓存满了才往文件中写入
    });

    //下载进度
    connect(reply, &QNetworkReply::downloadProgress,[=](qint64 bytesReceived, qint64 bytesTotal)
    {
        slot_receiveData_progressbar(bytesReceived,bytesTotal);
    });
    //结束退出事件循环
    connect(reply, &QNetworkReply::finished,[=]()
    {
        reply->deleteLater();
        m_file.write(m_array);
        m_file.resize(m_array.size());//重置大小，QFile写入文件会额外增加一些东西
        m_file.close(); //关闭文件，也会将缓存写入文件
        m_array.clear();//清除原先的数据，否则下次数据写入是叠加在以前数据之上
      emit  sig_receiveData_finished();//数据接收完毕，转换界面
    });
}

void Worker::slot_receiveData_pause()
{
    m_workItem->pause();
    qDebug() <<QString::fromLocal8Bit("暂停");
}

void Worker::slot_receiveData_cancel()
{
    m_workItem->cancel();
    qDebug() <<QString::fromLocal8Bit("取消");
}

void Worker::slot_receiveData_resume()
{
    m_workItem->resume();
    qDebug() <<QString::fromLocal8Bit("继续");
}

void Worker::slot_receiveData_progressbar(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << QString::fromLocal8Bit("线程中已接受数据：")<<bytesReceived
             << QString::fromLocal8Bit("百分比：%1%").arg((bytesReceived*100)/bytesTotal)
             << QString::fromLocal8Bit("文件总大小：") << bytesTotal;
    emit sig_receiveData_progressbar(bytesReceived,bytesTotal);//向外发射进度
}

void Worker::slot_receiveData_finished()
{
    qDebug() << QString::fromLocal8Bit("任务下载结束！");
    emit sig_receiveData_finished();
}
