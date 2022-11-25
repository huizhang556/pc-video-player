#include "MiniPlayer.h"

MiniPlayer::MiniPlayer(QWidget *parent) :
    QWidget(parent)
{
    initWorkUI();
    handleSignalsAndSlots();
}

MiniPlayer::~MiniPlayer()
{
    delete  m_subMenu1;
    delete  m_subMenu2;
    delete  m_videoMenu;
    delete  m_clityListWgt;
    delete  m_frameSound;
}

void MiniPlayer::initWorkUI()
{
    createRightMenu();//创建右键菜单

    m_timer = new QTimer(this);
    m_timer->start(1000);

    m_frameTitle = new QFrame(this);
    m_frameTitle->setContentsMargins(0,0,0,0);
    m_frameTitle->setFixedHeight(FIXEDHEIGHT);
    m_frameTitle->setMinimumWidth(700);
    m_frameTitle->setObjectName(QString::fromUtf8(u8"m_miniframeTitle"));

    m_buttonTitle = new QPushButton(QString(u8"我是播放器我是播放器我是播放器我是播放器我是播放器"));
    m_buttonTitle->setObjectName(QString::fromUtf8("m_minibuttonTitle"));
    m_buttonTitle->setMinimumSize(600,FIXEDHEIGHT-4);
    QHBoxLayout *hblayout1 = new QHBoxLayout();
    hblayout1->setSpacing(0);
    hblayout1->setMargin(0);
    hblayout1->setContentsMargins(0,0,0,0);
    hblayout1->addWidget(m_buttonTitle);
    hblayout1->addSpacerItem(new QSpacerItem(10,FIXEDHEIGHT,QSizePolicy::Expanding,QSizePolicy::Fixed));
    m_frameTitle->setLayout(hblayout1);

    m_frameControl = new QFrame(this);
    m_frameControl->setContentsMargins(0,0,0,0);
    m_frameControl->setFixedHeight(FIXEDHEIGHT+12);//加一个进度条高度
    m_frameControl->setMinimumWidth(700);
    m_frameControl->setObjectName(QString::fromUtf8(u8"m_miniframeControl"));

    m_clityListWgt = new QListWidget();
    m_clityListWgt->installEventFilter(this);
    m_clityListWgt->setFixedSize(80,150);
    m_clityListWgt->setLayoutDirection(Qt::RightToLeft);//图标在右侧,文字的布局方向也变反了
    m_clityListWgt->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    m_clityListWgt->setHidden(true);//指定父亲默认是显示在父亲的左上角
    m_clityListWgt->setFrameShape(QFrame::NoFrame);
    m_clityListWgt->setObjectName(QString::fromUtf8("m_miniclityListWgt"));
    QListWidgetItem *item_clity1 = new QListWidgetItem(QIcon("://images/user/itemmark_vyp.png"),QString(u8"标清"));
    QListWidgetItem *item_clity2 = new QListWidgetItem(QIcon("://images/user/itemmark_vyp.png"),QString(u8"720P"));
    QListWidgetItem *item_clity3 = new QListWidgetItem(QIcon("://images/user/itemmark_vyp.png"),QString(u8"高清"));
    QListWidgetItem *item_clity4 = new QListWidgetItem(QIcon("://images/user/itemmark_vyp.png"),QString(u8"1080P"));
    QListWidgetItem *item_clity5 = new QListWidgetItem(QIcon("://images/user/itemmark_vyp.png"),QString(u8"蓝光"));
    item_clity1->setSizeHint(QSize(80,30));
    item_clity2->setSizeHint(QSize(80,30));
    item_clity3->setSizeHint(QSize(80,30));
    item_clity4->setSizeHint(QSize(80,30));
    item_clity5->setSizeHint(QSize(80,30));
    item_clity1->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
    item_clity2->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
    item_clity3->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
    item_clity4->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
    item_clity5->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
    m_clityListWgt->addItem(item_clity5);
    m_clityListWgt->addItem(item_clity4);
    m_clityListWgt->addItem(item_clity3);
    m_clityListWgt->addItem(item_clity2);
    m_clityListWgt->addItem(item_clity1);

    m_frameSound = new QFrame();
    m_frameSound->installEventFilter(this);
    m_frameSound->setContentsMargins(0,0,0,0);
    m_frameSound->setFixedSize(30,120);//加一个进度条高度
    m_frameSound->setHidden(true);//指定父亲默认是显示在父亲的左上角
    m_frameSound->setObjectName(QString::fromUtf8(u8"m_miniframeSound"));
    m_frameSound->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);

    m_verSlider = new QSlider(Qt::Vertical);
    m_verSlider->setFixedSize(30,100);
    m_verSlider->setRange(0,100);
    m_verSlider->setValue(10);
    m_verSlider->setSingleStep(5);
    m_verSlider->setObjectName(QString::fromUtf8("m_miniverSlider"));
    QVBoxLayout *vblayout0 = new QVBoxLayout(m_frameSound);//指定父亲，相当于设置布局
    vblayout0->setSpacing(0);
    vblayout0->setContentsMargins(0,0,0,0);
    vblayout0->setMargin(0);
    vblayout0->addWidget(m_verSlider);

    m_horSlider = new QSlider(Qt::Horizontal);
    m_horSlider->setFixedHeight(12);
    m_horSlider->setObjectName(QString::fromUtf8("m_minihorSlider"));

    m_buttonPlayer = new QPushButton();
    m_buttonPlayer->setObjectName(QString::fromUtf8("m_minibuttonPlayer"));
    m_buttonPlayer->setFixedSize(20,20);
    m_buttonPlayer->setCheckable(true);

    m_buttonNext = new QPushButton();
    m_buttonNext->setObjectName(QString::fromUtf8("m_minibuttonNext"));
    m_buttonNext->setFixedSize(20,20);

    m_labelProgress = new QLabel();
    m_labelProgress->setText(QString(u8""));
    m_labelProgress->setObjectName(QString::fromUtf8("m_minilabelProgress"));
    m_labelProgress->setFixedSize(220,FIXEDHEIGHT-4);

    m_buttonClarity = new QPushButton(QString(u8"清晰度"));
    m_buttonClarity->installEventFilter(this);
    m_buttonClarity->setObjectName(QString::fromUtf8("m_minibuttonClarity"));
    m_buttonClarity->setFixedSize(60,20);

    m_buttonSound = new QPushButton();
    m_buttonSound->installEventFilter(this);
    m_buttonSound->setObjectName(QString::fromUtf8("m_minibuttonSound"));
    m_buttonSound->setFixedSize(20,20);
    m_buttonSound->setCheckable(true);

    QHBoxLayout *hblayout2 = new QHBoxLayout();
    hblayout2->setSpacing(10);
    hblayout2->setMargin(0);
    hblayout2->setContentsMargins(0,0,0,0);//左 上 右 下
    hblayout2->addWidget(m_buttonPlayer);
    hblayout2->addWidget(m_buttonNext);
    hblayout2->addWidget(m_labelProgress);
    hblayout2->addSpacerItem(new QSpacerItem(300,FIXEDHEIGHT,QSizePolicy::Expanding,QSizePolicy::Fixed));
    hblayout2->addWidget(m_buttonClarity);
    hblayout2->addWidget(m_buttonSound);

    QVBoxLayout *vblayout1 = new QVBoxLayout();
    vblayout1->setSpacing(0);
    vblayout1->setMargin(0);
    vblayout1->setContentsMargins(6,0,6,0);//左 上 右 下
    vblayout1->addWidget(m_horSlider);
    vblayout1->addLayout(hblayout2);
    m_frameControl->setLayout(vblayout1);

    m_videoWidget = new QVideoWidget();
    m_videoWidget->setContextMenuPolicy(Qt::CustomContextMenu);//自定义右键菜单

    QVBoxLayout *vblayout2 = new QVBoxLayout();
    vblayout2->setSpacing(0);
    vblayout2->setMargin(0);
    vblayout2->setContentsMargins(0,0,0,0);//上 右 下 左
    vblayout2->addWidget(m_videoWidget);
    this->setLayout(vblayout2);
    this->setContentsMargins(0,0,0,0);

    m_player = new QMediaPlayer(this);
    m_playlist = new QMediaPlaylist(m_player);
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
    m_playlist->addMedia(QUrl("http://43.143.226.251:8080/group1/tempvideo/temp001.flv"));
    m_player->setPlaylist(m_playlist);
    m_player->setVideoOutput(m_videoWidget);
    m_player->setMuted(false);//静音
    m_player->setVolume(10);
