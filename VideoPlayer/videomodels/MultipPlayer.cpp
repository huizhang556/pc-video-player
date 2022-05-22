#include "MultipPlayer.h"
#include "ui_MultipPlayer.h"

#include <QFile>
#include <QMenu>
#include <QDebug>
#include <QAction>
#include <QCursor>
#include <QProcess>
#include <QKeyEvent>
#include <QDateTime>
#include <QFileInfo>
#include <QScrollBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidgetAction>
#include <QtSql/QSqlQuery>

MultipPlayer::MultipPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultipPlayer),
    m_winMax(false),
    m_times(0),
    m_voice(10),
    m_collectStatus(false),//默认没有收藏
    m_isHide(false),//侧边栏默认没有隐藏
    m_playerState(QMediaPlayer::StoppedState)
{
    ui->setupUi(this);
    this->setMinimumSize(1240,800);//1400,800
    this->setMouseTracking(true);//开启鼠标跟踪，适应捕捉屏幕
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setWindowTitle(QString::fromLocal8Bit("Qt简易视频播放器"));
    initMainWindow();//初始化界面
    chandleSignalAndSLots();//处理信号与槽函数
    //设置监听
    ui->pushButton_sound->installEventFilter(this);//音量调节按钮设置监听
    ui->stackedWidget->installEventFilter(this);//侧边按钮显隐用
    videoWidget->installEventFilter(this);//视频界面

  //测试功能
  list_temp<<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/xiashanshalajiang.flv")
          <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/movies/let_the_bullets_fly.flv")
         <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/hongzhaoyuan123.flv")
        <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/JIMINGYUE_DANCE.flv")
       <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/yuxitan.flv")
      <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/你莫走_山水组合_97217950_MP4.mp4")
     <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/星月神话_金莎_628218_MP4UL.mp4")
    <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/心若琉璃_刘惜君_196224216.mp4")
   <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/mp3/最美情侣-白小白-23534035.mp3")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/mp3/Monody-Laura_Brehm_TheFatRat-7185892.mp3")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/mp3/红昭愿-音阙诗听-16644260.mp3")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/mp3/追梦人-古筝-280886.mp3")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/wxinyongheng.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/cover Roller Coaster.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/fangxuefancha.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/huaijiejie1.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/The Pussycat Dolls.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/TOMBOY.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/Love Story.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/chiling.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/fanliang.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/pengyouzhouhuajian.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/qiazouyixiang.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/fangxuefancha.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/sahonianjiandangbainia.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/shakeit.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/sishouzhiyouzhongguoren.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/womingyouwobuyoutian.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/qingyi.flv?name=qingyi.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/shuishouzhengzhihua.flv")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/f64160074119f49ecf09828b2d82145c")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/b406f97ae4c797de546e5776d0e14c60")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/ae713714dacc980f8dee31b0b3281ac0")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/b8754a3a7cba5352dbf960e8762d5c30")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/db3eb18b5025eba07fd61e80ec8e1a75")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/685912fb972c3546d40f95476688a7fd")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/e47b954f2874ac8dd46b2242cacb55c8")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/bb973a1f2c9d1d1113873c15e59e1d0b")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/a0543afc8f61754a4227170a8aae6998")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/8d8b31c3dbcaa65345ca0c9889dcb960")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/1b71f2b2936726193b1ac72fdce38de2")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/74edbb7393d79e8e37e74d57c13dda6f")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/0af39ea6c5d7f1198c200ef02921e187")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/7255576ae140a95ab474224ee9135922")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/b88d5e802a67e90678aae0326c89b14b")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/dd905ebafc1a90e60781f95af9b3417d")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/55ae340607ab4d4b32d126308cd2ea4f")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/de44c9d7ffe85d26c85ae7a9bf17be3d")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/4e264ecf2db71d19806f498721c045ba")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/b1891ade83ea5427b90d474350858264")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/583aee9a9c7aaed615cf02f0a8352941")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/e0094eac26497a888f5c170e9d4fad60")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/76d8f20fee8e0cb6f2e88d1b3d7dad11")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/b62842ff56290bd8666981f02326886c")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/d9d6cd39aa871b5e57605908c446e703")
  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/big/upload/d9d6cd39aa871b5e57605908c446e703");
}

MultipPlayer::~MultipPlayer()
{
    //没有指定父亲的需要手动释放
    //有父级对象的，系统自动释放
    //有包含关系和指定父对象的自动释放
    delete ui;
    delete m_pTimer;
    delete m_pTimer2;
    delete m_widget1;
    delete m_musicUi;
    delete m_muteDlg;
    delete videoWidget;
    delete m_videoBlank;
    delete m_adjustBright;
    delete m_videoTitleBar;
    delete m_musicShowList;
    delete m_hboxlayout_rlist;
}

/*初始化界面*/
void MultipPlayer::initMainWindow()
{
//    ui->pushButton_danmu->setCheckable(true);
//    ui->pushButton_danmu->setChecked(false);
//    ui->pushButton_collect->setChecked(true);//收藏按钮可以checked
//    ui->pushButton_collect->setCheckable(false);//默认没有选中

    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    player->setVolume(10);

    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setPageStep(5);
    ui->horizontalSlider->setEnabled(false);

    playlist->setPlaybackMode(QMediaPlaylist::Loop);//设置默认播放模式
    player->setPlaylist(playlist);

    videoWidget = new MyVideoWidget(ui->stackedWidget);
    player->setVideoOutput(videoWidget);

    m_widget2 = new QWidget;//listwidget显示（暂时不用）
    m_widget2->setObjectName(QString::fromLocal8Bit("m_widget2"));

    m_videoBlank = new VideoBlank();
    m_videoBlank->setObjectName(QString::fromLocal8Bit("m_videoBlank"));

    m_musicUi = new MusicPlayShow();
    m_musicUi->setObjectName(QString::fromLocal8Bit("m_musicUi"));

    m_videoTitleBar = new VideoTitleBar();
    m_videoTitleBar->setObjectName(QString::fromLocal8Bit("m_videoTitleBar"));

    //中间主显示部分，视频显示部分
    m_videoBlank->setHideOpenButton(true);
    ui->stackedWidget->insertWidget(0,m_videoBlank);
    ui->stackedWidget->insertWidget(1,videoWidget);
    ui->stackedWidget->insertWidget(2,m_musicUi);
    ui->stackedWidget->setCurrentIndex(0);//默认显示空白界面
    ui->stackedWidget->setMinimumSize(976,700);//必须设置最小尺寸，否则播放控制栏位置不正确

    //用户信息（暂时）
//    m_listWisget1 = new QListWidget;
//    m_listWisget1->setObjectName(QString::fromLocal8Bit("m_listWisget1"));
//    m_listWisget1->setMinimumWidth(260);
//    m_listWisget1->setAlternatingRowColors(false);//交替显示

    //播放列表
    m_listWisget2 = new QListWidget;
    m_listWisget2->setObjectName(QString::fromLocal8Bit("m_listWisget2"));
    m_listWisget2->setContextMenuPolicy(Qt::CustomContextMenu);
    m_listWisget2->setMinimumWidth(260);
    m_listWisget2->setFocusPolicy(Qt::NoFocus);//作用是点击item去掉虚线边框
    m_listWisget2->setAlternatingRowColors(false);//交替显示
    m_listWisget2->verticalScrollBar()->setObjectName(QString::fromUtf8("list2_vertical_scrollBar"));//单独设置样式
    m_listWisget2->horizontalScrollBar()->setHidden(true);
    m_listWisget2->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_listWisget2->clear();
    //我的收藏
    m_listWisget3 = new QListWidget;
    m_listWisget3->setObjectName(QString::fromLocal8Bit("m_listWisget3"));
    m_listWisget3->setContextMenuPolicy(Qt::CustomContextMenu);
    m_listWisget3->setMinimumWidth(260);
    m_listWisget3->setAlternatingRowColors(false);//交替显示
    m_listWisget3->verticalScrollBar()->setObjectName(QString::fromUtf8("list3_vertical_scrollBar"));
    m_listWisget3->horizontalScrollBar()->setHidden(true);
    m_listWisget3->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_listWisget3->clear();

    //网络曲库
    m_listWisget4 = new QListWidget;
    m_listWisget4->setObjectName(QString::fromLocal8Bit("m_listWisget4"));
    m_listWisget4->setContextMenuPolicy(Qt::CustomContextMenu);
    m_listWisget4->setMinimumWidth(260);
    m_listWisget4->setAlternatingRowColors(false);//交替显示
    m_listWisget4->verticalScrollBar()->setObjectName(QString::fromUtf8("list4_vertical_scrollBar"));
    m_listWisget4->horizontalScrollBar()->setHidden(true);
    m_listWisget4->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);


    m_lineEdit = new QLineEdit;//曲库列表搜索框
    m_lineEdit->setObjectName(QString::fromLocal8Bit("m_lineEdit"));
    m_lineEdit->setMinimumWidth(200);
    m_lineEdit->setFixedHeight(30);
    m_lineEdit->installEventFilter(this);

    m_searchBtn = new QPushButton;//曲库列表搜索按钮
    m_searchBtn->setObjectName(QString::fromLocal8Bit("m_searchBtn"));
    m_searchBtn->setFixedSize(33,30);
    m_searchBtn->installEventFilter(this);

    m_hLayout = new QHBoxLayout(this);
    m_hLayout->insertWidget(0,m_lineEdit);
    m_hLayout->insertWidget(1,m_searchBtn);
    m_hLayout->setSpacing(0);
    m_hLayout->setStretch(0,4);
//      m_hLayout->setStretch(1,1);

    m_vHlayout = new QVBoxLayout(this);
    m_vHlayout->insertLayout(0,m_hLayout);
    m_vHlayout->insertWidget(1,m_listWisget2);
    m_vHlayout->setStretch(0,1);
    m_vHlayout->setStretch(1,4);
    m_vHlayout->setSpacing(0);
    m_vHlayout->setContentsMargins(0,0,0,0);

    m_widget2->setLayout(m_vHlayout);
    //添加抽屉
    m_toolBox = new QToolBox;
    m_toolBox->setFixedWidth(260);
    m_toolBox->setObjectName(QString::fromLocal8Bit("m_toolBox"));
//    QIcon icon_user(":/images/icon/user.png");
    QIcon icon_playlist(":/images/icon/playerlist.png");
    QIcon icon_collect(":/images/icon/play_collect_checked.png");
    QIcon icon_internet(":/images/icon/playerinternet.png");
//    m_toolBox->addItem(m_listWisget1,icon_user,QString::fromLocal8Bit("用户信息"));
    m_toolBox->addItem(m_widget2,icon_playlist,QString::fromLocal8Bit("播放列表"));
    m_toolBox->addItem(m_listWisget3,icon_collect,QString::fromLocal8Bit("我的收藏"));
    m_toolBox->addItem(m_listWisget4,icon_internet,QString::fromLocal8Bit("播放记录"));
    m_toolBox->layout()->setSpacing(3);//item之间的间距

    m_introduceForm = new IntroduceForm;
    m_introduceForm->setObjectName(QString::fromLocal8Bit("m_introduceForm"));
    m_introduceForm->setCommentStarts(4);//亮4颗星星

    m_introStack = new QStackedWidget;//视频简介
    m_introStack->setObjectName(QString::fromLocal8Bit("m_introStack"));
    m_introStack->setFixedSize(260,100);
    m_introStack->insertWidget(0,m_introduceForm);
    m_introStack->setHidden(true);

    m_recomTab = new RecomVideoTab;
    m_recomTab->setObjectName(QString::fromLocal8Bit("m_recomTab"));
    m_recomTab->setFixedWidth(260);

    m_commentTab = new CommentTab;
    m_commentTab->setObjectName(QString::fromLocal8Bit("m_commentTab"));
    m_commentTab->setFixedWidth(260);

    //节目列表分块
    m_tabWidget1 = new QTabWidget;//不用手动释放，有包含关系
    m_tabWidget1->setObjectName(QString::fromLocal8Bit("m_tabWidget1"));
    m_tabWidget1->setFixedWidth(260);//固定宽度
    set_showTwoTabBar(m_tabWidget1,0,m_toolBox,QString::fromLocal8Bit("播放列表"),1,m_recomTab,QString::fromLocal8Bit("推荐视频"));
