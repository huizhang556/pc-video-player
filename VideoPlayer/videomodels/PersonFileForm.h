#ifndef PERSONFILEFORM_H
#define PERSONFILEFORM_H

#define DISITEMSIZE QSize(200,155)

#include "database/dataBase.h"
#include "videomodels/MultipPlayer.h"
#include "creator/mywork/MediaGroup.h"
#include "creator/producer/FilesItem.h"

#include <QWidget>
#include <QUrlQuery>
#include <QTabWidget>
#include <QListWidget>
#include <QButtonGroup>
#include <QStackedWidget>
#include <QDebug>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace Ui {
class PersonFileForm;
}

class PersonFileForm : public QWidget
{
    Q_OBJECT

public:
    explicit PersonFileForm(QWidget *parent = nullptr);
    ~PersonFileForm();
    void initWorkUI();
    void chandleSignalsAndSLots();

    QStackedWidget* getgetCurrentShowWidget_SW();
    QListWidget*    getCurrentShowWidget_LW();
    QTabWidget*     getCurrentShowWidget_TW();

public slots:
    void    slot_showOtherUserInfo(const QString& userid);
    void    slot_setUserFansStatus(const QString& user_id,const QString& follow_id);
    //处理各个界面  重载
    void    slot_setShowCurrentWidget(QObject *obj1,int index1, QObject *obj2,int index2);
    void    slot_setShowCurrentWidget(QObject *obj1,QWidget *wdgt1, QObject *obj2,QWidget *wdgt2);

    void    slot_get_user_produces();//获取所有作品
    void    slot_get_user_albums();//获取所有专辑
    void    slot_get_user_groups();//获取所有合集
    void    slot_get_user_activities();//获取所有动态
    void    slot_get_user_return();//返回标志

    void    slot_loading_produces(QList<QVariant>& produces);//加载所有作品
    void    slot_loading_albums(GROUPTYPE TYPE, const QString& name, const QString& pix_url, const QString &album_id);//加载所有专辑
    void    slot_loading_album_items(QList<QVariant>& albums);//加载某个专辑下的所有items
    void    slot_loading_collections(GROUPTYPE TYPE, const QString& name, const QString& pix_url, const QString &group_id);//加载所有合集
    void    slot_loading_collection_items(QList<QVariant>& collections);//加载某个合集下的所有items
    void    slot_loading_activities(QList<QVariant>& medias);//加载所有动态

private slots:
    void    slot_receivedUserHeader(QNetworkReply* reply);
    void    slot_load_watches_counts(const QString &userid);//更新关注数量
    void    slot_load_fans_counts(const QString &userid);//更新粉丝数量
    void    slot_load_upvote_counts(const QString &userid);//更新收藏数量

private:
    void        setBlankMessage(QWidget* page, const QString& message);
    void        setOtherUser_grade(const int grade);
    QCheckBox*  getItemCheckedButton(QListWidgetItem* item, const QString& objname);//获取QCheckBox
    FilesItem*  getItemWidget(QListWidgetItem* item, const QString& objname);//获取FilesItem

private:
    Ui::PersonFileForm *ui;
    QString     m_userId = "0000000000";
    QNetworkAccessManager   *m_manager  =   nullptr;

    QButtonGroup    *m_stackBtnGroup    =   nullptr;

signals:
    void    sig_sendReturnPage(int);
};

#endif // PERSONFILEFORM_H
