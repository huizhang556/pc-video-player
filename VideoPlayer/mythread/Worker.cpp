#include "Worker.h"
#include <QDebug>

Worker::Worker(QObject *parent) : m_count(0)
{
    m_count++;
    m_netManager = new QNetworkAccessManager(this);
}

Worker::~Worker()
{

}

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

void Worker::slot_receiveData_accept(QUrl url,QString filename, QString savepath)
{
    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply *reply = m_netManager->get(request);
    qDebug() << QString::fromLocal8Bit("接收到的指定保存路径：") << savepath+filename;
    m_file = new QFile(savepath+filename);//指定保存路径
    m_file->open(QIODevice::WriteOnly);
    //   file.remove();//删除已经有的
    //数据可读
    connect(reply, &QNetworkReply::readyRead,[=](){
        if(!m_file->isOpen())
        {
            //            qDebug() << "file open error";
            return;
        }
        m_file->write(reply->readAll());
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
    });
    m_file->close(); //关闭文件
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
    qDebug()<< QString::fromLocal8Bit("第%1个下载任务，").arg(m_count)
            << QString::fromLocal8Bit("线程中已接受数据：")<<bytesReceived
            << QString::fromLocal8Bit("百分比：%1%").arg((bytesReceived*100)/bytesTotal)
            << QString::fromLocal8Bit("文件总大小：") << bytesTotal;
    emit sig_receiveData_progressbar(bytesReceived,bytesTotal);//向外发射进度
}

void Worker::slot_receiveData_finished()
{
    qDebug() << QString::fromLocal8Bit("第%1个任务下载结束！").arg(m_count);
    emit sig_receiveData_finished();
}
