#ifndef BUYVIPITEM_H
#define BUYVIPITEM_H

#include <QWidget>

namespace Ui {
class BuyVipItem;
}

class BuyVipItem : public QWidget
{
    Q_OBJECT

public:
    explicit BuyVipItem(QWidget *parent = nullptr);
    ~BuyVipItem();

private:
    Ui::BuyVipItem *ui;
};

#endif // BUYVIPITEM_H
