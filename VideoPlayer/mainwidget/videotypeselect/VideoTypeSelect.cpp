#include "VideoTypeSelect.h"
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
    m_listWgt_sortResult->setMinimumHeight(1000);
    m_listWgt_sortResult->setFrameShape(QFrame::NoFrame);//去边框
    m_listWgt_sortResult->setViewMode(QListView::IconMode);
    m_listWgt_sortResult->setMovement(QListView::Static);
    m_listWgt_sortResult->setWrapping(true);
    m_listWgt_sortResult->setResizeMode(QListView::Adjust);
    m_listWgt_sortResult->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWgt_sortResult->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWgt_sortResult->setVerticalScrollMode(QListView::ScrollPerPixel);

    m_listWgt_sortResult->setObjectName(QString::fromLocal8Bit("m_listWgt_sortResult"));
    for(int i = 0; i < 10; i++)
    {
        QListWidgetItem *item = new QListWidgetItem();
        MemberVideoItem *itemWidget = new MemberVideoItem();
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
}

VideoTypeSelect::~VideoTypeSelect()
{

}
