#include "CSplashScreen.h"
#include <QThread>
#include <QSoundEffect>
#include <QDebug>

#ifdef QT_DEBUG
   QString CSplashScreen::edition = QString(u8"调试版");
#else
   QString CSplashScreen::edition = QString(u8"正式版");
#endif

CSplashScreen::CSplashScreen(const QPixmap & pixmap) : QSplashScreen(pixmap)
{
//    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground,true);
    m_progressbar = new QProgressBar(this);
    m_progressbar->setFixedHeight(14);
    m_progressbar->setObjectName(QString::fromUtf8("splash_progressbar"));
    m_progressbar->setValue(0);
    m_progressbar->setStyleSheet("QProgressBar#splash_progressbar{"
                                 "color: #d10c64;"
                                 "text-align:center;"
                                 "background-color: #303030;"
                                 "border-radius:7px;"
                                 "border: 1px solid #424041;"
                                 "}"
                                 "QProgressBar#splash_progressbar::chunk "
                                 "{"
                                 "background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #14dbad, stop:0.5 #ff8f03, stop:1 #0688f6);"
                                 "border-radius:5px;"
                                 "margin:1px;"
                                 "}"
                                 );

    QRect ret = this->rect();
    ret.setRect(ret.x()+10, ret.y() + ret.height() - 40, ret.width() - 20, m_progressbar->height());
    m_progressbar->setGeometry(ret);
//    playerWelcome();
    showMessage(QString::fromLocal8Bit("正在加载文件..."),Qt::AlignRight | Qt::AlignBottom,Qt::yellow);

}

CSplashScreen::CSplashScreen( const QString gifname)
{
//    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground,true);
    m_move  = new QMovie(gifname);
    timer   = new QTimer(this);
    m_progressbar = new QProgressBar(this);
    m_progressbar->setFixedHeight(14);
    m_progressbar->setObjectName(QString::fromUtf8("splash_progressbar"));
    m_progressbar->setValue(0);
    m_progressbar->setStyleSheet("#splash_progressbar{"
                                 "color: #d10c64;"
                                 "text-align:center;"
                                 "background-color: #303030;"
                                 "border-radius:7px;"
                                 "border: 1px solid #424041;"
                                 "}"
                                 "#splash_progressbar::chunk "
                                 "{"
                                 "background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 #14dbad, stop:0.5 #ff8f03, stop:1 #0688f6);"
                                 "border-radius:5px;"
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
    qDebug() << "roate = " << roate;
    setPixmap(m_move->currentPixmap());
    showMessage(QString::fromLocal8Bit("正在加载信息。。。%1").arg(roate),Qt::AlignHCenter | Qt::AlignBottom,Qt::blue);
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
    QLinearGradient gradient(0, 0, 200,200);  // 创建线性渐变，从左上到右下
    gradient.setColorAt(0, QColor(0, 245, 244,255));  // 渐变起始颜色，紫色
    gradient.setColorAt(0.33, QColor(9, 141, 235,255)); // 中间颜色，绿色
    gradient.setColorAt(0.66, QColor(235, 90, 124,255)); // 中间颜色，绿色
    gradient.setColorAt(1, QColor(124, 2, 185, 255));   // 渐变终止颜色，黄色

    painter->setFont(QFont("Mircrosoft YaHei", 36));
//    painter->setPen(QPen(QBrush(gradient),20));
    painter->setPen(QPen(QColor(23, 159, 177),20));
    QRect rec_title = rect();
    rec_title.setRect(rec_title.x(), rec_title.y(), rec_title.width(), 80);
//    painter->drawText(QPointF(20, 80), QString(u8"Qt音视频播放器"));
    painter->drawText(rec_title, Qt::AlignBottom | Qt::AlignCenter, QString(u8"音视频播放器"));

    painter->setFont(QFont("Mircrosoft YaHei", 12,QFont::Bold));
    painter->setPen(QPen(QColor(83, 156, 178),20));
    painter->drawText(QPointF(30, 140), QString(u8"Version: 1.5.0"));

    painter->setFont(QFont("Mircrosoft YaHei", 12,QFont::Bold));
    painter->setPen(QPen(QColor(35, 171, 117),20));
    painter->drawText(QPointF(30, 180), QString(u8"Author: ZhangHui"));

    painter->setFont(QFont("Mircrosoft YaHei", 12,QFont::Bold));
    painter->setPen(QPen(QColor(83, 156, 178),20));
    painter->drawText(QPointF(30, 220), QString(u8"Emails: 2493920797@qq.com"));

    painter->setFont(QFont("Mircrosoft YaHei", 12,QFont::Bold));
    painter->setPen(QPen(QColor(35, 171, 117),20));
    painter->drawText(QPointF(30, 260), QString(u8"Based on: Qt 5.12.0 (MSVC2017 64bit 编译) + MySQL 5.7.36 for Linux (x86_64)"));

    painter->setFont(QFont("Helvetica", 16, 800));
    painter->setPen(QColor(23, 164, 184));
    QRect r = rect();
    r.setRect(r.x(), r.y(), r.width(), r.height() -75);
    painter->drawText(r, Qt::AlignBottom | Qt::AlignCenter, edition);

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
            showMessage(QString::fromLocal8Bit("文件加载完成！"),Qt::AlignRight | Qt::AlignBottom,Qt::yellow);//右下角,黄色字体
    }
}

