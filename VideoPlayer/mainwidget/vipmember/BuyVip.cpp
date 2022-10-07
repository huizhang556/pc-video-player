#include "BuyVip.h"
#include "ui_BuyVip.h"
#include "mainwidget/vipmember/BuyVipItem.h"
#ifdef Q_OS_WIN
#include <qt_windows.h>
#pragma comment (lib,"user32.lib")
#endif
#include <QMouseEvent>
#include <QListWidgetItem>
#include <QDebug>

BuyVip* BuyVip::m_pInstance = nullptr;

BuyVip::BuyVip(QWidget *parent):
    QDialog(parent),
    ui(new Ui::BuyVip)
{
    ui->setupUi(this);
    this->setFixedSize(580,600);
    this->setAttribute(Qt::WA_Hover);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    initWorkUI();
    handleSignalsAndSlots();
}

void BuyVip::initWorkUI()
{

    ui->listWidget_musicvip->setViewMode(QListView::IconMode);
    ui->listWidget_videovip->setViewMode(QListView::IconMode);
    ui->listWidget_rightmusic->setViewMode(QListView::IconMode);


    ui->listWidget_musicvip->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_videovip->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_rightmusic->setMovement(QListView::Static);//图标不可拖动

    ui->listWidget_musicvip->setResizeMode(QListWidget::Adjust);
    ui->listWidget_videovip->setResizeMode(QListWidget::Adjust);
    ui->listWidget_rightmusic->setResizeMode(QListWidget::Adjust);

    ui->listWidget_musicvip->setWrapping(false);//自动换行 所有itm在一行显示
    ui->listWidget_videovip->setWrapping(false);//自动换行 所有itm在一行显示
    ui->listWidget_rightmusic->setWrapping(false);//自动换行 所有itm在一行显示

    ui->listWidget_musicvip->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_musicvip->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_musicvip->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->listWidget_videovip->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_videovip->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_videovip->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->listWidget_rightmusic->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_rightmusic->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_rightmusic->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->tabWidget_vipType->setCurrentIndex(0);

    for(int i = 0; i < 4; i++)
    {
        BuyVipItem *buyItem = new BuyVipItem();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(buyItem->size());
        ui->listWidget_musicvip->addItem(item);
        ui->listWidget_musicvip->setItemWidget(item,buyItem);
        connect(buyItem,&BuyVipItem::sig_sendMouseClicked,[=](){
//            qDebug() << QString(u8"设置item");
            ui->listWidget_musicvip->setCurrentItem(item);
        });
    }

    for(int i = 0; i < 4; i++)
    {
        BuyVipItem *buyItem = new BuyVipItem();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(buyItem->size());
        ui->listWidget_rightmusic->addItem(item);
        ui->listWidget_rightmusic->setItemWidget(item,buyItem);
        connect(buyItem,&BuyVipItem::sig_sendMouseClicked,[=](){
//            qDebug() << QString(u8"设置item");
            ui->listWidget_rightmusic->setCurrentItem(item);
        });
    }


    for(int i = 0; i < 4; i++)
    {
        BuyVipItem *buyItem = new BuyVipItem();
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(buyItem->size());
        ui->listWidget_videovip->addItem(item);
        ui->listWidget_videovip->setItemWidget(item,buyItem);
        connect(buyItem,&BuyVipItem::sig_sendMouseClicked,[=](){
//            qDebug() << QString(u8"设置item");
            ui->listWidget_videovip->setCurrentItem(item);
        });
    }

}

void BuyVip::handleSignalsAndSlots()
{
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        this->close();
    });
}

BuyVip::~BuyVip()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;

}

BuyVip *BuyVip::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new BuyVip();
    }
    return m_pInstance;
}


void BuyVip::mousePressEvent(QMouseEvent *event)
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

