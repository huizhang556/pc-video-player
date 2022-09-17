#include "MVRecmmend.h"
#include "ui_MVRecmmend.h"


#include "mainwidget/videosmv/MultipType.h"
#include "mainwidget/videosmv/RecmmendVideoItem.h"

#include <QListWidgetItem>
#include <QDebug>

MVRecmmend::MVRecmmend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MVRecmmend)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

MVRecmmend::~MVRecmmend()
{
    delete ui;
}

void MVRecmmend::initWorkUI()
{
    ui->listWidget_recmmend->setViewMode(QListView::ListMode);
    ui->listWidget_recmmend->setMovement(QListView::Static);
    ui->listWidget_recmmend->setResizeMode(QListView::Adjust);
//    ui->listWidget_recmmend->setWrapping(true);//自动换行 所有itm在一行显示
//    ui->listWidget_recmmend->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_recmmend->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_recmmend->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    for(int i = 0; i < 2; i++)
    {
        MvType *itemWidget = new MvType();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());

        ui->listWidget_recmmend->addItem(item);
        ui->listWidget_recmmend->setItemWidget(item,itemWidget);
    }

    for(int i = 0; i < 6; i++)
    {
        RecmmendVideoItem *itemWidget = new RecmmendVideoItem();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());

        ui->listWidget_recmmend->addItem(item);
        ui->listWidget_recmmend->setItemWidget(item,itemWidget);
    }
}

void MVRecmmend::handleSignalsAndSlots()
{

}

void MVRecmmend::setInstallEventFilter()
{

}
