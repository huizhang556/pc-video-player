#include "PicWallItem.h"
#include "ui_PicWallItem.h"
#include <QDebug>
#include <QPixmap>

PicWallItem::PicWallItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicWallItem)
{
    ui->setupUi(this);
    this->setMinimumSize(200,436);
}

PicWallItem::~PicWallItem()
{
    delete ui;
}

QPushButton* PicWallItem::getWallItemTextButton()
{
    return ui->pushButton_wall_title1;
}


void PicWallItem::setPicItemWall(QString path)
{
    QPixmap pix(path);
    ui->label_wallitem1->setPixmap(pix);
    ui->label_wallitem1->setScaledContents(true);//自适应

}

void PicWallItem::setPicItemWallText(QString text)
{
    ui->pushButton_wall_title1->setText(text);

}

void PicWallItem::setPicItemWall2(QString path)
{
    QPixmap pix(path);
    ui->label_wallitem2->setPixmap(pix);
    ui->label_wallitem2->setScaledContents(true);//自适应
}

void PicWallItem::setPicItemWallText2(QString text)
{
    ui->pushButton_wall_title2->setText(text);
}

void PicWallItem::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    emit sig_sizeChange(this->size());
}
