#ifndef CRETITLEBAR_H
#define CRETITLEBAR_H

#include <QWidget>
#include <QPixmap>
#include <QRegion>
#include <QMouseEvent>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QDebug>

namespace Ui {
class CreTitleBar;
}

class CreTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit CreTitleBar(QWidget *parent = nullptr);
    ~CreTitleBar();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();
    void    setUserIcon(bool online,const QString& header);

protected:
//    void    mousePressEvent(QMouseEvent *event)override;
    bool    eventFilter(QObject *watched, QEvent *event)override;

public slots:
    void    slot_replyFinished(QNetworkReply *reply);

private:
    Ui::CreTitleBar *ui;
    bool    m_winMax = false;//默认非最大化
    QNetworkAccessManager   *manager;
    QNetworkReply           *reply;

signals:
    void    sig_win_close();
    void    sig_win_min();
    void    sig_win_restore(bool);
};

#endif // CRETITLEBAR_H
