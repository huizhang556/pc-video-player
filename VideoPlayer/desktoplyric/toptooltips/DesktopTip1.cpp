#include "DesktopTip1.h"
#include "ui_DesktopTip1.h"
#include <QSoundEffect>
#include <QApplication>
#include <QDesktopServices>
#include <QScreen>
#include <QDebug>

DesktopTip1* DesktopTip1::instance = nullptr;
DesktopTip1::AnimationMode DesktopTip1::mode = DesktopTip1::AllAnimation;

DesktopTip1::DesktopTip1() :
    QWidget(nullptr),
    showGroup(new QParallelAnimationGroup(this)),
    ui(new Ui::DesktopTip1)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose);
    //setWindowModality(Qt::WindowModal);

    //resize会被label撑开
//    setFixedSize(310,210);
    setFixedSize(260,200);
    //设置可以自动打开链接，也可以链接信号与槽函数
    ui->contentLabel->setOpenExternalLinks(true);
    ui->contentLabel->setWordWrap(true);
    //响应打开链接信号
//    connect(ui->contentLabel,&QLabel::linkActivated,[=](const QString& link){
//        QDesktopServices::openUrl(QUrl(link));
//    });

    //关闭
    connect(ui->btnClose,&QPushButton::clicked,this,&DesktopTip1::hideTip);
    //程序退出时释放
    connect(qApp,&QApplication::aboutToQuit,this,&DesktopTip1::close);
    //动画设置
    initAnimation();
    //定时器设置
    initTimer();
}

DesktopTip1::~DesktopTip1()
{
    delete ui;
}

void DesktopTip1::showTip(const QStringList &texts, int timeout)
{
    QSoundEffect    *effect = new QSoundEffect();
    effect->setSource(QUrl::fromLocalFile(":/audio/player/tooltips.wav"));
    effect->setLoopCount(1);  //循环次数
    effect->setVolume(0.30f); //音量  0~1之间
    effect->play();

    if(!instance)
    {
        //仅在ui线程
        instance = new DesktopTip1;
    }
    instance->readyTimer(timeout);
    //模态框
    instance->setWindowModality(Qt::WindowModal);
    instance->setTextList(texts);
    instance->showAnimation();
    //延迟删除
    QTimer::singleShot(1000,0,[=](){
        qDebug() << QString(u8"showTip delete effect");
        delete effect;
    });
}

void DesktopTip1::showTip(const QStringList &texts, const QStringList &urls, int timeout)
{
    QSoundEffect *effect = new QSoundEffect();
    effect->setSource(QUrl::fromLocalFile(":/audio/player/tooltips.wav"));
    effect->setLoopCount(1);  //循环次数
    effect->setVolume(0.30f); //音量  0~1之间
    effect->play();

    if(!instance)
    {
        //仅在ui线程
        instance = new DesktopTip1;
    }
    instance->readyTimer(timeout);
    //模态框
    instance->setWindowModality(Qt::WindowModal);
    instance->setTextList(texts,urls);
    instance->showAnimation();
    //延迟删除
    QTimer::singleShot(1000,0,[=](){
        qDebug() << QString(u8"showTip delete effect");
        delete effect;
    });
}

void DesktopTip1::keepTip(const QStringList &texts)
{
    QSoundEffect    *effect = new QSoundEffect();
    effect->setSource(QUrl::fromLocalFile(":/audio/player/tooltips.wav"));
    effect->setLoopCount(1);  //循环次数
    effect->setVolume(0.30f); //音量  0~1之间
    effect->play();

    if(!instance)
    {
        //仅在ui线程
        instance = new DesktopTip1;
    }
    instance->readyTimer(0);
    //模态框
    instance->setWindowModality(Qt::WindowModal);
    instance->setTextList(texts);
    instance->keepAnimation();
    //延迟删除
    QTimer::singleShot(1000,0,[=](){
        delete effect;
        qDebug() << QString(u8"Keeptip delete effect");
    });
}

void DesktopTip1::keepTip(const QStringList &texts, const QStringList &urls)
{
    QSoundEffect    *effect = new QSoundEffect();
    effect->setSource(QUrl::fromLocalFile(":/audio/player/tooltips.wav"));
    effect->setLoopCount(1);  //循环次数
    effect->setVolume(0.30f); //音量  0~1之间
    effect->play();

    if(!instance)
    {
        //仅在ui线程
        instance = new DesktopTip1;
    }
    instance->readyTimer(0);
    //模态框
    instance->setWindowModality(Qt::WindowModal);
    instance->setTextList(texts,urls);
    instance->keepAnimation();
    //延迟删除
    QTimer::singleShot(1000,0,[=](){
        delete effect;
        qDebug() << QString(u8"Keeptip delete effect");
    });
}

void DesktopTip1::hideTip()
{
    if(!instance)
    {
        return;
    }
    instance->hideAnimation();
}

DesktopTip1::AnimationMode DesktopTip1::getMode()
{
    return mode;
}

