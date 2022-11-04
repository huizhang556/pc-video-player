#include "CusVideoBox5.h"
#include "ui_CusVideoBox5.h"

CusVideoBox5::CusVideoBox5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CusVideoBox5)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusVideoBox5::~CusVideoBox5()
{
    delete ui;
}

void CusVideoBox5::initWorkUI()
{
    ui->scrollArea->setFrameShape(QFrame::NoFrame);//继承自QFrame的，都可以用此方法去掉边界线
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_switchStackWgt = new CusStackWidget(this);
    m_switchStackWgt->setObjectName(QString::fromLocal8Bit("m_switchStackWgt"));

    for(int i = 0; i < 10; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall3/stackwall%1.jpg").arg(i);
        m_switchStackWgt->slot_addItemToStackWgt(path);
    }
    addItemToVideosBox(m_switchStackWgt);

    for(int i = 0; i < 6; i++)
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

}

void CusVideoBox5::addItemToVideosBox(QWidget *widget)
{
    ui->m_itemsLayout->addWidget(widget);
}

void CusVideoBox5::removeItemToVideosBox(QWidget *widget)
{
    ui->m_itemsLayout->removeWidget(widget);
}
