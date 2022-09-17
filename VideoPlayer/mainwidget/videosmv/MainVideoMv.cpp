#include "MainVideoMv.h"
#include "ui_MainVideoMv.h"

#include "mainwidget/videosmv/MVRecmmend.h"
#include "mainwidget/videosmv/MVSortType.h"

#include <QListWidgetItem>
#include <QDebug>

VideoMv::VideoMv(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoMv)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

VideoMv::~VideoMv()
{
    delete ui;
}

void VideoMv::initWorkUI()
{
    ui->pushButton_recommend->setCheckable(true);
    ui->pushButton_mvSort->setCheckable(true);
    ui->pushButton_recommend->setChecked(true);

    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(ui->pushButton_recommend,0);
    m_buttonGroup->addButton(ui->pushButton_mvSort,1);


    MVRecmmend *itemRecmmend = new MVRecmmend();
    MVSortType *itemSort = new MVSortType();

    ui->stackedWidget_sort->addWidget(itemRecmmend);
    ui->stackedWidget_sort->addWidget(itemSort);
}

void VideoMv::handleSignalsAndSlots()
{
//    connect(m_buttonGroup,&QButtonGroup::buttonClicked,this,&VideoMv::slot_setButtonChecked);
    connect(m_buttonGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_setButtonChecked(QAbstractButton*)));

    connect(ui->pushButton_recommend,&QPushButton::clicked,[=](){
        ui->stackedWidget_sort->setCurrentIndex(0);
    });
    connect(ui->pushButton_mvSort,&QPushButton::clicked,[=](){
        ui->stackedWidget_sort->setCurrentIndex(1);
    });
}

void VideoMv::setInstallEventFilter()
{

}

void VideoMv::slot_globalResize()
{
    this->resize(1,1);
    qDebug() << QString(u8"视频界面已更新！");
}

void VideoMv::slot_setButtonChecked(QAbstractButton *button)
{
    button->setChecked(true);
}
