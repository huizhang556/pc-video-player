#include "MyPicFile.h"
#include "ui_MyPicFile.h"

MyPicFile::MyPicFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyPicFile)
{
    ui->setupUi(this);
}

MyPicFile::~MyPicFile()
{
    delete ui;
}
