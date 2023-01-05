#include "MainMembForm.h"
#include "global/Global.h"

#include "mainwidget/CusVerStackWgt.h"
#include "CusStackWidget.h"
#include "VideoSortType.h"
#include "SwitchVideoType.h"

#include <QDebug>

MainMembForm::MainMembForm(QWidget *parent):
    CToTopWidget(parent)
{
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

MainMembForm::~MainMembForm()
{

}

void MainMembForm::initWorkUI()
{
    CusVerStackWgt *itemWidget  = new CusVerStackWgt();
    for(int i = 0; i < 6; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall/stack%1.png").arg(i);
        itemWidget->slot_addItemToCusVerStackWgt(path);
    }

    SwitchVideoType *switchItem   = new SwitchVideoType();
    this->addItemToWidget(itemWidget);
    this->addItemToWidget(switchItem);

    for(int i = 0; i < 3; i++)
    {
        VideoSortType *videoSortItem1 = new VideoSortType();
        this->addItemToWidget(videoSortItem1);
    }

}

void MainMembForm::handleSignalsAndSlots()
{

}

void MainMembForm::setInstallEventFilter()
{

}
