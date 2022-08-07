#include "WebMessageBox.h"
#include "ui_WebMessageBox.h"

WebMessageBox::WebMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WebMessageBox)
{
    ui->setupUi(this);
    this->setFixedSize(520,465);
    setWindowFlags(Qt::FramelessWindowHint);
    initWorkUI();
    chandleSignalsAndSLots();
}

WebMessageBox::~WebMessageBox()
{
    delete ui;
}

void WebMessageBox::initWorkUI()
{
    ui->checkBox_addCollect->setText(QString::fromLocal8Bit("将本条收藏固定到快捷收藏栏"));
}

void WebMessageBox::chandleSignalsAndSLots()
{
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){this->hide();});
}
