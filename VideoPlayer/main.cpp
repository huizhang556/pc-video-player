#include "MainWidget.h"
#include <QApplication>
#include "skin/MySkin.h"
#include "global/Global.h"
#include "browser/NewWork.h"
#include "skin/MySkinItem.h"
#include "database/dataBase.h"
#include "titleBar/TitleBar.h"
#include "style/loadGlobalQss.h"
#include "customer/SystemTray.h"
#include "customer/CusLineEdit.h"
#include "mainwidget/recommend/Slideshow.h"
#include "customer/CusLineEdit.h"
#include "lunbotu/PictureWidget.h"
#include "videomodels/CommentTab.h"
#include "customer/CusFileDialog.h"
#include "browser/WebDownLoadList.h"
#include "messagebox/CusMessageBox.h"
#include "mainwidget/recommend/RecommendForm.h"
#include "videomodels/MultipPlayer.h"
#include "videomodels/PersonFileForm.h"
#include "musicmodels/SongItemForm.h"
#include "mainwidget/recommend/StackItemForm.h"
#include "mainwidget/recommend/GalleryItemForm.h"
#include "videomodels/VideoProgressBar.h"
#include "videomodels/RotatePic.h"
#include "browser/DownLoadItem.h"
#include "browser/CusTabBar.h"
#include "videomodels/FloatPlayCtl.h"
#include "customer/CustomFileDialog.h"
#include "videomodels/RecVideoItem.h"
#include "splashscreen/CSplashScreen.h"

#include "mainwidget/TrianButton.h"
#include "mainwidget/songersort/SongerSort.h"
#include "mainwidget/songlistsort/TagsMenu.h"
#include "mainwidget/rankinglist/RankingList.h"

#include <QTranslator>
#include <QThread>
#include <QTimer>
#include <QPixmap>
#include <QLabel>
#include <QMovie>
#include <QDebug>


int main(int argc, char *argv[])
{

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
        Global::setIni();
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
        for(int i = 0; i< 10; ++i)
        {
            splashscream.slot_updateProgressbarValue(i*11);
            QThread::sleep(1);
        }
    }

    //05--->显示主界面
    MainWidget w1;
    w1.show();

//        MultipPlayer w1;
//        w1.show();

//    RankingList w1;
//    w1.show();
    splashscream.finish(&w1);


    //06--->数据恢复初始化
    QTimer::singleShot(1500,0,[=](){
        dataBase::getInstance()->initGlobalDate();
    });


//    SongerSort s;
//    s.show();

//    TagsMenu t;
//    t.show();

    //播放器注册
//    Global::registerLAVplayer();

//    RecVideoItem c;
//    c.show();

//    CustomFileDialog s;
//    s.show();

//    RecVideoItem r;
//    r.show();

//    FloatPlayCtl::getInstance()->show();

//    CusTabBar t;
//    t.show();

//    RotatePic p;
//    p.show();

//    WebDownLoadList f;
//    f.show();

//    NewWork m;
//    m.show();

//    CusMessageBox e;
//    e.show();

//    CusFileDialog s;
//    s.show();

//    SystemTray s;
//    s.show();

//    VideoProgressBar::getInstance()->show();

//    StackItemForm s;
//    s.show();

//    GalleryItemForm g;
//    g.show();

//    SongItemForm s("001",QString("第%1"),true,QString("zhanghui%1"),QString("zhuanji%1"));;
//    s.show();

//    RecommendForm m;
//    m.show();

//    MySkin s;
//    s.show();

//    MySkinItem mskin(180,130,20,20,0);
//    mskin.show();

//    PersonFileForm f;
//    f.show();

//    CommentTab c;
//    c.show();

//    CusLineEdit x("123");
//    x.show();

//    Slideshow s;
//    s.show();

//    CusLineEdit c(QIcon(":/images/icon/checked.png"));
//    c.show();

//    TitleBar t;
//    t.show();

    return a.exec();
}
