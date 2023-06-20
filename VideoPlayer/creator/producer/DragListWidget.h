#ifndef DRAGLISTWIDGET_H
#define DRAGLISTWIDGET_H

#include <QEvent>
#include <QMimeData>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QListWidget>
#include <QScrollBar>
#include <QFileInfo>
#include <QDebug>

class DragListWidget : public QListWidget
{
    Q_OBJECT

public:
    explicit DragListWidget(QWidget *parent = nullptr);
    ~DragListWidget();
    void    initListWidget(bool on, const int item_W,const int item_H,const qreal rate_minW,const qreal rate_maxW);
    void    resizeItemsSizeHint();

protected:
    void    dragEnterEvent(QDragEnterEvent *event) override;//拖动操作
    void    dropEvent(QDropEvent *event)override;//放下事件
    bool    eventFilter(QObject *object, QEvent *event)override;//事件捕获过滤

private:
    bool    getFileType2(const QString &fileName);
    int     item_calAvg_W();//计算平均宽度

private:
    bool    m_on = true;//是否开启自动调整item个数
    int     m_colCount = 0;//一列的数目
    int     m_item_W = 215;//item的宽度
    int     m_item_H = 160;//item的高度
    qreal   m_minRate_W = 1.025;//宽度调整比例
    qreal   m_maxRate_W = 1.035;//宽度调整比例
    //偏移量(非必须)
    qreal   m_widthOffset = 1;//临时偏移量（非必须）

signals:
    void    sig_item_url_list(QUrl);

};

#endif // DRAGLISTWIDGET_H
