#include "Updater.h"
#include "ui_Updater.h"
#include "updater/Installer.h"

#ifdef Q_OS_WIN
#include <qt_windows.h>
#pragma comment (lib,"user32.lib")
#endif

Updater* Updater::m_pInstance = nullptr;

Updater::Updater(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Updater)
{
    ui->setupUi(this);
    setFixedSize(320,200);
    this->setAttribute(Qt::WA_Hover);
//    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    initWorkUI();
    handleSignalsAndSlots();
}

Updater::~Updater()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

Updater *Updater::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new Updater();
    }
    return m_pInstance;
}

void Updater::initWorkUI()
{
    ui->stackedWidget_select->setCurrentIndex(1);
    ui->textEdit_info->setAlignment(Qt::AlignLeft);
    ui->textEdit_info->setText(QString(u8"Windows客户端V1.1.6版本\n,\n,最新版本：客户端V1.1.7版本"));
}

void Updater::handleSignalsAndSlots()
{
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        this->close();
    });

    connect(ui->pushButton_iknow,&QPushButton::clicked,[=](){
        this->close();
    });

    connect(ui->pushButton_accept,&QPushButton::clicked,[=](){
        this->accept();
        Installer::getInstance()->exec();
    });

    //完成
    connect(Installer::getInstance(),&Installer::sig_sendFinished,[=](){
        ui->stackedWidget_select->setCurrentIndex(0);
        ui->textEdit_info->setText(QString(u8"当前客户端已是最新版本！"));
    });

    connect(ui->pushButton_reject,&QPushButton::clicked,[=](){
        this->reject();
    });


}

void Updater::mousePressEvent(QMouseEvent *event)
{
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
