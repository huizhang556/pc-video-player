#ifndef USERITEM_H
#define USERITEM_H

#include <QWidget>

namespace Ui {
class UserItem;
}

class UserItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserItem(QWidget *parent = nullptr);
    explicit UserItem(QString name, QWidget *parent = nullptr);
    ~UserItem();
    void        initWorkUI();
    void        handleSignalsAndSLots();

private:
    void    setUserName(const QString name);

private:
    Ui::UserItem *ui;
    int m_id;
    QString m_userName;
//    QString m_userPwd;

signals:
    void    sig_item_remove();
    void    sig_item_clicked(QString);
};

#endif // USERITEM_H
