#include "FloatPlayCtl.h"
#include "ui_FloatPlayCtl.h"
#include <QDebug>

FloatPlayCtl* FloatPlayCtl::m_pInstance = NULL;//初始化指针

FloatPlayCtl::FloatPlayCtl(QWidget *parent) :
    QWidget(parent),
    m_playStatus(false),//默认正在播放状态
    m_soundStatus(true),//默认没静音
    ui(new Ui::FloatPlayCtl)
{
    ui->setupUi(this);
    //去掉标题栏,窗口始终在最前面（鼠标点击也在最前面）
    this->setWindowFlags(Qt::FramelessWindowHint| Qt::Tool | Qt::WindowStaysOnTopHint);
    this->setFixedHeight(80);
    this->setMouseTracking(true);
    initWorkUI();
    chandleSignalsAndSlots();
}

//获取单例
FloatPlayCtl *FloatPlayCtl::getInstance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new FloatPlayCtl();
    }
    return m_pInstance;
}

void FloatPlayCtl::setHorzontalSlider_PlayerRange(int start, int end)
{
    ui->horizontalSlider_playProgress->setRange(start,end);
}

void FloatPlayCtl::setHorzontalSlider_VoiceRange(int start, int end)
{
    ui->horizontalSlider_voiceProgress->setRange(start,end);
}

FloatPlayCtl::~FloatPlayCtl()
{
    delete ui;
    //删除创建的单例
    if(m_pInstance != NULL)
        delete m_pInstance;
    m_pInstance = NULL;
}

void FloatPlayCtl::initWorkUI()
{
    //    QPalette myPalette;
    //    QColor myColor(255,255,255);
    //    myColor.setAlphaF(0.1);
    //    myPalette.setBrush(backgroundRole(),myColor);
    //    this->setPalette(myPalette);
    //    this->setAutoFillBackground(true);
    //    QGraphicsOpacityEffect *goe = new QGraphicsOpacityEffect();
    //    this->setGraphicsEffect(goe);
    //    goe->setOpacity(0.0);
    setAttribute(Qt::WA_TranslucentBackground, true);//背景透明
    //    setWindowOpacity(0.2);//子控件内所有的透明度都会变（不好用）
    ui->horizontalSlider_playProgress->installEventFilter(this);
//    ui->horizontalSlider_playProgress->setTickInterval(1);//间隔为1（100份，间隔为2，分为50个间隔）

    ui->horizontalSlider_voiceProgress->setRange(0,100);
    ui->horizontalSlider_voiceProgress->setPageStep(5);
    ui->horizontalSlider_voiceProgress->setValue(10);
    //初始播放状态
    ui->pushButton_start->setStyleSheet("QPushButton{"
                                        "border-radius:20px;"
                                        "background-color: rgba(255,255,255,0.1);"
                                        "border-image: url(:/images/tray/tray_pause.png);"
                                        "}");
    //初始非静音状态
    ui->pushButton_voice->setStyleSheet("QPushButton{"
                                       "border-image: url(:/images/tray/tray_sound.png);"
                                       "}");
    ui->pushButton_fullScreen->setToolTip(QString::fromLocal8Bit("退出全屏"));
}

