#include "RecmmendVideoItem.h"
#include "ui_RecmmendVideoItem.h"

#include "mainwidget/videosmv/VideoItem.h"
#include <QListWidgetItem>
#include <QScrollBar>
#include <QDebug>

RecmmendVideoItem::RecmmendVideoItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecmmendVideoItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

RecmmendVideoItem::~RecmmendVideoItem()
{
    delete ui;
}

void RecmmendVideoItem::initWorkUI()
{
    ui->pushButton_mark1->setCheckable(true);
    ui->pushButton_mark2->setCheckable(true);
    ui->pushButton_mark3->setCheckable(true);
    ui->pushButton_mark1->setChecked(true);

    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(ui->pushButton_mark1,0);
    m_buttonGroup->addButton(ui->pushButton_mark2,1);
    m_buttonGroup->addButton(ui->pushButton_mark3,2);

    ui->listWidget_recomItem->setViewMode(QListView::IconMode);
    ui->listWidget_recomItem->setMovement(QListView::Static);
    ui->listWidget_recomItem->setResizeMode(QListView::Adjust);
//    ui->listWidget_recomItem->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_recomItem->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_recomItem->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_recomItem->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    for(int i = 0; i < 10; i++)
    {
        VideoItem *itemWidget = new VideoItem();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());

        ui->listWidget_recomItem->addItem(item);
        ui->listWidget_recomItem->setItemWidget(item,itemWidget);
    }
}

void RecmmendVideoItem::handleSignalsAndSlots()
{
    connect(m_buttonGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_setButtonChecked(QAbstractButton*)));
}

void RecmmendVideoItem::setInstallEventFilter()
{
    ui->listWidget_recomItem->installEventFilter(this);
}

bool RecmmendVideoItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_recomItem)
        if(event->type() == QEvent::Resize)
        {
            resizeListWidgetItemSize();
        }
    return QWidget::eventFilter(watched,event);
}

void RecmmendVideoItem::resizeListWidgetItemSize()
{
    int width = ui->listWidget_recomItem->width();
    int fitWidth = (width - ui->listWidget_recomItem->verticalScrollBar()->width() +99)/5;
    if(fitWidth < 300)
    {
        int Width_4 = (width - ui->listWidget_recomItem->verticalScrollBar()->width() +99)/4;
        for(int i = 0; i< ui->listWidget_recomItem->count(); i++)
        {
            ui->listWidget_recomItem->item(i)->setSizeHint(QSize(Width_4,(Width_4)*SCALE));
        }
    }
    else
    {
        for(int i = 0; i< ui->listWidget_recomItem->count(); i++)
        {
            ui->listWidget_recomItem->item(i)->setSizeHint(QSize(fitWidth,(fitWidth)*SCALE));
        }
    }
}

void RecmmendVideoItem::slot_setButtonChecked(QAbstractButton *button)
{
    button->setChecked(true);
}
