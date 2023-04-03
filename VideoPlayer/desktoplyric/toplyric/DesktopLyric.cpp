#include "DesktopLyric.h"
#include "ui_DesktopLyric.h"

#include "desktoplyric/toptooltips/DesktopTip1.h"

//#ifdef Q_OS_WIN
//#include <qt_windows.h>
//#pragma comment (lib,"user32.lib")
//#endif

DesktopLyric* DesktopLyric::m_pInstance = nullptr;

DesktopLyric::DesktopLyric(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DesktopLyric)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_Hover);
    this->setFixedSize(960,110);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
//    this->setWindowOpacity(0.6);
//    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    initWorkUI();
    handleSignalsAndSlots();
}

DesktopLyric::~DesktopLyric()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

DesktopLyric *DesktopLyric::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new DesktopLyric();
    }
    return m_pInstance;
}

void DesktopLyric::initWorkUI()
{
    this->installEventFilter(this);
//    ui->frame_func->hide();

    ui->pushButton_collect->setCheckable(true);
    ui->pushButton_collect->setChecked(true);

    ui->pushButton_deskplay->setCheckable(true);
    ui->pushButton_deskplay->setChecked(false);
    ui->pushButton_lock->setCheckable(true);

    ui->pushButton_search->setText(QString(u8"搜索歌词"));
    ui->pushButton_search->setIcon(QIcon(":/images/desktop/desktop_search.png"));

    //如果要设置字体大小，不要设置样式字体
    QFont font ("Microsoft YaHei",32,75);
    ui->label_lyric->setFont(font);

//        QRadialGradient g();
//        g.setSpread(QGradient::ReflectSpread);
//        double s = 6;
//        g.setColorAt(0/s,Qt::yellow);
//        g.setColorAt(1/s,Qt::green);
//        g.setColorAt(2/s,Qt::blue);
//        g.setColorAt(3/s,Qt::red);
//        g.setColorAt(4/s,Qt::magenta);
//        g.setColorAt(5/s,Qt::cyan);
//        g.setColorAt(6/s,Qt::white);
}

