#include "BuyVipItem.h"
#include "ui_BuyVipItem.h"

BuyVipItem::BuyVipItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuyVipItem)
{
    ui->setupUi(this);
    setFixedSize(170,100);
}

BuyVipItem::~BuyVipItem()
{
    delete ui;
}
