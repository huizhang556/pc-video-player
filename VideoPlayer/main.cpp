#include "MainWidget.h"
#include <QApplication>
#include "database/dataBase.h"
#include "videomodels/HolisticVideos.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    dataBase::creatConnection();
//    MainWidget w;
//    w.show();

    MainWindow s;
    s.show();

    return a.exec();
}
