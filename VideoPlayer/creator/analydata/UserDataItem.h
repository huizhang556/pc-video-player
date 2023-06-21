#ifndef USERDATAITEM_H
#define USERDATAITEM_H

#include <QWidget>

namespace Ui {
class UserDataItem;
}

class UserDataItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserDataItem(QWidget *parent = nullptr);
    ~UserDataItem();

private:
    Ui::UserDataItem *ui;
};

#endif // USERDATAITEM_H
