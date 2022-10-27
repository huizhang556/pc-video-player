#ifndef SUBUNITITEM_H
#define SUBUNITITEM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class SubUnitItem;
}

class SubUnitItem : public QLabel
{
    Q_OBJECT

public:
    explicit SubUnitItem(QWidget *parent = nullptr);
    ~SubUnitItem();

private:
    Ui::SubUnitItem *ui;
};

#endif // SUBUNITITEM_H
