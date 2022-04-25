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
    void addPicPathToMap();
    void setPicItemWall(QString path);
    void setPicItemWallText(QString text);

private:
    Ui::PicWallItem *ui;
    QMap<int,QString>       m_picpath;
};

#endif // PICWALLITEM_H
