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
               <<QString(u8"会员视频")
               <<QString(u8"热门搜索")
               <<QString(u8"个性推荐")
               <<QString(u8"歌曲分类")
               <<QString(u8"热门飙升")
               <<QString(u8"热门标签")
               <<QString(u8"精选电台")
               <<QString(u8"正在直播")
               <<QString(u8"会员专享")
               <<QString(u8"资讯速览")
               <<QString(u8"下载记录")
               <<QString(u8"个人主页")
               <<QString(u8"传输记录")
               <<QString(u8"最初的页");//21项目
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

void LeftSideBar::slot_setCurrentIndex(int index)
{
    m_listWidget->setCurrentRow(index);
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


