/**************************
 * 功能：轮播图+可随机选择视图（小轮播图）
 *
 *
 * ***********************/

#ifndef ANISTACKWIDGET_H
#define ANISTACKWIDGET_H

#define SACLWIDTH   1200 //开始放大最小宽度1200
#define FIXEDHEIGHT 360  //小于放大宽度设置为固定高 360
#define SCALSIZE    0.28 //放大时 高/宽 比例
#define MINWINSIZE  QSize(830,FIXEDHEIGHT)  //界面最小size
#define RESIZESIZE  QSize(1160,360)     //默认加载是size（一般会被重置）
#define SRLISTSIZE  QSize(600,180)
#define RDEFSIZE    QSize(260,320)
#define RSACLE_H  0.88  //放大时 右侧列表高占整体高 比例
#define RSACLE_W  0.18  //放大时 右侧列表宽占整体宽 比例

#define ITEMMARGIN  QSize(0,0)

#include "global/Global.h"
#include "mainwidget/SCrollListWidget.h"
#include <QEvent>
#include <QLabel>
#include <QWidget>
#include <QStackedWidget>
#include <QDebug>

class AniStackWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit AniStackWidget(QWidget *parent = nullptr);
    ~AniStackWidget();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();


public slots:
    void    slot_addItemToCusVerStackWgt(const QString& picpath);
    void    slot_addItemToSmallList(const QString& picpath);

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    void    updateSelectedItemStyle();
    void    update_W_H_scale();
    void    autoResize_ScroListWidget_Geometry();

private:
    SCrollListWidget    *m_scroListWidget   =   nullptr;
    int     m_curIndex = 0;//当前page索引
signals:


};

#endif // ANISTACKWIDGET_H
