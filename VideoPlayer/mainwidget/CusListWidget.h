#ifndef CUSLISTWIDGET_H
#define CUSLISTWIDGET_H

#include <QEvent>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QScrollBar>
#include <QTimer>
#include <QPropertyAnimation>
#include <QDebug>

class CusListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit CusListWidget(QWidget *parent = nullptr);
    ~CusListWidget();
    void        initWorkUI();
    void        handleSignalsAndSlots();
    void        setInstallEventFilter();
    void        setButtonControl(bool enabled);//是否需要显示左右调节按钮
    void        setOffset(int itemwidth,int width_offset,int adjust_lw,int adjust_rw,int adjust_h);
    void        setZoomScale(double scale);

protected:
    bool        eventFilter(QObject *object, QEvent *event)override;

private:
    double      m_scale = 1.3;
    int         m_adjust_lw;
    int         m_adjust_rw;
    int         m_adjust_h;
    int         m_itemWidth;
    int         m_widthOffset;
    bool        m_isShow = false;

    QPushButton     *m_videoButton_L   =   nullptr;
    QPushButton     *m_videoButton_R   =   nullptr;

private:
    void    autoResizeListItemsSize();//动态调节item显示的个数
    int     calAvergeWidth();
    void    checkPositonAdjust_LR();
    void    updataAdjustButton_LR();//随着窗口变化调节左右按钮的位置
};

#endif // CUSLISTWIDGET_H