//    m_player->play();
}

void MiniPlayer::handleSignalsAndSlots()
{
    //定时器
    connect(m_timer,&QTimer::timeout,[=](){
        on_updatePosition();
    });
    //媒体状态改变
    connect(m_player,&QMediaPlayer::stateChanged,[=](QMediaPlayer::State newState){
        qDebug() << QString(u8"当前媒体状态：")<<newState;
        switch (newState)
        {
        case QMediaPlayer::State::PlayingState:
        {
            m_buttonPlayer->setChecked(true);
            emit sig_player_status(true);
        }
            break;
        case QMediaPlayer::State::PausedState:
        {
            m_buttonPlayer->setChecked(false);
            emit sig_player_status(false);
        }
            break;
        case QMediaPlayer::State::StoppedState:
        {
            m_buttonPlayer->setChecked(false);
            emit sig_player_status(false);
        }
            break;
        default:
            break;
        }
    });

    connect(m_buttonPlayer,&QPushButton::clicked,[=](bool checked){
        if(checked)
        {
            m_buttonPlayer->setChecked(true);
            m_player->play();
        }
        else
        {
            m_buttonPlayer->setChecked(false);
            m_player->pause();
        }
    });

    connect(m_buttonSound,&QPushButton::clicked,[=](bool checked){
        if(checked)
        {
            m_buttonSound->setChecked(true);
            m_player->setMuted(true);
        }
        else
        {
            m_buttonSound->setChecked(false);
            m_player->setMuted(false);
        }
    });

    connect(m_player,&QMediaPlayer::durationChanged,[=](){
        m_times = m_player->duration()/1000;
        m_horSlider->setRange(0,m_times);

    });

    connect(m_horSlider,&QSlider::sliderMoved,[=](int pos){
        m_player->setPosition(pos*1000);
    });

    //下一首
    connect(m_buttonNext,&QPushButton::clicked,[=](){
        emit sig_player_next();
    });

    //视频右键
    connect(m_videoWidget,&QVideoWidget::customContextMenuRequested,[=](){
        m_videoMenu->exec(QCursor::pos());
    });

    //全屏/退出全屏
    connect(m_screenAction,&QAction::triggered,[=](){
        if(m_screenAction->text() == QString(u8"全屏"))
        {
            m_videoWidget->setFullScreen(true);
            m_screenAction->setText(QString(u8"退出全屏"));
        }
        else if(m_screenAction->text() == QString(u8"退出全屏"))
        {
            m_videoWidget->setFullScreen(false);
            m_screenAction->setText(QString(u8"全屏"));
        }
    });
    //画面比例
    connect(m_actionGroup1,&QActionGroup::triggered,[=](QAction *action)
    {
        action->setChecked(true);
        slot_menu_scale(action);//发送信号
    });
    //播放速率
    connect(m_actionGroup2,&QActionGroup::triggered,[=](QAction *action)
    {
        action->setChecked(true);
        slot_menu_playrate(action);//发送信号
    });

    //音量大小
    connect(m_verSlider,&QSlider::valueChanged,[=](int value){
        m_player->setVolume(value);
    });
}

