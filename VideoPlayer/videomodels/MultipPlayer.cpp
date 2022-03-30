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
#include <QDesktopWidget>
#include <QtSql/QSqlQuery>

MultipPlayer::MultipPlayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MultipPlayer),
    m_winMax(false),
    m_playerState(QMediaPlayer::StoppedState)
{
    ui->setupUi(this);
    this->setMinimumSize(1240,800);//1400,800
    this->setMouseTracking(true);//开启鼠标跟踪，适应捕捉屏幕
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setWindowTitle(QString::fromLocal8Bit("Qt简易视频播放器"));
    //设置监听
    ui->pushButton_sound->installEventFilter(this);//音量调节按钮设置监听
    initMainWindow();//初始化界面
    chandleSignalAndSLots();//处理信号与槽函数
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
           <<QString::fromLocal8Bit("https://v10.dious.cc/20211110/Bx3wAzvZ/index.m3u8")
           <<QString::fromLocal8Bit("https://video.dious.cc/20200803/wr5KWg9J/index.m3u8")
           <<QString::fromLocal8Bit("https://v10.dious.cc/20210919/h1ueTDVx/index.m3u8")
           <<QString::fromLocal8Bit("https://v7.monidai.com/20190706/ZU4NZfxz/index.m3u8")
           <<QString::fromLocal8Bit("https://v2.dious.cc/20200921/9VPsVGWm/index.m3u8")
           <<QString::fromLocal8Bit("https://v7.dious.cc/20210430/UKq6knEQ/index.m3u8")
           <<QString::fromLocal8Bit("https://v4.monidai.com/20200819/k4DLoiaS/index.m3u8")
           <<QString::fromLocal8Bit("https://video.dious.cc/20200617/AKAsLPFR/index.m3u8")
           <<QString::fromLocal8Bit("https://video.dious.cc/20200826/Y7W3mXTb/index.m3u8")
           <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/videos/heikediguo.avi")
           <<QString::fromLocal8Bit("https://s1.monidai.com/20211222/NfoLZcsd/index.m3u8");
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
    delete m_widget2;
    delete m_musicUi;
    delete m_muteDlg;
    delete m_toolBox;
    delete videoWidget;
    delete m_videoBlank;
    delete m_adjustBright;
    delete m_videoTitleBar;
    delete m_musicShowList;
    delete m_systemSetting;
    delete m_hboxlayout_rlist;
}

