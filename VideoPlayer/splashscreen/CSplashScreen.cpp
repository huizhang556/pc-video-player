#include "CSplashScreen.h"
#include <QThread>
#include <QDebug>

CSplashScreen::CSplashScreen(const QPixmap & pixmap) : QSplashScreen(pixmap)
{
    m_progressbar = new QProgressBar(this);
    m_progressbar->setObjectName(QString::fromLocal8Bit("splash_progressbar"));
    m_progressbar->setValue(0);
    m_progressbar->setStyleSheet("#splash_progressbar{"
                                 "color:white;"
                                 "text-align:center;"
                                 "background-color:#36b0eb;"
                                 "border-radius:5px;"
                                 "}"
                                 "#splash_progressbar::chunk "
                                 "{"
                                 "width:6px;"
                                 "background-color:lightgreen;"
                                 "border-radius:3px;"
                                 "margin:2px;"
                                 "}"
                                 );

    QRect rect = this->rect();
    rect.setRect(rect.x()+20,rect.y()+450,860,12);
    m_progressbar->setGeometry(rect);
    showMessage(QString::fromLocal8Bit("正在加载文件..."),Qt::AlignRight | Qt::AlignBottom,Qt::yellow);

}

CSplashScreen::CSplashScreen( const QString gifname )
{
    m_move  = new QMovie(gifname);
    timer   = new QTimer(this);
    m_progressbar = new QProgressBar(this);
    m_progressbar->setObjectName(QString::fromLocal8Bit("splash_progressbar"));
    m_progressbar->setValue(0);
    m_progressbar->setStyleSheet("#splash_progressbar{"
                                 "color:white;"
                                 "text-align:center;"
                                 "background-color:#36b0eb;"
                                 "border-radius:5px;"
                                 "}"
                                 "#splash_progressbar::chunk "
                                 "{"
                                 "width:6px;"
                                 "background-color: lightgreen;"
                                 "border-radius:3px;"
                                 "margin:2px;"
                                 "}"
                                 );
    QRect rect = this->rect();
    rect.setRect(rect.x()+20,rect.y()+450,860,12);
    m_progressbar->setGeometry(rect);
    m_move->start();
//    setGif(gifname);
    timer->start(300);
    connect(timer,&QTimer::timeout,this,&CSplashScreen::slot_update);
}

CSplashScreen::~CSplashScreen()
{

}

void CSplashScreen::slot_update()
{
    roate++;
    qDebug() << "roate = "<<roate;
    setPixmap(m_move->currentPixmap());
    showMessage(QString::fromLocal8Bit("正在加载信息。。。%1").arg(roate),Qt::AlignHCenter | Qt::AlignBottom,Qt::yellow);
    repaint();
    qDebug() << "+++++++888888++++++++";
}

void CSplashScreen::drawContents(QPainter *painter)
{
    painter->setFont(QFont("Mircrosoft YaHei", 36));
    painter->setPen(QColor(213, 218, 220));
    painter->drawText(QPointF(20, 100), QString::fromLocal8Bit("音视频播放器"));

    painter->setFont(QFont("Mircrosoft YaHei", 12));
    painter->setPen(QColor(213, 218, 220));
    painter->drawText(QPointF(30, 140), QString::fromLocal8Bit("Version: 1.0.0"));

    painter->setFont(QFont("Mircrosoft YaHei", 12));
    painter->setPen(QColor(213, 218, 220));
    painter->drawText(QPointF(30, 180), QString::fromLocal8Bit("Author:ZhangHui"));

    painter->setFont(QFont("Mircrosoft YaHei", 12));
    painter->setPen(QColor(213, 218, 220));
    painter->drawText(QPointF(30, 220), QString::fromLocal8Bit("Emails:2493920797@qq.com"));

    painter->setFont(QFont("Helvetica", 16));
    painter->setPen(QColor(Qt::white));
    QRect r = rect();
    r.setRect(r.x(), r.y(), r.width(), r.height() -75);
    painter->drawText(r, Qt::AlignBottom | Qt::AlignCenter, QString::fromLocal8Bit("调试版"));

    painter->setFont(QFont("Verdana", 11));

    QSplashScreen::drawContents(painter);
}


void CSplashScreen::setGif( QString filename )
{
    m_move->setFileName(filename);
    m_move->start();
}

void CSplashScreen::slot_updateProgressbarValue(int value)
{
    m_progressbar->setValue(value);
    if(value == 100)
    {
//            clearMessage();
            showMessage(QString::fromLocal8Bit("文件加载完成！"),Qt::AlignRight | Qt::AlignBottom,Qt::yellow);
    }
}

