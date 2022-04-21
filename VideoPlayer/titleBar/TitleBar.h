#ifndef TITLEBAR_H
#define TITLEBAR_H
#include "login/Login.h"
#include "skin/MySkin.h"
#include "mainwidget/SearchForm.h"

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

//私有槽函数，外部不能直接访问
private slots:
    void chandleMainWinStatus(bool status);
    void getSystemTimeShow();
    void setLineEditAddress(const QUrl url);
    void showLoginForm();//显示登录窗口
    void showMySkin();//皮肤设置

private:

    void setShowToolTip();

private:
    QTimer          *m_timer1       = nullptr;
    QTimer          *m_timer2       = nullptr;
    QTimer          *m_timer3       = nullptr;
    SearchForm      *m_searchForm   = nullptr;
    Login           *m_loginForm    = nullptr;
    MySkin          *m_mySkin       = nullptr;
    Ui::TitleBar    *ui;

signals:
    //窗口大小调节按钮
    void sig_winClose();
    void sig_winNormal();
    void sig_winMinimum();
    void sig_doubleClick();//调节主窗口
    //标题栏功能按钮
    void sig_settingHelp();//帮助
    void sig_callLogin();//登录
    void sig_setWindowSkin();//设置皮肤
    void sig_filesUploadDownLoad(int index1, int index2);//上传下载
    void sig_historyDownload(int index1, int index2);//历史记录
    void sig_screenPicture();//截图
    //浏览器部分的信号
    void sig_sendNewUrl(QString url);
    void sig_sendNewSearch(QString his);
    void sig_sendUrlBack();
    void sig_sendUrlAdvance();
    void sig_sendUrlRefreshen();
    void sig_sendUrlHome();
};

#endif // TITLEBAR_H