/*初始化界面*/
void MultipPlayer::initMainWindow()
{
    ui->pushButton_danmu->setCheckable(true);
    m_times = 0;
    m_voice = 10;
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    player->setVolume(10);
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setEnabled(false);
    ui->horizontalSlider->setPageStep(5);
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);
    videoWidget = new MyVideoWidget();
    player->setVideoOutput(videoWidget);

    m_widget1 = new QWidget;//视频显示
    m_widget1->setObjectName(QString::fromUtf8("m_widget1"));

    m_widget2 = new QWidget;//listwidget显示（暂时不用）
    m_widget2->setObjectName(QString::fromUtf8("m_widget2"));

    m_videoBlank = new VideoBlank();
    m_videoBlank->setObjectName(QString::fromLocal8Bit("m_videoBlank"));

    m_musicUi = new MusicPlayShow();
    m_musicUi->setObjectName(QString::fromLocal8Bit("m_musicUi"));

    m_systemSetting = new SystemSetting();
    m_systemSetting->setObjectName(QString::fromLocal8Bit("m_systemSetting"));

    m_videoTitleBar = new VideoTitleBar();
    m_videoTitleBar->setObjectName(QString::fromLocal8Bit("m_videoTitleBar"));

    ui->stackedWidget->insertWidget(0,m_videoBlank);
    m_videoBlank->setHideOpenButton(true);
    ui->stackedWidget->insertWidget(1,videoWidget);
    ui->stackedWidget->insertWidget(2,m_musicUi);
    ui->stackedWidget->setCurrentIndex(0);//默认显示音乐界面

    //用户信息（暂时）
    m_listWisget1 = new QListWidget;
    m_listWisget1->setObjectName(QString::fromUtf8("m_listWisget1"));
    m_listWisget1->setMinimumWidth(260);
    m_listWisget1->setAlternatingRowColors(false);//交替显示

    //播放列表
    m_listWisget2 = new QListWidget;
    m_listWisget2->setObjectName(QString::fromUtf8("m_listWisget2"));
    m_listWisget2->setMinimumWidth(260);
    m_listWisget2->setFocusPolicy(Qt::NoFocus);//作用是点击item去掉虚线边框
    m_listWisget2->setAlternatingRowColors(false);//交替显示

    //我的收藏
    m_listWisget3 = new QListWidget;
    m_listWisget3->setObjectName(QString::fromUtf8("m_listWisget3"));
    m_listWisget3->setMinimumWidth(260);
    m_listWisget3->setAlternatingRowColors(false);//交替显示

    //网络曲库
    m_listWisget4 = new QListWidget;
    m_listWisget4->setObjectName(QString::fromUtf8("m_listWisget4"));
    m_listWisget4->setMinimumWidth(260);
    m_listWisget4->setAlternatingRowColors(false);//交替显示

    m_lineEdit = new QLineEdit;//曲库列表搜索框
    m_lineEdit->setObjectName(QString::fromUtf8("m_lineEdit"));
    m_lineEdit->setMinimumWidth(200);
    m_lineEdit->setFixedHeight(30);
    m_searchBtn = new QPushButton;//曲库列表搜索按钮
    m_searchBtn->setObjectName(QString::fromUtf8("m_searchBtn"));
    m_searchBtn->setFixedSize(33,30);

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
    m_toolBox->setObjectName(QString::fromLatin1("m_toolBox"));
    QIcon icon_user(":/images/icon/user.png");
    QIcon icon_playlist(":/images/icon/playerlist.png");
    QIcon icon_collect(":/images/icon/playercollect.png");
    QIcon icon_internet(":/images/icon/playerinternet.png");
    m_toolBox->addItem(m_listWisget1,icon_user,QString::fromLocal8Bit("用户信息"));
    m_toolBox->addItem(m_widget2,icon_playlist,QString::fromLocal8Bit("播放列表"));
    m_toolBox->addItem(m_listWisget3,icon_collect,QString::fromLocal8Bit("我的收藏"));
    m_toolBox->addItem(m_listWisget4,icon_internet,QString::fromLocal8Bit("播放记录"));
    m_toolBox->layout()->setSpacing(3);//item之间的间距

    m_recomTab = new RecomVideoTab;
    m_recomTab->setObjectName(QString::fromLocal8Bit("m_recomTab"));
    m_recomTab->setFixedWidth(260);
    //节目列表分块
    m_tabWidget1 = new QTabWidget;//不用手动释放，有包含关系
    m_tabWidget1->setObjectName(QString::fromLocal8Bit("m_tabWidget1"));
    m_tabWidget1->setFixedWidth(260);//固定宽度
    m_tabWidget1->insertTab(0,m_toolBox,QString::fromLocal8Bit("播放列表"));
    m_tabWidget1->insertTab(1,m_recomTab,QString::fromLocal8Bit("推荐视频"));
    m_tabWidget1->setCurrentIndex(0);
    m_hboxlayout_rlist = new QHBoxLayout;
    m_hboxlayout_rlist->addWidget(ui->stackedWidget);
    m_hboxlayout_rlist->addWidget(m_tabWidget1);
    m_hboxlayout_rlist->setSpacing(0);
    m_hboxlayout_rlist->setStretch(0,7);
    m_hboxlayout_rlist->setStretch(1,3);

    ui->verticalLayout_5->insertWidget(0,m_videoTitleBar);//标题栏
    ui->verticalLayout_5->insertLayout(1,m_hboxlayout_rlist);
    ui->verticalLayout_5->insertWidget(2,ui->widget_splider);
    ui->verticalLayout_5->insertWidget(3,ui->stackedWidget_player);
    ui->verticalLayout_5->setSpacing(0);
    ui->verticalLayout_5->setStretch(0,1);
    ui->verticalLayout_5->setStretch(1,7);
    ui->verticalLayout_5->setStretch(2,1);
    ui->verticalLayout_5->setStretch(3,1);
    loadDefaultLogo();//加载默认图标
    this->centralWidget()->setLayout(ui->verticalLayout_2);


    m_pTimer  = new QTimer(this);
    m_pTimer2 = new QTimer(this);
    m_pTimer2->setSingleShot(true);//只执行一次定时器
    m_pTimer->start(1000);

    m_muteDlg = new muteDialog();//不加this
    m_muteDlg->setHidden(true);
}

