#include "WebMessageBox.h"
#include "ui_WebMessageBox.h"

WebMessageBox::WebMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WebMessageBox)
{
    ui->setupUi(this);
    this->setFixedSize(400,450);
    setWindowFlags(Qt::FramelessWindowHint);
    chandleSignalsAndSLots();
}

WebMessageBox::~WebMessageBox()
{
    delete ui;
}

void WebMessageBox::chandleSignalsAndSLots()
{
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){this->hide();});
}
