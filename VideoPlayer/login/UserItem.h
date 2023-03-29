#ifndef USERITEM_H
#define USERITEM_H

#include <QWidget>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace Ui {
class UserItem;
}

class UserItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserItem(QWidget *parent = nullptr);
    explicit UserItem(const QString& user_nick, const QString& user_pwd, const QString& user_header, QWidget *parent = nullptr);
    ~UserItem();
    void        initWorkUI();
    void        handleSignalsAndSLots();

private:
    void    setUserName(const QString& name);
    void    setUserPwd(const QString& pwd);
    void    setUserHeader(const QString &header);

private slots:
    void    slot_setUserHeaderPix(QNetworkReply *reply);

private:
    Ui::UserItem *ui;
    QString m_userName;
    QString m_userPwd;
    QString m_userHeader;
    QNetworkAccessManager   *m_manager = nullptr;

signals:
    void    sig_item_remove(QString);
    void    sig_item_clicked(QString);
};

#endif // USERITEM_H
