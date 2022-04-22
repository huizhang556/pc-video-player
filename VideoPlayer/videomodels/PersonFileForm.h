#ifndef PERSONFILEFORM_H
#define PERSONFILEFORM_H

#include <QWidget>
#include <QTabWidget>
#include <QListWidget>
#include <QStackedWidget>

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
    //处理各个界面  重载
    void setShowCurrentWidget(QObject *obj1,int index1, QObject *obj2,int index2);
    void setShowCurrentWidget(QObject *obj1,QWidget *wdgt1, QObject *obj2,QWidget *wdgt2);

private:
    Ui::PersonFileForm *ui;
};

#endif // PERSONFILEFORM_H
