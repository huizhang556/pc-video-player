#include "LeftSideBar.h"
#include <QStringList>

LeftSideBar::LeftSideBar(QWidget *parent) :
    QWidget(parent)
{
    initWidgetUi();
    chandleSignalAndSlots();
}

LeftSideBar::~LeftSideBar()
{

}

void LeftSideBar::setSlideBarListText()
{
    //节目列表
    QStringList strPlayList;
    strPlayList<<QString::fromLocal8Bit("最新视剧")
               <<QString::fromLocal8Bit("热播电影")
               <<QString::fromLocal8Bit("当前视频")
               <<QString::fromLocal8Bit("当前音乐")
               <<QString::fromLocal8Bit("播放列表")
               <<QString::fromLocal8Bit("少儿动漫")
               <<QString::fromLocal8Bit("世界纪录")
               <<QString::fromLocal8Bit("教育课堂")
               <<QString::fromLocal8Bit("游戏直播")
               <<QString::fromLocal8Bit("建党百年")
               <<QString::fromLocal8Bit("王者荣耀")
               <<QString::fromLocal8Bit("健康养生")
               <<QString::fromLocal8Bit("资讯速递")
               <<QString::fromLocal8Bit("生活解密")
               <<QString::fromLocal8Bit("世界地理")
               <<QString::fromLocal8Bit("人文艺术")
               <<QString::fromLocal8Bit("今日影院")
               <<QString::fromLocal8Bit("影视排行")
               <<QString::fromLocal8Bit("最新上架")
               <<QString::fromLocal8Bit("评分最高")
               <<QString::fromLocal8Bit("热门点播")
               <<QString::fromLocal8Bit("明星娱乐");//21项目
    //传统方法
    for(int i = 0;i<strPlayList.size();i++)
    {
        QIcon strIcon = QIcon(QString(":/images/hot%1.png").arg(i));
        QString name = strPlayList.at(i);
        QListWidgetItem *ppItem = new QListWidgetItem(strIcon,name);
        ppItem->setTextAlignment(Qt::AlignVCenter);
        m_listWidget->addItem(ppItem);
    }
}

//初始化界面
void LeftSideBar::initWidgetUi()
{
    m_listWidget = new QListWidget(this);
    m_listWidget->setFixedWidth(170);
    m_listWidget->setObjectName(QString::fromLatin1("listWidget_playlist"));//对象名称用于设置样式

    m_expandBtn = new QPushButton(this);
    m_expandBtn->setFixedSize(170,40);
    m_expandBtn->setText(QString::fromLocal8Bit("展开更多>>"));
    m_expandBtn->setObjectName(QString::fromLatin1("m_expandBtn"));

    m_vbayout = new QVBoxLayout(this);
    m_vbayout->setObjectName(QString::fromLatin1("m_vbayout"));
    m_vbayout->addWidget(m_listWidget);
    m_vbayout->addWidget(m_expandBtn);
    m_vbayout->setSpacing(0);
    m_vbayout->setContentsMargins(0,0,0,0);
    setSlideBarListText();//设置文字
}

/*处理信号与槽函数*/
void LeftSideBar::chandleSignalAndSlots()
{
    connect(m_listWidget,&QListWidget::itemClicked,[=](QListWidgetItem *item)
    {
//        int row = m_listWidget->row(item);
        sig_sidebarItemChange(m_listWidget->row(item));
    });
}
