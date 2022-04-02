#include "SearchForm.h"
#include "ui_SearchForm.h"
#include <QDebug>

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    initWorkUi();
    chandleSignalsAndSlot();

}

SearchForm::~SearchForm()
{
    delete ui;
}

void SearchForm::initWorkUi()
{
    ui->btn_his_delete->setFlat(true);
    ui->btn_hot_more->setFlat(true);
    clearHistoryList();
}

void SearchForm::chandleSignalsAndSlot()
{
    connect(ui->btn_his_delete,&QPushButton::clicked,[=](){ clearHistoryList(); });
}

void SearchForm::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->hide();
}

void SearchForm::clearHistoryList()
{
    ui->listWidget_his1->clear();
    ui->listWidget_his2->clear();
}

void SearchForm::addHistoryItem(QString his)
{
    if(ui->listWidget_his2->count() > 4)
    {
        clearHistoryList();
    }
    qDebug() << his;
    QListWidgetItem *item =  new QListWidgetItem(his);
    if(ui->listWidget_his1->count() <= 4)
    {
//      item->setSizeHint(QSize());
        ui->listWidget_his1->addItem(item);
    }
    else
    {
        if((ui->listWidget_his2->count() <= 4))
        ui->listWidget_his2->addItem(item);
    }

}

void SearchForm::closeSearchForm()
{
    this->close();
}