/*处理信号与槽函数*/
void MultipPlayer::chandleSignalAndSLots()
{
    //应该在有影片播放的时候，执行定时器，否则就是无效；1s更新一次进度
    connect(m_pTimer,&QTimer::timeout,this,&MultipPlayer::on_time);
    //监测媒体播放状态 StoppedState PlayingState PausedState
    connect(player,&QMediaPlayer::stateChanged,this,&MultipPlayer::checkChandleMediaPlayerStatus);
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
    connect(ui->pushButton_sound,&QPushButton::clicked,[=]()
    {
        if(m_muteDlg)
        {
            if(m_muteDlg->isHidden())
            {
                int x = ui->pushButton_sound->parentWidget()->mapToGlobal(ui->pushButton_sound->pos()).x();
                int y = ui->pushButton_sound->parentWidget()->mapToGlobal(ui->pushButton_sound->pos()).y();
                int h = m_muteDlg->height();
                m_muteDlg->setGeometry(x-6,y-h-6,m_muteDlg->width(),m_muteDlg->height());
                m_muteDlg->raise();
                m_muteDlg->show();
            }
            else
            {
                m_muteDlg->hide();
            }
        }
    });

    /*音量值调节显示数值*/
    connect(m_muteDlg,&muteDialog::sig_SpliderValueChange,[=](int value){
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

    //右侧播放列表显示,[=]代表以传值的方式捕获当前所有能捕获的数据对象
    connect(ui->pushButton_curlist,&QPushButton::clicked,[=]()
    {
        if(m_tabWidget1->isHidden())
        {
            m_tabWidget1->show();
        }
        else
        {
            m_tabWidget1->hide();
        }
    });

    /*跟随列表选择播放对应文件,将鼠标单击播放该为双击*/
    connect(m_listWisget2,&QListWidget::itemDoubleClicked,[=](QListWidgetItem *item)
    {
        int row = m_listWisget2->row(item);
        m_playerState = QMediaPlayer::PlayingState;
        ui->pushButton_pauseStart->setIcon(QIcon(":/images/icon/pausehover.png"));//播放
        playlist->setCurrentIndex(row);
        fileType(row);
        player->play();
    });

    //标题栏显示当前播放文件名
    connect(this,SIGNAL(sig_sendSwitchToMusicPage(QString)),m_videoTitleBar,SLOT(setTitleText(QString)));
    //窗口关闭按钮
    connect(m_videoTitleBar,&VideoTitleBar::sig_winVClose,[=]()
    {
        closeCurrentWindow();
    });

    //窗口最小化按钮
    connect(m_videoTitleBar,&VideoTitleBar::sig_winVMinimum,this,&MultipPlayer::showMinimized);

    //窗口还原按钮
    connect(this,SIGNAL(sig_winVStatus(bool)),m_videoTitleBar,SLOT(chandleVMainWinStatus(bool)));
    connect(m_videoTitleBar,&VideoTitleBar::sig_winVRestore,[=]()
    {
        if(!m_winMax)//非最大化
        {
            this->showMaximized();
            emit sig_winVStatus(m_winMax);
        }
        else
        {
            this->showNormal();
            emit sig_winVStatus(m_winMax);
        }
        m_winMax = !m_winMax;
    });

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
        fileType(index);
        m_listWisget2->setCurrentRow(index);
        //          ui->playerListWidget->setCurrentRow(index);
        loadFileInfoToWinTitle(index);
        updateRateTypeUiLayout(index);
    });

    /*浮动窗口-曲库歌曲搜索*/
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
    //调节播放模式
    connect(m_adjustBright,SIGNAL(valueChange_playBackMode(int)),this,SLOT(adjust_playBackMode(int)));
    //调节屏幕占比
    connect(m_adjustBright,SIGNAL(valueChange_aspectRatio(int)),this,SLOT(adjust_aspectRatioMode(int)));
    connect(m_adjustBright,SIGNAL(valueChange_liangdu(int)),videoWidget,SLOT(setBrightness(int)));
    connect(m_adjustBright,SIGNAL(valueChange_duibidu(int)),videoWidget,SLOT(setContrast(int)));
    connect(m_adjustBright,SIGNAL(valueChange_baohedu(int)),videoWidget,SLOT(setSaturation(int)));
    connect(m_adjustBright,SIGNAL(valueChange_sediao(int)),videoWidget,SLOT(setHue(int)));

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
//        QFileInfo info(newurl);
        QUrl url = QUrl::fromLocalFile(newurl);
        player->setMedia(url);
        player->play();
    });
}

