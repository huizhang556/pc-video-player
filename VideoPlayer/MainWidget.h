#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#define MARGIN 2 //窗口边距

#include "browser/NewWork.h"
#include "titleBar/TitleBar.h"
#include "browser/CusTabBar.h"
#include "browser/WebHistory.h"
#include "customer/SystemTray.h"
#include "slidebar/LeftSideBar.h"
#include "customer/CusTabWidget.h"
#include "browser/WebMessageBox.h"
#include "browser/CusWebBrowser.h"
#include "messagebox/ExitDialog.h"
#include "login/LoginPersonInfo.h"
#include "browser/CollectRecords.h"
#include "videomodels/VideoBlank.h"
#include "videomodels/FloatPlayCtl.h"
#include "messagebox/SystemSetting.h"
#include "videomodels/MultipPlayer.h"
#include "musicmodels/MusicPlaylist.h"
#include "musicmodels/MusicPlayShow.h"
#include "videomodels/PlayOrderForm.h"
#include "videomodels/VideoTitleBar.h"
#include "mainwidget/CentralHomeForm.h"
#include "videomodels/PersonFileForm.h"
#include <QMenu>
#include <QPoint>
#include <QLayout>
#include <QThread>
#include <QWidget>
#include <QShowEvent>
#include <QTabWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QResizeEvent>
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
    bool        eventFilter(QObject *watched, QEvent *event) override;

    void        mousePressEvent(QMouseEvent *event) override;

    void        mouseMoveEvent(QMouseEvent *event) override;

    void        mouseReleaseEvent(QMouseEvent *event) override;

    void        changeEvent(QEvent *event) override;

    void        showEvent(QShowEvent *event) override;

    void        closeEvent(QCloseEvent *event) override;

    void        resizeEvent(QResizeEvent *event) override;

private:
    void        initOtherWidgetUi();

    void        chandleSignalAndSlots();

    void        updateAddWebButtonPosition();//更新新增网页按钮的位置

    void        setStackedWidgetPage();//添加界面

    void        createTrayMenu();//托盘菜单

    void        setGlobalToolTip();


private slots:
    void        slot_setRemoveTabLineEditText(int index);//删除某个tab后，标题栏显示URL

    void        slot_switchCurrentTab_URL(int index);//转换到当前索引

    void        slot_setCurrentTabWidgetEnable();//设置可用不可用

    void        slot_judgeCurrentBrowserIsActive_home();//过滤不是当前活跃的窗口--返回主页

    void        slot_judgeCurrentBrowserIsActive_back();//返回上一级

    void        slot_judgeCurrentBrowserIsActive_freshen();//刷新

    void        slot_judgeCurrentBrowserIsActive_advance();//下一页

    void        slot_judgeCurrentBrowserIsActive_load(QString newUrl);//加载输入框地址

    void        slot_addToWebTabwidgetBrowser(QUrl &url);//重载1

    void        slot_addToWebTabwidgetBrowser(QString &url);//重载2

    void        slot_removeTabWidgetTab(int index);//删除某一个tab

    void        slot_on_leftButton_clicked();//左侧边栏点击判断

    void        setLeftButtonStyleSheetStatus();//更新左侧边栏按钮样式

    void        updateLeftButtonGeometry();//更新左侧边栏按钮位置

    void        chandleRestoreWindow();

    void        chandleSetHelpItem(int index);

    void        help_stemAboutSetting();//系统设置

    void        help_questionAnswer();//问题帮助

    void        help_openWebSite();//门户网站

    void        help_aboutLocalFile();//播放本地资源

    void        help_aboutNetworklFile();//播放网络资源

    //浏览器
    void        slot_canGoForward();
    void        slot_canGoBack();

    //托盘
    void        tray_showMainWidget();
    void        tray_showDesktopLyric();
    void        tray_systemSettting();
    void        tray_onlineUpgrade();
    void        tray_systemLogout();
    void        tray_systemExitSoftware();
    void        tray_getCurrentPlayOrder(QAction *sendAction);
    void        tray_setCurrentPlayOrderStatus(QAction *sendAction);//重载1
    void        tray_setCurrentPlayOrderStatus(int index);//重载2


    //界面拉伸私有成员函数
    int         countRow(QPoint p);             //获取光标在窗口所在区域的 行   返回行数
    int         countFlag(QPoint p,int row);    //获取光标在窗口所在区域的 列  返回行列坐标
    void        setCursorType(int flag);        //根据传入的坐标，设置光标样式

signals:
    void        sig_winStatus(bool);
    void        sig_trayPlayOrder(int order);
    void        sig_startCloseAppliction();//主窗口关闭信号
    void        sig_canGoBack(bool status);
    void        sig_canGoForward(bool status);

private:
    QStackedWidget      *m_stackWidget_center      = nullptr;//中心显示区域
    QStackedWidget      *m_stackWidget_left        = nullptr;//左侧边栏区域
    QPushButton         *m_leftButton              = nullptr;//控制显示还是隐藏的按钮
    QVBoxLayout         *m_vblayout                = nullptr;
    QHBoxLayout         *m_hblayout                = nullptr;
    ExitDialog          *m_pExitDlg                = nullptr;
    TitleBar            *m_titleBar                = nullptr;
    CentralHomeForm     *m_homeWdgt                = nullptr;
    PersonFileForm      *m_personForm              = nullptr;
    MultipPlayer        *m_mainPlayer              = nullptr;
    LeftSideBar         *m_leftSideBar             = nullptr;
    MusicPlaylist       *m_musicList               = nullptr;
    MusicPlayShow       *m_musicShow               = nullptr;
    CusTabWidget        *m_tabWidget               = nullptr;
    VideoBlank          *m_videoBlank              = nullptr;
    QTabWidget          *m_webTabWidget            = nullptr;
    QVBoxLayout         *m_webVblayout             = nullptr;
    CusTabBar           *m_cusTabbar               = nullptr;
    CusWebBrowser       *m_webBrowser              = nullptr;
    CollectRecords      *m_webRecords              = nullptr;//浏览器收藏标签界面
    WebHistory          *m_webHistory              = nullptr;//浏览器历史记录界面
    WebMessageBox       *m_webMessage              = nullptr;//浏览器标签修改界面
    QStackedWidget      *m_webStackWgt             = nullptr;//关于浏览器所有界面的管理器
    QWidget             *m_webWidget               = nullptr;
    SystemSetting       *m_systemSetting           = nullptr;
    SystemTray          *m_systemTray              = nullptr;
    QSystemTrayIcon     *m_tray                    = nullptr;
    QActionGroup        *m_actionGroup             = nullptr;
    QMenu               *m_menuTray                = nullptr;
    QMenu               *m_playMode                = nullptr;
    QMenu               *pmenu2                    = nullptr;
    QMenu               *pmenu3                    = nullptr;
    bool                 m_isHide;        //左侧显示隐藏按钮
    bool                 m_winMax;        //默认非最大化
    bool                 m_isClose;
    bool                 m_firstOpen;     //第一次打开文件
    //界面拉伸私有成员变量
    bool                _isleftpressed             = false;      //判断是否是左键点击
    int                 _curpos = 0;                             //鼠标左键按下时光标所在区域
    QPoint              _plast;                                  //获取鼠标左键按下时光标在全局(屏幕而非窗口)的位置

    //浏览器通信
    QThread             *m_workThread           = nullptr;
};

#endif // MAINWIDGET_H
