#include "MainWidget.h"
#include <QApplication>
#include "skin/MySkin.h"
#include "global/Global.h"
#include "skin/MySkinItem.h"
#include "database/dataBase.h"
#include "titleBar/TitleBar.h"
#include "style/loadGlobalQss.h"
#include "customer/SystemTray.h"
#include "customer/CusLineEdit.h"
#include "mainwidget/Slideshow.h"
#include "customer/CusLineEdit.h"
#include "lunbotu/PictureWidget.h"
#include "videomodels/CommentTab.h"
#include "mainwidget/RecommendForm.h"
#include "videomodels/ControlForm.h"
#include "videomodels/MultipPlayer.h"
#include "videomodels/PersonFileForm.h"
#include "musicmodels/SongItemForm.h"
#include "mainwidget/StackItemForm.h"
#include "mainwidget/GalleryItemForm.h"
#include "videomodels/VideoProgressBar.h"
#include "videomodels/PlayCtlAdjustForm.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loadGlobalQss::loadAllUIQss();//加载全局样式
    dataBase::creatConnection();//连接数据库
    MainWidget w1;
    w1.show();

//    SystemTray s;
//    s.show();

//    VideoProgressBar::getInstance()->show();

//    PlayCtlAdjustForm p;
//    p.show();

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

//    CusLineEdit x;
//    x.show();

//    ControlForm v;
//    v.show();

//    Slideshow s;
//    s.show();

//    CusLineEdit c(QIcon(":/images/icon/checked.png"));
//    c.show();

//    MultipPlayer w;
//    w.show();

//    TitleBar t;
//    t.show();

    return a.exec();
}
