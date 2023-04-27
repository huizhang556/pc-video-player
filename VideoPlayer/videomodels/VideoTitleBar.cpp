#include "VideoTitleBar.h"
#include "ui_VideoTitleBar.h"

//#ifdef Q_OS_WIN
//#include <qt_windows.h>
//#pragma comment (lib,"user32.lib")
//#endif

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
    this->installEventFilter(this);
    this->setFixedHeight(40);
    setTitleStackWidgetPage(0);
    ui->pushButton_close->setFlat(true);
    ui->pushButton_min->setFlat(true);
    ui->lineEdit_url->setPlaceholderText(QString::fromLocal8Bit("请输入网络资源地址"));
    ui->pushButton_return->installEventFilter(this);
    ui->pushButton_return->setIcon(QIcon(":/images/icon/returnhome.png"));
    ui->pushButton_return->setText(QString::fromLocal8Bit("返回主界面"));
    //类型 + 文本 + 字体 + 字体颜色 + 间隔
    ui->label_title->initMoveText(MOVETYPE::FIFO,QString(u8""),QFont("Microsoft YaHei UI",13,75),QColor(30, 222, 3, 255),20);
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
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){emit sig_returnMainUi();});
    //清除标题文字
    connect(this,&VideoTitleBar::sig_winVClose,this,&VideoTitleBar::clearTitleText);
    //发送输入的视频地址
    connect(ui->lineEdit_url,&QLineEdit::returnPressed,[=]()
    {
        QString input = ui->lineEdit_url->text().trimmed();//去除两端的空格
        if(input.isEmpty()) return;
        emit sig_inputSourceUrl(input);
    });

    //下载
    connect(ui->pushButton_vdownload,&QPushButton::clicked,[=](){ emit sig_videodownload(); });
    //截图
    connect(ui->pushButton_grub,&QPushButton::clicked,[=](){ emit sig_videoCapture(); });
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
    if(text.isEmpty())
        return;
    ui->label_title->setText(QString::fromLocal8Bit("正在播放：")+text);
}


/*清除标题栏*/
void VideoTitleBar::clearTitleText()
{
    ui->label_title->clear();
    ui->label_title->setText("");
}

void VideoTitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(event->button() == Qt::LeftButton)
    emit sig_doubleClick();
}

bool VideoTitleBar::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->pushButton_return)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->pushButton_return->setIcon(QIcon(":/images/icon/returnhome_hover.png"));
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->pushButton_return->setIcon(QIcon(":/images/icon/returnhome.png"));
        }
    }

    if(watched == this && event->type() == QEvent::Enter)
    {
        this->setCursor(Qt::ArrowCursor);
    }
    return QWidget::eventFilter(watched,event);
}

//void VideoTitleBar::mousePressEvent(QMouseEvent *event)
//{
//        if(ReleaseCapture())
//        {
//            QWidget* pWindow = this->window();
//            if(pWindow->isTopLevel())
//            {
//                SendMessage(HWND(pWindow->winId()),WM_SYSCOMMAND,SC_MOVE + HTCAPTION,0);
//            }
//        }
//    event->ignore();
//}

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
