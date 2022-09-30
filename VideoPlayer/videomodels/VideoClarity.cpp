#include "VideoClarity.h"
#include "ui_VideoClarity.h"

#include <QPainterPath>
#include <QPolygon>
#include <QDebug>

VideoClarity::VideoClarity(QWidget *parent) :
    QWidget(parent),
    m_offset(0),
    m_triangleWidth(20),
    m_triangleHeight(20),
    ui(new Ui::VideoClarity)
{
    ui->setupUi(this);
    this->setFixedSize(105,185);
    initWorkUI();
    handleChandleSignalsAndSlots();
}

VideoClarity::~VideoClarity()
{
    delete ui;
}

void VideoClarity::initWorkUI()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup | Qt::Tool | windowFlags());
    this->setAttribute(Qt::WA_TranslucentBackground);    //重要
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(ui->pushButton_num1,0);
    m_buttonGroup->addButton(ui->pushButton_num2,1);
    m_buttonGroup->addButton(ui->pushButton_num3,2);
    m_buttonGroup->addButton(ui->pushButton_num4,3);
    m_buttonGroup->addButton(ui->pushButton_num5,4);
    m_buttonGroup->setExclusive(true);

    for(int i = 0; i < 5; i++)
    {
        m_buttonGroup->button(i)->setCheckable(true);
        m_buttonGroup->button(i)->setLayoutDirection(Qt::RightToLeft);
    }

    //设置图标
    ui->pushButton_num5->setIcon(QIcon(":/images/user/itemmark_vyp.png"));
    ui->pushButton_num5->setIconSize(QSize(26,26));
    ui->pushButton_num5->setText(QString(u8"超清"));
    ui->pushButton_num5->setDisabled(true);
    ui->pushButton_num4->setIcon(QIcon(":/images/user/itemmark_vyp.png"));
    ui->pushButton_num4->setIconSize(QSize(26,26));
    ui->pushButton_num4->setText(QString(u8"1080P"));
    ui->pushButton_num3->setIcon(QIcon(":/images/user/itemmark_vyp.png"));
    ui->pushButton_num3->setIconSize(QSize(26,26));
    ui->pushButton_num3->setText(QString(u8"720P"));
    ui->pushButton_num2->setIcon(QIcon(""));
    ui->pushButton_num2->setIconSize(QSize(26,26));
    ui->pushButton_num2->setText(QString(u8"480P"));
    ui->pushButton_num1->setIcon(QIcon(""));
    ui->pushButton_num1->setIconSize(QSize(26,26));
    ui->pushButton_num1->setText(QString(u8"标清"));
}

void VideoClarity::handleChandleSignalsAndSlots()
{
    connect(m_buttonGroup,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton *button){
        button->setChecked(true);
//        button->setDisabled(true);//测试样式用，有效样式
//        qDebug() <<button->text();
        emit sig_clarityChanged(button->text());
    });
}

void VideoClarity::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(24, 27, 31));
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(width()/2-m_triangleWidth/2 , height()- m_triangleHeight);
    trianglePolygon << QPoint(width()/2,height());
    trianglePolygon << QPoint(width()/2+m_triangleWidth/2 , height()- m_triangleHeight);
    QPainterPath drawPath;
    drawPath.addRegion(trianglePolygon);
    painter.drawPath(drawPath);
}

void VideoClarity::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
//    this->hide();
}
