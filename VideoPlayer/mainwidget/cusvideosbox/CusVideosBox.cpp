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
    for(int i = 0; i < 10; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall2/stackwall%1.jpg").arg(i);
        itemWidget->slot_addItemToStackWgt(path);
    }
    itemWidget->setSelectType(0);//去掉左右按钮
    ui->m_itemsLayout->addWidget(itemWidget);

    for(int i = 0; i < 10; i++)
    {
        Container00 *containerItem1 = new Container00(QString(u8"独家剧有料"));
        Container00 *containerItem11 = new Container00(QString(u8"宠爱现场"));
        Container01 *containerItem2 = new Container01(QString(u8"最新预告"),QString(Global::appDirPath +"/pictures/cusvideoitem/cusvideoitem_left%1.png").arg(1));

        ui->m_itemsLayout->addWidget(containerItem1);
        ui->m_itemsLayout->addWidget(containerItem11);
        ui->m_itemsLayout->addWidget(containerItem2);
    }
}

void CusVideosBox::handleSignalsAndSlots()
{

}

void CusVideosBox::setInstallEventFilter()
{

}
