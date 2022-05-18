#include "Worker.h"
#include <QDebug>

Worker::Worker(QObject *parent) :
    QObject(parent)
{

}

Worker::~Worker()
{

}

void Worker::doWork(const QString &para)
{

}

void Worker::slot_createNewDownloadWorker(QWebEngineDownloadItem *item)
{
    item->accept();
    qDebug() << QString::fromLocal8Bit("接收到下载请求，同意下载 ...");
    connect(item,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(slot_downLoad_progress(qint64,qint64)));
    connect(item,&QWebEngineDownloadItem::finished,this,&Worker::slot_receiveData_finished);
}

void Worker::slot_receiveData_progressbar(qint64 bytesReceived, qint64 bytesTotal)
{
    qDebug() << QString::fromLocal8Bit("已接受数据：")<<bytesReceived << QString::fromLocal8Bit("百分比：%1%").arg((bytesReceived*100)/bytesTotal)  << QString::fromLocal8Bit("文件总大小：") << bytesTotal;
    emit sig_receiveData_progressbar(bytesReceived,bytesTotal);
}

void Worker::slot_receiveData_finished()
{
    qDebug() <<QString::fromLocal8Bit("下载结束！");
    emit sig_receiveData_finished();
}