void MiniPlayer::slot_receivePlayMediaFile(const QString &mediaUrl, const QString &mediaName)
{
    m_player->stop();
    m_playlist->clear();
    m_playlist->addMedia(QUrl(mediaUrl));
    m_player->play();
    m_buttonTitle->setText(mediaName);
}

void MiniPlayer::slot_mouseEnter()
{
    m_frameTitle->show();
    m_frameControl->show();
}

void MiniPlayer::slot_mouseLeave()
{
    m_frameTitle->hide();
    m_frameControl->hide();
}

void MiniPlayer::slot_player_on()
{
    m_buttonPlayer->click();
}

bool MiniPlayer::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_buttonClarity)
    {
        int x = m_buttonClarity->parentWidget()->mapToGlobal(m_buttonClarity->pos()).x();
        int y = m_buttonClarity->parentWidget()->mapToGlobal(m_buttonClarity->pos()).y();
        if(event->type() == QEvent::Enter)
        {
            qDebug() << QString("m_buttonClarity->geometry()")<< m_buttonClarity->geometry();
            qDebug() << QString("mouse pos()")<< QCursor::pos();
            m_clityListWgt->move(x - 9,y - m_clityListWgt->height()-m_buttonClarity->height()-1);//80 150
            m_clityListWgt->show();
        }
        else if(event->type() == QEvent::Leave)
        {
            QRect rect = QRect(x ,
                               y - m_clityListWgt->height(),
                               m_buttonClarity->width(),
                               m_clityListWgt->height() + m_buttonClarity->height());//鼠标真实横坐标比控件横坐标大140
            qDebug() <<QString(u8"处理后的矩形：") << rect;
            if(!rect.contains(QCursor::pos()))
            {
                m_clityListWgt->hide();
//                qDebug() << QString(u8"鼠标不在区域内！");
            }
            else
            {
//                qDebug() << QString(u8"鼠标在区域内！");
            }
        }
    }
    else if(watched == m_buttonSound)
    {
        int x = m_buttonSound->parentWidget()->mapToGlobal(m_buttonSound->pos()).x();
        int y = m_buttonSound->parentWidget()->mapToGlobal(m_buttonSound->pos()).y();
        if(event->type() == QEvent::Enter)
        {
            qDebug() << QString("m_buttonClarity->geometry()")<< m_buttonSound->geometry();
            qDebug() << QString("mouse pos()")<< QCursor::pos();
            m_frameSound->move(x-8,y-m_frameSound->height()-m_buttonSound->height()-1);//26 120
            m_frameSound->show();
        }
        else if(event->type() == QEvent::Leave)
        {
            QRect rect = QRect(x,
                               y - m_frameSound->height(),
                               m_buttonSound->width(),
                               m_frameSound->height() + m_buttonSound->height());//鼠标真实横坐标比控件横坐标大140
            qDebug() <<QString(u8"处理后的矩形：") << rect;
            if(!rect.contains(QCursor::pos()))
            {
                m_frameSound->hide();
//                qDebug() << QString(u8"鼠标不在区域内！");
            }
            else
            {
//                qDebug() << QString(u8"鼠标在区域内！");
            }
        }
    }
    else if(watched == m_frameSound)
    {
        if(event->type() == QEvent::Leave)
            m_frameSound->hide();
    }
    else if(watched == m_clityListWgt)
    {
        if(event->type() == QEvent::Leave)
            m_clityListWgt->hide();
    }
    return QWidget::eventFilter(watched,event);
}

