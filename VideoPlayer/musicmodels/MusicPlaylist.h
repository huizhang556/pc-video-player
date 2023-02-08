#ifndef MUSICPLAYLIST_H
#define MUSICPLAYLIST_H
#define ITEMSIZE QSize(1000,40)
#include "SongItemForm.h"
#include "delegate/Delegate.h"
#include <QMenu>
#include <QWidget>
#include <QAction>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSqlTableModel>
#include <QListWidgetItem>

//自定义属性：
//Q_PROPERTY(type name READ getFunction [WRITE setFunction] [RESET resetFunction] [NOTIFY notifySignal] [DESIGNABLE bool] [SCRIPTABLE bool] [STORED bool] [USER bool] [CONSTANT] [FINAL])

//type 类型
//name 自定义属性名字
//READ 读取实现函数
//WRITE 写入实现函数
//RESET 复位函数，把设置还原5
//NOTIFY （参数改变时）发送信号
//STODE 一直存在的
//DESIGNABLE designer用（或者designer里设置也可以）
//USER 是否可以被用户编辑
//CONST 是否可以修改（不能修改的话，WRITE 就不能有）
//FINAL 不能被重写


namespace Ui {
class MusicPlaylist;
}

class MusicPlaylist : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlaylist(QWidget *parent = nullptr);
    ~MusicPlaylist();
    void            initWorkUI();
    void            handleSignalsAndSlots();
    void            setInstallEventFilter();
    void            sortCurrentIndex(int index);
    QString         addPrefixNum(QString num);
//    QWidget*        makeSongInfoItem();

protected:
    bool            eventFilter(QObject *watched, QEvent *event) override;

public slots:
    bool            playerListIsNull();//判断播放列表是否为空

    void            addFileInfoToListView();//从数据库加载歌曲数据

    void            selectTableAboutSongName(QString name);

    void            slots_rightMenu_player();

    void            slots_rightMenu_delete();

    void            slots_rightMenu_download();

    void            slots_rightMenu_clearAllList();

    void            slots_rightMenu_next();

    void            slots_rightMenu_addtolist();

    void            slots_rightMenu_movetolist();

    void            slots_rightMenu_openFilePath();

    bool            slots_addSonersToPage2(const QStringList &list);


private slots:
   void             on_tableView_songList_entered(const QModelIndex &index);

   void             slots_selectRowIndex(const QModelIndex &index);

   void             slots_btnSortCustomMenu();//歌曲排序右键功能菜单

   void             slots_btnSortAscOrder();

   void             slots_btnSortDescOrder();

   void             slots_btnBatchToNewUi();

   void             slots_btnBatchToNewUiExit();

   void             slots_btnBatchModelUpdate();

   void             on_tableView_songList_customContextMenuRequested(const QPoint &pos);

   void             on_listWidget_songer_customContextMenuRequested(const QPoint &pos);

   void             slot_listWidget_songer_Play();//播放处理

   void             slot_listWidget_songer_MV();//播放MV处理

   void             slot_listWidget_songer_Collect();//收藏

   void             slot_listWidget_songer_Download();//下载

   void             slot_listWidget_songer_Delete(QListWidget *listWgt, QWidget *itemWgt, QListWidgetItem *item);//删除

   void             slot_listWidget_songer_sort(QListWidget *listWgt);//删除后排序

   void             slot_listWidget_songer_More();//更多信息

   void             slot_listWidget_songer_Quality();//音质

   void             slot_updateSongerAllCounts();//更新歌曲总数

private:
    Ui::MusicPlaylist *ui;
//    QAction       *m_songAction;
    QMenu           *pmenu_right          = nullptr;
    QSqlTableModel  *model_songInfo       = nullptr;
    Delegate        *delegate             = nullptr;

private:
    QPushButton*    getItem_Button(QListWidgetItem *item,const QString& objname);
    QLabel*         getItem_Label(QListWidgetItem *item,const QString& objname);
    QCheckBox*      getItem_CheckBox(QListWidgetItem *item,const QString& objname);
    void            setToolButtonTextAndIcon(const QAction *action);
    void            autoResizeList_songer();

signals:
    void            hoverIndexChanged(QModelIndex);

    void            sig_selectRowIndex(QModelIndex);

    void            sig_containerIsNull(bool isnull);//判断列表容器是否为空

    void            sig_updateCounts();//更新总数
};

#endif // MUSICPLAYLIST_H
