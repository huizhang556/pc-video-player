#include "SystemTray.h"
#include "ui_SystemTray.h"
#include <QDebug>

//SystemTray* SystemTray::m_pInstance = NULL;

SystemTray::SystemTray(QWidget *parent) :
    QWidget(parent),
    m_playStatus(true),//默认正在播放状态
    m_soundStatus(true),//默认没静音
    ui(new Ui::SystemTray)
{
    ui->setupUi(this);
    this->setFixedSize(200,95);
    initWorkUI();
    chandleSignalsAndSlots();
//    this->setMouseTracking(true);//鼠标跟踪
}

SystemTray::~SystemTray()
{
    delete ui;
    //删除创建的单例
//    if(m_pInstance != NULL)
//        delete m_pInstance;
    //    m_pInstance = NULL;
}

void SystemTray::initWorkUI()
{
    //初始播放状态
    ui->pushButton_pause->setStyleSheet("QPushButton{"
                                        "border-image: url(:/images/tray/tray_play.png);"
                                        "}");
    //初始非静音状态
    ui->pushButton_mute->setStyleSheet("QPushButton{"
                                       "border-image: url(:/images/tray/tray_sound.png);"
                                       "}");
    //初始10%音量值
    ui->horizontalSlider_sound->setRange(0,100);
    ui->horizontalSlider_sound->setPageStep(5);
    ui->horizontalSlider_sound->setValue(10);
    ui->label_percentage->setText(QString::fromLocal8Bit("10%"));
}

void SystemTray::chandleSignalsAndSlots()
{
    //上一首信号
    connect(ui->pushButton_previous,&QPushButton::clicked,[=](){
        emit sig_playStatusPrevious();
        slot_updatePlayButtonStatusStyleSheet();
        qDebug() << "emit sig_playStatusPrevious();";
    });
    //下一首信号
    connect(ui->pushButton_next,&QPushButton::clicked,[=](){
        emit sig_playStatusNext();
        slot_updatePlayButtonStatusStyleSheet();
        qDebug() << "emit sig_playStatusNext()";
    });
    //暂停/开始信号
    connect(ui->pushButton_pause,&QPushButton::clicked,[=](){
        emit sig_playStatusPause(m_playStatus);
        qDebug() <<"emit sig_playStatusPause()" <<m_playStatus ;
    });
    //静音/打开信号
    connect(ui->pushButton_mute,&QPushButton::clicked,[=](){
            if(ui->horizontalSlider_sound->value() == 0) return;
        slot_setCurrentMediaMutedStyleSheet();//只更新样式
        emit sig_playStatusMuted(m_soundStatus);
        qDebug() <<"emit sig_playStatusMuted()" << m_soundStatus;
    });
    //进度条值
    connect(ui->horizontalSlider_sound,&QSlider::valueChanged,[=](int value){
        emit sig_playProgressValue(value);
        slot_setCurrentPlayMutedStatus(value);
        slot_setCurrentMediaSoundShowToop(value);
        qDebug() << "emit sig_playProgressValue(value);" << value;
    });

}

void SystemTray::slot_setCurrentPlayStatus(bool status)
{
    if(!status)//播放
    {
        ui->pushButton_pause->setStyleSheet("QPushButton{"
                                            "border-image: url(:/images/tray/tray_pause.png);"
                                            "}");
        m_playStatus = false;//暂停状态
    }
    else
    {
        ui->pushButton_pause->setStyleSheet("QPushButton{"
                                            "border-image: url(:/images/tray/tray_play.png);"
                                            "}");
        m_playStatus = true;//播放状态
    }
}

void SystemTray::slot_setCurrentPlaySoundValue(int value)
{
    ui->horizontalSlider_sound->setValue(value);
}

void SystemTray::slot_setCurrentMediaMutedStyleSheet()
{
    if(m_soundStatus)
    {
        ui->pushButton_mute->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/tray/tray_muted.png);"
                                           "}");
    }
    else if(!m_soundStatus)
    {
        ui->pushButton_mute->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/tray/tray_sound.png);"
                                           "}");
    }
    m_soundStatus = !m_soundStatus;
}

void SystemTray::slot_setCurrentPlayMutedStatus(int value)
{
    if(value == 0)
    {
        ui->pushButton_mute->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/tray/tray_muted.png);"
                                           "}");
        m_soundStatus = false;
    }
    else
    {
        ui->pushButton_mute->setStyleSheet("QPushButton{"
                                           "border-image: url(:/images/tray/tray_sound.png);"
                                           "}");
        m_soundStatus = true;
    }
}

void SystemTray::slot_setCurrentMediaSoundShowToop(int value)
{
    ui->label_percentage->setText(QString::fromLocal8Bit("%1%").arg(value));
}

void SystemTray::slot_updatePlayButtonStatusStyleSheet()
{
    ui->pushButton_pause->setStyleSheet("QPushButton{"
                                        "border-image: url(:/images/tray/tray_play.png);"
                                        "}");
    m_playStatus = true;//播放状态
}

///*获取单例*/
//SystemTray *SystemTray::getInstance()
//{
//    if(m_pInstance != NULL)
//    {
//        m_pInstance = new SystemTray();
//    }
//    return m_pInstance;
//}
