#ifndef LOGINPERSONINFO_H
#define LOGINPERSONINFO_H

#include <QWidget>
#include <QPoint>
#include <QAction>

namespace Ui {
class LoginPersonInfo;
}

class LoginPersonInfo : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPersonInfo(QWidget *parent = nullptr);
    ~LoginPersonInfo();

public slots:
    void showLoginWindow();

    void receiveLoginAppClose();
protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

signals:


private slots:
    void on_pushButton_return_page2_clicked();

    void on_pushButton_return_page3_clicked();

    void on_gis_BtnRegister_clicked();

    void on_reset_BtnReset_clicked();

    void on_pushButton_return_page4_clicked();

    void on_set_BtnReturn_clicked();


private:
    Ui::LoginPersonInfo *ui;
    QPoint              m_mvPos;
    QAction             *clearAction1;
    QAction             *clearAction2;
    QAction             *clearAction3;
    QAction             *clearAction4;
    QAction             *clearAction5;
    bool                passwdStatus;
    bool                passwdStatus2;
};

#endif // LOGINPERSONINFO_H