//      set_showTwoTabBar(m_tabWidget1,0,m_toolBox,QString::fromLocal8Bit("播放列表"),1,m_commentTab,QString::fromLocal8Bit("讨论"));
    //set_showTwoTabBar(m_tabWidget1,0,m_commentTab,QString::fromLocal8Bit("讨论"),1,m_commentTab,QString::fromLocal8Bit("讨论"));
    m_tabWidget1->setCurrentIndex(0);
    //测试
//    removeTabwidgetTabBar(m_tabWidget1);

    m_vHlayout_jianjie = new QVBoxLayout;
    m_vHlayout_jianjie->setObjectName(QString::fromLocal8Bit("m_vHlayout_jianjie"));
    m_vHlayout_jianjie->addWidget(m_introStack,2);
    m_vHlayout_jianjie->addWidget(m_tabWidget1,8);
    m_vHlayout_jianjie->setSpacing(0);

    m_widget1 = new QWidget(this);//右侧列表整体父亲
    m_widget1->setObjectName(QString::fromLocal8Bit("m_widget1"));
    m_widget1->setFixedWidth(260);
    m_widget1->setContentsMargins(0,0,0,0);//m_widget1的内容与m_widget1的间距
    m_widget1->setLayout(m_vHlayout_jianjie);
    m_widget1->layout()->setContentsMargins(1,0,0,0);//包裹m_widget1的布局 左 上 右 下
//    m_widget1->setHidden(true);//测试使用


    m_hboxlayout_rlist = new QHBoxLayout;
    m_hboxlayout_rlist->addWidget(ui->stackedWidget);
    m_hboxlayout_rlist->addWidget(m_widget1);
    m_hboxlayout_rlist->setSpacing(0);
    m_hboxlayout_rlist->setStretch(0,7);
    m_hboxlayout_rlist->setStretch(1,3);

    ui->verticalLayout_main->insertWidget(0,m_videoTitleBar);//标题栏
    ui->verticalLayout_main->insertLayout(1,m_hboxlayout_rlist);
    ui->verticalLayout_main->insertWidget(2,ui->stackedWidget_player);
    ui->verticalLayout_main->setSpacing(0);
    ui->verticalLayout_main->setStretch(0,1);
    ui->verticalLayout_main->setStretch(1,7);
    ui->verticalLayout_main->setStretch(2,1);
    ui->verticalLayout_main->setContentsMargins(0,0,0,0);
    ui->verticalLayout_main->setSpacing(0);
    ui->verticalLayout_main->setMargin(2);
    this->setLayout(ui->verticalLayout_main);
    loadDefaultLogo();//加载默认图标

    VideoProgressBar::getInstance()->hide();

    m_pTimer  = new QTimer(this);
    m_pTimer2 = new QTimer(this);
    m_pTimer2->setSingleShot(true);//只执行一次定时器
    m_pTimer->start(1000);//每1000毫秒执行一次

    m_muteDlg = new muteDialog();//不加this
    m_muteDlg->setObjectName(QString::fromLocal8Bit("m_muteDlg"));
    m_muteDlg->setHidden(true);

//    m_playOrderForm = new PlayOrderForm();
//    m_playOrderForm->setObjectName(QString::fromLocal8Bit("m_playOrderForm"));

    m_foldBtn = new QPushButton(ui->stackedWidget);//父亲必须指定，要不然显示不出来
    m_foldBtn->setObjectName(QString::fromLocal8Bit("m_foldBtn"));
    m_foldBtn->setFixedSize(40,60);
//    m_foldBtn->setAttribute(Qt::WA_TranslucentBackground,true);//没效果，得定制
    m_foldBtn->setHidden(true);//初始化隐藏按钮
}

/*处理信号与槽函数*/
void MultipPlayer::chandleSignalAndSLots()
{
    //列表折叠指示按钮
    connect(m_foldBtn,&QPushButton::clicked,[=](){
        judgeFoldBtnOfRightDockList();
    });

    //查看评论
    connect(ui->pushButton_comments,&QPushButton::clicked,[=](){ showMediaCommentTab();});
    //应该在有影片播放的时候，执行定时器，否则就是无效；1s更新一次进度
    connect(m_pTimer,&QTimer::timeout,this,&MultipPlayer::on_time);
    connect(m_pTimer,&QTimer::timeout,this,&MultipPlayer::updateProgressBarGeometry);//每0.3秒更新不管有没有缓冲
    //监测媒体播放状态 StoppedState PlayingState PausedState
    connect(player,SIGNAL(stateChanged(QMediaPlayer::State)),this,SLOT(checkChandleMediaPlayerStatus(QMediaPlayer::State)));
    //监测媒体本身状态,所带参数为新的媒体状态，比如缓冲状态 BufferingMedia BufferedMedia
    connect(player,&QMediaPlayer::mediaStatusChanged,this,&MultipPlayer::checkChandleMediaStatus);
    connect(player,&QMediaPlayer::durationChanged,[=](){
        m_times = player->duration()/1000;//持续时间,毫秒为单位，转化为秒为单位
        ui->horizontalSlider->setRange(0,m_times);
    });

    /*移动---拖动进度条，设置媒体的播放进度*/
    connect(ui->horizontalSlider,&QSlider::sliderMoved,[=](int pos){
        if(m_bPress)
            player->setPosition(pos*1000);//position单位是ms,所以需要*1000转换为ms
    });

    /*按下*/
    connect(ui->horizontalSlider,&QSlider::sliderPressed,[=](){
        m_bPress = true;
    });

    /*释放*/
    connect(ui->horizontalSlider,&QSlider::sliderReleased,[=](){
        m_bPress = false;
    });

    /*音量显示*/
//    connect(ui->pushButton_sound,&QPushButton::clicked,[=]()
//    {
//        if(m_muteDlg)
//        {
//            if(m_muteDlg->isHidden())
//            {
//                int x = ui->pushButton_sound->parentWidget()->mapToGlobal(ui->pushButton_sound->pos()).x();
//                int y = ui->pushButton_sound->parentWidget()->mapToGlobal(ui->pushButton_sound->pos()).y();
//                int h = m_muteDlg->height();
//                m_muteDlg->setGeometry(x-6,y-h-6,m_muteDlg->width(),m_muteDlg->height());
//                m_muteDlg->raise();
//                m_muteDlg->show();
//            }
//            else
//            {
//                m_muteDlg->hide();
//            }
//        }
//    });
    //接收value值改变
    connect(this,SIGNAL(sig_currentMediaSoundValueChange(int)),m_muteDlg,SLOT(setSpliderValue(int)));

    /*音量值调节显示数值*/
    connect(m_muteDlg,&muteDialog::sig_SpliderValueChange,[=](int value){
        emit sig_currentMediaSoundValueChange(value);//托盘接收信号
        player->setVolume(value);
        if(value != 0)
        {
            qDebug() << "value != 0";
            ui->pushButton_sound->setIcon(QIcon(":/images/icon/yingling.png"));
        }
        else
        {
            qDebug() << "value == 0";
            ui->pushButton_sound->setIcon(QIcon(":/images/icon/jingyin.png"));
        }
    });



    /*跟随列表选择播放对应文件,将鼠标单击播放该为双击*/
    connect(m_listWisget2,&QListWidget::itemDoubleClicked,[=](QListWidgetItem *item)
    {
        int row = m_listWisget2->row(item);
//        m_playerState = QMediaPlayer::PlayingState;
//        ui->pushButton_pauseStart->setIcon(QIcon(":/images/icon/pausehover.png"));//播放

        playlist->setCurrentIndex(row);
        fileType(row);
        player->play();
    });

    //标题栏显示当前播放文件名
    connect(this,SIGNAL(sig_sendSwitchToMusicPage(QString)),m_videoTitleBar,SLOT(setTitleText(QString)));
    //进度条上方显示当前播放媒体歌名
    connect(this,SIGNAL(sig_sendSwitchToMusicPage(QString)),this,SLOT(setCurrentMediaName(QString)));

    //窗口关闭按钮
    connect(m_videoTitleBar,&VideoTitleBar::sig_winVClose,[=]()
    {
        closeCurrentWindow();
    });

    //窗口最小化按钮
    connect(m_videoTitleBar,&VideoTitleBar::sig_winVMinimum,this,&MultipPlayer::showMinimized);

    //窗口还原按钮
    connect(this,SIGNAL(sig_winVStatus(bool)),m_videoTitleBar,SLOT(chandleVMainWinStatus(bool)));
    connect(m_videoTitleBar,&VideoTitleBar::sig_doubleClick,[=](){chandleRestoreWindow();});
    //窗口还原，关闭视频配置调节界面
    connect(m_videoTitleBar,&VideoTitleBar::sig_winVRestore,[=](){m_adjustBright->close();});
    //窗口还原
    connect(m_videoTitleBar,&VideoTitleBar::sig_winVRestore,[=](){chandleRestoreWindow();});
    //窗口关闭
    connect(m_videoTitleBar,&VideoTitleBar::sig_winVClose,[=](){m_adjustBright->close();});


    connect(ui->Btn_adjust,&QPushButton::clicked,[=](){set_adjustBright();});
    //通知播放列表加载信息
    connect(this,&MultipPlayer::sig_sendToMusicList,m_musicShowList,&MusicPlaylist::addFileInfoToListView);
    //播放列表界面传来播放歌曲的信息
    connect(m_musicShowList,&MusicPlaylist::sig_selectRowIndex,[=](QModelIndex index)
    {
        QString name_song = index.data().toString();
        qDebug()<<name_song;
    });


    /*上一首，下一首，对应m_listwidget项的变化*/
    connect(playlist,&QMediaPlaylist::currentIndexChanged,[=](int index)
    {
        fileType(index);//判断视频还是歌曲，显示对应的界面
        m_listWisget2->setCurrentRow(index);
        //          ui->playerListWidget->setCurrentRow(index);
        setCollectBtnShowStatus();//处理所有的item改变时的操作
        loadFileInfoToWinTitle(index);
        updateRateTypeUiLayout();
        checkChandleMediaPlayerStatus(player->state());//核验状态
    });

    /*右侧窗口-曲库歌曲搜索*/
    connect(m_lineEdit,&QLineEdit::textChanged,[=](QString str){findFileFromLineEdit(str);});

    //向音乐界面发送名字,带参数 QString name,注意跨线程的问题,QTimer类不是线程安全的类型，注意第五个参数问题
    //    connect(this,SIGNAL(sig_sendSwitchToMusicPage(QString)),m_musicUi,SLOT(receiveMainWinData(QString)));

    //调节列表发来的信号处理
    m_adjustBright = new AdjustBright();//必须先new出来，再使用，否则无用
    m_adjustBright->setObjectName(QString::fromLocal8Bit("m_adjustBright"));
    m_adjustBright->setHidden(true);//界面运行起来弹出界面bug
    connect(playlist,SIGNAL(currentIndexChanged(int)),m_adjustBright,SLOT(updatePlayRate()));//倍速恢复正常选项状态
    connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(update_adjustBright()));//亮度，饱和度，色调，对比度恢复原值
    //调节倍速
    connect(m_adjustBright,SIGNAL(valueChange_playRate(qreal)),player,SLOT(setPlaybackRate(qreal)));
    //调节播放模式(暂时不用)
