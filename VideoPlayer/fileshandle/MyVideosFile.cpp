#include "MyVideosFile.h"
#include "ui_MyVideosFile.h"

MyVideosFile::MyVideosFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyVideosFile)
{
    ui->setupUi(this);
}

MyVideosFile::~MyVideosFile()
{
    delete ui;
}
