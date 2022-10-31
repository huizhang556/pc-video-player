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
#include "browser/CusWebBrowser.h"
#include "messagebox/ExitDialog.h"
#include "login/LoginPersonInfo.h"
#include "browser/CollectRecords.h"
#include "videomodels/VideoBlank.h"
#include "fileshandle/FilesTrans.h"
#include "videomodels/FloatPlayCtl.h"
#include "messagebox/SystemSetting.h"
#include "videomodels/MultipPlayer.h"
#include "musicmodels/MusicPlaylist.h"
#include "musicmodels/MusicPlayShow.h"
#include "videomodels/PlayOrderForm.h"
#include "videomodels/VideoTitleBar.h"
#include "videomodels/PersonFileForm.h"
#include "mainwidget/HomeWidget.h"
#include "mainwidget/videomember/MainMembForm.h"
#include "mainwidget/videosmv/MainVideoMv.h"
#include "mainwidget/songersort/SongerSort.h"
#include "mainwidget/rankinglist/RankingList.h"
#include "mainwidget/songlistsort/SonglistSort.h"
#include "mainwidget/radiohost/RadioHost.h"
#include "mainwidget/musicscene/MusicScene.h"
#include "mainwidget/vipmember/VipMember.h"
#include "mainwidget/cusvideosbox/CusVideosBox.h"
#include "mainwidget/hotsearch/HotSearchForm.h"
#include "mainwidget/cusvideosbox/CusVideoBox2.h"
#include "mainwidget/videotypeselect/VideoTypeSelect.h"


#include <QMenu>
#include <QPoint>
#include <QLayout>
#include <QThread>
#include <QWidget>
#include <QStatusBar>
#include <QShowEvent>
#include <QTabWidget>
#include <QKeyEvent>
#include <QSpacerItem>
#include <QPushButton>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QProgressBar>
#include <QApplication>
#include <QStackedWidget>
#include <QSystemTrayIcon>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

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
    bool        nativeEvent(const QByteArray& eventType, void* message, long* result) override;

    bool        eventFilter(QObject *watched, QEvent *event) override;  

    void        mousePressEvent(QMouseEvent *event) override;

    void        mouseMoveEvent(QMouseEvent *event) override;

    void        mouseReleaseEvent(QMouseEvent *event) override;

    void        changeEvent(QEvent *event) override;

    void        showEvent(QShowEvent *event) override;

    void        closeEvent(QCloseEvent *event) override;

    void        resizeEvent(QResizeEvent *event) override;

    void        keyPressEvent(QKeyEvent *event) override;

private:
    void        initOtherWidgetUi();

    void        handleSignalAndSLots();

    void        updateAddWebButtonPosition();//更新新增网页按钮的位置

    void        setStackedWidgetPage();//添加界面

    void        setLeftSliderCurrentIndex(int index);

    void        createTrayMenu();//托盘菜单

    void        setGlobalToolTip();

    void        userSignIn();

    void        userSignOut();

    void        updateWebAddButtonGeometry();//更新添加按钮位置

    void        updateWinTitleBarButtons();

private slots:
    void        slot_setWebProgreeBarValue(int value);//网页进度

    void        slot_setCurrentCenterStackWidget(int index);//设置中心区域

    void        slot_setCurrentCenterStackWidget(QString name);//设置中心区域

    void        slot_resetWebProgressBarValue();

    void        slot_setRemoveTabLineEditText(int index);//删除某个tab后，标题栏显示URL

    void        slot_switchCurrentTab_URL(int index);//转换到当前索引

    void        slot_setCurrentTabWidgetEnable();//设置可用不可用

    void        slot_setCurrentWebBarTitle(int index,const QString &title);//设置标题

    void        slot_setCurrentWebBarIcon(int index,const QIcon &icon);//设置图标

    void        slot_judgeCurrentBrowserIsActive_home();//过滤不是当前活跃的窗口--返回主页

    QIcon       slot_getCurrentBrowserIcon();//获取当前web图标

    QString     slot_getCurrentBrowserTitle();//获取当前web标题

    void        slot_judgeCurrentBrowserIsActive_back();//返回上一级

    void        slot_judgeCurrentBrowserIsActive_freshen();//刷新

    void        slot_judgeCurrentBrowserIsActive_advance();//下一页

    void        slot_webbrowserShowFullscreen();//全屏显示

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
    void        slot_showLinkOnStatusBar(const QString &text);

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
    bool        tray_setUserLoginStatusText(const QString& previous, const QString& current);//设置用户登录状态

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
    void        sig_createNewWebTab();//创建新的tab
    void        sig_globalResize();
    void        sig_sendWindowResize();

