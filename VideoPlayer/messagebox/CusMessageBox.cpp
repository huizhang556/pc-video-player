#include "CusMessageBox.h"
#include "ui_CusMessageBox.h"

CusMessageBox::CusMessageBox(QWidget *parent) :
    QMessageBox(parent),
    ui(new Ui::CusMessageBox)
{
    ui->setupUi(this);
}

CusMessageBox::CusMessageBox(QString title, QString prompt, QWidget *parent):
    QMessageBox(parent),
    ui(new Ui::CusMessageBox)
{
    ui->setupUi(this);
}


CusMessageBox::~CusMessageBox()
{
    delete ui;
}
