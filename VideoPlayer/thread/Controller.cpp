#include "Controller.h"
#include <QDebug>

Controller::Controller(QObject *parent) : QObject(parent)
{
    workerThread = new QThread();//新的工作线程
    worker = new Worker();//实际工作的对象，不能指定父对象
    worker->moveToThread(workerThread);//要求是传地址
    connect(workerThread,&QThread::finished,worker,&QObject::deleteLater);//谨防内存泄露
    connect(workerThread,&QThread::finished,workerThread,&QObject::deleteLater);//这一步必须有
//    connect(this,&Controller::sig_operate,worker,&Worker::doWork);
//    connect(worker,&Worker::sig_resultReady,this,&Controller::slot_handleResult);
    workerThread->start();
}

Controller::~Controller()
{
    qDebug() << QString::fromLocal8Bit("start destory widget");
    if(workerThread)
    {
        workerThread->quit();
    }
    workerThread->wait();
    qDebug() << QString::fromLocal8Bit("end destory widget");
}