private:
    QGraphicsOpacityEffect *opacity                = nullptr;
    QStackedWidget      *m_stackWidget_center      = nullptr;//中心显示区域
    QStackedWidget      *m_stackWidget_left        = nullptr;//左侧边栏区域
    QPushButton         *m_leftButton              = nullptr;//控制显示还是隐藏的按钮
    QVBoxLayout         *m_vblayout                = nullptr;//标题栏+center
    QVBoxLayout         *m_vblayout_center         = nullptr;//选择按钮+center
    QHBoxLayout         *m_hblayout                = nullptr;//侧边栏+center
    ExitDialog          *m_pExitDlg                = nullptr;
    TitleBar            *m_titleBar                = nullptr;
    HomeWidget          *m_homeWidget              = nullptr;//首页推荐
    VideoMv             *m_mainVideoMv             = nullptr;//视频
    MainMembForm        *m_videoMember             = nullptr;//会员视频
    HotSearchForm       *m_hotSearch               = nullptr;//热搜
    SongerSort          *m_songerSort              = nullptr;//歌手排行
    RankingList         *m_rankList                = nullptr;//排行榜
    SonglistSort        *m_songlistSort            = nullptr;//歌单分类
    RadioHost           *m_radioHost               = nullptr;//主播电台
    MusicScene          *m_musicScene              = nullptr;//音乐现场
    VipMember           *m_vipMember               = nullptr;//会员专区
    CusVideosBox        *m_cusVideoBox             = nullptr;//视频盒子
    CusVideoBox2        *m_cusVideoBox2            = nullptr;//视频盒子
    VideoTypeSelect     *videoFindResult           = nullptr;//视频筛选结果
    PersonFileForm      *m_personForm              = nullptr;
    MultipPlayer        *m_mainPlayer              = nullptr;
    LeftSideBar         *m_leftSideBar             = nullptr;
    MusicPlaylist       *m_musicList               = nullptr;
    MusicPlayShow       *m_musicShow               = nullptr;
    FilesTrans          *m_fileTrans               = nullptr;//文件传输界面
    CusTabWidget        *m_tabWidget               = nullptr;
    VideoBlank          *m_videoBlank              = nullptr;
    QTabWidget          *m_webTabWidget            = nullptr;
    QVBoxLayout         *m_webVblayout             = nullptr;
    CusTabBar           *m_cusTabbar               = nullptr;//自定义tabbar标题栏(收藏栏)
    CusWebBrowser       *m_webBrowser              = nullptr;//自定义浏览器
    QPushButton         *m_webAddBtn               = nullptr;//添加按钮
    QSpacerItem         *sparcer_item              = nullptr;
    QWidget             *m_addWidget               = nullptr;//添加tab网页栏
    QHBoxLayout         *m_addHblayout             = nullptr;
    QStatusBar          *m_statusBar               = nullptr;//浏览器状态栏
    QProgressBar        *m_progressBar             = nullptr;//浏览器网页加载进度
    CollectRecords      *m_webRecords              = nullptr;//浏览器收藏标签界面
    WebHistory          *m_webHistory              = nullptr;//浏览器历史记录界面
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
};

#endif // MAINWIDGET_H
