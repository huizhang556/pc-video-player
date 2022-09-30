#include "VipMember.h"
#include "ui_VipMember.h"

#include "mainwidget/vipmember/HotSort.h"
#include "mainwidget/vipmember/HotVideo.h"
#include "mainwidget/vipmember/HotDownload.h"

#include <QListWidgetItem>
#include <QScrollBar>
#include <QDebug>

VipMember::VipMember(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VipMember)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

VipMember::~VipMember()
{
    delete ui;
}

void VipMember::initWorkUI()
{
    ui->listWidget_vipshared->setViewMode(QListView::ListMode);
    ui->listWidget_vipshared->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_vipshared->setResizeMode(QListWidget::Adjust);
//    ui->listWidget_vipshared->setWrapping(true);//自动换行 所有itm在一行显示
//    ui->listWidget_vipshared->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_vipshared->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_vipshared->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    for(int i = 0; i < 2; i++)
    {
        //会员专享下载
        HotDownload *itemWidget = new HotDownload();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());
        ui->listWidget_vipshared->addItem(item);
        ui->listWidget_vipshared->setItemWidget(item,itemWidget);
        //槽函数
        connect(itemWidget,&HotDownload::sig_itemSizeChanged,this,&VipMember::resizeListWidgetItemWidget);
    }

    for(int i = 0; i < 2; i++)
    {
        //精选分类
        HotSort *itemWidget = new HotSort();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());
        ui->listWidget_vipshared->addItem(item);
        ui->listWidget_vipshared->setItemWidget(item,itemWidget);
        //槽函数

    }

    for(int i = 0; i < 2; i++)
    {
        //热门视频
        HotVideo *itemWidget = new HotVideo();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());
        ui->listWidget_vipshared->addItem(item);
        ui->listWidget_vipshared->setItemWidget(item,itemWidget);
        //槽函数
    }
//    ui->listWidget_vipshared->setMinimumHeight((230*2+60)*ui->listWidget_vipshared->count()+ui->listWidget_vipshared->horizontalScrollBar()->height());
//    ui->listWidget_vipshared->setMinimumHeight((82*3 + 60)*2 + (230*2+60)*8);
}

void VipMember::handleSignalsAndSlots()
{

}

void VipMember::setInstallEventFilter()
{
    ui->listWidget_vipshared->installEventFilter(this);
}

bool VipMember::eventFilter(QObject *watched, QEvent *event)
{
//    if(watched == ui->listWidget_vipshared)
//    {
//       if(event->type() == QEvent::Resize)
//       {

//       }
//    }
    return QWidget::eventFilter(watched,event);
}

void VipMember::resizeListWidgetItemWidget(const QSize &size)
{
//    ui->listWidget_vipshared->setMinimumSize(QSize(size.width(),size.height()*4));
}

