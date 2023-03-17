#include "MoveLabel.h"
#include "ui_MoveLabel.h"
#include "global/Global.h"

MoveLabel::MoveLabel(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::MoveLabel)
{
    ui->setupUi(this);
    m_gifpath = Global::appDirPath + "/pictures/splashscreen/move_jif_00.gif";
    m_movie = new QMovie(m_gifpath);
    setMovie(m_movie);
    setScaledContents(true);
    m_movie->start();
    ui->pushButton_clogin->setText(QString(u8"点击登录"));
    ui->pushButton_clogin->setEnabled(true);
    connect(ui->pushButton_clogin,&QPushButton::clicked,[=](){  emit sig_sendLogin(); });
    connect(ui->pushButton_minClose,&QPushButton::clicked,[=](){  emit sig_sendClose(); });
}

MoveLabel::~MoveLabel()
{
    delete ui;
}

void MoveLabel::setLoginTips(bool online)
{
    if(online)
    {
        ui->pushButton_clogin->setEnabled(true);
        ui->label_tips->setText(QString(u8"当前已有账户登录，点击快捷登录！"));
    }
    else
    {
        ui->label_tips->setText(QString(u8"您暂时未登录账号，请先登录账号！"));
        ui->pushButton_clogin->setEnabled(false);
    }
}
