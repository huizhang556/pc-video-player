#include "MainWidget.h"
#include <QApplication>
#include "database/dataBase.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dataBase::creatConnection();
    MainWidget w;
    w.show();

    return a.exec();
}
