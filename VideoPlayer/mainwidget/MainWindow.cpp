//#pragma execution_character_set("utf-8")
#include "MainWindow.h"
#include "ui_MainWindow.h"

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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_winMax(false),
    m_playerState(QMediaPlayer::StoppedState)
{
    ui->setupUi(this);
    this->setMinimumSize(1240,800);//1400,800
//    this->setMaximumSize(1920,1040);
//    showMaximized();
//    setFixedSize(1280,750);//给个固定大小
    setMouseTracking(true);//开启鼠标跟踪，适应捕捉屏幕
    //设置自定义大小鼠标
//    QPixmap pixmap(":/images/cursor.png");
//    QSize size(5,5);
//    pixmap.scaled(5,5,Qt::KeepAspectRatio);
//    QCursor *myCursor = new QCursor(pixmap,0,0);    //-1,-1表示热点位于图片中心
//    this->setCursor(*myCursor);

    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setWindowTitle(QString::fromLocal8Bit("Qt简易视频播放器"));

    ui->Btn_adjust->installEventFilter(this);

    ui->pushButton_danmu->setCheckable(true);

    //LCD数字显示
    ui->lcdNumber->setDigitCount(20);//显示数量（个数）
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setPalette(Qt::red);//显示文字颜色，不怎么生效
    //顶层搜索按钮和搜索框
    ui->lineEditSearch->installEventFilter(this);
    ui->BtnSearch->installEventFilter(this);
    QIcon icon_clear(":/images/clear.png");
    clearAction = new QAction(icon_clear,"");
    clearAction->setObjectName(QString::fromLocal8Bit("clearAction"));
    ui->lineEditSearch->addAction(clearAction, QLineEdit::TrailingPosition);// 右侧显示
    clearAction->setVisible(false);
    connect(clearAction,&QAction::triggered,[=](){ui->lineEditSearch->clear();});
    connect(ui->lineEditSearch,&QLineEdit::textChanged,[=]()
    {
        if(ui->lineEditSearch->text().isEmpty())
        {
            clearAction->setVisible(false);
        }
        else
        {
            clearAction->setVisible(true);
        }

    });

//    ui->comboBoxRate->addItem(QString::fromLocal8Bit("0.5倍速"), QVariant(0.5));
//    ui->comboBoxRate->addItem(QString::fromLocal8Bit("1.0倍速"), QVariant(1.0));
//    ui->comboBoxRate->addItem(QString::fromLocal8Bit("1.5倍速"), QVariant(1.5));
//    ui->comboBoxRate->addItem(QString::fromLocal8Bit("2.0倍速"), QVariant(2.0));
//    ui->comboBoxRate->addItem(QString::fromLocal8Bit("4.0倍速"), QVariant(4.0));
//    ui->comboBoxRate->setCurrentIndex(1);
//    ui->comboBoxRate->setView(new QListView);
//    ui->comboBoxRate->setEnabled(false);
//    connect(ui->comboBoxRate,SIGNAL(currentIndexChanged(int)),this,SLOT(setVideoRate(int)));// 明确指明类型，需注意同名函数的重载

    //加载节目列表
    addFileToPlayList();
    ui->listWidget_playlist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//关闭滚动条可见
    ui->listWidget_playlist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_playlist->setFocusPolicy(Qt::NoFocus);//作用是点击item去掉虚线边框

    //托盘
    QIcon icno(":/images/tray.png");
    m_tray = new QSystemTrayIcon(icno,this);
    m_tray->setToolTip(QString::fromLocal8Bit("播放器"));
    createTrayMenu();//托盘菜单

    m_times = 0;
    m_voice = 10;
    player = new QMediaPlayer;
    playlist = new QMediaPlaylist;
    player->setVolume(10);
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setEnabled(false);
    ui->horizontalSlider->setPageStep(5);

    //QMediaPlaylist::CurrentItemInLoop 单循环
    //QMediaPlaylist::CurrentItemOnce   播放一次
    //QMediaPlaylist::Sequential        顺序播放
    //QMediaPlaylist::Loop              列表循环
    //QMediaPlaylist::Random            随机播放

    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    player->setPlaylist(playlist);
//      playlist->addMedia(QUrl("E:\\QtProjects\\000QtDemo_51ctodemo\\04_20VideosPlayer\\shaonianzhongguoshuo.mp4"));
//      playlist->addMedia(QUrl("E:\\QtProjects\\000QtDemo_51ctodemo\\04_20VideosPlayer\\youshanlian.mp4"));
//      player->setMedia(QUrl::fromLocalFile("E:\\QtProjects\\000QtDemo_51ctodemo\\04_20VideosPlayer\\shaonianzhongguoshuo.mp4"));
//      player->setMedia(QUrl::fromLocalFile("E:\\QtProjects\\000QtDemo_51ctodemo\\04_20VideosPlayer\\youshanlian.mp4"));
      videoWidget = new MyVideoWidget();
//      QVBoxLayout *vLayout = new QVBoxLayout();
//      vLayout->addWidget(videoWidget);//将widget和videoWidget共同设置在一起，相当于中心布局
//      ui->widget->setLayout(vLayout);
//      videoWidget->setStyleSheet("QVideoWidget{background-color:black;}");
//      QPalette* palette = new QPalette();
//      palette->setBrush(QPalette::Background, Qt::black);
//      videoWidget->setPalette(*palette);
//      videoWidget->setAutoFillBackground(true);
//      delete palette;

//      videoWidget->installEventFilter(this);//这句话很关键,装了过滤器按ESC键成才有效果，注意布局对过滤器影响
//      ui->pushButton_1->installEventFilter(this);
      player->setVideoOutput(videoWidget);
      widget1 = new QWidget;//视频显示
      widget1->setObjectName(QString::fromUtf8("widget1"));
      widget2 = new QWidget;//listwidget显示（暂时不用）
      widget2->setObjectName(QString::fromUtf8("widget2"));

      m_cusWebBrowser = new CusWebBrowser(ui->stackedWidget);
      m_cusWebBrowser->setObjectName(QString::fromLocal8Bit("m_cusWebBrowser"));

      m_cusTabWidget = new CusTabWidget(ui->stackedWidget);
      m_cusTabWidget->setObjectName(QString::fromLocal8Bit("m_cusTabWidget"));

      m_cusVideoWidget = new CusVideoWidget(ui->stackedWidget);
      m_cusVideoWidget->setObjectName(QString::fromLocal8Bit("m_cusVideoWidget"));

      m_musicUi = new MusicPlayShow(ui->stackedWidget);
      m_musicUi->setObjectName(QString::fromLocal8Bit("m_musicUi"));

      m_musicShowList = new MusicPlaylist(ui->stackedWidget);
      m_musicShowList->setObjectName(QString::fromLocal8Bit("m_musicShowList"));

      m_systemSetting = new SystemSetting();
      m_systemSetting->setObjectName(QString::fromLocal8Bit("m_systemSetting"));

      ui->stackedWidget->insertWidget(0,m_cusTabWidget);//自定义1
      ui->stackedWidget->insertWidget(1,m_cusVideoWidget);//自定义2
      ui->stackedWidget->insertWidget(2,videoWidget);//视频
      ui->stackedWidget->insertWidget(3,m_musicUi);//音乐歌词显示
      ui->stackedWidget->insertWidget(4,m_musicShowList);//音乐列表显示
      ui->stackedWidget->insertWidget(5,m_cusWebBrowser);//浏览器
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
      m_searchBtn->setFixedWidth(60);
      m_searchBtn->setFixedHeight(30);

      m_hLayout = new QHBoxLayout;
      m_hLayout->insertWidget(0,m_lineEdit);
      m_hLayout->insertWidget(1,m_searchBtn);
      m_hLayout->setSpacing(0);
      m_hLayout->setStretch(0,4);
      m_hLayout->setStretch(1,1);


      m_vHlayout = new QVBoxLayout;
      m_vHlayout->insertLayout(0,m_hLayout);
      m_vHlayout->insertWidget(1,m_listWisget2);
      m_vHlayout->setStretch(0,1);
      m_vHlayout->setStretch(1,4);
      m_vHlayout->setSpacing(0);
      m_vHlayout->setContentsMargins(0,0,0,0);

      widget2->setLayout(m_vHlayout);

      //添加抽屉
      m_toolBox = new QToolBox;
      m_toolBox->setFixedWidth(260);
      m_toolBox->setObjectName(QString::fromLatin1("m_toolBox"));
      QIcon icon_user(":/images/user.png");
      QIcon icon_playlist(":/images/playerlist.png");
      QIcon icon_collect(":/images/playercollect.png");
      QIcon icon_internet(":/images/playerinternet.png");
      m_toolBox->addItem(m_listWisget1,icon_user,QString::fromLocal8Bit("用户信息"));
      m_toolBox->addItem(widget2,icon_playlist,QString::fromLocal8Bit("播放列表"));
      m_toolBox->addItem(m_listWisget3,icon_collect,QString::fromLocal8Bit("我的收藏"));
      m_toolBox->addItem(m_listWisget4,icon_internet,QString::fromLocal8Bit("网络曲库"));
      m_toolBox->layout()->setSpacing(3);//item之间的间距

//      widget2->setFixedSize(175,750);//影响m_listwidget垂直显示
//      m_dockWidget = new QDockWidget;
//      m_dockWidget->setObjectName(QString::fromUtf8("m_dockWidget"));
//      m_dockWidget->setWindowTitle(QString::fromLocal8Bit("曲库列表"));
//      m_dockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);//所有此控件的操作都支持
//      m_dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);//指定可以停靠区域
//      m_dockWidget->setWidget(widget2);
//      m_dockWidget->setWidget(m_toolBox);
//      m_dockWidget->setMinimumWidth(260);
//      m_dockWidget->setContentsMargins(0,0,0,0);//左 上 右 下
//      m_dockWidget->hide();
//      addDockWidget(Qt::LeftDockWidgetArea, m_dockWidget);//指定加载默认停靠区域
      hboxlayout_rlist = new QHBoxLayout;
      hboxlayout_rlist->addWidget(ui->stackedWidget);
      hboxlayout_rlist->addWidget(m_toolBox);
      hboxlayout_rlist->setSpacing(0);
      hboxlayout_rlist->setStretch(0,7);
      hboxlayout_rlist->setStretch(1,3);
      m_toolBox->setHidden(true);

      ui->verticalLayout_5->insertWidget(0,ui->widget_title);
      ui->verticalLayout_5->insertLayout(1,hboxlayout_rlist);
//      ui->verticalLayout_5->insertWidget(1,ui->stackedWidget);//刚开始显示的是ui->stackedWidget,resize之后，videowidget在widget上显示
      ui->verticalLayout_5->insertWidget(2,ui->widget_splider);
      ui->verticalLayout_5->insertWidget(3,ui->widget_player);
      ui->verticalLayout_5->setSpacing(0);
      ui->verticalLayout_5->setStretch(0,1);
      ui->verticalLayout_5->setStretch(1,7);
      ui->verticalLayout_5->setStretch(2,1);
      ui->verticalLayout_5->setStretch(3,1);

      getAndShowCurTime();//获取当前系统时间并显示
      loadDefaultLogo();//加载默认图标
      loadAllUIQss();//加载界面样式
      this->centralWidget()->setLayout(ui->horizontalLayout_5);

//      playlist->setCurrentIndex(1);
//      player->play();

/***********************************信号与槽函数**********************************/
      //音量滑条
//      ui->horizontalSlider_vol->setRange(0,100);
//      ui->horizontalSlider_vol->setPageStep(5);
//      ui->horizontalSlider_vol->setValue(10);
//      ui->label_vol->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//      ui->label_vol->setText(QString::fromLocal8Bit("10%"));
      //值改变发出带参数信号
//      connect(ui->horizontalSlider_vol,&QSlider::valueChanged,[=](int val){
//          player->setVolume(val);
//      ui->label_vol->setText(QString::number(val)+QString::fromLocal8Bit("%"));
//      });

      m_pExitDlg = new ExitDialog();
      //收到关闭主窗口信号
      connect(m_pExitDlg,&ExitDialog::sig_SendcloseMain,[=](){
          m_isClose = true;
      });

      //收到不关闭主窗口信号
      connect(m_pExitDlg,&ExitDialog::sig_SendNotcloseMain,[=](){
          m_isClose = false;
      });

      //窗口关闭按钮
      connect(ui->pushButton_close,SIGNAL(clicked()),this,SLOT(close()));


      //窗口最小化按钮
      connect(ui->pushButton_min,SIGNAL(clicked()),this,SLOT(showMinimized()));

      //窗口还原按钮
      connect(ui->pushButton_normal,&QPushButton::clicked,[=]()
      {
          if(!m_winMax)//非最大化
          {
              qDebug()<<"win not is max";
              this->showMaximized();
              ui->pushButton_normal->setStyleSheet("QPushButton{"
                                                   "background-color: transparent;"
                                                   "border-image: url(:/images/normal.png);}"
                                                   "QPushButton:hover{"
                                                   "border: 1px solid #3C80B1;"
                                                   "border-image: url(:/images/normalhover.png);}");

          }
          else
          {


              qDebug()<<"win is max";
              this->showNormal();
              ui->pushButton_normal->setStyleSheet("QPushButton{"
                                                   "background-color: transparent;"
                                                   "border-image: url(:/images/normalmax.png);}"
                                                   "QPushButton:hover{"
                                                   "border: 1px solid #3C80B1;"
                                                   "border-image: url(:/images/normalmaxhover.png);}");
          }
          m_winMax = !m_winMax;

      });


      m_pTimer = new QTimer(this);
      m_pTimer2 = new QTimer(this);
      m_pTimer2->setSingleShot(true);//只执行一次定时器
      m_pTimer->start(1000);

      //应该在有影片播放的时候，执行定时器，否则就是无效；1s更新一次进度
      connect(m_pTimer,&QTimer::timeout,this,&MainWindow::on_time);
      connect(player,&QMediaPlayer::durationChanged,[=](int dura){
          Q_UNUSED(dura);
          m_times = player->duration()/1000;//持续时间,毫秒为单位，转化为秒为单位
          ui->horizontalSlider->setRange(0,m_times);
      });

      m_pTimer3 = new QTimer(this);
      connect(m_pTimer3,&QTimer::timeout,[=](){getAndShowCurTime();});
      m_pTimer3->start(100);//0.1s更新发送一次时间,放在下面合适

//      connect(videoWidget,&MyVideoWidget::mouseEnter,[=](){on_enterShowFrame();});
//      connect(videoWidget,&MyVideoWidget::mouseLeave,[=](){on_frameHidden();});

      //信号
      //void valueChanged(int value);
      //void sliderPressed();
      //void sliderMoved(int position);
      //void sliderReleased();

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

      /*值改变*/
//      connect(ui->horizontalSlider,&QSlider::valueChanged,[=](int pos){
//         player->setPosition(pos*1000);
//      });

        m_muteDlg = new muteDialog(this);
        m_muteDlg->setHidden(true);
        connect(ui->pushButton_1,&QPushButton::clicked,[=]()
        {
            if(m_muteDlg)
            {
                if(m_muteDlg->isHidden())
                {
                    //这是全局坐标
                    QPoint mutePos = QPoint(QCursor::pos().x()-20,QCursor::pos().y()-190);
                    qDebug()<<"mutePos = "<<mutePos;
                    m_muteDlg->move(mutePos);
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
             ui->pushButton_1->setIcon(QIcon(":/images/yingling.png"));
         }
         else
         {
             qDebug() << "value == 0";
             ui->pushButton_1->setIcon(QIcon(":/images/jingyin.png"));
         }
      });

      //右侧播放列表显示,[=]代表以传值的方式捕获当前所有能捕获的数据对象
      connect(ui->pushButton_curlist,&QPushButton::clicked,[=]()
      {
          if(m_toolBox->isHidden())
          {
              m_toolBox->show();
          }
          else
          {
              m_toolBox->hide();
          }
      });

      /*跟随列表选择播放对应文件,将鼠标单击播放该为双击*/
      connect(m_listWisget2,&QListWidget::itemDoubleClicked,[=](QListWidgetItem *item)
      {
          int row = m_listWisget2->row(item);
//          qDebug()<<"current row = "<<row;
//          ui->playerListWidget->setCurrentRow(row);
          m_playerState = QMediaPlayer::PlayingState;
          ui->pushButton_4->setIcon(QIcon(":/images/pausehover.png"));//播放
          playlist->setCurrentIndex(row);
          fileType(row);
          player->play();
//          loadFileInfoToWinTitle(row);
      });

      /*当前播放列表双击改变项*/
//      connect(ui->playerListWidget,&QListWidget::itemDoubleClicked,[=](QListWidgetItem *item)
//      {
//          int row = ui->playerListWidget->row(item);
//          m_listWisget2->setCurrentRow(row);
//          m_playerState = QMediaPlayer::PlayingState;
//          ui->pushButton_4->setIcon(QIcon(":/images/pausehover.png"));//播放
//          playlist->setCurrentIndex(row);
//          fileType(row);
//          player->play();
//      });

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

      //点击节目列表转换页面
      connect(ui->listWidget_playlist,&QListWidget::itemClicked,[=](QListWidgetItem *item)
      {
          int row = ui->listWidget_playlist->row(item);
          switchListPage(row);
      });

      //帮助
      connect(ui->Btnhelp,&QPushButton::clicked,[=](){createHelpMenu();});

      //向音乐界面发送名字,带参数 QString name,注意跨线程的问题,QTimer类不是线程安全的类型，注意第五个参数问题
      connect(this,SIGNAL(sig_sendSwitchToMusicPage(QString)),m_musicUi,SLOT(receiveMainWinData(QString)));

      m_login = new Login(this);//不带this界面显示不出来，空白；问题是界面出现定位不准确
      m_login->setObjectName(QString::fromLocal8Bit("m_login"));
      ui->Btnlogin->installEventFilter(this);
      m_login->setHidden(true);//界面运行起来弹出界面bug
     connect(ui->Btnlogin,SIGNAL(clicked(bool)),this,SLOT(set_adjustLogin()));
      //通知关闭程序
      connect(this,&MainWindow::sig_startCloseAppliction,m_login,&Login::receiveMainWinCloseAppSignal);

      //通知播放列表加载信息
      connect(this,&MainWindow::sig_sendToMusicList,m_musicShowList,&MusicPlaylist::addFileInfoToListView);
      //播放列表界面传来播放歌曲的信息
      connect(m_musicShowList,&MusicPlaylist::sig_selectRowIndex,[=](QModelIndex index)
      {
          QString name_song = index.data().toString();
          qDebug()<<name_song;
      });

      //历史记录
      connect(ui->BtnHistory,&QPushButton::clicked,[=]()
      {
          ui->stackedWidget->setCurrentIndex(4);
      });

      //调用截图程序
      connect(ui->BtnScreen,&QPushButton::clicked,[=]()
      {
          showCaptureScreen();
      });

      connect(ui->Btn_adjust,&QPushButton::clicked,[=](){set_adjustBright();});

      //调节列表发来的信号处理
      m_adjustBright = new AdjustBright(this);//必须先new出来，再使用，否则无用
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
//      connect(m_adjustBright,&AdjustBright::valueChange_liangdu,[=](int value)
//      {
//          qDebug()<<"received:valueChange_liangdu ="<<value;
//      });

      connect(m_adjustBright,SIGNAL(valueChange_liangdu(int)),videoWidget,SLOT(setBrightness(int)));
      connect(m_adjustBright,SIGNAL(valueChange_duibidu(int)),videoWidget,SLOT(setContrast(int)));
      connect(m_adjustBright,SIGNAL(valueChange_baohedu(int)),videoWidget,SLOT(setSaturation(int)));
      connect(m_adjustBright,SIGNAL(valueChange_sediao(int)),videoWidget,SLOT(setHue(int)));

      //腾讯主页
      connect(ui->Btn_logo,&QPushButton::clicked,[=]()
      {
//          QMessageBox::information(this,"home page","there is show tencent home page!");
          QDesktopServices::openUrl(QUrl(QString("https://v.qq.com/")));//下载页面
      });

      //控制节目列表显示影藏
      connect(ui->Btn_eyes,&QPushButton::clicked,this,&MainWindow::showJieMuListWidget);

/***********************************信号与槽函数******************************************/

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

MainWindow::~MainWindow()
{
    //没有指定父亲的需要手动释放
    //有父级对象的，系统自动释放
    delete ui;
    delete clearAction;
    delete m_tray;
    delete player;
    delete playlist;
    delete videoWidget;
    delete widget1;
    delete widget2;
    delete m_cusTabWidget;
    delete m_cusVideoWidget;
    delete m_musicUi;
    delete m_listWisget1;
    delete m_listWisget3;
    delete m_listWisget4;
    delete m_toolBox;
//    delete m_dockWidget;
    delete m_pExitDlg;
    delete m_pTimer;
    delete m_pTimer2;
    delete m_pTimer3;
    delete m_muteDlg;
    delete m_login;
//    delete m_cusWebBrowser;
}

/*加载默认图标*/
void MainWindow::loadDefaultLogo()
{

//    widget1->setStyleSheet("border-image:url(:/images/background.png)");
//    ui->pushButton_close->setIcon(QIcon(":/images/close2.png"));
//    ui->pushButton_close->setIconSize(QSize(30,30));
    ui->pushButton_curlist->setToolTip(QString::fromLocal8Bit("显示列表"));

    m_lineEdit->setPlaceholderText(QString::fromLocal8Bit("输入点内容吧^_^"));
    m_lineEdit->setEnabled(false);
    m_searchBtn->setText(QString::fromLocal8Bit("搜索"));
    ui->pushButton_close->setFlat(true);

    ui->moreBtn->setIcon(QIcon(":/images/allexpand.png"));
    ui->moreBtn->setText(QString::fromLocal8Bit("展开全部"));
//    ui->moreBtn->setFlat(true);


//    ui->pushButton_min->setIcon(QIcon(":/images/min.png"));
//    ui->pushButton_min->setIconSize(QSize(33,26));
    ui->pushButton_min->setFlat(true);

    ui->pushButton_1->setIcon(QIcon(":/images/yingling.png"));//图标是正常音量
    ui->pushButton_1->setIconSize(QSize(26,26));//以后所有显示图片都是此大小
    ui->pushButton_1->setFlat(true);

    ui->pushButton_5->setIcon(QIcon(":/images/openhover.png"));//打开
    ui->pushButton_5->setFlat(true);
    ui->pushButton_5->setIconSize(QSize(50,50));
    ui->pushButton_5->setToolTip(QString::fromLocal8Bit("添加文件"));

    ui->pushButton_4->setIcon(QIcon(":/images/playhover.png"));//播放
    ui->pushButton_4->setFlat(true);
    ui->pushButton_4->setIconSize(QSize(50,50));
    ui->pushButton_4->setToolTip(QString::fromLocal8Bit("播放"));

    ui->pushButton_2->setIcon(QIcon(":/images/stophover.png"));//停止
    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setIconSize(QSize(50,50));
    ui->pushButton_2->setToolTip(QString::fromLocal8Bit("停止"));

    ui->pushButton_6->setIcon(QIcon(":/images/fullscr.png"));//全屏
    ui->pushButton_6->setFlat(true);
    ui->pushButton_6->setIconSize(QSize(50,50));
    ui->pushButton_6->setToolTip(QString::fromLocal8Bit("播放新文件"));

    ui->pushButton_7->setIcon(QIcon(":/images/previoushover.png"));//上一首
    ui->pushButton_7->setFlat(true);
    ui->pushButton_7->setIconSize(QSize(50,50));
    ui->pushButton_7->setToolTip(QString::fromLocal8Bit("上一个"));

    ui->pushButton_8->setIcon(QIcon(":/images/nexthover.png"));//下一首
    ui->pushButton_8->setFlat(true);
    ui->pushButton_8->setIconSize(QSize(50,50));
    ui->pushButton_8->setToolTip(QString::fromLocal8Bit("下一个"));

    ui->Btn_logo->setToolTip(QString::fromLocal8Bit("转至网页"));
    ui->Btnhelp->setToolTip(QString::fromLocal8Bit("帮助"));
    ui->Btnlogin->setToolTip(QString::fromLocal8Bit("登录"));
    ui->Btnskin->setToolTip(QString::fromLocal8Bit("皮肤"));
    ui->BtnDownload->setToolTip(QString::fromLocal8Bit("云端"));
    ui->BtnHistory->setToolTip(QString::fromLocal8Bit("历史记录"));
    ui->BtnScreen->setToolTip(QString::fromLocal8Bit("截屏"));

//    ui->label_time->setText(QString::fromLocal8Bit("00:00:00/00:00:00"));//计时器只要程序已启动，就一直再更新

    m_tray->show();
//    QPalette* palette = new QPalette();
//    palette->setBrush(QPalette::Background, Qt::black);
//    videoWidget->setPalette(*palette);
//    videoWidget->setAutoFillBackground(true);
    //    delete palette;
}

/*加载所有界面样式表*/
void MainWindow::loadAllUIQss()
{
    QFile file(":/style/alluistyle.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    if(!file.isOpen())
    {
        qDebug()<<"the style qss is unload!";
        return;
    }
    else
    {
        QString style = tr(file.readAll());
        qApp->setStyleSheet(style);
        qDebug()<<"the style is load successfull!";
    }
    file.close();
}

/*添加进播放列表*/
void MainWindow::addToPlaylist(const QStringList &fileNames)
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

/*托盘菜单*/
void MainWindow::createTrayMenu()
{
    QMenu *pmenu = new QMenu(this);
    pmenu->setStyleSheet("font-size:12px;"
                         "background-color:#3d3d3d;"
                         "color:green;");//font:bold italic 18px "微软雅黑";
    pmenu->addAction(QString::fromLocal8Bit("显示主界面"),this,SLOT(showPlayerUi()));
    pmenu->addSeparator();
    pmenu->addAction(QString::fromLocal8Bit("显示播放列表"),this,SLOT(showPlayerList()));
    pmenu->addSeparator();
    pmenu->addAction(QString::fromLocal8Bit("上一首"),this,SLOT(on_pushButton_7_clicked()));
    pmenu->addSeparator();
    pmenu->addAction(QString::fromLocal8Bit("下一首"),this,SLOT(on_pushButton_8_clicked()));
    pmenu->addSeparator();
    pmenu->addAction(QString::fromLocal8Bit("暂停/播放"),this,SLOT(on_pushButton_4_clicked()));
    pmenu->addSeparator();
    pmenu->addAction(QString::fromLocal8Bit("退出"),this,SLOT(close()));//注意消息阻塞
    m_tray->setContextMenu(pmenu);
}

/*帮助菜单*/
void MainWindow::createHelpMenu()
{
    QMenu *pmenu2 = new QMenu(this);
    pmenu2->setObjectName(QString::fromLocal8Bit("pmenu2"));//样式表中设置样式必须设置对象名称才能生效
    pmenu2->setStyleSheet("QMenu"
                          "{"
                          "font-size:12px;"
                          "background-color:#3d3d3d;"
                          "color:green;"
//                        "padding:15px 15px;"//调整文字间距
                          "}"
                          "QMenu::item:selected"
                          "{"
                          "color:red;"
                          "}");//font:bold italic 18px "微软雅黑";
    pmenu2->addAction(QString::fromLocal8Bit("系统设置"),this,SLOT(help_stemAboutSetting()));
    pmenu2->addSeparator();
    pmenu2->addAction(QString::fromLocal8Bit("网络资源"),this,SLOT(playHttpRequireRecourse(QString)));
    pmenu2->addSeparator();
    pmenu2->addAction(QString::fromLocal8Bit("问题帮助"),this,SLOT(help_questionAnswer()));
    pmenu2->addSeparator();
    pmenu2->addAction(QString::fromLocal8Bit("本地文件"),this,SLOT(help_aboutLocalFile()));
    pmenu2->addSeparator();
    pmenu2->addAction(QString::fromLocal8Bit("软件下载"),this,SLOT(help_openWebSite()));
    pmenu2->addSeparator();
    pmenu2->addAction(QString::fromLocal8Bit("软件退出"),this,SLOT(close()));
    ui->Btnhelp->setContextMenuPolicy(Qt::CustomContextMenu);
//    ui->Btnhelp->setMenu(pmenu2);
//    pmenu2->show();

    QPoint point4 = QPoint(QCursor::pos().x()-70,QCursor::pos().y()+25);
    pmenu2->exec(point4);
//    pmenu2->exec(QCursor::pos());
    delete pmenu2;
}

/*登录菜单*/
void MainWindow::createLoginMenu()
{

}

/*换肤菜单*/
void MainWindow::createSwitchSkinMenu()
{

}

/*判断文件类型1*/
bool MainWindow::fileType(QStringList &filenames, int index)
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

/*共服务端获取文件列表*/
void MainWindow::get_fileFromServer()
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

void MainWindow::set_fileTolistWidget(QString item)
{
    QListWidgetItem *pitem = new QListWidgetItem(item);
    pitem->setTextAlignment(Qt::AlignLeft);//item文字向左对齐
    m_listWisget2->addItem(pitem);
}



/*判断文件类型2*/
bool MainWindow::fileType(int index)
{
    QString filename = m_mapList2[index];
    bool mp3 = filename.endsWith(QString::fromLocal8Bit(".mp3"),Qt::CaseInsensitive);//判断是否以.mp3结尾，去除大小写敏感
    if(mp3)
    {
        //音乐显示3，音乐界面
        emit sig_sendSwitchToMusicPage(filename);
        ui->stackedWidget->setCurrentIndex(3);
        return true;//这里true代表以.mp3结尾的文件
    }
    else
    {
        //视屏显示4，视屏界面
        emit sig_sendSwitchToMusicPage(filename);
        ui->stackedWidget->setCurrentIndex(2);
        return false;//这里false代表非.mp3结尾的文件，默认为视频文件
    }
}


/*节目列表*/
void MainWindow::addFileToPlayList()
{
    //节目列表
    QStringList strPlayList;
    strPlayList<<QString::fromLocal8Bit("最新视剧")
               <<QString::fromLocal8Bit("热播电影")
               <<QString::fromLocal8Bit("当前视频")
               <<QString::fromLocal8Bit("当前音乐")
               <<QString::fromLocal8Bit("播放列表")
               <<QString::fromLocal8Bit("少儿动漫")
               <<QString::fromLocal8Bit("世界纪录")
               <<QString::fromLocal8Bit("教育课堂")
               <<QString::fromLocal8Bit("游戏直播")
               <<QString::fromLocal8Bit("建党百年")
               <<QString::fromLocal8Bit("王者荣耀")
               <<QString::fromLocal8Bit("健康养生")
               <<QString::fromLocal8Bit("资讯速递")
               <<QString::fromLocal8Bit("生活解密")
               <<QString::fromLocal8Bit("世界地理")
               <<QString::fromLocal8Bit("人文艺术")
               <<QString::fromLocal8Bit("今日影院")
               <<QString::fromLocal8Bit("影视排行")
               <<QString::fromLocal8Bit("最新上架")
               <<QString::fromLocal8Bit("评分最高")
               <<QString::fromLocal8Bit("热门点播")
               <<QString::fromLocal8Bit("明星娱乐");//21项目
    //传统方法
    for(int i = 0;i<strPlayList.size();i++)
    {
        QIcon strIcon = QIcon(QString(":/images/hot%1.png").arg(i));
        QString name = strPlayList.at(i);
        QListWidgetItem *ppItem = new QListWidgetItem(strIcon,name);
        ppItem->setTextAlignment(Qt::AlignVCenter);
//        ppItem->setSizeHint(QSize(150,50));
        ui->listWidget_playlist->addItem(ppItem);
    }

//    QFont font;
//    font.setFamily(QString::fromLocal8Bit("微软雅黑"));
//    font.setBold(true);
//    font.setPointSize(25);
//    font.setWeight(50);
    ui->listWidget_playlist->setIconSize(QSize(50,50));//item的图标的大小
//    ui->listWidget_playlist->setFont(font);


    //自定义方法
/*    for(int i = 0; i < strPlayList.size(); i++)
    {
        QWidget *itemWidget = new QWidget(ui->listWidget_playlist);
        QHBoxLayout *itemContentLayout = new QHBoxLayout;
        QString strIcon = QString(":/images/hot%1.png").arg(i);
        QPixmap icon_list(strIcon);
        QLabel *lblPicture = new QLabel("");
        lblPicture->setPixmap(icon_list);

         QString name = strPlayList.at(i);
        QLabel *lblContent = new QLabel(name);
        itemContentLayout->addWidget(lblPicture,1);//图片控件占1列
        itemContentLayout->addStretch(1);
        itemContentLayout->addWidget(lblContent,4);//文字占4列
//        itemContentLayout->setSpacing(0);
        itemWidget->setLayout(itemContentLayout);
//        qDebug()<<name;
        QListWidgetItem *p_Item = new  QListWidgetItem(ui->listWidget_playlist);
//        p_Item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        p_Item->setSizeHint(QSize(150,50));
        ui->listWidget_playlist->setItemWidget(p_Item,itemWidget);
    }
*/
}

/*文件路径放进容器，将名称显示在列表*/
void MainWindow::addFileToList(const QStringList &strList)
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

        QIcon btnIcon1(":/images/video.png");//视频
        QIcon btnIcon2(":/images/mp3.png");//音乐

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
//        QIcon btnIcondelete(":/images/itemdelete.png");
//        QPushButton *pushButton2 = new QPushButton(btnIcondelete,QString::fromLocal8Bit("删除"),w);
//        pushButton2->setFixedHeight(30);
//        pushButton2->setFixedWidth(30);
//        QIcon btnIcon3(":/images/selection.png");
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
void MainWindow::findFileFromLineEdit(QString name)
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



/*获取系统事件并显示*/
void MainWindow::getAndShowCurTime()
{
    QDateTime curtime = QDateTime::currentDateTime();
    QString strTime = curtime.toString("yyyy-MM-dd hh:mm:ss");
    ui->lcdNumber->display(strTime);

//    QDate currentdate = QDate::currentDate();
//    QString str1 = currentdate.toString("yyyy-MM-dd");
//    QString year = str1.mid(0,4);//从0开始，截取2个字符，包括0本身
//    QString month = str1.mid(5,2);
//    QString date = str1.mid(8,2);
//    QByteArray ba = str1.toLatin1();//将QString 转换为 char *类型
//    char *dateStr = ba.data();//将QString 转换为 char *类型
//    char *year = strtok(dateStr,"-");
//    char *month = strtok(NULL,"-");
//    char *date = strtok(NULL,"-");

//    QTime currenttime = QTime::currentTime();
//    QString str2 = currenttime.toString("hh:mm:ss");
//    QString hour = str2.mid(0,2);//从0开始，截取2个字符，包括0本身
//    QString min = str2.mid(3,2);
//    QString sec = str2.mid(6,2);

//    QByteArray bt = str2.toLatin1();//将QString 转换为 char *类型
//    char *timeStr = bt.data();//将QString 转换为 char *类型
//    char *hour = strtok(timeStr,":");
//    char *min = strtok(NULL,":");
//    char *sec = strtok(NULL,":");

//  QString datetime = year + QString::fromLocal8Bit("年")+ month + QString::fromLocal8Bit("月") + date + QString::fromLocal8Bit("日")
//                    + "-" +hour + QString::fromLocal8Bit("时") + min + QString::fromLocal8Bit("分") + sec + QString::fromLocal8Bit("秒");
    //  ui->label_datetime->setText(datetime);
}

void MainWindow::itemDoubleClick(QListWidgetItem *item)
{
    //获取播放的url地址，根据地址，打开播放的文件
    QUrl url;
    url.setUrl("http://192.168.191.5:80/mv/" + item->text());
    player->setMedia(url);
}

void MainWindow::loadFileInfoToWinTitle(int index)
{
        Q_UNUSED(index);
//              QString path = m_mapList[index];
//              qDebug()<<path;
//              ui->label_title->setText(path);
}


//void MainWindow::on_openfile(QStringList fileNames)
//{

//}

/*打开文件*/
void MainWindow::on_pushButton_5_clicked()
{
    if(!m_newStart)
    {
        m_fileNames =  QFileDialog::getOpenFileNames(this,
                                                               "Open Files","C:\\Users\\24939\\Desktop",
                                                               "Videos(*avi *mp4 *flv *mp3)");

        //测试功能
        m_fileNames = list_temp;
        ui->pushButton_5->setFocusPolicy(Qt::NoFocus);//点击按钮后去掉虚线框
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
//              ui->verticalLayout_5->replaceWidget(ui->stackedWidget,videoWidget);//widget1在索引为0的dockwidget上
                m_playerState = QMediaPlayer::PlayingState;
                ui->pushButton_4->setIcon(QIcon(":/images/pausehover.png"));
                ui->pushButton_4->setToolTip(QString::fromLocal8Bit("暂停"));
                m_newStart = true;
            });
            player->play();
        }
    }
    else
    {
//        on_pushButton_6_clicked();

    }
//    m_pTimer2->stop();
}