void MiniPlayer::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    if(!m_clityListWgt->isHidden() || !m_frameSound->isHidden()) return;
    m_frameTitle->show();
    m_frameControl->show();
}

void MiniPlayer::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    if(!m_clityListWgt->isHidden() || !m_frameSound->isHidden()) return;
    m_frameTitle->hide();
    m_frameControl->hide();
}

void MiniPlayer::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    QRect rect_t = m_videoWidget->rect();
    m_frameTitle->setGeometry(rect_t.x(),
                              rect_t.y(),
                              rect_t.width(),
                              m_frameTitle->height());
    m_frameTitle->raise();
    m_frameTitle->show();

    m_frameControl->setGeometry(rect_t.x(),
                              rect_t.y() + rect_t.height()-m_frameControl->height(),
                              rect_t.width(),
                              m_frameControl->height());
    m_frameControl->raise();
    m_frameControl->show();
}

void MiniPlayer::createRightMenu()
{
    //菜单变量需要在堆上创建（指针）,否则勾选项不生效，每次都是新的变量
    m_videoMenu = new QMenu(this);
    m_videoMenu->setObjectName(QString(u8"m_miniVideoMenu"));

    m_subMenu1 = new QMenu(QString(u8"画面比例"),this);
    m_subMenu1->setObjectName(QString(u8"m_miniSub1Menu"));

    m_subMenu2 = new QMenu(QString(u8"倍速播放"),this);
    m_subMenu2->setObjectName(QString(u8"m_miniSub2Menu"));

    m_actionGroup1 = new QActionGroup(this);
    m_actionGroup1->setExclusive(true);
    m_actionGroup1->setObjectName(QString(u8"m_miniActionGroup1"));

    m_actionGroup2 = new QActionGroup(this);
    m_actionGroup2->setExclusive(true);
    m_actionGroup2->setObjectName(QString(u8"m_miniActionGroup2"));

    m_screenAction = new QAction();
    m_screenAction->setText(QString(u8"全屏"));

    m_videoMenu->addAction(QString(u8"主播放器打开"),this,SLOT(slot_menu_mainPlayer()));
    m_videoMenu->addAction(QString(u8"下载"),this,SLOT(slot_menu_download()));
    m_videoMenu->addAction(m_screenAction);
    m_videoMenu->addSeparator();
    QAction *sub1Action1 = new QAction(QString(u8"原始比例"));
    QAction *sub1Action2 = new QAction(QString(u8"铺满窗口"));
    QAction *sub1Action3 = new QAction(QString(u8"4:3"));
    QAction *sub1Action4 = new QAction(QString(u8"16:9"));

    sub1Action1->setCheckable(true);
    sub1Action2->setCheckable(true);
    sub1Action3->setCheckable(true);
    sub1Action4->setCheckable(true);
    sub1Action1->setChecked(true);//默认

    m_subMenu1->addAction(sub1Action1);
    m_subMenu1->addAction(sub1Action2);
    m_subMenu1->addAction(sub1Action3);
    m_subMenu1->addAction(sub1Action4);
    m_videoMenu->addMenu(m_subMenu1);
    //使用容器以达到互斥
    m_actionGroup1->addAction(sub1Action1);
    m_actionGroup1->addAction(sub1Action2);
    m_actionGroup1->addAction(sub1Action3);
    m_actionGroup1->addAction(sub1Action4);

    QAction *sub2Action1 = new QAction(QString(u8"2.0X"));
    QAction *sub2Action2 = new QAction(QString(u8"1.5X"));
    QAction *sub2Action3 = new QAction(QString(u8"1.25X"));
    QAction *sub2Action4 = new QAction(QString(u8"1.0X(正常)"));
    QAction *sub2Action5 = new QAction(QString(u8"0.5X"));
    sub2Action1->setCheckable(true);
    sub2Action2->setCheckable(true);
    sub2Action3->setCheckable(true);
    sub2Action4->setCheckable(true);
    sub2Action5->setCheckable(true);
    sub2Action4->setChecked(true);//默认正常1倍速
    m_subMenu2->addAction(sub2Action1);
    m_subMenu2->addAction(sub2Action2);
    m_subMenu2->addAction(sub2Action3);
    m_subMenu2->addAction(sub2Action4);
    m_subMenu2->addAction(sub2Action5);
    m_videoMenu->addMenu(m_subMenu2);

    m_actionGroup2->addAction(sub2Action1);
    m_actionGroup2->addAction(sub2Action2);
    m_actionGroup2->addAction(sub2Action3);
    m_actionGroup2->addAction(sub2Action4);
    m_actionGroup2->addAction(sub2Action5);

    m_videoMenu->addAction(QString(u8"视频信息"),this,SLOT(slot_menu_videoinfo()));
    m_videoMenu->addAction(QString(u8"设置"),this,SLOT(slot_menu_setting()));
}

