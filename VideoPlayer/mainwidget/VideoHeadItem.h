#ifndef VIDEOHEADITEM_H
#define VIDEOHEADITEM_H

#include <QWidget>
#include <QLabel>

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

protected:
    bool        eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::VideoHeadItem *ui;

signals:
    void    sig_sendPlayer();
};

#endif // VIDEOHEADITEM_H
