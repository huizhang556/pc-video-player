#include "CusVideoBox7.h"

CusVideoBox7::CusVideoBox7(QWidget *parent) :
    CToTopWidget(parent)
{
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusVideoBox7::~CusVideoBox7()
{

}

void CusVideoBox7::initWorkUI()
{
    m_aniStackWgt = new AniStackWidget(this);
    m_aniStackWgt->setObjectName(QString::fromUtf8("m_aniStackWgt"));
    for(int i = 0; i < 6; i++)
    {
        QString path1 = Global::appDirPath + QString("/pictures/stackwall2/stackwall%1.jpg").arg(i);
        QString path2 = Global::appDirPath + QString("/pictures/stackwall5/smallList%1.jpg").arg(i);
        m_aniStackWgt->slot_addItemToCusVerStackWgt(path1);
        m_aniStackWgt->slot_addItemToSmallList(path2);
    }
    addItemToVideosBox(m_aniStackWgt);
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
//        hblayout1->addWidget(item_RK1);
        hblayout1->addWidget(container01_1);
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

        addItemToVideosBox(videoSortItem1);
        addItemToVideosBox(hblayout2);
        addItemToVideosBox(hblayout1);
    }
}

void CusVideoBox7::handleSignalsAndSlots()
{

}

void CusVideoBox7::setInstallEventFilter()
{
    this->installEventFilter(this);
}

void CusVideoBox7::addItemToVideosBox(QWidget *widget)
{
    this->addItemToWidget(widget);
}

void CusVideoBox7::removeItemToVideosBox(QWidget *widget)
{
    this->removeItemFromWidget(widget);
}

void CusVideoBox7::addItemToVideosBox(QLayout *layout)
{
    this->addItemToWidget(layout);
}

void CusVideoBox7::removeItemToVideosBox(QLayoutItem *layout)
{
    this->removeItemFromWidget(layout);
}

bool CusVideoBox7::eventFilter(QObject *watched, QEvent *event)
{
    return  QWidget::eventFilter(watched,event);
}
