#include "MainWidget.h"
#include <QApplication>
#include "titleBar/TitleBar.h"
#include "style/loadGlobalQss.h"
#include "creator/CreateCenter.h"
#include "videomodels/MultipPlayer.h"
#include "splashscreen/CSplashScreen.h"
#include "mainwidget/subunititems/HotRankList.h"
#include "mainwidget/cusvideosbox/CusVideoBox6.h"
#include "miniplayer/MiniPlayer.h"

#include <QTranslator>
#include <QThread>
#include <QTimer>
#include <QPixmap>
#include <QLabel>
#include <QMovie>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//高分辨率支持
//    QApplication::setAttribute(Qt::AA_UseOpenGLES);
    QApplication a(argc, argv);
    //00--->加载翻译文件
    QTranslator translator1;
    translator1.load(":/font/qt_zh_CN.qm");//翻译为中文
    a.installTranslator(&translator1);

    //01--->加载全局样式
    loadGlobalQss::loadAllUIQss();
//    QFont f("黑体",10);
//    a.setFont(f);

    //02--->数据初始化（放在界面初始化完成以后）
    dataBase::readXML(Global::appDirPath + "/config/config.xml");
    dataBase::creatMysqlConnection();//连接数据库,有数据的必须先连接数据库

//    //03--->注册解码器(记得打开管理员权限)
    if(!Global::getRegisStatus())
    {
        qDebug() << QString::fromLocal8Bit("播放器还未注册！");
        Global::registerLAVplayer();
        Global::setIni_ungis(true);//设置播放器为注册状态
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("播放器已经注册！");
    }

    //04--->开机启动屏幕
    QPixmap pixmap(Global::appDirPath + dataBase::getSkin_splash());
    CSplashScreen splashscream(pixmap);
    if(dataBase::getSkin_switch())
    {
        //    QPixmap pixmap(Global::appDirPath + "/pictures/splashscreen/splash.png");//静图
        //    QPixmap pixmap(Global::appDirPath + "/pictures/splashscreen/splash1.gif");//动态
        a.processEvents();
        splashscream.show();
        splashscream.setCursor(Qt::BlankCursor);
        for(int i = 0; i< 6; ++i)
        {
            splashscream.slot_updateProgressbarValue(i*19);
            QThread::sleep(1);//450 280 270 100
        }
    }

    //05--->显示主界面
    MainWidget w1;
    w1.move((QApplication::desktop()->width() - w1.width())/2,(QApplication::desktop()->height() - w1.height())/2);//居中显示
    w1.show();

//    MultipPlayer::getInstance()->show();

//    TitleBar w1;
//    w1.show();

//    RankList w1(QString(u8"动画热播榜"),10);
//    w1.show();

//    ShortVideo w1;
//    w1.show();

//    CusVideoBox6 w1;
//    w1.show();

//    CreateCenter::getInstance()->show();

    splashscream.finish(&w1);

    //06--->数据恢复初始化
    QTimer::singleShot(1500,0,[=](){
        dataBase::getInstance()->initGlobalDate();
    });

    return a.exec();
}
