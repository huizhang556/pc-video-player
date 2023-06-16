#ifndef DONEWORKS_H
#define DONEWORKS_H

//不要定义同名的宏
#define DITEMSIZE QSize(212,170)

#include "database/dataBase.h"
#include "creator/mywork/LeftItem.h"
#include "videomodels/MultipPlayer.h"
#include "creator/mywork/LabLoading.h"
#include "creator/mywork/MediaGroup.h"
#include "creator/mywork/SortDialog.h"
#include "creator/producer/FilesItem.h"
#include <QSize>
#include <QLabel>
#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QVariant>
#include <QUrlQuery>
#include <QScrollBar>
#include <QListWidget>
#include <QUrlQuery>
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
    void            initWorkUI();
    void            handleSignalsAndSlots();
    void            setInstallEventer();
    void            clearOldContent();

public slots:
    //左侧列表部分
    void            slot_addItemToList(const QString text,const QVariant& data, int counts);//加载左侧类型列表自定义刷新item
    void            slot_insertItemToList(int index, QString& text, const  QVariant& data, int counts);//特定位置加载左侧类型列表自定义刷新item
    void            slot_receivedData_findTypeResult(QVariant& media);//加载(更新)对应类型媒体下item
    void            slot_setUserTagsWorkCounts(QStringList& list_counts);//查询各个标签视频数量
    //专辑部分
    void            slot_initUserAlbums();//查询初始化当前用户下所有专集
    void            slot_addItemToAlbumList(GROUPTYPE TYPE, const QString& name, const QString& pix_url, const QString &album_id);//添加专集
    void            slot_addItmeToAlbumIDList(QVariant& media);//添加某个专集的item

    //合集部分
    void            slot_initUserGroups();//查询初始化当前用户下所有合集
    void            slot_addItemToGroupList(GROUPTYPE TYPE, const QString& name, const QString& pix_url, const QString &group_id);//添加合集
    void            slot_addItmeToGroupIDList(QVariant& media);//添加某个合集的item

protected:
    bool            eventFilter(QObject *watched, QEvent *event)override;

private:
    QListWidget*    getConnectListWidget(const QString& type);
    void            checkListItemsCounts(QListWidgetItem *item, int allcounts);
    QLabel*         getCurrentItem(QListWidgetItem *item, const QString &objname);
    LabLoading*     getProgresslable(QListWidgetItem *item, const QString &objname);
    void            showErrorPageMessage(QWidget* page, const QString& message);
    void            createHJ_ContextMenu();

private slots:
    void            slot_createNewHJ();

private:
    Ui::DoneWorks *ui;
    int             m_items = 0;
    QListWidgetItem *m_curItem  =   nullptr;//当前选中的item

    QStringList     m_producelist =
    {
        QString(u8"电影"),
        QString(u8"网络剧"),
        QString(u8"短视频"),
        QString(u8"中视频"),
        QString(u8"音乐"),
        QString(u8"图片")
    };

    QStringList     m_datalist =
    {
        QString(u8"movies"),
        QString(u8"netdrama"),
        QString(u8"shortvideos"),
        QString(u8"midvideos"),
        QString(u8"musics"),
        QString(u8"pictures")
    };

signals:

};

#endif // DONEWORKS_H
