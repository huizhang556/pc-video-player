#include "CusListWidget.h"
#include "ui_CusListWidget.h"
#include <QScrollBar>
#include <QDebug>

CusListWidget::CusListWidget(QWidget *parent) :
    QListWidget(parent),
    ui(new Ui::CusListWidget)
{
    ui->setupUi(this);
    handleSignalsAndSlots();
}

CusListWidget::~CusListWidget()
{
    delete ui;
}

void CusListWidget::handleSignalsAndSlots()
{
    connect(ui->pushButton_left,&QPushButton::clicked,[=](){
        int step = this->horizontalScrollBar()->value();
        this->horizontalScrollBar()->setValue(step - this->item(0)->sizeHint().width());
    });

    connect(ui->pushButton_right,&QPushButton::clicked,[=](){
        int step = this->horizontalScrollBar()->value();
        this->horizontalScrollBar()->setValue(step + this->item(0)->sizeHint().width());
    });
}
