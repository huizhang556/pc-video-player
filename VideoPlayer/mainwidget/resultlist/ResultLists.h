#ifndef RESULTLISTS_H
#define RESULTLISTS_H
#include "mainwidget/resultlist/SynopsisForm.h"
#include "mainwidget/resultlist/FUserForm.h"
#include "mainwidget/resultlist/FAboutForm.h"
#include <QWidget>
#include <QAction>
#include <QButtonGroup>
#include <QDebug>

namespace Ui {
class ResultLists;
}

class ResultLists : public QWidget
{
    Q_OBJECT

public:
    explicit ResultLists(QWidget *parent = nullptr);
    ~ResultLists();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

private:
    Ui::ResultLists *ui;
    QButtonGroup    *m_btnGroup1    =   nullptr;
    QButtonGroup    *m_btnGroup2    =   nullptr;
    QButtonGroup    *m_btnGroup3    =   nullptr;
    QButtonGroup    *m_btnGroup4    =   nullptr;
    QButtonGroup    *m_btnGroup5    =   nullptr;
    QAction         *m_searchAction =   nullptr;

signals:
    void    sig_return_home();
};

#endif // RESULTLISTS_H
