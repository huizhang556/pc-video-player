#include "CusLabel3.h"
#include "ui_CusLabel3.h"

CusLabel3::CusLabel3(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::CusLabel3)
{
    ui->setupUi(this);
}

CusLabel3::~CusLabel3()
{
    delete ui;
}
