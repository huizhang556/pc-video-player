#include "CusVideoBox3.h"
#include "ui_CusVideoBox3.h"

CusVideoBox3::CusVideoBox3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CusVideoBox3)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusVideoBox3::~CusVideoBox3()
{
    delete ui;
}

void CusVideoBox3::initWorkUI()
{
    ui->scrollArea->setFrameShape(QFrame::NoFrame);//继承自QFrame的，都可以用此方法去掉边界线
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_switchStackWgt = new CusStackWidget(this);
    m_switchStackWgt->setSelectType(1);//去掉底部frame
    m_switchStackWgt->setObjectName(QString::fromLocal8Bit("m_switchStackWgt"));

    for(int i = 0; i < 10; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall4/stackwall%1.jpg").arg(i);
        m_switchStackWgt->slot_addItemToStackWgt(path);
    }
    addItemToVideosBox(m_switchStackWgt);

    for(int i = 0; i < 3; i++)
    {
        VideoSortType *videoSortItem1 = new VideoSortType();
        Container01 *container01_1 = new Container01(QString(u8"最新预告"),QString(Global::appDirPath +"/pictures/cusvideoitem/cusvideoitem_left%1.png").arg(1));
        Container00 *container00_1 = new Container00();
        addItemToVideosBox(videoSortItem1);
//        addItemToVideosBox(container01_1);
        addItemToVideosBox(container00_1);
        addItemToVideosBox(container01_1);
    }
}

void CusVideoBox3::handleSignalsAndSlots()
{

}

void CusVideoBox3::setInstallEventFilter()
{
    installEventFilter(this);
}

void CusVideoBox3::addItemToVideosBox(QWidget *widget)
{
    ui->m_itemsLayout->addWidget(widget);
}

void CusVideoBox3::removeItemToVideosBox(QWidget *widget)
{
    ui->m_itemsLayout->removeWidget(widget);
}

bool CusVideoBox3::eventFilter(QObject *watched, QEvent *event)
{
    return  QWidget::eventFilter(watched,event);
}