/*重新打开播放新文件*/
void MainWindow::on_pushButton_6_clicked()
{
    if(!m_newStart)
    {
        return;
    }
    else
    {
        player->pause();
        ui->pushButton_4->setIcon(QIcon(":/images/playhover.png"));//播放
        ui->pushButton_4->setToolTip(QString::fromLocal8Bit("播放"));
        m_fileNames =  QFileDialog::getOpenFileNames(this,
                                                   "Open Files","C:\\Users\\24939\\Desktop",
                                                   "Videos(*avi *mp4 *flv *mp3)");
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
            ui->pushButton_4->setIcon(QIcon(":/images/pausehover.png"));
            ui->pushButton_4->setToolTip(QString::fromLocal8Bit("暂停"));
        }
        else
        {
            m_playerState = QMediaPlayer::PausedState;
        }
    }
}

void MainWindow::on_frameHidden()
{
    ui->widget_splider->setHidden(true);
//    ui->verticalLayout_5->removeWidget(ui->widget_splider);
}

void MainWindow::on_enterShowFrame()
{
    ui->widget_splider->setHidden(false);
    //    ui->verticalLayout_5->insertWidget(2,ui->widget_splider);
}

/*点击左侧节目列表转换显示页面*/
void MainWindow::switchListPage(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

void MainWindow::setVideoRate(int value)
{
       player->setPlaybackRate(value);
}

/*更新rate,type,layout*/
void MainWindow::updateRateTypeUiLayout(int str)
{
    Q_UNUSED(str);
    ui->pushButton_4->setIcon(QIcon(":/images/pausehover.png"));//播放
    player->setPlaybackRate(1.0);//速率恢复正常

}

/*暂停*/
//void MainWindow::on_pushButton_clicked()
//{
//    ui->pushButton->setFocusPolicy(Qt::NoFocus);//点击按钮后去掉虚线框
//    player->pause();
//}


/*播放and暂停*/
void MainWindow::on_pushButton_4_clicked()
{
//    qDebug()<<m_playerState;
    ui->pushButton_4->setFocusPolicy(Qt::NoFocus);//点击按钮后去掉虚线框
    if(m_playerState == QMediaPlayer::PlayingState)
    {
        player->pause();
        m_playerState = QMediaPlayer::PausedState;
        ui->pushButton_4->setIcon(QIcon(":/images/playhover.png"));
        ui->pushButton_4->setToolTip(QString::fromLocal8Bit("播放"));
    }
    else if(m_playerState == QMediaPlayer::PausedState)
    {
        player->play();
        m_playerState = QMediaPlayer::PlayingState;
        ui->pushButton_4->setIcon(QIcon(":/images/pausehover.png"));
        ui->pushButton_4->setToolTip(QString::fromLocal8Bit("暂停"));
    }
//    playlist->setCurrentIndex(1);
//    player->play();
}


/*停止*/
void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton_2->setFocusPolicy(Qt::NoFocus);//点击按钮后去掉虚线框
    player->stop();
    m_playerState = QMediaPlayer::PausedState;
    ui->pushButton_4->setIcon(QIcon(":/images/playhover.png"));
    ui->pushButton_4->setToolTip(QString::fromLocal8Bit("播放"));

}

