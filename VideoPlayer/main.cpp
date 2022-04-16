#include "MainWidget.h"
#include <QApplication>
#include "database/dataBase.h"
#include "titleBar/TitleBar.h"
#include "customer/FirstShow.h"
#include "style/loadGlobalQss.h"
#include "customer/CusLineEdit.h"
#include "mainwidget/Slideshow.h"
#include "customer/CusLineEdit.h"
#include "videomodels/CommentTab.h"
#include "videomodels/ControlForm.h"
#include "videomodels/MultipPlayer.h"
#include "videomodels/PersonFileForm.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    loadGlobalQss::loadAllUIQss();//加载全局样式
    dataBase::creatConnection();//连接数据库
//    MainWidget w1;
//    w1.show();


//    PersonFileForm f;
//    f.show();

//    CommentTab c;
//    c.show();

//    CusLineEdit x;
//    x.show();

//    ControlForm v;
//    v.show();

//    FirstShow f;
//    f.show();

//    Slideshow s;
//    s.show();

//    CusLineEdit c(QIcon(":/images/icon/checked.png"));
//    c.show();

    MultipPlayer w;
    w.show();

//    TitleBar t;
//    t.show();

    return a.exec();
}
