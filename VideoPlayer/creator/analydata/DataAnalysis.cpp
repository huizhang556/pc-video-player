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
    ui->pushButton_fanscount->setCheckable(true);
    ui->pushButton_playcount->setCheckable(true);
    ui->pushButton_likecount->setCheckable(true);
    ui->pushButton_collectcount->setCheckable(true);
    ui->pushButton_fanscount->setChecked(true);
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(ui->pushButton_fanscount,0);
    m_buttonGroup->addButton(ui->pushButton_playcount,1);
    m_buttonGroup->addButton(ui->pushButton_likecount,2);
    m_buttonGroup->addButton(ui->pushButton_collectcount,3);
    m_buttonGroup->setExclusive(true);

    ui->stackedWidget_contents->setCurrentWidget(ui->page_fanscounts);
}

void DataAnalysis::handleSignalsAndSlots()
{
    connect(m_buttonGroup,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton *button){
        if(button->objectName() == QString(u8"pushButton_fanscount"))
        {
            ui->stackedWidget_contents->setCurrentWidget(ui->page_fanscounts);

        }
        else if(button->objectName() == QString(u8"pushButton_playcount"))
        {
            ui->stackedWidget_contents->setCurrentWidget(ui->page_playcounts);
        }
        else if(button->objectName() == QString(u8"pushButton_likecount"))
        {
            ui->stackedWidget_contents->setCurrentWidget(ui->page_likecounts);
        }
        else if(button->objectName() == QString(u8"pushButton_collectcount"))
        {
            ui->stackedWidget_contents->setCurrentWidget(ui->page_colcounts);
        }
    });
}

void DataAnalysis::setInstallEventer()
{

}
