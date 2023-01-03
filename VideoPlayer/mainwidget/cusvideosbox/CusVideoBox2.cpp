#include "CusVideoBox2.h"
#include "global/Global.h"
#include <QDebug>

CusVideoBox2::CusVideoBox2(QWidget *parent) :
    CToTopWidget(parent)
{
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusVideoBox2::~CusVideoBox2()
{

}

void CusVideoBox2::initWorkUI()
{
    m_switchStackWgt = new SwitchStackWgt();
    m_switchStackWgt->setObjectName(QString::fromLocal8Bit("m_switchStackWgt"));

    for(int i = 0; i < 6; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall3/stackwall%1.jpg").arg(i);
        m_switchStackWgt->slot_addToStackItemPicture(path);
    }
    addItemToVideosBox(m_switchStackWgt);

    for(int i = 0; i < 3; i++)
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
    installEventFilter(this);
}

void CusVideoBox2::addItemToVideosBox(QWidget *widget)
{
    this->addItemToWidget(widget);
}

void CusVideoBox2::removeItemToVideosBox(QWidget *widget)
{
    this->removeItemFromWidget(widget);
}

bool CusVideoBox2::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched,event);
}
