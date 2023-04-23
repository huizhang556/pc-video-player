#ifndef ADVTERITEM_H
#define ADVTERITEM_H

#include <QWidget>
#include <QTimer>
#include <QDebug>

#include <QNetworkReply>
#include <QNetworkAccessManager>

enum    ADVTYPE
{
    ADV_CONTINUE,
    ADV_NOCONTINUE
};

namespace Ui {
class AdvterItem;
}

class AdvterItem : public QWidget
{
    Q_OBJECT

public:
    explicit AdvterItem(QWidget *parent = nullptr);
    explicit AdvterItem(ADVTYPE type, const QString& url, const QString& cover, const QString& duration, const QString& intro, const QString &like, QWidget *parent = nullptr);
    ~AdvterItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();

    void    setItem_type();
    void    setItem_cover();
    void    setItemIntro();
    void    setItem_duration();
    void    setItemLike();

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private slots:
    void    slot_receiveMediaCover(QNetworkReply *reply);

private:
    Ui::AdvterItem *ui;
    ADVTYPE     m_type;
    QString     m_url;
    QString     m_cover;
    QString     m_intro;
    QString     m_like;
    QString     m_duration;
    bool        m_clicked = false;
    QTimer      *m_timer    = nullptr;
    int         time = 6;
    QNetworkAccessManager   *m_manager = nullptr;

signals:
    void    sig_item_cancelplay(QString);//取消连播
    void    sig_item_continue(QString);//继续连播
};

#endif // ADVTERITEM_H
