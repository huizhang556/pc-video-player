#include "DataAnalysis.h"
#include "ui_DataAnalysis.h"

DataAnalysis::DataAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataAnalysis)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
}

DataAnalysis::~DataAnalysis()
{
    delete ui;
}

void DataAnalysis::initWorkUI()
{
    ui->pushButton_playcount->setCheckable(true);
    ui->pushButton_likecount->setCheckable(true);
    ui->pushButton_collectcount->setCheckable(true);
    ui->pushButton_playcount->setChecked(true);
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(ui->pushButton_playcount,0);
    m_buttonGroup->addButton(ui->pushButton_likecount,1);
    m_buttonGroup->addButton(ui->pushButton_collectcount,2);
    m_buttonGroup->setExclusive(true);
}

void DataAnalysis::handleSignalsAndSlots()
{
    connect(m_buttonGroup,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton *button){
        qDebug() << button->text();
        button->setChecked(true);
    });
}

void DataAnalysis::setInstallEventer()
{

}