/*加载默认图标*/
void MultipPlayer::loadDefaultLogo()
{
    ui->pushButton_curlist->setToolTip(QString::fromLocal8Bit("当前列表"));
    m_lineEdit->setPlaceholderText(QString::fromLocal8Bit("输入要搜索的内容^_^"));
    m_lineEdit->setEnabled(false);

    m_searchBtn->setText(QString::fromLocal8Bit(""));
    m_searchBtn->setToolTip(QString::fromLocal8Bit("打开文件"));

    ui->pushButton_sound->setIcon(QIcon(":/images/icon/yingling.png"));//图标是正常音量
    ui->pushButton_sound->setIconSize(QSize(26,26));//以后所有显示图片都是此大小
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

void MultipPlayer::set_fileTolistWidget(QString item)
{
    QListWidgetItem *pitem = new QListWidgetItem(item);
    pitem->setTextAlignment(Qt::AlignLeft);//item文字向左对齐
    m_listWisget2->addItem(pitem);
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
//        QString name = path.split("/").last();//文件名称,此法也可行
        m_mapList.insert(i,path);
        m_mapList2.insert(i,name);
        emit sig_sendToMusicList();//通知音乐列表可以加载信息了

        QIcon btnIcon1(":/images/icon/video.png");//视频
        QIcon btnIcon2(":/images/icon/mp3.png");//音乐

        QListWidgetItem *pItem = nullptr;

        //判断一下文件类型，加载不同图标
        if(fileSuffix == "mp4")//返回的是mp4,而非 .mp4
        {
            pItem = new QListWidgetItem(btnIcon1,QString::fromLocal8Bit("%1.").arg(i+1) + name);
        }
        else if(fileSuffix == "mp3")
        {
            pItem = new QListWidgetItem(btnIcon2,QString::fromLocal8Bit("%1.").arg(i+1) + name);
        }
        else if(fileSuffix == "flv")
        {
            pItem = new QListWidgetItem(btnIcon1,QString::fromLocal8Bit("%1.").arg(i+1) + name);
        }
        else//后面有需要还可以添加文件类型判断
        {
            pItem = new QListWidgetItem(btnIcon1,QString::fromLocal8Bit("%1.").arg(i+1) + name);
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
    m_listWisget2->setCurrentRow(0);
//    ui->playerListWidget->setCurrentRow(0);
    m_toolBox->setCurrentIndex(1);//浮动窗口显示歌曲列表，索引：1

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
        m_fileNames =  QFileDialog::getOpenFileNames(this,
                                                               "Open Files","C:\\Users\\24939\\Desktop",
                                                               "Videos(*avi *mp4 *flv *mp3 *wmv)");

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
            player->play();
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
        m_fileNames =  QFileDialog::getOpenFileNames(this,
                                                   "Open Files","C:\\Users\\24939\\Desktop",
                                                   "Videos(*avi *mp4 *flv *mp3 *wmv)");
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
            addFileToList(m_fileNames);
            fileType(m_fileNames,0);//判断文件类型并作出界面反应
            player->play();
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
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(index == 1)
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {

    }
}

void MultipPlayer::on_frameHidden()
{
    ui->widget_splider->setHidden(true);
//    ui->verticalLayout_5->removeWidget(ui->widget_splider);
}

void MultipPlayer::on_enterShowFrame()
{
    ui->widget_splider->setHidden(false);
    //    ui->verticalLayout_5->insertWidget(2,ui->widget_splider);
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
void MultipPlayer::updateRateTypeUiLayout(int str)
{
    Q_UNUSED(str);
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

//监测处理媒体播放状态
void MultipPlayer::checkChandleMediaPlayerStatus()
{
    if(player->media().isNull())
        return;
    if(player->state() == QMediaPlayer::PausedState)
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::PausedState");
    }
    else if(player->state() == QMediaPlayer::PlayingState)
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::PlayingState");
    }
    else if(player->state() == QMediaPlayer::StoppedState)
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::StoppedState");
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("other state!");
    }
}

//监测处理媒体本身状态，加载完毕，正在加载，缓冲结束，正在缓冲，未知，有效等
void MultipPlayer::checkChandleMediaStatus()
{
    if(player->media().isNull())
        return;
    if(player->mediaStatus() == QMediaPlayer::UnknownMediaStatus)//未知媒体状态
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::UnknownMediaStatus");
    }
    else if(player->mediaStatus() == QMediaPlayer::NoMedia)//无媒体状态
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::NoMedia");
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(player->mediaStatus() == QMediaPlayer::LoadingMedia)//加载媒体中
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::LoadingMedia");
    }
    else if(player->mediaStatus() == QMediaPlayer::LoadedMedia)//媒体加载完毕
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::LoadedMedia");
    }
    else if(player->mediaStatus() == QMediaPlayer::StalledMedia)//媒体停顿
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::StalledMedia");
    }
    else if(player->mediaStatus() == QMediaPlayer::BufferingMedia)//媒体正在缓冲
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::BufferingMedia");
    }
    else if(player->mediaStatus() == QMediaPlayer::BufferedMedia)//媒体缓冲完毕
    {
        qDebug() << QString::fromLocal8Bit("QMediaPlayer::BufferedMedia");
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

/*显示播放器界面*/
void MultipPlayer::showPlayerUi()
{
//    this->showNormal();
//    this->move((QApplication::desktop()->width()-this->width())/2, (QApplication::desktop()->height()-this->height())/2);
//    m_winMax = true;
//    if(this->isHidden() || this->isMinimized())
//    {
//        m_winMax = true;
        this->showMinimized();
//        ui->pushButton_normal->setStyleSheet("QPushButton{"
//                                             "background-color: transparent;"
//                                             "border-image: url(:/images/icon/normal.png);}"
//                                             "QPushButton:hover{"
//                                             "border: 1px solid #3C80B1;"
//                                             "border-image: url(:/images/icon/normalhover.png);}");
        qDebug()<<"show ui to the central";
//    }
}

void MultipPlayer::showPlayerList()
{
//    m_dockWidget->show();
    m_toolBox->show();
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
    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
    if(watched == videoWidget)
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
                    this->move(m_videoPos);
                }
            }
            else if(event->type() == QEvent::MouseButtonDblClick)
            {
                //static_cast:可进行基类与派生类的上下行转换；但是下行转换（基类转到派生类）没有动态类型检查，是不安全的；
                //dynamic_cast:可以进行上下行转换，且下行转换更安全；以及类之间的交叉转换；

                if(m_playerState == QMediaPlayer::PlayingState && mouseEvent->button() == Qt::LeftButton)//左键双击
                {
                    if(videoWidget->isFullScreen())
                    {
                        return false;
                    }
                    else
                    {
                        m_videoPos = this->pos();
                        videoWidget->setWindowFlags(Qt::Window);//设置为顶级窗口
                        videoWidget->showFullScreen();
                    }
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
        qDebug()<<"pushButton_sound enter";
        if(event->type() == QEvent::Enter)
        {
            if(m_muteDlg)
            {
                if(!m_muteDlg->isHidden())
                {
                    m_muteDlg->hide();
                }
                else
                {
                    int x = ui->pushButton_sound->parentWidget()->mapToGlobal(ui->pushButton_sound->pos()).x();
                    int y = ui->pushButton_sound->parentWidget()->mapToGlobal(ui->pushButton_sound->pos()).y();
                    int h = m_muteDlg->height();
                    qDebug() << "QPont_g(" << x << "," << y << ")";
                    m_muteDlg->setGeometry(x-6,y-h-6,m_muteDlg->width(),m_muteDlg->height());
                    m_muteDlg->raise();
                    m_muteDlg->show();
                }
            }
        }
    }
}

