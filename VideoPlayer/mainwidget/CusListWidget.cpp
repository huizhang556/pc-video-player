#include "CusListWidget.h"

#include <QScrollBar>
#include <QDebug>

CusListWidget::CusListWidget(QWidget *parent) :
    QListWidget(parent)
{
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    setButtonControl(true);//默认带有左右调节按钮

}

CusListWidget::~CusListWidget()
{

}

void CusListWidget::initWorkUI()
{

    this->setFrameShape(QFrame::NoFrame);
    this->setAutoScroll(false);//鼠标在两端拖动不进行滚动
    m_videoButton_L = new QPushButton("<",this);
    m_videoButton_L->setObjectName(QString::fromLocal8Bit("m_videoButton_L"));
    m_videoButton_L->setFixedSize(22,30);
    m_videoButton_L->hide();

    m_videoButton_R = new QPushButton(">",this);
    m_videoButton_R->setObjectName(QString::fromLocal8Bit("m_videoButton_R"));
    m_videoButton_R->setFixedSize(22,30);
    m_videoButton_R->hide();
}

void CusListWidget::handleSignalsAndSlots()
{
        connect(m_videoButton_L,&QPushButton::clicked,[=](){
            if(this->horizontalScrollBar()->value() == this->horizontalScrollBar()->minimum()) return;
            if(m_isShow)
            {
                m_videoButton_L->hide();
                m_videoButton_R->hide();

            }
            int step = this->horizontalScrollBar()->value();
            QPropertyAnimation *pAnimation = new QPropertyAnimation(this->horizontalScrollBar(),"value",this);
            pAnimation->setDuration(500);
            pAnimation->setStartValue(step);
            pAnimation->setEndValue(step - this->item(0)->sizeHint().width());
            pAnimation->start();
            connect(pAnimation,&QPropertyAnimation::finished,[=](){
            pAnimation->deleteLater();
            checkPositonAdjust_LR();
            });
//            this->horizontalScrollBar()->setValue(step - this->item(0)->sizeHint().width());
        });

        connect(m_videoButton_R,&QPushButton::clicked,[=](){
            if(this->horizontalScrollBar()->value() == this->horizontalScrollBar()->maximum()) return;
            if(m_isShow)
            {
                m_videoButton_L->hide();
                m_videoButton_R->hide();

            }
            int step = this->horizontalScrollBar()->value();
            QPropertyAnimation *pAnimation = new QPropertyAnimation(this->horizontalScrollBar(),"value",this);
            pAnimation->setDuration(500);
            pAnimation->setStartValue(step);
            pAnimation->setEndValue(step + this->item(0)->sizeHint().width());
            pAnimation->start();
            connect(pAnimation,&QPropertyAnimation::finished,[=](){
            pAnimation->deleteLater();
            checkPositonAdjust_LR();
            });
//            this->horizontalScrollBar()->setValue(step + this->item(0)->sizeHint().width());
        });

//        connect(this->horizontalScrollBar(),&QScrollBar::valueChanged,[=](int val){
//            checkPositonAdjust_LR();
//        });
}

void CusListWidget::setInstallEventFilter()
{
    //安装事件过滤器
    this->installEventFilter(this);
}

void CusListWidget::setButtonControl(bool enabled)
{
    if(enabled)
    {
        m_isShow = true;
    }
    else
    {
        m_isShow = false;
    }
}

/********************************************
 1. @ProjName:   04_20SubVideoPlayer
 2. @Author:     ZhangHui
 3. @Date:       2023-01-15
 4. @Brief:      调节左右调节按钮偏移位置
 5. @Param:      itemwidth：一个item的保持的宽度（固定），width_offset：左右边距，adjust_w：高度，adjust_h：高度
 6. @Return:     void
*********************************************/
void CusListWidget::setOffset(int itemwidth,int width_offset,int adjust_lw,int adjust_rw,int adjust_h)
{
    m_itemWidth = itemwidth;
    m_widthOffset = width_offset;
    m_adjust_lw = adjust_lw;
    m_adjust_rw = adjust_rw;
    m_adjust_h = adjust_h;
}

void CusListWidget::setZoomScale(double scale)
{
    m_scale = scale;
}

