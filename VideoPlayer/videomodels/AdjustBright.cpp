#include "AdjustBright.h"
#include "ui_AdjustBright.h"
#include <QPainter>
#include <QDebug>

AdjustBright::AdjustBright(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdjustBright)
{
    ui->setupUi(this);
    setFixedSize(385,310);//固定尺寸
//    setFixedSize(300,245);
    ui->widget_grid->setContentsMargins(5,5,5,5);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup | Qt::Tool | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);    //重要
    //屏幕占比没啥用，屏蔽
//    ui->label_hmbl->setVisible(false);
//    ui->checkBox_1->setVisible(false);
//    ui->checkBox_2->setVisible(false);
//    ui->checkBox_3->setVisible(false);
//    ui->checkBox_4->setVisible(false);

    ui->label_playSelect->setFixedSize(0,0);
    ui->radioButton_dcxh->setFixedSize(0,0);
    ui->radioButton_sjbf->setFixedSize(0,0);
    ui->radioButton_lbxh->setFixedSize(0,0);
    ui->radioButton_sxbf->setFixedSize(0,0);

    ui->BtnRate_1->setCheckable(true);//设置为可设置选中状态
    ui->BtnRate_2->setCheckable(true);
    ui->BtnRate_3->setCheckable(true);
    ui->BtnRate_4->setCheckable(true);
    ui->BtnRate_5->setCheckable(true);

    ui->BtnRate_2->setChecked(true);
    ui->radioButton_lbxh->setChecked(true);
    ui->checkBox_4->setChecked(true);

    ui->horizontalSlider_liangdu->setRange(0,100);
    ui->horizontalSlider_liangdu->setValue(10);
    ui->label_liangdu->setText(QString::fromLocal8Bit("10%"));
    ui->horizontalSlider_duibidu->setRange(0,100);
    ui->horizontalSlider_duibidu->setValue(10);
    ui->label_duibidu->setText(QString::fromLocal8Bit("10%"));
    ui->horizontalSlider_baohedu->setRange(0,100);
    ui->horizontalSlider_baohedu->setValue(10);
    ui->label_baohedu->setText(QString::fromLocal8Bit("10%"));
    ui->horizontalSlider_sediao->setRange(0,100);
    ui->horizontalSlider_sediao->setValue(10);
    ui->label_sediao->setText(QString::fromLocal8Bit("10%"));

    connect(ui->horizontalSlider_liangdu,&QSlider::valueChanged,[=](int value)
    {
        emit valueChange_liangdu(value);
        ui->label_liangdu->setText(QString::number(value)+"%");
        qDebug()<<"send:valueChange_liangdu ="<<value;
    });//亮度

    connect(ui->horizontalSlider_duibidu,&QSlider::valueChanged,[=](int value)
    {
        emit valueChange_duibidu(value);
        ui->label_duibidu->setText(QString::number(value)+"%");
        qDebug()<<"send:valueChange_duibidu ="<<value;
    });//对比度

    connect(ui->horizontalSlider_baohedu,&QSlider::valueChanged,[=](int value)
    {
        emit valueChange_baohedu(value);
        ui->label_baohedu->setText(QString::number(value)+"%");
        qDebug()<<"send:valueChange_baohedu ="<<value;
    });//饱和度
    connect(ui->horizontalSlider_sediao,&QSlider::valueChanged,[=](int value)
    {
        emit valueChange_sediao(value);
        ui->label_sediao->setText(QString::number(value)+"%");
        qDebug()<<"send:valueChange_sediao ="<<value;
    });//色调

    //播放速率
    connect(ui->BtnRate_1,SIGNAL(clicked(bool)),this,SLOT(setPlayRate()));
    connect(ui->BtnRate_2,SIGNAL(clicked(bool)),this,SLOT(setPlayRate()));
    connect(ui->BtnRate_3,SIGNAL(clicked(bool)),this,SLOT(setPlayRate()));
    connect(ui->BtnRate_4,SIGNAL(clicked(bool)),this,SLOT(setPlayRate()));
    connect(ui->BtnRate_5,SIGNAL(clicked(bool)),this,SLOT(setPlayRate()));

    connect(ui->BtnRate_1,SIGNAL(clicked(bool)),this,SLOT(selectPlayRate()));
    connect(ui->BtnRate_2,SIGNAL(clicked(bool)),this,SLOT(selectPlayRate()));
    connect(ui->BtnRate_3,SIGNAL(clicked(bool)),this,SLOT(selectPlayRate()));
    connect(ui->BtnRate_4,SIGNAL(clicked(bool)),this,SLOT(selectPlayRate()));
    connect(ui->BtnRate_5,SIGNAL(clicked(bool)),this,SLOT(selectPlayRate()));

    //播放模式
