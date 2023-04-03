#include "CToTopWidget.h"
#include "ui_CToTopWidget.h"

CToTopWidget::CToTopWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CToTopWidget)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();

}

CToTopWidget::~CToTopWidget()
{
    delete ui;
}

void CToTopWidget::initWorkUI()
{
    ui->scrollArea->setFrameShape(QFrame::NoFrame);//继承自QFrame的，都可以用此方法去掉边界线
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void CToTopWidget::handleSignalsAndSlots()
{
    connect(ui->scrollArea->verticalScrollBar(),&QScrollBar::valueChanged,[=](int value){
        if(value > 200)
        {
            emit  sig_scroll_verticalbar(true);
        }
        else
        {
            emit  sig_scroll_verticalbar(false);
        }
    });
}

void CToTopWidget::setScrollBarToTop()
{

    QPropertyAnimation *pAnimation = new QPropertyAnimation(ui->scrollArea->verticalScrollBar(),"value",this);
    pAnimation->setDuration(500);
    pAnimation->setStartValue(ui->scrollArea->verticalScrollBar()->value());
    pAnimation->setEndValue(0);
    pAnimation->start();
    connect(pAnimation,&QPropertyAnimation::finished,[=](){
    pAnimation->deleteLater();
    });
//    ui->scrollArea->verticalScrollBar()->setValue(0);//回到顶端(改用动画)
}

void CToTopWidget::setFlushContent()
{
//    RingWait1::getInstance()->move(this->width()/2 - RingWait1::getInstance()->width()/2,this->height()/2 - RingWait1::getInstance()->height()/2);
//    RingWait1::getInstance()->show();
//    //3s后自动消失
//    QTimer::singleShot(2000,0,[&](){
//        RingWait1::getInstance()->hide();
//    });
//    qDebug() <<QString(u8"收到更新内容消息");
}

void CToTopWidget::addItemToWidget(QWidget *itemWidget)
{
    ui->m_itemsLayout->addWidget(itemWidget);
}

void CToTopWidget::addItemToWidget(QLayout *layout)
{
    ui->m_itemsLayout->addLayout(layout);
}

void CToTopWidget::removeItemFromWidget(QWidget *itemWidget)
{
    ui->m_itemsLayout->removeWidget(itemWidget);
}

void CToTopWidget::removeItemFromWidget(QLayoutItem *layout)
{
    ui->m_itemsLayout->removeItem(layout);
}
