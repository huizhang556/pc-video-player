#ifndef NEWLOGINFORM_H
#define NEWLOGINFORM_H

#include <QPoint>
#include <QAction>
#include <QPainter>
#include <QPaintEvent>
#include <QDialog>

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

public slots:
    void        receiveLoginAppClose();
    void        slot_switchWinType(ShowType type);

protected:
    void        paintEvent(QPaintEvent* event) override;
    void        mousePressEvent(QMouseEvent *event) override;
    void        mouseMoveEvent(QMouseEvent *event) override;

private:
    explicit NewLoginForm(QWidget *parent = nullptr);
    Ui::NewLoginForm *ui;
    QPoint  m_mvPos;
    QAction *m_actionShowPwd;//查看密码
    static  NewLoginForm* m_pInstance;
};

#endif // NEWLOGINFORM_H
