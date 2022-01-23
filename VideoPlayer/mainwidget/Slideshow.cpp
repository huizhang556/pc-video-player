#include "Slideshow.h"
#include "ui_Slideshow.h"
#include <QDebug>

Slideshow::Slideshow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Slideshow)
{
    ui->setupUi(this);
}

Slideshow::~Slideshow()
{
    delete ui;
}

//左移动
void Slideshow::on_pushButton_left_clicked()
{
    qDebug() <<"left move";
}

//右移动
void Slideshow::on_pushButton_right_clicked()
{
    qDebug() <<"right move";
}
