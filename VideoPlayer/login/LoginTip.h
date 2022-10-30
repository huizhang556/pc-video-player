#ifndef LOGINTIP_H
#define LOGINTIP_H
#include "NewLoginForm.h"
#include <QWidget>
#include <QEvent>
#include <QDebug>

namespace Ui {
class LoginTip;
}

class LoginTip : public QWidget
{
    Q_OBJECT

public:
    ~LoginTip();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    static LoginTip*  getInstance();

protected:
    bool    eventFilter(QObject *watch, QEvent *event) override;
    void    paintEvent(QPaintEvent *event) override;
    void    leaveEvent(QEvent *event) override;

private:
    explicit LoginTip(QWidget *parent = nullptr);
    Ui::LoginTip *ui;
    static  LoginTip* m_pInstance;
    int     m_startX;
    int     m_startY;
    int     m_triangleWidth;//小三角宽度
    int     m_triangleHeight;//小三角高度

private:
    void    userLogin();
};

#endif // LOGINTIP_H