/*静音*/
//void MainWindow::on_pushButton_1_clicked()
//{
//    ui->pushButton_1->setFocusPolicy(Qt::NoFocus);//点击按钮后去掉虚线框
////    if(player->isMuted())//如果静音
////    {
////        player->setMuted(false);
////        ui->pushButton_1->setIcon(QIcon(":/images/yingling.png"));
////    }
////    else
////    {
////        m_voice = player->volume();
////        player->setMuted(true);
////        ui->pushButton_1->setIcon(QIcon(":/images/jingyin.png"));
////    }
//    if(m_muteDlg->isHidden())
//    {
//        m_muteDlg->show();
//    }
//    else
//    {
//        m_muteDlg->hide();
//    }
//}

/*每秒更新一次函数*/
void MainWindow::on_time()
{

    int pos  = player->position()/1000;
    ui->horizontalSlider->setValue(pos);
    QDateTime dt1 = QDateTime::fromSecsSinceEpoch(m_times);
    QDateTime dt2 = QDateTime::fromSecsSinceEpoch(pos);
    QString str = dt1.toString("hh:mm:ss");//转换的时间不对
    QString str2 = dt2.toString("hh:mm:ss");
    ui->label_time->setText(str2+ "/" +str);

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

/*显示播放器界面*/
void MainWindow::showPlayerUi()
{
//    this->showNormal();
//    this->move((QApplication::desktop()->width()-this->width())/2, (QApplication::desktop()->height()-this->height())/2);
//    m_winMax = true;
//    if(this->isHidden() || this->isMinimized())
//    {
//        m_winMax = true;
        this->showMinimized();
        ui->pushButton_normal->setStyleSheet("QPushButton{"
                                             "background-color: transparent;"
                                             "border-image: url(:/images/normal.png);}"
                                             "QPushButton:hover{"
                                             "border: 1px solid #3C80B1;"
                                             "border-image: url(:/images/normalhover.png);}");
        qDebug()<<"show ui to the central";
//    }
}

void MainWindow::showPlayerList()
{
//    m_dockWidget->show();
    m_toolBox->show();
}

/*上一首*/
void MainWindow::on_pushButton_7_clicked()
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
void MainWindow::on_pushButton_8_clicked()
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

//void MainWindow::keyPressEvent(QKeyEvent *event)
//{
//    qDebug()<<"keyPressEvent is actived!";
//    if(event->modifiers()==Qt::ControlModifier && event->key() == Qt::Key_E)
//    {
//        videoWidget->setWindowFlags(Qt::SubWindow);
//        videoWidget->showNormal();
//    }
//}

/*解决接收不到键盘事件问题*/
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    //顶层搜索框鼠标进入离开
//    searchMouseEnterLeaveShow(watched,event);
    if(watched == ui->lineEditSearch)//监控对象每次只能监控一个，也就是说各自在各自的监控对象范围内去执行操作，不能同时监控两个
    {
        /*搜索框，搜索按钮鼠标离开*/
        if(mouseEvent->type() == QEvent::Leave)
        {
            ui->BtnSearch->setStyleSheet(
                        "QPushButton"
                        "{"
                        "color:white;"
                        "background-color:#ff5246;"
                        "border: 1px solid #ff5c38;"
                        "border-left:transparent;"
                        "border-top-right-radius:18px;"
                        "border-bottom-right-radius:18px;"
                        "border-bottom-left-radius:0px;"
                        "border-top-left-radius:0px;"
                        "}"
                         );

            ui->lineEditSearch->setStyleSheet(
                        "QLineEdit"
                        "{"
                        "color:#cccccc;"
                        "font-size:14px;"
                        "background-color: rgb(81, 81, 81);"
                        "selection-background-color: #D1DBCB;"
                        "border: 1px solid #ff5c38;"
                        "border-right:transparent;"
                        "border-top-left-radius:18px;"
                        "border-bottom-left-radius:18px;"
                        "border-bottom-right-radius:0px;"
                        "border-top-right-radius:0px;"
                        "padding-left:15px;"
                        "}"
                        );
        }

        /*搜索框，搜索按钮鼠标进入*/
        if(mouseEvent->type() == QEvent::Enter)
        {
            ui->BtnSearch->setStyleSheet(
                        "QPushButton"
                        "{"
                        "color:white;"
                        "background-color:#ff5246;"
                        "border: 1px solid #ff5c38;"
                        "border-top-right-radius:18px;"
                        "border-bottom-right-radius:18;px;"
                        "border-bottom-left-radius:0px;"
                        "border-top-left-radius:0px;"
                        "}"
                        );

            ui->lineEditSearch->setStyleSheet(
                        "QLineEdit"
                        "{"
                        "color:#cccccc;"
                        "font-size:14px;"
                        "background-color: rgb(33, 33, 33);"
                        "border:1px solid #ff5c38;"
                        "border-right:transparnet;"
                        "border-top-left-radius:18px;"
                        "border-bottom-left-radius:18px;"
                        "border-bottom-right-radius:0px;"
                        "border-top-right-radius:0px;"
                        "padding-left:15px;"
                        "}"
                        );
        }
    }

    if(watched == ui->BtnSearch)//监控对象每次只能监控一个，也就是说各自在各自的监控对象范围内去执行操作，不能同时监控两个
    {
        /*搜索框，搜索按钮鼠标离开*/
        if(mouseEvent->type() == QEvent::Leave)
        {
            ui->BtnSearch->setStyleSheet(
                        "QPushButton"
                        "{"
                        "color:white;"
                        "background-color:#ff5246;"
                        "border: 1px solid #ff5c38;"
                        "border-left:transparent;"
                        "border-top-right-radius:18px;"
                        "border-bottom-right-radius:18px;"
                        "border-bottom-left-radius:0px;"
                        "border-top-left-radius:0px;"
                        "}"
                         );

            ui->lineEditSearch->setStyleSheet(
                        "QLineEdit"
                        "{"
                        "color:#cccccc;"
                        "font-size:14px;"
                        "background-color: rgb(81, 81, 81);"
                        "selection-background-color: #D1DBCB;"
                        "border: 1px solid #ff5c38;"
                        "border-right:transparent;"
                        "border-top-left-radius:18px;"
                        "border-bottom-left-radius:18px;"
                        "border-bottom-right-radius:0px;"
                        "border-top-right-radius:0px;"
                        "padding-left:15px;"
                        "}"
                        );
        }

        /*搜索框，搜索按钮鼠标进入*/
        if(mouseEvent->type() == QEvent::Enter)
        {
            ui->BtnSearch->setStyleSheet(
                        "QPushButton"
                        "{"
                        "color:white;"
                        "background-color:#ff5246;"
                        "border: 1px solid #ff5c38;"
                        "border-top-right-radius:18px;"
                        "border-bottom-right-radius:18;px;"
                        "border-bottom-left-radius:0px;"
                        "border-top-left-radius:0px;"
                        "}"
                        );

            ui->lineEditSearch->setStyleSheet(
                        "QLineEdit"
                        "{"
                        "color:#cccccc;"
                        "font-size:14px;"
                        "background-color: rgb(33, 33, 33);"
                        "border:1px solid #ff5c38;"
                        "border-right:transparnet;"
                        "border-top-left-radius:18px;"
                        "border-bottom-left-radius:18px;"
                        "border-bottom-right-radius:0px;"
                        "border-top-right-radius:0px;"
                        "padding-left:15px;"
                        "}"
                        );
        }
    }


    //播放列表鼠标进入离开
//    playlistMouseEnterLeave(watched,event);
    //音量显示隐藏
//    volumeAdjustShowUi(watched,mouseEvent);
    //视屏退出全屏
//    videoDouleExit(watched,event);
    //登录提示窗口
//        if(watched == ui->Btnlogin && mouseEvent->type() == QEvent::Enter)
//        {
//             if(m_login)
//             {
//                 if(!m_login->isHidden())
//                 {
//                     m_login->hide();
//                 }
//             else
//                 {
//                     m_login->move(QCursor::pos().x()-155,QCursor::pos().y()+15);
//                     m_login->raise();
//                     m_login->show();
//                 }
//             }
//            set_adjustLogin();
//        }

    return QMainWindow::eventFilter(watched,event);
}

