#ifndef NEWLOGINFORM_H
#define NEWLOGINFORM_H
#define QRSIZE QSize(140,140)
#include "login/FAQitem.h"
#include "login/UserList.h"
#include "database/dataBase.h"
#include "qrcode/QrCode.hpp"

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
#include <QRegExp>
#include <QHeaderView>
#include <QScrollBar>
#include <QPlainTextEdit>
#include <QTreeWidgetItem>
#include <QRegExpValidator>
#include <QAbstractItemView>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsDropShadowEffect>
#include <QDebug>


enum TipType
{
    Normal = 0,
    Error = 1,
    Correct = 2
};

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
    void        setType(TipType type);
    void        show_c();

    static void showCText(TipType type, const QPoint &pos, const QString& text, QWidget *w, const QRect &rect, int msecShowTime);
    static      NewLoginForm* getInstance();

public slots:
    void        receiveLoginAppClose();
    void        slot_switchWinType(ShowType type);

protected:
    void        paintEvent(QPaintEvent* event) override;
    bool        eventFilter(QObject *obj, QEvent *ev) override;

private slots:
    void        setUser_login();
    void        setUser_register();
    void        setUser_reSet();
    void        setUser_findPwd();

    void        slot_clearTempInputText();

private:
    bool        checkCurUserLoginStatus();//检查登录状态
    void        setCurUserLoginedInfo(int grade,const QString &nick);//设置当前登录用户信息
    void        showTipContentLenRule(const QString& ruleText);//显示账号规则
    void        initAnimations();
    void        update_QRcode();//刷新二维码
    void        set_QRcode(const QString& content);//根据内容生成二维码
    void        addProtocol();//添加协议
    void        addUserQuestions(FAQitem *item);//添加问题
    void        addUserToLoginLists(int id_index);
    void        removeUserToLoginLists(int id_index);
    void        updateUserListGeomotry();

private:
    explicit NewLoginForm(QWidget *parent = nullptr);
    Ui::NewLoginForm *ui;
    static  NewLoginForm* m_pInstance;
//    QPoint  m_mvPos;

    bool    m_isEnabled = true;//刷新按钮状态(默认可以刷新)
    QAction *m_actionShowPwd;//查看密码
    QAction *m_act_pwd;//查看密码
    QPropertyAnimation *ani_opacity = nullptr;
//    QPropertyAnimation *ani_show = nullptr;
//    QPropertyAnimation *ani_top_hide   = nullptr;
//    QPropertyAnimation *ani_bom_hide   = nullptr;
    QParallelAnimationGroup *aniGroup = nullptr;
    UserList    *m_userLists    =   nullptr;

signals:
    void    sig_sendClearTempRecords();
    void    sig_sendLoginOK(QString,QString,int);
    void    sig_sendToLoginedUser(QString,QString,QString);
};

#endif // NEWLOGINFORM_H
