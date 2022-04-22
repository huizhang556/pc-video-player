#include "VideoTitleBar.h"
#include "ui_VideoTitleBar.h"
#include <QDebug>

VideoTitleBar::VideoTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoTitleBar)
{
    ui->setupUi(this);
    initUi();//初始化代码层面界面
    chandleSignalsAndSlots();//处理信号与槽函数
}

VideoTitleBar::~VideoTitleBar()
{
    delete ui;
}

void VideoTitleBar::initUi()
{
    this->setFixedHeight(55);
    setTitleStackWidgetPage(0);
    ui->pushButton_close->setFlat(true);
    ui->pushButton_min->setFlat(true);
    ui->lineEdit_url->setPlaceholderText(QString::fromLocal8Bit("请输入网络资源地址"));
}

void VideoTitleBar::chandleSignalsAndSlots()
{
    //关闭按钮
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){emit sig_winVClose();});
    //还原按钮
    connect(ui->pushButton_normal,&QPushButton::clicked,[=](){emit sig_winVRestore();});
    //最小化按钮
    connect(ui->pushButton_min,&QPushButton::clicked,[=](){emit sig_winVMinimum();});
    //返回主界面按钮
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){emit sig_winVMinimum();});
    //清除标题文字
    connect(this,&VideoTitleBar::sig_winVClose,this,&VideoTitleBar::clearTitleText);
    //发送输入的视频地址
    connect(ui->lineEdit_url,&QLineEdit::returnPressed,[=]()
    {
        QString input = ui->lineEdit_url->text().trimmed();//去除两端的空格
        emit sig_inputSourceUrl(input);
    });
}

/*设置标题栏*/
void VideoTitleBar::setTitleStackWidgetPage(int index)
{
    qDebug() << "now is web url lineedit";
    if(index == 0)//显示媒体标题
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(index == 1)//输入网址
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

/*设置当前标题*/
void VideoTitleBar::setTitleText(const QString &text)
{
    ui->label_title->setText(QString::fromLocal8Bit("正在播放：")+text);
}

/*清除标题栏*/
void VideoTitleBar::clearTitleText()
{
    ui->label_title->clear();
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
                                             "border-image: url(:/images/icon/normal.png);}"
                                             "QPushButton:hover{"
                                             "border: 1px solid #3C80B1;"
                                             "border-image: url(:/images/icon/normalhover.png);}");
    }
    else
    {
        ui->pushButton_normal->setStyleSheet("QPushButton{"
                                             "background-color: transparent;"
                                             "border-image: url(:/images/icon/normalmax.png);}"
                                             "QPushButton:hover{"
                                             "border: 1px solid #3C80B1;"
                                             "border-image: url(:/images/icon/normalmaxhover.png);}");
    }
}
