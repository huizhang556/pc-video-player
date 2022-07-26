#include "WebHistory.h"
#include "ui_WebHistory.h"
#include <QDebug>

WebHistory::WebHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebHistory)
{
    ui->setupUi(this);
    chandleSignalsAndSLots();
}

WebHistory::~WebHistory()
{
    delete ui;
}

void WebHistory::chandleSignalsAndSLots()
{
    //返回按钮
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){emit sig_returnPage();});
    //历史记录选中回显----回显选择的历史记录到lineEdit
    connect(ui->listWidget_showHis,&QListWidget::itemClicked,[=](QListWidgetItem *item)
    {
        if(item->text().isEmpty()) return;
        emit sig_sendItemText(item->text());
    });
}

bool WebHistory::judgeHistoryUrlExist(const QString &url)
{
    for(int i = 0; i < ui->listWidget_showHis->count(); i++)
    {
        if(ui->listWidget_showHis->item(i)->text() == url)
            return true;//代表有
    }
    return false;//代表无
}

void WebHistory::slot_addToListHistoryWidget(const QString &text)
{
    if(text.isEmpty()) return;
    if(!judgeHistoryUrlExist(text))//没有找到才添加
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon("://images/function/history_list_item.png"),text);
        ui->listWidget_showHis->addItem(item);
    }
}

