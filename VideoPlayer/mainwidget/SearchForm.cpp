#include "SearchForm.h"
#include "ui_SearchForm.h"

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
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
