#ifndef REFRESHBUTTON_H
#define REFRESHBUTTON_H

/*实现一个刷新效果按钮*/

#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QMatrix>
#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>


class RefreshButton : public QPushButton
{
    Q_OBJECT

public:
    RefreshButton(QWidget *parent = 0);
    ~RefreshButton();
    void        initWorkUI();//初始化
    void        handleSignalsAndSLots();
    void        setPixmap(const QPixmap& pixmap,const QSize& size);
    void        setInterval(int msec);

protected:
    void      paintEvent(QPaintEvent* event)override;
    bool      eventFilter(QObject *watched, QEvent *event)override;

private:
    void        on_refreshButton();//刷新

private:
    QTimer      m_timer;
    int         m_angle;//旋转角度
    int         m_interval;
    QMatrix     m_matrix;
    QPixmap     m_pixmap;
};

#endif // REFRESHBUTTON_H
