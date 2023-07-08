#ifndef NEWLOGINFORM_H
#define NEWLOGINFORM_H
#define QRSIZE QSize(140,140)
#include "login/FAQitem.h"
#include "login/UserList.h"
#include "database/dataBase.h"
#include "qrcode/QrCode.hpp"
#include "login/ChangeHead.h"
#include "smtp/Smtp.h"

#include <string>
#include <vector>
using namespace qrcodegen;//注意加上命名空间

#include <QPoint>
#include <QImage>
#include <QAction>
#include <QPainter>
#include <QPaintEvent>
#include <QDialog>
#include <QColor>
#include <QToolTip>
#include <QTimer>
#include <QChar>
#include <QRegExp>
#include <QHeaderView>
#include <QScrollBar>
#include <QPlainTextEdit>
#include <QTreeWidgetItem>
#include <QRandomGenerator>
#include <QRegExpValidator>
#include <QAbstractItemView>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

//消息提示类型
enum TipType
{
    SUCCESS = 0,
    FAILED = 1,
    UNKMOW = 2
};


//窗口显示类型
enum ShowType
{
    LoginWin_0,//扫码登录
    LoginWin_1,//短信登录
    LoginWin_2,//账号登录
    RegisWin,//注册窗口
    ReSetWin//重置窗口
};

namespace Ui {
class NewLoginForm;
}

class NewLoginForm : public QDialog
{
    Q_OBJECT

public:
    ~NewLoginForm();
    void        initWorkUI();
    void        handleSignalsAndSLots();
    void        setInstallEventFilter();
    void        show_c();

    static      NewLoginForm* getInstance();

public slots:
    void        receiveLoginAppClose();
    void        slot_switchWinType(ShowType type);

protected:
//    void        paintEvent(QPaintEvent* event) override;
    bool        eventFilter(QObject *obj, QEvent *ev) override;

private slots:
    void        setUser_login();
    void        setUser_register();
    void        setUser_resetPwd();

    void        slot_clearTempInputText();

private:
    void        setType(TipType type);//设置报错信息显示样式
    void        showCText(ShowType stype,TipType type, const QPoint &pos, const QString& text, QWidget *w, const QRect &rect, int msecShowTime);//设置tooltip提示信息
    void        setStatusTips(ShowType stype,TipType type,const QString& text);//设置提示信息
    QString     generateRandomCode(int length);//生成随机字符串（字母+数字）
    bool        checkCurUserLoginStatus();//检查登录状态
    void        setCurUserLoginedInfo(int grade,const QString &nick);//设置当前登录用户信息
    void        showTipContentLenRule(const ShowType type, const QString& ruleText);//显示账号规则
    void        initAnimations();
    void        update_QRcode();//刷新二维码
    void        set_QRcode(const QString& content);//根据内容生成二维码
    void        addProtocol();//添加协议
    void        addUserQuestions(FAQitem *item);//添加问题
    void        addUserToLoginLists(int id_index);
    void        removeUserToLoginLists(int id_index);
    void        updateUserListGeomotry();
    bool        updateRemPwdStatus();//更新记住密码状态
    bool        sendCheckCode(ShowType type, const QString &receiver_email);//发送验证码

private:
    explicit NewLoginForm(QWidget *parent = nullptr);
    Ui::NewLoginForm *ui;
    static  NewLoginForm* m_pInstance;
//    QPoint  m_mvPos;

    bool        m_isEnabled = true;//刷新按钮状态(默认可以刷新)
    QAction     *m_actionShowPwd;//查看密码
    QAction     *m_act_pwd;//查看密码
    QPropertyAnimation *ani_opacity = nullptr;
//    QPropertyAnimation *ani_show = nullptr;
//    QPropertyAnimation *ani_top_hide   = nullptr;
//    QPropertyAnimation *ani_bom_hide   = nullptr;
    QParallelAnimationGroup *aniGroup = nullptr;
    UserList    *m_userLists   =   nullptr;
    QTimer      *loginTimer   =   nullptr;
    int         login_count = 60;
    QString     m_login_Random;

    QTimer      *regisTimer   =   nullptr;
    int         regis_count = 60;
    QString     m_regis_Random;

    QTimer      *fpwdTimer    =   nullptr;
    int         fpwd_count  = 60;
    QString     m_reset_Random;

signals:
    void    sig_sendClearTempRecords();
    void    sig_sendLoginOK(QString,QString,int);
    void    sig_sendToLoginedUser(QString,QString,QString);
};

#endif // NEWLOGINFORM_H
