#ifndef HEADHOVER_H
#define HEADHOVER_H

#include "login/ChangeHead.h"

#include <QWidget>
#include <QPixmap>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>


namespace Ui {
class HeadHover;
}

class HeadHover : public QWidget
{
    Q_OBJECT

public:
    explicit HeadHover(QWidget *parent = nullptr);
    ~HeadHover();
    void        initWorkUI();
    void        handleSignalsAndSlots();

public slots:
    void        slot_setCurrentUserInfo(const QString &head,const QString &nick,int grade,const QString &info);//设置个人信息

protected:
    void        leaveEvent(QEvent *event) override;
private:
    Ui::HeadHover *ui;
    QByteArray              m_headBytes;
    QPixmap                 m_headPixmap;
    QNetworkAccessManager   *m_manager;

private:
    void        slots_setUserHead(const QString &head);
    void        slots_setUserName(const QString &nick);
    void        slots_setUserIcon(int grade,const QString &nick);
    void        slot_setUserInfo(const QString &info);
    void        slot_receivedNetworkPicture(QNetworkReply* reply);

signals:
    void        sig_itemChanged(QString);
};

#endif // HEADHOVER_H
