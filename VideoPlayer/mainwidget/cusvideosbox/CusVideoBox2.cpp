#include "CusVideoBox2.h"
#include "ui_CusVideoBox2.h"
#include "global/Global.h"
#include <QDebug>

CusVideoBox2::CusVideoBox2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CusVideoBox2)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusVideoBox2::~CusVideoBox2()
{
    delete ui;
}

void CusVideoBox2::initWorkUI()
{
    ui->scrollArea->setFrameShape(QFrame::NoFrame);//继承自QFrame的，都可以用此方法去掉边界线
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_switchStackWgt = new SwitchStackWgt(this);
    m_switchStackWgt->setObjectName(QString::fromLocal8Bit("m_switchStackWgt"));

    for(int i = 0; i < 6; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall/stack%1.png").arg(i);
        m_switchStackWgt->slot_addToStackItemPicture(path);
    }
    addItemToVideosBox(m_switchStackWgt);

    for(int i = 0; i < 6; i++)
    {
        VideoSortType *videoSortItem1 = new VideoSortType();
//        Container01 *container01_1 = new Container01();
        Container00 *container00_1 = new Container00();
        Container00 *container00_2 = new Container00();
        addItemToVideosBox(videoSortItem1);
//        addItemToVideosBox(container01_1);
        addItemToVideosBox(container00_1);
        addItemToVideosBox(container00_2);

    }
}

void CusVideoBox2::handleSignalsAndSlots()
{

}

void CusVideoBox2::setInstallEventFilter()
{

}

void CusVideoBox2::addItemToVideosBox(QWidget *widget)
{
    ui->m_itemsLayout->addWidget(widget);
}

void CusVideoBox2::removeItemToVideosBox(QWidget *widget)
{
    ui->m_itemsLayout->removeWidget(widget);
}
