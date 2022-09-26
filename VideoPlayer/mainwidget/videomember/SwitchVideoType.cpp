#include "SwitchVideoType.h"
#include "ui_SwitchVideoType.h"

SwitchVideoType::SwitchVideoType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SwitchVideoType)
{
    ui->setupUi(this);
    setFixedHeight(60);
}

SwitchVideoType::~SwitchVideoType()
{
    delete ui;
}
