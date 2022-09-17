#include "MVSortType.h"
#include "ui_MVSortType.h"

#include "mainwidget/videosmv/VideoItem.h"
#include <QListWidgetItem>
#include <QScrollBar>
#include <QDebug>

MVSortType::MVSortType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MVSortType)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

MVSortType::~MVSortType()
{
    delete ui;
}

void MVSortType::initWorkUI()
{
    ui->listWidget_sort->setViewMode(QListView::IconMode);
    ui->listWidget_sort->setMovement(QListView::Static);
    ui->listWidget_sort->setResizeMode(QListView::Adjust);
//    ui->listWidget_sort->setWrapping(true);//自动换行 所有itm在一行显示
//    ui->listWidget_sort->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_sort->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_sort->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->pushButton_mark1->setCheckable(true);
    ui->pushButton_mark2->setCheckable(true);
    ui->pushButton_mark3->setCheckable(true);
    ui->pushButton_mark1->setChecked(true);

    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(ui->pushButton_mark1,0);
    m_buttonGroup->addButton(ui->pushButton_mark2,1);
    m_buttonGroup->addButton(ui->pushButton_mark3,2);

    for(int i = 0; i < 100; i++)
    {
        VideoItem *itemWidget = new VideoItem();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());

        ui->listWidget_sort->addItem(item);
        ui->listWidget_sort->setItemWidget(item,itemWidget);
    }
}

void MVSortType::handleSignalsAndSlots()
{
    connect(m_buttonGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_setButtonChecked(QAbstractButton*)));
}

void MVSortType::setInstallEventFilter()
{
    ui->listWidget_sort->installEventFilter(this);
}

bool MVSortType::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_sort)
    {
        if(event->type() == QEvent::Resize)
        {
            resizeListWidgetItemSize();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void MVSortType::slot_setButtonChecked(QAbstractButton *button)
{
    button->setChecked(true);
}

void MVSortType::resizeListWidgetItemSize()
{
    int width = ui->listWidget_sort->width();
    int fitWidth = (width - ui->listWidget_sort->verticalScrollBar()->width() -1)/5;
    if(fitWidth < 300)
    {
        int Width_4 = (width - ui->listWidget_sort->verticalScrollBar()->width() -1)/4;
        for(int i = 0; i< ui->listWidget_sort->count(); i++)
        {
            ui->listWidget_sort->item(i)->setSizeHint(QSize(Width_4,(Width_4)*SCALE));
        }
    }
    else
    {
        for(int i = 0; i< ui->listWidget_sort->count(); i++)
        {
            ui->listWidget_sort->item(i)->setSizeHint(QSize(fitWidth,(fitWidth)*SCALE));
        }
    }
}
