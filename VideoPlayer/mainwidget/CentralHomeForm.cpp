#include "CentralHomeForm.h"
#include <QListWidgetItem>

CentralHomeForm::CentralHomeForm(QWidget *parent) :
    QWidget(parent)
{
    initWorkUI();
    chandleSignalsAndSLots();
}

CentralHomeForm::~CentralHomeForm()
{

}

void CentralHomeForm::initWorkUI()
{
    m_recommend = new RecommendForm(this);
    m_recommend->setObjectName(QString::fromLocal8Bit("m_recommend"));

    m_homeListWidget = new QListWidget(this);
    m_homeListWidget->setObjectName(QString::fromLocal8Bit("m_homeListWidget"));

    m_vBlayout = new QVBoxLayout(this);
    m_vBlayout->setObjectName(QString::fromLocal8Bit("m_vBlayout"));
    m_vBlayout->addWidget(m_homeListWidget);
    m_vBlayout->setSpacing(0);
    m_vBlayout->setContentsMargins(0,0,0,0);
    this->setLayout(m_vBlayout);
    addWidgetToListWidget();
}

void CentralHomeForm::chandleSignalsAndSLots()
{

}

void CentralHomeForm::addWidgetToListWidget()
{

    QListWidgetItem *item0 = new QListWidgetItem();
    item0->setSizeHint(m_recommend->size());
    m_homeListWidget->addItem(item0);
    m_homeListWidget->setItemWidget(item0,m_recommend);

    QListWidgetItem *item1 = new QListWidgetItem();
    GalleryItemForm *pitem1 = new GalleryItemForm();
    pitem1->setHeaderTitle(QString::fromLocal8Bit("个性推荐"));
    item1->setSizeHint(pitem1->size());
    m_homeListWidget->addItem(item1);
    m_homeListWidget->setItemWidget(item1,pitem1);

    QListWidgetItem *item2 = new QListWidgetItem();
    GalleryItemForm *pitem2 = new GalleryItemForm();
    pitem2->setHeaderTitle(QString::fromLocal8Bit("推荐电台"));
    item2->setSizeHint(pitem2->size());
    m_homeListWidget->addItem(item2);
    m_homeListWidget->setItemWidget(item2,pitem2);

    QListWidgetItem *item3 = new QListWidgetItem();
    GalleryItemForm *pitem3 = new GalleryItemForm();
    pitem3->setHeaderTitle(QString::fromLocal8Bit("最潮视频"));
    item3->setSizeHint(pitem3->size());
    m_homeListWidget->addItem(item3);
    m_homeListWidget->setItemWidget(item3,pitem3);

    QListWidgetItem *item4 = new QListWidgetItem();
    GalleryItemForm *pitem4 = new GalleryItemForm();
    pitem4->setHeaderTitle(QString::fromLocal8Bit("新碟上架"));
    item4->setSizeHint(pitem4->size());
    m_homeListWidget->addItem(item4);
    m_homeListWidget->setItemWidget(item4,pitem4);

    QListWidgetItem *item5 = new QListWidgetItem();
    GalleryItemForm *pitem5 = new GalleryItemForm();
    pitem5->setHeaderTitle(QString::fromLocal8Bit("音乐周边"));
    item5->setSizeHint(pitem5->size());
    m_homeListWidget->addItem(item5);
    m_homeListWidget->setItemWidget(item5,pitem5);
}

void CentralHomeForm::resizeEvent(QResizeEvent *event)
{
//    QListWidgetItem *item = m_homeListWidget->item(0);//得到第一项item
////    m_homeListWidget->setMinimumHeight(m_homeListWidget->sizeHintForRow(0));
//    item->setSizeHint(QSize(this->width(),m_homeListWidget->sizeHintForRow(0)));
}
