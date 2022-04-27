#include "MyVideoWidget.h"
#include <QDebug>

MyVideoWidget::MyVideoWidget(QWidget *parent) :
    QVideoWidget()
{
    Q_UNUSED(parent);
//    this->setWindowFlags(Qt::FramelessWindowHint);
//    int brightness() const;
//    int contrast() const;
//    int hue() const;
//    int saturation() const;
    //监听player播放状态
//    m_playAdjust = new PlayCtlAdjustForm();
//    m_playAdjust->setObjectName(QString::fromLocal8Bit("m_playAdjust"));
}

MyVideoWidget::~MyVideoWidget()
{

}

void MyVideoWidget::enterEvent(QEvent *e)
{
    Q_UNUSED(e);
//    emit mouseEnterToVideoUI();
//    updatePlayAdustForm();
//    qDebug() << "the mouse enter video";
}

void MyVideoWidget::leaveEvent(QEvent *e)
{
    Q_UNUSED(e);
//    emit mouseLeaveFromVideoUI();
//    m_playAdjust->hide();
    //    qDebug() << "the mouse leave video";
}

void MyVideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
//    if(isFullScreen())
//    {
//        updatePlayAdustForm();
//    }
//    else
//    {
//        return;
//    }

}

/*更新播放栏目位置*/
//void MyVideoWidget::updatePlayAdustForm()
//{
//    m_playAdjust->setGeometry(0,this->height(),this->width(),60);
//    m_playAdjust->raise();
//    m_playAdjust->show();
//}