/*播放列表界面搜索框鼠标进入离开*/
void MultipPlayer::playlistMouseEnterLeave(QObject *watched, QEvent *event)
{
    if(watched == m_lineEdit || m_searchBtn)//监视器每次只能监视一个对象，这里需要分开写
    {
        /*搜索框，搜索按钮鼠标离开*/
        if(event->type() == QEvent::Leave)
        {
            m_searchBtn->setStyleSheet("QDockWidget QWidget QPushButton"
                                         "{"
                                         "color:#ff5c38;"
                                         "background:rgb(75, 75, 75);"
                                         "border-top-right-radius:0px;"
                                         "border-bottom-right-radius:0px;"
                                         "border-bottom-left-radius:0px;"
                                         "border-top-left-radius:0px;"
                                         "}"
                                         );

            m_lineEdit->setStyleSheet("QDockWidget QWidget QLineEdit"
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
            m_searchBtn->setStyleSheet("QDockWidget QWidget QPushButton"
                                         "{"
                                         "color:white;"
                                         "background-color:#ff5246;"
                                         "border: 1px solid #ff5c38;"
                                         "border-top-right-radius:0px;"
                                         "border-bottom-right-radius:0;px;"
                                         "border-bottom-left-radius:0px;"
                                         "border-top-left-radius:0px;"
                                         "}"
                                         );
            m_lineEdit->setStyleSheet("QDockWidget QWidget QLineEdit"
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

/*系统设置*/
void MultipPlayer::help_stemAboutSetting()
{

}

/*问题帮助*/
void MultipPlayer::help_questionAnswer()
{
    QMessageBox::information(this,QString::fromLocal8Bit("问题帮助"),QString::fromLocal8Bit("为当前系统进行问题帮助。"));
}

/*打开本地文件*/
void MultipPlayer::help_aboutLocalFile()
{
//    QMessageBox::information(this,QString::fromLocal8Bit("本地文件"),QString::fromLocal8Bit("选择本地文件进行播放。"));
     openLocalFile();
     this->show();
}

/*打开门户网站*/
void MultipPlayer::help_openWebSite()
{
//    QMessageBox::information(this,QString::fromLocal8Bit("修复建议"),QString::fromLocal8Bit("为当前系统提供修复建议。"));
    QDesktopServices::openUrl(QUrl(QString("https://v.qq.com/biu/download#Windows")));
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
    qDebug()<<index;
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


void MultipPlayer::on_pushButton_danmu_clicked()
{
    if(!m_danmuStatus)
    {
        ui->lineEdit_danmu->setEnabled(true);
    }
    else
    {
        ui->lineEdit_danmu->setEnabled(false);
    }
    m_danmuStatus = !m_danmuStatus;
}

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
        emit sig_winVStatus(m_winMax);//向窗口发送正常状态信号
    }
    m_winMax = !m_winMax;
}

void MultipPlayer::closeCurrentWindow()
{
    player->stop();//暂停播放
    m_mapList.clear();//清空容器
    m_mapList2.clear();//清空容器
    ui->stackedWidget->setCurrentIndex(0);//空白页
    clearListWidgetList_user();
    clearListWidgetList_playlist();
    clearListWidgetList_collection();
    clearListWidgetList_history();
    clearUserInputSearchInfo();
    this->hide();//隐藏界面

}

//清空用户信息
void MultipPlayer::clearListWidgetList_user()
{
    m_listWisget1->clear();
}

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

/*监听事件*/
bool MultipPlayer::eventFilter(QObject *watched, QEvent *event)
{
//    QMouseEvent *mousevent = static_cast<QMouseEvent*>(event);
//    volumeAdjustShowUi(watched,mousevent);
    return QWidget::eventFilter(watched,event);
}







