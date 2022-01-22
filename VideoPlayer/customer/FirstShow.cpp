#include "FirstShow.h"
#include "ui_FirstShow.h"

FirstShow::FirstShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstShow)
{
    ui->setupUi(this);
}

FirstShow::~FirstShow()
{
    delete ui;
}
