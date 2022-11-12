#ifndef TITLEBAR_H
#define TITLEBAR_H
#include "login/Login.h"
#include "skin/MySkin.h"
#include "titlebar/HeadHover.h"
#include "messagebox/SearchForm.h"
#include "login/LoginPersonInfo.h"
#include "login/NewLoginForm.h"
#include "login/LoginTip.h"
#include "browser/WebDownLoadList.h"
#include "customer/CusLineEdit.h"
#include "titlebar/WatchRecords.h"
#include "desktoplyric/toptooltips/DesktopTip1.h"

#include <QMenu>
#include <QPoint>
#include <QTimer>
#include <QMenu>
#include <QWidget>
#include <QPixmap>
#include <QLibrary>
#include <QLineEdit>
#include <QHostInfo>
#include <QPushButton>
#include <QMouseEvent>
#include <QSoundEffect>
#include <QWidgetAction>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QNetworkConfigurationManager>//网络配置管理类

typedef bool(*ConnectFun)(int* lpdwFlags, int  dwReserved);

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();
    void    initWorker();
    void    handleSignalAndSLots();
    void    setWebDefUrl(const QString& title);

protected:
    void    showEvent(QShowEvent *event) override;
    void    keyPressEvent(QKeyEvent *event) override;
    void    mousePressEvent(QMouseEvent *event) override;
    void    mouseDoubleClickEvent(QMouseEvent *event) override;
    bool    eventFilter(QObject *watched, QEvent *event) override;

//公有槽函数以公共接口的形式暴露在外面，外部任何客户可以直接访问
public slots:
    void    isNecessaryShowSearch(int index);
    void    receiveMainFormClose();
    void    slot_callLoginTipsShow(QObject *watched, QEvent *event);//登录提示界面
    void    slot_callWatchRecordShow(QObject *watched, QEvent *event);//观看历史提示界面
    void    slot_showUserInfoWgt(QObject *watched, QEvent *event);//显示用户信息
    void    mouseIsEnterLeaveLineEdit(QObject *watched, QEvent *event);
    void    setSelectAllTextStatus(QObject *watched, QEvent *event);//lineEdit按下
    void    mouseIsPressReleaseLineEdit(QObject *watched, QEvent *event);//搜索框点击事件
//    void    serarchLineEditFacous(QObject *watched, QEvent *event);
    void    slot_switchToLoginPage(int mark,QString nick);//登录设置名称
    void    slot_setCurrentUserGrade(int grade);//设置当前用户等级
    void    slot_setButtonHelpEmitItem();
    void    slot_receivedListItemText(QString text);
    void    slot_setWebLineEditCurentUrl(QUrl url);//设置当前url
    void    slot_clearWebLineEditText();//清除weblineedit文字
    void    slot_setWebProgressBarValue(int value);//网页加载时，显示加载进度
    void    slot_receiveBlankWebTab();//接收tabbar添加一个空白网页的请求
    void    slot_clearAllPopupUi();
    void    slot_initCollectRecordListWgt(const QString &text);//初始化
    void    slot_clearColletRecords();
    void    slot_showPersonLogin();
    void    showLoginForm();
    //接收登录界面信号
    void    slot_receivedLoginInfo(const QString& name,const QString& head,int grade);
    void    slot_receivedSign_out();//退出登录

//私有槽函数，外部不能直接访问
private slots:
    void    onLookupHost(QHostInfo host);
    void    chandleMainWinStatus(bool status);
    void    getSystemTimeShow();//更新时间
    void    checkCurrentNetworkStatus_method0();//首次初始化网络状态
    void    checkCurrentNetworkStatus_method1();//检查当前网络状态 方法1
    void    checkCurrentNetworkStatus_method2();//检查当前网络状态 方法2（不好使，检测结果比较慢，不及时）
    void    setLineEditAddress(const QUrl url);
    void    showMySkin();//皮肤设置
    void    createHelpMenu();//帮助菜单
    QString judgeUrlType(QString url);
    bool    judgeCollectUrlType(QString url);//判断要收藏的url是否有效类型
    bool    judgeCollectUrlExist(const QString &url);//判断当前的网址是否已经在收藏栏

    bool    judgeHistorytUrlType(QString url);//判断要收藏的url是否有效类型
    bool    judgeHistoryUrlExist(const QString &url);//判断当前的网址是否已经在收藏栏
    void    slot_setCurrentWebSiteCollectStatus(const QString &url);//判断当前的网址是显示收藏还是未收藏
    void    slot_addToListCollectWidget(const QString &text);//添加一条
    void    slot_deleteListCollectWidget(const QString &url);//删除一条
    void    slot_updateShowListHistoryWidget();//显示历史记录界面
    void    slot_addToListHistoryWidget(const QString &text);
    void    slot_updateShowListEngineWidget();//显示历史记录界面
    void    slot_changeEngineIcon(const QString &text);//选中回显
    void    slot_addWebEngine();//添加引擎
    void    slot_updateShowListSettigMenu();//显示设置右键菜单
    void    slot_setCanGoForward(bool status);
    void    slot_setCanGoBack(bool status);
    void    slot_resetWebProgressBarValue();
    void    slot_replyFinished(QNetworkReply *reply);//设置头像

    //浏览器设置---右键菜单
    void    slot_browser_setMenu_createTab();               //新建窗口
    void    slot_browser_setMenu_createHiddenTab();         //新建隐身窗口
    void    slot_browser_setMenu_savePage();                //保存网页
    void    slot_browser_setMenu_findText();                //网页查找
    void    slot_browser_setMenu_fullScreen();              //网页全屏
    void    slot_browser_setMenu_showCollectRecords();      //显示收藏栏
    void    slot_browser_setMenu_clearSearchRecords();      //清空搜索记录
    void    slot_browser_setMenu_showCollectList();         //显示搜藏列表
    void    slot_browser_setMenu_showHistories();           //显示历史记录
    void    slot_browser_setMenu_manageExtensions();        //管理扩展
    void    slot_browser_setMenu_clearHistories();          //清除上网痕迹
    void    slot_browser_setMenu_viewSourceCode();          //查看源代码
    void    slot_browser_setMenu_workerManager();           //任务管理器
    void    slot_browser_setMenu_consoleOptions();          //控制台选项
    void    slot_browser_setMenu_internetOptions();         //internet选项
    void    slot_browser_setMenu_logOut();                  //退出登录
    void    slot_browser_setMenu_FAQ();                     //常见问题
    void    slot_browser_setMenu_help();                    //帮助

