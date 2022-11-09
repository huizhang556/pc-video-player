#include "MyAllFile.h"
#include "ui_MyAllFile.h"

MyAllFile::MyAllFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyAllFile)
{
    ui->setupUi(this);
    ui->treeWidget_allfiles->resize(QSize(215,500));
    ui->treeWidget_allfiles->setMinimumWidth(215);
    ui->treeWidget_allfiles->setMaximumWidth(280);
}

MyAllFile::~MyAllFile()
{
    delete ui;
}
