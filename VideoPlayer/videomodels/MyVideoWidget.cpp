#include "MyVideoWidget.h"
#include <QDebug>

MyVideoWidget::MyVideoWidget(QWidget *parent) :
    QVideoWidget()
{
    Q_UNUSED(parent);
//    int brightness() const;
//    int contrast() const;
//    int hue() const;
//    int saturation() const;
    //监听player播放状态
}

MyVideoWidget::~MyVideoWidget()
{

}

void MyVideoWidget::enterEvent(QEvent *e)
{
    Q_UNUSED(e);
    emit mouseEnterToVideoUI();
    qDebug() << "the mouse enter video";
}

void MyVideoWidget::leaveEvent(QEvent *e)
{
    Q_UNUSED(e);
    emit mouseLeaveFromVideoUI();
    qDebug() << "the mouse leave video";
}