//    connect(m_adjustBright,SIGNAL(valueChange_playBackMode(int)),this,SLOT(adjust_playBackMode(int)));
    //调节屏幕占比
    connect(m_adjustBright,SIGNAL(valueChange_aspectRatio(int)),this,SLOT(adjust_aspectRatioMode(int)));
    connect(m_adjustBright,SIGNAL(valueChange_liangdu(int)),videoWidget,SLOT(setBrightness(int)));
    connect(m_adjustBright,SIGNAL(valueChange_duibidu(int)),videoWidget,SLOT(setContrast(int)));
    connect(m_adjustBright,SIGNAL(valueChange_baohedu(int)),videoWidget,SLOT(setSaturation(int)));
    connect(m_adjustBright,SIGNAL(valueChange_sediao(int)),videoWidget,SLOT(setHue(int)));

    //空白页打开文件
    connect(m_videoBlank,&VideoBlank::sig_openLocalFile,[=]()
    {
        if(!m_newStart)
        {
            on_pushButton_5_clicked();
        }
        else
        {

            on_pushButton_6_clicked();
        }
    });
    //打开文件
    connect(m_searchBtn,&QPushButton::clicked,[=]()
    {
        if(!m_newStart)
        {
            on_pushButton_5_clicked();
        }
        else
        {

            on_pushButton_6_clicked();
        }
    });

    //接受发过来的网络资源链接
    connect(m_videoTitleBar,&VideoTitleBar::sig_inputSourceUrl,[=](QString newurl)
    {
        QUrl url = QUrl::fromLocalFile(newurl);
        player->setMedia(url);
        player->play();
        fileType(newurl);
    });

    //收藏按钮
    connect(ui->pushButton_collect,&QPushButton::clicked,[=](){
        qDebug() << "pushButton_collect clicled!";
        addCurrentMediaToList_Collect(m_listWisget3);
    });

    //播放添加历史记录
    connect(this,&MultipPlayer::sig_sendSwitchToMusicPage,[=](){
        addCurrentMediaToList_History(m_listWisget4);
    });

    //播放顺序选择
    connect(ui->pushButton_playOrder,&QPushButton::clicked,[=](){
//        if(PlayOrderForm::getInstance())
//        {
            if(!PlayOrderForm::getInstance()->isHidden())
            {
                PlayOrderForm::getInstance()->hide();
            }
            else
            {
                int x = ui->pushButton_playOrder->parentWidget()->mapToGlobal(ui->pushButton_playOrder->pos()).x();
                int y = ui->pushButton_playOrder->parentWidget()->mapToGlobal(ui->pushButton_playOrder->pos()).y();
                int w = PlayOrderForm::getInstance()->width();
                int h = PlayOrderForm::getInstance()->height();
                PlayOrderForm::getInstance()->setGeometry(x-w/2,y-h-10,PlayOrderForm::getInstance()->width(),PlayOrderForm::getInstance()->height());
                PlayOrderForm::getInstance()->raise();
                PlayOrderForm::getInstance()->show();
            }
//        }
//        else
//        {
//            PlayOrderForm::getInstance() = new PlayOrderForm();
//            int x = ui->pushButton_playOrder->parentWidget()->mapToGlobal(ui->pushButton_playOrder->pos()).x();
//            int y = ui->pushButton_playOrder->parentWidget()->mapToGlobal(ui->pushButton_playOrder->pos()).y();
//            int w = PlayOrderForm::getInstance()->width();
//            int h = PlayOrderForm::getInstance()->height();
//            PlayOrderForm::getInstance()->setGeometry(x-w/2,y-h-10,PlayOrderForm::getInstance()->width(),PlayOrderForm::getInstance()->height());
//            PlayOrderForm::getInstance()->raise();
//            PlayOrderForm::getInstance()->show();
//        }
    });

    //播放顺序 -- 单曲1 顺序2 循环3 随机4
    connect(PlayOrderForm::getInstance(),SIGNAL(sig_playerOrder(int)),this,SLOT(setPlayOrderButtonStyleSheet(int)));

    //显示 列表
    connect(ui->pushButton_curlist,&QPushButton::clicked,[=](){setMainWindowShowFullgreen();});

    //播放列表右键
    connect(m_listWisget2,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slot_createRight_playListTable(QPoint)));
    //收藏列表右键
    connect(m_listWisget3,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slot_createRight_playCollectTable(QPoint)));
    //历史列表右键
    connect(m_listWisget4,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slot_createRight_playHistoryTable(QPoint)));
}

/*加载默认图标*/
void MultipPlayer::loadDefaultLogo()
{
    ui->Btn_adjust->setToolTip(QString::fromLocal8Bit("设置"));
    ui->pushButton_sound->setToolTip(QString::fromLocal8Bit("音量"));
    ui->pushButton_collect->setToolTip(QString::fromLocal8Bit("收藏"));
    ui->pushButton_download->setToolTip(QString::fromLocal8Bit("下载"));
    ui->pushButton_curlist->setToolTip(QString::fromLocal8Bit("全屏(ESC键退出)"));

    m_lineEdit->setPlaceholderText(QString::fromLocal8Bit("输入要搜索的内容^_^"));
    m_lineEdit->setEnabled(false);

    m_searchBtn->setText(QString::fromLocal8Bit(""));
    m_searchBtn->setToolTip(QString::fromLocal8Bit("打开文件"));

    ui->pushButton_sound->setIcon(QIcon(":/images/icon/yingling.png"));//图标是正常音量
    ui->pushButton_sound->setIconSize(QSize(20,20));//以后所有显示图片都是此大小
    ui->pushButton_sound->setFlat(true);

//    ui->pushButton_5->setIcon(QIcon(":/images/icon/openhover.png"));//打开
//    ui->pushButton_5->setFlat(true);
//    ui->pushButton_5->setIconSize(QSize(50,50));
//    ui->pushButton_5->setToolTip(QString::fromLocal8Bit("添加文件"));

    ui->pushButton_pauseStart->setIcon(QIcon(":/images/icon/playhover.png"));//播放
    ui->pushButton_pauseStart->setFlat(true);
    ui->pushButton_pauseStart->setIconSize(QSize(45,45));
    ui->pushButton_pauseStart->setToolTip(QString::fromLocal8Bit("播放"));

//    ui->pushButton_2->setIcon(QIcon(":/images/icon/stophover.png"));//停止
//    ui->pushButton_2->setFlat(true);
//    ui->pushButton_2->setIconSize(QSize(50,50));
//    ui->pushButton_2->setToolTip(QString::fromLocal8Bit("停止"));

//    ui->pushButton_6->setIcon(QIcon(":/images/icon/fullscr.png"));//全屏
//    ui->pushButton_6->setFlat(true);
//    ui->pushButton_6->setIconSize(QSize(50,50));
//    ui->pushButton_6->setToolTip(QString::fromLocal8Bit("播放新文件"));

    ui->pushButton_previous->setIcon(QIcon(":/images/icon/previoushover.png"));//上一首
    ui->pushButton_previous->setFlat(true);
    ui->pushButton_previous->setIconSize(QSize(40,40));
    ui->pushButton_previous->setToolTip(QString::fromLocal8Bit("上一个"));

    ui->pushButton_next->setIcon(QIcon(":/images/icon/nexthover.png"));//下一首
    ui->pushButton_next->setFlat(true);
    ui->pushButton_next->setIconSize(QSize(40,40));
    ui->pushButton_next->setToolTip(QString::fromLocal8Bit("下一个"));

    //    QPalette* palette = new QPalette();
    //    palette->setBrush(QPalette::Background, Qt::black);
    //    videoWidget->setPalette(*palette);
    //    videoWidget->setAutoFillBackground(true);
    //    delete palette;
}

/*添加进播放列表*/
void MultipPlayer::addToPlaylist(const QStringList &fileNames)
{
    foreach (QString const &argument, fileNames)
    {
        QFileInfo fileInfo(argument);
        if (fileInfo.exists())
        {
            QUrl url = QUrl::fromLocalFile(fileInfo.absoluteFilePath());
            if (fileInfo.suffix().toLower() == QLatin1String("m3u"))
            {
                playlist->load(url);
            }
            else
            {
                playlist->addMedia(url);
            }
        }
        else
        {
            QUrl url(argument);
            if (url.isValid())
            {
                playlist->addMedia(url);
            }
        }
    }
}

/*登录菜单*/
void MultipPlayer::createLoginMenu()
{

}

/*换肤菜单*/
void MultipPlayer::createSwitchSkinMenu()
{

}

/*判断文件类型1*/
bool MultipPlayer::fileType(QStringList &filenames, int index)
{
    QString filename = filenames[index];
    m_curMediaName = filename;
    bool mp3 = filename.endsWith(QString::fromLocal8Bit(".mp3"),Qt::CaseInsensitive);//判断是否以.mp3结尾，去除大小写敏感
    if(mp3)
    {
        emit sig_sendSwitchToMusicPage(filename);
        ui->stackedWidget->setCurrentIndex(3);
        return true;//这里true代表以.mp3结尾的文件
    }
    else
    {
        emit sig_sendSwitchToMusicPage(filename);
        ui->stackedWidget->setCurrentIndex(2);
        return false;//这里false代表非.mp3结尾的文件，默认为视频文件
    }
}

/*判断文件类型2*/
bool MultipPlayer::fileType(int index)
{
    QString filename = m_mapList2[index];
    m_curMediaName = filename;
    bool mp3 = filename.endsWith(QString::fromLocal8Bit(".mp3"),Qt::CaseInsensitive);//判断是否以.mp3结尾，去除大小写敏感
    if(mp3)
    {
        //音乐显示3，音乐界面
        emit sig_sendSwitchToMusicPage(filename);
        ui->stackedWidget->setCurrentIndex(2);
        return true;//这里true代表以.mp3结尾的文件
    }
    else
    {
        //视屏显示4，视屏界面
        emit sig_sendSwitchToMusicPage(filename);
        ui->stackedWidget->setCurrentIndex(1);
        return false;//这里false代表非.mp3结尾的文件，默认为视频文件
    }
}

/*判断文件类型3*/
bool MultipPlayer::fileType(QString filename)
{
    m_curMediaName = filename;
    bool mp3 = filename.endsWith(QString::fromLocal8Bit(".mp3"),Qt::CaseInsensitive);//判断是否以.mp3结尾，去除大小写敏感
    if(mp3)
    {
        //音乐显示3，音乐界面
        emit sig_sendSwitchToMusicPage(filename);
        ui->stackedWidget->setCurrentIndex(2);
        return true;//这里true代表以.mp3结尾的文件
    }
    else
    {
        //视屏显示4，视屏界面
        emit sig_sendSwitchToMusicPage(filename);
        ui->stackedWidget->setCurrentIndex(1);
        return false;//这里false代表非.mp3结尾的文件，默认为视频文件
    }
}

/*共服务端获取文件列表*/
void MultipPlayer::get_fileFromServer()
{
    MyHttp http;
    QString content = http.get_fileList("192.168.191.5",80);
    qDebug()<<"CONTENT = "<< content;
    //content的格式如下
    //难忘今宵.mv   \n为分隔符
    //快乐至上.mv
    //将资源列表中的内容,编程listwidhet中item的条目
    QStringList ls = content.split("\n");
    for(int i = 0; i< ls.count(); i++)
    {
//        qDebug()<<ls[i];
        QString item = ls[i];
        if(!item.isEmpty())//不为空才会添加到listwidget
        {
            set_fileTolistWidget(ls[i]);
        }

    }
}

void MultipPlayer::removeTabwidgetTabBar(QTabWidget *tabwidget)
{
    if(tabwidget)
    {
        for(int i = tabwidget->tabBar()->count(); i > 0;i--)
        {

            tabwidget->removeTab(i);//从大往小删除
        }
    }
}

/*重载1---只显示1个tab*/
void MultipPlayer::set_showTwoTabBar(QTabWidget *tabwidget, int index1, QWidget *obj1, QString tabtext1)
{
    tabwidget->insertTab(index1,obj1,tabtext1);
}

/*重载2---设置显示2个的tab*/
void MultipPlayer::set_showTwoTabBar(QTabWidget *tabwidget, int index1, QWidget *obj1, QString tabtext1, int index2, QWidget *obj2, QString tabtext2)
{
    tabwidget->insertTab(index1,obj1,tabtext1);
    tabwidget->insertTab(index2,obj2,tabtext2);
}