/*重写窗口关闭事件*/
void MainWindow::closeEvent(QCloseEvent *event)
{
//    QMessageBox::StandardButton button;
//        button = QMessageBox::question(this,QString::fromLocal8Bit(" "),
//                                       QString::fromLocal8Bit("确认退出程序?"),
//                                       QMessageBox::Yes|QMessageBox::No);
//        if(button==QMessageBox::No)
//        {
//            event->ignore(); // 忽略退出信号，程序继续进行
//        }
//        else if(button==QMessageBox::Yes)
//        {
//            event->accept(); // 接受退出信号，程序退出
//            QSqlQuery query;
//            query.exec("delete from LocalMusic");
//            qDebug()<<"LocalMusic data is clear";
//        }

    if(m_pExitDlg->isShow)
        m_pExitDlg->exec();
     if(!m_isClose)
     {
         event->ignore();
     }
     else
     {
         /*做一些数据保存*/
         emit sig_startCloseAppliction();
         m_pExitDlg->setIni();
         m_tray->hide();
         m_login->close();
         QSqlQuery query;
         query.exec("DROP TABLE IF EXISTS 'LocalMusic'");
         query.exec("DROP TABLE IF EXISTS 'LoginInfo'");
         qDebug()<<"LocalMusic,LoginInfo tables is drop!";

         event->accept();
     }

}

