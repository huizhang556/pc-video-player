#include "StackItemForm.h"
#include "ui_StackItemForm.h"

StackItemForm::StackItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackItemForm)
{
    ui->setupUi(this);
    initWorkUI();
    chandleSignalsAndSlots();
}

StackItemForm::~StackItemForm()
{
    delete ui;
}

void StackItemForm::initWorkUI()
{
    for(int i = 0; i < 10; i++)
    {
        QLabel *label = new QLabel("picture%1");
        m_mapLabel.insert(i, label);
    }
    addLabelToStackWidget();
}

void StackItemForm::chandleSignalsAndSlots()
{

}

void StackItemForm::addLabelToStackWidget()
{
    for(int i = 0; i < m_mapLabel.count(); i++)
    {
        ui->stackedWidget_itempic->insertWidget(i,m_mapLabel[i]);
    }
}
