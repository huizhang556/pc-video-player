#include "RoundLab.h"

RoundLab::RoundLab(QWidget *parent) :
    QLabel(parent)
{
    this->installEventFilter(this);
}

RoundLab::RoundLab(const QPixmap &path, const QColor &bordercolor,int border, int padding, QWidget *parent):
    QLabel(parent),
    m_picpath(path),
    m_borberColor(bordercolor),
    m_border(border),
    m_padding(padding)
{
    this->installEventFilter(this);
}

RoundLab::~RoundLab()
{

}

void RoundLab::initRoundLabel(const QPixmap &path, const QColor &bordercolor, int border, int padding)
{
    m_picpath       = path;
    m_borberColor   = bordercolor;
    m_border        = border;
    m_padding       = padding;
}

void RoundLab::setPixmap_(const QPixmap &path)
{
    m_picpath   = path;
    this->update();
}

void RoundLab::setPadding(int padding)
{
    m_padding = padding;
    this->update();
}

void RoundLab::setBorderColor(const QColor &color)
{
    m_borberColor = color;
    this->update();
}

void RoundLab::setBorderWidth(bool open, int width)
{
    m_openBorder = open;
    m_border = width;
    this->update();
}

bool RoundLab::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            emit sig_clicked();
            qDebug() << QString(u8"头像被点击！");
        }
        else if(event->type() == QEvent::Enter)
        {
            if(m_openBorder)
            {
                QRadialGradient gradient(0, 0, 200);  // 创建线性渐变，从左上到右下
                gradient.setColorAt(0, QColor(0, 245, 244,255));  // 渐变起始颜色，紫色
                gradient.setColorAt(0.33, QColor(9, 141, 235,255)); // 中间颜色，绿色
                gradient.setColorAt(0.66, QColor(235, 90, 124,255)); // 中间颜色，绿色
                gradient.setColorAt(1, QColor(124, 2, 185, 255));   // 渐变终止颜色，黄色
                m_border_t = m_border;
                m_pen.setBrush(QBrush(gradient));
                m_pen.setWidth(m_border_t);
                m_pen.setStyle(Qt::SolidLine);
                m_pen.setCapStyle(Qt::RoundCap);
                m_pen.setJoinStyle(Qt::RoundJoin);
                this->update();
            }
        }
        else if(event->type() == QEvent::Leave)
        {
            if(m_openBorder)
            {
                m_border_t = m_border;
                QRadialGradient gradient(0, 0, 200);  // 创建线性渐变，从左上到右下
                gradient.setColorAt(0, QColor(0, 245, 244,200));  // 渐变起始颜色，紫色
                gradient.setColorAt(0.33, QColor(9, 141, 235,200)); // 中间颜色，绿色
                gradient.setColorAt(0.66, QColor(235, 90, 124,200)); // 中间颜色，绿色
                gradient.setColorAt(1, QColor(124, 2, 185, 200));   // 渐变终止颜色，黄色
                m_pen.setBrush(QBrush(gradient));
                m_pen.setWidth(m_border_t);
                m_pen.setStyle(Qt::SolidLine);
                m_pen.setCapStyle(Qt::RoundCap);
                m_pen.setJoinStyle(Qt::RoundJoin);
                this->update();
            }

        }
    }
    return QLabel::eventFilter(watched,event);
}

void RoundLab::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QPixmap pixmap(m_picpath);
    if(m_openBorder)
    {

    painter.setPen(m_pen);//设置边框
    }
    else
    {
    painter.setPen(QPen(Qt::transparent,0,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));//不设置边框
    }
    painter.setRenderHints(QPainter::Antialiasing,true);
    QPainterPath path;
    path.addEllipse((m_padding-m_border),
                    (m_padding-m_border),
                    qMin(width()-2*(m_padding-m_border),height()-2*(m_padding-m_border)),
                    qMin(width()-2*(m_padding-m_border),height()-2*(m_padding-m_border)));
    painter.setClipPath(path);

    painter.drawPixmap((m_padding-m_border),
                       (m_padding-m_border),
                       qMin(width()-2*(m_padding-m_border),height()-2*(m_padding-m_border)),
                       qMin(width()-2*(m_padding-m_border),height()-2*(m_padding-m_border)),pixmap);

    painter.drawArc(QRect((m_padding-m_border),
                          (m_padding-m_border),
                          qMin(width()-2*(m_padding-m_border),height()-2*(m_padding-m_border)),
                          qMin(width()-2*(m_padding-m_border),height()-2*(m_padding-m_border))),
                          0*16,360*16);//315*16,270*16

}