//    connect(ui->radioButton_dcxh,SIGNAL(clicked(bool)),this,SLOT(selectPlaybackMode()));
//    connect(ui->radioButton_sjbf,SIGNAL(clicked(bool)),this,SLOT(selectPlaybackMode()));
//    connect(ui->radioButton_lbxh,SIGNAL(clicked(bool)),this,SLOT(selectPlaybackMode()));
//    connect(ui->radioButton_sxbf,SIGNAL(clicked(bool)),this,SLOT(selectPlaybackMode()));

    //屏幕占比
    connect(ui->checkBox_1,SIGNAL(clicked(bool)),this,SLOT(setAspectRatioMode()));
    connect(ui->checkBox_2,SIGNAL(clicked(bool)),this,SLOT(setAspectRatioMode()));
    connect(ui->checkBox_3,SIGNAL(clicked(bool)),this,SLOT(setAspectRatioMode()));
    connect(ui->checkBox_4,SIGNAL(clicked(bool)),this,SLOT(setAspectRatioMode()));
    connect(ui->checkBox_1,SIGNAL(clicked(bool)),this,SLOT(selectaspectRatioMode()));
    connect(ui->checkBox_2,SIGNAL(clicked(bool)),this,SLOT(selectaspectRatioMode()));
    connect(ui->checkBox_3,SIGNAL(clicked(bool)),this,SLOT(selectaspectRatioMode()));
    connect(ui->checkBox_4,SIGNAL(clicked(bool)),this,SLOT(selectaspectRatioMode()));


}

AdjustBright::~AdjustBright()
{
    delete ui;
}

void AdjustBright::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/icon/mainback1.png"));
}

void AdjustBright::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->close();
}

//亮度
void AdjustBright::slot_setProgressBarValue_brightness(int value)
{
    ui->horizontalSlider_liangdu->setValue(value);
}

//对比度
void AdjustBright::slot_setProgressBarValue_contrast(int value)
{
    ui->horizontalSlider_duibidu->setValue(value);
}

//饱和度
void AdjustBright::slot_setProgressBarValue_saturation(int value)
{
    ui->horizontalSlider_baohedu->setValue(value);
}

//色相
void AdjustBright::slot_setProgressBarValue_hue(int value)
{
    ui->horizontalSlider_sediao->setValue(value);
}

void AdjustBright::clearAllRateButtonChecked()
{
    ui->BtnRate_1->setChecked(false);//设置为为未选中状态
    ui->BtnRate_2->setChecked(false);
    ui->BtnRate_3->setChecked(false);
    ui->BtnRate_4->setChecked(false);
    ui->BtnRate_5->setChecked(false);
}

void AdjustBright::clearAllCheckBoxChecked()
{
    ui->checkBox_1->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
}

void AdjustBright::setAspectRatioMode()
{
    QCheckBox *pButton = qobject_cast<QCheckBox*>(sender());
    clearAllCheckBoxChecked();
    pButton->setChecked(true);
}

void AdjustBright::setPlayRate()
{
    //lambda表达式不能使用强转，只能使用普通的信号与槽函数连接
    QPushButton *pButton = qobject_cast<QPushButton*>(sender());
    clearAllRateButtonChecked();//先取消所有按钮选中状态
    pButton->setChecked(true);//然后再单独设置状态
    //    qDebug()<<pButton->objectName();
}

/*判断播放速率并向视频界面发射调节速率信号*/
void AdjustBright::selectPlayRate()
{
    qreal rate = 0.0;
    QPushButton *pButton = qobject_cast<QPushButton*>(sender());
    qDebug()<<pButton->objectName();
    if(pButton->objectName() == "BtnRate_1")
    {
        rate = 0.5;
    }
    else if(pButton->objectName() == "BtnRate_2")
    {
        rate = 1.0;
    }
    else if(pButton->objectName() == "BtnRate_3")
    {
        rate = 1.25;
    }
    else if(pButton->objectName() == "BtnRate_4")
    {
        rate = 2.0;
    }
    else if(pButton->objectName() == "BtnRate_5")
    {
        rate = 0.75;
    }
    emit valueChange_playRate(rate);
    qDebug()<<"valueChange_playRate ="<<rate;
}

/*判断播放模式并向视频界面发射调节模式信号*/
void AdjustBright::selectPlaybackMode()
{
//    int mode = 0;
//    QRadioButton *pButton = qobject_cast<QRadioButton*>(sender());
//    if(pButton->objectName() == "radioButton_dcxh")
//    {
//        mode = 0;//单次播放
//    }
//    else if(pButton->objectName() == "radioButton_lbxh")
//    {
//        mode = 1;//列表循环
//    }
//    else if(pButton->objectName() == "radioButton_sjbf")
//    {
//        mode = 2;//随机播放
//    }
//    else if(pButton->objectName() == "radioButton_sxbf")
//    {
//        mode = 3;//顺序播放
//    }
//    emit valueChange_playBackMode(mode);
//    qDebug()<<"valueChange_playBackMode ="<<mode;
}

/*判断屏幕占比并向视频界面发送调节信号*/
void AdjustBright::selectaspectRatioMode()
{
    int aspect = 0;
    QCheckBox *pButton = qobject_cast<QCheckBox*>(sender());
    if(pButton->objectName() == "checkBox_1")
    {
        aspect = 0;//4:3
    }
    else if(pButton->objectName() == "checkBox_2")
    {
        aspect = 1;//16:9
    }
    else if(pButton->objectName() == "checkBox_3")
    {
        aspect = 2;//正常
    }
    else if(pButton->objectName() == "checkBox_4")
    {
        aspect = 3;//铺满
    }
    emit valueChange_aspectRatio(aspect);
    qDebug()<<"valueChange_aspectRatio"<<aspect;
}

void AdjustBright::updatePlayRate()
{
    clearAllRateButtonChecked();
    ui->BtnRate_2->setChecked(true);
    ui->horizontalSlider_baohedu->setValue(10);
    ui->horizontalSlider_duibidu->setValue(10);
    ui->horizontalSlider_liangdu->setValue(10);
    ui->horizontalSlider_sediao->setValue(10);
}