void MultipPlayer::set_fileTolistWidget(QString item)
{
    QListWidgetItem *pitem = new QListWidgetItem(item);
    pitem->setTextAlignment(Qt::AlignLeft);//item文字向左对齐
    m_listWisget2->addItem(pitem);
}

void MultipPlayer::showMediaCommentTab()
{
            removeTabwidgetTabBar(m_tabWidget1);
            set_showTwoTabBar(m_tabWidget1,0,m_toolBox,QString::fromLocal8Bit("播放列表"),1,m_commentTab,QString::fromLocal8Bit("讨论"));
            m_tabWidget1->setCurrentWidget(m_commentTab);
}

QString MultipPlayer::getCurrentMediaPlayFileName()
{
    return m_curMediaName;
}

QRect MultipPlayer::getDesktopScreenGeometry()
{
    system_screen = QApplication::desktop();
    QRect desktop_screen = system_screen->screenGeometry();
    return desktop_screen;
}

/*文件路径放进容器，将名称显示在列表*/
void MultipPlayer::addFileToList(const QStringList &strList)
{
    for(int i = 0; i<strList.size(); i++)
    {
        QString path = strList.at(i);//文件绝对路径
        QFileInfo fileInfo(path);
        QString name = fileInfo.fileName();//文件名称
        qDebug()<<"file name = "<<name;
        QString fileSuffix = fileInfo.suffix();//文件后缀
        qDebug()<<"file suffix = "<<fileSuffix;
//        QString fullname = path.split(".").last();//文件名称,此法也可行
//        qDebug() << "fullname = " << fullname;
        m_mapList.insert(i,path);//存储路径
        m_mapList2.insert(i,name);//存储歌名带后缀


        QIcon btnIcon1(":/images/icon/video.png");//视频
        QIcon btnIcon2(":/images/icon/mp3.png");//音乐

        QListWidgetItem *pItem = nullptr;

        //判断一下文件类型，加载不同图标
        if(fileSuffix == "mp4")//返回的是mp4,而非 .mp4
        {
//            pItem = new QListWidgetItem(btnIcon1,QString::fromLocal8Bit("%1.").arg(i+1) + name);
            pItem = new QListWidgetItem(btnIcon1,name);
        }
        else if(fileSuffix == "mp3")
        {
//            pItem = new QListWidgetItem(btnIcon2,QString::fromLocal8Bit("%1.").arg(i+1) + name);
            pItem = new QListWidgetItem(btnIcon2,name);
        }
        else if(fileSuffix == "flv")
        {
//            pItem = new QListWidgetItem(btnIcon1,QString::fromLocal8Bit("%1.").arg(i+1) + name);
            pItem = new QListWidgetItem(btnIcon1,name);
        }
        else//后面有需要还可以添加文件类型判断
        {
//            pItem = new QListWidgetItem(btnIcon1,QString::fromLocal8Bit("%1.").arg(i+1) + name);
            pItem = new QListWidgetItem(btnIcon1,name);
        }

        pItem->setToolTip(name);
//        pItem->setCheckState(Qt::Unchecked);//未选中
        pItem->setSizeHint(QSize(180,30));//每个item与整体空间宽度一致,效果不理想，需要在样式中设置

//        QWidget *w = new QWidget;
//        QHBoxLayout *layout = new QHBoxLayout;

//        QPushButton *pushButton1 = new QPushButton(btnIcon1,QString::fromLocal8Bit("%1.").arg(i+1) + name, w);
//        pushButton1->setFixedHeight(30);
//        pushButton1->setFixedWidth(170);
//        pushButton1->setAttribute(Qt::WA_TransparentForMouseEvents,true);//设置鼠标穿透
//        pushButton1->setFixedWidth(30);
//        QIcon btnIcondelete(":/images/icon/itemdelete.png");
//        QPushButton *pushButton2 = new QPushButton(btnIcondelete,QString::fromLocal8Bit("删除"),w);
//        pushButton2->setFixedHeight(30);
//        pushButton2->setFixedWidth(30);
//        QIcon btnIcon3(":/images/icon/selection.png");
//        QPushButton *pushButton3 = new QPushButton(btnIcon3,QString::fromLocal8Bit("收藏"),w);
//        pushButton3->setFixedHeight(30);
//        pushButton3->setFixedWidth(30);
//        layout->addWidget(pushButton1);
//        layout->addStretch(25);
//        layout->addWidget(pushButton2);
//        layout->addWidget(pushButton3);
//        layout->addStretch(5);
//        layout->setSpacing(0);
//        w->setLayout(layout);

        QSqlQuery query;
        query.exec(QString("insert into LocalMusic values(%1,'%2','%3','%4')").arg("NULL").arg(name).arg(path).arg((QString::fromLocal8Bit("高音品质"))));
        qDebug()<<"all data insert successful!";

        m_listWisget2->addItem(pItem);
    }
    emit sig_sendToMusicList();//全部插入到数据库中，才可以通知音乐列表可以加载信息
    m_listWisget2->setCurrentRow(0);
//    ui->playerListWidget->setCurrentRow(0);
    m_toolBox->setCurrentIndex(0);//浮动窗口显示歌曲列表，索引：0

//    for(QMap<int,QString>::iterator it = m_mapList.begin(); it != m_mapList.end(); it++)
//    {
//        qDebug()<<"key = "<<it.key()<<"value = "<<it.value();
//    }
//    for(QMap<int,QString>::iterator it = m_mapList2.begin(); it != m_mapList2.end(); it++)
//    {
//        qDebug()<<"key = "<<it.key()<<"value = "<<it.value();
    //    }
}

/*查找搜索内容并显示*/
void MultipPlayer::findFileFromLineEdit(QString name)
{
    name.remove(QRegExp("\\s"));
    if(name.isEmpty())
    {
        for(int i = 0; i < m_listWisget2->model()->rowCount(); i++)
            m_listWisget2->setRowHidden(i,false);

    }
    else
    {
        for(int i = 0; i <m_listWisget2->model()->rowCount(); i++)
        {
            m_listWisget2->setRowHidden(i,true);
            QString curname = "";
            QAbstractItemModel *model = m_listWisget2->model();
            QModelIndex index;
            for(int j = 0; j <m_listWisget2->model()->columnCount(); j++)
            {
                index = model->index(i,j);
                curname += model->data(index).toString();
            }
            curname.remove(QRegExp("\\s"));
            if(curname.contains(name,Qt::CaseInsensitive)) //CaseSensitive:敏感
               m_listWisget2->setRowHidden(i,false);
        }
    }
}

void MultipPlayer::itemDoubleClick(QListWidgetItem *item)
{
    //获取播放的url地址，根据地址，打开播放的文件
    QUrl url;
    url.setUrl("http://192.168.191.5:80/mv/" + item->text());
    player->setMedia(url);
}

void MultipPlayer::loadFileInfoToWinTitle(int index)
{
        Q_UNUSED(index);
//              QString path = m_mapList[index];
//              qDebug()<<path;
//              ui->label_title->setText(path);
}

/*第一次打开文件*/
void MultipPlayer::on_pushButton_5_clicked()
{
    if(!m_newStart)
    {
        m_fileNames =  QFileDialog::getOpenFileNames(0,//不指定父窗口，设置自己的样式
                                                     QString::fromLocal8Bit("选择文件"),
                                                     QString::fromLocal8Bit("/"),
                                                     QString::fromLocal8Bit("Videos(*avi *mp4 *flv *mp3 *wmv)"),
                                                     0,
                                                     QFileDialog::DontUseNativeDialog);

        //测试功能
        m_fileNames = list_temp;
//        ui->pushButton_5->setFocusPolicy(Qt::NoFocus);//点击按钮后去掉虚线框
        //多文件打开
        if(!m_fileNames.isEmpty())
        {
            addToPlaylist(m_fileNames);//1.添加进播放列表playlist
            addFileToList(m_fileNames);//2.媒体界面显示
            fileType(m_fileNames,0);//3.判断文件类型并作出界面反应
            loadFileInfoToWinTitle(0);//显示第1首歌的title
            ui->horizontalSlider->setEnabled(true);//滚动条
            m_lineEdit->setEnabled(true);//浮动输入框
            m_pTimer2->start(80);//加定时器给界面一个缓冲
            connect(m_pTimer2,&QTimer::timeout,[=](){
            //这里必须加一个定时器，以解决界面缓冲，是的界面来得及反应（主要是标题栏反应不过来）
//                ui->stackedWidget->setCurrentIndex(2);//索引2,界面显示视频
                m_playerState = QMediaPlayer::PlayingState;
                ui->pushButton_pauseStart->setIcon(QIcon(":/images/icon/pausehover.png"));
                ui->pushButton_pauseStart->setToolTip(QString::fromLocal8Bit("暂停"));
                m_newStart = true;
            });
            player->play();//调试暂停2022-05-14
            setMainCurrentIndex(1);
        }
    }
}

/*重新打开播放新文件*/
void MultipPlayer::on_pushButton_6_clicked()
{
    if(!m_newStart)
    {
        return;
    }
    else
    {
        player->pause();
        ui->pushButton_pauseStart->setIcon(QIcon(":/images/icon/playhover.png"));//播放
        ui->pushButton_pauseStart->setToolTip(QString::fromLocal8Bit("播放"));
        m_fileNames =  QFileDialog::getOpenFileNames(0,//不指定父窗口，设置自己的样式,
                                                     QString::fromLocal8Bit("选择文件"),
                                                     QString::fromLocal8Bit("/"),
                                                     QString::fromLocal8Bit("Videos(*avi *mp4 *flv *mp3 *wmv)"),
                                                     0,
                                                     QFileDialog::DontUseNativeDialog);
        if(!m_fileNames.isEmpty())
        {
            QSqlQuery query;
            //再次添加新数据，数据库先清空原有数据
            query.exec("delete from LocalMusic;");
            //sqlite不支持truncate清除主键自增id，只能手动清除id序列，使新数据id从0开始
            query.exec("delete from sqlite_sequence where name = 'LocalMusic';");
            playlist->clear();
            addToPlaylist(m_fileNames);
            m_listWisget2->clear();
            m_listWisget3->clear();
            addFileToList(m_fileNames);
            fileType(m_fileNames,0);//判断文件类型并作出界面反应
            player->play();//调试暂停 2022-05-14
            setMainCurrentIndex(1);
            m_playerState = QMediaPlayer::PlayingState;
            ui->pushButton_pauseStart->setIcon(QIcon(":/images/icon/pausehover.png"));
            ui->pushButton_pauseStart->setToolTip(QString::fromLocal8Bit("暂停"));
        }
        else
        {
            m_playerState = QMediaPlayer::PausedState;
        }
    }
}

/*打开本地文件*/
void MultipPlayer::openLocalFile()
{
    on_pushButton_5_clicked();
}


/*切换stackwidget*/
void MultipPlayer::setMainCurrentIndex(const int index)
{
    if(index == 0)
    {
        ui->stackedWidget->setCurrentIndex(0);//空白页面
    }
    else if(index == 1)
    {
        ui->stackedWidget->setCurrentIndex(1);//视频界面
    }
    else if(index == 2)
    {
        ui->stackedWidget->setCurrentIndex(2);//音乐界面
    }
    else
    {

    }
}

/*点击左侧节目列表转换显示页面*/
void MultipPlayer::switchListPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void MultipPlayer::setVideoRate(int value)
{
       player->setPlaybackRate(value);
}

/*更新rate,type,layout*/
void MultipPlayer::updateRateTypeUiLayout()
{
    ui->pushButton_pauseStart->setIcon(QIcon(":/images/icon/pausehover.png"));//播放
    player->setPlaybackRate(1.0);//速率恢复正常
}

