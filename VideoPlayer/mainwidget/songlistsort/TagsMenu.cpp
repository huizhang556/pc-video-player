#include "TagsMenu.h"
#include "ui_TagsMenu.h"
#include "mainwidget/songlistsort/TagsMenuItem.h"

#include <QListWidgetItem>
#include <QScrollBar>
#include <QPolygon>
#include <QDebug>

TagsMenu::TagsMenu(QWidget *parent) :
    QWidget(parent),
    m_startX(10),
    m_startY(0),
    m_triangleWidth(30),
    m_triangleHeight(30),
    ui(new Ui::TagsMenu)
{
    ui->setupUi(this);
    setFixedSize(746,360);
    initWorkUI();
    handleSignalsAndSlots();
}

TagsMenu::~TagsMenu()
{
    delete ui;
}

void TagsMenu::initWorkUI()
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    ui->listWidget_menu->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_menu->verticalScrollBar()->setObjectName(QString("songlist_vertical_scrollBar"));//样式用

    m_vector.append(m_area);
    m_vector.append(m_subject);
    m_vector.append(m_feeling);
    m_vector.append(m_scene);
    m_vector.append(m_years);
    m_vector.append(m_language);
    m_vector.append(m_style);

    m_vectorPic.append(QString("://images/icon/hot0.png"));
    m_vectorPic.append(QString("://images/icon/hot1.png"));
    m_vectorPic.append(QString("://images/icon/hot2.png"));
    m_vectorPic.append(QString("://images/icon/hot3.png"));
    m_vectorPic.append(QString("://images/icon/hot4.png"));
    m_vectorPic.append(QString("://images/icon/hot5.png"));
    m_vectorPic.append(QString("://images/icon/hot6.png"));

    for(int i = 0; i < m_theme.size(); i++)
    {
        slot_addSongItem(m_vectorPic.at(i),m_theme.at(i),m_vector.at(i));
    }
}

void TagsMenu::handleSignalsAndSlots()
{

}

void TagsMenu::slot_addSongItem(const QString &titleIcon, const QString &titleText, const QStringList &list)
{
    TagsMenuItem *itemWidget = new TagsMenuItem(titleIcon,titleText,list);
    itemWidget->setMenuListWidgetHeight(list.count());
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(itemWidget->size());
    ui->listWidget_menu->addItem(item);
    ui->listWidget_menu->setItemWidget(item,itemWidget);

    //信号与槽
    connect(itemWidget,&TagsMenuItem::sig_sendItemTextChanged,[=](QString text){
        emit sig_sendCurrentItemText(text);
        qDebug() << QString::fromLocal8Bit("已发送url==>%1").arg(text);
    });
}

void TagsMenu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255,255,255));
    //小三角区域
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_startX , m_startY );
    trianglePolygon << QPoint(m_startX + m_triangleWidth / 2, m_startY - m_triangleHeight );
    trianglePolygon << QPoint(m_startX + m_triangleWidth, m_startY);
    QPainterPath drawPath;
//    drawPath.addRoundedRect(0,0,width(),height(),0,0);
//    drawPath.addPolygon(trianglePolygon);
//    painter.drawPath(drawPath);
    painter.drawPolygon(trianglePolygon);
}