/*双击事件，这是指针全局的，不能指定某个空间，范围太大*/
//void MainWindow::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    if(m_playerState == QMediaPlayer::PlayingState && event->button() == Qt::LeftButton)
//    {
//        videoWidget->setWindowFlags(Qt::Window);//设置为顶级窗口
//        videoWidget->showFullScreen();
//        m_winMax = false;
//        ui->pushButton_normal->setStyleSheet("QPushButton{"
//                                             "background-color: transparent;"
//                                             "border-image: url(:/images/normal.png);}"
//                                             "QPushButton:hover{"
//                                             "border: 1px solid #3C80B1;"
//                                             "border-image: url(:/images/normalhover.png);}");

//    }
//}

//void MainWindow::mousePressEvent(QMouseEvent *event)
//{
//    QPoint winPos = this->pos();//主窗口相对于电脑屏幕的左上角（x = 0, y =0）
//    qDebug()<<"winpos = "<<winPos;
//    qDebug()<<frameGeometry();
//    QPoint uiPos = event->globalPos();//鼠标偏离电脑屏幕的坐标（x = 0, y =0）
//    qDebug()<<"uipos =  "<<uiPos;
//    m_mvPos = uiPos - winPos;//算出的是鼠标当前按下位置距离主窗口的w,h值
//    qDebug()<<"firrerent = "<<m_mvPos;
//}

