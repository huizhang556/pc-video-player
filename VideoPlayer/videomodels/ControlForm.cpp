#include "ControlForm.h"
#include "ui_ControlForm.h"
#include <QDebug>

ControlForm::ControlForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlForm)
{
    ui->setupUi(this);
    m_muteDlg = new muteDialog();
    m_muteDlg->setObjectName(QString::fromLocal8Bit("m_muteDlg"));
}

ControlForm::~ControlForm()
{
    delete ui;
}

void ControlForm::on_pushButton_sound_clicked()
{

    int x = this->mapToGlobal(ui->pushButton_sound->pos()+ui->stackedWidget_control->pos()+this->pos()).x();
    int y = this->mapToGlobal(ui->pushButton_sound->pos()+ui->stackedWidget_control->pos()+this->pos()).y();
    int h = m_muteDlg->height();
    qDebug() << "QPont_g(" << x << "," << y << ")";
    m_muteDlg->setGeometry(x-6,y-170-6,m_muteDlg->width(),m_muteDlg->height());
//    m_muteDlg->move(ui->pushButton_sound->pos());
    m_muteDlg->raise();
    m_muteDlg->show();

}
