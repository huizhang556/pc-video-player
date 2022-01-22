#include "CusVideoWidget.h"
#include "ui_CusVideoWidget.h"

CusVideoWidget::CusVideoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CusVideoWidget)
{
    ui->setupUi(this);
}

CusVideoWidget::~CusVideoWidget()
{
    delete ui;
}