void MiniPlayer::on_updatePosition()
{
    int pos  = m_player->position()/1000;//最新的进度
    m_horSlider->setValue(pos);//设置主播放界面当前进度
    //将总进度（duration）转换为时分秒
    int H1 = m_times / (60*60);
    int M1 = (m_times- (H1 * 60 * 60)) / 60;
    int S1 = (m_times - (H1 * 60 * 60)) - M1 * 60;
    QString hour1 = QString::number(H1);
    if (hour1.length() == 1) hour1 = "0" + hour1;
    QString min1 = QString::number(M1);
    if (min1.length() == 1) min1 = "0" + min1;
    QString sec1 = QString::number(S1);
    if (sec1.length() == 1) sec1 = "0" + sec1;
    QString qTZ = hour1 + ":" + min1 + ":" + sec1;

    //将进度（position）秒数转化为时分秒格式
    int H = pos / (60*60);
    int M = (pos- (H * 60 * 60)) / 60;
    int S = (pos - (H * 60 * 60)) - M * 60;
    QString hour = QString::number(H);
    if (hour.length() == 1) hour = "0" + hour;
    QString min = QString::number(M);
    if (min.length() == 1) min = "0" + min;
    QString sec = QString::number(S);
    if (sec.length() == 1) sec = "0" + sec;
    QString qTime = hour + ":" + min + ":" + sec;
    m_labelProgress->setText(qTime+ "/" +qTZ);
}

