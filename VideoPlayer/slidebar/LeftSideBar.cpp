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
               <<QString(u8"新浏览器")
               <<QString(u8"最新视频")
               <<QString(u8"VIP会员")
               <<QString(u8"精彩推荐")
               <<QString(u8"全球歌手")
               <<QString(u8"新排行榜")
               <<QString(u8"歌单分类")
               <<QString(u8"主播电台")
               <<QString(u8"音乐现场")
               <<QString(u8"会员专区")
               <<QString(u8"播放列表")
               <<QString(u8"个人信息")
               <<QString(u8"文件传输")
               <<QString(u8"世界地理")
               <<QString(u8"人文艺术")
               <<QString(u8"今日影院")
               <<QString(u8"影视排行")
               <<QString(u8"最新上架")
               <<QString(u8"评分最高")
               <<QString(u8"热门点播")
               <<QString(u8"明星娱乐");//21项目
    //传统方法
    for(int i = 0;i<t_strList.size();i++)
    {
        QIcon strIcon = QIcon(QString(":/images/icon/hot%1.png").arg(i));
        QString name = t_strList.at(i);
        QListWidgetItem *ppItem = new QListWidgetItem(strIcon,name);
        ppItem->setTextAlignment(Qt::AlignVCenter);
        m_listWidget->addItem(ppItem);
    }
        m_listWidget->setCurrentRow(0);//默认选中第一个，必须在加载内容的情况下设置，否则无效
}

/*设置左侧边栏宽度*/
void LeftSideBar::setLeftSliderFixedWidth(int width)
{
    m_listWidget->setFixedWidth(width);
    m_expandBtn->setFixedWidth(width);
}

//初始化界面
void LeftSideBar::initWidgetUi()
{
    m_listWidget = new QListWidget(this);
    m_listWidget->setFixedWidth(140);
    m_listWidget->setObjectName(QString::fromLatin1("listWidget_playlist"));//对象名称用于设置样式
    m_listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭滚动条可见
    m_listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
    m_listWidget->setFocusPolicy(Qt::NoFocus);//作用是点击item去掉虚线边框

    m_expandBtn = new QPushButton(this);
    m_expandBtn->setFixedSize(140,40);
    m_expandBtn->setCheckable(true);
    m_expandBtn->setText(QString::fromLocal8Bit("展开更多>>"));
    m_expandBtn->setObjectName(QString::fromLatin1("m_expandBtn"));

    m_vbayout = new QVBoxLayout(this);
    m_vbayout->setObjectName(QString::fromLatin1("m_vbayout"));
    m_vbayout->addWidget(m_listWidget);
    m_vbayout->addWidget(m_expandBtn);
    m_vbayout->setSpacing(0);
    m_vbayout->setMargin(0);
    m_vbayout->setContentsMargins(0,0,0,0);
}

/*处理信号与槽函数*/
void LeftSideBar::handleSignalAndSLots()
{
    connect(m_listWidget,&QListWidget::itemClicked,[=](QListWidgetItem *item)
    {
        emit sig_sidebarItemChange(m_listWidget->row(item));
    });
}


