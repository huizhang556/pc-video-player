#include "MainMembForm.h"
#include "global/Global.h"
#include "ui_MainMembForm.h"
#include "mainwidget/CusVerStackWgt.h"
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
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    CusVerStackWgt *itemWidget  = new CusVerStackWgt();
    for(int i = 0; i < 6; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall/stack%1.png").arg(i);
        itemWidget->slot_addItemToCusVerStackWgt(path);
    }

    SwitchVideoType *switchItem   = new SwitchVideoType();

    ui->m_itemsLayout->addWidget(itemWidget);
    ui->m_itemsLayout->addWidget(switchItem);

    for(int i = 0; i < 20; i++)
    {
        VideoSortType *videoSortItem1 = new VideoSortType();
        ui->m_itemsLayout->addWidget(videoSortItem1);
    }

}

void MainMembForm::handleSignalsAndSlots()
{

}

void MainMembForm::setInstallEventFilter()
{

}
