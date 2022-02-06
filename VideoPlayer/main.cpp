#include "MainWidget.h"
#include <QApplication>
#include "database/dataBase.h"
#include "titleBar/TitleBar.h"
#include "videomodels/HolisticVideos.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    dataBase::creatConnection();
    MainWidget w1;
    w1.show();

//    MainWindow w;
//    w.show();

//    TitleBar t;
//    t.show();

    return a.exec();
}
