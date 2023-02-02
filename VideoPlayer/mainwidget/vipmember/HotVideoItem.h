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

    void    setVideoItemPicture(const QString& picpath);

private:
    Ui::HotVideoItem *ui;
};

#endif // HOTVIDEOITEM_H
