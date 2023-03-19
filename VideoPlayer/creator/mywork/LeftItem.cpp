#include "LeftItem.h"
#include "ui_LeftItem.h"

LeftItem::LeftItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LeftItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
}

LeftItem::LeftItem(const QString &text, const int counts, QWidget *parent):
    QWidget(parent),
    ui(new Ui::LeftItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
    setItemText(text);
//    setItemCounts(counts);

}

LeftItem::~LeftItem()
{
    delete ui;
}

void LeftItem::initWorkUI()
{
    ui->label_counts->setText("");//默认什么都不显示
}

void LeftItem::handleSignalsAndSlots()
{
    connect(ui->pushButton_text,&QPushButton::clicked,[=](){
        ui->label_status->startRun();
        emit sig_item_selected(ui->pushButton_text->text());
        QTimer::singleShot(800,0,[=](){
            ui->label_status->stopRun();
        });
        qDebug() << QString(u8"已发出信号：")<< ui->pushButton_text->text();
    });
}

void LeftItem::setInstallEventer()
{

}

void LeftItem::setItemText(const QString &text)
{
    ui->pushButton_text->setText(text);
}

void LeftItem::setItemCounts(int counts)
{
//    if(counts == 0) return;
    ui->label_counts->setText(QString::number(counts));
}
