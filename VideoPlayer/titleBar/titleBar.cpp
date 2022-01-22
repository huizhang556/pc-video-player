#include "TitleBar.h"
#include "ui_TitleBar.h"
#include <QDebug>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);
    this->setFixedHeight(50);
    //发送窗口关闭信号
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){emit sig_winClose();});
    //发送窗口还原信号
    connect(ui->pushButton_normal,&QPushButton::clicked,[=](){emit sig_winNormal();});
    //发送窗口最小化信号
    connect(ui->pushButton_min,&QPushButton::clicked,[=](){emit sig_winMinimum();});

}

TitleBar::~TitleBar()
{
    delete ui;
}

/*重写鼠标双击事件*/
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit sig_doubleClick();
}

/*根据窗口状态设置样式*/
void TitleBar::chandleMainWinStatus(bool status)
{
    if(!status)
    {
        ui->pushButton_normal->setStyleSheet("QPushButton{"
                                             "background-color: transparent;"
                                             "border-image: url(:/images/normal.png);}"
                                             "QPushButton:hover{"
                                             "border: 1px solid #3C80B1;"
                                             "border-image: url(:/images/normalhover.png);}");
    }
    else
    {
        ui->pushButton_normal->setStyleSheet("QPushButton{"
                                             "background-color: transparent;"
                                             "border-image: url(:/images/normalmax.png);}"
                                             "QPushButton:hover{"
                                             "border: 1px solid #3C80B1;"
                                             "border-image: url(:/images/normalmaxhover.png);}");
    }
}
