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
}

void RoundLab::setPadding(int padding)
{
    m_padding = padding;
}

void RoundLab::setBorderColor(const QColor &color)
{
    m_borberColor = color;
}

void RoundLab::setBorderWidth(int width)
{
    m_border = width;
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
            m_border_t = 0;
            this->update();
        }
        else if(event->type() == QEvent::Leave)
        {
            m_border_t = 0;
            this->update();
        }
    }
    return QLabel::eventFilter(watched,event);
}

void RoundLab::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    QPixmap pixmap(m_picpath);
//    painter.setPen(QPen(m_borberColor,m_border_t,Qt::SolidLine));//这里主要是border
    painter.setRenderHints(QPainter::Antialiasing,true);
    QPainterPath path;
    path.addEllipse(m_padding,m_padding,qMin(width()-2*m_padding,height()-2*m_padding),qMin(width()-2*m_padding,height()-2*m_padding));
    painter.setClipPath(path);
    painter.drawPixmap(QRect(m_padding,m_padding,qMin(width()-2*m_padding,height()-2*m_padding),qMin(width()-2*m_padding,height()-2*m_padding)),pixmap);
    painter.drawArc(QRect(m_padding,m_padding,qMin(width()-2*m_padding,height()-2*m_padding),qMin(width()-2*m_padding,height()-2*m_padding)),16*0,360*16);

}
