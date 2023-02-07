#ifndef CPOLLABEL_H
#define CPOLLABEL_H

#include <QLabel>
#include <QEvent>
#include <QBitmap>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
#include <QDebug>


enum  LABTYPE
{
    LAB_NORMAL,//正常LABLE
    LAB_ROUND,//带圆角的
    LAB_ELLIPSE//圆形的
};

class CPolLabel : public QLabel
{
    Q_OBJECT

public:
    explicit CPolLabel(QWidget *parent = nullptr);
    explicit CPolLabel(const QSize& size, const QString& pic, const int radius, QWidget *parent = nullptr);
    ~CPolLabel();

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;
    void    paintEvent(QPaintEvent *event);

private:
    QPixmap scaledPixmap(const QPixmap &src, int width, int height);
    QPixmap generatePixmap(const QPixmap &src, const int &radius);

private:
    QString m_picpath;
    int     m_radius;

};

#endif // CPOLLABEL_H
