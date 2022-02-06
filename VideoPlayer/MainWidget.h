#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#define MARGIN 3 //窗口边距

#include "login/Login.h"
#include "titleBar/TitleBar.h"
#include "slidebar/LeftSideBar.h"
#include "customer/CusTabWidget.h"
#include "browser/CusWebBrowser.h"
#include "messagebox/ExitDialog.h"
#include "login/LoginPersonInfo.h"
#include "videomodels/VideoBlank.h"
#include "videomodels/HolisticVideos.h"
#include "musicmodels/MusicPlaylist.h"
#include "musicmodels/MusicPlayShow.h"
#include "videomodels/VideoTitleBar.h"

#include <QPoint>
#include <QLayout>
#include <QWidget>
#include <QShowEvent>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QApplication>
#include <QStackedWidget>
#include <QSystemTrayIcon>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();



protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void changeEvent(QEvent *event) override;

    void showEvent(QShowEvent *event) override;

    void closeEvent(QCloseEvent *event) override;//重写关闭事件

private:
    void initOtherWidgetUi();

    void chandleSignalAndSlots();

    void loadAllUIQss();//加载UI样式文件

    void setStackedWidgetPage();

    void createTrayMenu();//托盘菜单

    void setGlobalToolTip();

private slots:
    void chandleRestoreWindow();

    void set_adjustLogin();

    void createHelpMenu();//帮助菜单


    //界面拉伸私有成员函数
    int   countRow(QPoint p);             //获取光标在窗口所在区域的 行   返回行数
    int   countFlag(QPoint p,int row);    //获取光标在窗口所在区域的 列  返回行列坐标
    void  setCursorType(int flag);        //根据传入的坐标，设置光标样式
private:
    QStackedWidget      *m_stackWidget  = nullptr;
    QVBoxLayout         *m_vblayout     = nullptr;
    QHBoxLayout         *m_hblayout     = nullptr;
    ExitDialog          *m_pExitDlg     = nullptr;
    TitleBar            *m_titleBar     = nullptr;
    Login               *m_login        = nullptr;
    MainWindow          *m_mainWin      = nullptr;
    LeftSideBar         *m_leftSideBar  = nullptr;
    MusicPlaylist       *m_musicList    = nullptr;
    MusicPlayShow       *m_musicShow    = nullptr;
    CusTabWidget        *m_tabWidget    = nullptr;
    VideoBlank          *m_videoWidget  = nullptr;
    CusWebBrowser       *m_webBrowser   = nullptr;
    VideoTitleBar       *m_videoTitle   = nullptr;
    QSystemTrayIcon     *m_tray         = nullptr;
    bool                 m_winMax;        //默认非最大化
    bool                 m_isClose;

    //界面拉伸所用
    bool     _isleftpressed = false;      //判断是否是左键点击
    int      _curpos = 0;                 //鼠标左键按下时光标所在区域
    QPoint   _plast;                      //获取鼠标左键按下时光标在全局(屏幕而非窗口)的位置

signals:
    void sig_winStatus(bool);
    void sig_startCloseAppliction();//主窗口关闭信号
};

#endif // MAINWIDGET_H
