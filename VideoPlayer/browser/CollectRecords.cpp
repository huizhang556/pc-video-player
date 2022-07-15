#include "CollectRecords.h"
#include "ui_CollectRecords.h"
#include <QDebug>

CollectRecords::CollectRecords(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectRecords)
{
    ui->setupUi(this);
    chandleSignalsAndSlots();
}

CollectRecords::~CollectRecords()
{
    delete ui;
}

void CollectRecords::chandleSignalsAndSlots()
{
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){emit sig_returnPage();});
}
