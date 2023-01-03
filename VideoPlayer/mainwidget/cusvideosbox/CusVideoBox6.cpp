#include "CusVideoBox6.h"

CusVideoBox6::CusVideoBox6(QWidget *parent) :
    CToTopWidget(parent)
{
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusVideoBox6::~CusVideoBox6()
{

}

void CusVideoBox6::initWorkUI()
{
    m_switchStackWgt = new CusVerStackWgt();
    m_switchStackWgt->setObjectName(QString::fromLocal8Bit("m_switchStackWgt"));
    for(int i = 0; i < 6; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall2/stackwall%1.jpg").arg(i);
        m_switchStackWgt->slot_addItemToCusVerStackWgt(path);
    }
    addItemToVideosBox(m_switchStackWgt);
    for(int i = 0; i < 3; i++)
    {
        Container01 *container01_1 = new Container01(QString(u8"热播电影"),QString(Global::appDirPath +"/pictures/cusvideoitem/cusvideoitem_left%1.png").arg(2));
        RankList *item_RK1 = new RankList(QString(u8"热播电影榜"),5);
        RankList *item_RK2 = new RankList(QString(u8"热播影视榜"),7);
        item_RK1->setMinimumWidth(240);
        item_RK2->setMinimumWidth(240);
        item_RK1->setFixedWidth(360);
        item_RK2->setFixedWidth(360);
        Container00 *container00_1 = new Container00();
        Container00 *container00_2 = new Container00();
        VideoSortType *videoSortItem1 = new VideoSortType();

        QHBoxLayout *hblayout1 = new QHBoxLayout();
        hblayout1->addWidget(container01_1);
        hblayout1->addWidget(item_RK1);
        hblayout1->setSpacing(0);
        hblayout1->setContentsMargins(0,0,0,0);

        QVBoxLayout *vblayout1 = new QVBoxLayout();
        vblayout1->addWidget(container00_1);
        vblayout1->addWidget(container00_2);
        vblayout1->setSpacing(0);
        vblayout1->setContentsMargins(0,0,0,0);

        QHBoxLayout *hblayout2 = new QHBoxLayout();
        hblayout2->addLayout(vblayout1);
        hblayout2->addWidget(item_RK2);
        hblayout2->setSpacing(0);
        hblayout2->setContentsMargins(0,0,0,0);

        addItemToVideosBox(hblayout1);
        addItemToVideosBox(hblayout2);
        addItemToVideosBox(videoSortItem1);
    }
}

void CusVideoBox6::handleSignalsAndSlots()
{

}

void CusVideoBox6::setInstallEventFilter()
{
    this->installEventFilter(this);
}

void CusVideoBox6::addItemToVideosBox(QWidget *widget)
{
    this->addItemToWidget(widget);
}

void CusVideoBox6::removeItemToVideosBox(QWidget *widget)
{
    this->removeItemFromWidget(widget);
}

void CusVideoBox6::addItemToVideosBox(QLayout *layout)
{
    this->addItemToWidget(layout);
}

void CusVideoBox6::removeItemToVideosBox(QLayoutItem *layout)
{
    this->removeItemFromWidget(layout);
}

bool CusVideoBox6::eventFilter(QObject *watched, QEvent *event)
{
    return  QWidget::eventFilter(watched,event);
}
