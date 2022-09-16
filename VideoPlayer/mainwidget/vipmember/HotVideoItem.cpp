#include "HotVideoItem.h"
#include "ui_HotVideoItem.h"

HotVideoItem::HotVideoItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotVideoItem)
{
    ui->setupUi(this);
}

HotVideoItem::~HotVideoItem()
{
    delete ui;
}
