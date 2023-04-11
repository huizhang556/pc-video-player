#include "MainWidget.h"
#include "login/Nationlity.h"
#include "login/ChangeHead.h"
#include "titlebar/TitleBar.h"
#include "customer/CPolLabel.h"
#include "style/loadGlobalQss.h"
#include "pernotice/MainNotice.h"
#include "slidebar/LeftSideBar.h"
#include "creator/CreateCenter.h"
#include "miniplayer/MiniPlayer.h"
#include "messagebox/ExitDialog.h"
#include "pernotice/ScrollToTop.h"
#include "fileshandle/DownloadType.h"
#include "videomodels/MultipPlayer.h"
#include "mainwidget/AniStackWidget.h"
#include "splashscreen/CSplashScreen.h"
//#include "facebread/myemotionwindow.h"
#include "mainwidget/resultlist/ResultLists.h"
#include "desktoplyric/toplyric/DesktopLyric.h"
#include "mainwidget/subunititems/HotRankList.h"
#include "mainwidget/cusvideosbox/CusVideoBox7.h"

#include <QApplication>
#include <QTranslator>
#include <QUrlQuery>
#include <QThread>
#include <QTimer>
#include <QPixmap>
#include <QLabel>
#include <QMovie>
#include <QDebug>
//QFileOpenEvent只支持只支持MacOS X和Symbian
#include <QFileOpenEvent>

//自定义一个可以接接收外部文件请求的QApplication
//class MyApplication : public QApplication
//{
//public:
//    MyApplication(int &argc, char **argv):
//    QApplication(argc, argv)
//    {
//    }

//    bool event(QEvent *event) override
//    {
//        if (event->type() == QEvent::DragEnter)
//        {
//            QFileOpenEvent *openEvent = static_cast<QFileOpenEvent *>(event);
//            qDebug() << "Open file" << openEvent->url();
//            MultipPlayer::getInstance()->slot_addTempPlaylist(999,QStringList{openEvent->url().toString()},QString(openEvent->url().toString()));
//        }

//        return QApplication::event(event);
//    }
//};

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);//高分辨率支持
    QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath())+QDir::separator()+"plugins");
    QCoreApplication::addLibraryPath(strLibPath);
    QApplication a(argc, argv);

    qDebug()<< QString(u8"argv: %1,argv[1]:%2").arg(argc).arg(QString::fromLocal8Bit(argv[1]));

    //00--->加载翻译文件，插件
    QApplication::setAttribute(Qt::AA_UseOpenGLES);
    qDebug() << QApplication::libraryPaths();//打印库路径

    QTranslator translator1;
    translator1.load(":/font/qt_zh_CN.qm");//翻译为中文
    a.installTranslator(&translator1);


    //01--->加载全局样式
    loadGlobalQss::loadAllUIQss(STYLETYPE::STYLE_BLACK);
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

    //判断是否为播放器支持的类型
    if(Global::getFileType(QString::fromLocal8Bit(argv[1])))//支持类型（直接显示主播放器）
    {
        QUrlQuery query;
        query.addQueryItem(u8"url",QString::fromLocal8Bit(argv[1]));
        query.addQueryItem(u8"nick",QString::fromLocal8Bit(argv[1]));
        query.addQueryItem(u8"pos",u8"0");
        MultipPlayer::getInstance()->slot_addTempPlaylist(999,QStringList{QString::fromLocal8Bit(argv[1])},query);
        MainWidget w1;
        w1.move((QApplication::desktop()->width() - w1.width())/2,(QApplication::desktop()->height() - w1.height())/2);//居中显示
        w1.hide();

        //数据恢复初始化
        QTimer::singleShot(1500,0,[=](){
            dataBase::getInstance()->initGlobalDate();
        });
        return a.exec();
    }
    else//不支持类型（正常启动）
    {
        //04--->开机启动屏幕
        QPixmap pixmap(Global::appDirPath + dataBase::getSkin_splash());
        pixmap = pixmap.scaled(dataBase::getSize_splash(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        CSplashScreen splashscream(pixmap);
        if(dataBase::getSkin_switch())
        {
            //    QPixmap pixmap(Global::appDirPath + "/pictures/splashscreen/splash.png");//静图
            //    QPixmap pixmap(Global::appDirPath + "/pictures/splashscreen/splash1.gif");//动态
            a.processEvents();
            splashscream.show();
            splashscream.setCursor(Qt::BlankCursor);
            for(int i = 0; i< 100; ++i)
            {
                splashscream.slot_updateProgressbarValue(i);
                QThread::msleep(30);
            }
        }

        //05--->显示主界面
#if 0
        //    ScrollToTop::getInstance()->show();
        //    DesktopLyric::getInstance()->show();

//            MultipPlayer::getInstance()->show();


//        LeftSideBar lbar; lbar.show();
//        ChangeHead::getInstance()->exec_(OPENTYPE::PER_HEAD);

        //    MiniPlayer m;
        //    m.c_show();
        //    m.slot_receivePlayMediaFile("http://43.143.226.251:8080/group1/videos_drama/SuperStar_SHE.mp4","SuperStar_SHE");

        //    ResultLists w; w.show();

        //    MainNotice::getInstance()->show();

        //    ExitDialog w; w.show();

        //    TitleBar w1;
        //    w1.show();

        //    RankList w1(QString(u8"动画热播榜"),10);
        //    w1.show();

        //    ShortVideo w1;
        //    w1.show();

//            CusVideoBox7 w1;
//            w1.show();

        //        CPolLabel w1(QSize(100,100),QString(":/images/bgpic/dieji3.png"),8);
        //        w1.show();

//            MainNotice w1;
//            w1.show();

        //    CreateCenter::getInstance()->show();

        //    MyEmotionWindow w1;
        //    w1.showNormalEmotion(QPoint(500 , 500));
        //    DownloadType::getInstance()->show();
            NewLoginForm::getInstance()->show();
        //    AniStackWidget w1;
        //    w1.show();
        //    splashscream.finish(&w1);

#else
        MainWidget w1;
        w1.move((QApplication::desktop()->width() - w1.width())/2,(QApplication::desktop()->height() - w1.height())/2);//居中显示
        w1.show();
        splashscream.finish(&w1);
#endif

        //06--->数据恢复初始化
        QTimer::singleShot(1500,0,[=](){
            dataBase::getInstance()->initGlobalDate();
        });
        return a.exec();
    }
}



