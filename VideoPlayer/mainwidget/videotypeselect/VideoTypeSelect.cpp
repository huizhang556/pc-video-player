#include "VideoTypeSelect.h"
#include "global/Global.h"
#include "mainwidget/videomember/MemberVideoItem.h"

VideoTypeSelect::VideoTypeSelect(QWidget *parent) :
    QWidget(parent)
{

    m_vblayout = new QVBoxLayout(this);
    m_vblayout->setSpacing(0);
    m_vblayout->setContentsMargins(0,0,0,0);
    m_vblayout->setMargin(0);
    m_sortVideoForm = new SelectVideoType();
    m_listWgt_sortResult = new QListWidget();
    m_listWgt_sortResult->installEventFilter(this);
//    m_listWgt_sortResult->setMinimumHeight(1000);
    m_listWgt_sortResult->setFrameShape(QFrame::NoFrame);//去边框
    m_listWgt_sortResult->setViewMode(QListView::IconMode);
    m_listWgt_sortResult->setMovement(QListView::Static);
    m_listWgt_sortResult->setWrapping(true);
    m_listWgt_sortResult->setResizeMode(QListView::Adjust);
    m_listWgt_sortResult->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWgt_sortResult->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWgt_sortResult->setVerticalScrollMode(QListView::ScrollPerPixel);

    m_listWgt_sortResult->setObjectName(QString::fromLocal8Bit("m_listWgt_sortResult"));
    for(int i = 0; i < 50; i++)
    {
        //视频分类搜索结果
        QString path2 = Global::appDirPath + QString("/pictures/mylike/videos_list2/list_intro%1.jpg").arg(i);
        MemberVideoItem *itemWidget = new MemberVideoItem(path2,QString(u8"搜索分类视频%1").arg(i),QString(u8"搜索分类结果"),QColor(43, 44, 53));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());
        m_listWgt_sortResult->addItem(item);
        m_listWgt_sortResult->setItemWidget(item,itemWidget);
    }
    m_vblayout->addWidget(m_sortVideoForm);
    m_vblayout->addWidget(m_listWgt_sortResult);
    setLayout(m_vblayout);

    //信号与槽函数
    connect(m_sortVideoForm,&SelectVideoType::sig_selectResult,[=](QString text){
        qDebug() << QString(u8"接收到查询结果：") << text;
    });

    connect(m_listWgt_sortResult->verticalScrollBar(),&QScrollBar::valueChanged,[=](int value){
        if(value > 80)
        {
            m_sortVideoForm->slot_setSortHidden(false);
        }
        else
        {
            m_sortVideoForm->slot_setSortHidden(true);
        }
    });
}

VideoTypeSelect::~VideoTypeSelect()
{

}

bool VideoTypeSelect::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_listWgt_sortResult)
    {
        if(event->type() == QEvent::Resize)
        {
            resizeListWgt_result();
        }
    }
    return  QWidget::eventFilter(watched,event);
}

void VideoTypeSelect::resizeListWgt_result()
{
    int width = m_listWgt_sortResult->width();
//    滚动条宽度默认17
    int colWidth0  = (int)(width - m_listWgt_sortResult->verticalScrollBar()->width() - 1);
    for(int i = 0; i < m_listWgt_sortResult->count(); i++)
    {
        if( colWidth0 < 225*5)
        {
            int colWidth_5  = (int)((width - m_listWgt_sortResult->verticalScrollBar()->width() - 1)/4);
            m_listWgt_sortResult->item(i)->setSizeHint(QSize(colWidth_5,m_listWgt_sortResult->item(i)->sizeHint().height()));
        }
        else if( colWidth0 < 225*6)
        {
            int colWidth_6  = (int)((width - m_listWgt_sortResult->verticalScrollBar()->width() - 1)/5);
            m_listWgt_sortResult->item(i)->setSizeHint(QSize(colWidth_6,m_listWgt_sortResult->item(i)->sizeHint().height()));
        }
        else if( colWidth0 < 225*7)
        {
            int colWidth_7  = (int)((width - m_listWgt_sortResult->verticalScrollBar()->width() - 1)/6);
            m_listWgt_sortResult->item(i)->setSizeHint(QSize(colWidth_7,m_listWgt_sortResult->item(i)->sizeHint().height()));
        }
        else if( colWidth0 < 225*8)
        {
            int colWidth_8  = (int)((width - m_listWgt_sortResult->verticalScrollBar()->width() - 1)/7);
            m_listWgt_sortResult->item(i)->setSizeHint(QSize(colWidth_8,m_listWgt_sortResult->item(i)->sizeHint().height()));
        }
        else
        {
            int colWidth_9  = (int)((width - m_listWgt_sortResult->verticalScrollBar()->width() - 1)/8);
            m_listWgt_sortResult->item(i)->setSizeHint(QSize(colWidth_9,m_listWgt_sortResult->item(i)->sizeHint().height()));
        }
    }
}
