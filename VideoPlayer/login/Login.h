#ifndef LOGIN_H
#define LOGIN_H
#define ITEMSIZE QSize(290,63)
#include <QDialog>
#include <QSize>
#include "NewLoginForm.h"
#include "LoginPersonInfo.h"
#include <QPaintEvent>

enum MessType
{
    M_COMMENT,
    M_ABOUTME,
    M_NOTIFY
};

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    void    initWorkUI();
    void    handleSignalsAndSlots();

protected:
//    bool eventFilter(QObject *watch, QEvent *event) override;
    void    leaveEvent(QEvent *event) override;

    void    paintEvent(QPaintEvent *event) override;

public slots:
    void    receiveMainWinCloseAppSignal();
    void    slot_setPersonVipPage(int index);
    void    slot_addMessageItemToBox(MessType mtype, const QString& pic,const QString& nickname,const QString& datatime,const QString& message);

signals:
    void    sig_LoginWinClose();
    void    sig_sendSign_out();//退出

private:
    Ui::Login *ui;
    int     m_startX;
    int     m_startY;
    int     m_triangleWidth;//小三角宽度
    int     m_triangleHeight;//小三角高度
};

#endif // LOGIN_H
