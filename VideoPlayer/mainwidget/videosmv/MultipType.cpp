#include "MultipType.h"
#include "ui_MultipType.h"

#include "mainwidget/videosmv/VideoItem.h"
#include <QListWidgetItem>
#include <QScrollBar>
#include <QDebug>

MvType::MvType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MvType)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

MvType::~MvType()
{
    delete ui;
}

void MvType::initWorkUI()
{
    ui->label_picMv->constructItem(":/images/videosmv/rectitle/music1.png","://images/user/itemmark_new.png",QString(u8"6.6"),true,true,false);

    ui->listWidget_list->setViewMode(QListView::IconMode);
    ui->listWidget_list->setMovement(QListView::Static);
    ui->listWidget_list->setResizeMode(QListView::Adjust);
//    ui->listWidget_list->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_list->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    for(int i = 0; i < 6; i++)
    {
        VideoItem *itemWidget = new VideoItem();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());

        ui->listWidget_list->addItem(item);
        ui->listWidget_list->setItemWidget(item,itemWidget);
    }
}

void MvType::handleSignalsAndSlots()
{

}

void MvType::setInstallEventFilter()
{
    ui->listWidget_list->installEventFilter(this);
}

bool MvType::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_list)
    {
        if(event->type() == QEvent::Resize)
        {
            resizeListWidgetItemSize();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void MvType::resizeListWidgetItemSize()
{
    int width = ui->listWidget_list->width();
    int fitWidth = (width - ui->listWidget_list->verticalScrollBar()->width() +99)/3;
    if(fitWidth < 300)
    {
        int Width_4 = (width - ui->listWidget_list->verticalScrollBar()->width() +99)/2;
        for(int i = 0; i< ui->listWidget_list->count(); i++)
        {
            ui->listWidget_list->item(i)->setSizeHint(QSize(Width_4,(Width_4)*SCALE));
        }
    }
    else
    {
        for(int i = 0; i< ui->listWidget_list->count(); i++)
        {
            ui->listWidget_list->item(i)->setSizeHint(QSize(fitWidth,(fitWidth)*SCALE));
        }
    }
}
