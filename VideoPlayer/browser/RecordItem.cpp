#include "RecordItem.h"
#include "ui_RecordItem.h"
#include <QDebug>

RecordItem::RecordItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordItem)
{
    ui->setupUi(this);
    this->setFixedHeight(26);
    handleSignalAndSLots();
}

RecordItem::RecordItem(int type, QIcon icon, QString text, QWidget *parent) :
    QWidget(parent),
    m_type(type),
    m_icon(icon),
    m_record(text),
    m_dateTime(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")),
    ui(new Ui::RecordItem)
{
    ui->setupUi(this);
    this->setFixedHeight(26);
    handleSignalAndSLots();
    ui->pushButton_record->setIcon(icon);
    ui->pushButton_record->setText(text);
    ui->label_time->setText(m_dateTime);
    ui->pushButton_modify->setText(QString::fromLocal8Bit("修改"));
    ui->pushButton_delete->setText(QString::fromLocal8Bit("删除"));
    judgeType();
}

RecordItem::~RecordItem()
{
    delete ui;
}

void RecordItem::handleSignalAndSLots()
{
    //
    connect(ui->pushButton_record,&QPushButton::clicked,[=](){
        emit sig_item_record(ui->pushButton_record->text());
        qDebug() << QString::fromLocal8Bit("点击获得的历史地址:")<< ui->pushButton_record->text();
    });
    //修改
    connect(ui->pushButton_modify,&QPushButton::clicked,[=](){ emit sig_item_modify(ui->pushButton_record->text(),ui->pushButton_modify); });
    //删除item
    connect(ui->pushButton_delete,&QPushButton::clicked,[=](){ emit sig_item_delete(); });
}

void RecordItem::slot_setRecordButtonText(QString text)
{
    ui->pushButton_record->setText(text);
}

void RecordItem::slot_setRecordCreatetime(const QString &time)
{
    ui->label_time->setText(time);
}

void RecordItem::judgeType()
{
    if(m_type == 0)//都不显示
    {
        ui->pushButton_delete->setHidden(true);
        ui->pushButton_modify->setHidden(true);
        ui->label_time->setHidden(true);
    }
    else if(m_type == 1)//只有一个按钮（删除）
    {
        ui->pushButton_delete->setHidden(false);
        ui->pushButton_modify->setHidden(true);
        ui->label_time->setHidden(true);
    }
    else if(m_type == 2)//有两个按钮
    {
        ui->pushButton_delete->setHidden(false);
        ui->pushButton_modify->setHidden(false);
        ui->label_time->setHidden(true);
    }
    else if(m_type == 3)//两个按钮+一个label
    {
        ui->pushButton_delete->setHidden(false);
        ui->pushButton_modify->setHidden(false);
        ui->label_time->setHidden(false);
    }
    else if(m_type == 4)//1个按钮+一个label
    {
        ui->pushButton_delete->setHidden(false);
        ui->pushButton_modify->setHidden(true);
        ui->label_time->setHidden(false);
    }
    else if(m_type == 6)//1个label
    {
        ui->pushButton_delete->setHidden(true);
        ui->pushButton_modify->setHidden(true);
        ui->label_time->setHidden(false);
    }
}
