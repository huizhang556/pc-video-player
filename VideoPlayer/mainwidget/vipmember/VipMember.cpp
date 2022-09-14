#include "VipMember.h"
#include "ui_VipMember.h"

#include "mainwidget/vipmember/HotSort.h"
#include "mainwidget/vipmember/HotDownload.h"

#include <QListWidgetItem>
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
//    ui->listWidget_vipshared->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_vipshared->setResizeMode(QListWidget::Adjust);
//    ui->listWidget_vipshared->setWrapping(true);//自动换行 所有itm在一行显示
//    ui->listWidget_vipshared->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_vipshared->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_vipshared->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    for(int i = 0; i < 3; i++)
    {
        HotDownload *hItem = new HotDownload();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(hItem->size());
        ui->listWidget_vipshared->addItem(item);
        ui->listWidget_vipshared->setItemWidget(item,hItem);
        //槽函数
        connect(hItem,&HotDownload::sig_itemSizeChanged,this,&VipMember::resizeListWidgetItemWidget);
    }

    for(int i = 0; i < 6; i++)
    {
        HotSort *hItem = new HotSort();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(hItem->size());
        ui->listWidget_vipshared->addItem(item);
        ui->listWidget_vipshared->setItemWidget(item,hItem);
        //槽函数

    }
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

