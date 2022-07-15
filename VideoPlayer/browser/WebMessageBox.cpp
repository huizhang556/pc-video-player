#include "WebMessageBox.h"
#include "ui_WebMessageBox.h"

WebMessageBox::WebMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WebMessageBox)
{
    ui->setupUi(this);
    this->setFixedSize(400,500);
}

WebMessageBox::~WebMessageBox()
{
    delete ui;
}
