#include "CentralHomeForm.h"
#include <QDebug>
#include <QScrollBar>
#include <QListView>
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
    //默认按每次一个item滚动,另一个默认按每次一个像素滚动
    m_homeListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//按照像素滚动

    //底部按钮
    m_bottomBtn = new QPushButton(m_homeListWidget);//指定父窗口，可以使用相对坐标
    m_bottomBtn->setObjectName(QString::fromLocal8Bit("m_bottomBtn"));
    m_bottomBtn->setFixedSize(50,50);
    m_bottomBtn->setHidden(true);//指定父窗口默认是显示的，需要隐藏

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
    connect(m_homeListWidget->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(makeBottomButton(int)));
    connect(m_bottomBtn,&QPushButton::clicked,[=](){
        m_homeListWidget->scrollToTop();//返回到顶部 scrollToBottom();
    });
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

    QListWidgetItem *item6 = new QListWidgetItem();
    GalleryItemForm *pitem6 = new GalleryItemForm();
    pitem6->setHeaderTitle(QString::fromLocal8Bit("我的附近"));
    item6->setSizeHint(pitem6->size());
    m_homeListWidget->addItem(item6);
    m_homeListWidget->setItemWidget(item6,pitem6);

    QListWidgetItem *item7 = new QListWidgetItem();
    GalleryItemForm *pitem7 = new GalleryItemForm();
    pitem7->setHeaderTitle(QString::fromLocal8Bit("好剧推荐"));
    item7->setSizeHint(pitem7->size());
    m_homeListWidget->addItem(item7);
    m_homeListWidget->setItemWidget(item7,pitem7);

    QListWidgetItem *item8 = new QListWidgetItem();
    GalleryItemForm *pitem8 = new GalleryItemForm();
    pitem8->setHeaderTitle(QString::fromLocal8Bit("热播大剧"));
    item8->setSizeHint(pitem8->size());
    m_homeListWidget->addItem(item8);
    m_homeListWidget->setItemWidget(item8,pitem8);

    QListWidgetItem *item9 = new QListWidgetItem();
    GalleryItemForm *pitem9 = new GalleryItemForm();
    pitem9->setHeaderTitle(QString::fromLocal8Bit("抖音热歌"));
    item9->setSizeHint(pitem9->size());
    m_homeListWidget->addItem(item9);
    m_homeListWidget->setItemWidget(item9,pitem9);

    QListWidgetItem *item10 = new QListWidgetItem();
    GalleryItemForm *pitem10 = new GalleryItemForm();
    pitem10->setHeaderTitle(QString::fromLocal8Bit("每日推荐"));
    item10->setSizeHint(pitem10->size());
    m_homeListWidget->addItem(item10);
    m_homeListWidget->setItemWidget(item10,pitem10);

    QListWidgetItem *item_back = new QListWidgetItem();
    QWidget *subWidget = new QWidget();
    QLineEdit *subEdit = new QLineEdit();
    subEdit->setPlaceholderText(QString::fromLocal8Bit("点我反馈"));
    QPushButton *submitBtn = new QPushButton(QString::fromLocal8Bit("提交"));
    QHBoxLayout *hblayout = new QHBoxLayout();
    subEdit->setMinimumSize(300,36);
    subEdit->setMaximumSize(300,36);
    submitBtn->setFixedSize(50,36);
    hblayout->addWidget(subEdit);
    hblayout->addWidget(submitBtn);
    subWidget->setLayout(hblayout);
    subWidget->setFixedSize(350,36);
    hblayout->layout()->setMargin(0);
    item_back->setSizeHint(subWidget->size());
    m_homeListWidget->addItem(item_back);
    m_homeListWidget->setItemWidget(item_back,subWidget);
}

void CentralHomeForm::resizeEvent(QResizeEvent *event)
{
//    QListWidgetItem *item = m_homeListWidget->item(0);//得到第一项item
////    m_homeListWidget->setMinimumHeight(m_homeListWidget->sizeHintForRow(0));
//    item->setSizeHint(QSize(this->width(),m_homeListWidget->sizeHintForRow(0)));
    //    m_homeListWidget->updateGeometries();//更新所有itemWidget的布局
    updateBottomButtonGeometry();
}

//判断滚动条位置，适时出现
void CentralHomeForm::makeBottomButton(int value)
{
//    qDebug() << "value ==" << value;
    if(value > m_homeListWidget->item(0)->sizeHint().height())
    {
        updateBottomButtonGeometry();
        m_bottomBtn->show();
    }
    else if(value < m_homeListWidget->item(0)->sizeHint().height())
    {
        updateBottomButtonGeometry();
        m_bottomBtn->hide();
    }
}

void CentralHomeForm::updateBottomButtonGeometry()
{
    m_bottomBtn->setGeometry(m_homeListWidget->width()-m_bottomBtn->width()-10,
                             m_homeListWidget->height() - m_bottomBtn->height()-10,
                             m_bottomBtn->width(),m_bottomBtn->height());
}
