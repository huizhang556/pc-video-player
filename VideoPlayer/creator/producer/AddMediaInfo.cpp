#include "AddMediaInfo.h"
#include "ui_AddMediaInfo.h"

AddMediaInfo::AddMediaInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddMediaInfo)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(300,145);
    initWorkUI();
    handleSignalsAndSLots();
}

AddMediaInfo::~AddMediaInfo()
{
    qDebug() << QString(u8"析构了");
    delete ui;
}

void AddMediaInfo::initWorkUI()
{

}

void AddMediaInfo::handleSignalsAndSLots()
{
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){close();});
    connect(ui->pushButton_add,&QPushButton::clicked,[=](){
        emit sig_addMediaText(ui->label_title_type->text().trimmed(),ui->lineEdit_type->text().trimmed());
        qDebug() << ui->label_title_type->text().trimmed() << ui->lineEdit_type->text().trimmed();
        QTimer::singleShot(1000,0,[=](){this->accept();});
    });
    connect(ui->pushButton_cancel,&QPushButton::clicked,[=](){this->reject();});
}

int AddMediaInfo::c_exec(const QString &title)
{
    ui->label_title_type->setText(title);
    return  this->exec();
}
