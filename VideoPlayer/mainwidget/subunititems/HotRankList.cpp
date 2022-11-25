#include "HotRankList.h"

RankList::RankList(QWidget *parent) :
    QWidget(parent)
{
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

RankList::RankList(const QString &title, const int num, QWidget *parent):
    QWidget(parent)
{
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    m_buttonTitle->setText(title);
    for(int i = 0; i < num; i++)
    {
        slot_addItemToRankList("www.hao123.com",QString::number(i+1),":/images/bgpic/cusvideoitem1.png",mainInfo.at(i),Info.at(i),QString(u8"778899"));
    }
}

RankList::~RankList()
{
}

void RankList::initWorkUI()
{
    m_buttonTitle = new QPushButton(this);
    m_buttonTitle->setText(QString(u8"动漫热播榜"));
    m_buttonTitle->setObjectName(QString::fromUtf8("m_buttonTitle_rank"));
    m_buttonTitle->setFixedHeight(ITEMHEIGHT);

    m_rankListWgt = new QListWidget(this);
    m_rankListWgt->setFrameShape(QFrame::NoFrame);//去边框
    m_rankListWgt->setObjectName(QString::fromUtf8("m_rankListWgt_rank"));
    m_rankListWgt->setMinimumSize(240,ITEMHEIGHT);
    m_rankListWgt->setViewMode(QListView::ListMode);
    m_rankListWgt->setMovement(QListView::Static);
    m_rankListWgt->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_rankListWgt->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_rankListWgt->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_vblayout1 = new QVBoxLayout(this);//指定父亲，就不要再setLayout
    m_vblayout1->setObjectName(QString::fromUtf8("m_vblayout1_rank"));
    m_vblayout1->setSpacing(0);
    m_vblayout1->setMargin(0);
    m_vblayout1->setContentsMargins(0,0,0,0);
    m_vblayout1->addWidget(m_buttonTitle);
    m_vblayout1->addWidget(m_rankListWgt);
}

void RankList::handleSignalsAndSlots()
{
    //item被点击
    connect(m_rankListWgt,&QListWidget::itemClicked,[=](QListWidgetItem *item){
        qDebug() << QString(u8"第%1个item被点击，点击内容是：%2").arg(item->text()).arg(item->data(Qt::UserRole).toString());
    });
}

void RankList::setInstallEventFilter()
{
    m_rankListWgt->installEventFilter(this);
}

void RankList::slot_addItemToRankList(const QString &url, const QString& num, const QString& picpath, const QString& maininfo, const QString& info, const QString& hotvalue)
{
    HotListItem *itemWidget = new HotListItem(num,picpath,maininfo,info,hotvalue);
    QListWidgetItem *item = new QListWidgetItem(num);
    item->setSizeHint(itemWidget->size());
    item->setData(Qt::UserRole,url);
    m_rankListWgt->addItem(item);
    m_rankListWgt->setItemWidget(item,itemWidget);
}

bool RankList::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_rankListWgt)
    {
        if(event->type() == QEvent::Resize)
        {
            resizeListGeometry();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void RankList::resizeListGeometry()
{
    if(m_rankListWgt->count() == 0) return;
    int avgHeight = (int)(m_rankListWgt->height()/ m_rankListWgt->count());
    if(avgHeight <  45) avgHeight = 45;
    for(int i = 0; i < m_rankListWgt->count(); i++)
    {
        m_rankListWgt->item(i)->setSizeHint(QSize(m_rankListWgt->width() - m_rankListWgt->verticalScrollBar()->width()-1,avgHeight));
    }
}
