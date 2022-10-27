#include "HomeWidget.h"
#include "ui_HomeWidget.h"

#include <QDebug>

HomeWidget::HomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWidget)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    addToStackWidget();

}

HomeWidget::~HomeWidget()
{
    delete ui;
}

void HomeWidget::initWorkUI()
{
    m_stackWgt_center = new QStackedWidget(this);
    m_stackWgt_center->setObjectName(QString::fromLocal8Bit("m_stackWgt_center"));

    //选择按钮
    m_selectButton = new SelectButtons(this);
    m_selectButton->setObjectName(QString::fromLocal8Bit("m_selectButton"));

    //推荐专区
    m_homeWdgt = new CentralHomeForm();
    m_homeWdgt->setObjectName(QString::fromLocal8Bit("m_homeWdgt"));

    //歌手排行
    m_songerSort = new SongerSort();
    m_songerSort->setObjectName(QString::fromLocal8Bit("m_songerSort"));

    //排行榜
    m_rankList = new RankingList();
    m_rankList->setObjectName(QString::fromLocal8Bit("m_rankList"));

    //歌单分类
    m_songlistSort = new SonglistSort();
    m_songlistSort->setObjectName(QString::fromLocal8Bit("m_songlistSort"));

    //主播电台
    m_radioHost = new RadioHost();
    m_radioHost->setObjectName(QString::fromLocal8Bit("m_radioHost"));

    //音乐现场
    m_musicScene = new MusicScene();
    m_musicScene->setObjectName(QString::fromLocal8Bit("m_musicScene"));

    //会员专区
    m_vipMember = new VipMember();
    m_vipMember->setObjectName(QString::fromLocal8Bit("m_vipMember"));

    m_vbHlayout = new QVBoxLayout(this);
    m_vbHlayout->setSpacing(0);
    m_vbHlayout->setMargin(0);
    m_vbHlayout->setContentsMargins(0,0,0,0);
    m_vbHlayout->addWidget(m_selectButton);
    m_vbHlayout->addWidget(m_stackWgt_center);
}

void HomeWidget::handleSignalsAndSlots()
{
    //中心区域切换
    connect(m_selectButton,SIGNAL(sig_buttonItemChanged(int)),this,SLOT(slot_setCurrentCenterStackWidget(int)));
    //界面更新
    connect(this,&HomeWidget::sig_globalResize,[=](){
        m_homeWdgt->slot_globalResize();
//        m_songerSort->slot_globalResize();
        m_rankList->slot_globalResize();
    });
}

void HomeWidget::addToStackWidget()
{
    m_stackWgt_center->insertWidget(0,m_homeWdgt);
//    m_stackWgt_center->insertWidget(1,m_songerSort);
//    m_stackWgt_center->insertWidget(2,m_rankList);
//    m_stackWgt_center->insertWidget(3,m_songlistSort);
//    m_stackWgt_center->insertWidget(4,m_radioHost);
//    m_stackWgt_center->insertWidget(5,m_musicScene);
//    m_stackWgt_center->insertWidget(6,m_vipMember);
}

void HomeWidget::slot_globalResize()
{
    this->repaint();
    emit sig_globalResize();//向子界面发送更新信号
    qDebug() << QString(u8"推荐总界面已更新！");
}

void HomeWidget::slot_setCurrentCenterStackWidget(int index)
{
//    m_stackWgt_center->setCurrentIndex(index);
}
