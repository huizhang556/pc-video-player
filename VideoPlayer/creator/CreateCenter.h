/**用户创作中心**/
#ifndef CREATECENTER_H
#define CREATECENTER_H
#define MARWIDTH 2 //窗口边距,进过测试最小需要2px

#include "database/dataBase.h"
#include "creator/CreTitleBar.h"
#include "customer/BaseWidget.h"
#include "creator/income/Income.h"
#include "creator/producer/Maker.h"
#include "creator/mywork/DoneWorks.h"
#include "creator/percenter/PerCenter.h"
#include "creator/analydata/DataAnalysis.h"

#include <QWidget>
#include <QEvent>
#include <QCursor>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class CreateCenter;
}

class CreateCenter : public BaseWidget
{
    Q_OBJECT

    explicit CreateCenter(QWidget *parent = nullptr);
public:
    ~CreateCenter();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();
    static CreateCenter* getInstance();
    void    exec_();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;


private:
    Ui::CreateCenter *ui;
    static  CreateCenter*   m_pInstance;
    CreTitleBar             *m_ctitleBar    =   nullptr;
    PerCenter               *m_perCenter    =   nullptr;
    Maker                   *m_maker        =   nullptr;
    DoneWorks               *m_doneWorks    =   nullptr;
    Income                  *m_income       =   nullptr;
    DataAnalysis            *m_dataAnaly    =   nullptr;

};

#endif // CREATECENTER_H
