#include "PerCenter.h"
#include "ui_PerCenter.h"

PerCenter::PerCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PerCenter)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
}

PerCenter::~PerCenter()
{
    delete ui;
}

void PerCenter::initWorkUI()
{
    ui->label_header->setToolTip(QString(u8"单击修改头像"));

    ui->toolBox_center->layout()->setSpacing(1);//item之间的间距
    ui->toolBox_center->setItemIcon(0,QIcon(""));
    ui->toolBox_center->setItemIcon(1,QIcon(""));
    ui->toolBox_center->setItemIcon(2,QIcon(""));
    ui->toolBox_center->setItemIcon(3,QIcon(""));

    for(int i = 0; i < ui->listWidget_perCenter->count(); i++)
    {
        ui->listWidget_perCenter->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }

    for(int i = 0; i < ui->listWidget_shortVideo->count(); i++)
    {
        ui->listWidget_shortVideo->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }

    for(int i = 0; i < ui->listWidget_midVideo->count(); i++)
    {
        ui->listWidget_midVideo->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }

    for(int i = 0; i < ui->listWidget_musics->count(); i++)
    {
        ui->listWidget_musics->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }
}

void PerCenter::handleSignalsAndSlots()
{
    //修改头像
    connect(ui->label_header,&RoundLab::sig_clicked,[=](){
        ChangeHead::getInstance()->exec_(OPENTYPE::PER_HEAD);
    });

    connect(ui->pushButton_newcreate,&QPushButton::clicked,[=](){
        emit sig_person_createguid();
        qDebug() <<QString(u8"新手创作");
    });

    connect(ui->pushButton_polish,&QPushButton::clicked,[=](){
        emit sig_person_polish();
        qDebug() <<QString(u8"发布视频");
    });
}

void PerCenter::setInstallEventer()
{

}

void PerCenter::setCurUserInfo(const QString &name, const QPixmap &pix)
{
    ui->pushButton_userName->setText(name);
    ui->label_header->setPixmap_(pix);
    ui->label_header->setScaledContents(true);
}
