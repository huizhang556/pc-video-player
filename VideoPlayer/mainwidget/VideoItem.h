#ifndef VIDEOITEM_H
#define VIDEOITEM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class VideoItem;
}

class VideoItem : public QLabel
{
    Q_OBJECT

public:
    explicit VideoItem(QWidget *parent = nullptr);
    ~VideoItem();

private:
    Ui::VideoItem *ui;
};

#endif // VIDEOITEM_H
