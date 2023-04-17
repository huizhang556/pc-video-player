#ifndef INCOME_H
#define INCOME_H

#include <QWidget>
#include <QMenu>
#include <QStringList>
#include <QWidgetAction>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDebug>

#include "database/dataBase.h"
#include "creator/income/CusCalendar.h"

namespace Ui {
class Income;
}

class Income : public QWidget
{
    Q_OBJECT

public:
    explicit Income(QWidget *parent = nullptr);
    ~Income();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();

    void    getUserIncomeRecord();//查询区间记录

private:
    void    addOneUserIncomeRecordTo_UI(QStringList &recordlist);
    void    clearTable();

private:
    Ui::Income *ui;
    int             m_row = 0;
    CusCalendar     *m_calendar     =   nullptr;
    QMenu           *m_menuDataTime =   nullptr;
    QWidgetAction   *m_wgtAction    =   nullptr;

    QStringList m_header =
    {
        QString(u8"提取时间"),
        QString(u8"类型"),
        QString(u8"金额(元)"),
        QString(u8"状态"),
        QString(u8"操作")
    };
};

#endif // INCOME_H
