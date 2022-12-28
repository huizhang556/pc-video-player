#ifndef SUBUNITITEM_H
#define SUBUNITITEM_H

#include <QWidget>
#include <QEvent>
#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QDebug>

namespace Ui {
class SubUnitItem;
}

class SubUnitItem : public QLabel
{
    Q_OBJECT

public:
    explicit SubUnitItem(QWidget *parent = nullptr);
    explicit SubUnitItem(const QString &picpath,QWidget *parent = nullptr);
    ~SubUnitItem();
    void    setItemPicture(const QString& path);
    void    setItemMask(bool enabled);
    void    setItemCanScale(bool can);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;
    void    paintEvent(QPaintEvent *event) override;

private:
    Ui::SubUnitItem *ui;
    QString     m_picPath;
    bool        m_canScale = false;//是否可以进行缩放显示
    bool        m_iscaled = false;//默认不缩放
};

#endif // SUBUNITITEM_H
