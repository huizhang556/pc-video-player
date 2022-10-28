#ifndef VIDEOHEADITEM_H
#define VIDEOHEADITEM_H

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
protected:
    bool        eventFilter(QObject *watched, QEvent *event)override;
    void        paintEvent(QPaintEvent *event) override;//不要轻易绘制，否则 设置不了图片

private:
    Ui::VideoHeadItem *ui;
    QString     m_picPath;

signals:
    void    sig_sendPlayer();
};

#endif // VIDEOHEADITEM_H
