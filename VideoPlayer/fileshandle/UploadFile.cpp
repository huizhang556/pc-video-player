#include "UploadFile.h"
#include "ui_UploadFile.h"

UploadFile::UploadFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UploadFile)
{
    ui->setupUi(this);
}

UploadFile::~UploadFile()
{
    delete ui;
}
