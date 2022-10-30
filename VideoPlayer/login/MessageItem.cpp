#include "MessageItem.h"
#include "ui_MessageItem.h"

MessageItem::MessageItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageItem)
{
    ui->setupUi(this);
}

MessageItem::~MessageItem()
{
    delete ui;
}
