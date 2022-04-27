#include "PlayCtlAdjustForm.h"
#include "ui_PlayCtlAdjustForm.h"
#include <QColor>
#include <QPalette>
#include <QGraphicsOpacityEffect>

PlayCtlAdjustForm::PlayCtlAdjustForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayCtlAdjustForm)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setFixedHeight(60);
//    QPalette myPalette;
//    QColor myColor(255,255,255);
//    myColor.setAlphaF(0.1);
//    myPalette.setBrush(backgroundRole(),myColor);
//    this->setPalette(myPalette);
//    this->setAutoFillBackground(true);
//    QGraphicsOpacityEffect *goe = new QGraphicsOpacityEffect();
//    this->setGraphicsEffect(goe);
//    goe->setOpacity(0.0);
    setAttribute(Qt::WA_TranslucentBackground, true);//背景透明
//    setWindowOpacity(0.2);//子控件内所有的透明度都会变（不好用）
}

PlayCtlAdjustForm::~PlayCtlAdjustForm()
{
    delete ui;
}
