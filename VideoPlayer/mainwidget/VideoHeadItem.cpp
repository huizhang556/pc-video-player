#include "VideoHeadItem.h"
#include "ui_VideoHeadItem.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

VideoHeadItem::VideoHeadItem(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::VideoHeadItem)
{
    ui->setupUi(this);
    resize(200,270);
    initWorkUI();
    handleSignalsAndSlots();
    setEventFilter();
}

VideoHeadItem::~VideoHeadItem()
{
    delete ui;
}

void VideoHeadItem::initWorkUI()
{
//    this->setAttribute(Qt::WA_TranslucentBackground,true);
    ui->pushButton_mainPlayer->hide();
}

void VideoHeadItem::handleSignalsAndSlots()
{
    connect(ui->pushButton_mainPlayer,&QPushButton::clicked,[=](){
        qDebug() << "player clicked";
        emit sig_sendPlayer();
    });
}

void VideoHeadItem::setEventFilter()
{
    this->installEventFilter(this);
}

void VideoHeadItem::setItemPicture(const QString path)
{
    m_picPath = path;
}

void VideoHeadItem::setItemBGColor(const QColor &color)
{
    m_bgColor = color;
}

bool VideoHeadItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->pushButton_mainPlayer->show();
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->pushButton_mainPlayer->hide();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void VideoHeadItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(14, 27, 44,10));//rgba 背景色一致

        QPainterPath drawPath;
        drawPath.addRoundedRect(this->rect(),7,7);
        drawPath.addRect(this->rect());
        //如果不绘制图片（其上面叠加的部分会被覆盖），通过setPixmap添加的图片，圆角失效，只能重绘（但是通过样式设置的图片是圆角生效的）
        painter.drawPixmap(0,0,width(),height(),QPixmap(m_picPath));
        painter.fillPath(drawPath,QBrush(m_bgColor));//先绘图片再填充外部边缘（准确来说叫颜色压住覆盖）
}
