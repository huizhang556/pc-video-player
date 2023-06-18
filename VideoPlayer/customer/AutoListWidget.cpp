#include "AutoListWidget.h"

AutoListWidget::AutoListWidget(QWidget *parent) :
    QListWidget(parent)
{
    this->installEventFilter(this);
}

AutoListWidget::~AutoListWidget()
{

}

void AutoListWidget::set_adjust(bool on)
{
    m_on = on;
}

void AutoListWidget::setOffset(const qreal offset_w)
{
    m_widthOffset = offset_w;
}

//初始化参数
void AutoListWidget::initListWidget(bool on, const int item_W,const qreal rate_W,const qreal rate_H)
{
    m_on = on;
    m_item_W = item_W;
    m_sizeRate_W = rate_W;
    m_sizeRate_H = rate_H;
}

bool AutoListWidget::eventFilter(QObject *object, QEvent *event)
{
    if(object == this && event->type() == QEvent::Resize)
    {
        if(m_on)//打开情况下
            resizeItemsSizeHint();
    }
    return QListWidget::eventFilter(object,event);
}

//自动调节
void AutoListWidget::resizeItemsSizeHint()
{
    //不符合条件情况
    if(this->count() == 0) return;
    //符合条件
    if(this->count() > 0)
    {
        int avgWidth = item_calAvg_W();//求当前平均宽度
        if(avgWidth < m_item_W)//平均宽度不能小于默认的宽度
        {
            avgWidth = m_item_W;
        }
        else if(avgWidth > (int)(m_item_W*m_sizeRate_W))//平均宽度不能大于宽度乘以缩放比例后的宽度
        {
            avgWidth = (int)(m_item_W*m_sizeRate_W);
        }
        for(int i = 0; i < this->count(); i++)
        {
            this->item(i)->setSizeHint(QSize(avgWidth,avgWidth*m_sizeRate_H));//高度 = 当前宽度*m_sizeRate_H
        }
    }
    this->horizontalScrollBar()->setValue(0);//回到最顶端
}

int AutoListWidget::item_calAvg_W()
{
    int Width = (int)(this->width()-this->verticalScrollBar()->width() - m_widthOffset);
//    qDebug() << QString(u8"第一个ITEM默认宽度：%1").arg(sizeHint_w);
    int avgWidth = 0;
    if(Width < m_item_W*2)//小于3个默认宽度，默认按2个宽度拉升
    {
        avgWidth = Width;
        m_colCount = 1;//显示两列
    }
    else if(Width < m_item_W*3)
    {
        avgWidth = (int)(Width/2);
        m_colCount = 2;
    }
    else if(Width < m_item_W*4)
    {
        avgWidth = (int)(Width/3);
        m_colCount = 3;
    }
    else if(Width < m_item_W*5)
    {
        avgWidth = (int)(Width/4);
        m_colCount = 4;
    }
    else if(Width < m_item_W*6)
    {
        avgWidth = (int)(Width/5);
        m_colCount = 5;
    }
    else if(Width < m_item_W*7)
    {
        avgWidth = (int)(Width/6);
        m_colCount = 6;
    }
    else if(Width < m_item_W*8)
    {
        avgWidth = (int)(Width/7);
        m_colCount = 7;
    }
    else if(Width < m_item_W*9)
    {
        avgWidth = (int)(Width/8);
        m_colCount = 8;
    }
    else if(Width < m_item_W*10)
    {
        avgWidth = (int)(Width/9);
        m_colCount = 9;
    }
    else
    {
        avgWidth = m_item_W;
    }
    return avgWidth;
}
