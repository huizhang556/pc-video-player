#include "CusVideoBox2.h"
#include "ui_CusVideoBox2.h"

CusVideoBox2::CusVideoBox2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CusVideoBox2)
{
    ui->setupUi(this);
}

CusVideoBox2::~CusVideoBox2()
{
    delete ui;
}