void FloatPlayCtl::chandleSignalsAndSlots()
{
    //退出全屏
    connect(ui->pushButton_fullScreen,&QPushButton::clicked,[=](){emit sig_sendExitFullscreen();});
    //上一首
    connect(ui->pushButton_previous,&QPushButton::clicked,[=](){emit sig_sendPlayPrevious();});
    //下一首
    connect(ui->pushButton_next,&QPushButton::clicked,[=](){emit sig_sendPlayNext();});
    //开始暂停
    connect(ui->pushButton_start,&QPushButton::clicked,[=](){emit sig_sendPlayStartPause();});
    //静音
    connect(ui->pushButton_voice,&QPushButton::clicked,[=](){
        if(ui->horizontalSlider_voiceProgress->value() == 0) return;
        emit sig_sendPlayMute(m_soundStatus);
    });

    /*按下*/
    connect(ui->horizontalSlider_playProgress,&QSlider::sliderPressed,[=](){
        m_bPress = true;
    });

    /*释放*/
    connect(ui->horizontalSlider_playProgress,&QSlider::sliderReleased,[=](){
        m_bPress = false;
    });

    //播放进度改变,不用valuechange因为有延迟，导致数据不统一
    connect(ui->horizontalSlider_playProgress,&QSlider::sliderMoved,[=](int pos){
        if(m_bPress)
        {
            emit sig_sendProgress_player(pos);
            qDebug() << QString::fromLocal8Bit("浮动窗口拖动进度值已发送：")<< pos;
        }
    });
    //音量调节进度改变
    connect(ui->horizontalSlider_voiceProgress,&QSlider::valueChanged,[=](int value){
        emit sig_sendProgress_voice(value);
        slot_setCurrentPlayMutedStatus(value);
    });
}

void FloatPlayCtl::slot_setProgressbar_player(int value)
{
    ui->horizontalSlider_playProgress->setValue(value);
}

void FloatPlayCtl::slot_setProgressbar_voice(int value)
{
    ui->horizontalSlider_voiceProgress->setValue(value);
}

void FloatPlayCtl::slot_setPlayer_mute(bool mute)
{
    if(mute)//静音
    {
        ui->pushButton_voice->setIcon(QIcon(""));
    }
    else//非静音
    {
        ui->pushButton_voice->setIcon(QIcon(""));
    }
}

void FloatPlayCtl::slot_setMediaPlayName(QString name)
{
    ui->pushButton_name->setText(name);
}

void FloatPlayCtl::slot_setMediaPlayTime(QString time)
{
    ui->label_progressbar->setText(time);
}

void FloatPlayCtl::slot_setCurrentPlayStatus(bool status)
{
    qDebug() << "TRAY HAS RECEIVED CURRENT MEDIA NEW STATUS:" << status;
    if(!status)//播放
    {
        ui->pushButton_start->setStyleSheet("QPushButton{"
                                            "border-radius:20px;"
                                            "background-color: rgba(255,255,255,0.1);"
                                            "border-image: url(:/images/tray/tray_pause.png);"
                                            "}");
        m_playStatus = false;//暂停状态
    }
    else
    {
        ui->pushButton_start->setStyleSheet("QPushButton{"
                                            "border-radius:20px;"
                                            "background-color: rgba(255,255,255,0.1);"
                                            "border-image: url(:/images/tray/tray_play.png);"
                                            "}");
        m_playStatus = true;//播放状态
    }
}

void FloatPlayCtl::slot_setCurrentMediaMutedStyleSheet(bool status)
{
    if(status)
    {
        ui->pushButton_voice->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/tray/tray_muted.png);"
                                           "}");
    }
    else
    {
        ui->pushButton_voice->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/tray/tray_sound.png);"
                                           "}");
    }
    m_soundStatus = !m_soundStatus;
}

void FloatPlayCtl::slot_setCurrentPlayMutedStatus(int value)
{
    if(value == 0)
    {
        ui->pushButton_voice->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/tray/tray_muted.png);"
                                           "}");
        m_soundStatus = false;
    }
    else
    {
        ui->pushButton_voice->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/tray/tray_sound.png);"
                                           "}");
        m_soundStatus = true;
    }
}

bool FloatPlayCtl::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->horizontalSlider_playProgress)
    {
//        if(event->type() == QEvent::Enter)
//        {
//            ui->horizontalSlider_playProgress->setToolTip(QString::number(ui->horizontalSlider_playProgress->tickInterval()));
//        }
//        else if(event->type() == QEvent::Leave)
//        {

//        }
    }
    return QWidget::eventFilter(watched,event);
}
