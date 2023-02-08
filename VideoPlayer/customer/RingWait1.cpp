#include "RingWait1.h"

RingWait1* RingWait1::m_pInstance = nullptr;

RingWait1::RingWait1(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    offset = 0;
    //启动定时器
    startTimer(50);//50ms执行一次
    //设置控件大小
    setFixedSize(100,100);
    setFocusPolicy(Qt::NoFocus);
}

RingWait1::RingWait1(const QSize &size,const QColor &color, const bool switch_on, QWidget *parent):
    QWidget(parent),
    m_color(color),
    on(switch_on)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground, true);
    offset = 0;
    //启动定时器
    startTimer(50);//50ms执行一次
    //设置控件大小
    setFixedSize(size);
    setFocusPolicy(Qt::NoFocus);
}

RingWait1::~RingWait1()
{
    //如果单例指定了父亲，父亲会负责析构
//    if(m_pInstance != nullptr)
//        delete m_pInstance;
//    m_pInstance = nullptr;
}

void RingWait1::setColor(const QColor &color)
{
    m_color = color;
}

RingWait1 *RingWait1::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new RingWait1();
    }
    return m_pInstance;
}

void RingWait1::timerEvent(QTimerEvent*)
{
    ++offset;
    if(offset > 11)
        offset = 0;

   update();
}

void RingWait1::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);  // 反锯齿

    int width = this->width();
    int height = this->height();

    //画笔移动到中间
    painter.translate(width >> 1, height >> 1);

    //计算偏移坐标
    int offsetDest = (width-30)/2;

    painter.setPen(Qt::NoPen);

    //计算小圆坐标
    for(int i = 0;i < 12; ++i)
    {
        QPoint point(0,0);
        painter.setBrush(QColor(0, 221, 242,255-i*20));
        point.setX(offsetDest*qSin((-offset+i)*M_PI/5));//控制圆的个数
        point.setY(offsetDest*qCos((-offset+i)*M_PI/5));//控制圆的个数
        painter.drawEllipse(point.x()-10, point.y()-10, 15, 15);//圆圈的半径
    }

    if(on)
    {
        painter.setFont(QFont("Mircrosoft YaHei", 13));
        painter.setPen(m_color);
        painter.drawText(QPointF(-15, 0), QString("%1%").arg(buffer));
    }
}
