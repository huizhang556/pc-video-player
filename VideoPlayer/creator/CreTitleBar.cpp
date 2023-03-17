#include "CreTitleBar.h"
#include "ui_CreTitleBar.h"

//#ifdef Q_OS_WIN
//#include <qt_windows.h>
//#include <Windows.h>
//#include <windowsx.h>
//#pragma comment (lib,"user32.lib")
//#endif

CreTitleBar::CreTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreTitleBar)
{
    ui->setupUi(this);
    setFixedHeight(66);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
}

CreTitleBar::~CreTitleBar()
{
    delete ui;
}

void CreTitleBar::initWorkUI()
{
    manager = new QNetworkAccessManager(this);
    ui->pushButton_title->setIcon(QIcon("://images/creator/returnhome.png"));
    ui->pushButton_title->setIconSize(QSize(22,22));
    ui->pushButton_title->setLayoutDirection(Qt::RightToLeft);
    ui->pushButton_winRestore->setCheckable(true);
    ui->pushButton_winRestore->setChecked(false);
    ui->label_user->setFixedSize(QSize(50,50));//要使用遮罩，UI或者代码要设置大小，否则无法计算大小
    QRegion maskRegion(ui->label_user->rect(),QRegion::Ellipse);//创建圆形遮罩
    ui->label_user->setMask(maskRegion);//设置圆形遮罩
}

void CreTitleBar::handleSignalsAndSlots()
{
    //关闭
    connect(ui->pushButton_winClose,&QPushButton::clicked,[=](){
        emit sig_win_close();
    });

    //还原
    connect(ui->pushButton_winRestore,&QPushButton::clicked,[=](bool checked){
//        ui->pushButton_winRestore->setChecked(!checked);
        emit sig_win_restore(ui->pushButton_winRestore->isChecked());
        qDebug() << QString(u8"点击后状态：")<<checked;
    });

    //最小化
    connect(ui->pushButton_winMin,&QPushButton::clicked,[=](){
        emit sig_win_min();
    });
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_replyFinished(QNetworkReply*)));
}

void CreTitleBar::setInstallEventer()
{
    this->installEventFilter(this);
}

void CreTitleBar::setUserIcon(bool online, const QString &header)
{
    qDebug() << QString(u8"创作中心获取到的头像URL:") << header;
    if(online)
    {
        ui->stackedWidget_icon->setCurrentWidget(ui->page_login);
        manager->get(QNetworkRequest(QUrl(header)));

    }
    else
    {
        ui->stackedWidget_icon->setCurrentWidget(ui->page_unlogin);
    }
}

//void CreTitleBar::mousePressEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event)
//    if(ReleaseCapture())
//    {
//        QWidget* pWindow = this->window();
//        if(pWindow->isTopLevel())
//        {
//            SendMessage(HWND(pWindow->winId()),WM_SYSCOMMAND,SC_MOVE + HTCAPTION,0);
//        }
//    }
//    event->ignore();
//}

bool CreTitleBar::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this &&event->type() == QEvent::MouseButtonPress)
    {
        if(!this->hasFocus())
        {
            clearFocus();
            setFocus();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void CreTitleBar::slot_replyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        ui->label_user->setPixmap(pixmap);
        ui->label_user->setScaledContents(true);//内容自适应
        qDebug() << QString(u8"创作中心用户头像请求成功，使用自定义头像！");
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("请求错误：")<<reply->errorString();
        QPixmap pixmap("://images/user/default_woman00.png");
        ui->label_user->setPixmap(pixmap);
        ui->label_user->setScaledContents(true);//内容自适应
        qDebug() << QString(u8"创作中心用户头像请求失败，使用默认头像");
    }
}
