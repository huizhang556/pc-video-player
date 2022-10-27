#include "SubUnitItem.h"
#include "ui_SubUnitItem.h"

SubUnitItem::SubUnitItem(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::SubUnitItem)
{
    ui->setupUi(this);
}

SubUnitItem::~SubUnitItem()
{
    delete ui;
}