//void MainWindow::mouseMoveEvent(QMouseEvent *event)
//{
//    this->move(event->globalPos() - m_mvPos);//重新计算pos值，即鼠标拖动后位置值-差值
//}

/*鼠标释放*/
//void MainWindow::mouseReleaseEvent(QMouseEvent *event)
//{

//}

/*窗口伸缩-此法不灵，只适用于windows下*/
//bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
//{
//    MSG* msg = (MSG*)message;
//        switch(msg->message)
//        {
//        case WM_NCHITTEST:
//            int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
//            int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();

//            if(this->childAt(xPos,yPos) == 0)
//            {
//                *result = HTCAPTION;
//            }else{
//                return false;
//            }

//            if(xPos > 0 && xPos < 8)
//                *result = HTLEFT;
//            if(xPos > (this->width() - 8) && xPos < (this->width() - 0))
//                *result = HTRIGHT;
//            if(yPos > 0 && yPos < 8)
//                *result = HTTOP;
//            if(yPos > (this->height() - 8) && yPos < (this->height() - 0))
//                *result = HTBOTTOM;
//            if(xPos > 18 && xPos < 22 && yPos > 18 && yPos < 22)
//                *result = HTTOPLEFT;
//            if(xPos > (this->width() - 22) && xPos < (this->width() - 18) && yPos > 18 && yPos < 22)
//                *result = HTTOPRIGHT;
//            if(xPos > 18 && xPos < 22 && yPos > (this->height() - 22) && yPos < (this->height() - 18))
//                *result = HTBOTTOMLEFT;
//            if(xPos > (this->width() - 22) && xPos < (this->width() - 18) && yPos > (this->height() - 22) && yPos < (this->height() - 18))
//                *result = HTBOTTOMRIGHT;
//            return true;
//        }

