#ifndef MUSICPLAYLIST_H
#define MUSICPLAYLIST_H

#include "SongItemForm.h"
#include "delegate/Delegate.h"
#include <QMenu>
#include <QWidget>
#include <QAction>
#include <QSqlTableModel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QListWidgetItem>

namespace Ui {
class MusicPlaylist;
}

class MusicPlaylist : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlaylist(QWidget *parent = nullptr);
    ~MusicPlaylist();
    void    sortCurrentIndex(int index);
    QString addPrefixNum(QString num);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

public slots:
    bool playerListIsNull();//判断播放列表是否为空

    void addFileInfoToListView();//从数据库加载歌曲数据

    void selectTableAboutSongName(QString name);

    void slots_rightMenu_player();

    void slots_rightMenu_delete();

    void slots_rightMenu_download();

    void slots_rightMenu_clearAllList();

    void slots_rightMenu_next();

    void slots_rightMenu_addtolist();

    void slots_rightMenu_movetolist();

    void slots_rightMenu_openFilePath();

    bool slots_addSonersToPage2(const QStringList &list);

signals:
    void hoverIndexChanged(QModelIndex);

    void sig_selectRowIndex(QModelIndex);

    void sig_containerIsNull(bool isnull);//判断列表容器是否为空

private slots:
    void on_tableView_songList_entered(const QModelIndex &index);

   void slots_selectRowIndex(const QModelIndex &index);

   void slots_btnSortCustomMenu();//歌曲排序右键功能菜单

   void slots_btnSortAscOrder();

   void slots_btnSortDescOrder();

   void slots_btnBatchToNewUi();

   void slots_btnBatchToNewUiExit();

   void slots_btnBatchModelUpdate();

   void on_tableView_songList_customContextMenuRequested(const QPoint &pos);

   void on_listWidget_songer_customContextMenuRequested(const QPoint &pos);

   void slot_listWidget_songer_Play();//播放处理

   void slot_listWidget_songer_MV();//播放MV处理

   void slot_listWidget_songer_Collect();//收藏

   void slot_listWidget_songer_Download();//下载

   void slot_listWidget_songer_Delete();//删除

   void slot_listWidget_songer_More();//更多信息

   void slot_listWidget_songer_Quality();//音质
private:
    Ui::MusicPlaylist *ui;
//    QAction         *m_songAction;
    QMenu                   *pmenu_right          = nullptr;
    QSqlTableModel          *model_songInfo       = nullptr;
    Delegate                *delegate             = nullptr;
    SongItemForm            *son_item             = nullptr;

};

#endif // MUSICPLAYLIST_H