void DesktopTip1::setMode(DesktopTip1::AnimationMode newMode)
{
    if(mode != newMode)
    {
        mode = newMode;
    }
}

void DesktopTip1::initAnimation()
{
    //透明度动画
    showOpacity=new QPropertyAnimation(this,"windowOpacity");
    //判断是否设置了此模式的动画
    if( mode & AnimationMode::OpacityAnimation)
    {
        showOpacity->setDuration(1500);
        showOpacity->setStartValue(0);
    }
    else
    {
        showOpacity->setDuration(0);
        showOpacity->setStartValue(1);
    }
    showOpacity->setEndValue(1);
    showGroup->addAnimation(showOpacity);

    //位置动画
    showPos = new QPropertyAnimation(this,"pos");
    QScreen * screen = QGuiApplication::primaryScreen();
    if (screen)
    {
        const QRect desk_rect = screen->availableGeometry();
        const QPoint hide_pos{desk_rect.width()-this->width(),
                    desk_rect.height()};

        const QPoint show_pos{desk_rect.width()-this->width(),
                    desk_rect.height()-this->height()};

        //判断是否设置了此模式的动画
        if(mode & AnimationMode::PosAnimation)
        {
            showPos->setDuration(1500);
            showPos->setStartValue(hide_pos);
        }
        else
        {
            showPos->setDuration(0);
            showPos->setStartValue(show_pos);
        }
        showPos->setEndValue(show_pos);
    }
    showGroup->addAnimation(showPos);
    //
    connect(showGroup,&QParallelAnimationGroup::finished,[this](){
        //back消失动画结束关闭窗口
        if(showGroup->direction() == QAbstractAnimation::Backward)
        {
            //Qt::WA_DeleteOnClose后手动设置为null
            instance = nullptr;
            qApp->disconnect(this);
            //关闭时设置为非模态，方式主窗口被遮挡，待测试
            this->setWindowModality(Qt::NonModal);
            this->close();
        }
        else
        {
            //配合keepAnimation
            showAnimEnd = true;
            //配合定时关闭
            if(hideCount > 0)
               hideTimer->start();
        }
    });
}

void DesktopTip1::initTimer()
{
    hideTimer = new QTimer(this);
    hideTimer->setInterval(1000); //1s间隔
    connect(hideTimer,&QTimer::timeout,[this](){
        if(hideCount > 1)
        {
            hideCount--;
            ui->btnClose->setText(QString("%1 S").arg(hideCount));
        }
        else
        {
            ui->btnClose->setText(QString(u8"关闭"));
            hideTimer->stop();
            hideTip();
        }
    });
}

void DesktopTip1::readyTimer(int timeout)
{
    //先设置，在显示动画结束再start开始计时器
    hideCount = timeout;
    hideTimer->stop();

    if(hideCount > 0)
    {
        ui->btnClose->setText(QString("%1 S").arg(hideCount));
    }
    else
    {
        ui->btnClose->setText(QString(u8"关闭"));
    }
}

void DesktopTip1::showAnimation()
{
    showGroup->setDirection(QAbstractAnimation::Forward);
    //停止正在进行的动画重新
    if(showGroup->state() == QAbstractAnimation::Running)
    {
        showGroup->stop();
    }
    showGroup->start();
    show();
}

void DesktopTip1::keepAnimation()
{
    //show没有完成，或者正在动画中才进入
    if(!showAnimEnd || showGroup->state() != QAbstractAnimation::Stopped)
    {
        showGroup->setDirection(QAbstractAnimation::Forward);
        showGroup->start();
        show();
    }
}

void DesktopTip1::hideAnimation()
{
    //Backward反向执行动画
    showGroup->setDirection(QAbstractAnimation::Backward);
    showGroup->start();
}

void DesktopTip1::setTextList(const QStringList &texts)
{
    QString tip_text("<p style='line-height:120%'>");
    for (const QString &text : texts)
    {
        if (text.isEmpty())
            continue;
        QString t_text = QString(u8"<span style = 'font-size: 13px; color:#38e054;'>%1</span>").arg(text);
        tip_text += t_text + "<br>";
    }
    tip_text += "</p>";
    ui->contentLabel->setText(tip_text);
}

void DesktopTip1::setTextList(const QStringList &texts, const QStringList &urls)
{
    QString tip_text("<p style='line-height:120%'>");
    //普通文字显示
    for (const QString &text : texts)
    {
        if (text.isEmpty())
            continue;
        QString t_text = QString(u8"<span style = 'font-size: 13px; color:#38e054;'>%1</span>").arg(text);
        tip_text += t_text + "<br>";//换行
    }

    //链接显示
    for(const QString &url : urls)
    {
        if(url.isEmpty())
            continue;
       QString t_url = QString(u8"<a href = %1 style ='text-decoration:underline; font-size: 13px; color:#009bdb;'>%2</a>").arg(url).arg(url);
        tip_text += t_url + "<br>";//换行
    }
    tip_text += "</p>";//这是一个段落
    ui->contentLabel->setText(tip_text);
}
