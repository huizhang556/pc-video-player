#ifndef LISTMANAGER_H
#define LISTMANAGER_H

#include "NewListItem.h"
#include <QEvent>
#include <QLayout>
#include <QLayoutItem>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QScrollBar>
#include <QWidget>
#include <QList>
#include <QMap>
#include <QVector>
#include <QDebug>

namespace Ui {
class ListManager;
}

class ListManager : public QWidget
{
    Q_OBJECT

public:
    explicit ListManager(QWidget *parent = nullptr);
    ~ListManager();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::ListManager *ui;
    bool                m_expand;//是否为展开状态
    int                 m_counts = 0;
    QList<NewListItem*> m_listItems;
//    QScrollBar          *m_verScrollbar     =   nullptr;
    NewListItem         *m_curListItem      =   nullptr;

    QFrame              *m_findFrame        =   nullptr;//find and close
    QLineEdit           *m_searchEdit       =   nullptr;
    QPushButton         *m_hideButton       =   nullptr;
    QHBoxLayout         *m_hblayout         =   nullptr;

    QFrame              *m_posFrame         =   nullptr;//find and location
    QPushButton         *m_findButton       =   nullptr;
    QPushButton         *m_locateButton     =   nullptr;
    QVBoxLayout         *m_vblayout         =   nullptr;

private:
    int     calSpaceExpandHeight();//计算剩余高度
    void    createNewSongList(FINSTATUS status, QString sname);
    void    findContentTextItems(QString name);
    void    hideAllItemWidgets(NewListItem* myself);
    void    showAllItemWidgets(NewListItem* myself);
    void    setItemWidgetCloseStatus(NewListItem* myself);
    void    updateScrollbarGeomotry();
     void   autoResizeGeometry();

signals:
    void    sig_send_height(int);
    void    sig_play_newPlayist(int,QStringList,QString);
};

#endif // LISTMANAGER_H