private:
    void    setShowToolTip();
    void    setUserHeadPicture(const QString & path);

signals:
    //窗口大小调节按钮
    void    sig_winClose();
    void    sig_winNormal();
    void    sig_winMinimum();
    void    sig_doubleClick();//调节主窗口
    //标题栏功能按钮
    void    sig_settingHelpItem(int index);//帮助
    void    sig_callLogin();//登录
    void    sig_setWindowSkin();//设置皮肤
    void    sig_filesUploadDownLoad(int index1, int index2);//上传下载
    void    sig_historyDownload(int index1, int index2);//历史记录
    void    sig_screenPicture();//截图
    //浏览器部分的信号
    void    sig_sendBlankUrl(QString url);//新建一个空白页（中转信号）
    void    sig_sendInputNewUrl(QString url);
    void    sig_sendNewSearch(QString his);
    void    sig_sendUrlBack();//返回
    void    sig_sendUrlAdvance();//前进
    void    sig_sendUrlRefreshen();//刷新
    void    sig_sendUrlHome();//主页
    void    sig_sendCanGoBack();//是否可回退
    void    sig_sendCanForward();//是否可前进
    void    sig_sendWebSkin();//皮肤
    void    sig_sendFavorites();//收藏栏
    void    sig_sendRecords();//历史记录
    void    sig_sendResume();//恢复
    void    sig_sendCollectRecord(QString address);

    //浏览器右键部分信号
    void    sig_sendBrowserCreateTab();//新建窗口
    void    sig_sendBrowserCreateHiddenTab();//新建隐身窗口
    void    sig_sendBrowserSavePage();//保存网页
    void    sig_sendBrowserFindText();//网页查找
    void    sig_sendBrowserFullScreen();//网页全屏
    void    sig_sendBrowserShowCollectRecords();//显示收藏栏
    void    sig_sendBrowserClearSearchRecords();//清空搜索记录
    void    sig_sendBrowserShowCollectList();//显示收藏列表
    void    sig_sendBrowserShowHistories();//显示历史记录
    void    sig_sendBrowserManageExtensions();//管理扩展
    void    sig_sendBrowserClearHistories();//清除上网痕迹
    void    sig_sendBrowserViewSourceCode();//查看源代码
    void    sig_sendBrowserWorkerManager();//任务管理器
    void    sig_sendBrowserConsoleOptions();//控制台选项
    void    sig_sendBrowserInternetOptions();//internet选项
    void    sig_sendBrowserLogOut();//退出登录
    void    sig_sendBrowserFAQ();//常见问题
    void    sig_sendBrowserHelp();//帮助

    //登录部分
    void    sig_sendClearTempRecords();
    void    sig_userSign_in(QString);//登录
    void    sig_userSign_out(QString);//下线
    void    sig_userRegister();//注册

    //下拉搜索界面
    void    sig_SendToMoreHots();//更多热搜


private:
    //视频内容搜索
    QAction         *m_actHotRank           =   nullptr;//热搜榜
    //网址搜索栏目
    QAction         *m_actSafeMode          =   nullptr;//浏览模式
    QAction         *m_actCollect           =   nullptr;//收藏网址
    QAction         *m_actRecords           =   nullptr;//搜索记录
    //简要搜索栏目
    QAction         *m_actEngine            =   nullptr;//搜索引擎
    QAction         *m_actSSearch           =   nullptr;//简要搜索
    QTimer          *m_timer3               =   nullptr;
    QMenu           *pmenu_help1            =   nullptr;
    QMenu           *pmenu_help2            =   nullptr;
    SearchForm      *m_searchForm           =   nullptr;
    HeadHover       *m_headHover            =   nullptr;
    Login           *m_loginForm            =   nullptr;
    QListWidget     *m_listWdgt_colloect    =   nullptr;//收藏列表
    QListWidget     *m_listWdgt_history     =   nullptr;//搜索历史记录
    QListWidget     *m_listWdgt_engine      =   nullptr;//搜索引擎
    QPushButton     *m_engineSetBtn         =   nullptr;//引擎设置按钮
    QString         m_headUrl;
    QPixmap         m_headPixmap;
    bool            m_signStatus;//登录状态，默认未未登录
    bool            m_netStatus[2] = {false,false};//（前一刻）网络状态
    QNetworkAccessManager   *manager;
    QNetworkConfigurationManager    *m_ncmgr = nullptr;
    QNetworkReply           *reply;
    Ui::TitleBar    *ui;
};

#endif // TITLEBAR_H
