#include "HotVideo.h"
#include "ui_HotVideo.h"

#include "mainwidget/vipmember/HotVideoItem.h"
#include <QListWidgetItem>
#include <QDebug>

HotVideo::HotVideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotVideo)
{
    ui->listWidget_videoItem->setViewMode(QListView::IconMode);
    ui->listWidget_videoItem->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_videoItem->setResizeMode(QListWidget::Adjust);
    ui->listWidget_videoItem->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_videoItem->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_videoItem->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_videoItem->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->setupUi(this);

    for(int i = 0; i < 9; i++)
    {
        HotVideoItem *itemWidget = new HotVideoItem();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(itemWidget->size()));
        ui->listWidget_videoItem->addItem(item);
        ui->listWidget_videoItem->setItemWidget(item,itemWidget);
    }
}

HotVideo::~HotVideo()
{
    delete ui;
}
