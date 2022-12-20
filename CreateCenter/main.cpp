#include "CreateCenter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CreateCenter::getPinstance()->show();

    return a.exec();
}
