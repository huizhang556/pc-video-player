#ifndef USERLIST_H
#define USERLIST_H

#include "login/UserItem.h"
#include <QWidget>
#include <QDebug>

namespace Ui {
class UserList;
}

class UserList : public QWidget
{
    Q_OBJECT

public:
    explicit UserList(QWidget *parent = nullptr);
    ~UserList();
    void    initWorkUI();

public slots:
    void    slot_addItem(QString name);
    void    slot_removeItem();

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::UserList *ui;
    QStringList nameList = {
        QString(u8"2493920797"),
        QString(u8"天空之城8020"),
        QString(u8"test_guest"),
        QString(u8"风华古城823"),
        QString(u8"美好的明天2023")
    };


private:
    void    checkedItemsCounts();

signals:
    void    sig_list_username(QString);
};

#endif // USERLIST_H