/*播放and暂停*/
void MultipPlayer::on_pushButton_pauseStart_clicked()
{
    ui->pushButton_pauseStart->setFocusPolicy(Qt::NoFocus);//点击按钮后去掉虚线框
    if(m_playerState == QMediaPlayer::PlayingState)
    {
        player->pause();
        m_playerState = QMediaPlayer::PausedState;
        ui->pushButton_pauseStart->setIcon(QIcon(":/images/icon/playhover.png"));
        ui->pushButton_pauseStart->setToolTip(QString::fromLocal8Bit("播放"));
    }
    else if(m_playerState == QMediaPlayer::PausedState)
    {
        player->play();
        m_playerState = QMediaPlayer::PlayingState;
        ui->pushButton_pauseStart->setIcon(QIcon(":/images/icon/pausehover.png"));
        ui->pushButton_pauseStart->setToolTip(QString::fromLocal8Bit("暂停"));
    }
}

/*每秒更新一次函数*/
void MultipPlayer::on_time()
{
    //方法1
    int pos  = player->position()/1000;//最新的进度
    ui->horizontalSlider->setValue(pos);//设置进度显示
//    QDateTime dt1 = QDateTime::fromSecsSinceEpoch(m_times);
//    QString str = dt1.toString("hh:mm:ss");
//    int min = pos/60;
//    int sec = pos%60;
//    QString str2 = QString::asprintf("%d:%d",min,sec);
//    QDateTime dt2 = QDateTime::fromSecsSinceEpoch(pos);
//    QString str2 = dt2.toString("hh:mm:ss");
//    ui->label_time->setText(str2+ "/" +str);
    //方法2
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
//    qDebug() <<QString::fromLocal8Bit("总的 时间：")<< qTZ;
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
//    qDebug() <<QString::fromLocal8Bit("进度时间：")<< qTime;
    ui->label_time->setText(qTime+ "/" +qTZ);

    //方法3
//    int ss = 1000;
//        int mi = ss * 60;
//        int hh = mi * 60;
//        int dd = hh * 24;

//        long day = ms / dd;
//        long hour = (ms - day * dd) / hh;
//        long minute = (ms - day * dd - hour * hh) / mi;
//        long second = (ms - day * dd - hour * hh - minute * mi) / ss;
//        long milliSecond = ms - day * dd - hour * hh - minute * mi - second * ss;

//        QString hou = QString::number(hour,10);
//        QString min = QString::number(minute,10);
//        QString sec = QString::number(second,10);
//        QString msec = QString::number(milliSecond,10);

//        //qDebug() << "minute:" << min << "second" << sec << "ms" << msec <<endl;

    //        return hou + ":" + min + ":" + sec ;
}

/*监测处理媒体播放状态*/
void MultipPlayer::checkChandleMediaPlayerStatus(QMediaPlayer::State newState)
{
    qDebug() << "media status had changed! NEW STATUS:" <<newState ;
    if(player->media().isNull()) return;
    if(newState == QMediaPlayer::PausedState)
    {
        ui->pushButton_pauseStart->setIcon(QIcon(":/images/icon/playhover.png"));//播放
        ui->pushButton_pauseStart->setToolTip(QString::fromLocal8Bit("播放"));
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::PausedState");
        emit sig_currentMediaPlayStatus(false);//false 代表暂停状态
    }
    else if(newState == QMediaPlayer::PlayingState)
    {
        ui->pushButton_pauseStart->setIcon(QIcon(":/images/icon/pausehover.png"));
        ui->pushButton_pauseStart->setToolTip(QString::fromLocal8Bit("暂停"));
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::PlayingState");
        emit sig_currentMediaPlayStatus(true);//true 代表播放状态
    }
    else if(newState == QMediaPlayer::StoppedState)
    {

        qDebug() << QString::fromLocal8Bit("QMediaPlayer::StoppedState");
        emit sig_currentMediaPlayStatus(false);//false 代表暂停状态
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("other unknow state!");
    }
}

//监测处理媒体本身状态，加载完毕，正在加载，缓冲结束，正在缓冲，未知，有效等
void MultipPlayer::checkChandleMediaStatus()
{
    if(player->media().isNull()) return;

    if(player->mediaStatus() == QMediaPlayer::UnknownMediaStatus)//未知媒体状态
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::UnknownMediaStatus");
    }
    else if(player->mediaStatus() == QMediaPlayer::NoMedia)//无媒体状态
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::NoMedia");
        ui->stackedWidget->setCurrentIndex(0);//空白页
    }
    else if(player->mediaStatus() == QMediaPlayer::LoadingMedia)//加载媒体中
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::LoadingMedia");
        mediaLoadingStatusProgressBar_Start();
    }
    else if(player->mediaStatus() == QMediaPlayer::LoadedMedia)//媒体加载完毕
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::LoadedMedia");
        mediaLoadingStatusProgressBar_End();
    }
    else if(player->mediaStatus() == QMediaPlayer::StalledMedia)//媒体停顿
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::StalledMedia");
    }
    else if(player->mediaStatus() == QMediaPlayer::BufferingMedia)//媒体正在缓冲
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::BufferingMedia");
        mediaLoadingStatusProgressBar_Start();
    }
    else if(player->mediaStatus() == QMediaPlayer::BufferedMedia)//媒体缓冲完毕
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::BufferedMedia");
        mediaLoadingStatusProgressBar_End();
    }
    else if(player->mediaStatus() == QMediaPlayer::EndOfMedia)//媒体结束
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::EndOfMedia");
    }
    else if(player->mediaStatus() == QMediaPlayer::InvalidMedia)//媒体无效
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::InvalidMedia");
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("other unknow problem!");
    }
}

/*上一首*/
void MultipPlayer::on_pushButton_previous_clicked()
{
//    int row = playlist->mediaCount();
    int current = playlist->currentIndex();
    if(--current < 0)//先做--运算，在比较
        {
        current = 0;//第一首不能再往前
    }
    playlist->setCurrentIndex(current);
    fileType(current);
    player->play();
}

//接收托盘发过来的音量信号
void MultipPlayer::receiveSystemTraySendSoundValue(int value)
{
    emit sig_currentMediaSoundValueChange(value);
}

//设置静音
void MultipPlayer::on_setCurrentMediaSoundSatus()
{
    if(player->isMuted())
    {
        player->setMuted(false);
    }
    else
    {
        player->setMuted(true);
    }
}

/*下一首*/
void MultipPlayer::on_pushButton_next_clicked()
{
    int row = playlist->mediaCount();
    int current = playlist->currentIndex();
    if(++current > row)
    {
        current = row;//最后一首不能再往后
    }
    playlist->setCurrentIndex(current);
    fileType(current);
    player->play();
}

//鼠标按下事件
/*
 *作用：
 *1.判断是否时左键点击 _isleftpressed
 *2.获取光标在屏幕中的位置 _plast
 *3.左键按下时光标所在区域 _curpos
 */
void MultipPlayer::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (event->button() == Qt::LeftButton)
    {
        this->_isleftpressed = true;
        QPoint temp = event->globalPos();
        _plast = temp;
        _curpos = countFlag(event->pos(), countRow(event->pos()));
    }
}

//鼠标释放事件
/*
 *作用：
 *1.将_isleftpressed 设为false
 *2.将光标样式恢复原样式  setCursor(Qt::ArrowCursor);
 */
void MultipPlayer::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (_isleftpressed)
        _isleftpressed = false;
    setCursor(Qt::ArrowCursor);
}

void MultipPlayer::changeEvent(QEvent *event)
{
    switch (event->type())
        {
        case QEvent::WindowStateChange:
            {
                this->update();
                this->repaint();
                event->ignore();
                break;
            }
        default:
            break;
    }
}

/*界面卡顿*/
void MultipPlayer::showEvent(QShowEvent *event)
{
    this->setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(event);
}

/*大小改变事件*/
void MultipPlayer::resizeEvent(QResizeEvent *event)
{
//    int x = this->mapToGlobal(this->pos()).x();
//    int y = this->mapToGlobal(this->pos()).y();
//    m_widget1->move(x,y+30);
//    m_widget1->setMinimumHeight(ui->stackedWidget->height());
//    m_widget1->raise();
//    m_widget1->show();
    Q_UNUSED(event);
//    updateFoldButtonGeometry();
//    updatePlayAdustForm();
    updateFoldButtonGeometry();
    setFoldButtonStyle();
}

/*键盘事件*/
void MultipPlayer::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)//ESC键盘
    {
        chandleRestoreWindow();
    }
}

//鼠标移动事件
void MultipPlayer::mouseMoveEvent(QMouseEvent *event)
{
    //拖动之前判断是否串口处于最大化
    if(this->isMaximized())
    {
        return;
    }
    Q_UNUSED(event);
    if(this->isFullScreen()) return;	//窗口铺满全屏，直接返回，不做任何操作
    int poss = countFlag(event->pos(), countRow(event->pos()));
    setCursorType(poss);
    if (_isleftpressed)//是否左击
    {
        QPoint ptemp = event->globalPos();
        ptemp = ptemp - _plast;
        if (_curpos == 22)//移动窗口
        {
            ptemp = ptemp + pos();
            move(ptemp);
        }
        else
        {
            QRect wid = geometry();
            switch (_curpos)//改变窗口的大小
            {
            case 11:wid.setTopLeft(wid.topLeft() + ptemp); break;//左上角
            case 13:wid.setTopRight(wid.topRight() + ptemp); break;//右上角
            case 31:wid.setBottomLeft(wid.bottomLeft() + ptemp); break;//左下角
            case 33:wid.setBottomRight(wid.bottomRight() + ptemp); break;//右下角
            case 12:wid.setTop(wid.top() + ptemp.y()); break;//中上角
            case 21:wid.setLeft(wid.left() + ptemp.x()); break;//中左角
            case 23:wid.setRight(wid.right() + ptemp.x()); break;//中右角
            case 32:wid.setBottom(wid.bottom() + ptemp.y()); break;//中下角
            }
            setGeometry(wid);
        }
        _plast = event->globalPos();//更新位置
    }
}

//获取光标在窗口所在区域的 列  返回行列坐标
int MultipPlayer::countFlag(QPoint p,int row)//计算鼠标在哪一列和哪一行
{
    if(p.y()<MARWIDTH)
        return 10+row;
    else if(p.y()>this->height()-MARWIDTH)
        return 30+row;
    else
        return 20+row;
}

//获取光标在窗口所在区域的 行   返回行数
int MultipPlayer::countRow(QPoint p)
{
    return (p.x()<MARWIDTH) ? 1 : (p.x()>(this->width() - MARWIDTH) ? 3 : 2);
}

//根据鼠标所在位置改变鼠标指针形状
void MultipPlayer::setCursorType(int flag)
{
    switch(flag)
    {
    case 11:
    case 33:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case 13:
    case 31:
        setCursor(Qt::SizeBDiagCursor);break;
    case 21:
    case 23:
        setCursor(Qt::SizeHorCursor);break;
    case 12:
    case 32:
        setCursor(Qt::SizeVerCursor);break;
    case 22:
        setCursor(Qt::ArrowCursor);
        QApplication::restoreOverrideCursor();//恢复鼠标指针性状
        break;
    }
}

/*展开更多*/
void MultipPlayer::on_moreBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

/*顶层搜索框鼠标进入离开*/
void MultipPlayer::searchMouseEnterLeaveShow(QObject *watched, QEvent *event)
{
    Q_UNUSED(watched);
    Q_UNUSED(event);
}

/*处理视频界面双击退出事件*/
bool MultipPlayer::videoDouleExit(QObject *watched, QEvent *event)
{
    if(watched == ui->stackedWidget)
    {
        {
            if(event->type() == QEvent::KeyPress)
            {
                //获取键盘输入事件对象
                QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
                if(keyEvent->key() == Qt::Key_Escape)
                {
                    videoWidget->setWindowFlags(Qt::SubWindow);
                    videoWidget->showNormal();
                }
            }
            else if(event->type() == QEvent::MouseButtonDblClick)
            {
                //static_cast:可进行基类与派生类的上下行转换；但是下行转换（基类转到派生类）没有动态类型检查，是不安全的；
                //dynamic_cast:可以进行上下行转换，且下行转换更安全；以及类之间的交叉转换；

                if(m_playerState == QMediaPlayer::PlayingState)//左键双击
                {
                    videoWidget->setWindowFlags(Qt::Window);//设置为顶级窗口
//                    QRect screen =  getDesktopScreenGeometry();
//                    videoWidget->resize(screen.width(),screen.height());
                    videoWidget->showFullScreen();
                    qDebug() << "fullscreen";
                }
            }
        }
    }
    return 0;
}

