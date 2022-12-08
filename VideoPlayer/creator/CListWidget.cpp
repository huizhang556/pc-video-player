#include "CListWidget.h"
#include "ui_CListWidget.h"

CListWidget::CListWidget(QWidget *parent) :
    QListWidget(parent),
    ui(new Ui::CListWidget)
{
    ui->setupUi(this);
}

CListWidget::~CListWidget()
{
    delete ui;
}

void CListWidget::initWorkUI()
{

}

void CListWidget::handleSignalsAndSLots()
{

}

void CListWidget::dragEnterEvent()
{

}

void CListWidget::dropEvent(QDropEvent *event)
{

}
