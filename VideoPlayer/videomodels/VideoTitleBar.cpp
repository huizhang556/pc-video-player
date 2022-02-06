#include "VideoTitleBar.h"
#include "ui_VideoTitleBar.h"

VideoTitleBar::VideoTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoTitleBar)
{
    ui->setupUi(this);
    this->setFixedHeight(58);
    ui->pushButton_close->setFlat(true);
    ui->pushButton_min->setFlat(true);
    //关闭按钮
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){emit sig_winVClose();});
    //还原按钮
    connect(ui->pushButton_normal,&QPushButton::clicked,[=](){emit sig_winVRestore();});
    //最小化按钮
    connect(ui->pushButton_min,&QPushButton::clicked,[=](){emit sig_winVMinimum();});
    //返回主界面按钮
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){emit sig_winVMinimum();});
}

VideoTitleBar::~VideoTitleBar()
{
    delete ui;
}

/*设置当前标题*/
void VideoTitleBar::setTitleText(const QString &text)
{
    ui->label_title->setText(text);
}

void VideoTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit sig_doubleClick();
}

/*处理样式*/
void VideoTitleBar::chandleVMainWinStatus(bool status)
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
