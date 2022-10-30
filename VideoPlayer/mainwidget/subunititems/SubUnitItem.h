#ifndef SUBUNITITEM_H
#define SUBUNITITEM_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>

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

protected:
    void    paintEvent(QPaintEvent *event) override;

private:
    Ui::SubUnitItem *ui;
    QString m_picPath;
};

#endif // SUBUNITITEM_H
