#ifndef HEADLABEL_H
#define HEADLABEL_H
#include <QStyle>
#include <QEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QPixmap>
#include <QDebug>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace Ui {
class HeadLabel;
}

class HeadLabel : public QLabel
{
    Q_OBJECT

public:
    explicit HeadLabel(QWidget *parent = nullptr);
    explicit HeadLabel(const QString& url,const bool on_del,const bool on_checked, QWidget *parent = nullptr);
    explicit HeadLabel(const QPixmap& pix,const bool on_del,const bool on_checked, QWidget *parent = nullptr);
    ~HeadLabel();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setDeleteOn();
    void    setCheckedOn();

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::HeadLabel *ui;
    QPixmap m_pix;
    bool    m_del;
    bool    m_checked;
    QString m_url;
    QNetworkAccessManager   *m_manager = nullptr;

private slots:
    void    slot_setUserHeaderPix(QNetworkReply *reply);

signals:
    void    sig_item_pix(QPixmap&);
    void    sig_item_delete();


};

#endif // HEADLABEL_H
