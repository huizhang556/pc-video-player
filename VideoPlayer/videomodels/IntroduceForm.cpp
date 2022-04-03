#include "IntroduceForm.h"
#include "ui_IntroduceForm.h"

IntroduceForm::IntroduceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntroduceForm)
{
    ui->setupUi(this);
    this->setFixedSize(260,100);
    ui->pushButton_introduce->setFlat(true);
    ui->pushButton_start1->setFlat(true);
    ui->pushButton_start2->setFlat(true);
    ui->pushButton_start3->setFlat(true);
    ui->pushButton_start4->setFlat(true);
    ui->pushButton_start5->setFlat(true);



}

IntroduceForm::~IntroduceForm()
{
    delete ui;
}

void IntroduceForm::setDramaName(QString name)
{
    ui->label_dramaname->setText(name);
}

void IntroduceForm::setDramaCommentGrade(double grade)
{
    ui->label_grade->setText(grade + QString::fromLocal8Bit("分"));
}

void IntroduceForm::setDramaSetCounts(int count)
{
    ui->label_dramacount->setText(count + QString::fromLocal8Bit("集"));
}

void IntroduceForm::setDramaPlayCounts(int count)
{
    ui->label_playcount->setText(count + QString::fromLocal8Bit("次"));
}

void IntroduceForm::setCommentCheckabelCounts(int num)
{
    if(num <= 0)
    {
        ui->pushButton_start1->setCheckable(true);
        ui->pushButton_start2->setCheckable(true);
        ui->pushButton_start3->setCheckable(true);
        ui->pushButton_start4->setCheckable(true);
        ui->pushButton_start5->setCheckable(true);
    }
    else if(num == 1)
    {
        ui->pushButton_start1->setCheckable(true);
        ui->pushButton_start2->setCheckable(true);
        ui->pushButton_start3->setCheckable(true);
        ui->pushButton_start4->setCheckable(true);
    }
    else if(num == 3)
    {
        ui->pushButton_start1->setCheckable(true);
        ui->pushButton_start2->setCheckable(true);
        ui->pushButton_start3->setCheckable(true);
    }
    else if(num == 2)
    {
        ui->pushButton_start1->setCheckable(true);
        ui->pushButton_start2->setCheckable(true);
    }
    else if(num == 1)
    {
        ui->pushButton_start1->setCheckable(true);
    }
    else
    {
        return;
    }
}

void IntroduceForm::setCommentStarts(int starts)
{
    if(starts == 5)
    {
        ui->pushButton_start1->setChecked(true);
        ui->pushButton_start2->setChecked(true);
        ui->pushButton_start3->setChecked(true);
        ui->pushButton_start4->setChecked(true);
        ui->pushButton_start5->setChecked(true);
    }
    else if(starts == 4)
    {
        ui->pushButton_start1->setChecked(true);
        ui->pushButton_start2->setChecked(true);
        ui->pushButton_start3->setChecked(true);
        ui->pushButton_start4->setChecked(true);
    }
    else if(starts == 3)
    {
        ui->pushButton_start1->setChecked(true);
        ui->pushButton_start2->setChecked(true);
        ui->pushButton_start3->setChecked(true);
    }
    else if(starts == 2)
    {
        ui->pushButton_start1->setChecked(true);
        ui->pushButton_start2->setChecked(true);
    }
    else if(starts == 1)
    {
        ui->pushButton_start1->setChecked(true);
    }
    else
    {
        return;
    }
}
