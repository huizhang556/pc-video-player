#include "CusVideosBox.h"
#include "ui_CusVideosBox.h"
#include "global/Global.h"
#include "mainwidget/CusVerStackWgt.h"
#include "mainwidget/subunititems/Container00.h"
#include "mainwidget/subunititems/Container01.h"
#include "mainwidget/videomember/CusStackWidget.h"

CusVideosBox::CusVideosBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CusVideosBox)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusVideosBox::~CusVideosBox()
{
    delete ui;
}

void CusVideosBox::initWorkUI()
{
    ui->scrollArea->setFrameShape(QFrame::NoFrame);//继承自QFrame的，都可以用此方法去掉边界线
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    CusStackWidget *itemWidget  = new CusStackWidget();
    Container00 *containerItem1 = new Container00(QString(u8"独家剧有料"));
    Container00 *containerItem11 = new Container00(QString(u8"宠爱现场"));
    Container01 *containerItem2 = new Container01(QString(u8"最新预告"),QString(Global::appDirPath +"/pictures/cusvideoitem/cusvideoitem_left%1.png").arg(1));
    Container00 *containerItem3 = new Container00(QString(u8"港剧场"));
    Container00 *containerItem33 = new Container00(QString(u8"小剧场"));
    Container01 *containerItem4 = new Container01(QString(u8"网络电影"),QString(Global::appDirPath +"/pictures/cusvideoitem/cusvideoitem_left%1.png").arg(2));
    Container00 *containerItem5 = new Container00(QString(u8"卫视剧专区"));
    Container00 *containerItem55 = new Container00(QString(u8"独家经典剧场"));
    Container01 *containerItem6 = new Container01(QString(u8"经典回看"),QString(Global::appDirPath +"/pictures/cusvideoitem/cusvideoitem_left%1.png").arg(3));
    ui->m_itemsLayout->addWidget(itemWidget);
    ui->m_itemsLayout->addWidget(containerItem1);
    ui->m_itemsLayout->addWidget(containerItem11);
    ui->m_itemsLayout->addWidget(containerItem2);
    ui->m_itemsLayout->addWidget(containerItem3);
    ui->m_itemsLayout->addWidget(containerItem33);
    ui->m_itemsLayout->addWidget(containerItem4);
    ui->m_itemsLayout->addWidget(containerItem5);
    ui->m_itemsLayout->addWidget(containerItem55);
    ui->m_itemsLayout->addWidget(containerItem6);
}

void CusVideosBox::handleSignalsAndSlots()
{

}

void CusVideosBox::setInstallEventFilter()
{

}
