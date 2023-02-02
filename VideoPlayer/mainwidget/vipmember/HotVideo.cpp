#include "HotVideo.h"
#include "ui_HotVideo.h"
#include "global/Global.h"
#include "mainwidget/vipmember/HotVideoItem.h"
#include <QScrollBar>
#include <QListWidgetItem>
#include <QDebug>

HotVideo::HotVideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotVideo)
{
    ui->setupUi(this);

    ui->listWidget_videoItem->setViewMode(QListView::IconMode);
    ui->listWidget_videoItem->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_videoItem->setResizeMode(QListWidget::Adjust);
    ui->listWidget_videoItem->setWrapping(false);//自动换行 所有itm在一行显示
    ui->listWidget_videoItem->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_videoItem->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_videoItem->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_videoItem->setFrameShape(QFrame::NoFrame);//无边界线
    ui->listWidget_videoItem->horizontalScrollBar()->setDisabled(true);
    ui->listWidget_videoItem->verticalScrollBar()->setDisabled(true);

    ui->pushButton_title->setIcon(QIcon("://images/user/itemmark_new2.png"));
    ui->pushButton_title->setIconSize(QSize(36,36));

    for(int i = 0; i < 9; i++)
    {
        HotVideoItem *itemWidget = new HotVideoItem();
//        itemWidget->setVideoItemPicture("://images/bgpic/loading_001.gif");
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());
        ui->listWidget_videoItem->addItem(item);
        ui->listWidget_videoItem->setItemWidget(item,itemWidget);
    }
}

HotVideo::~HotVideo()
{
    delete ui;
}
