#include "muteDialog.h"
#include "ui_muteDialog.h"
#include <QDebug>

muteDialog::muteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::muteDialog)
{
    ui->setupUi(this);
    this->setFixedSize(40,170);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    ui->verticalSlider->setRange(0,100);
    ui->verticalSlider->setPageStep(5);
    ui->verticalSlider->setValue(10);
    ui->label_mute->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->label_mute->setText(QString::fromLocal8Bit("10%"));
    //值改变发出带参数信号
    connect(ui->verticalSlider,&QSlider::valueChanged,[=](int val){
        emit sig_SpliderValueChange(val);//player设置声音
    ui->label_mute->setText(QString::number(val)+QString::fromLocal8Bit("%"));
    });
}

muteDialog::~muteDialog()
{
    delete ui;
}

void muteDialog::setSpliderValue(int value)
{
    ui->verticalSlider->setValue(value);
}

int muteDialog::getSpliderValue()
{
    return ui->verticalSlider->value();
}

void muteDialog::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "voice ui leave";
    this->close();

}

