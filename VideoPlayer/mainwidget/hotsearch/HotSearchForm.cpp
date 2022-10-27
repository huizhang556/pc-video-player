#include "HotSearchForm.h"
#include "ui_HotSearchForm.h"
#include "mainwidget/hotsearch/HotSearchItem.h"

#include <QTreeWidgetItem>
#include <QDebug>

HotSearchForm::HotSearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotSearchForm)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

HotSearchForm::~HotSearchForm()
{
    delete ui;
}

void HotSearchForm::initWorkUI()
{
    ui->treeWidget_1->setMinimumHeight(520);
    ui->treeWidget_2->setMinimumHeight(520);
    ui->treeWidget_3->setMinimumHeight(520);
    ui->treeWidget_4->setMinimumHeight(520);
    ui->treeWidget_5->setMinimumHeight(520);
    ui->treeWidget_6->setMinimumHeight(520);
    ui->treeWidget_7->setMinimumHeight(520);
    ui->treeWidget_8->setMinimumHeight(520);
    ui->treeWidget_9->setMinimumHeight(520);

    ui->treeWidget_1->setMinimumWidth(360);
    ui->treeWidget_2->setMinimumWidth(360);
    ui->treeWidget_3->setMinimumWidth(360);
    ui->treeWidget_4->setMinimumWidth(360);
    ui->treeWidget_5->setMinimumWidth(360);
    ui->treeWidget_6->setMinimumWidth(360);
    ui->treeWidget_7->setMinimumWidth(360);
    ui->treeWidget_8->setMinimumWidth(360);
    ui->treeWidget_9->setMinimumWidth(360);

    ui->treeWidget_1->setHeaderLabel(QString(u8"热门搜索"));
    ui->treeWidget_2->setHeaderLabel(QString(u8"全网热点"));
    ui->treeWidget_3->setHeaderLabel(QString(u8"电视剧"));
    ui->treeWidget_4->setHeaderLabel(QString(u8"综艺"));
    ui->treeWidget_5->setHeaderLabel(QString(u8"电影"));
    ui->treeWidget_6->setHeaderLabel(QString(u8"动漫"));
    ui->treeWidget_7->setHeaderLabel(QString(u8"少儿"));
    ui->treeWidget_8->setHeaderLabel(QString(u8"纪录片"));
    ui->treeWidget_9->setHeaderLabel(QString(u8"文化"));


    for(int i = 0; i < 10; i++)
    {
        slot_addItemToTreeWgt(ui->treeWidget_1,QString::number(i+1),QString(u8"热门搜索--->热搜%1").arg(i+1),true);
        slot_addItemToTreeWgt(ui->treeWidget_2,QString::number(i+1),QString(u8"全网热点--->热搜%1").arg(i+1),false);
        slot_addItemToTreeWgt(ui->treeWidget_3,QString::number(i+1),QString(u8"全网电视剧--->热搜%1").arg(i+1),true);
        slot_addItemToTreeWgt(ui->treeWidget_4,QString::number(i+1),QString(u8"全网综艺--->热搜%1").arg(i+1),false);
        slot_addItemToTreeWgt(ui->treeWidget_5,QString::number(i+1),QString(u8"全网电影--->热搜%1").arg(i+1),true);
        slot_addItemToTreeWgt(ui->treeWidget_6,QString::number(i+1),QString(u8"全网动漫--->热搜%1").arg(i+1),false);
        slot_addItemToTreeWgt(ui->treeWidget_7,QString::number(i+1),QString(u8"全网少儿--->热搜%1").arg(i+1),true);
        slot_addItemToTreeWgt(ui->treeWidget_8,QString::number(i+1),QString(u8"全网纪录片--->热搜%1").arg(i+1),false);
        slot_addItemToTreeWgt(ui->treeWidget_9,QString::number(i+1),QString(u8"全网文化--->热搜%1").arg(i+1),true);
    }

}

void HotSearchForm::handleSignalsAndSlots()
{

}

void HotSearchForm::slot_addItemToTreeWgt(QTreeWidget *treeWgt, const QString &order, const QString &text, bool up)
{
    HotSearchItem *itemWidget = new HotSearchItem(order,text,m_up);
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();
    treeItem->setSizeHint(0,itemWidget->size());
    treeWgt->addTopLevelItem(treeItem);
    treeWgt->setItemWidget(treeItem,0,itemWidget);
    m_up = !m_up;
    connect(itemWidget,&HotSearchItem::sig_sendItemText,[=](QString text){
       qDebug() << text;
    });
}
