#ifndef PICWALLITEM_H
#define PICWALLITEM_H

#include <QWidget>
#include <QMap>

namespace Ui {
class PicWallItem;
}

class PicWallItem : public QWidget
{
    Q_OBJECT

public:
    explicit PicWallItem(QWidget *parent = nullptr);
    ~PicWallItem();
    void setPicItemWall(QString path);
    void setPicItemWallText(QString text);

private:
    Ui::PicWallItem *ui;
};

#endif // PICWALLITEM_H
