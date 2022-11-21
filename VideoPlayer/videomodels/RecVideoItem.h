#ifndef RECVIDEOITEM_H
#define RECVIDEOITEM_H

#include <QWidget>
#include <QPixmap>
#include <QNetworkReply>
#include <QNetworkAccessManager>

namespace Ui {
class RecVideoItem;
}

class RecVideoItem : public QWidget
{
    Q_OBJECT

public:
    explicit RecVideoItem(QWidget *parent = nullptr);
    explicit RecVideoItem(const QString& url,const QString& path, const QString time, QString info, QString count, QWidget *parent = nullptr);
    ~RecVideoItem();
    void    handleSignalsAndSlots();
    void    setVideoPicture(const QString path);//设置图片
    void    setItemPicture(const QString path);
    void    setVideoTime(const QString &time);//设置时长
    void    setVideoText(QString info);//视频介绍
    void    setVideoUpvoye(const QString &count);//点赞数

public slots:
    void    slot_replyFinished(QNetworkReply *reply);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::RecVideoItem *ui;
    QString     m_videoUrl;
    QString     m_picPath;
    QString     m_picTime;
    QString     m_picInfo;
    QString     m_picCount;
    QNetworkAccessManager   *manager;
    QNetworkReply           *reply;

signals:
    void    sig_sendVideoUrl(QString);
};

#endif // RECVIDEOITEM_H
