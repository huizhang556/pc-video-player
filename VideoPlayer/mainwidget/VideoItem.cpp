#include "VideoItem.h"
#include "ui_VideoItem.h"

VideoItem::VideoItem(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::VideoItem)
{
    ui->setupUi(this);
}

VideoItem::~VideoItem()
{
    delete ui;
}
