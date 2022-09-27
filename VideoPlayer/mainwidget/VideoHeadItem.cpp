#include "VideoHeadItem.h"
#include "ui_VideoHeadItem.h"

VideoHeadItem::VideoHeadItem(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::VideoHeadItem)
{
    ui->setupUi(this);
}

VideoHeadItem::~VideoHeadItem()
{
    delete ui;
}
