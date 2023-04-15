#include "CusHSlider.h"

CusHSlider::CusHSlider(QWidget *parent) :
    QSlider(parent)
{
//    setFixedHeight(26);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusHSlider::~CusHSlider()
{
    delete m_frameImages;
}

void CusHSlider::initWorkUI()
{
//    setStyleSheet(style_hslider);
//    setSpacing(25);
//    setOpenTipImage(true);
    m_seekBtn = new QPushButton(this);
    m_seekBtn->setObjectName(QString::fromUtf8("m_seekBtn"));
    m_seekBtn->setFlat(true);
    m_seekBtn->setDefault(false);
    m_seekBtn->setFixedSize(7,this->height());
    m_seekBtn->setStyleSheet("QPushButton#m_seekBtn{"
                            "border-image: url(://images/icon/arrow_seek.png);"
                            "border: none;"
                            "margin: 5px 0px 9px 0px;"
                            "}");
    m_seekBtn->hide();

    m_frameImages = new ValueToImage();
    m_frameImages->setFixedSize(150,100);
}

void CusHSlider::handleSignalsAndSlots()
{
    connect(this,&CusHSlider::destroyed,m_frameImages,&ValueToImage::close);
    connect(m_seekBtn,&QPushButton::clicked,[=](){
        m_use = false;
        m_seekBtn->hide();
        m_frameImages->hide();
        emit sig_valueToPosition((m_seekBtn->x() - m_seekBtn->width()/2)*this->maximum()/(this->width()-24));//margin也算宽度之一
        setCursor(Qt::ArrowCursor);
//        qDebug() <<QString(u8"触发点击！");
    });
}

void CusHSlider::setInstallEventFilter()
{
    this->installEventFilter(this);
    m_seekBtn->installEventFilter(this);
}

void CusHSlider::setSpacing(int spacing)
{
    m_spacing = spacing;
}

void CusHSlider::setOpenTipImage(bool on)
{
    m_isImage = on;
}

void CusHSlider::setLoadingStatus(const QString& text)
{
    m_frameImages->slot_setWaitingStatus(text);
}


bool CusHSlider::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && this->isEnabled())
    {
        if(event->type() == QEvent::HoverEnter)
        {
            m_use = true;
            updateSeekPosition(static_cast<QMouseEvent*>(event));
            setCursor(Qt::PointingHandCursor);
//            qDebug() <<QString(u8"触发HoverEnter！");
        }
        else if(event->type() == QEvent::HoverLeave)
        {
            m_use = false;
            updateSeekPosition(static_cast<QMouseEvent*>(event));
            setCursor(Qt::ArrowCursor);
//            qDebug() <<QString(u8"触发HoverLeave！");
        }
        else if(event->type() == QEvent::HoverMove)
        {
            //注意区分:HoverMove Move MouseMove
            updateSeekPosition(static_cast<QMouseEvent*>(event));
//            qDebug() <<QString(u8"触发移动！");
        }

    }

    return QSlider::eventFilter(watched,event);
}

void CusHSlider::updateSeekPosition(QMouseEvent *event)
{
    updateVernierPosition(event);
    updateValueImagePosition(event);
//    qDebug() << "maxnum = " << this->maximum() << "minnum = " << this->minimum();
    emit sig_anyValuePosition((m_seekBtn->x() - m_seekBtn->width()/2)*this->maximum()/(this->width()-24));//margin也算宽度之一
}

void CusHSlider::updateVernierPosition(QMouseEvent *event)
{
        if(m_use && this->isEnabled())
        {
            m_seekBtn->show();
            m_seekBtn->move(event->pos().x() - m_seekBtn->width()/2,0);
        }
        else
        {
            m_seekBtn->hide();
        }
}

void CusHSlider::updateValueImagePosition(QMouseEvent *event)
{
    if(m_use && m_isImage && this->isEnabled())
    {
        m_seekBtn->show();
//        m_frameImages->setFixedSize(150,100);
        m_frameImages->raise();
        m_frameImages->show();
        const int global_x = this->mapToGlobal(event->pos()).x();
        const int global_y = this->parentWidget()->mapToGlobal(this->pos()).y();
        const int slider_x_start = this->mapToGlobal(this->pos()).x() - 52;
        const int slider_x_end = this->mapToGlobal(this->pos()).x() + this->width() - 75;
        if(slider_x_start < global_x && slider_x_end > global_x )//在进度条的合理区间内显示，不在合理区间内就隐藏
        {
//            qDebug() << QString(u8"合理区域!");
            if(global_x <  slider_x_start + m_frameImages->width()/2)
            {
                m_frameImages->move(slider_x_start,global_y - m_frameImages->height() - m_spacing);
            }
            else if(global_x > slider_x_start + m_frameImages->width()/2 && global_x < slider_x_end - m_frameImages->width()/2)
            {
                m_frameImages->move(global_x - m_frameImages->width()/2,global_y - m_frameImages->height() - m_spacing);
            }
            else if(global_x > slider_x_end - m_frameImages->width()/2)
            {
                m_frameImages->move(slider_x_end - m_frameImages->width(),global_y - m_frameImages->height() - m_spacing);
            }
            m_frameImages->slot_setValueImageTime((m_seekBtn->x() - m_seekBtn->width()/2)*this->maximum()/(this->width()-24));
//            qDebug() << this->mapToGlobal(event->pos()).x();
        }
        else
        {
            m_frameImages->hide();
            m_seekBtn->hide();
//            qDebug() << QString(u8"不合理区域！");
        }
    }
    else
    {
        m_frameImages->hide();
//        m_frameImages->setFixedSize(60,20);
    }
}

//显示图像
void CusHSlider::updateValueToImage(QImage &image)
{
    m_frameImages->slot_setValueImage(image);
}
