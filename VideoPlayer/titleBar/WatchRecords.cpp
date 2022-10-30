#include "WatchRecords.h"
#include "ui_WatchRecords.h"
#include <QPainter>
#include <QPainterPath>
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
}

WatchRecords::~WatchRecords()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
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
