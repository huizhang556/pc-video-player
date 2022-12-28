#ifndef VIDEOHEADITEM_H
#define VIDEOHEADITEM_H
#include "mainwidget/VideoItemHover.h"
#include <QWidget>
#include <QLabel>
#include <QPaintEvent>

namespace Ui {
class VideoHeadItem;
}

class VideoHeadItem : public QLabel
{
    Q_OBJECT

public:
    explicit VideoHeadItem(QWidget *parent = nullptr);
    ~VideoHeadItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setEventFilter();
    void    setItemPicture(const QString path);
    void    setItemBGColor(const QColor& color);
    void    setItemMask(bool enabled);
    void    setItemCanScale(bool can);
protected:
    bool        eventFilter(QObject *watched, QEvent *event)override;
    void        paintEvent(QPaintEvent *event) override;//不要轻易绘制，否则 设置不了图片

private:
    Ui::VideoHeadItem *ui;
    VideoItemHover  *m_videoItemHover = nullptr;
    QString     m_picPath;
    QColor      m_bgColor;
    bool        m_canScale = false;//是否可以进行缩放显示
    bool        m_iscaled = false;//默认不缩放

signals:
    void    sig_sendPlayer();
};

#endif // VIDEOHEADITEM_H
