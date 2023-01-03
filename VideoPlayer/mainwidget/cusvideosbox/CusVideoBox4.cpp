#include "CusVideoBox4.h"

CusVideoBox4::CusVideoBox4(QWidget *parent) :
    CToTopWidget(parent)
{
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusVideoBox4::~CusVideoBox4()
{
}

void CusVideoBox4::initWorkUI()
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
        VideoSortType *videoSortItem1 = new VideoSortType();
        Container01 *container01_1 = new Container01(QString(u8"热播电影"),QString(Global::appDirPath +"/pictures/cusvideoitem/cusvideoitem_left%1.png").arg(2));
        Container00 *container00_1 = new Container00();
//        Container00 *container00_2 = new Container00();
//        addItemToVideosBox(container01_1);
        addItemToVideosBox(container00_1);
        addItemToVideosBox(container01_1);
        addItemToVideosBox(videoSortItem1);
    }
}

void CusVideoBox4::handleSignalsAndSlots()
{

}

void CusVideoBox4::setInstallEventFilter()
{
    installEventFilter(this);
}

void CusVideoBox4::addItemToVideosBox(QWidget *widget)
{
    this->addItemToWidget(widget);
}

void CusVideoBox4::removeItemToVideosBox(QWidget *widget)
{
    this->removeItemFromWidget(widget);
}

bool CusVideoBox4::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched,event);
}
