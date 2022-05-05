#include "CusFileDialog.h"
#include "ui_CusFileDialog.h"

CusFileDialog::CusFileDialog(QWidget *parent) :
    QFileDialog(parent),
    ui(new Ui::CusFileDialog)
{
    ui->setupUi(this);
    initWorkUI();
    chandleSignalsAndSLots();
}

CusFileDialog::~CusFileDialog()
{
    delete ui;
}

void CusFileDialog::initWorkUI()
{
//    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setMinimumSize(700,420);
    this->setWindowTitle(QString::fromLocal8Bit(" 选择文件"));
    this->setLabelText(QFileDialog::LookIn,QString::fromLocal8Bit("选择目录"));
    this->setLabelText(QFileDialog::FileName,QString::fromLocal8Bit("文件名:"));
    this->setLabelText(QFileDialog::FileType,QString::fromLocal8Bit("文件类型:"));
    this->setLabelText(QFileDialog::Accept,QString::fromLocal8Bit("打开"));
    this->setLabelText(QFileDialog::Reject,QString::fromLocal8Bit("取消"));
}

void CusFileDialog::chandleSignalsAndSLots()
{
    connect(this,&CusFileDialog::currentChanged,[=](){
        this->setLabelText(QFileDialog::Accept,QString::fromLocal8Bit("打开"));
    });
}
