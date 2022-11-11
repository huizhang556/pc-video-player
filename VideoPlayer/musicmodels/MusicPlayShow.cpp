#include "MusicPlayShow.h"
#include "ui_MusicPlayShow.h"
#include "musicmodels/FontColor.h"
#include "musicmodels/MusicLeftTip.h"
#include <QDebug>

MusicPlayShow::MusicPlayShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayShow)
{

    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

MusicPlayShow::~MusicPlayShow()
{
    delete ui;
}

void MusicPlayShow::initWorkUI()
{
    photo = new QPixmap;
}

void MusicPlayShow::handleSignalsAndSlots()
{
    connect(Global::getInstance(),&Global::sig_sendGlobalTimeOut,[=]()
    {
        fileName = Global::appDirPath + QString("/pictures/musicwall/%1.png").arg(i);
        loadPictures(fileName);
        changeTimeCout();
    });

    //字体大小
    connect(FontColor::getInstance(),&FontColor::sig_send_fontsize,[=](int size){
        ui->labelPicture->setCurrentTextFontSize(size);
    });
    //字体颜色
    connect(FontColor::getInstance(),&FontColor::sig_send_fontcolor,[=](QString color){
        ui->labelPicture->setCurrentTextFontColor(color);
    });
}

void MusicPlayShow::setInstallEventFilter()
{
    this->installEventFilter(this);
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

bool MusicPlayShow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            MusicLeftTip::getInstance()->setParent(this);
            MusicLeftTip::getInstance()->move(-1,80);
            MusicLeftTip::getInstance()->show();
        }
    }
    return QWidget::eventFilter(watched,event);
}
