#include "MiniRecordItem.h"
#include "ui_MiniRecordItem.h"

MiniRecordItem::MiniRecordItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiniRecordItem)
{
    ui->setupUi(this);
}

MiniRecordItem::MiniRecordItem(QString text, QIcon icon, QWidget *parent):
    QWidget(parent),
    m_record(text),
    m_icon(icon),
    ui(new Ui::MiniRecordItem)
{
    ui->setupUi(this);
    this->setFixedHeight(26);
    chandleSignalAndSLots();
    ui->pushButton_record->setText(text);
    ui->pushButton_record->setIcon(icon);
    ui->pushButton_change->setToolTip(QString::fromLocal8Bit("修改"));
    ui->pushButton_delete->setToolTip(QString::fromLocal8Bit("移除"));
}

MiniRecordItem::~MiniRecordItem()
{
    delete ui;
}

void MiniRecordItem::chandleSignalAndSLots()
{
    connect(ui->pushButton_record,&QPushButton::clicked,[=](){emit sig_item_record(ui->pushButton_record->text());});
    connect(ui->pushButton_change,&QPushButton::clicked,[=](){emit sig_item_modify(ui->pushButton_record->text());});
    connect(ui->pushButton_delete,&QPushButton::clicked,[=](){emit sig_item_delete();});
}
