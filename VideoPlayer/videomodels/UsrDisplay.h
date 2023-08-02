#ifndef USRDISPLAY_H
#define USRDISPLAY_H
#include "database/dataBase.h"

#include <QWidget>
#include <QUrlQuery>
#include <QDebug>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace Ui {
class UsrDisplay;
}

class UsrDisplay : public QWidget
{
    Q_OBJECT

public:
    ~UsrDisplay();
    void    initWorkUI();
    void    handleSignalAndSlot();
    void    updateUsrUiInfo(QUrlQuery queryUrl);
    static  UsrDisplay* getInstance();

protected:
    void    leaveEvent(QEvent *event) override;

private slots:
    void    slot_receivedUserHeader(QNetworkReply* reply);
    void    slot_setUserGrade(const int grade);
    void    slot_setUserWatchedStatus(const QString& user_id,const QString& follow_id);
    void    slot_reloadWatchesCounts(const QString &userid);

private:
    explicit UsrDisplay(QWidget *parent = nullptr);
    Ui::UsrDisplay *ui;
    QUrlQuery               m_usrQueryUrl;
    static  UsrDisplay      *m_pInstance;
    QNetworkAccessManager   *m_manager  =   nullptr;
};

#endif // USRDISPLAY_H
