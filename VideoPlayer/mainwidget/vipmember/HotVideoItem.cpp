#include "HotVideoItem.h"
#include "ui_HotVideoItem.h"

HotVideoItem::HotVideoItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotVideoItem)
{
    ui->setupUi(this);
    setFixedSize(365,300);
}

HotVideoItem::~HotVideoItem()
{
    delete ui;
}
