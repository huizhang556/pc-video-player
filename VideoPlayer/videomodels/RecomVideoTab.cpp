#include "RecomVideoTab.h"
#include "ui_RecomVideoTab.h"
#include "RecVideoItem.h"
#include "global/Global.h"

#include <QListWidgetItem>
#include <QDebug>

RecomVideoTab::RecomVideoTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecomVideoTab),
    m_turnOnStatus(false)
{
    ui->setupUi(this);
    this->setFixedWidth(260);
    initWorkUI();
    handleSignalsAndSLots();
}

RecomVideoTab::~RecomVideoTab()
{
    delete ui;
}

void RecomVideoTab::initWorkUI()
{
    ui->listWidget_recommend->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    for(int i = 0; i < 17; i++)
    {
        RecVideoItem *videoItem = new RecVideoItem(QString(Global::appDirPath + "/pictures/musics/recradio/music%1.png").arg(i),
                                                   "11:58:36",
                                                   QString::fromLocal8Bit("视频中的内容是一个真实的故事，源自我国六七十年代"),
                                                   QString::fromLocal8Bit("6.7万"));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(videoItem->size());//留出来1px的边框
        ui->listWidget_recommend->addItem(item);
        ui->listWidget_recommend->setItemWidget(item,videoItem);
    }
}

void RecomVideoTab::handleSignalsAndSLots()
{
    connect(ui->Btn_turn,&QPushButton::clicked,this,&RecomVideoTab::slots_switchTurn);
}

void RecomVideoTab::slots_switchTurn()
{
    if(!m_turnOnStatus)
    {
        qDebug() << "!m_turnOnStatus";
        ui->Btn_turn->setStyleSheet("#Btn_turn{"
                                           "border-image: url(:/images/icon/turn_on.png);"
                                           "}");
    }
    else
    {
        qDebug() << "m_turnOnStatus";
        ui->Btn_turn->setStyleSheet("#Btn_turn{"
                                           "border-image: url(:/images/icon/turn_off.png);"
                                           "}");
    }
    m_turnOnStatus = !m_turnOnStatus;
}

