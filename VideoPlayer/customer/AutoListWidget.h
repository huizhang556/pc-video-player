#ifndef AUTOLISTWIDGET_H
#define AUTOLISTWIDGET_H
#include <QEvent>
#include <QListWidget>
#include <QScrollBar>
#include <QResizeEvent>
#include <QDebug>

class AutoListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit AutoListWidget(QWidget *parent = nullptr);
    ~AutoListWidget();
    void    set_adjust(bool on);
    void    setOffset(const qreal offset_w = 0);
    void    initListWidget(bool on, const int item_W,const qreal rate_W,const qreal rate_H);
    void    resizeItemsSizeHint();//更新items的大小，以适应填充满整个QListWidget

protected:
    bool    eventFilter(QObject *object, QEvent *event)override;

private:
    int     item_calAvg_W();//计算平均宽度

private:
    bool    m_on = false;//是否开启自动调整item个数
    int     m_colCount;//一列的数目
    int     m_item_W;//item的宽度（注：高度=宽度*缩放比例）
    qreal   m_sizeRate_W = 1.50;//宽度调整比例
    qreal   m_sizeRate_H = 0.65;//高度调整比例

    //偏移量(非必须)
    qreal  m_widthOffset = 0;

};

#endif // AUTOLISTWIDGET_H
