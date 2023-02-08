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
void loadGlobalQss::loadAllUIQss(STYLETYPE style)
{
    QString styleFile;
    switch (style) {
    case STYLE_WHITE:
    {
        styleFile = QString(":/style/alluistyle_white.qss");
    }
        break;
    case STYLE_BLACK:
    {
        styleFile = QString(":/style/alluistyle_black.qss");
    }
        break;
    case STYLE_DARK:
    {
        styleFile = QString(":/style/alluistyle_dark.qss");
    }
        break;
    case STYLE_PINK:
    {
        styleFile = QString(":/style/alluistyle_pink.qss");
    }
        break;
    default:
        break;
    }

    QFile file(styleFile);
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


