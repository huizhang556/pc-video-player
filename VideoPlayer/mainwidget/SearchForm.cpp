#include "SearchForm.h"
#include "ui_SearchForm.h"

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    ui->btn_his_delete->setFlat(true);
    ui->btn_hot_more->setFlat(true);
}

SearchForm::~SearchForm()
{
    delete ui;
}

void SearchForm::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->hide();
}
