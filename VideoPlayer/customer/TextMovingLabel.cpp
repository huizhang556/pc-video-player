#include "TextMovingLabel.h"

TextMovingLabel::TextMovingLabel(QWidget *parent)
    : QLabel(parent),
      m_direction(0),
      m_x(0)
{
    this->installEventFilter(this);
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_UpdateTextGeometry()));
}

TextMovingLabel::~TextMovingLabel()
{

}

void TextMovingLabel::initMoveText(MOVETYPE type, const QString &text, const QFont &font, const QColor &color, const int &interval)
{
    setTextMoveType(type);
    setTimerInterval(interval);
    setTextColor(color);
    setTextFont(font);
    setText(text);
}

void TextMovingLabel::setText(const QString &t)
{
    m_text = t;
    m_x = 0;
    update();//运行过程中设置不同文字立即生效
}

void TextMovingLabel::setTextColor(const QColor &color)
{
    m_color = color;
}

void TextMovingLabel::setTextFont(const QFont &font)
{
    m_font = font;
}

void TextMovingLabel::setTimerInterval(const int interval)
{
    m_upTime = interval;
    m_timer->setInterval(m_upTime);
    m_timer->start();
}

void TextMovingLabel::setTextMoveType(MOVETYPE type)
{
    m_moveType = type;
}

void TextMovingLabel::setTextMoveOffset(const int &offset_start, const int &offset_end)
{
    m_startOffset = offset_start;
    m_endOffset = offset_end;
}

void TextMovingLabel::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter p(this);
    p.setFont(m_font);
    p.setPen(m_color);

    QFontMetrics metric(m_font);
    int y = (height()- metric.height())/2;//垂直居中显示
    p.drawText(m_x, y, metric.width(m_text), metric.height(), Qt::AlignLeft, m_text);
}

inline int TextMovingLabel::getDirection(const QString &text)
{
    QFontMetrics metrics(m_font);
    int tw = metrics.width(text);
    if(MOVETYPE::FIFO ==  m_moveType)
    {
        if(tw <= width() + tw - m_endOffset)
        {
            if(m_x + tw > width() + tw - m_endOffset)
                return 0;//left
            else if(m_x <= 0)
            return 1;//right
            return m_direction;
        }
        else
        {
            if(m_x == 10)
              return 0;
            else if(m_x <= width()-tw-10)
            return 1;
            return m_direction;
        }
    }
    else if(MOVETYPE::FILO ==  m_moveType)
    {
        if(tw <= width())
        {
            if(m_x + tw > width())
                return 0;//left
            else if(m_x <= 0)
            return 1;//right
            return m_direction;
        }
        else
        {
            if(m_x == 10)
              return 0;
            else if(m_x <= width()-tw-10)
            return 1;
            return m_direction;
        }
    }
}

bool TextMovingLabel::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            slot_controlTimer(false);
        }
        else if(event->type() == QEvent::Leave)
        {
            slot_controlTimer(true);
        }
    }
    return QWidget::eventFilter(watched,event);
}

void TextMovingLabel::slot_UpdateTextGeometry()
{
    QFontMetrics metric(m_font);
    int tw = metric.width(m_text);
    if(MOVETYPE::FIFO ==  m_moveType)
    {
        if(tw > width()) //If the text width greater than widget width
        {
            if(m_direction) //right
                m_x++;
            else          //left
    //            m_x--;
                m_x = 0 - tw + m_startOffset;
        }
        else
        {
            if(m_direction) //right
                m_x++;
            else          //left
    //            m_x--;
                m_x = 0 - tw + m_startOffset;
        }
    }
    else if(MOVETYPE::FILO ==  m_moveType)
    {
        if(tw > width()) //If the text width greater than widget width
        {
            if(m_direction) //right
                m_x++;
            else          //left
                m_x--;
        }
        else
        {
            if(m_direction) //right
                m_x++;
            else          //left
                m_x--;
        }
    }
    m_direction = getDirection(m_text);
    update();
}

void TextMovingLabel::slot_controlTimer(bool start)
{
    if(start)
        m_timer->start();
    else
        m_timer->stop();
}

