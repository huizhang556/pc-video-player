#include "MusicPlayShow.h"
#include "ui_MusicPlayShow.h"
#include "musicmodels/FontColor.h"
#include "musicmodels/MusicLeftTip.h"
#include <QDebug>

MusicPlayShow::MusicPlayShow(QWidget *parent) :
    QWidget(parent),
    m_skinPath(u8"本地图片"),//默认显示
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

//    if(photo != nullptr)
//        delete photo;
//    photo = nullptr;
}

void MusicPlayShow::initWorkUI()
{
    photo = new QPixmap();
}

void MusicPlayShow::handleSignalsAndSlots()
{
    connect(Global::getInstance(),&Global::sig_sendGlobalTimeOut,[=]()
    {
        fileName = Global::appDirPath + switchSkin(m_skinPath).arg(i);
        loadPictures(fileName);
        changeTimeCout();
    });

    //切换皮肤
    connect(FontColor::getInstance(),&FontColor::sig_send_switchskin,[=](QString skin){
        m_skinPath = skin;
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
    if(++i > 9)
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

const QString MusicPlayShow::switchSkin(const QString &text)
{
    QString path_t;
    if(text == QString(u8"歌手写真"))
    {
        path_t = QString("/pictures/songers/songer%1.jpg");
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(text == QString(u8"酷我皮肤"))
    {
        path_t = QString("/pictures/musics/fashion/music%1.png");
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if(text == QString(u8"本地图片"))
    {
        path_t = QString("/pictures/musicwall/%1.png");
    }
    return path_t;
}
