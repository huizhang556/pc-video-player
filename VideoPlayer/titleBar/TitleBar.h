#ifndef TITLEBAR_H
#define TITLEBAR_H
#include "login/Login.h"
#include "skin/MySkin.h"
#include "mainwidget/SearchForm.h"
#include "login/LoginPersonInfo.h"
#include "browser/WebDownLoadList.h"
#include <QMenu>
#include <QPoint>
#include <QTimer>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMouseEvent>

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
    void    chandleSignalAndSLots();

protected:
    void    mouseDoubleClickEvent(QMouseEvent *event) override;
    bool    eventFilter(QObject *watched, QEvent *event) override;
    void    showEvent(QShowEvent *event) override;

//公有槽函数以公共接口的形式暴露在外面，外部任何客户可以直接访问
public slots:
    void isNecessaryShowSearch(int index);
    //处理鼠标进入离开输入框
    void    mouseIsEnterLeaveLineEdit(QObject *watched, QEvent *event);
    void    receiveMainFormClose();
    void    mouseIsPressReleaseLineEdit(QObject *watched, QEvent *event);//搜索框点击事件
    void    serarchLineEditFacous(QObject *watched, QEvent *event);
    void    slot_switchToLoginPage(int mark,QString nick);
    void    slot_setButtonHelpEmitItem();
    void    slot_receivedListItemText(QString text);
    void    slot_setWebLineEditCurentUrl(QUrl url);//设置当前url
    void    slot_clearWebLineEditText();//清除weblineedit文字
    void    slot_setWebProgressBarValue(int value);//网页加载时，显示加载进度
    void    slot_resetWebProgressBarValue();
    void    slot_receiveBlankWebTab();//接收tabbar添加一个空白网页的请求

//私有槽函数，外部不能直接访问
private slots:
    void    chandleMainWinStatus(bool status);
    void    getSystemTimeShow();
    void    setLineEditAddress(const QUrl url);
    void    showLoginForm();//显示登录窗口
    void    showMySkin();//皮肤设置
    void    createHelpMenu();//帮助菜单
    QString judgeUrlType(QString url);
    bool    judgeCollectUrlType(QString url);//判断要收藏的url是否有效类型
    bool    judgeCollectUrlExist(const QString &url);//判断当前的网址是否已经在收藏栏

    bool    judgeHistorytUrlType(QString url);//判断要收藏的url是否有效类型
    bool    judgeHistoryUrlExist(const QString &url);//判断当前的网址是否已经在收藏栏
    void    slot_setCurrentWebSiteCollectStatus(const QString &url);//判断当前的网址是显示收藏还是未收藏
    void    slot_addToListCollectWidget(const QString &text);//选中回显
    void    slot_updateShowListHistoryWidget();//显示历史记录界面
    void    slot_addToListHistoryWidget(const QString &text);
    void    slot_updateShowListEngineWidget();//显示历史记录界面
    void    slot_changeEngineIcon(const QString &text);//选中回显
    void    slot_addWebEngine();//添加引擎
    void    slot_updateShowListSettigMenu();//显示设置右键菜单
    void    slot_setCanGoForward(bool status);
    void    slot_setCanGoBack(bool status);
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
    void    sig_userLogin();
    void    sig_userRegister();

private:
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
    Login           *m_loginForm            =   nullptr;
    MySkin          *m_mySkin               =   nullptr;
    QListWidget     *m_listWdgt_colloect    =   nullptr;//收藏列表
    QListWidget     *m_listWdgt_history     =   nullptr;//历史记录
    QListWidget     *m_listWdgt_engine      =   nullptr;//搜索引擎
    QPushButton     *m_engineSetBtn         =   nullptr;//引擎设置按钮
    QString         m_headUrl;
    Ui::TitleBar    *ui;
};

#endif // TITLEBAR_H
