#include "RadioHost.h"
#include "ui_RadioHost.h"

RadioHost::RadioHost(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RadioHost)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

RadioHost::~RadioHost()
{
    delete ui;
}

void RadioHost::initWorkUI()
{
    ui->listWidget_2->horizontalScrollBar()->setDisabled(true);
    ui->listWidget_3->horizontalScrollBar()->setDisabled(true);
    ui->listWidget_4->horizontalScrollBar()->setDisabled(true);
    ui->listWidget_5->horizontalScrollBar()->setDisabled(true);
}

void RadioHost::handleSignalsAndSlots()
{

}
