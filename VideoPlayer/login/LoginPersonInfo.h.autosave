#ifndef LOGINPERSONINFO_H
#define LOGINPERSONINFO_H

#include <QWidget>
#include <QPoint>
#include <QAction>
#include <QListView>
#include <QCompleter>
#include <QPushButton>
#include <QListWidget>
#include <QStringListModel>

namespace Ui {
class LoginPersonInfo;
}

class LoginPersonInfo : public QWidget
{
    Q_OBJECT
public:
    ~LoginPersonInfo();
    void        initWorkUI();
    void        chandleSignalsAndSLots();
    static      LoginPersonInfo* getInstance();

public slots:
    void        showLoginWindow();

    void        showLoginWindow(int index);

    void        receiveLoginAppClose();

protected:

    void        showEvent(QShowEvent *event) override;

private slots:
    void        on_pushButton_return_page2_clicked();

    void        on_pushButton_return_page3_clicked();

    void        on_gis_BtnRegister_clicked();

    void        on_reset_BtnReset_clicked();

    void        on_pushButton_return_page4_clicked();

    void        on_set_BtnReturn_clicked();

    void        slot_showWarning_login(const QString &text);//登录界面提示
    void        slot_clearWarning_login();//清除登录界面提示


    void        slot_showWarning_gis(const QString &text);//注册界面提示
    void        slot_clearWarning_gis();//清除注册界面提示

    void        slot_showWaringText(const QString &text);//测试界面

    void        slot_clearWarningText();

    void        slot_addLoginHisUsers(const QString &name);//添加登录历史
    void        slot_clearTempInputText();//清除临时输入的文字
    void        slot_setLoginStatusButtonGeometry();//设置位置
    void        slot_setLoginStatusButtonStyle(bool status);//设置样式

private:
    //构造函数私有化  实现单例
    explicit LoginPersonInfo(QWidget *parent = nullptr);
    Ui::LoginPersonInfo *ui;
    QListWidget         *m_listWgt_UserList     =   nullptr;

    QAction             *userAction;
    QAction             *keybordAction;
    QAction             *clearAction1;
    QAction             *clearAction2;
    QAction             *clearAction3;
    QAction             *clearAction4;
    QAction             *clearAction5;
    bool                passwdStatus;
    bool                passwdStatus2;
    QPushButton         *m_loginStatusBtn;
    QCompleter          *m_completer;
    QStringList         m_comlist;//登录历史记录
    static  LoginPersonInfo* m_pInstance;

signals:
    void        sig_sendClearTempRecords();//登陆之前清除临时的记录
    void        sig_sendLoginOK(QString,QString,int);//名称，头像连接 用户级别
};

#endif // LOGINPERSONINFO_H