/*音量调节界面显隐*/
void MultipPlayer::volumeAdjustShowUi(QObject *watched, QEvent *event)
{
        /*音量调节显示*/
    if(watched == ui->pushButton_sound)
    {
//        qDebug()<<"pushButton_sound enter!";
        if(event->type() == QEvent::Enter && this->isActiveWindow())
        {
                    int x = ui->pushButton_sound->parentWidget()->mapToGlobal(ui->pushButton_sound->pos()).x();
                    int y = ui->pushButton_sound->parentWidget()->mapToGlobal(ui->pushButton_sound->pos()).y();
                    int h = m_muteDlg->height();
//                    qDebug() << "QPont_g(" << x << "," << y << ")";
                    m_muteDlg->setGeometry(x-11,y-h-6,m_muteDlg->width(),m_muteDlg->height());//
                    m_muteDlg->raise();
                    m_muteDlg->show();
        }
        else if(event->type() == QEvent::Leave)
        {
//            qDebug() << "pushButton_sound leave!";
            QRect tempRect = ui->pushButton_sound->geometry();
//            qDebug() << "old rect:" << tempRect << "cursor:" << ui->pushButton_sound->parentWidget()->mapFromGlobal(QCursor::pos());
            tempRect.moveTo(ui->pushButton_sound->pos().x(),ui->pushButton_sound->y()-ui->pushButton_sound->height());
//            qDebug() << "new rect:" << tempRect;
            if(!tempRect.contains(ui->pushButton_sound->parentWidget()->mapFromGlobal(QCursor::pos())))//鼠标在固定的矩形区域外
            m_muteDlg->hide();
        }
    }
}

void MultipPlayer::stackWidgetSliderButtonEventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->stackedWidget)
    {
        //01.注意区分界面隐藏和按钮隐藏是两个不同的状态,
        //02.按钮的样式取决于m_isHide状态，显隐取决于进入还是离开
        //03.进入的时候更新坐标和样式，点击以后也要更新坐标和样式
        if(event->type() == QEvent::Enter)//鼠标进入监视对象
        {
//            qDebug() << "stackwidget enter";
            updateFoldButtonGeometry();
            setFoldButtonStyle();
            m_foldBtn->show();
        }
        else if(event->type() == QEvent::Leave)//鼠标离开监视对象
        {
            m_foldBtn->hide();
//            qDebug() << "stackwidget leave";
        }
    }
}

/*播放列表界面搜索框鼠标进入离开*/
void MultipPlayer::playlistMouseEnterLeave(QObject *watched, QEvent *event)
{
    if(watched == m_lineEdit)//监视器每次只能监视一个对象，这里需要分开写
    {
        /*搜索框，搜索按钮鼠标离开*/
        if(event->type() == QEvent::Leave)
        {
//            qDebug() << "mouse Leave!";
            m_searchBtn->setStyleSheet("QPushButton"
                                         "{"
                                         "color:#ff5c38;"
                                         "background:rgb(75, 75, 75);"
                                         "border-top-right-radius:0px;"
                                         "border-bottom-right-radius:0px;"
                                         "border-bottom-left-radius:0px;"
                                         "border-top-left-radius:0px;"
                                         "}"
                                         );

            m_lineEdit->setStyleSheet("QLineEdit"
                                              "{"
                                              "color:#cccccc;"
                                              "font-size:14px;"
                                              "background-color: rgb(81, 81, 81);"
                                              "selection-background-color: #D1DBCB;"
                                              "border:transparent;"
                                              "border-top-left-radius:0px;"
                                              "border-bottom-left-radius:0px;"
                                              "border-bottom-right-radius:0px;"
                                              "border-top-right-radius:0px;"
                                              "padding-left:15px;"
                                              "}"
                                              );

        }
        /*搜索框，搜索按钮鼠标进入*/
        if(event->type() == QEvent::Enter)
        {
//             qDebug() << "mouse Enter!";
            m_searchBtn->setStyleSheet("QPushButton"
                                         "{"
                                         "color:white;"
                                         "border: 1px solid #ff5c38;"
                                         "border-left:transparent;"
                                         "border-top-right-radius:0px;"
                                         "border-bottom-right-radius:0;px;"
                                         "border-bottom-left-radius:0px;"
                                         "border-top-left-radius:0px;"
                                         "}"
                                         );
            m_lineEdit->setStyleSheet("QLineEdit"
                                              "{"
                                              "color:#cccccc;"
                                              "font-size:14px;"
                                              "background-color: rgb(33, 33, 33);"
                                              "border:1px solid #ff5c38;"
                                              "border-right:transparnet;"
                                              "border-top-left-radius:0px;"
                                              "border-bottom-left-radius:0px;"
                                              "border-bottom-right-radius:0px;"
                                              "border-top-right-radius:0px;"
                                              "padding-left:15px;"
                                              "}"
                                              );

        }
    }

    if(watched == m_searchBtn)//监视器每次只能监视一个对象，这里需要分开写
    {
        /*搜索框，搜索按钮鼠标离开*/
        if(event->type() == QEvent::Leave)
        {
//            qDebug() << "mouse Leave!";
            m_searchBtn->setStyleSheet("QPushButton"
                                         "{"
                                         "color:#ff5c38;"
                                         "background:rgb(75, 75, 75);"
                                         "border-top-right-radius:0px;"
                                         "border-bottom-right-radius:0px;"
                                         "border-bottom-left-radius:0px;"
                                         "border-top-left-radius:0px;"
                                         "}"
                                         );

            m_lineEdit->setStyleSheet("QLineEdit"
                                              "{"
                                              "color:#cccccc;"
                                              "font-size:14px;"
                                              "background-color: rgb(81, 81, 81);"
                                              "selection-background-color: #D1DBCB;"
                                              "border:transparent;"
                                              "border-top-left-radius:0px;"
                                              "border-bottom-left-radius:0px;"
                                              "border-bottom-right-radius:0px;"
                                              "border-top-right-radius:0px;"
                                              "padding-left:15px;"
                                              "}"
                                              );

        }
        /*搜索框，搜索按钮鼠标进入*/
        if(event->type() == QEvent::Enter)
        {
//            qDebug() << "mouse Enter!";
            m_searchBtn->setStyleSheet("QPushButton"
                                         "{"
                                         "color:white;"
                                         "border: 1px solid #ff5c38;"
                                         "border-left:transparent;"
                                         "border-top-right-radius:0px;"
                                         "border-bottom-right-radius:0;px;"
                                         "border-bottom-left-radius:0px;"
                                         "border-top-left-radius:0px;"
                                         "}"
                                         );
            m_lineEdit->setStyleSheet("QLineEdit"
                                              "{"
                                              "color:#cccccc;"
                                              "font-size:14px;"
                                              "background-color: rgb(33, 33, 33);"
                                              "border:1px solid #ff5c38;"
                                              "border-right:transparnet;"
                                              "border-top-left-radius:0px;"
                                              "border-bottom-left-radius:0px;"
                                              "border-bottom-right-radius:0px;"
                                              "border-top-right-radius:0px;"
                                              "padding-left:15px;"
                                              "}"
                                              );

        }
    }
}


/*打开本地文件*/
void MultipPlayer::help_aboutLocalFile()
{
     openLocalFile();
     this->show();
}


/*调节界面*/
void MultipPlayer::set_adjustBright()
{
//    QMouseEvent *event = new QMouseEvent();
//    QPoint point = mapToGlobal(this->pos()+ui->widget_splider->pos()+ui->Btnlogin->pos());
    if(m_adjustBright)
    {
        if(!m_adjustBright->isHidden())
        {
            m_adjustBright->hide();
        }
        else
        {
//            QMenu *menu_adj = new QMenu(this);
//            menu_adj->setFixedSize(410,338);
//            QWidgetAction *waction = new QWidgetAction(menu_adj);
//            waction->setDefaultWidget(m_adjustBright);
//            menu_adj->addAction(waction);
//            menu_adj->move(QCursor::pos().x()-200,QCursor::pos().y()-370);
//            ui->Btn_adjust->setMenu(menu_adj);
//            m_adjustBright->move(point.x()-200,point.y()-370);
            int x = ui->Btn_adjust->parentWidget()->mapToGlobal(ui->Btn_adjust->pos()).x();
            int y = ui->Btn_adjust->parentWidget()->mapToGlobal(ui->Btn_adjust->pos()).y();
            int w = m_adjustBright->width();
            int h = m_adjustBright->height();
            m_adjustBright->setGeometry(x-w/2-50,y-h-9,m_adjustBright->width(),m_adjustBright->height());
            m_adjustBright->raise();
            m_adjustBright->show();
        }
    }
    else
    {
        m_adjustBright = new AdjustBright();
        int x = ui->Btn_adjust->parentWidget()->mapToGlobal(ui->Btn_adjust->pos()).x();
        int y = ui->Btn_adjust->parentWidget()->mapToGlobal(ui->Btn_adjust->pos()).y();
        int w = m_adjustBright->width();
        int h = m_adjustBright->height();
        m_adjustBright->setGeometry(x-w/2-50,y-h-9,m_adjustBright->width(),m_adjustBright->height());
        m_adjustBright->raise();
        m_adjustBright->show();
    }

}

/*调节播放模式*/
void MultipPlayer::adjust_playBackMode(int index)
{
    qDebug()<< "player mode =" <<index;
    if(index == 0)
    {
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }
    else if(index == 1)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
    }
    else if(index == 2)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Random);
    }
    else if(index == 3)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    }
}

/*调节屏幕占比*/
void MultipPlayer::adjust_aspectRatioMode(int index)
{
    qDebug()<<index;
    if(index == 0)
    {

    }
    else if(index == 1)
    {
        videoWidget->setAspectRatioMode(Qt::IgnoreAspectRatio);
    }
    else if(index == 2)
    {
        videoWidget->setAspectRatioMode(Qt::KeepAspectRatio);
    }
    else if(index == 3)
    {
        videoWidget->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);
    }
}

/*获取媒体信息，亮度，对比度，饱和度，色调*/
void MultipPlayer::update_adjustBright()
{
    videoWidget->setBrightness(10);
    videoWidget->setSaturation(10);
    videoWidget->setContrast(10);
    videoWidget->setHue(10);
}

void MultipPlayer::downloadInternetPathRecource()
{

}

void MultipPlayer::playHttpRequireRecourse(const QString &url)
{
    QUrl url_rec;
    url_rec.setUrl("http://192.168.220.128:8080/group1/videos/wanjiang_MP4HV.mp4");
    player->setMedia(url_rec);
    player->play();
}

/*弹幕*/
//void MultipPlayer::on_pushButton_danmu_clicked()
//{
//    if(!m_danmuStatus)
//    {
//        ui->lineEdit_danmu->setEnabled(true);
//    }
//    else
//    {
//        ui->lineEdit_danmu->setEnabled(false);
//    }
//    m_danmuStatus = !m_danmuStatus;
//}

void MultipPlayer::chandleRestoreWindow()
{
    if(!m_winMax)//非最大化
    {
        this->showMaximized();
        emit sig_winVStatus(m_winMax);//向标题栏发送最大化状态信号
    }
    else
    {
        this->showNormal();
        if(m_videoTitleBar->isHidden()) m_videoTitleBar->show();
        if(ui->stackedWidget_player->isHidden()) ui->stackedWidget_player->show();
        emit sig_winVStatus(m_winMax);//向窗口发送正常状态信号
    }
    m_winMax = !m_winMax;
}

bool MultipPlayer::loadCollectListWidgetList()
{
    m_listWisget3->clear();
    if(m_mapList_collect.isEmpty())
    {
        return false;
    }
    else
    {
        for(QMap<int,QString>::iterator iter = m_mapList_collect.begin();iter != m_mapList_collect.end();++iter)
        {
            m_listWisget3->addItem(new QListWidgetItem(iter.value()));
        }
    }
    return true;
}

