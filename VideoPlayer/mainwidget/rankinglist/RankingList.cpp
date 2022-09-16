#include "RankingList.h"
#include "ui_RankingList.h"
#include "mainwidget/TrianButton.h"
#include "mainwidget/rankinglist/RankItem.h"
#include "mainwidget/rankinglist/RankListItem.h"
#include <QListWidgetItem>
#include <QScrollBar>
#include <QDebug>

RankingList::RankingList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RankingList)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

RankingList::~RankingList()
{
    delete ui;
}

void RankingList::initWorkUI()
{
    ui->pushButton_raisesong->setButtonType(ButtonType::LeftType);
    ui->pushButton_newsong->setButtonType(ButtonType::MidType);
    ui->pushButton_hotsong->setButtonType(ButtonType::rightType);
    ui->pushButton_raisesong->setButtonPicture("://images/home/rank_raisesong.png");
    ui->pushButton_newsong->setButtonPicture("://images/home/rank_hotsong.png");
    ui->pushButton_hotsong->setButtonPicture("://images/home/rank_newsong.png");

    m_buttonGroup1 = new QButtonGroup(this);
    m_buttonGroup1->addButton(ui->pushButton_raisesong,0);
    m_buttonGroup1->addButton(ui->pushButton_newsong,1);
    m_buttonGroup1->addButton(ui->pushButton_hotsong,2);

    for(int i = 0; i < 3; i++)
    {
        m_buttonGroup1->button(i)->setCheckable(true);
    }
    ui->pushButton_raisesong->setChecked(true);

    ui->listWidget_left->setViewMode(QListView::ListMode);
    ui->listWidget_left->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_left->setResizeMode(QListWidget::Adjust);
//    ui->listWidget_left->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_left->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_left->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_left->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->listWidget_right->setViewMode(QListView::ListMode);
    ui->listWidget_right->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_right->setResizeMode(QListWidget::Adjust);
//    ui->listWidget_right->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_right->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_right->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_right->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->listWidget_feature->setViewMode(QListView::ListMode);
    ui->listWidget_feature->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_feature->setResizeMode(QListWidget::Adjust);
//    ui->listWidget_feature->setWrapping(true);//自动换行 所有itm在一行显示
//    ui->listWidget_feature->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->listWidget_feature->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_feature->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->listWidget_left->setMinimumHeight(40*10);
    ui->listWidget_right->setMinimumHeight(40*10);
    ui->scrollArea->setWidgetResizable(true);
    slot_addRankListItem();
}

void RankingList::handleSignalsAndSlots()
{
    connect(m_buttonGroup1,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_setCheckedButton(QAbstractButton*)));
}

void RankingList::setInstallEventFilter()
{
    ui->listWidget_feature->installEventFilter(this);
}

void RankingList::slot_addRankListItem()
{
    for(int i = 0; i < 10; i++)
    {
        RankItem *itemWidget = new RankItem();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(itemWidget->size()));
        ui->listWidget_left->addItem(item);
        ui->listWidget_left->setItemWidget(item,itemWidget);
    }

    for(int i = 0; i < 10; i++)
    {
        RankItem *itemWidget = new RankItem();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(itemWidget->size()));
        ui->listWidget_right->addItem(item);
        ui->listWidget_right->setItemWidget(item,itemWidget);
    }

    for(int i = 0; i < 6; i++)
    {
       slot_addSongItem_recommend();
    }

    ui->listWidget_feature->setMinimumHeight((230*2+60)*ui->listWidget_feature->count()+ui->listWidget_feature->horizontalScrollBar()->height());
}

void RankingList::slot_addSongItem_recommend()
{
    RankListItem *itemWidget = new RankListItem();
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(itemWidget->size());
    ui->listWidget_feature->addItem(item);
    ui->listWidget_feature->setItemWidget(item,itemWidget);
    //调整大小
    connect(itemWidget,&RankListItem::sig_itemSizeChanged,[=](QSize size){
        for(int i = 0; i < ui->listWidget_feature->count(); i++)
        {
            ui->listWidget_feature->item(i)->setSizeHint(size);
        }
//        ui->listWidget_feature->setMinimumHeight(ui->listWidget_feature->count()*size.height());
    });
}

void RankingList::slot_setCheckedButton(QAbstractButton *button)
{
    button->setChecked(true);
}

bool RankingList::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_feature)
    {
        if(event->type() == QEvent::Resize)
        {
            resizeListWidgetItemWidget();
        }

    }
    return QWidget::eventFilter(watched,event);
}

void RankingList::resizeListWidgetItemWidget()
{
    ui->scrollArea->verticalScrollBar()->setValue(ui->listWidget_feature->height()+ui->widget_recommed->height()+ui->widget_title->height());
}