//          return QWidget::nativeEvent(eventType, message, result);
//}


//鼠标按下事件
/*
 *作用：
 *1.判断是否时左键点击 _isleftpressed
 *2.获取光标在屏幕中的位置 _plast
 *3.左键按下时光标所在区域 _curpos
 */
void MainWindow::mousePressEvent(QMouseEvent *event)
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
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (_isleftpressed)
        _isleftpressed = false;
    setCursor(Qt::ArrowCursor);
}

void MainWindow::changeEvent(QEvent *event)
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
void MainWindow::showEvent(QShowEvent *event)
{
    this->setAttribute(Qt::WA_Mapped);
       QWidget::showEvent(event);
}

//鼠标移动事件
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
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
int MainWindow::countFlag(QPoint p,int row)//计算鼠标在哪一列和哪一行
{
    if(p.y()<MARGIN)
        return 10+row;
    else if(p.y()>this->height()-MARGIN)
        return 30+row;
    else
        return 20+row;
}

//获取光标在窗口所在区域的 行   返回行数
int MainWindow::countRow(QPoint p)
{
    return (p.x()<MARGIN) ? 1 : (p.x()>(this->width() - MARGIN) ? 3 : 2);
}

//根据鼠标所在位置改变鼠标指针形状
void MainWindow::setCursorType(int flag)
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
void MainWindow::on_moreBtn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