/*槽函数：设置收藏按钮状态*/
bool MultipPlayer::setCollectBtnShowStatus()
{
    bool hasVal = findCollectListStatus(m_listWisget3,getCurrentMediaPlayFileName());
    qDebug() << getCurrentMediaPlayFileName() << "current collect status = " <<hasVal;
    if(hasVal)//有，设置收藏（红心）
    {
//        ui->pushButton_collect->setChecked(true);
        ui->pushButton_collect->setStyleSheet("QPushButton{"
                                              "border-image: url(:/images/icon/play_collect_checked.png);"
                                              "}");
    }
    else//没有，设置非收藏（灰色）
    {
//        ui->pushButton_collect->setChecked(false);
        ui->pushButton_collect->setStyleSheet("QPushButton{"
                                              "border-image: url(:/images/icon/play_collect_unchecked.png);"
                                              "}");
    }
    return 0;
}

/*私有槽函数：遍历列表，判断有没有收藏当前媒体*/
bool MultipPlayer::findCollectListStatus(QListWidget *listdgt, QString name)
{
    int row = 0;
    QString line;
    while(row < listdgt->count())
    {
        line = listdgt->item(row)->text();
        qDebug() << line << "\n";
        if(name == line)
        {
            qDebug() << "source = "<< name << "finded media" << "line =" << line;
            return true;//循环当中找到了，直接返回true
        }
       row++;
    }
    qDebug() << name << " no find media";
    return false;//循环完毕，没有找到，返回 false
}

//查找当前媒体在收藏列表中的位置
int MultipPlayer::getCurrentMediaRowOfCollectList(QListWidget* listdgt, QString name)
{
    int row = 0;
    QString mname;
    while(row < listdgt->count())
    {
        mname = listdgt->item(row)->text();
        qDebug() << mname << "\n";
        if(name == mname)
        {
            return row;//循环当中找到了，返回row
            qDebug()<< "current media " <<  name << "finded";
        }
       row++;
    }
    qDebug()<< "current media " <<  name << "no-find";
    return -1;//没找到，返回row为-1
}

//重载函数1
void MultipPlayer::addCurrentMediaToList_Collect(QListWidget *destList)
{
    bool hasValue = findCollectListStatus(destList,m_curMediaName);//判断是否收藏
    qDebug() << QString::fromLocal8Bit("当前播放媒体收藏状态：") << hasValue;
    qDebug() << QString::fromLocal8Bit("添加前收藏总数：") << destList->count();
    if(!hasValue)//不存在则添加进收藏
    {
        if(m_curMediaName.isEmpty()) return;
        destList->insertItem(0,m_curMediaName);//头插法
        ui->pushButton_collect->setStyleSheet("QPushButton{"
                                              "border-image: url(:/images/icon/play_collect_checked.png);"
                                              "}");
    }
    else//存在则取消收藏
    {
        //按理第一步能确认媒体在收藏列表，那么一定能返回行号，所以对-1不做处理
        QListWidgetItem *item = destList->takeItem(getCurrentMediaRowOfCollectList(destList,m_curMediaName));
        ui->pushButton_collect->setStyleSheet("QPushButton{"
                                              "border-image: url(:/images/icon/play_collect_unchecked.png);"
                                              "}");
        delete item;//手动释放
    }
    qDebug() << QString::fromLocal8Bit("添加后收藏总数：") << destList->count();
}

//重载函数2
void MultipPlayer::addCurrentMediaToList_Collect(QListWidget *destList, QString text)
{
    bool hasValue = findCollectListStatus(destList,text);//判断是否收藏
    qDebug() << QString::fromLocal8Bit("当前播放媒体收藏状态：") << hasValue;
    qDebug() << QString::fromLocal8Bit("添加前收藏总数：") << destList->count();
    if(!hasValue)//不存在则添加进收藏
    {
        if(text.isEmpty()) return;
        destList->insertItem(0,text);//头插法
        ui->pushButton_collect->setStyleSheet("QPushButton{"
                                              "border-image: url(:/images/icon/play_collect_checked.png);"
                                              "}");
    }
    else//存在则取消收藏
    {
        //按理第一步能确认媒体在收藏列表，那么一定能返回行号，所以对-1不做处理
        QListWidgetItem *item = destList->takeItem(getCurrentMediaRowOfCollectList(destList,text));
        ui->pushButton_collect->setStyleSheet("QPushButton{"
                                              "border-image: url(:/images/icon/play_collect_unchecked.png);"
                                              "}");
        delete item;//手动释放
    }
    qDebug() << QString::fromLocal8Bit("添加后收藏总数：") << destList->count();
}

void MultipPlayer::addCurrentMediaToList_History(QListWidget *destList)
{
    bool hasValue = findCollectListStatus(destList,m_curMediaName);//判断是否收藏
    qDebug() << "current media collect status = " << hasValue;
    if(!hasValue)//不存在则添加进收藏
    {
        if(m_curMediaName.isEmpty()) return;
        qDebug() << "now collect list's count = " << destList->count();
        destList->insertItem(0,m_curMediaName);//头插法
    }
    else
    {
        //存在，什么也不做
    }
}

void MultipPlayer::mediaLoadingStatusProgressBar_Start()
{
    if(this->isHidden() || this->isMinimized()) return;
    VideoProgressBar::getInstance()->raise();
    VideoProgressBar::getInstance()->show();
}

void MultipPlayer::mediaLoadingStatusProgressBar_End()
{
    if(!VideoProgressBar::getInstance())
    {
        return;
    }
    else
    {
        VideoProgressBar::getInstance()->hide();
    }
}

bool MultipPlayer::updateProgressBarGeometry()
{
    int x = ui->stackedWidget->parentWidget()->mapToGlobal(ui->stackedWidget->pos()).x();
    int y = ui->stackedWidget->parentWidget()->mapToGlobal(ui->stackedWidget->pos()).y();
    VideoProgressBar::getInstance()->setGeometry(x+ui->stackedWidget->width()/2 - VideoProgressBar::getInstance()->width()/2,
                                                 y+ui->stackedWidget->height()/2 - VideoProgressBar::getInstance()->height()/2,
                                                 VideoProgressBar::getInstance()->width(),
                                                 VideoProgressBar::getInstance()->height());
    return 0;
}

//播放列表右键菜单
void MultipPlayer::slot_createRight_playListTable(const QPoint &pos)
{
    if(m_listWisget2->count() == 0) return;//没有item就返回，不出现右键菜单
    QMenu *playMenu = new QMenu(m_listWisget2);
    playMenu->setObjectName(QString::fromLocal8Bit("playlist_playMenu"));
    QAction *playAction = new QAction(QIcon(""),QString::fromLocal8Bit("播放"));
    QAction *nextAction = new QAction(QIcon(""),QString::fromLocal8Bit("下一首"));
    QAction *deleteAction = new QAction(QIcon(""),QString::fromLocal8Bit("删除"));
    QAction *downloadAction = new QAction(QIcon(""),QString::fromLocal8Bit("下载"));
    QAction *collectAction = new QAction(QIcon(""),QString::fromLocal8Bit("收藏"));
    QAction *selectallAction = new QAction(QIcon(""),QString::fromLocal8Bit("全选"));
    QAction *clearAction = new QAction(QIcon(""),QString::fromLocal8Bit("清空列表"));
//    int row = m_listWisget2->currentRow();//当前选中的行号，注意-1和向后传递的情况
//    QString text = m_listWisget2->currentItem()->text();
    //播放
    connect(playAction,&QAction::triggered,[=](){slot_playCurrentListItem(m_listWisget2,m_listWisget2->currentRow());});
    //下一首
    connect(nextAction,&QAction::triggered,[=](){slot_playNextListItem(m_listWisget2,m_listWisget2->currentRow());});
    //删除
    connect(deleteAction,&QAction::triggered,[=](){slot_deleteListRecord(m_listWisget2,m_listWisget2->currentRow());});
    //下载
    connect(downloadAction,&QAction::triggered,[=](){slot_downloadListItem(m_listWisget2,m_listWisget2->currentRow());});
    //全选
    connect(selectallAction,&QAction::triggered,[=](){slot_selectAllListItem(m_listWisget2);});
    //清空列表
    connect(clearAction,&QAction::triggered,[=](){slot_clearListAllRecords(m_listWisget2);});
    //收藏
    connect(collectAction,&QAction::triggered,[=](){slot_collectListItem(m_listWisget3,m_listWisget2->currentItem()->text());});
    playMenu->addAction(playAction);
//    playMenu->addAction(nextAction);
    playMenu->addAction(deleteAction);
    playMenu->addAction(downloadAction);
//    playMenu->addAction(selectallAction);
    playMenu->addAction(collectAction);
    playMenu->addAction(clearAction);
    playMenu->exec(m_listWisget2->mapToGlobal(pos));//deng同于playMenu->exec(this->mapToGlobal(m_listWisget2->mapToParent(pos)));
    delete playMenu;
    playMenu = nullptr;
}

//收藏列表右键菜单
void MultipPlayer::slot_createRight_playCollectTable(const QPoint &pos)
{
    if(m_listWisget3->count() == 0) return;
    QMenu *collectMenu = new QMenu(m_listWisget3);
    collectMenu->setObjectName(QString::fromLocal8Bit("playlist_collectMenu"));
    QAction *playAction = new QAction(QIcon(""),QString::fromLocal8Bit("播放"));
    QAction *downloadAction = new QAction(QIcon(""),QString::fromLocal8Bit("下载"));
    QAction *deleteAction = new QAction(QIcon(""),QString::fromLocal8Bit("删除"));
    QAction *nextAction = new QAction(QIcon(""),QString::fromLocal8Bit("下一首"));
    QAction *selectallAction = new QAction(QIcon(""),QString::fromLocal8Bit("全选"));
    QAction *collectAction = new QAction(QIcon(""),QString::fromLocal8Bit("取消收藏"));
    QAction *clearAction = new QAction(QIcon(""),QString::fromLocal8Bit("清空列表"));
//    int row = m_listWisget3->currentRow();//当前选中的行号，注意-1和向后传递的情况
//    QString text = m_listWisget3->currentItem()->text();
    //播放
    connect(playAction,&QAction::triggered,[=](){slot_playCurrentListItem(m_listWisget3,m_listWisget3->currentRow());});
    //下一首
    connect(nextAction,&QAction::triggered,[=](){slot_playNextListItem(m_listWisget3,m_listWisget3->currentRow());});
    //删除
    connect(deleteAction,&QAction::triggered,[=](){slot_deleteListRecord(m_listWisget3,m_listWisget3->currentRow());});
    //下载
    connect(downloadAction,&QAction::triggered,[=](){slot_downloadListItem(m_listWisget3,m_listWisget3->currentRow());});
    //清空列表
    //全选
    connect(selectallAction,&QAction::triggered,[=](){slot_selectAllListItem(m_listWisget3);});
    connect(clearAction,&QAction::triggered,[=](){slot_clearListAllRecords(m_listWisget3);});
    //收藏
    connect(collectAction,&QAction::triggered,[=](){slot_collectListItem(m_listWisget3,m_listWisget3->currentItem()->text());});
    collectMenu->addAction(playAction);
    collectMenu->addAction(downloadAction);
//    collectMenu->addAction(deleteAction);
//    collectMenu->addAction(nextAction);
    collectMenu->addAction(collectAction);
    collectMenu->addAction(clearAction);
    collectMenu->exec(m_listWisget3->mapToGlobal(pos));
    delete collectMenu;
    collectMenu = nullptr;
}

