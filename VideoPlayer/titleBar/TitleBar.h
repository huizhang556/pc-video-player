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
    void initWorker();
    void chandleSignalAndSLots();
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    void showEvent(QShowEvent *event) override;

//公有槽函数以公共接口的形式暴露在外面，外部任何客户可以直接访问
public slots:
    void isNecessaryShowSearch(int index);
    //处理鼠标进入离开输入框
    void mouseIsEnterLeaveLineEdit(QObject *watched, QEvent *event);
    void receiveMainFormClose();
    void mouseIsPressReleaseLineEdit(QObject *watched, QEvent *event);//搜索框点击事件
    void serarchLineEditFacous(QObject *watched, QEvent *event);
    void slot_switchToLoginPage(int mark,QString nick);
    void slot_setButtonHelpEmitItem();
    void slot_setWebLineEditCurentUrl(QUrl url);//设置当前url
    void slot_setWebProgressBarValue(int value);//网页加载时，显示加载进度
    void slot_resetWebProgressBarValue();
//私有槽函数，外部不能直接访问
private slots:
    void chandleMainWinStatus(bool status);
    void getSystemTimeShow();
    void setLineEditAddress(const QUrl url);
    void showLoginForm();//显示登录窗口
    void showMySkin();//皮肤设置
    void createHelpMenu();//帮助菜单
    QString judgeUrlType(QString url);
    bool judgeCollectUrlType(QString url);//判断要收藏的url是否有效类型
    bool judgeCollectUrlExist(const QString &url);//判断当前的网址是否已经在收藏栏

    bool judgeHistorytUrlType(QString url);//判断要收藏的url是否有效类型
    bool judgeHistoryUrlExist(const QString &url);//判断当前的网址是否已经在收藏栏

    void slot_setCurrentWebSiteCollectStatus(const QString &url);//判断当前的网址是显示收藏还是未收藏
    void slot_updateShowListCollectWidget();//显示收藏菜单界面
    void slot_addToListCollectWidget(const QString &text);//选中回显
    void slot_updateShowListHistoryWidget();//显示历史记录界面
    void slot_addToListHistoryWidget(const QString &text);//选中回显
    void slot_updateShowListSettigMenu();//显示设置右键菜单
    void slot_setCanGoForward(bool status);
    void slot_setCanGoBack(bool status);
    //浏览器设置
    void slot_browser_setting_newWindows();//新建窗口
    void slot_browser_setting_clearSearchHistory();
    void slot_clearSearchListHistory();
private:
    void setShowToolTip();

signals:
    //窗口大小调节按钮
    void sig_winClose();
    void sig_winNormal();
    void sig_winMinimum();
    void sig_doubleClick();//调节主窗口
    //标题栏功能按钮
    void sig_settingHelpItem(int index);//帮助
    void sig_callLogin();//登录
    void sig_setWindowSkin();//设置皮肤
    void sig_filesUploadDownLoad(int index1, int index2);//上传下载
    void sig_historyDownload(int index1, int index2);//历史记录
    void sig_screenPicture();//截图
    //浏览器部分的信号
    void sig_sendInputNewUrl(QString url);
    void sig_sendNewSearch(QString his);
    void sig_sendUrlBack();
    void sig_sendUrlAdvance();
    void sig_sendUrlRefreshen();
    void sig_sendUrlHome();
    void sig_sendCanGoBack();
    void sig_sendCanForward();
    //登录部分
    void sig_userLogin();
    void sig_userRegister();

private:
    QTimer          *m_timer3               = nullptr;
    QMenu           *pmenu_help1            = nullptr;
    QMenu           *pmenu_help2            = nullptr;
    SearchForm      *m_searchForm           = nullptr;
    Login           *m_loginForm            = nullptr;
    MySkin          *m_mySkin               = nullptr;
    QListWidget     *m_listWdgt_colloect    = nullptr;//收藏列表
    QListWidget     *m_listWdgt_history     = nullptr;//历史记录
    Ui::TitleBar    *ui;
};

#endif // TITLEBAR_H
