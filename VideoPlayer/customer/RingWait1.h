#ifndef RINGWAIT1_H
#define RINGWAIT1_H

#include <QtMath>
#include <QWidget>
#include <QPainter>
#include <QColor>
#include <QTimerEvent>

class RingWait1 : public QWidget
{
    Q_OBJECT

public:
    RingWait1(QWidget *parent = nullptr);
    RingWait1(const QSize& size,const QColor& color, const bool switch_on, QWidget *parent = nullptr);
    ~RingWait1();
    void    setColor(const QColor& color);
    static  RingWait1* getInstance();
protected:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent*);

private:
    static RingWait1* m_pInstance;
    QColor  m_color;
    int     offset;
    int     buffer = 0;
    bool    on;

};
#endif
