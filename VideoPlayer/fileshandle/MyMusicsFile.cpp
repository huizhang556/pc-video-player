#include "MyMusicsFile.h"
#include "ui_MyMusicsFile.h"

MyMusicsFile::MyMusicsFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyMusicsFile)
{
    ui->setupUi(this);
}

MyMusicsFile::~MyMusicsFile()
{
    delete ui;
}
