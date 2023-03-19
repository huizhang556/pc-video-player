#ifndef DONEWORKS_H
#define DONEWORKS_H

//不要定义同名的宏
#define DITEMSIZE QSize(212,170)

#include "database/dataBase.h"
#include "creator/mywork/LabLoading.h"
#include "creator/mywork/LeftItem.h"
#include "creator/producer/FilesItem.h"
#include "videomodels/MultipPlayer.h"
#include <QSize>
#include <QLabel>
#include <QWidget>
#include <QVariant>
#include <QScrollBar>
#include <QListWidget>
#include <QListWidgetItem>
#include <QDebug>

namespace Ui {
class DoneWorks;
}

class DoneWorks : public QWidget
{
    Q_OBJECT

public:
    explicit DoneWorks(QWidget *parent = nullptr);
    ~DoneWorks();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();

public slots:
    void    slot_receivedData_findTypeResult(QVariant &media);
    void    slot_addItemToList(const QString text,const QVariant& data, int counts);
    void    slot_insertItemToList(int index, QString& text,const  QVariant& data, int counts);

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    QListWidget*    getConnectListWidget(const QString& type);
    void            checkListItemsCounts(QListWidgetItem *item, int allcounts);
    QLabel*         getCurrentItem(QListWidgetItem *item, const QString &objname);
    LabLoading*     getProgresslable(QListWidgetItem *item, const QString &objname);
    void            showErrorPageMessage(QWidget* page, const QString& message);
    void            setUserTagsWorkCounts(QStringList& list_counts);//查询各个标签视频数量

private:
    Ui::DoneWorks *ui;
    int             m_items = 0;
    QListWidgetItem *m_curItem  =   nullptr;//当前选中的item

    QStringList m_producelist =
    {
        QString(u8"电影"),
        QString(u8"网络剧"),
        QString(u8"短视频"),
        QString(u8"中视频"),
        QString(u8"音乐"),
        QString(u8"图片")
    };

    QStringList m_datalist =
    {
        QString(u8"movies"),
        QString(u8"netdrama"),
        QString(u8"shortvideos"),
        QString(u8"midvideos"),
        QString(u8"musics"),
        QString(u8"pictures")
    };

    QStringList mediaList = {};

signals:

};

#endif // DONEWORKS_H
