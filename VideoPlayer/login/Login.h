#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "LoginPersonInfo.h"
#include <QPaintEvent>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();


protected:
//    bool eventFilter(QObject *watch, QEvent *event) override;
    void leaveEvent(QEvent *event) override;

    void  paintEvent(QPaintEvent *event) override;
public slots:
    void receiveMainWinCloseAppSignal();

signals:
    void sig_LoginWinClose();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
