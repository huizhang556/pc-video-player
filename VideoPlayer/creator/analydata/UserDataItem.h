#ifndef USERDATAITEM_H
#define USERDATAITEM_H
#include "database/dataBase.h"

#include <QMovie>
#include <QWidget>
#include <QUrlQuery>
#include <QDebug>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

enum UserDataType
{
    FANS,
    WATCHES,
    VIDEO,
    COMMIT,
};

namespace Ui {
class UserDataItem;
}

class UserDataItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserDataItem(QWidget *parent = nullptr);
    explicit UserDataItem(const UserDataType& type,const QUrlQuery& query, QWidget *parent = nullptr);
    ~UserDataItem();
    void        initworkUI();
    void        handleSignalsAndSlots();
    QString     get_user_keywords();
    QString     get_user_nick();
    QString     get_user_vurl();

public slots:


private:
    void        set_user_id();
    void        set_user_page();
    void        set_user_grade();
    void        set_user_level();
    void        set_user_header();
    void        set_user_nick();
    void        set_user_ctime();
    void        set_user_motto();
    void        set_user_theme();
    void        set_user_likeStatus();
    void        set_video_url();


private slots:
    void    slot_receivedUserHeader(QNetworkReply* reply);

private:
    Ui::UserDataItem *ui;
    QNetworkAccessManager   *m_manager  =   nullptr;
    UserDataType    m_type;
    QUrlQuery       m_query;
    QString         m_usrid;
    QString         m_grade;
    QString         m_level;
    QString         m_nick;
    QString         m_header;
    QString         m_ctime;
    QString         m_motto;

    //视频追加
    QMovie          m_movie;
    QString         m_cover;
    QString         m_vtheme;
    QString         m_intro;
    QString         m_videourl;
    QString         m_playcount;
    QString         m_likecount;

signals:
    void    sig_item_click();

};

#endif // USERDATAITEM_H
