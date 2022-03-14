#include "VideoBlank.h"
#include "ui_VideoBlank.h"
#include <QDebug>

VideoBlank::VideoBlank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoBlank)
{
    ui->setupUi(this);
    connect(ui->Btn_blank,&QPushButton::clicked,[=]()
    {
        emit sig_openLocalFile();
        qDebug() <<"emit sig_openLocalFile!" ;
    });
}

VideoBlank::~VideoBlank()
{
    delete ui;
}

void VideoBlank::setHideOpenButton(bool hide)
{
    if(hide)
    {
        ui->Btn_blank->setHidden(true);
    }
    else
    {
        ui->Btn_blank->setHidden(false);
    }
}


