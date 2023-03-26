#include "CSplashScreen.h"
#include <QThread>
#include <QSoundEffect>
#include <QDebug>

//#ifdef QT_DEBUG
//   QString edition = QString::fromLocal8Bit("调试版");
//#else
//   QString edition = QString::fromLocal8Bit("正式版");
//#endif

CSplashScreen::CSplashScreen(const QPixmap & pixmap) : QSplashScreen(pixmap)
{
    m_progressbar = new QProgressBar(this);
    m_progressbar->setFixedHeight(10);
    m_progressbar->setObjectName(QString::fromLocal8Bit("splash_progressbar"));
    m_progressbar->setValue(0);
    m_progressbar->setStyleSheet("QProgressBar#splash_progressbar{"
                                 "color: #ffffff;"
                                 "text-align:center;"
                                 "background-color: #303030;"
                                 "border-radius:5px;"
                                 "border: 0px solid #a1a1ff;"
                                 "}"
                                 "QProgressBar#splash_progressbar::chunk "
                                 "{"
                                 "background-color: #ca296d;"
                                 "border-radius:3px;"
                                 "margin:1px;"
                                 "}"
                                 );

    QRect ret = this->rect();
    ret.setRect(ret.x()+10, ret.y() + ret.height() - 40, ret.width() - 20, m_progressbar->height());
    m_progressbar->setGeometry(ret);
//    playerWelcome();
    showMessage(QString::fromLocal8Bit("正在加载文件..."),Qt::AlignRight | Qt::AlignBottom,Qt::yellow);

}

CSplashScreen::CSplashScreen( const QString gifname )
{
    m_move  = new QMovie(gifname);
    timer   = new QTimer(this);
    m_progressbar = new QProgressBar(this);
    m_progressbar->setFixedHeight(10);
    m_progressbar->setObjectName(QString::fromLocal8Bit("splash_progressbar"));
    m_progressbar->setValue(0);
    m_progressbar->setStyleSheet("#splash_progressbar{"
                                 "color: #ffffff;"
                                 "text-align:center;"
                                 "background-color: #303030;"
                                 "border-radius:5px;"
                                 "border: 0px solid #a1a1ff;"
                                 "}"
                                 "#splash_progressbar::chunk "
                                 "{"
                                 "background-color: #ca296d;"
                                 "border-radius:3px;"
                                 "margin:1px;"
                                 "}"
                                 );
    QRect ret = this->rect();
    ret.setRect(ret.x()+10, ret.y() + ret.height() - 40, ret.width() - 20, m_progressbar->height());
    m_progressbar->setGeometry(ret);
    m_move->start();
//    setGif(gifname);
    timer->start(300);
//    playerWelcome();
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

void CSplashScreen::playerWelcome()
{
    QSoundEffect *effect = new QSoundEffect(this);
    effect->setSource(QUrl::fromLocalFile(":/audio/splash/welcome.wav"));
    effect->setLoopCount(1);  //循环次数
    effect->setVolume(0.96f); //音量  0~1之间
    effect->play();
    qDebug() << QString(u8"播放开机音乐！");
}

void CSplashScreen::drawContents(QPainter *painter)
{
    painter->setFont(QFont("Mircrosoft YaHei", 45));
    painter->setPen(QColor(36, 138, 182));
    painter->drawText(QPointF(20, 80), QString::fromLocal8Bit("音视频播放器"));

    painter->setFont(QFont("Mircrosoft YaHei", 12));
    painter->setPen(QColor(65, 205, 82));
    painter->drawText(QPointF(30, 140), QString::fromLocal8Bit("Version: 1.0.0"));

    painter->setFont(QFont("Mircrosoft YaHei", 12));
    painter->setPen(QColor(65, 205, 82));
    painter->drawText(QPointF(30, 180), QString::fromLocal8Bit("Author: ZhangHui"));

    painter->setFont(QFont("Mircrosoft YaHei", 12));
    painter->setPen(QColor(65, 205, 82));
    painter->drawText(QPointF(30, 220), QString::fromLocal8Bit("Emails: 2493920797@qq.com"));

    painter->setFont(QFont("Mircrosoft YaHei", 12));
    painter->setPen(QColor(65, 205, 82));
    painter->drawText(QPointF(30, 260), QString::fromLocal8Bit("Based on: Qt 5.12.0 (MSVC 2015, 32 bit) + MySQL 5.7.36 for Linux (x86_64)"));

    painter->setFont(QFont("Helvetica", 16, 800));
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
            showMessage(QString::fromLocal8Bit("文件加载完成！"),Qt::AlignRight | Qt::AlignBottom,Qt::yellow);//右下角,黄色字体
    }
}

