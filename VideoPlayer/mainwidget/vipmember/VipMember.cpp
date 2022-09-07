#include "VipMember.h"
#include "ui_VipMember.h"

VipMember::VipMember(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VipMember)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

VipMember::~VipMember()
{
    delete ui;
}

void VipMember::initWorkUI()
{

}

void VipMember::handleSignalsAndSlots()
{

}
