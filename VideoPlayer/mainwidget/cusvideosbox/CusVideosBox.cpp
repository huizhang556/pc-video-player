#include "CusVideosBox.h"

#include "global/Global.h"
#include "mainwidget/CusVerStackWgt.h"
#include "mainwidget/subunititems/Container00.h"
#include "mainwidget/subunititems/Container01.h"
#include "mainwidget/videomember/CusStackWidget.h"

CusVideosBox::CusVideosBox(QWidget *parent) :
    CToTopWidget(parent)
{
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusVideosBox::~CusVideosBox()
{

}

void CusVideosBox::initWorkUI()
{
    CusStackWidget *itemWidget  = new CusStackWidget();
    itemWidget->setObjectName(QString::fromUtf8("m_cusStackWidget"));
    for(int i = 0; i < 10; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall2/stackwall%1.jpg").arg(i);
        itemWidget->slot_addItemToStackWgt(path);
    }
    itemWidget->setSelectType(0);//去掉左右按钮
    this->addItemToWidget(itemWidget);

    for(int i = 0; i < 3; i++)
    {
        Container00 *containerItem1 = new Container00(QString(u8"独家剧有料"));
        Container00 *containerItem11 = new Container00(QString(u8"宠爱现场"));
        Container01 *containerItem2 = new Container01(QString(u8"最新预告"),QString(Global::appDirPath +"/pictures/cusvideoitem/cusvideoitem_left%1.png").arg(1));

        this->addItemToWidget(containerItem1);
        this->addItemToWidget(containerItem11);
        this->addItemToWidget(containerItem2);
    }
}

void CusVideosBox::handleSignalsAndSlots()
{

}

void CusVideosBox::setInstallEventFilter()
{
    this->installEventFilter(this);
}


bool CusVideosBox::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched,event);
}
