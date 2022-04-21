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
}

/*处理信号与槽函数*/
void DramaListForm::chandleSignalsAndSLots()
{

}