void CusListWidget::setAdjist(bool adjust)
{
    m_adjust = adjust;
}

bool CusListWidget::eventFilter(QObject *object, QEvent *event)
{
    if(object == this && event->type() == QEvent::Resize)
    {
        autoResizeListItemsSize();
        updataAdjustButton_LR();//更新位置
        checkPositonAdjust_LR();//判断是否应该显示
    }
    return QWidget::eventFilter(object,event);
}

void CusListWidget::autoResizeListItemsSize()
{
    if(!m_adjust) return;
    if(this->count() == 0) return;

    if(this->count() > 0)
    {
        int sizeHint_h = this->item(0)->sizeHint().height();//求默认宽度
        int avgWidth = calAvergeWidth();//求当前平均宽度
        if(avgWidth < m_itemWidth)//平均宽度不能小于默认的宽度
        {
            avgWidth = m_itemWidth;
        }
        if(avgWidth > (int)(m_itemWidth*m_scale))
        {
            avgWidth = (int)(m_itemWidth*m_scale);
        }
//        qDebug() << QString(u8"第一个ITEM默认高度：%1").arg(sizeHint_h);
//        qDebug() << QString(u8"第一个ITEM求得宽度：%1").arg(avgWidth);
        for(int i = 0; i < this->count(); i++)
        {
            this->item(i)->setSizeHint(QSize(avgWidth,sizeHint_h));
        }
    }
    this->horizontalScrollBar()->setValue(0);//回到最顶端
}

int CusListWidget::calAvergeWidth()
{
    int Width = (int)(this->width()-this->verticalScrollBar()->width() - m_widthOffset);
    int sizeHint_w = m_itemWidth;
//    qDebug() << QString(u8"第一个ITEM默认宽度：%1").arg(sizeHint_w);
    int avgWidth = 0;
    if(Width < sizeHint_w*3)//小于3个默认宽度，默认按2个宽度拉升
    {
        avgWidth = (int)(Width/2);
    }
    else if(Width < sizeHint_w*4)
    {
        avgWidth = (int)(Width/3);
    }
    else if(Width < sizeHint_w*5)
    {
        avgWidth = (int)(Width/4);
    }
    else if(Width < sizeHint_w*6)
    {
        avgWidth = (int)(Width/5);
    }
    else if(Width < sizeHint_w*7)
    {
        avgWidth = (int)(Width/6);
    }
    else if(Width < sizeHint_w*8)
    {
        avgWidth = (int)(Width/7);
    }
    else if(Width < sizeHint_w*9)
    {
        avgWidth = (int)(Width/8);
    }
    else if(Width < sizeHint_w*10)
    {
        avgWidth = (int)(Width/9);
    }
    else
    {
        avgWidth = sizeHint_w;
    }
    return avgWidth;
}

void CusListWidget::checkPositonAdjust_LR()
{
    int val = this->horizontalScrollBar()->value();
    if(m_isShow)
    {
        if(this->horizontalScrollBar()->minimum() == val)
        {
            m_videoButton_L->hide();
            m_videoButton_R->show();
        }
        else if(this->horizontalScrollBar()->maximum() == val)
        {
            m_videoButton_R->hide();
            m_videoButton_L->show();
        }
        else if(this->horizontalScrollBar()->minimum() < val < this->horizontalScrollBar()->maximum())
        {
            m_videoButton_R->show();
            m_videoButton_L->show();
        }
    }
}

void CusListWidget::updataAdjustButton_LR()
{
    if(m_isShow)
    {
        m_videoButton_L->setGeometry(m_adjust_lw,
                               this->height()/2 - m_videoButton_L->height()/2 - m_adjust_h,
                               m_videoButton_L->width(),m_videoButton_L->height());

        m_videoButton_R->setGeometry(this->width()-m_videoButton_R->width()- m_adjust_rw,
                                   this->height()/2 - m_videoButton_R->height()/2 - m_adjust_h,
                                m_videoButton_R->width(),m_videoButton_R->height());
        m_videoButton_L->raise();
        m_videoButton_L->show();
        m_videoButton_R->raise();
        m_videoButton_R->show();
    }
}
