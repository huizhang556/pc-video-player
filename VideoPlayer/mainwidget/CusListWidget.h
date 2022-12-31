#ifndef CUSLISTWIDGET_H
#define CUSLISTWIDGET_H

#include <QEvent>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
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
    void        setOffset(int itemwidth,int width_offset,int adjust_w,int adjust_h);

protected:
    bool        eventFilter(QObject *object, QEvent *event)override;

private:
    int         m_adjust_w;
    int         m_adjust_h;
    int         m_itemWidth;
    int         m_widthOffset;
    bool        m_isShow = false;

    QPushButton     *m_videoButton_L   =   nullptr;
    QPushButton     *m_videoButton_R   =   nullptr;

private:
    void    autoResizeListItemsSize();//动态调节item显示的个数
    int     calAvergeWidth();
    void    updataAdjustButton_LR();//随着窗口变化调节左右按钮的位置
};

#endif // CUSLISTWIDGET_H