//历史列表右键菜单
void MultipPlayer::slot_createRight_playHistoryTable(const QPoint &pos)
{
    if(m_listWisget4->count() == 0) return;
    QMenu *historytMenu = new QMenu(m_listWisget4);
    historytMenu->setObjectName(QString::fromLocal8Bit("playlist_historytMenu"));
    QAction *playAction = new QAction(QIcon(""),QString::fromLocal8Bit("播放"));
    QAction *deleteAction = new QAction(QIcon(""),QString::fromLocal8Bit("删除"));
    QAction *clearAction = new QAction(QIcon(""),QString::fromLocal8Bit("清空列表"));
//    int row = m_listWisget4->currentRow();//当前选中的行号，注意-1和向后传递的情况
    //播放
    connect(playAction,&QAction::triggered,[=](){slot_playCurrentListItem(m_listWisget4,m_listWisget4->currentRow());});
    //删除
    connect(deleteAction,&QAction::triggered,[=](){slot_deleteListRecord(m_listWisget4,m_listWisget4->currentRow());});
    //清空列表
    connect(clearAction,&QAction::triggered,[=](){slot_clearListAllRecords(m_listWisget4);});
    historytMenu->addAction(deleteAction);
    historytMenu->addAction(clearAction);
    historytMenu->exec(m_listWisget4->mapToGlobal(pos));
    delete historytMenu;
    historytMenu = nullptr;
}

//清空列表
void MultipPlayer::slot_clearListAllRecords(QListWidget *obj)
{
    if(obj->count() == 0) return;
    if(obj->objectName() == "m_listWisget2")
    {
        obj->clear();
    }
    else if(obj->objectName() == "m_listWisget3")
    {
        obj->clear();
    }
    else if(obj->objectName() == "m_listWisget4")
    {
        obj->clear();
    }
    else
    {
        return;
    }
}


//多选删除
void MultipPlayer::slot_deleteListRecords(QListWidget *obj, int start, int end)
{
    if(end - start < 0) return;
    if(obj->objectName() == "m_listWisget2")//播放列表
    {
        for(int i = start; i<end; i++)
        {
            QListWidgetItem *item =  obj->takeItem(i);
            delete item;
        }

        playlist->removeMedia(start,end);
    }
    else if(obj->objectName() == "m_listWisget3")//收藏列表
    {

    }
    else if(obj->objectName() == "m_listWisget4")//历史列表
    {

    }
    else
    {
        return;
    }
}

//删除某条记录
void MultipPlayer::slot_deleteListRecord(QListWidget *obj, int index)
{
    if(index == -1) return;
    qDebug() << QString::fromLocal8Bit("当操作列表：") << obj->objectName() << QString::fromLocal8Bit("当操作索引：") << index;
    if(obj->objectName() == "m_listWisget2")//播放列表
    {
        QListWidgetItem *item =  obj->takeItem(index);
        delete item;
        m_mapList2.remove(index);
        playlist->removeMedia(index);
    }
    else if(obj->objectName() == "m_listWisget3")//收藏列表
    {
        QListWidgetItem *item =  obj->takeItem(index);
        delete item;
        m_mapList_collect.remove(index);
    }
    else if(obj->objectName() == "m_listWisget4")//历史列表
    {
        QListWidgetItem *item =  obj->takeItem(index);
        delete item;
        m_mapList_history.remove(index);
    }
    else
    {
        return;
    }
}

//批量添加
void MultipPlayer::slot_addListRecordItems(QListWidget *obj)
{
    if(obj->objectName() == "m_listWisget2")
    {

    }
    else
    {
        return;
    }
}

//单个添加
void MultipPlayer::slot_addListRecordItem(QListWidget *obj)
{
    if(obj->objectName() == "m_listWisget2")
    {

    }
    else if(obj->objectName() == "m_listWisget3")
    {

    }
    else
    {
        return;
    }
}

//播放选中的某条记录
void MultipPlayer::slot_playCurrentListItem(QListWidget *obj, int index)
{
    if(index == -1) return;//-1非法值
    if(obj->objectName() == "m_listWisget2")//判断为播放列表
    {
        playlist->setCurrentIndex(index);
        player->play();
    }
    else if(obj->objectName() == "m_listWisget3")//判断为收藏列表
    {

    }
    else
    {
        return;
    }
}

//播放选中的某条记录的下一条
void MultipPlayer::slot_playNextListItem(QListWidget *obj, int index)
{
    if(index == -1) return;//-1非法值
    if(obj->objectName() == "m_listWisget2")
    {
        playlist->setCurrentIndex(index+1);
        player->play();
    }
    else if(obj->objectName() == "m_listWisget3")
    {

    }
    else
    {
        return;
    }
}

//下载选中的某条记录
void MultipPlayer::slot_downloadListItem(QListWidget *obj, int index)
{
    if(index == -1) return;//-1非法值
    if(obj->objectName() == "m_listWisget2")
    {

    }
    else if(obj->objectName() == "m_listWisget3")
    {

    }
    else
    {
        return;
    }
}

//收藏选中的某条记录
void MultipPlayer::slot_collectListItem(QListWidget *obj, QString text)
{
    if(text == -1) return;//-1非法值
    if(obj->objectName() == "m_listWisget2")
    {
        addCurrentMediaToList_Collect(obj);
    }
    else if(obj->objectName() == "m_listWisget3")
    {
        addCurrentMediaToList_Collect(obj,text);
    }
    else
    {
        return;
    }
}

//全选
void MultipPlayer::slot_selectAllListItem(QListWidget *obj)
{
    if(obj->count() == 0 ) return;
    if(obj->objectName() == "m_listWisget2")
    {
        if(m_selectAllStatus1)
        {
            for(int i = 0; i < obj->count(); i++)
            {
                obj->item(i)->setFlags(Qt::NoItemFlags);
            }
        }
        else
        {
            for(int i = 0; i < obj->count(); i++)
            {
                obj->item(i)->setCheckState(Qt::Checked);//Checked
            }
        }
        m_selectAllStatus1 = !m_selectAllStatus1;
    }
    else if(obj->objectName() == "m_listWisget3")
    {
        if(m_selectAllStatus2)
        {
            for(int i = 0; i < obj->count(); i++)
            {
                obj->item(i)->setFlags(Qt::NoItemFlags);
            }
        }
        else
        {
            for(int i = 0; i < obj->count(); i++)
            {
                obj->item(i)->setCheckState(Qt::Checked);//Checked
            }
        }
        m_selectAllStatus2 = !m_selectAllStatus2;
    }
    else
    {
        return;
    }
}


//bool MultipPlayer::findCollectList()
//{
//    if(m_mapList_collect.isEmpty())
//        return false;
//    for(QMap<int,QString>::iterator iter = m_mapList_collect.begin(); iter != m_mapList_collect.end(); ++iter)
//    {
//        if(iter.value() == m_curMediaName)
//        {
//            return true;//有
//        }
//        else
//        {
//            return false;//没找到
//        }
//    }
//}


void MultipPlayer::closeCurrentWindow()
{
    player->stop();//暂停播放
    playlist->clear();//播放列表清空
    m_mapList.clear();//清空容器
    m_mapList2.clear();//清空容器
    m_mapList_collect.clear();
    m_mapList_history.clear();
    ui->stackedWidget->setCurrentIndex(0);//空白页
//    clearListWidgetList_user();
    clearListWidgetList_playlist();//播放列表清空
    clearListWidgetList_collection();//收藏列表清空
    clearListWidgetList_history();//历史列表清空
    clearUserInputSearchInfo();//登陆列表以往输入的信息清空
    if(VideoProgressBar::getInstance())
    {
        VideoProgressBar::getInstance()->close();
    }
//    this->close();
    emit sig_mainPlayerClose();//主界面处理内存删除
}

//清空用户信息
//void MultipPlayer::clearListWidgetList_user()
//{
//    m_listWisget1->clear();
//}

//清空播放列表
void MultipPlayer::clearListWidgetList_playlist()
{
    m_listWisget2->clear();
}

//清空收藏列表
void MultipPlayer::clearListWidgetList_collection()
{
    m_listWisget3->clear();
}

//清空历史记录
void MultipPlayer::clearListWidgetList_history()
{
    m_listWisget4->clear();
}

//清空用户输入的搜索字
void MultipPlayer::clearUserInputSearchInfo()
{
    m_lineEdit->clear();
}

/*更新箭头的坐标*/
void MultipPlayer::updateFoldButtonGeometry()
{
        m_foldBtn->setGeometry(ui->stackedWidget->width()-m_foldBtn->width()+2,ui->stackedWidget->height()/2-m_foldBtn->height()/2,40,60);//固定的大小
        m_foldBtn->raise();
}

void MultipPlayer::setCurrentMediaName(QString name)
{
    ui->label_media_name->clear();
    int pos  = name.indexOf(".");
    QString filename = name.left(pos);//从pos位置向左侧截取
    ui->label_media_name->setText(filename);
}

/*当前媒体的图片*/
void MultipPlayer::setCurrentMediaNamePicture(const QPixmap &pix)
{
    ui->label_media_pic->setPixmap(pix);
}

void MultipPlayer::setFoldButtonStyle()
{
    /*不隐藏时，箭头向右；隐藏时，箭头向左,默认箭头向右，没有隐藏*/
    if(!m_isHide)
    {
        //需要隐藏
        m_foldBtn->setStyleSheet("QPushButton{background:rgba(81,81,81,0.3) url(:/images/icon/arrow_right.png) no-repeat center center;border:none;}");
    }
    else
    {
        //需要显示
        m_foldBtn->setStyleSheet("QPushButton{background:rgba(81,81,81,0.3) url(:/images/icon/arrow_left.png) no-repeat center center;border:none;}");
    }
}

/*判断右侧停靠栏指示按钮位置*/
void MultipPlayer::judgeFoldBtnOfRightDockList()
{
    if(m_isHide)//点击按钮发现，界面处于隐藏状态
    {
        m_widget1->show();//点击后则显示界面
        updateFoldButtonGeometry();
        setFoldButtonStyle();
        m_foldBtn->hide();
    }
    else//点击按钮发现，界面处于显示状态
    {
        m_widget1->hide();//点击后则隐藏界面
        updateFoldButtonGeometry();
        setFoldButtonStyle();
        m_foldBtn->hide();
    }
    m_isHide = !m_isHide;//状态置反
}


/*左侧列表控制显隐*/
void MultipPlayer::setMainWindowShowFullgreen()
{
    m_videoTitleBar->hide();
    ui->stackedWidget_player->hide();
    m_widget1->hide();
    m_isHide = true;
    chandleRestoreWindow();//相当于双击标题栏效果
}

/*播放次序按钮*/
void MultipPlayer::setPlayOrderButtonStyleSheet(int index)
{
    qDebug() << "current order = " << index;
    if(index == 1)//单曲
    {
        ui->pushButton_playOrder->setStyleSheet("QPushButton{"
                                                "border-image: url(:/images/icon/player_dxunhuan.png);"
                                                "}");
        adjust_playBackMode(0);//模式调节0
    }
    else if(index == 2)//顺序
    {
        ui->pushButton_playOrder->setStyleSheet("QPushButton{"
                                                "border-image: url(:/images/icon/player_shunxu.png);"
                                                "}");
        adjust_playBackMode(3);//模式调节3
    }
    else if(index == 3)//循环
    {
        ui->pushButton_playOrder->setStyleSheet("QPushButton{"
                                                "border-image: url(:/images/icon/player_xunhuan.png);"
                                                "}");
        adjust_playBackMode(1);//模式调节1
    }
    else if(index == 4)//随机
    {
        ui->pushButton_playOrder->setStyleSheet("QPushButton{"
                                                "border-image: url(:/images/icon/player_suiji.png);"
                                                "}");
        adjust_playBackMode(2);//模式调节4
    }
}

void MultipPlayer::setVideTitleBar(int index)
{
    m_videoTitleBar->setTitleStackWidgetPage(index);
}

/*监听事件*/
bool MultipPlayer::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *mousevent = static_cast<QMouseEvent*>(event);
    volumeAdjustShowUi(watched,mousevent);//视频参数调节界面
    playlistMouseEnterLeave(watched,mousevent);//节目列表搜索框
    stackWidgetSliderButtonEventFilter(watched,mousevent);//箭头显示影藏动作
//    videoDouleExit(watched,mousevent);
    return QWidget::eventFilter(watched,event);
}







