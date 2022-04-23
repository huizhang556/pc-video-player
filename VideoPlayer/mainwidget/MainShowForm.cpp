#include "MainShowForm.h"

MainShowForm::MainShowForm(QWidget *parent) :
    QWidget(parent)
{
    initWorkUI();
    chandleSignalsAndSlots();
}

MainShowForm::~MainShowForm()
{

}

void MainShowForm::initWorkUI()
{
    m_widget1 = new QWidget(this);
    m_widget1->setObjectName(QString::fromLocal8Bit("m_widget1"));

    m_tabWdgt = new QTabWidget(this);
    m_tabWdgt->setObjectName(QString::fromLocal8Bit("m_tabWdgt"));
    m_tabWdgt->setFixedHeight(300);

    m_picWidget = new PictureWidget();
    m_picWidget->setObjectName(QString::fromLocal8Bit("m_picWidget"));
    m_picWidget->setFixedHeight(260);

    m_vHlayout1 = new QVBoxLayout(this);
    m_vHlayout1->setObjectName(QString::fromLocal8Bit("m_vHlayout1"));

    m_tabWdgt->insertTab(0,m_picWidget,QString::fromLocal8Bit(""));

    m_vHlayout1->addWidget(m_tabWdgt);
    m_vHlayout1->addStretch();
    m_vHlayout1->setSpacing(0);
    m_vHlayout1->setContentsMargins(0,0,0,0);

    this->setLayout(m_vHlayout1);

}

void MainShowForm::chandleSignalsAndSlots()
{

}
