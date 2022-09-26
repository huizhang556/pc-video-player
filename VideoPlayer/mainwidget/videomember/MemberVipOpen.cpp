#include "MemberVipOpen.h"
#include "ui_MemberVipOpen.h"

MemberVipOpen::MemberVipOpen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MemberVipOpen)
{
    ui->setupUi(this);
}

MemberVipOpen::~MemberVipOpen()
{
    delete ui;
}
