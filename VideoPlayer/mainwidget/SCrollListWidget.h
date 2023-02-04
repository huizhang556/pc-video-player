#ifndef SCROLLLISTWIDGET_H
#define SCROLLLISTWIDGET_H
#define ITEMSACLE   666/1910
#define ITEMWIDTH 100
#include "global/Global.h"
#include "mainwidget/CusLabel1.h"
#include <QLabel>
#include <QWidget>
#include <QScrollBar>
#include <QListWidgetItem>
#include <QStackedWidget>
#include <QPropertyAnimation>
#include <QDebug>


namespace Ui {
class SCrollListWidget;
}

class SCrollListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SCrollListWidget(QWidget *parent = nullptr);
    ~SCrollListWidget();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:
    void    slot_addItemToList(const QString& picpath);
    void    slot_addItemsToList(const QStringList & list_pic);
    void    slot_update_RL_ITEM_geometry(const QSize &size);

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::SCrollListWidget *ui;
    int m_currentIndex = 0;

private:
    void        autoResizeListItems();
    void        setButtons_LR_Geometry();
    int         calAvgWidth();
    QWidget*    getMaskWidget(QListWidgetItem *item, const QString& objname);

signals:
    void    sig_sendCurIndex(int);

};

#endif // SCROLLLISTWIDGET_H
