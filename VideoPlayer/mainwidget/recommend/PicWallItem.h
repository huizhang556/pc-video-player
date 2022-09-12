#ifndef PICWALLITEM_H
#define PICWALLITEM_H

#include "mainwidget/CusLabelItem.h"

#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QPainter>
#include <QPaintEvent>
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

    void    setPicItemWall(QString path);
    void    setPicItemWallText(QString text);
    void    setPicItemWall2(QString path);
    void    setPicItemWallText2(QString text);

    CusLabelItem*    getItemPic_1Label();
    CusLabelItem*    getItemPic_2Label();

protected:
    void    paintEvent(QPaintEvent *event) override;
    void    resizeEvent(QResizeEvent *event) override;
    bool    eventFilter(QObject *watched, QEvent *event) override;
signals:
    void    sig_sizeChange(QSize size);
private:
    Ui::PicWallItem *ui;

private:
    void    setItemMask();
//    void    setItemHotText(const QString& picpath1,const QString& picpath2);
//    void    setItemPlayCounts(const QString& counts1,const QString& counts2);
//    void    setItemMainPlayOn(bool on1, bool on2);
//    void    setItemPlayOn(bool on1, bool on2);

};

#endif // PICWALLITEM_H
