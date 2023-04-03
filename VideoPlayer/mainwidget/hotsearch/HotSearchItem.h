#ifndef HOTSEARCHITEM_H
#define HOTSEARCHITEM_H

#include <QWidget>
#include <QStyle>
#include <QDebug>

namespace Ui {
class HotSearchItem;
}

class HotSearchItem : public QWidget
{
    Q_OBJECT

public:
    explicit HotSearchItem(QWidget *parent = nullptr);
    explicit HotSearchItem(const QString order, const QString hotStr, bool up, QWidget *parent = nullptr);
    ~HotSearchItem();
    void        initWorkUI();
    void        handleSignalsAndSlots();

private:
    Ui::HotSearchItem *ui;

private:
    void    setItemOrderText(const QString& order);

signals:
    void    sig_sendItemText(QString);
};

#endif // HOTSEARCHITEM_H
