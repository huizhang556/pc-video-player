#include "CusVideoBox5.h"

CusVideoBox5::CusVideoBox5(QWidget *parent) :
    CToTopWidget(parent)
{
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusVideoBox5::~CusVideoBox5()
{

}

void CusVideoBox5::initWorkUI()
{
    m_switchStackWgt = new CusStackWidget();
    m_switchStackWgt->setObjectName(QString::fromLocal8Bit("m_switchStackWgt"));

    for(int i = 0; i < 10; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall3/stackwall%1.jpg").arg(i);
        m_switchStackWgt->slot_addItemToStackWgt(path);
    }
    addItemToVideosBox(m_switchStackWgt);

    for(int i = 0; i < 3; i++)
    {
        VideoSortType *videoSortItem1 = new VideoSortType();
        Container01 *container01_1 = new Container01(QString(u8"青春剧场"),QString(Global::appDirPath +"/pictures/cusvideoitem/cusvideoitem_left%1.png").arg(2));
        Container01 *container01_2 = new Container01(QString(u8"偶像剧场"),QString(Global::appDirPath +"/pictures/cusvideoitem/cusvideoitem_left%1.png").arg(3));
        Container00 *container00_1 = new Container00();
        addItemToVideosBox(videoSortItem1);
        addItemToVideosBox(container01_1);
        addItemToVideosBox(container01_2);
        addItemToVideosBox(container00_1);
    }
}

void CusVideoBox5::handleSignalsAndSlots()
{

}

void CusVideoBox5::setInstallEventFilter()
{
    installEventFilter(this);
}

void CusVideoBox5::addItemToVideosBox(QWidget *widget)
{
    this->addItemToWidget(widget);
}

void CusVideoBox5::removeItemToVideosBox(QWidget *widget)
{
    this->removeItemFromWidget(widget);
}

bool CusVideoBox5::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched,event);
}
