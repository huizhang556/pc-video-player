#include "Global.h"


//类外初始化全局变量
//不同模式下选择不同的路径,可通过变换模式查看（变红）
#ifdef QT_DEBUG
        QString Global::appDirPath = QString("E:/QtProjects/000QtDemo_51ctodemo/04_20SubVideoPlayer/VideoPlayer");
#else
        QString Global::appDirPath = QDir::currentPath();//release时使用
#endif
//QString Global::appDirPath = QDir::currentPath();//静态全局变量使用applicationDirPath();为空
Global::Global(QObject *parent) : QObject(parent)
{

}

//注册LAV播放器
void Global::registerLAVplayer()
{
    QProcess p(NULL);
    p.setWorkingDirectory(Global::appDirPath + "/lav64");
    p.start(Global::appDirPath + "/lav64/install_video.bat");
    p.waitForFinished();//默认3000ms
}

//判断是否有网络连接（不一定能上网）
bool Global::isNetWorkOnline()
{
    QNetworkConfigurationManager mgr;
    return mgr.isOnline();
}

//判断是否能上网
void Global::checkNetWorkOnline()
{
    QHostInfo::lookupHost("www.baidu.com",this,SLOT(onLookupHost(QHostInfo)));
}

void Global::onLookupHost(QHostInfo host)
{
    if (host.error() != QHostInfo::NoError) {
        qDebug() << "Lookup failed:" << host.errorString();
        //网络未连接，发送信号通知
        emit sig_sendLookUpHostResult(false);
    }
    else{
        emit sig_sendLookUpHostResult(true);
    }
}
