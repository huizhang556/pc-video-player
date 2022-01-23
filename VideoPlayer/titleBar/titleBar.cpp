#include "TitleBar.h"
#include "ui_TitleBar.h"
#include <QDateTime>

#include <QDebug>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);
    this->setFixedHeight(50);
    initWorker();//初始化
    chandleSignalAndSLots();
}

TitleBar::~TitleBar()
{
    delete ui;
}

/*初始化工作*/
void TitleBar::initWorker()
{
    //LCD数字显示
    ui->lcdNumber->setDigitCount(20);//显示数量（个数）
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setPalette(Qt::red);//显示文字颜色，不怎么生效
    //初始化定时器
    m_timer1 = new QTimer(this);
    m_timer2 = new QTimer(this);
    m_timer3 = new QTimer(this);
    m_timer3->start(100);//0.1s更新发送一次时间,放在下面合适

    ui->pushButton_close->setFlat(true);
    setShowToolTip();//增加提示
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

/*槽函数 --- 获取系统时间并且显示*/
void TitleBar::getSystemTimeShow()
{
    QDateTime curtime = QDateTime::currentDateTime();
    QString strTime = curtime.toString("yyyy-MM-dd hh:mm:ss");
    ui->lcdNumber->display(strTime);
}

/*处理信号与槽函数*/
void TitleBar::chandleSignalAndSLots()
{
    //发送窗口关闭信号
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){emit sig_winClose();});
    //发送窗口还原信号
    connect(ui->pushButton_normal,&QPushButton::clicked,[=](){emit sig_winNormal();});
    //发送窗口最小化信号
    connect(ui->pushButton_min,&QPushButton::clicked,[=](){emit sig_winMinimum();});
    //更新时间
    connect(m_timer3,&QTimer::timeout,this,&TitleBar::getSystemTimeShow);
    //登录按钮触发
}

/*设置tooltip*/
void TitleBar::setShowToolTip()
{
    ui->Btn_logo->setToolTip(QString::fromLocal8Bit("转至网页"));
    ui->Btnhelp->setToolTip(QString::fromLocal8Bit("帮助"));
    ui->Btnlogin->setToolTip(QString::fromLocal8Bit("登录"));
    ui->Btnskin->setToolTip(QString::fromLocal8Bit("皮肤"));
    ui->BtnDownload->setToolTip(QString::fromLocal8Bit("云端"));
    ui->BtnHistory->setToolTip(QString::fromLocal8Bit("历史记录"));
    ui->BtnScreen->setToolTip(QString::fromLocal8Bit("截屏"));
}
