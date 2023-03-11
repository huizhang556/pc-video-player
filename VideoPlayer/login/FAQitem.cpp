#include "FAQitem.h"
#include "ui_FAQitem.h"

FAQitem::FAQitem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FAQitem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

FAQitem::FAQitem(const QString &title, const QString &content, QWidget *parent):
    QWidget(parent),
    ui(new Ui::FAQitem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    ui->pushButton_title->setText(title);
    ui->plainTextEdit->appendPlainText(content);

}

FAQitem::~FAQitem()
{
    delete ui;
}

void FAQitem::initWorkUI()
{
    setMinimumHeight(36);
    setMaximumSize(300,330);
    ui->pushButton_indicator->setCheckable(true);
    ui->pushButton_indicator->setChecked(false);//默认是关闭的
    ui->plainTextEdit->hide();
    ui->plainTextEdit->setContextMenuPolicy(Qt::NoContextMenu);
    ui->plainTextEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->plainTextEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void FAQitem::handleSignalsAndSlots()
{
    connect(ui->pushButton_title,&QPushButton::clicked,[=](){
        ui->pushButton_indicator->click();
    });

    connect(ui->pushButton_indicator,&QPushButton::clicked,[=](bool checked){
        if(checked)
        {
            ui->plainTextEdit->show();
            this->setFixedHeight(335);
        }
        else
        {
            ui->plainTextEdit->hide();
            this->setFixedHeight(36);
        }
        m_open = checked;
        emit sig_item_expand(checked);
    });
}

void FAQitem::setFoldItem()
{
    ui->plainTextEdit->hide();
    this->setFixedHeight(36);
}

void FAQitem::setShowItem()
{
    ui->plainTextEdit->show();
    this->setFixedHeight(335);
}
