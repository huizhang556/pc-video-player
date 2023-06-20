#ifndef SHORTVIDEO_H
#define SHORTVIDEO_H

#include "global/Global.h"
#include "database/dataBase.h"
#include "fileshandle/DownloadType.h"
#include "videomodels/RecVideoItem.h"
#include "videomodels/RecomVideoTab.h" //引入结构体
#include <QListWidgetItem>
#include <QScrollBar>
#include <QWidget>
#include <QTimer>
#include <QMovie>
#include <QVariant>
#include <QUrlQuery>
#include <QStringList>
#include <QDebug>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace Ui {
class ShortVideo;
}

class ShortVideo : public QWidget
{
    Q_OBJECT

public:
    explicit ShortVideo(QWidget *parent = nullptr);
    ~ShortVideo();
    void            initWorkUI();
    void            handleSignalsAndSLots();

public  slots:
    void    slot_addSelectTypeToList(const QStringList& typelist);
    bool    slot_addShortVideoItem(QVariant& musicVariant);//通过结构体传递信息
    bool    slot_addShortVideoItem(QString url, QString path, QString time, QString info, QString count);//添加item
    void    slot_setCurThemeCounts(int num);
    void    slot_setVideoMediaType(const QStringList& list);
    void    slot_setCurMediaHeader(const QString& headpic);
    void    slot_setCurMediaUsrName(const QString &usrname);
    void    slot_setCurUserFansStatus(const QString& user_id,const QString& follow_id);//设置粉丝关注情况
    void    slot_setCurMediaColStatus(const QString& user_id, const int media_id);//设置视频收藏状态

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    QPushButton*    getListWidgetItemButton(QListWidgetItem* item, QString objname);//在item中查找指定按钮
    void            setContentTips(const QString& tips);


private slots:
    void    slot_receivedUserHeader(QNetworkReply* reply);


private:
    Ui::ShortVideo *ui;
    QNetworkAccessManager   *m_manager  =   nullptr;
    QStringList videoTypeList;//视频类型
    int         m_curMediaId = 1;
    QString     m_curMediaName;
    QString     m_curMediaUrl;
    QString     m_curUserName;
    QString     m_curUserId;
    QString     m_curTheme;
    int         m_startpos = 0;//请求起始位置

signals:
    void    sig_sendToMainPlayer(int,const QStringList&,const QUrlQuery&);
    void    sig_sendTheme(const QString&,int,int);//主题 + 请求起始位置 +请求多少条记录
    void    sig_sendToUserInfo(const QString&);//传递过去userid

};

#endif // SHORTVIDEO_H
