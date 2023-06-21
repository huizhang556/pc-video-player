#include "UserDataItem.h"
#include "ui_UserDataItem.h"

UserDataItem::UserDataItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserDataItem)
{
    ui->setupUi(this);
}

UserDataItem::~UserDataItem()
{
    delete ui;
}
