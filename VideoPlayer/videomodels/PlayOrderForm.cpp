#include "PlayOrderForm.h"
#include "ui_PlayOrderForm.h"
#include <QButtonGroup>
#include <QDebug>

PlayOrderForm::PlayOrderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayOrderForm)
{
    ui->setupUi(this);
    this->setFixedSize(114,138);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    initWorkUI();
    chandleSignalsAndSlots();
}

PlayOrderForm::~PlayOrderForm()
{
    delete ui;
}

void PlayOrderForm::initWorkUI()
{
    ui->pushButton_danqu->setFlat(true);
    ui->pushButton_xunhuan->setFlat(true);
    ui->pushButton_suiji->setFlat(true);
    ui->pushButton_shunxu->setFlat(true);

    ui->pushButton_danqu->setCheckable(true);
    ui->pushButton_xunhuan->setCheckable(true);
    ui->pushButton_suiji->setCheckable(true);
    ui->pushButton_shunxu->setCheckable(true);
    ui->pushButton_xunhuan->setChecked(true);//默认选中

//    QButtonGroup btnGroup;
//    btnGroup.addButton(ui->pushButton_danqu,0);
//    btnGroup.addButton(ui->pushButton_xunhuan,1);
//    btnGroup.addButton(ui->pushButton_suiji,2);
//    btnGroup.addButton(ui->pushButton_shunxu,3);
//    btnGroup.setExclusive(false);
}

void PlayOrderForm::chandleSignalsAndSlots()
{
    connect(ui->pushButton_danqu,&QPushButton::clicked,[=](){
        clearButtonCheckedStatus();
        setButtonChedkedStatus(1);
        emit sig_playerOrder(1);
        qDebug() << "emit sig_playerOrder(1);";
    });//单曲
    connect(ui->pushButton_xunhuan,&QPushButton::clicked,[=](){
        clearButtonCheckedStatus();
        setButtonChedkedStatus(3);
        emit sig_playerOrder(3);
        qDebug() << "emit sig_playerOrder(3);";
    });//循环
    connect(ui->pushButton_shunxu,&QPushButton::clicked,[=](){
        clearButtonCheckedStatus();
        setButtonChedkedStatus(2);
        emit sig_playerOrder(2);
        qDebug() << "emit sig_playerOrder(2);";
    });//顺序
    connect(ui->pushButton_suiji,&QPushButton::clicked,[=](){
        clearButtonCheckedStatus();
        setButtonChedkedStatus(4);
        emit sig_playerOrder(4);
        qDebug() << "emit sig_playerOrder(4);";
    });//随机
}

void PlayOrderForm::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->hide();
}


bool PlayOrderForm::clearButtonCheckedStatus()
{
    ui->pushButton_danqu->setChecked(false);
    ui->pushButton_xunhuan->setChecked(false);
    ui->pushButton_suiji->setChecked(false);
    ui->pushButton_shunxu->setChecked(false);
    return true;
}

/*设置选中状态*/
bool PlayOrderForm::setButtonChedkedStatus(int index)
{
    if(index == 1)
    {
        ui->pushButton_danqu->setChecked(true);
    }
    else if(index == 2)
    {
        ui->pushButton_shunxu->setChecked(true);
    }
    else if(index == 3)
    {
        ui->pushButton_xunhuan->setChecked(true);
    }
    else if(index == 4)
    {
        ui->pushButton_suiji->setChecked(true);
    }
    return true;
}
