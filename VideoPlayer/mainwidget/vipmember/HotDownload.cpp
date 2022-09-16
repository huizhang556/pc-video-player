#include "HotDownload.h"
#include "ui_HotDownload.h"

#include "mainwidget/vipmember/HotDownloadItem.h"

#include <QListWidgetItem>
#include <QScrollBar>
#include <QDebug>

HotDownload::HotDownload(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotDownload)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    this->setMinimumHeight(82*3 + 60);
}

HotDownload::~HotDownload()
{
    delete ui;
}

void HotDownload::initWorkUI()
{

    ui->listWidget_vipHot->setViewMode(QListView::IconMode);
    ui->listWidget_vipHot->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_vipHot->setResizeMode(QListWidget::Adjust);
    ui->listWidget_vipHot->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_vipHot->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_vipHot->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_vipHot->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->pushButton_title->setIcon(QIcon(":/images/user/itemmark_vyp.png"));
    ui->pushButton_title->setIconSize(QSize(36,36));

    for(int i = 0; i < 9; i++)
    {
        HotDownloadItem *itemWidget = new HotDownloadItem();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(itemWidget->size()));
        ui->listWidget_vipHot->addItem(item);
        ui->listWidget_vipHot->setItemWidget(item,itemWidget);
    }

    ui->listWidget_vipHot->setMinimumHeight(82*3+ui->listWidget_vipHot->horizontalScrollBar()->height());
}

void HotDownload::handleSignalsAndSlots()
{

}

void HotDownload::setInstallEventFilter()
{
    ui->listWidget_vipHot->installEventFilter(this);
}

void HotDownload::slot_addItem()
{

}

bool HotDownload::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_vipHot)
    {
       if(event->type() == QEvent::Resize)
       {
           updateGeometry();
           resizeListWidgetItemWidget();
       }
    }
    return QWidget::eventFilter(watched,event);
}

void HotDownload::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    resizeListWidgetItemWidget();
}

void HotDownload::resizeListWidgetItemWidget()
{
    int width = ui->listWidget_vipHot->width();
    int fitWidth = (int)((width - ui->listWidget_vipHot->verticalScrollBar()->width() - 1)/3);
    int fitWidth1 = (int)((width - ui->listWidget_vipHot->verticalScrollBar()->width() - 1)/2);
    //滚动条默认宽度17
    for(int i = 0; i<ui->listWidget_vipHot->count();i++)
    {
        if(fitWidth < MINSIZE.width())
        {
            ui->listWidget_vipHot->item(i)->setSizeHint(QSize(fitWidth1+50,82));
        }
        else
        {
            ui->listWidget_vipHot->item(i)->setSizeHint(QSize(fitWidth+33,82));
        }
    }
    emit sig_itemSizeChanged(QSize(this->width(),82*3-15));
    ui->listWidget_vipHot->setMinimumHeight(82*3-15);
    updateGeometry();
}
