#include "DramaListForm.h"
#include "ui_DramaListForm.h"

DramaListForm::DramaListForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DramaListForm)
{
    ui->setupUi(this);  
    initWorkUI();
    chandleSignalsAndSLots();
}

DramaListForm::~DramaListForm()
{
    delete ui;
}

/*初始化界面*/
void DramaListForm::initWorkUI()
{
    this->setFixedWidth(260);
    ui->listWidget_darma->setViewMode(QListView::IconMode);//显示模式 图标模式
    ui->listWidget_darma->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_darma->setIconSize(QSize(80,80));//icon 大小
    ui->listWidget_darma->setGridSize( QSize(150, 150));//网格大小
    ui->listWidget_darma->setResizeMode(QListWidget::Adjust);//图标的调整模式，默认是固定的

    ui->pushButton_introduce->setFlat(true);
    ui->pushButton_start1->setFlat(true);
    ui->pushButton_start2->setFlat(true);
    ui->pushButton_start3->setFlat(true);
    ui->pushButton_start4->setFlat(true);
    ui->pushButton_start5->setFlat(true);

}

/*处理信号与槽函数*/
void DramaListForm::chandleSignalsAndSLots()
{

}

void DramaListForm::setDramaName(QString name)
{
    ui->label_dramaname->setText(name);
}

void DramaListForm::setDramaCommentGrade(double grade)
{
    ui->label_grade->setText(grade + QString::fromLocal8Bit("分"));
}

void DramaListForm::setDramaSetCounts(int count)
{
    ui->label_dramacount->setText(count + QString::fromLocal8Bit("集"));
}

void DramaListForm::setDramaPlayCounts(int count)
{
    ui->label_playcount->setText(count + QString::fromLocal8Bit("次"));
}

void DramaListForm::setCommentCheckabelCounts(int num)
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

void DramaListForm::setCommentStarts(int starts)
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
