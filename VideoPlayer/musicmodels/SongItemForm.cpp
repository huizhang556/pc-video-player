#include "SongItemForm.h"
#include "ui_SongItemForm.h"
#include <QDebug>

SongItemForm::SongItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SongItemForm)
{
    ui->setupUi(this);
}

SongItemForm::SongItemForm(QString num, QString son_name, bool col, QString songer, QString zhuanji, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SongItemForm)
{
    ui->setupUi(this);
    ui->label_order->setText(num);
    ui->pushButton_son_name->setText(son_name);
    slot_setSongCollectStatus(col);
    ui->pushButton_songer->setText(songer);
    ui->pushButton_zhuanji->setText(zhuanji);

//    ui->pushButton_son_collect->setAttribute(Qt::WA_TransparentForMouseEvents,true);//设置鼠标穿透
//    ui->pushButton_son_download->setAttribute(Qt::WA_TransparentForMouseEvents,true);//设置鼠标穿透
//    ui->pushButton_son_delete->setAttribute(Qt::WA_TransparentForMouseEvents,true);//设置鼠标穿透

    connect(ui->pushButton_son_collect,&QPushButton::clicked,[=](){
        emit on_son_collectbtn_clicked(ui->label_order->text().toInt());
        qDebug() << "clicked collectbtn" << ui->label_order->text().toInt();
    });

    connect(ui->pushButton_son_download,&QPushButton::clicked,[=](){
        emit on_son_downloadbtn_clicked(ui->label_order->text().toInt());
        qDebug() << "clicked downloadbtn"<< ui->label_order->text().toInt();
    });

    connect(ui->pushButton_son_delete,&QPushButton::clicked,[=](){
        emit on_son_deletebtn_clicked(ui->label_order->text().toInt());
        qDebug() << "clicked deletebtn"<< ui->label_order->text().toInt();
    });

    connect(ui->pushButton_son_more,&QPushButton::clicked,[=](){
        emit on_son_morebtn_clicked(ui->label_order->text().toInt());
        qDebug() << "clicked morebtn"<< ui->label_order->text().toInt();
    });
}

SongItemForm::~SongItemForm()
{
    delete ui;
}

void SongItemForm::slot_setSongCollectStatus(bool status)
{
    if(status)
    {
        ui->pushButton_son_collect->setCheckable(true);
    }
    else
    {
        ui->pushButton_son_collect->setCheckable(false);
    }
}
