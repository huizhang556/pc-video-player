#include "CusLabelItem.h"
#include "ui_CusLabelItem.h"

#include <QDebug>

CusLabelItem::CusLabelItem(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::CusLabelItem)
{
    ui->setupUi(this);
    initWorkUI();
    setEventFilter();
    handleSignalsAndSlots();
}

CusLabelItem::CusLabelItem(const QString &hotPath, const QString &playcounts, bool hotOn, bool playOff1, bool playOff2, QWidget *parent):
    QLabel(parent),
    m_hot(hotPath),
    m_counts(playcounts),
    m_hotOn(hotOn),
    m_mainPlay(playOff1),
    m_play(playOff2),
    ui(new Ui::CusLabelItem)
{
    ui->setupUi(this);
    initWorkUI();
    setEventFilter();
    handleSignalsAndSlots();
    setItem_hotOn(m_hotOn);
    setItemMainPlayerOn(m_mainPlay);
    setItemPlayerOn(m_play);

    setItem_hot(m_hot);
    setItem_playCounts(m_counts);
}

CusLabelItem::~CusLabelItem()
{
    delete ui;
}

void CusLabelItem::initWorkUI()
{
//    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    ui->pushButton_hot->hide();
    ui->pushButton_mainPlay->hide();
    ui->pushButton_play->hide();
}

void CusLabelItem::handleSignalsAndSlots()
{
  //播放
    connect(ui->pushButton_mainPlay,&QPushButton::clicked,[=](){  emit sig_sendPlayOn(); qDebug() << QString(u8"主播放"); });
    connect(ui->pushButton_play,&QPushButton::clicked,[=](){  emit sig_sendPlayOn(); qDebug() << QString(u8"副播放"); });
}

void CusLabelItem::setEventFilter()
{
    installEventFilter(this);
    ui->pushButton_mainPlay->installEventFilter(this);
    ui->pushButton_play->installEventFilter(this);
}

void CusLabelItem::constructItem(const QString &hotPath, const QString &playcounts, bool hotOn, bool playOff1, bool playOff2)
{
    this->setItem_hotOn(hotOn);
    this->setItemMainPlayerOn(playOff1);
    this->setItemPlayerOn(playOff2);
    this->setItem_hot(hotPath);
    this->setItem_playCounts(playcounts);
}

void CusLabelItem::setItem_hotOn(bool on)
{
    m_hotOn = on;
    ui->pushButton_hot->setHidden(!m_hotOn);
}

void CusLabelItem::setItemMainPlayerOn(bool on)
{
    m_mainPlay = on;
//    ui->pushButton_mainPlay->setHidden(!m_mainPlay);
}

void CusLabelItem::setItemPlayerOn(bool on)
{
    m_play = on;
//    ui->pushButton_play->setHidden(!m_play);
}

bool CusLabelItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter && m_mainPlay)//进入且用了mainPlay
        {
            ui->pushButton_mainPlay->show();
            qDebug() << "Mainplayer enter";
        }
        else if(event->type() == QEvent::Leave && m_mainPlay)
        {
            ui->pushButton_mainPlay->hide();
            qDebug() << "Mainplayer hide";
        }
    }

    if(watched == this)
    {
        if(event->type() == QEvent::Enter && m_play)//进入且用了mainPlay
        {
            ui->pushButton_play->show();
            qDebug() << "player enter";
        }
        else if(event->type() == QEvent::Leave && m_play)
        {
            ui->pushButton_play->hide();
            qDebug() << "player hide";
        }

        if(watched == this)
        {
            if(event->type() == QEvent::Resize)
            {
//                update();
            }
        }
    }
    return   QWidget::eventFilter(watched,event);
}

void CusLabelItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
//        QPainter painter(this);
//        painter.setRenderHint(QPainter::Antialiasing,true);
//        painter.setPen(Qt::NoPen);
//        painter.setBrush(QColor(56, 67, 99,10));//rgba
//        QPainterPath drawPath;

//        drawPath.addRoundedRect(this->rect(),10,10);
//        painter.drawPath(drawPath);
//        painter.drawPixmap(0,0,width(),height(),QPixmap(m_hot));
}

void CusLabelItem::setItem_hot(const QString &hot)
{
    ui->pushButton_hot->setIcon(QIcon(hot));
    ui->pushButton_hot->setIconSize(QSize(30,28));
}

void CusLabelItem::setItem_playCounts(const QString &counts)
{
    ui->pushButton_playcounts->setText(QString(u8"累计播放%1").arg(counts));
    ui->pushButton_playcounts->setIcon(QIcon("://images/icon/recvideo_amount.png"));
    ui->pushButton_playcounts->setIconSize(QSize(20,15));
}

void CusLabelItem::setItem_mainPlayer(bool on)
{
    ui->pushButton_mainPlay->setHidden(on);
}

void CusLabelItem::setItem_player(bool on)
{
    ui->pushButton_play->setHidden(on);
}
