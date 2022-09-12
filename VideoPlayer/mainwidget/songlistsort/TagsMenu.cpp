#include "TagsMenu.h"
#include "ui_TagsMenu.h"
#include "mainwidget/songlistsort/TagsMenuItem.h"

#include <QGraphicsDropShadowEffect>
#include <QListWidgetItem>
#include <QScrollBar>
#include <QPolygon>
#include <QDebug>

TagsMenu::TagsMenu(QWidget *parent) :
    QWidget(parent),
    m_startX(15),
    m_startY(15),
    m_triangleWidth(20),
    m_triangleHeight(15),
    ui(new Ui::TagsMenu)
{
    ui->setupUi(this);
    setFixedWidth(720);//120 * 6
//    setFixedSize(718,360);
    initWorkUI();
    handleSignalsAndSlots();
}

TagsMenu::~TagsMenu()
{
    delete ui;
}

void TagsMenu::initWorkUI()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    ui->listWidget_menu->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_menu->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_menu->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_menu->verticalScrollBar()->setObjectName(QString("songlist_vertical_scrollBar"));//样式用

//    auto shadowEffect = new QGraphicsDropShadowEffect(this);
//    shadowEffect->setOffset(0,0);
//    shadowEffect->setColor(Qt::white);
//    shadowEffect->setBlurRadius(0);// 阴影厚度
//    this->setGraphicsEffect(shadowEffect);

    m_vector.append(m_area);
    m_vector.append(m_subject);
    m_vector.append(m_feeling);
    m_vector.append(m_scene);
    m_vector.append(m_years);
    m_vector.append(m_language);
    m_vector.append(m_style);
    m_vector.append(m_voice);

    m_vectorPic.append(QString("://images/icon/hot0.png"));
    m_vectorPic.append(QString("://images/icon/hot1.png"));
    m_vectorPic.append(QString("://images/icon/hot2.png"));
    m_vectorPic.append(QString("://images/icon/hot3.png"));
    m_vectorPic.append(QString("://images/icon/hot4.png"));
    m_vectorPic.append(QString("://images/icon/hot5.png"));
    m_vectorPic.append(QString("://images/icon/hot6.png"));
    m_vectorPic.append(QString("://images/icon/hot7.png"));

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
    painter.setBrush(QColor(56, 67, 99));//50 77 91
    //小三角区域
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_startX , m_startY);// 30 30
    trianglePolygon << QPoint(m_startX + m_triangleWidth / 2, 0);//45 0
    trianglePolygon << QPoint(m_startX + m_triangleWidth, m_startY);
    QPainterPath drawPath;
    //调整三角形高度：1.界面留出空白高度 2.三角形起点高度 3.三角形高度一致
    drawPath.addRoundedRect(0,m_startY,width(),height()- m_triangleHeight,5,5);//嵌入按钮中时，按钮也要设置圆角
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
}

