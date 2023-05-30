#ifndef PERSONFILEFORM_H
#define PERSONFILEFORM_H
#include "database/dataBase.h"

#include <QWidget>
#include <QUrlQuery>
#include <QTabWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QDebug>

#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

namespace Ui {
class PersonFileForm;
}

class PersonFileForm : public QWidget
{
    Q_OBJECT

public:
    explicit PersonFileForm(QWidget *parent = nullptr);
    ~PersonFileForm();
    void initWorkUI();
    void chandleSignalsAndSLots();

    QStackedWidget* getgetCurrentShowWidget_SW();
    QListWidget*    getCurrentShowWidget_LW();
    QTabWidget*     getCurrentShowWidget_TW();

public slots:
    void slot_showOtherUserInfo(const QString& userid);
    //处理各个界面  重载
    void setShowCurrentWidget(QObject *obj1,int index1, QObject *obj2,int index2);
    void setShowCurrentWidget(QObject *obj1,QWidget *wdgt1, QObject *obj2,QWidget *wdgt2);

private slots:
    void    slot_receivedUserHeader(QNetworkReply* reply);

private:
    void    setOtherUser_grade(const int grade);

private:
    Ui::PersonFileForm *ui;
    QNetworkAccessManager   *m_manager  =   nullptr;

signals:
    void    sig_sendReturnPage(int);
};

#endif // PERSONFILEFORM_H
