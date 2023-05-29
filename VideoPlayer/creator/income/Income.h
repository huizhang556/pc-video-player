#ifndef INCOME_H
#define INCOME_H

#include "database/dataBase.h"
#include "qcustomplot/qcustomplot.h"
#include "creator/income/CusCalendar.h"
//表数据导出用QtXlsx
#include <QtXlsx/xlsxdocument.h>
#include <QtCharts>
#include <QChartView>
#include <QPieSlice>
QT_CHARTS_USE_NAMESPACE

#include <QMenu>
#include <QTimer>
#include <QWidget>
#include <QMouseEvent>
#include <QFileDialog>
#include <QStringList>
#include <QWidgetAction>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QDebug>


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
    void    updateExportBtnStatus();
    void    exportTableRecords();//导出表记录
    void    drawIncomeDataTo_line();//绘制折线图
    void    drawIncomeDataTo_barchart();//绘制柱状图
    void    drawIncomeDataTo_piechart();//绘制饼图

private slots:
    void    slot_updateTracerText(QMouseEvent *event);//更新游标内容

private:
    Ui::Income *ui;
    int             m_row = 0;
    CusCalendar     *m_calendar     =   nullptr;
    QMenu           *m_menuDataTime =   nullptr;
    QWidgetAction   *m_wgtAction    =   nullptr;

    QCPItemTracer   *tracer;//游标
    QCPItemText     *tracerLabel;//游标显示内容的地方


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
