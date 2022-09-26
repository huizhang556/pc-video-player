#include "VideoBlank.h"
#include "ui_VideoBlank.h"
#include <QDebug>

VideoBlank::VideoBlank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoBlank)
{
    ui->setupUi(this);

    ui->pushButton_openfile->setIcon(QIcon(":/images/icon/openfile.png"));
    ui->pushButton_openfile->setIconSize(QSize(26,18));

    connect(ui->pushButton_openfile,&QPushButton::clicked,[=]()
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
    if(hide)//真 不隐藏
    {
        ui->pushButton_openfile->setHidden(false);
    }
    else//假 隐藏
    {
        ui->pushButton_openfile->setHidden(true);
    }
}


