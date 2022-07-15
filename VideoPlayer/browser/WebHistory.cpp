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
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){emit sig_returnPage();});
}
