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

    m_picWidget = new PictureWidget();
    m_picWidget->setObjectName(QString::fromLocal8Bit("m_picWidget"));

    m_vHlayout1 = new QVBoxLayout(this);
    m_vHlayout1->setObjectName(QString::fromLocal8Bit("m_vHlayout1"));

    m_vHlayout1->addWidget(m_picWidget);
    m_vHlayout1->addStretch();
    m_vHlayout1->setSpacing(0);
    m_vHlayout1->setContentsMargins(0,0,0,0);

    this->setLayout(m_vHlayout1);


}

void MainShowForm::chandleSignalsAndSlots()
{

}
