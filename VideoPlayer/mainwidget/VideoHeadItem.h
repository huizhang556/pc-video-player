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

private:
    Ui::VideoHeadItem *ui;
};

#endif // VIDEOHEADITEM_H
