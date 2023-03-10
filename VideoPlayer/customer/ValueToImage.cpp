#include "ValueToImage.h"
#include "ui_ValueToImage.h"

ValueToImage::ValueToImage(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::ValueToImage)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(150,100);
    initWoruUI();
}

ValueToImage::~ValueToImage()
{
//    delete m_waitingMovie;
    delete ui;
}

void ValueToImage::initWoruUI()
{
    ui->label_jingdu->setFixedSize(60,20);
    ui->label_jingdu->setAlignment(Qt::AlignCenter);
//    m_waitingMovie = new QMovie(":/images/bgpic/loading_001.gif");
//    this->setMovie(m_waitingMovie);
}

void ValueToImage::slot_setValueImageTime(const int time)
{
    //将进度（position）秒数转化为时分秒格式
    int H = time / (60*60);
    int M = (time - (H * 60 * 60)) / 60;
    int S = (time - (H * 60 * 60)) - M * 60;
    QString hour = QString::number(H);
    if (hour.length() == 1) hour = "0" + hour;
    QString min = QString::number(M);
    if (min.length() == 1) min = "0" + min;
    QString sec = QString::number(S);
    if (sec.length() == 1) sec = "0" + sec;
    QString qTime = hour + ":" + min + ":" + sec;
    ui->label_jingdu->setText(qTime);
}

void ValueToImage::slot_setValueImage(QImage &image)
{
//    if(m_waitingMovie->state() == QMovie::Running)
//    {
//        m_waitingMovie->setPaused(true);
//    }
    this->setPixmap(QPixmap::fromImage(image).scaled(this->size()));
//    if(m_waitingMovie->state() == QMovie::Running)
//    {
//        qDebug() << QString(u8"动画正在运行...");
//        return;

//    }
//    m_waitingMovie->start();
}

void ValueToImage::slot_setWaitingStatus(const QString& text)
{
    qDebug() << QString(u8"player2当前状态：") << text;
//    if(m_waitingMovie->state() == QMovie::Running)
//    {
//        qDebug() << QString(u8"动画正在运行...");
//        return;

//    }
//    m_waitingMovie->start();
}