/*顶层搜索框鼠标进入离开*/
void MainWindow::searchMouseEnterLeaveShow(QObject *watched, QEvent *event)
{
//    if(watched == ui->lineEditSearch || ui->BtnSearch)
//    {
//        /*搜索框，搜索按钮鼠标离开*/
//        if(event->type() == QEvent::Leave)
//        {
//            ui->BtnSearch->setStyleSheet("QPushButton"
//                                         "{"
//                                         "color:white;"
//                                         "background-color:#ff5246;"
//                                         "border: 1px solid #ff5c38;"
//                                         "border-left:transparent;"
//                                         "border-top-right-radius:18px;"
//                                         "border-bottom-right-radius:18px;"
//                                         "border-bottom-left-radius:0px;"
//                                         "border-top-left-radius:0px;"
//                                         "}"
//                                         );

//            ui->lineEditSearch->setStyleSheet("QLineEdit"
//                                              "{"
//                                              "color:#cccccc;"
//                                              "font-size:14px;"
//                                              "background-color: rgb(81, 81, 81);"
//                                              "selection-background-color: #D1DBCB;"
//                                              "border: 1px solid #ff5c38;"
//                                              "border-right:transparent;"
//                                              "border-top-left-radius:18px;"
//                                              "border-bottom-left-radius:18px;"
//                                              "border-bottom-right-radius:0px;"
//                                              "border-top-right-radius:0px;"
//                                              "padding-left:15px;"
//                                              "}"
//                                              );

//        }
//        /*搜索框，搜索按钮鼠标进入*/
//        if(event->type() == QEvent::Enter)
//        {
//            ui->BtnSearch->setStyleSheet("QPushButton"
//                                         "{"
//                                         "color:white;"
//                                         "background-color:#ff5246;"
//                                         "border: 1px solid #ff5c38;"
//                                         "border-top-right-radius:18px;"
//                                         "border-bottom-right-radius:18;px;"
//                                         "border-bottom-left-radius:0px;"
//                                         "border-top-left-radius:0px;"
//                                         "}"
//                                         );
//            ui->lineEditSearch->setStyleSheet("QLineEdit"
//                                              "{"
//                                              "color:#cccccc;"
//                                              "font-size:14px;"
//                                              "background-color: rgb(33, 33, 33);"
//                                              "border:1px solid #ff5c38;"
//                                              "border-right:transparnet;"
//                                              "border-top-left-radius:18px;"
//                                              "border-bottom-left-radius:18px;"
//                                              "border-bottom-right-radius:0px;"
//                                              "border-top-right-radius:0px;"
//                                              "padding-left:15px;"
//                                              "}"
//                                              );

//        }
//    }
}

/*处理视频界面双击退出事件*/
bool MainWindow::videoDouleExit(QObject *watched, QEvent *event)
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
 //                    m_winMax = true;
                     ui->pushButton_normal->setStyleSheet("QPushButton{"
                                                          "background-color: transparent;"
                                                          "border-image: url(:/images/normalmax.png);}"
                                                          "QPushButton:hover{"
                                                          "border: 1px solid #3C80B1;"
                                                          "border-image: url(:/images/normalmaxhover.png);}");
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
 //                        videoWidget->adjustSize();
 //                        this->setWindowState(Qt::WindowMaximized);
 //                        m_winMax = false;
                         ui->pushButton_normal->setStyleSheet("QPushButton{"
                                                              "background-color: transparent;"
                                                              "border-image: url(:/images/normal.png);}"
                                                              "QPushButton:hover{"
                                                              "border: 1px solid #3C80B1;"
                                                              "border-image: url(:/images/normalhover.png);}");
                     }
                 }
             }

         }
     }
     return 0;
}

/*音量调节界面显隐*/
void MainWindow::volumeAdjustShowUi(QObject *watched, QEvent *event)
{
        /*音量调节显示*/
    if(watched == ui->pushButton_1)
    {
        qDebug()<<"pushbutton_1 enter";
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
                    m_muteDlg->move(ui->pushButton_1->pos());
                    m_muteDlg->show();
                }
            }
        }
    }
}

/*播放列表界面搜索框鼠标进入离开*/
void MainWindow::playlistMouseEnterLeave(QObject *watched, QEvent *event)
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

/*外部功能-截图*/
void MainWindow::showCaptureScreen()
{
    //思路
    //[static] bool QDir::setCurrent(const QString &path),[static] QString QDir::currentPath()
    //applicationpath().可以设置path,根据path回退路径
    QProcess *pProcess = new QProcess(this);
    pProcess->start("E:\\software\\FastStoneCapturePortable\\FSCapture.exe");//为了方便演示，使用了绝对路径，release时，使用相对路径
    bool isOk = pProcess->waitForStarted(3000);
    if(isOk)
    {
        qDebug()<<"invoke ok";
    }
    else
    {
        qDebug()<<"invoke failed";
    }
    //    delete pProcess;
}

/*控制节目列表显示隐藏*/
void MainWindow::showJieMuListWidget()
{
//    qDebug()<<"show jie mu lie biao";
    if(!m_jiemuShow)
    {
        ui->listWidget_playlist->setHidden(true);
        ui->moreBtn->setHidden(true);
        ui->Btn_logo->setHidden(true);
    }
    else
    {
        ui->listWidget_playlist->setHidden(false);
        ui->moreBtn->setHidden(false);
        ui->Btn_logo->setHidden(false);
    }
    m_jiemuShow = !m_jiemuShow;
}

/*系统设置*/
void MainWindow::help_stemAboutSetting()
{
    if(m_systemSetting->isHidden())
    {
        m_systemSetting->exec();
    }
    else
    {
        m_systemSetting->hide();
    }
}

/*问题帮助*/
void MainWindow::help_questionAnswer()
{
    QMessageBox::information(this,QString::fromLocal8Bit("问题帮助"),QString::fromLocal8Bit("为当前系统进行问题帮助。"));
}

/*打开本地文件*/
void MainWindow::help_aboutLocalFile()
{
//    QMessageBox::information(this,QString::fromLocal8Bit("本地文件"),QString::fromLocal8Bit("选择本地文件进行播放。"));
    on_pushButton_6_clicked();
}

/*打开门户网站*/
void MainWindow::help_openWebSite()
{
//    QMessageBox::information(this,QString::fromLocal8Bit("修复建议"),QString::fromLocal8Bit("为当前系统提供修复建议。"));
    QDesktopServices::openUrl(QUrl(QString("https://v.qq.com/biu/download#Windows")));
}

/*调节界面*/
void MainWindow::set_adjustBright()
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
            m_adjustBright->move(QCursor::pos().x()-300,QCursor::pos().y()-370);
//            m_adjustBright->move(event->globalPos());
            m_adjustBright->raise();
            m_adjustBright->show();
        }
    }
    else
    {
        m_adjustBright = new AdjustBright(this);
//        m_adjustBright->move(point.x()-200,point.y()-370);
        m_adjustBright->move(QCursor::pos().x()-300,QCursor::pos().y()-370);
//        m_adjustBright->move(event->globalPos());
        m_adjustBright->raise();
        m_adjustBright->show();
    }

}

void MainWindow::set_adjustLogin()
{
//    QMenu *menu = new QMenu(this);
//    menu->setFixedSize(310,200);
//    QWidgetAction *a = new QWidgetAction(menu);
//    a->setDefaultWidget(m_login);
//    QPoint  point = QPoint(QCursor::pos().x()-155,QCursor::pos().y()+25);
//    menu->exec(point);
    if(m_login)
    {
        if(!m_login->isHidden())
        {
            m_login->hide();
        }
        else
        {
            m_login->move(QCursor::pos().x()-155,QCursor::pos().y()+25);
            m_login->raise();
            m_login->show();
        }
    }
    else
    {
        m_login = new Login(this);
        m_login->move(QCursor::pos().x()-155,QCursor::pos().y()+25);
        m_login->raise();
        m_login->show();
    }
}

/*调节播放模式*/
void MainWindow::adjust_playBackMode(int index)
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
void MainWindow::adjust_aspectRatioMode(int index)
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
void MainWindow::update_adjustBright()
{
    videoWidget->setBrightness(10);
    videoWidget->setSaturation(10);
    videoWidget->setContrast(10);
    videoWidget->setHue(10);
}

void MainWindow::downloadInternetPathRecource()
{

}

void MainWindow::playHttpRequireRecourse(const QString &url)
{
    QUrl url_rec;
    url_rec.setUrl("http://192.168.220.128:8080/group1/videos/wanjiang_MP4HV.mp4");
    player->setMedia(url_rec);
    player->play();
}


void MainWindow::on_pushButton_danmu_clicked()
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
