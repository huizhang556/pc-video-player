#include "MusicPlayShow.h"
#include "ui_MusicPlayShow.h"
#include <QDebug>

MusicPlayShow::MusicPlayShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayShow)
{

    ui->setupUi(this);
//    ui->labelSong->setAlignment(Qt::AlignCenter);
    photo = new QPixmap;
    //    photo->load("./pictures");
    time = new QTimer(this);
    time->start(6000);
    connect(time,&QTimer::timeout,[=]()
    {
        /********release时使用***************/
//        QString exepath = qApp->applicationDirPath();
//        fileName = exepath + QString("/pictures/%1.png").arg(i);
//        qDebug()<<fileName;
        /***********debug时候使用************/
       fileName = QString("E:/QtProjects/000QtDemo_51ctodemo/04_20VideosPlayer/pictures/%1.png").arg(i);//只能使用png格式的图片
        loadPictures(fileName);
        changeTimeCout();
    });

}

MusicPlayShow::~MusicPlayShow()
{
    delete ui;
}

/*显示图片*/
void MusicPlayShow::loadPictures(QString &path) const
{
    photo->load(path);
    ui->labelPicture->setPixmap(*photo);
    //图片自适应显示
    ui->labelPicture->setScaledContents(true);

}

void MusicPlayShow::changeTimeCout()
{
    if(++i > 15)
        i = 1;
}

void MusicPlayShow::receiveMainWinData(QString name)
{
//    ui->label_title->clear();
//    ui->labelSong->clear();
//    ui->label_title->setText(QString::fromLocal8Bit(""));
//    ui->labelSong->setText(name);
}
