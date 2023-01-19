#ifndef NEWLOGINFORM_H
#define NEWLOGINFORM_H

#include <QPoint>
#include <QAction>
#include <QPainter>
#include <QPaintEvent>
#include <QDialog>
#include <QColor>
#include <QToolTip>
#include <QPropertyAnimation>
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
    void        chandleSignalsAndSLots();
    static      NewLoginForm* getInstance();
    void        setType(TipType type);
    static void showCText(TipType type, const QPoint &pos, const QString& text, QWidget *w, const QRect &rect, int msecShowTime);

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
    explicit NewLoginForm(QWidget *parent = nullptr);
    Ui::NewLoginForm *ui;
//    QPoint  m_mvPos;
    QAction *m_actionShowPwd;//查看密码
    static  NewLoginForm* m_pInstance;

signals:
    void    sig_sendClearTempRecords();
    void    sig_sendLoginOK(QString,QString,int);
};

#endif // NEWLOGINFORM_H
