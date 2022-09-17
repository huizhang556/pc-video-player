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
    m_homeListWidget->setViewMode(QListView::ListMode);
    m_homeListWidget->setMovement(QListView::Static);
    m_homeListWidget->setResizeMode(QListView::Adjust);
//    m_homeListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_homeListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_homeListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//按照像素滚动

    //底部按钮
    m_bottomBtn = new QPushButton(m_homeListWidget);//指定父窗口，可以使用相对坐标
    m_bottomBtn->setObjectName(QString::fromLocal8Bit("m_bottomBtn"));
    m_bottomBtn->setFixedSize(36,36);
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
    //滚动条调节
    connect(m_homeListWidget->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(makeBottomButton(int)));
    connect(m_bottomBtn,&QPushButton::clicked,[=](){
        m_homeListWidget->scrollToTop();//返回到顶部 scrollToBottom();
    });

    //接收 推荐部分 尺寸变化
    connect(m_recommend,&RecommendForm::sig_sizeChange,[=](QSize size){
        qDebug() << QString::fromLocal8Bit("接收到的推荐部分的尺寸：") << size;
    });
}

void CentralHomeForm::addWidgetToListWidget()
{

    QListWidgetItem *item0 = new QListWidgetItem();
    item0->setSizeHint(QSize(800,360));//推荐部分
    m_homeListWidget->addItem(item0);
    m_homeListWidget->setItemWidget(item0,m_recommend);

    QListWidgetItem *item1 = new QListWidgetItem();
    GalleryItemForm *pitem1 = new GalleryItemForm();//分类介绍画廊1
    pitem1->setHeaderTitle(QString::fromLocal8Bit("个性推荐"));
    pitem1->createItems(18,QString("/pictures/musics/recommend"));
    item1->setSizeHint(pitem1->size());
    m_homeListWidget->addItem(item1);
    m_homeListWidget->setItemWidget(item1,pitem1);
    //信号与槽函数
    connect(pitem1,&GalleryItemForm::sig_itemResizeChanged,[=](QSize size){
        resizeHomeListWidgetSize(item1,size);
    });

    QListWidgetItem *item2 = new QListWidgetItem();
    GalleryItemForm *pitem2 = new GalleryItemForm();//分类介绍画廊2
    pitem2->setHeaderTitle(QString::fromLocal8Bit("推荐电台"));
    pitem2->createItems(18,QString("/pictures/musics/recradio"));
    item2->setSizeHint(pitem2->size());
    m_homeListWidget->addItem(item2);
    m_homeListWidget->setItemWidget(item2,pitem2);
    //信号与槽函数
    connect(pitem2,&GalleryItemForm::sig_itemResizeChanged,[=](QSize size){
        resizeHomeListWidgetSize(item2,size);
    });

    QListWidgetItem *item3 = new QListWidgetItem();
    GalleryItemForm *pitem3 = new GalleryItemForm();//分类介绍画廊3
    pitem3->setHeaderTitle(QString::fromLocal8Bit("最潮视频"));
    pitem3->createItems(18,QString("/pictures/musics/fashion"));
    item3->setSizeHint(pitem3->size());
    m_homeListWidget->addItem(item3);
    m_homeListWidget->setItemWidget(item3,pitem3);
    //信号与槽函数
    connect(pitem3,&GalleryItemForm::sig_itemResizeChanged,[=](QSize size){
        resizeHomeListWidgetSize(item3,size);
    });

    QListWidgetItem *item4 = new QListWidgetItem();
    GalleryItemForm *pitem4 = new GalleryItemForm();//分类介绍画廊4
    pitem4->setHeaderTitle(QString::fromLocal8Bit("新碟上架"));
    pitem4->createItems(18,QString("/pictures/musics/new"));
    item4->setSizeHint(pitem4->size());
    m_homeListWidget->addItem(item4);
    m_homeListWidget->setItemWidget(item4,pitem4);
    //信号与槽函数
    connect(pitem4,&GalleryItemForm::sig_itemResizeChanged,[=](QSize size){
        resizeHomeListWidgetSize(item4,size);
    });

    QListWidgetItem *item5 = new QListWidgetItem();
    GalleryItemForm *pitem5 = new GalleryItemForm();//分类介绍画廊5
    pitem5->setHeaderTitle(QString::fromLocal8Bit("音乐周边"));
    pitem5->createItems(18,QString("/pictures/musics/nearly"));
    item5->setSizeHint(pitem5->size());
    m_homeListWidget->addItem(item5);
    m_homeListWidget->setItemWidget(item5,pitem5);
    //信号与槽函数
    connect(pitem5,&GalleryItemForm::sig_itemResizeChanged,[=](QSize size){
        resizeHomeListWidgetSize(item5,size);
    });

    QListWidgetItem *item6 = new QListWidgetItem();
    GalleryItemForm *pitem6 = new GalleryItemForm();//分类介绍画廊6
    pitem6->setHeaderTitle(QString::fromLocal8Bit("我的附近"));
    pitem6->createItems(18,QString("/pictures/musics/recommend"));
    item6->setSizeHint(pitem6->size());
    m_homeListWidget->addItem(item6);
    m_homeListWidget->setItemWidget(item6,pitem6);
    //信号与槽函数
    connect(pitem6,&GalleryItemForm::sig_itemResizeChanged,[=](QSize size){
        resizeHomeListWidgetSize(item6,size);
    });

    QListWidgetItem *item7 = new QListWidgetItem();
    GalleryItemForm *pitem7 = new GalleryItemForm();//分类介绍画廊7
    pitem7->setHeaderTitle(QString::fromLocal8Bit("好剧推荐"));
    pitem7->createItems(18,QString("/pictures/musics/recradio"));
    item7->setSizeHint(pitem7->size());
    m_homeListWidget->addItem(item7);
    m_homeListWidget->setItemWidget(item7,pitem7);
    //信号与槽函数
    connect(pitem7,&GalleryItemForm::sig_itemResizeChanged,[=](QSize size){
        resizeHomeListWidgetSize(item7,size);
    });

    QListWidgetItem *item8 = new QListWidgetItem();
    GalleryItemForm *pitem8 = new GalleryItemForm();//分类介绍画廊8
    pitem8->setHeaderTitle(QString::fromLocal8Bit("热播大剧"));
    pitem8->createItems(18,QString("/pictures/musics/fashion"));
    item8->setSizeHint(pitem8->size());
    m_homeListWidget->addItem(item8);
    m_homeListWidget->setItemWidget(item8,pitem8);
    //信号与槽函数
    connect(pitem8,&GalleryItemForm::sig_itemResizeChanged,[=](QSize size){
        resizeHomeListWidgetSize(item8,size);
    });

    QListWidgetItem *item9 = new QListWidgetItem();
    GalleryItemForm *pitem9 = new GalleryItemForm();//分类介绍画廊9
    pitem9->setHeaderTitle(QString::fromLocal8Bit("抖音热歌"));
    pitem9->createItems(18,QString("/pictures/musics/new"));
    item9->setSizeHint(pitem9->size());
    m_homeListWidget->addItem(item9);
    m_homeListWidget->setItemWidget(item9,pitem9);
    //信号与槽函数
    connect(pitem9,&GalleryItemForm::sig_itemResizeChanged,[=](QSize size){
        resizeHomeListWidgetSize(item9,size);
    });

    QListWidgetItem *item10 = new QListWidgetItem();
    GalleryItemForm *pitem10 = new GalleryItemForm();//分类介绍画廊10
    pitem10->setHeaderTitle(QString::fromLocal8Bit("每日推荐"));
    pitem10->createItems(18,QString("/pictures/musics/nearly"));
    item10->setSizeHint(pitem10->size());
    m_homeListWidget->addItem(item10);
    m_homeListWidget->setItemWidget(item10,pitem10);
    //信号与槽函数
    connect(pitem10,&GalleryItemForm::sig_itemResizeChanged,[=](QSize size){
        resizeHomeListWidgetSize(item10,size);
    });

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

//page1的大小改变
void CentralHomeForm::resizeEvent(QResizeEvent *event)
{
    updateBottomButtonGeometry();
//    qDebug() << QString::fromLocal8Bit("page 1的大小改变：")<<event->size();
//    QListWidgetItem *item = m_homeListWidget->item(0);//得到第一项item
//    item->setSizeHint(QSize(1300,400));
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
    m_bottomBtn->setGeometry(m_homeListWidget->width()-m_bottomBtn->width()-15,
                             m_homeListWidget->height() - m_bottomBtn->height()-10,
                             m_bottomBtn->width(),m_bottomBtn->height());
}

void CentralHomeForm::resizeHomeListWidgetSize(QListWidgetItem *item, QSize size)
{
    item->setSizeHint(QSize(size.width(),size.height()+m_homeListWidget->horizontalScrollBar()->height()));
}

void CentralHomeForm::slot_globalResize()
{
    this->resize(1,1);
    qDebug() <<QString(u8"推荐主界面更新");
}
