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

}

void RadioHost::handleSignalsAndSlots()
{

}
