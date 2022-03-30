#include "RecomVideoTab.h"
#include "ui_RecomVideoTab.h"
#include <QDebug>

RecomVideoTab::RecomVideoTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecomVideoTab),
    m_turnOnStatus(false)
{
    ui->setupUi(this);
    this->setFixedWidth(260);
    connect(ui->Btn_turn,&QPushButton::clicked,this,&RecomVideoTab::slots_switchTurn);
}

RecomVideoTab::~RecomVideoTab()
{
    delete ui;
}

void RecomVideoTab::slots_switchTurn()
{
    if(!m_turnOnStatus)
    {
        qDebug() << "!m_turnOnStatus";
        ui->Btn_turn->setStyleSheet("#Btn_turn{"
                                           "border-image: url(:/images/icon/turn_on.png);"
                                           "}");
    }
    else
    {
        qDebug() << "m_turnOnStatus";
        ui->Btn_turn->setStyleSheet("#Btn_turn{"
                                           "border-image: url(:/images/icon/turn_off.png);"
                                           "}");
    }
    m_turnOnStatus = !m_turnOnStatus;
}

