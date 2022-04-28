#include "PicWallItem.h"
#include "ui_PicWallItem.h"
#include <QPixmap>
#include <QDebug>

PicWallItem::PicWallItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicWallItem)
{
    ui->setupUi(this);
    this->setFixedSize(200,180);
}

PicWallItem::~PicWallItem()
{
    delete ui;
}


void PicWallItem::setPicItemWall(QString path)
{
    QPixmap pix(path);
    ui->label_wallitem->setPixmap(pix);
    ui->label_wallitem->setScaledContents(true);//自适应
}

void PicWallItem::setPicItemWallText(QString text)
{
    ui->pushButton_wall_title->setText(text);
}
