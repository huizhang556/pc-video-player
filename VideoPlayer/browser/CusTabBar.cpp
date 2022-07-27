#include "CusTabBar.h"

CusTabBar::CusTabBar(QWidget *parent) :
    QWidget(parent)
{
//    this->setAttribute(Qt::WA_TranslucentBackground);
    initWorkUI();
    chandleSignalsAndSlots();
}

CusTabBar::~CusTabBar()
{

}

void CusTabBar::initWorkUI()
{
    m_tabBar = new QTabBar(this);
    m_tabBar->setFixedHeight(24);
    m_tabBar->setMovable(true);
    m_tabBar->setObjectName(QString::fromLocal8Bit("m_tabBar"));
//    m_tabBar->setStyle(new CustomTabStyle);
//    m_addTabBtn = new QPushButton(QString::fromLocal8Bit("+"),this);
//    m_addTabBtn->setFixedSize(26,24);
//    m_addTabBtn->setFlat(true);
//    m_addTabBtn->setToolTip(QString::fromLocal8Bit("新建页面"));
//    m_addTabBtn->setObjectName(QString::fromLocal8Bit("m_addTabBtn"));

    m_expandBtn = new QPushButton(QString::fromLocal8Bit(">>"),this);
    m_expandBtn->setFixedSize(40,24);
    m_expandBtn->setFlat(true);
    m_expandBtn->setToolTip(QString::fromLocal8Bit("展开收藏夹"));
    m_expandBtn->setObjectName(QString::fromLocal8Bit("m_webExpandBtn"));

    m_hideBtn = new QPushButton(QString::fromLocal8Bit("隐藏"),this);
    m_hideBtn->setFixedSize(40,24);
    m_hideBtn->setFlat(true);
    m_hideBtn->setToolTip(QString::fromLocal8Bit("隐藏收藏栏"));
//    m_hideBtn->setIcon(QIcon("://images/icon/tabbar_hide.png"));
//    m_hideBtn->setIconSize(QSize());
    m_hideBtn->setObjectName(QString::fromLocal8Bit("m_webHideBtn"));

//    this->setTabButton(0,QTabBar::RightSide,m_closeBtn);//这个是在tab内部设置的按钮
    m_hblayout = new QHBoxLayout(this);
    m_hblayout->setSpacing(0);
    m_hblayout->setContentsMargins(0,0,0,0);
    m_hblayout->setMargin(0);
    m_hblayout->addWidget(m_tabBar);
//    m_hblayout->addWidget(m_addTabBtn);
    m_hblayout->addSpacerItem(new QSpacerItem(15,24, QSizePolicy::MinimumExpanding));
    m_hblayout->addWidget(m_expandBtn);
    m_hblayout->addWidget(m_hideBtn);
    this->setLayout(m_hblayout);

    for(int i = 0; i<10;i++)
    {
        slot_addMarkToTabBar(QString::fromLocal8Bit("://images/icon/engine.png"),
                             QString::fromLocal8Bit("qtcn社区广泛爱好者"),
                             QString::fromLocal8Bit("https://www.huawei.com/"));
    }
}

void CusTabBar::chandleSignalsAndSlots()
{
//    connect(m_addTabBtn,&QPushButton::clicked,[=](){ emit sig_sendTabAddWebTabBar();});
    connect(m_expandBtn,&QPushButton::clicked,[=](){ emit sig_sendTabShowRecords();});
    connect(m_hideBtn,&QPushButton::clicked,[=](){ slot_setMarksHidden(true);});
}

//隐藏标签栏
void CusTabBar::slot_setMarksHidden(bool hide)
{
    if(hide)
    {
        this->hide();
    }
    else
    {
        this->show();
    }
}

//获取标签真实地址
QString CusTabBar::slot_getTabText(int index)
{
    return m_tabBar->tabText(index);
}

void CusTabBar::slot_setTabText(const int index, const QString &rename)
{
    m_tabBar->setTabText(index,rename);
}

//获取标签左边图标
QIcon CusTabBar::slot_getTabIcon(int index)
{
    return m_tabBar->tabIcon(index);
}

//设置标签图标
void CusTabBar::slot_setTabIcon(const int index, const QIcon &icon)
{
    m_tabBar->setTabIcon(index,icon);
}

//添加一条标签
//参数：左边图标，标签别名，标签网址
void CusTabBar::slot_addMarkToTabBar(const QString &icon, const QString &nickname, const QString &address)
{
    m_tabBar->addTab(QIcon(icon), nickname);
    m_tabBar->setTabToolTip(m_tabBar->count(),address);
}

//删除标签栏的标签
void CusTabBar::slot_deleteMarkOfTabBar(int index)
{
    m_tabBar->removeTab(index);
}
