#ifndef PICWALLITEM_H
#define PICWALLITEM_H

#include <QWidget>
#include <QMap>
#include <QPushButton>

namespace Ui {
class PicWallItem;
}

class PicWallItem : public QWidget
{
    Q_OBJECT

public:
    explicit PicWallItem(QWidget *parent = nullptr);
    ~PicWallItem();
    QPushButton* getWallItemTextButton();
    void setPicItemWall(QString path);
    void setPicItemWallText(QString text);
    void setPicItemWall2(QString path);
    void setPicItemWallText2(QString text);
protected:
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
signals:
    void sig_sizeChange(QSize size);
private:
    Ui::PicWallItem *ui;
};

#endif // PICWALLITEM_H
