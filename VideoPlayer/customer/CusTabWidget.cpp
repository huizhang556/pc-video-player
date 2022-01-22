#include "CusTabWidget.h"
#include "ui_CusTabWidget.h"

CusTabWidget::CusTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CusTabWidget)
{
    ui->setupUi(this);

}

CusTabWidget::~CusTabWidget()
{
    delete ui;
}
