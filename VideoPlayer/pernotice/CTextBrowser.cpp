#include "CTextBrowser.h"
#include "ui_CTextBrowser.h"

CTextBrowser::CTextBrowser(QWidget *parent) :
    QTextBrowser(parent),
    m_startX(15),
    m_startY(20),
    m_triangleWidth(20),
    m_triangleHeight(15),
    ui(new Ui::CTextBrowser)
{
    ui->setupUi(this);
}

CTextBrowser::~CTextBrowser()
{
    delete ui;
}

void CTextBrowser::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setBrush(QColor(48, 48, 48));
    painter.setPen(Qt::NoPen);
    //小三角区域
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_startX , m_startY);
    trianglePolygon << QPoint(0, 45);
    trianglePolygon << QPoint(m_startX + m_triangleWidth, 35);
    QPainterPath drawPath;
    //调整三角形高度：1.界面留出空白高度 2.三角形起点高度 3.三角形高度一致
    drawPath.addRoundRect(m_startX,0,width()-m_startX,height(),4,4);
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
}
