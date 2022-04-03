#include "PersonFileForm.h"
#include "ui_PersonFileForm.h"
#include <QDebug>

PersonFileForm::PersonFileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonFileForm)
{
    ui->setupUi(this);
    chandleSignalsAndSLots();
}

PersonFileForm::~PersonFileForm()
{
    delete ui;
}

void PersonFileForm::chandleSignalsAndSLots()
{
    //返回页
    connect(ui->pushButton_returnpage,&QPushButton::clicked,[=](){});
    //看过---全部历史
    connect(ui->pushButton_his_all,&QPushButton::clicked,[=](){ ui->stackedWidget_history->setCurrentIndex(0);});
    //看过---本地视频
    connect(ui->pushButton_his_localfile,&QPushButton::clicked,[=](){ ui->stackedWidget_history->setCurrentIndex(1);});
    //看过---选择文件
    connect(ui->pushButton_his_select,&QPushButton::clicked,[=](){qDebug() << "HIS_SELECT_FILES"; });
}
