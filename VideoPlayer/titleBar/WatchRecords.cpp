#include "WatchRecords.h"
#include "ui_WatchRecords.h"
#include "global/Global.h"
#include "titlebar/WHistoryItem.h"
#include <QPainter>
#include <QScrollBar>
#include <QPainterPath>
#include <QListWidgetItem>
#include <QDebug>

WatchRecords* WatchRecords::m_pInstance = nullptr;

WatchRecords::WatchRecords(QWidget *parent) :
    QWidget(parent),
    m_startX(140),
    m_startY(20),
    m_triangleWidth(20),
    m_triangleHeight(15),
    ui(new Ui::WatchRecords)
{
    ui->setupUi(this);
    setFixedSize(300,400);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Popup | Qt::Tool | Qt::WindowStaysOnTopHint);
    initWorkUI();
    handleSignalsAndSlots();
}

WatchRecords::~WatchRecords()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void WatchRecords::initWorkUI()
{
    ui->listWidget_watched->setViewMode(QListView::ListMode);
    ui->listWidget_watched->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_watched->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_subscrbe->setViewMode(QListView::ListMode);
    ui->listWidget_subscrbe->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_subscrbe->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_collect->setViewMode(QListView::ListMode);
    ui->listWidget_collect->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_collect->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0; i < 20; i++)
    {
        QString url = QString(u8"www.hao123.com");
        QString picpath = Global::appDirPath + QString("/pictures/videos/dramalist/temp_%1.png").arg(i+1);
        QString info = QString(u8"赵本山经典之作%1").arg(i+1);
        QString progress = QString(u8"观看至11:24:13");
        WHistoryItem *itemWidget = new WHistoryItem(picpath,info,progress);
        QListWidgetItem *item = new QListWidgetItem(url);
        item->setSizeHint(ITEMSIZE);
        ui->listWidget_watched->addItem(item);
        ui->listWidget_watched->setItemWidget(item,itemWidget);
    }

    for(int i = 0; i < 20; i++)
    {
        QString url = QString(u8"www.hao123.com");
        QString picpath = Global::appDirPath + QString("/pictures/videos/dramalist/temp_%1.png").arg(i+1);
        QString info = QString(u8"赵本山经典之作%1").arg(i+1);
        QString progress = QString(u8"观看至11:24:13");
        WHistoryItem *itemWidget = new WHistoryItem(picpath,info,progress);
        QListWidgetItem *item = new QListWidgetItem(url);
        item->setSizeHint(ITEMSIZE);
        ui->listWidget_subscrbe->addItem(item);
        ui->listWidget_subscrbe->setItemWidget(item,itemWidget);
    }

    for(int i = 0; i < 20; i++)
    {
        QString url = QString(u8"www.hao123.com");
        QString picpath = Global::appDirPath + QString("/pictures/videos/dramalist/temp_%1.png").arg(i+1);
        QString info = QString(u8"赵本山经典之作%1").arg(i+1);
        QString progress = QString(u8"观看至11:24:13");
        WHistoryItem *itemWidget = new WHistoryItem(picpath,info,progress);
        QListWidgetItem *item = new QListWidgetItem(url);
        item->setSizeHint(ITEMSIZE);
        ui->listWidget_collect->addItem(item);
        ui->listWidget_collect->setItemWidget(item,itemWidget);
    }

    ui->tabWidget_watch->setCurrentIndex(0);
}

void WatchRecords::handleSignalsAndSlots()
{

}

WatchRecords *WatchRecords::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new WatchRecords();
    }
    return m_pInstance;
}

void WatchRecords::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(48, 48, 48));
    //小三角区域
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_startX , m_startY);
    trianglePolygon << QPoint(m_startX + m_triangleWidth / 2, 20 - m_triangleHeight);
    trianglePolygon << QPoint(m_startX + m_triangleWidth, m_startY);
    QPainterPath drawPath;
    //调整三角形高度：1.界面留出空白高度 2.三角形起点高度 3.三角形高度一致
    drawPath.addRoundRect(0,m_startY,width(),height()-20,4,4);
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
}

void WatchRecords::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->close();
}