void DesktopLyric::handleSignalsAndSlots()
{
    //关闭桌面歌词
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
//        qDebug() <<QString(u8"关闭按钮点击");
        this->close();
    });

    //字体--放大
    connect(ui->pushButton_zoomIn,&QPushButton::clicked,[=](){
        int fontSize = ui->label_lyric->font().pointSize();
        qDebug() << QString(u8"目前字体大小：")<<fontSize;
        QFont font ("Microsoft YaHei", fontSize+2, 75);
        ui->label_lyric->setFont(font);
//        ui->label_lyric->setText(ui->label_lyric->text());

    });

    //字体--缩小
    connect(ui->pushButton_zoomOut,&QPushButton::clicked,[=](){
        int fontSize = ui->label_lyric->font().pointSize();
        qDebug() << QString(u8"目前字体大小：")<<fontSize;
        QFont font ("Microsoft YaHei", fontSize-2, 75);
        ui->label_lyric->setFont(font);
//        ui->label_lyric->setText(ui->label_lyric->text());
    });

    //设置
    connect(ui->pushButtonsetting,&QPushButton::clicked,[=](){
        emit sig_sendSetting();
    });

    //收藏
    connect(ui->pushButton_collect,&QPushButton::clicked,[=](){

    });

    //上一首
    connect(ui->pushButton_previous,&QPushButton::clicked,[=](){
        emit sig_sendPrevious();
    });

    //暂停
    connect(ui->pushButton_deskplay,&QPushButton::clicked,[=](){
        emit sig_sendPlay();
    });

    //下一首
    connect(ui->pushButton_next,&QPushButton::clicked,[=](){
        emit sig_sendNext();
    });

    //图标
    connect(ui->pushButton_icon,&QPushButton::clicked,[=](){
        QStringList list = {QString(u8"showTips,NoAnimation!")};
        DesktopTip1::setMode(DesktopTip1::NoAnimation);//位置动画
        DesktopTip1::showTip(list,5);
    });

    //竖屏
    connect(ui->pushButton_vertical,&QPushButton::clicked,[=](){
        QStringList list = {QString(u8"showTips,OpacityAnimation!")};
        DesktopTip1::setMode(DesktopTip1::OpacityAnimation);//位置动画
        DesktopTip1::showTip(list,5);
    });

    //加速
    connect(ui->pushButton_add,&QPushButton::clicked,[=](){
        QStringList list = {QString(u8"showTips,PosAnimation!")};
        DesktopTip1::setMode(DesktopTip1::PosAnimation);//位置动画
        DesktopTip1::showTip(list,5);
    });

    //减速
    connect(ui->pushButton_sub,&QPushButton::clicked,[=](){
        QStringList list = {QString(u8"showTips,AllAnimation!")};
        DesktopTip1::setMode(DesktopTip1::AllAnimation);//位置动画
        DesktopTip1::showTip(list,5);
    });

    //卡拉ok
    connect(ui->pushButton_kala,&QPushButton::clicked,[=](){
        QStringList list_text = {
            QString(u8"检测到软件有最新版本，点击链接进行下载1！"),
            QString(u8"检测到软件有最新版本，点击链接进行下载2！")};
        QStringList list_url = {
            QString(u8"www.bing.com"),
            QString(u8"www.hao123.com")};
        DesktopTip1::setMode(DesktopTip1::NoAnimation);//位置动画
        DesktopTip1::keepTip(list_text,list_url);
    });

    //调色盘
    connect(ui->pushButton_color,&QPushButton::clicked,[=](){
        QStringList list = {QString(u8"keepTip,OpacityAnimation!")};
        DesktopTip1::setMode(DesktopTip1::OpacityAnimation);//位置动画
        DesktopTip1::keepTip(list);
    });

    //搜索歌词
    connect(ui->pushButton_search,&QPushButton::clicked,[=](){
        QStringList list = {QString(u8"keepTip,PosAnimation!")};
        DesktopTip1::setMode(DesktopTip1::PosAnimation);//位置动画
        DesktopTip1::keepTip(list);
    });

    //锁定
    connect(ui->pushButton_lock,&QPushButton::clicked,[=](){
        if(ui->label_lyric->isHidden())
        {
            ui->label_lyric->show();
            ui->pushButton_lock->setChecked(true);
        }
        else
        {
            ui->label_lyric->hide();
            ui->pushButton_lock->setChecked(false);
        }
    });

    //回到桌面
    connect(ui->pushButton_desktop,&QPushButton::clicked,[=](){
        QStringList list = {QString(u8"keepTip,AllAnimation!")};
        DesktopTip1::setMode(DesktopTip1::AllAnimation);//位置动画
        DesktopTip1::keepTip(list);
    });

    //音量 +
    connect(ui->pushButton_sound_add,&QPushButton::clicked,[=](){
        emit sig_sendSound(true);
    });

    //音量 -
    connect(ui->pushButton_sound_sub,&QPushButton::clicked,[=](){
        emit sig_sendSound(false);
    });


}

void DesktopLyric::slot_setCurrentPlayStatus(bool status)
{
//    qDebug() << QString(u8"桌面歌词接收到播放状态是：")<<status;
    //需要注意：
    //采用checked实现两种状态的时候，样式表只能有正常样式和勾选样式，非勾选样式不要设置
    if(status)//播放状态
    {
        ui->pushButton_deskplay->setChecked(true);
    }
    else
    {
        ui->pushButton_deskplay->setChecked(false);
    }
}

void DesktopLyric::slot_setCurrentLyric(QString& text)
{
    ui->label_lyric->setText(text);
}

void DesktopLyric::mousePressEvent(QMouseEvent *event)
{
//    if(ReleaseCapture())
//    {
//        QWidget* pWindow = this->window();
//        if(pWindow->isTopLevel())
//        {
//            SendMessage(HWND(pWindow->winId()),WM_SYSCOMMAND,SC_MOVE + HTCAPTION,0);
//        }
//    }
//    event->ignore();
    Q_UNUSED(event)
    m_mvPos = event->globalPos() - this->pos();
}

void DesktopLyric::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    this->move(event->globalPos() - m_mvPos);
}

bool DesktopLyric::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && event->type() == QEvent::Enter)
    {
        this->setFocus();
//        ui->frame_func->show();
        ui->label_lyric->setStyleSheet("background-color: rgba(64, 66, 68,0.6);");
    }
    else if(watched == this && event->type() == QEvent::Leave)
    {
//        ui->frame_func->hide();
        ui->label_lyric->setStyleSheet("background-color: rgba(64, 66, 68,0.0);");
    }
    return QWidget::eventFilter(watched,event);
}
