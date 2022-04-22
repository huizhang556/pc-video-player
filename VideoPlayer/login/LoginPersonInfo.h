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
    ~LoginPersonInfo();
    void initWorkUI();
    void chandleSignalsAndSLots();
    static  LoginPersonInfo* getInstance();

public slots:
    void showLoginWindow();

    void showLoginWindow(int index);

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
    //构造函数私有化  实现单例
    explicit LoginPersonInfo(QWidget *parent = nullptr);
    Ui::LoginPersonInfo *ui;
    QPoint              m_mvPos;
    QAction             *clearAction1;
    QAction             *clearAction2;
    QAction             *clearAction3;
    QAction             *clearAction4;
    QAction             *clearAction5;
    bool                passwdStatus;
    bool                passwdStatus2;
    static  LoginPersonInfo* m_pInstance;
};

#endif // LOGINPERSONINFO_H
