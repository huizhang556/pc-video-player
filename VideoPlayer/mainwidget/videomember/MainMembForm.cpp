#include "MainMembForm.h"
#include "ui_MainMembForm.h"

#include "CusStackWidget.h"
#include "VideoSortType.h"
#include "SwitchVideoType.h"

#include <QDebug>

MainMembForm::MainMembForm(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MainMembForm)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

MainMembForm::~MainMembForm()
{
    delete ui;
}

void MainMembForm::initWorkUI()
{
    ui->scrollArea->setFrameShape(QFrame::NoFrame);//继承自QFrame的，都可以用此方法去掉边界线
    CusStackWidget *itemWidget    = new CusStackWidget();
    SwitchVideoType *switchItem   = new SwitchVideoType();
    VideoSortType *videoSortItem1 = new VideoSortType();
    VideoSortType *videoSortItem2 = new VideoSortType();
    VideoSortType *videoSortItem3 = new VideoSortType();
    VideoSortType *videoSortItem4 = new VideoSortType();
    VideoSortType *videoSortItem5 = new VideoSortType();
    ui->m_itemsLayout->addWidget(itemWidget);
    ui->m_itemsLayout->addWidget(switchItem);
    ui->m_itemsLayout->addWidget(videoSortItem1);
    ui->m_itemsLayout->addWidget(videoSortItem2);
    ui->m_itemsLayout->addWidget(videoSortItem3);
    ui->m_itemsLayout->addWidget(videoSortItem4);
    ui->m_itemsLayout->addWidget(videoSortItem5);
}

void MainMembForm::handleSignalsAndSlots()
{

}

void MainMembForm::setInstallEventFilter()
{

}
