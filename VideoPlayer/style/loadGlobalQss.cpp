#include "loadGlobalQss.h"

#include <QFile>
#include <QDebug>
#include <QApplication>

loadGlobalQss::loadGlobalQss(QWidget *parent) :
    QWidget(parent)
{

}

loadGlobalQss::~loadGlobalQss()
{

}

/*加载界面样式*/
void loadGlobalQss::loadAllUIQss()
{
    QFile file(":/style/alluistyle_day.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    if(!file.isOpen())
    {
        qDebug()<<"the style qss is unload!";
        return;
    }
    else
    {
        QString style = tr(file.readAll());
        qApp->setStyleSheet(style);
        qDebug()<<"the style is load successfull!";
    }
    file.close();
}


