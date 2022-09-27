#include "VideoSortType.h"
#include "ui_VideoSortType.h"
#include "MemberVideoItem.h"
#include "global/Global.h"
#include <QScrollBar>
#include <QDebug>

VideoSortType::VideoSortType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoSortType)
{
    ui->setupUi(this);
    initWorkUI();
    setFixedHeight(410);
    handleSignalsAndSlots();
    setInstallEventFilter();
}

VideoSortType::~VideoSortType()
{
    delete ui;
}

void VideoSortType::initWorkUI()
{
    ui->listWidget_items->setViewMode(QListView::IconMode);
    ui->listWidget_items->setMovement(QListView::Static);
    ui->listWidget_items->setWrapping(false);
    ui->listWidget_items->setResizeMode(QListView::Adjust);
    ui->listWidget_items->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_items->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_items->setVerticalScrollMode(QListView::ScrollPerPixel);

    for(int i = 0; i < 10; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/mylike/list_intro%1.png").arg(i);
        MemberVideoItem *itemWidget = new MemberVideoItem(path,QString(u8"沸腾人生%1").arg(i),QString(u8"再现中国重卡制造史"));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());
        ui->listWidget_items->addItem(item);
        ui->listWidget_items->setItemWidget(item,itemWidget);
    }
}

void VideoSortType::handleSignalsAndSlots()
{

}

void VideoSortType::setInstallEventFilter()
{

}
