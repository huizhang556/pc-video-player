#include "Global.h"

#include <QSettings>
#include <QDebug>

//类外初始化全局变量
//不同模式下选择不同的路径,可通过变换模式查看（变红）
#ifdef QT_DEBUG
        QString Global::appDirPath = QString("E:/QtProjects/000QtDemo_51ctodemo/04_20SubVideoPlayer/VideoPlayer");
#else
        QString Global::appDirPath = QDir::currentPath();//release时使用
#endif
//QString Global::appDirPath = QDir::currentPath();//静态全局变量使用applicationDirPath();为空

QTimer* Global::m_globalTimer = new QTimer();//类外初始化
Global* Global::m_pInstance   = nullptr;

Global::Global(QObject *parent) : QObject(parent)
{
    m_globalTimer->start(5000);//更新一次时间
    connect(m_globalTimer,&QTimer::timeout,[=](){
//        qDebug() << QString(u8"全局定时器已更新一次");
        emit sig_sendGlobalTimeOut();
    });
}

Global::~Global()
{
//    unRegisterLAVplayer();
    if(m_globalTimer != nullptr)
        delete m_globalTimer;
    m_globalTimer = nullptr;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

//注册LAV播放器
void Global::registerLAVplayer()
{
//    QProcess p(NULL);
//    p.setWorkingDirectory(Global::appDirPath + "/lav64");
//    p.start(Global::appDirPath + "/lav64/install_video.bat");
//    p.waitForFinished();//默认3000ms
    QProcess process1;
    process1.setWorkingDirectory(Global::appDirPath + "/lav64");
    QString cmd1 = QString(Global::appDirPath + "/lav64/install_splitter.bat");
    bool isOK1 = process1.startDetached(cmd1);
    if(isOK1)
    {
        qDebug() << QString::fromLocal8Bit("注册splitter成功！");
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("注册splitter失败！");
    }

    QProcess process2;
    process2.setWorkingDirectory(Global::appDirPath + "/lav64");
    QString cmd2 = QString(Global::appDirPath + "/lav64/install_audio.bat");
//    process2.startDetached(cmd2);
    bool isOK2 = process2.startDetached(cmd2);
    if(isOK2)
    {
        qDebug() << QString::fromLocal8Bit("注册audio成功！");
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("注册audio失败！");
    }

    QProcess process3;
    process3.setWorkingDirectory(Global::appDirPath + "/lav64");
    QString cmd3 = QString(Global::appDirPath + "/lav64/install_video.bat");
//    process3.startDetached(cmd3);
    bool isOK3 = process3.startDetached(cmd3);
    if(isOK3)
    {
        qDebug() << QString::fromLocal8Bit("注册video成功！");
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("注册video失败！");
    }
}

//卸载注册
void Global::unRegisterLAVplayer()
{
    QProcess process1;
    process1.setWorkingDirectory(Global::appDirPath + "/lav64");
    QString cmd1 = QString(Global::appDirPath + "/lav64/uninstall_splitter.bat");
//    process1.startDetached(cmd1);
    bool isOK1 = process1.startDetached(cmd1);
    if(isOK1)
    {
        qDebug() << QString::fromLocal8Bit("卸载video成功！");
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("卸载video失败！");
    }

    QProcess process2;
    process2.setWorkingDirectory(Global::appDirPath + "/lav64");
    QString cmd2 = QString(Global::appDirPath + "/lav64/uninstall_audio.bat");
//    process2.startDetached(cmd2);
    bool isOK2 = process2.startDetached(cmd2);
    if(isOK2)
    {
        qDebug() << QString::fromLocal8Bit("卸载audio成功！");
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("卸载audio失败！");
    }

    QProcess process3;
    process3.setWorkingDirectory(Global::appDirPath + "/lav64");
    QString cmd3 = QString(Global::appDirPath + "/lav64/uninstall_video.bat");
//    process3.startDetached(cmd3);
    bool isOK3 = process3.startDetached(cmd3);
    if(isOK3)
    {
        qDebug() << QString::fromLocal8Bit("卸载video成功！");
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("卸载video失败！");
    }
    setIni_ungis(false);//注册状态恢复为 0
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
//    QHostInfo::lookupHost("www.baidu.com",this,SLOT(onLookupHost(QHostInfo)));
//    QLibrary lib("Wininet.dll");
//    if (lib.load())
//    {
//        bool bOnline = false;//是否在线
//        int  flags;

//        //获取dll库中的函数InternetGetConnectedState函数地址`
//        ConnectFun  myConnectFun = (ConnectFun)lib.resolve("InternetGetConnectedState");

//        //判断是否连网
//        bOnline = myConnectFun(&flags, 0);
//        if(bOnline)
//            qDebug() << __FUNCTION__ << "isOnline = true";
//        else
//            qDebug() << __FUNCTION__ << "isOnline = false";
    //    }
}

Global *Global::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new Global();
    }
    return m_pInstance;
}

bool Global::getFileType(const QString &filepath)
{
    if(filepath.isEmpty())
    {
        return false;
    }
    else
    {
        QFileInfo info(filepath);
        QString suffix = info.suffix();
        if(suffix == "mp4")//返回的是mp4,而非 .mp4
        {
            return true;
        }
        else if(suffix == "mov")
        {
            return true;
        }
        else if(suffix == "avi")
        {
            return true;
        }
        else if(suffix == "flv")
        {
            return true;
        }
        else if(suffix == "mp3")
        {
            return true;
        }
        else if(suffix == "aac")
        {
            return true;
        }
        else if(suffix == "wav")
        {
            return true;
        }
        else if(suffix == "wma")
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

//读取注册状态(退出)
QString Global::readIni_exit()
{
    QSettings *set = new QSettings(appDirPath + "/config/config.ini",QSettings::IniFormat);
    QString statusValue = set->value("/check_status/status").toString();
    delete set;
    set = nullptr;
    return statusValue;
}

//播放器注册状态
QString Global::readIni_regis()
{
    QSettings *set = new QSettings(appDirPath + "/config/config.ini",QSettings::IniFormat);
    QString statusValue = set->value("/regis_status/status").toString();
    delete set;
    set = nullptr;
    return statusValue;
}

//写入注册状态（退出）
void Global::setIni_exit(bool on)
{
    QSettings *set = new QSettings(appDirPath + "/config/config.ini",QSettings::IniFormat);
    if(on)
    set->setValue("/check_status/status","1");
    else
    set->setValue("/check_status/status","0");
    delete set;
    set = nullptr;
}

void Global::setIni_ungis(bool on)
{
    QSettings *set = new QSettings(appDirPath + "/config/config.ini",QSettings::IniFormat);
    if(!on)
    set->setValue("/regis_status/status","0");
    else
    set->setValue("/regis_status/status","1");
    delete set;
    set = nullptr;
}

bool Global::getRegisStatus()
{
    if(readIni_regis() == "1")//1 已经注册
    {
        return true;
    }
    else if(readIni_regis() == "0")//0 未注册
    {
        return false;
    }
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
