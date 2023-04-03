#include "CusLabel3.h"
#include "ui_CusLabel3.h"

CusLabel3::CusLabel3(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::CusLabel3)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

CusLabel3::~CusLabel3()
{
    delete ui;
}

void CusLabel3::initWorkUI()
{
    ui->pushButton_play->setToolTip(QString(u8"播放"));
    ui->pushButton_start->setToolTip(QString(u8"收藏"));
}

void CusLabel3::handleSignalsAndSlots()
{
    connect(ui->pushButton_play,&QPushButton::clicked,[=](){
        emit sig_send_play();
    });

    connect(ui->pushButton_start,&QPushButton::clicked,[=](){
        emit sig_send_start();
    });
}
