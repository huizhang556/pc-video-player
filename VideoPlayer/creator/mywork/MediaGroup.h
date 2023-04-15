#ifndef MEDIAGROUP_H
#define MEDIAGROUP_H
#include "creator/producer/UploadWork.h"
#include "creator/mywork/SortDialog.h"
#include <QWidget>
#include <QEvent>
#include <QImage>
#include <QThread>
#include <QFileDialog>
#include <QMouseEvent>
#include <QTimer>
#include <QDebug>

#include <QBuffer>
#include <QPixmap>
#include <QByteArray>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

//ITEM类型
enum   GROUPTYPE
{
    G_NORMAL,
    G_CUSTOM
};

namespace Ui {
class MediaGroup;
}

class MediaGroup : public QWidget
{
    Q_OBJECT

public:
    explicit MediaGroup(QWidget *parent = nullptr);
    explicit MediaGroup(GROUPTYPE type, const QString& g_id, const QString& g_name, const QString& g_cover_url, QWidget *parent = nullptr);
    ~MediaGroup();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:


protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::MediaGroup *ui;
    GROUPTYPE   m_type;
    QString     m_name;
    QString     m_pix_url;
    QString     m_groupid;
    QImage      m_cover;
    QNetworkAccessManager   *m_manager;

private:
    void    setItemCover();
    void    setItemType();

private slots:
    void    slot_receiveGroupCover(QNetworkReply* reply);
    bool    slot_uploadUserGroupCover(const QByteArray &pic_bytedata);//更新封面

signals:
    void    sig_item_clicked();
    void    sig_item_additem();
    void    sig_item_delete();
    void    sig_item_rename(const QString);//新的名称
    void    sig_item_newCover(const QString&,const QString&);
};

#endif // MEDIAGROUP_H
