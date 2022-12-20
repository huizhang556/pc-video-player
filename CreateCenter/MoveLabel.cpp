#include "MoveLabel.h"
#include "ui_MoveLabel.h"
#include "Global.h"

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

    connect(ui->pushButton_clogin,&QPushButton::clicked,[=](){  emit sig_sendLogin(); });
    connect(ui->pushButton_minClose,&QPushButton::clicked,[=](){  emit sig_sendClose(); });
}

MoveLabel::~MoveLabel()
{
    delete ui;
}
