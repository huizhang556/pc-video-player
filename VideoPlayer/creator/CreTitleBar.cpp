#include "CreTitleBar.h"
#include "ui_CreTitleBar.h"

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windows.h>
#include <windowsx.h>
#pragma comment (lib,"user32.lib")
#endif

CreTitleBar::CreTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreTitleBar)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
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
    ui->pushButton_title->setIcon(QIcon("://images/creator/returnhome.png"));
    ui->pushButton_title->setIconSize(QSize(22,22));
    ui->pushButton_title->setLayoutDirection(Qt::RightToLeft);
    ui->pushButton_winRestore->setCheckable(true);
    ui->pushButton_winRestore->setChecked(false);
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
}

void CreTitleBar::setInstallEventer()
{
    this->installEventFilter(this);
}

void CreTitleBar::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    if(ReleaseCapture())
    {
        QWidget* pWindow = this->window();
        if(pWindow->isTopLevel())
        {
            SendMessage(HWND(pWindow->winId()),WM_SYSCOMMAND,SC_MOVE + HTCAPTION,0);
        }
    }
    event->ignore();
}

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
