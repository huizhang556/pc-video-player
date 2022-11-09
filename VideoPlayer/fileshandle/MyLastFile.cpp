#include "MyLastFile.h"
#include "ui_MyLastFile.h"

MyLastFile::MyLastFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyLastFile)
{
    ui->setupUi(this);
}

MyLastFile::~MyLastFile()
{
    delete ui;
}
