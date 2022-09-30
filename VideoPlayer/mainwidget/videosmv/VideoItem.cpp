#include "VideoItem.h"
#include "ui_VideoItem.h"

VideoItem::VideoItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

VideoItem::VideoItem(const QString &picPath, const QString &introduce, const QString &author, QWidget *parent):
    QWidget(parent),
    ui(new Ui::VideoItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();

}

VideoItem::~VideoItem()
{
    delete ui;
}

void VideoItem::initWorkUI()
{
//    ui->label_mvPic->constructItem(":/images/videosmv/mvsort/music1.png","://images/user/itemmark_new.png",QString(u8"6.6"),true,true,false);
}

void VideoItem::handleSignalsAndSlots()
{

}

void VideoItem::setInstallEventFilter()
{

}
