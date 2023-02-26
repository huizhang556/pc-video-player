#ifndef NEWLISTITEM_H
#define NEWLISTITEM_H
#include "songListItem.h"
#include <QWidget>
#include <QEvent>
#include <QMenu>
#include <QAction>
#include <QScrollBar>
#include <QListWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QDebug>


enum FINSTATUS
{
    STA_FINISHED,
    STA_UNFINISHED
};

namespace Ui {
class NewListItem;
}

class NewListItem : public QWidget
{
    Q_OBJECT

public:
    explicit NewListItem(QWidget *parent = nullptr);
    explicit NewListItem(FINSTATUS type,const int id, const QString& name, QWidget *parent = nullptr);
    ~NewListItem();
    void            initWorkUI();
    void            handleSignalsAndSlots();
    void            setInstallEventFilter();
    int             getItemId()const;
    void            setItemId(int id);
    QString         getItemName()const;
    QListWidget*    getCurListWidget();

public  slots:
    void    setListFold();//接收外部展开/折叠控制信号
    void    slot_setNodeCounts(int num);
    void    slot_finishedRename();//命名完成

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::NewListItem *ui;
    FINSTATUS   m_status;
    int         m_selfHeight;//父容器高度
    int         m_id;//item 自身 ID
    QString     m_name;//item 列表名称
    bool        m_switch        =   true;//default switch is open.
    QMenu       *m_rMenu        =   nullptr;//右键菜单

private:
    void    createRightMenu();
    void    setFinishedStatus();//设置完成状态

private slots:
    void    checkListCounts();
    bool    getFoldStatus();

    void    slot_menu_newList();
    void    slot_menu_deleteList();
    void    slot_menu_clearList();
    void    slot_menu_renameList();


signals:
    void    sig_item_expand(bool);//开关状态带出去
    void    sig_item_create();
    void    sig_item_delete();
    void    sig_item_clear();
    void    sig_item_rename();
    void    sig_item_scrollbar(int);
    void    sig_item_addtolist();
};

#endif // NEWLISTITEM_H
