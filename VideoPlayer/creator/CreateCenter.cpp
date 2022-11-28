#include "CreateCenter.h"
#include "ui_CreateCenter.h"

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windows.h>
#include <windowsx.h>
#pragma comment (lib,"user32.lib")
#endif

CreateCenter* CreateCenter::m_pInstance = nullptr;

CreateCenter::CreateCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreateCenter)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
}

CreateCenter::~CreateCenter()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void CreateCenter::initWorkUI()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->stackedWidget_switch->setCurrentWidget(ui->page_login);
    ui->pushButton_title_icon->setIcon(QIcon(":/images/fileitem_documents.png"));
    ui->toolBox_center->layout()->setSpacing(1);//item之间的间距
    ui->toolBox_center->setItemIcon(0,QIcon(":/images/fileitem_documents.png"));
    ui->toolBox_center->setItemIcon(1,QIcon(":/images/fileitem_manager.png"));
    ui->toolBox_center->setItemIcon(2,QIcon(":/images/fileitem_musics.png"));
    ui->toolBox_center->setItemIcon(3,QIcon(":/images/fileitem_videos.png"));


    ui->listWidget_videopolish->setSelectionMode(QAbstractItemView::SingleSelection);//设置选择模式为单选
    ui->listWidget_videopolish->setDragEnabled(true);//启用拖拽
    ui->listWidget_videopolish->viewport()->setAcceptDrops(true);//设置接受拖放
    ui->listWidget_videopolish->setDropIndicatorShown(true);//设置显示将要被放置的位置
    ui->listWidget_videopolish->setDragDropMode(QAbstractItemView::InternalMove);//设置拖放模式为移动项目，如果不设置，默认为复制项目

    for(int i = 0; i < ui->listWidget_perCenter->count(); i++)
    {
        ui->listWidget_perCenter->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }

    for(int i = 0; i < ui->listWidget_shortVideo->count(); i++)
    {
        ui->listWidget_shortVideo->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }

    for(int i = 0; i < ui->listWidget_midVideo->count(); i++)
    {
        ui->listWidget_midVideo->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }

    for(int i = 0; i < ui->listWidget_musics->count(); i++)
    {
        ui->listWidget_musics->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }
}

void CreateCenter::handleSignalsAndSlots()
{
    //关闭
    connect(ui->pushButton_winClose,&QPushButton::clicked,[=](){
        this->close();
    });

    //还原
    connect(ui->pushButton_winRestore,&QPushButton::clicked,[=](){
        if(this->isMaximized())
            this->showNormal();
        else
            this->showMaximized();
    });

    //最小化
    connect(ui->pushButton_winMin,&QPushButton::clicked,[=](){
        this->showMinimized();
    });

    //小窗口关闭
    connect(ui->pushButton_minClose,&QPushButton::clicked,[=](){
        ui->pushButton_winClose->click();
    });

    //登录
    connect(ui->pushButton_clogin,&QPushButton::clicked,[=](){
        ui->stackedWidget_switch->setCurrentWidget(ui->page_create);
    });
}

void CreateCenter::setInstallEventer()
{

}

CreateCenter *CreateCenter::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new CreateCenter();
    }
    return m_pInstance;
}

void CreateCenter::mousePressEvent(QMouseEvent *event)
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
