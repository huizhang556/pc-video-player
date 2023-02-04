#include "LeftSideBar.h"
#include <QStringList>

LeftSideBar::LeftSideBar(QWidget *parent) :
    QWidget(parent)
{
    initWidgetUi();
    handleSignalAndSLots();
}

LeftSideBar::~LeftSideBar()
{

}

void LeftSideBar::setSlideBarListText(QStringList strList)
{
    //节目列表
    QStringList t_strList;
    t_strList  <<QString(u8"精选推荐")
               <<QString(u8"独家影院")
               <<QString(u8"少儿动画")
               <<QString(u8"热播电影")
               <<QString(u8"独家播放")
               <<QString(u8"分类查询")
               <<QString(u8"会员影视")
               <<QString(u8"新浏览器")
//               <<QString(u8"会员视频")
               <<QString(u8"热门搜索")
//               <<QString(u8"个性推荐")
//               <<QString(u8"歌曲分类")
//               <<QString(u8"热门飙升")
               <<QString(u8"热门标签")
//               <<QString(u8"精选电台")
//               <<QString(u8"正在直播")
//               <<QString(u8"会员专享")
               <<QString(u8"资讯速览")
               <<QString(u8"下载记录")
               <<QString(u8"个人主页")
               <<QString(u8"传输记录")
               <<QString(u8"视屏盒子6")
               <<QString(u8"视屏盒子7");//21项目
    //传统方法
    for(int i = 0;i<t_strList.size();i++)
    {
        QIcon strIcon = QIcon(QString(":/images/icon/hot%1.png").arg(i));
        QString name = t_strList.at(i);
        QListWidgetItem *ppItem = new QListWidgetItem(strIcon,name);
        ppItem->setSizeHint(QSize(80,68));
        ppItem->setTextAlignment(Qt::AlignBottom);
        m_listWidget->addItem(ppItem);
    }
        m_listWidget->setCurrentRow(0);//默认选中第一个，必须在加载内容的情况下设置，否则无效
}

/*设置左侧边栏宽度*/
void LeftSideBar::setLeftSliderFixedWidth(const int width)
{
    m_listWidget->setFixedWidth(width);
    m_moreBtn->setFixedWidth(width);
    m_modeBtn->setFixedWidth(width);
    m_setBtn->setFixedWidth(width);
}

void LeftSideBar::slot_setCurrentIndex(int index)
{
    m_listWidget->setCurrentRow(index);
}

bool LeftSideBar::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && event->type() == QEvent::Enter)
    {
        this->setCursor(Qt::ArrowCursor);
    }
    return QWidget::eventFilter(watched,event);
}

//初始化界面
void LeftSideBar::initWidgetUi()
{
    this->installEventFilter(this);
    m_listWidget = new QListWidget(this);
    m_listWidget->setObjectName(QString::fromLatin1("listWidget_playlist"));//对象名称用于设置样式
    m_listWidget->setMinimumWidth(60);
    m_listWidget->setViewMode(QListView::IconMode);//图标模式下，默认是自动换行的
    m_listWidget->setMovement(QListView::Static);//不可拖动
//    m_listWidget->setLayoutDirection(Qt::RightToLeft);
    m_listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭滚动条可见
    m_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
    m_listWidget->setFocusPolicy(Qt::NoFocus);//作用是点击item去掉虚线边框

    //消息
    m_msgBtn = new QPushButton(QIcon("://images/icon/leftbar_msg.png"),QString(u8""), this);
    m_msgBtn->setObjectName(QString::fromLatin1("m_msgBtn"));
    m_msgBtn->setFixedHeight(BTN_HEIGHT);
    m_msgBtn->setCheckable(true);

    //设置
    m_setBtn = new QPushButton(QIcon("://images/icon/leftbar_set.png"),QString(u8""), this);
    m_setBtn->setObjectName(QString::fromLatin1("m_setBtn"));
    m_setBtn->setFixedHeight(BTN_HEIGHT);
    m_setBtn->setCheckable(true);

    //模式（白天/夜晚）
    m_modeBtn = new QPushButton(QIcon("://images/icon/leftbar_day.png"),QString(u8""), this);
    m_modeBtn->setObjectName(QString::fromLatin1("m_modeBtn"));
    m_modeBtn->setFixedHeight(BTN_HEIGHT);
    m_modeBtn->setCheckable(true);
    //更多
    m_moreBtn = new QPushButton(QIcon("://images/icon/leftbar_more.png"),QString(u8""),this);
    m_moreBtn->setObjectName(QString::fromLatin1("m_moreBtn"));
    m_moreBtn->setFixedHeight(BTN_HEIGHT);
    m_moreBtn->setCheckable(true);

    QVBoxLayout *m_vbayout1 = new QVBoxLayout(this);
    QVBoxLayout *m_vbayout2 = new QVBoxLayout(this);

    m_vbayout2->addWidget(m_msgBtn);
    m_vbayout2->addWidget(m_modeBtn);
    m_vbayout2->addWidget(m_setBtn);
    m_vbayout2->addWidget(m_moreBtn);
    m_vbayout2->setSpacing(0);
    m_vbayout2->setContentsMargins(0,0,0,0);

    m_vbayout1->addWidget(m_listWidget);
    m_vbayout1->addLayout(m_vbayout2);
    m_vbayout1->setSpacing(0);
    m_vbayout1->setContentsMargins(0,0,0,0);
}

/*处理信号与槽函数*/
void LeftSideBar::handleSignalAndSLots()
{
    connect(m_listWidget,&QListWidget::itemClicked,[=](QListWidgetItem *item)
    {
        emit sig_sidebarItemChange(m_listWidget->row(item));
    });

    //消息
    connect(m_msgBtn,&QPushButton::clicked,[=](bool checked){
        emit sig_sendPersonMessage(checked);
    });

    //模式转换
    connect(m_modeBtn,&QPushButton::clicked,[=](bool checked){
        if(checked)
        {
            m_modeBtn->setIcon(QIcon("://images/icon/leftbar_night.png"));
        }
        else
        {
            m_modeBtn->setIcon(QIcon("://images/icon/leftbar_day.png"));
        }
        emit sig_sendSkinMode(checked);
    });

    //设置
    connect(m_setBtn,&QPushButton::clicked,[=](bool checked){
        emit sig_sendSetting(checked);
    });

    //更多
    connect(m_moreBtn,&QPushButton::clicked,[=](){
        emit sig_sendMore();
    });
}


