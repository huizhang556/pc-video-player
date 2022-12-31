#include "BuyVip.h"
#include "ui_BuyVip.h"

//#ifdef Q_OS_WIN
//#include <qt_windows.h>
//#pragma comment (lib,"user32.lib")
//#endif
#include <QMouseEvent>
#include <QListWidgetItem>
#include <QDebug>

BuyVip* BuyVip::m_pInstance = nullptr;

BuyVip::BuyVip(QWidget *parent):
    QDialog(parent),
    ui(new Ui::BuyVip)
{
    ui->setupUi(this);
    this->setFixedSize(666,570);
    this->setAttribute(Qt::WA_Hover);

    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    initWorkUI();
    handleSignalsAndSlots();
}

void BuyVip::initWorkUI()
{
    m_strList.append(m_yearVip);
    m_strList.append(m_quarterVip);
    m_strList.append(m_monthVip);
    m_strList.append(m_freeTimeVip);

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

    ui->listWidget_musicvip->setOffset(170,0,0,0);
    ui->listWidget_videovip->setOffset(170,0,0,0);
    ui->listWidget_rightmusic->setOffset(170,0,0,0);

    ui->tabWidget_vipType->setCurrentIndex(0);

    for(int i = 0; i < 4; i++)
    {
        BuyVipItem *buyItem = new BuyVipItem(m_strList.at(i).at(0),m_strList.at(i).at(1),m_strList.at(i).at(2),m_strList.at(i).at(3));
        QListWidgetItem *item = new QListWidgetItem(m_strList.at(i).at(2));
        item->setSizeHint(QSize(170,100));
        ui->listWidget_musicvip->addItem(item);
        ui->listWidget_musicvip->setItemWidget(item,buyItem);
        connect(buyItem,&BuyVipItem::sig_sendMouseClicked,[=](){
//            qDebug() << QString(u8"设置item");
            ui->listWidget_musicvip->setCurrentItem(item);
            ui->label_payprice->setText(QString(u8"实付： ")+m_strList.at(i).at(2));
        });
    }
    ui->listWidget_musicvip->setCurrentRow(0);

    for(int i = 0; i < 4; i++)
    {
        BuyVipItem *buyItem = new BuyVipItem(m_strList.at(i).at(0),m_strList.at(i).at(1),m_strList.at(i).at(2),m_strList.at(i).at(3));
        QListWidgetItem *item = new QListWidgetItem(m_strList.at(i).at(2));
        item->setSizeHint(QSize(170,100));
        ui->listWidget_rightmusic->addItem(item);
        ui->listWidget_rightmusic->setItemWidget(item,buyItem);
        connect(buyItem,&BuyVipItem::sig_sendMouseClicked,[=](){
//            qDebug() << QString(u8"设置item");
            ui->listWidget_rightmusic->setCurrentItem(item);
            ui->label_payprice->setText(QString(u8"实付： ")+m_strList.at(i).at(2));
        });
    }
    ui->listWidget_rightmusic->setCurrentRow(0);


    for(int i = 0; i < 4; i++)
    {
        BuyVipItem *buyItem = new BuyVipItem(m_strList.at(i).at(0),m_strList.at(i).at(1),m_strList.at(i).at(2),m_strList.at(i).at(3));
        QListWidgetItem *item = new QListWidgetItem(m_strList.at(i).at(2));
        item->setSizeHint(QSize(170,100));
        ui->listWidget_videovip->addItem(item);
        ui->listWidget_videovip->setItemWidget(item,buyItem);
        connect(buyItem,&BuyVipItem::sig_sendMouseClicked,[=](){
//            qDebug() << QString(u8"设置item");
            ui->listWidget_videovip->setCurrentItem(item);
            ui->label_payprice->setText(QString(u8"实付： ")+m_strList.at(i).at(2));
        });
    }
    ui->listWidget_videovip->setCurrentRow(0);
    ui->label_payprice->setText(QString(u8"实付： ")+m_strList.at(0).at(2));
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
    Q_UNUSED(event)
    m_mvPos = event->globalPos() - this->pos();
}

void BuyVip::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    this->move(event->globalPos() - m_mvPos);
}