void MiniPlayer::slot_menu_mainPlayer()
{
    emit sig_player_toMainPlayer();
    qDebug() <<QString(u8"主播放器播放");
}

void MiniPlayer::slot_menu_download()
{
    emit sig_player_download();
    qDebug() <<QString(u8"视频下载");
}

void MiniPlayer::slot_menu_fullscreen()
{
    m_videoWidget->setFullScreen(true);
}

void MiniPlayer::slot_menu_scale(QAction *action)
{
    qDebug() << action->text();
    if(action->text() == QString(u8"原始比例"))
    {
        m_videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
    }
    else if(action->text() == QString(u8"铺满窗口"))
    {
        m_videoWidget->setAspectRatioMode(Qt::IgnoreAspectRatio);
    }
    else if(action->text() == QString(u8"4:3"))
    {
        m_videoWidget->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
    }
    else if(action->text() == QString(u8"16:9"))
    {
        m_videoWidget->setAspectRatioMode(Qt::IgnoreAspectRatio);
    }
}

void MiniPlayer::slot_menu_playrate(QAction *action)
{
    qDebug() << action->text();
    qreal   speed = 1.0;
    if(action->text() == QString(u8"2.0X"))
    {
        speed = 2.0;
    }
    else if(action->text() == QString(u8"1.5X"))
    {
        speed = 1.5;
    }
    else if(action->text() == QString(u8"1.25X"))
    {
        speed = 1.25;
    }
    else if(action->text() == QString(u8"1.0X(正常)"))
    {
        speed = 1.0;
    }
    else if(action->text() == QString(u8"0.5X"))
    {
        speed = 0.5;
    }
  m_player->setPlaybackRate(speed);
}

void MiniPlayer::slot_menu_videoinfo()
{
    emit sig_player_videoInfo();
    qDebug() <<QString(u8"视频信息");
}

void MiniPlayer::slot_menu_setting()
{
    emit sig_player_videoSetting();
    qDebug() <<QString(u8"视频设置");
}
