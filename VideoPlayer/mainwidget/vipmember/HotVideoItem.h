#ifndef HOTVIDEOITEM_H
#define HOTVIDEOITEM_H

#include <QWidget>

namespace Ui {
class HotVideoItem;
}

class HotVideoItem : public QWidget
{
    Q_OBJECT

public:
    explicit HotVideoItem(QWidget *parent = nullptr);
    ~HotVideoItem();

private:
    Ui::HotVideoItem *ui;
};

#endif // HOTVIDEOITEM_H
