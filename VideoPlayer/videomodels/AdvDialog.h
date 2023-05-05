#ifndef ADVDIALOG_H
#define ADVDIALOG_H
#include "videomodels/RecomVideoTab.h"
#include "videomodels/AdvterItem.h"
#include "database/dataBase.h"

#include <QScrollBar>
#include <QStringList>
#include <QUrlQuery>
#include <QDialog>
#include <QTimer>
#include <QDebug>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

enum    POPTYPE
{
    P_NEXTMEDIA,
    P_BREAKMEDIA,
    P_OTHEREDIA,
    P_UNKNOW
};

namespace Ui {
class AdvDialog;
}

class AdvDialog : public QDialog
{
    Q_OBJECT

public:
    ~AdvDialog();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    static  AdvDialog* getInstance();
    void    exec_(POPTYPE type, const int media_id);
    void    hide_();

public slots:
    void    slot_addItemTo_ContinueNextList(QList<QVariant>& medias);

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    explicit AdvDialog(QWidget *parent = nullptr);
    Ui::AdvDialog *ui;
    POPTYPE    m_curType;
    static  AdvDialog* m_pInstance;
    QUrlQuery   m_curQurlQuery;
    QStringList m_curPlayList;
    int         m_media_id = 1;
    QString     m_curUserId;
    QString     m_curUserName;
    QString     m_curMediaUrl;
    QString     m_curMedialias;
    QString     m_curHeader;
    QString     m_curTheme;
    int         m_startpos = 1;//请求起始位置1，要排除第一个是自己的情况
    QNetworkAccessManager   *m_manager  =   nullptr;

private slots:
    void    slot_receivedUserHeader(QNetworkReply* reply);
    void    slot_setUserHeader(const QString& userHeader);
    void    slot_setUserName(const QString& userName);
    void    slot_getCurUserInfo(const int media_id);

signals:
    void    sig_play_cancel();//取消连播
    void    sig_play_continue(const int,const QStringList&,const QUrlQuery&);//继续连播
};

#endif // ADVDIALOG_H
