#include "AutoListWidget.h"

AutoListWidget::AutoListWidget(QWidget *parent) :
    QListWidget(parent)
{
    this->installEventFilter(this);
    this->verticalScrollBar()->setFixedWidth(10);
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
void AutoListWidget::initListWidget(bool on, const int item_W, const int item_H, const qreal rate_minW, const qreal rate_maxW)
{
    m_on = on;
    m_item_W = item_W;
    m_item_H = item_H;
    m_minRate_W = rate_minW;
    m_maxRate_W = rate_maxW;
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
    //不符合条件情况1
    if(this->count() == 0) return;

    //符合条件
    if(this->count() > 0)
    {
        //宽度盛不下item才进行缩放
        if(this->count()*this->item(0)->sizeHint().width() > this->width())
        {
            int avgWidth = item_calAvg_W();
//            if(avgWidth < m_item_W)
//            {
//                avgWidth = m_item_W;
//            }

            for(int i = 0; i < this->count(); i++)
            {
                this->item(i)->setSizeHint(QSize(avgWidth,m_item_H));//只变化宽度，高度固定
            }
        }
        this->horizontalScrollBar()->setValue(0);//回到最顶端
    }
}

int AutoListWidget::item_calAvg_W()
{
    int avg_w = 0;
    int Width = this->width() - this->verticalScrollBar()->width() - m_widthOffset;
    if (Width <= m_item_W*m_maxRate_W*1) //1个item最小宽度 和 最大宽度之间
    {
        //(200 - 215]
        m_colCount = 1;
    }
    else if(Width <= m_item_W*m_maxRate_W*2)
    {
        //(215,430]
        m_colCount = 2;
    }
    else if(Width <= m_item_W*m_maxRate_W*3)
    {
        //(430,645]
        m_colCount = 3;
    }
    else if(Width <= m_item_W*m_maxRate_W*4)
    {
        m_colCount = 4;
    }
    else if(Width <= m_item_W*m_maxRate_W*5)
    {
        m_colCount = 5;
    }
    else if(Width <= m_item_W*m_maxRate_W*6)
    {
        m_colCount = 6;
    }
    else if(Width <= m_item_W*m_maxRate_W*7)
    {
        m_colCount = 7;
    }
    else if(Width <= m_item_W*m_maxRate_W*8)
    {
        m_colCount = 8;
    }
    else if(Width <= m_item_W*m_maxRate_W*9)
    {
        m_colCount = 9;
    }
    else if(Width <= m_item_W*m_maxRate_W*10)
    {
        m_colCount = 10;
    }
    else if(Width <= m_item_W*m_maxRate_W*11)
    {
        m_colCount = 11;
    }
    else if(Width <= m_item_W*m_maxRate_W*12)
    {
        m_colCount = 12;
    }

    avg_w = (int)(Width/m_colCount);
//    qDebug() << QString(u8"计算应该放列数:") << m_colCount << QString(u8"计算每列宽度:") << avg_w;
    return avg_w;
}
