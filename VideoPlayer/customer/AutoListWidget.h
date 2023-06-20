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
    void    initListWidget(bool on, const int item_W,const int item_H,const qreal rate_minW,const qreal rate_maxW);
    void    resizeItemsSizeHint();//更新items的大小，以适应填充满整个QListWidget

protected:
    bool    eventFilter(QObject *object, QEvent *event)override;

private:
    int     item_calAvg_W();//计算平均宽度

private:
    bool    m_on = true;//是否开启自动调整item个数
    int     m_colCount = 0;//一列的数目
    int     m_item_W = 215;//item的宽度
    int     m_item_H = 160;//item的高度
    qreal   m_minRate_W = 1.025;//宽度调整比例
    qreal   m_maxRate_W = 1.035;//宽度调整比例

    //偏移量(非必须)
    qreal  m_widthOffset = 1;

};

#endif // AUTOLISTWIDGET_H
