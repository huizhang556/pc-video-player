#include "MyDocFile.h"
#include "ui_MyDocFile.h"

MyDocFile::MyDocFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyDocFile)
{
    ui->setupUi(this);
}

MyDocFile::~MyDocFile()
{
    delete ui;
}
