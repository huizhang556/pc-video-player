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
    ui->label_order->setText(addPrefixNum(num));
    ui->pushButton_son_name->setText(son_name);
    slot_setSongCollectStatus(col);
    ui->pushButton_songer->setText(songer);
    ui->pushButton_zhuanji->setText(zhuanji);

//    ui->pushButton_son_collect->setAttribute(Qt::WA_TransparentForMouseEvents,true);//设置鼠标穿透
//    ui->pushButton_son_download->setAttribute(Qt::WA_TransparentForMouseEvents,true);//设置鼠标穿透
//    ui->pushButton_son_delete->setAttribute(Qt::WA_TransparentForMouseEvents,true);//设置鼠标穿透

    ui->pushButton_son_collect->setFixedSize(21,21);
    ui->pushButton_son_collect->setCheckable(true);
    ui->pushButton_son_collect->setChecked(false);
    ui->pushButton_son_download->setFixedSize(21,21);
    ui->pushButton_son_delete->setFixedSize(21,21);
    ui->pushButton_son_more->setFixedSize(21,21);
    ui->pushButton_son_mv->setFixedSize(21,21);

    //播放按钮
//    connect(ui->pushButton_son_name,&QPushButton::clicked,[=](){
//        emit sig_son_playbtn_clicked(ui->label_order->text().toInt());
//        slot_printSenderName();
//        qDebug() <<  ui->pushButton_son_name->objectName();
//        qDebug() << "clicked playbtn" << ui->label_order->text().toInt();
//        qDebug() << ui->pushButton_son_name->parentWidget()->parentWidget()->parentWidget()->objectName();
//    });

    //MV播放按钮
    connect(ui->pushButton_son_mv,&QPushButton::clicked,[=](){
        emit sig_son_mvbtn_clicked(ui->label_order->text().toInt());
        slot_printSenderName();
        qDebug() << "clicked MVbtn" << ui->label_order->text().toInt();
        qDebug() << ui->pushButton_son_mv->parentWidget()->parentWidget()->parentWidget()->objectName();
    });
    //收藏按钮
    connect(ui->pushButton_son_collect,&QPushButton::clicked,[=](){
        emit sig_son_collectbtn_clicked(ui->label_order->text().toInt());
        slot_printSenderName();
        qDebug() << "clicked collectbtn" << ui->label_order->text().toInt();
        qDebug() << ui->pushButton_son_collect->parentWidget()->parentWidget()->parentWidget()->objectName();
        if(ui->pushButton_son_collect->isChecked())
        {
            ui->pushButton_son_collect->setStyleSheet("QPushButton{"
                                                      "border-image: url(:/images/icon/play_collect_unchecked.png);"
                                                      "}");
        }
        else
        {
            ui->pushButton_son_collect->setStyleSheet("QPushButton{"
                                                      "border-image: url(:/images/icon/play_collect_checked.png);"
                                                      "}");
        }
    });
    //下载按钮
    connect(ui->pushButton_son_download,&QPushButton::clicked,[=](){
        emit sig_son_downloadbtn_clicked(ui->label_order->text().toInt());
        slot_printSenderName();
        qDebug() << "clicked downloadbtn"<< ui->label_order->text().toInt();
        qDebug() << ui->pushButton_son_download->parentWidget()->parentWidget()->parentWidget()->objectName();
    });
    //删除按钮
    connect(ui->pushButton_son_delete,&QPushButton::clicked,[=](){
        emit sig_son_deletebtn_clicked(ui->label_order->text().toInt());
        slot_printSenderName();
        qDebug() << "clicked deletebtn"<< ui->label_order->text().toInt();
        qDebug() << ui->pushButton_son_delete->parentWidget()->parentWidget()->parentWidget()->objectName();
    });
    //更多信息按钮
    connect(ui->pushButton_son_more,&QPushButton::clicked,[=](){
        emit sig_son_morebtn_clicked(ui->label_order->text().toInt());
        slot_printSenderName();
        qDebug() << "clicked morebtn"<< ui->label_order->text().toInt();
        qDebug() << ui->pushButton_son_more->parentWidget()->parentWidget()->parentWidget()->objectName();
    });
    //音质按钮
    connect(ui->pushButton_yinzhi,&QPushButton::clicked,[=](){
        emit sig_son_qualityBtn_clicked(ui->label_order->text().toInt());
        slot_printSenderName();
        qDebug() << "clicked qualitybtn"<< ui->label_order->text().toInt();
        qDebug() << ui->pushButton_yinzhi->parentWidget()->parentWidget()->objectName();
    });
}

SongItemForm::~SongItemForm()
{
    delete ui;
}

QString SongItemForm::addPrefixNum(QString num)
{
    if(num.length() == 1)
    {
        return QString::fromLocal8Bit("00")+num;
    }
    else if(num.length() == 2)
    {
        return QString::fromLocal8Bit("0")+num;
    }
    else
    {
        return num;
    }
}


void SongItemForm::enterEvent(QEvent *event)
{
    Q_UNUSED(event);
//    ui->frame_make->show();
}

void SongItemForm::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
//    ui->frame_make->hide();
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

void SongItemForm::slot_printSenderName()
{
//    QPushButton *btn = qobject_cast<QPushButton*>(sender());
//    qDebug() << btn->objectName();
}
