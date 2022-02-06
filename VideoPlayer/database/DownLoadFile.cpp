#include "DownLoadFile.h"
#include "ui_DownLoadFile.h"

DownLoadFile::DownLoadFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DownLoadFile)
{
    ui->setupUi(this);
}

DownLoadFile::~DownLoadFile()
{
    delete ui;
}
