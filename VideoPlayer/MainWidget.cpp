#include "MainWidget.h"
#include "updater/Updater.h"
#include "database/dataBase.h"
#include "customer/CustomTabStyle.h"
#include "desktoplyric/toplyric/DesktopLyric.h"


#ifdef Q_OS_WIN
//#include <qt_windows.h>
//#include <Windows.h>
//#include <windowsx.h>
//#pragma comment (lib,"user32.lib")
#endif

#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QActionGroup>
#include <QWidgetAction>

MainWidget::MainWidget(QWidget *parent) :
    BaseWidget(parent),
    m_isHide(false),
    m_winMax(false),
    m_firstOpen(true)
{
    setMinimumSize(1160,680);//1320,800 1500,950
    this->resize(QSize(1500,920));

    setWindowTitle(QString::fromLocal8Bit("主界面"));
    initOtherWidgetUi();//初始化界面
    setInstallEventFilter();
    setLeftSliderCurrentIndex(0);//主界面左侧列表内容
    setStackedWidgetPage();//设置StackedWidget布局每个page界面
    handleSignalAndSLots();//处理所有的信号与槽函数
}

//初始化界面
void MainWidget::initOtherWidgetUi()
{
    m_titleBar = new TitleBar(this);
    m_titleBar->setWebDefUrl(dataBase::getWebDef_url());//设置默认显示标题
    m_titleBar->setObjectName(QString::fromLatin1("m_titleBar"));
    setTitleBarMoveArea(m_titleBar,2);//这里的5是setContentsMargins


    m_leftSideBar = new LeftSideBar(this);
    m_leftSideBar->setObjectName(QString::fromLatin1("m_leftSideBar"));
    QStringList list = {};
    m_leftSideBar->setSlideBarListText(list);//侧边栏目录
    m_leftSideBar->setLeftSliderFixedWidth(LISTWIDTH_L);//左侧列表+按钮

    m_stackWidget_center = new QStackedWidget(this);
    m_stackWidget_center->setObjectName(QString::fromLatin1("m_stackWidget_center"));    
    //QStackedWidget此处不能指定父参数，否则界面会出问题

    m_leftButton = new QPushButton(m_stackWidget_center);
    m_leftButton->setObjectName(QString::fromLocal8Bit("m_leftButton"));
    m_leftButton->setFixedSize(20,60);
    m_leftButton->hide();
    //首页推荐
//    m_homeWidget = new HomeWidget(m_stackWidget_center);
//    m_homeWidget->setObjectName(QString::fromLocal8Bit("m_homeWidget"));

//    m_mainVideoMv = new VideoMv(m_stackWidget_center);
//    m_mainVideoMv->setObjectName(QString::fromLocal8Bit("m_mainVideoMv"));

    m_videoMember = new MainMembForm(m_stackWidget_center);
    m_videoMember->setObjectName(QString::fromLocal8Bit("m_videoMember"));

    MultipPlayer::getInstance()->setObjectName(QString::fromLatin1("m_mainPlayer"));

    m_musicList = new MusicPlaylist(m_stackWidget_center);
    m_musicList->setObjectName(QString::fromLatin1("m_musicList"));

    m_shortVideo = new ShortVideo(m_stackWidget_center);
    m_shortVideo->setObjectName(QString::fromLatin1("m_shortVideo"));


//    m_tabWidget = new CusTabWidget(m_stackWidget_center);
//    m_tabWidget->setObjectName(QString::fromLatin1("m_tabWidget"));

    m_videoBlank = new VideoBlank();
    m_videoBlank->setHideOpenButton(false);//隐藏打开文件按钮
    m_videoBlank->setObjectName(QString::fromLatin1("m_videoBlank"));

    m_webBrowser = new CusWebBrowser();
    m_webBrowser->setCurrentDefaultUrl(dataBase::getWebDef_url());
    m_webBrowser->setObjectName(QString::fromLatin1("m_webBrowser"));

    m_webAddBtn = new QPushButton("+");//添加tab按钮
    m_webAddBtn->setFixedSize(30,26);
    m_webAddBtn->setFlat(true);
    m_webAddBtn->setObjectName(QString::fromLocal8Bit("m_webAddBtn"));

    m_addHblayout = new QHBoxLayout();
    m_addHblayout->addWidget(m_webAddBtn);
    //    enum Policy {
    //        Fixed = 0,
    //        Minimum = GrowFlag,
    //        Maximum = ShrinkFlag,
    //        Preferred = GrowFlag | ShrinkFlag,
    //        MinimumExpanding = GrowFlag | ExpandFlag,
    //        Expanding = GrowFlag | ShrinkFlag | ExpandFlag,
    //        Ignored = ShrinkFlag | GrowFlag | IgnoreFlag
    //    };
    sparcer_item = new QSpacerItem(20,20,QSizePolicy::MinimumExpanding);
    m_addHblayout->addSpacerItem(sparcer_item);
//    m_addHblayout->addStretch(50);
    m_addHblayout->setSpacing(0);
    m_addHblayout->setContentsMargins(0,0,0,0);

    m_addWidget = new QWidget();
    m_addWidget->setObjectName(QString::fromLocal8Bit("m_addWidget"));
    m_addWidget->setLayout(m_addHblayout);
//    m_addWidget->layout()->invalidate();

    m_cusTabbar = new CusTabBar();
    m_cusTabbar->setObjectName(QString::fromLocal8Bit("m_cusTabbar"));
    m_cusTabbar->hide();

    m_progressBar = new QProgressBar();
    m_progressBar->setFixedSize(100,14);
    m_progressBar->setObjectName(QString::fromLocal8Bit("m_progressBar"));

    opacity = new QGraphicsOpacityEffect(m_progressBar);//状态栏进度条设置

    m_statusBar = new QStatusBar();
    m_statusBar->setFixedHeight(20);
    m_statusBar->setObjectName(QString::fromLocal8Bit("m_statusBar"));
    m_statusBar->setSizeGripEnabled(false);
    m_statusBar->addPermanentWidget(m_progressBar);//右侧插入，永久性消息
//    m_statusBar->addWidget(m_progressBar);//左侧插入，临时性消息

    m_webTabWidget = new QTabWidget();
    m_webTabWidget->setObjectName(QString::fromLocal8Bit("m_webTabWidget"));
//    m_webTabWidget->setCornerWidget(m_addWidget,Qt::TopRightCorner);//每次添加或者删除一个tab都要计算宽度
    m_webTabWidget->tabBar()->setObjectName(QString::fromLocal8Bit("m_webTabBar"));
    m_webTabWidget->tabBar()->setLayoutDirection(Qt::LeftToRight);
    m_webTabWidget->insertTab(0,m_webBrowser,QIcon("://images/icon/engine.png"),m_webBrowser->title());
//    m_webTabWidget->setTabToolTip(0,m_webBrowser->title());
    m_webTabWidget->setTabsClosable(true);//打开关闭按钮
    m_webTabWidget->setMovable(true);//标签可拖动
    m_webTabWidget->setElideMode(Qt::ElideRight);//文字过长省略号代替
//    m_webTabWidget->setDocumentMode(true);
    m_webTabWidget->tabBar()->setStyle(new CustomTabStyle);//调整体字、图标

//    m_webTabWidget->tabBar()->setTabButton(0,QTabBar::RightSide,m_addWebButton);
//    m_webTabWidget->setCornerWidget(m_addWebButton,Qt::TopRightCorner);
//    m_webTabWidget->setTabShape(QTabWidget::Triangular);//设置样式后，不起作用
    m_webVblayout = new QVBoxLayout();
    m_webVblayout->setSpacing(0);
    m_webVblayout->setContentsMargins(0,0,0,0);

    m_webVblayout->addWidget(m_cusTabbar);
    m_webVblayout->addWidget(m_webTabWidget);
    m_webVblayout->addWidget(m_statusBar);

    m_webWidget  = new QWidget(m_webStackWgt);
    m_webWidget->setObjectName(QString::fromLocal8Bit("m_webWidget"));
    m_webWidget->setLayout(m_webVblayout);

    m_webRecords = new CollectRecords(m_webStackWgt);
    m_webRecords->setObjectName(QString::fromLocal8Bit("m_webRecords"));

    m_webHistory = new WebHistory(m_webStackWgt);
    m_webHistory->setObjectName(QString::fromLocal8Bit("m_webHistory"));

    m_webStackWgt = new QStackedWidget(m_stackWidget_center);
    m_webStackWgt->setObjectName(QString::fromLocal8Bit("m_webStackWgt"));
    m_webStackWgt->addWidget(m_webWidget);// 0 浏览器
    m_webStackWgt->addWidget(m_webRecords);//1 浏览器收藏记录
    m_webStackWgt->addWidget(m_webHistory);//2 浏览器浏览历史
    m_webStackWgt->setCurrentWidget(m_webWidget);


    m_fileTrans = new FilesTrans(m_stackWidget_center);
    m_fileTrans->setObjectName(QString::fromLocal8Bit("m_fileTrans"));

    m_personForm = new PersonFileForm(m_stackWidget_center);
    m_personForm->setObjectName(QString::fromLatin1("m_personForm"));

    //弹出对话框
    m_pExitDlg = new ExitDialog(this);
    m_pExitDlg->setObjectName(QString::fromLatin1("m_pExitDlg"));

    m_hotSearch = new HotSearchForm(m_stackWidget_center);
    m_hotSearch->setObjectName(QString::fromLocal8Bit("m_hotSearch"));

    m_systemSetting = new SystemSetting();
    m_systemSetting->setObjectName(QString::fromLocal8Bit("m_systemSetting"));

    //歌手排行
//    m_songerSort = new SongerSort(m_stackWidget_center);
//    m_songerSort->setObjectName(QString::fromLocal8Bit("m_songerSort"));

    //排行榜
//    m_rankList = new RankingList(m_stackWidget_center);
//    m_rankList->setObjectName(QString::fromLocal8Bit("m_rankList"));

    //歌单分类
    m_songlistSort = new SonglistSort(m_stackWidget_center);
    m_songlistSort->setObjectName(QString::fromLocal8Bit("m_songlistSort"));

    //主播电台
//    m_radioHost = new RadioHost(m_stackWidget_center);
//    m_radioHost->setObjectName(QString::fromLocal8Bit("m_radioHost"));

    //音乐现场
//    m_musicScene = new MusicScene(m_stackWidget_center);
//    m_musicScene->setObjectName(QString::fromLocal8Bit("m_musicScene"));

    //会员专区
//    m_vipMember = new VipMember(m_stackWidget_center);
//    m_vipMember->setObjectName(QString::fromLocal8Bit("m_vipMember"));

    //视频盒子1
    m_cusVideoBox = new CusVideosBox(m_stackWidget_center);
    m_cusVideoBox->setObjectName(QString::fromLocal8Bit("m_cusVideoBox"));

    //视频盒子2
    m_cusVideoBox2 = new CusVideoBox2(m_stackWidget_center);
    m_cusVideoBox2->setObjectName(QString::fromLocal8Bit("m_cusVideoBox2"));

    //视频盒子3
    m_cusVideoBox3 = new CusVideoBox3(m_stackWidget_center);
    m_cusVideoBox3->setObjectName(QString::fromLocal8Bit("m_cusVideoBox3"));

    //视频盒子4
    m_cusVideoBox4 = new CusVideoBox4(m_stackWidget_center);
    m_cusVideoBox4->setObjectName(QString::fromLocal8Bit("m_cusVideoBox4"));

    //视频盒子5
    m_cusVideoBox5 = new CusVideoBox5(m_stackWidget_center);
    m_cusVideoBox5->setObjectName(QString::fromLocal8Bit("m_cusVideoBox5"));

    //视频盒子6
    m_cusVideoBox6 = new CusVideoBox6(m_stackWidget_center);
    m_cusVideoBox6->setObjectName(QString::fromLocal8Bit("m_cusVideoBox6"));

    //视频盒子7
    m_cusVideoBox7 = new CusVideoBox7(m_stackWidget_center);
    m_cusVideoBox7->setObjectName(QString::fromLocal8Bit("m_cusVideoBox7"));


    //视频筛选结果
    videoFindResult = new VideoTypeSelect(m_stackWidget_center);
    videoFindResult->setObjectName(QString::fromLocal8Bit("videoFindResult"));

    //全局查找结果
    globalFindRlt = new ResultLists(m_stackWidget_center);
    globalFindRlt->setObjectName(QString::fromLocal8Bit("globalFindRlt"));

    //托盘
    m_tray = new QSystemTrayIcon(QIcon(":/images/icon/tray.png"),this);
//    m_tray->installEventFilter(this);
    m_tray->setToolTip(QString(u8"音视频播放器"));
    m_tray->show();
    createTrayMenu();

    m_stackWidget_left = new QStackedWidget(this);
    m_stackWidget_left->setObjectName(QString::fromLocal8Bit("m_stackWidget_left"));
    m_stackWidget_left->setFixedWidth(LISTWIDTH_L);//固定宽度66
    m_stackWidget_left->insertWidget(0,m_leftSideBar);
//    m_stackWidget_left->insertWidget(1,new CentralHomeForm());

    m_vblayout  = new QVBoxLayout();//左后的上下布局
    m_hblayout  = new QHBoxLayout();//最后的左右布局

    //侧边栏+QStackedWidget--->水平布局
    m_hblayout->addWidget(m_stackWidget_left,0,Qt::AlignLeft);
//    m_hblayout->addStretch(50);
    m_hblayout->addWidget(m_stackWidget_center);
    m_hblayout->setSpacing(0);
    m_hblayout->setContentsMargins(0,0,0,0);

    //标题栏+水平布局--->垂直布局
    m_vblayout->addWidget(m_titleBar,0,Qt::AlignTop);
    m_vblayout->addLayout(m_hblayout,1);
//    m_vblayout->setContentsMargins(MARGIN,MARGIN,MARGIN,MARGIN);
    m_vblayout->setSpacing(0);

    //说明：
    //setlayout接口使用时，所有的布局没有指定父亲为this
    //如果有布局父亲为this,可以不设置setlayout

    //这是一种布局实现方式
    this->setLayout(m_vblayout);
    this->setContentsMargins(MARWIDTH,MARWIDTH,MARWIDTH,MARWIDTH);//界面拉伸的边缘宽度
    this->layout()->setContentsMargins(0,0,0,0);//布局的边缘宽度

    ScrollToTop::getInstance()->setParent(this);//设为父亲
    ScrollToTop::getInstance()->hide();

    RingWait1::getInstance()->setParent(this);
    RingWait1::getInstance()->hide();
}

//设置StackedWidget布局每个page界面
void MainWidget::setStackedWidgetPage()
{
    m_stackWidget_center->addWidget(m_cusVideoBox);//精选推荐
    connectToTopWidget(m_cusVideoBox);//建立关联
    m_stackWidget_center->addWidget(m_cusVideoBox2);//独家影院
    connectToTopWidget(m_cusVideoBox2);//建立关联
    m_stackWidget_center->addWidget(m_cusVideoBox3);//少儿动画
    connectToTopWidget(m_cusVideoBox3);//建立关联
    m_stackWidget_center->addWidget(m_cusVideoBox4);//热播电影
    connectToTopWidget(m_cusVideoBox4);//建立关联
    m_stackWidget_center->addWidget(m_cusVideoBox5);//独家播放
    connectToTopWidget(m_cusVideoBox5);//建立关联
    m_stackWidget_center->addWidget(videoFindResult);//视频分类查询
    m_stackWidget_center->addWidget(m_videoMember);//会员视频
    connectToTopWidget(m_videoMember);//建立关联
    m_stackWidget_center->addWidget(m_webStackWgt);//浏览器
//    m_stackWidget_center->addWidget(m_mainVideoMv);//视频mv
    m_stackWidget_center->addWidget(m_hotSearch);//热门搜索
//    m_stackWidget_center->addWidget(m_homeWidget);//个性推荐
//    m_stackWidget_center->addWidget(m_songerSort);//歌手分类
//    m_stackWidget_center->addWidget(m_rankList);//热门飙升
    m_stackWidget_center->addWidget(m_songlistSort);//歌手筛选
//    m_stackWidget_center->addWidget(m_radioHost);//电台
//    m_stackWidget_center->addWidget(m_musicScene);//音乐场景
//    m_stackWidget_center->addWidget(m_vipMember);//vip会员
    m_stackWidget_center->addWidget(m_shortVideo);//资讯速览
    m_stackWidget_center->addWidget(m_musicList);//歌曲列表
    m_stackWidget_center->addWidget(m_personForm);//个人管理
    m_stackWidget_center->addWidget(m_fileTrans);//文件传输
    m_stackWidget_center->addWidget(m_cusVideoBox6);
    connectToTopWidget(m_cusVideoBox6);//建立关联
    m_stackWidget_center->addWidget(m_cusVideoBox7);
    connectToTopWidget(m_cusVideoBox7);//建立关联
    m_stackWidget_center->addWidget(globalFindRlt);//全局查找结果

//    m_stackWidget_center->addWidget(m_tabWidget);//原始table界面
    m_stackWidget_center->setCurrentIndex(0);//默认显示第一个page页
}

void MainWidget::setLeftSliderCurrentIndex(int index)
{
    m_stackWidget_left->setCurrentIndex(index);
}

void MainWidget::slot_setCurrentCenterStackWidget(int index)
{
    m_stackWidget_center->setCurrentIndex(index);
}

void MainWidget::slot_setCurrentCenterStackWidget(QString name)
{
//    m_stackWidget_center->setCurrentWidget();
}

//重载函数1：添加一个browser---参数为QUrl
void MainWidget::slot_addToWebTabwidgetBrowser(QUrl &url)
{
    if(url.isEmpty()) return;
    CusWebBrowser *browser = new CusWebBrowser();
    browser->setObjectName(QString::fromLocal8Bit("browser"));
    browser->load(url);
    m_titleBar->slot_setWebLineEditCurentUrl(url);
    m_webTabWidget->insertTab(m_webTabWidget->currentIndex()+1,browser,QIcon("://images/icon/engine.png"),"new page");
    m_webTabWidget->setCurrentIndex(m_webTabWidget->currentIndex()+1);
//    updateAddWebButtonPosition();
    connect(browser,&CusWebBrowser::loadFinished,[=](){
        qDebug() <<QString::fromLocal8Bit("图标")<<browser->icon()<<QString::fromLocal8Bit("标题")<<browser->title();
    });
    //标题改变
    connect(browser,&CusWebBrowser::titleChanged,[=](const QString &title){
        slot_setCurrentWebBarTitle(m_webTabWidget->indexOf(browser),title);
    });
    //图标改变
    connect(browser,&CusWebBrowser::iconChanged,[=](const QIcon &icon){
        slot_setCurrentWebBarIcon(m_webTabWidget->indexOf(browser),icon);
    });
    connect(browser,SIGNAL(sig_sendToNewUrl(QUrl&)),this,SLOT(slot_addToWebTabwidgetBrowser(QUrl&)));
    //加载网页进度
    connect(browser,SIGNAL(loadProgress(int)),m_titleBar,SLOT(slot_setWebProgressBarValue(int)));
    connect(browser,SIGNAL(loadProgress(int)),this,SLOT(slot_setWebProgreeBarValue(int)));
    //网页下载请求1
    connect(browser->page()->profile(),SIGNAL(downloadRequested(QWebEngineDownloadItem*)),NewWork::getInstance(),SLOT(slot_receiveDownloadRequested(QWebEngineDownloadItem*)),Qt::UniqueConnection);//第五个参数，防止多次请求
    //可回退
    connect(m_titleBar,SIGNAL(sig_sendCanGoBack()),this,SLOT(slot_canGoBack()));
    connect(this,SIGNAL(sig_canGoBack(bool)),m_titleBar,SLOT(slot_setCanGoBack(bool)));
    //可前进
    connect(m_titleBar,SIGNAL(sig_sendCanForward()),this,SLOT(slot_canGoForward()));
    connect(this,SIGNAL(sig_canGoForward(bool)),m_titleBar,SLOT(slot_setCanGoForward(bool)));
    //回车
    connect(m_titleBar,SIGNAL(sig_sendInputNewUrl(QString)),this,SLOT(slot_judgeCurrentBrowserIsActive_load(QString)));
    //后退
    connect(m_titleBar,SIGNAL(sig_sendUrlBack()),this,SLOT(slot_judgeCurrentBrowserIsActive_back()));
    //刷新
    connect(m_titleBar,SIGNAL(sig_sendUrlRefreshen()),this,SLOT(slot_judgeCurrentBrowserIsActive_freshen()));
    //前进
    connect(m_titleBar,SIGNAL(sig_sendUrlAdvance()),this,SLOT(slot_judgeCurrentBrowserIsActive_advance()));
    //返回主页
    connect(m_titleBar,SIGNAL(sig_sendUrlHome()),this,SLOT(slot_judgeCurrentBrowserIsActive_home()));
    //当前项改变
    connect(browser,SIGNAL(urlChanged(QUrl)),m_titleBar,SLOT(slot_setWebLineEditCurentUrl(QUrl)));
    //当前网页自己显示
//    connect(browser->page(),SIGNAL(urlChanged(QUrl)),m_titleBar,SLOT(slot_setWebLineEditCurentUrl(QUrl)));
    //鼠标link
    connect(browser->page(),&QWebEnginePage::linkHovered,this,&MainWidget::slot_showLinkOnStatusBar);
    //URL改变
    connect(browser,&CusWebBrowser::urlChanged,[=](QUrl url){slot_showLinkOnStatusBar(url.toDisplayString());});
    //新增历史记录（浏览器点击链接跳转）
    connect(browser,&CusWebBrowser::urlChanged,[=](QUrl url){m_webHistory->slot_addToListHistoryWidget(url);});//添加历史记录
    //新添加的tab页面
    connect(browser,&CusWebBrowser::sig_sendToNewUrl,[=](QUrl url){m_webHistory->slot_addToListHistoryWidget(url);});
}

//重载函数2：添加一个browser---参数为QString
void MainWidget::slot_addToWebTabwidgetBrowser(QString &url)
{
    if(url.isEmpty()) return;
    CusWebBrowser *browser = new CusWebBrowser();
    browser->setObjectName(QString::fromLocal8Bit("browser"));
    browser->load(url);
    m_titleBar->slot_setWebLineEditCurentUrl(url);
    int current = m_webTabWidget->currentIndex();
    qDebug() <<QString::fromLocal8Bit("当前要插入的行号:") <<current;
    m_webTabWidget->insertTab(m_webTabWidget->currentIndex()+1,browser,QIcon("://images/icon/engine.png"),"new page");
    m_webTabWidget->setCurrentIndex(m_webTabWidget->currentIndex()+1);//新插入的为当前选中项
//    updateAddWebButtonPosition();
    connect(browser,&CusWebBrowser::loadFinished,[=](){
        qDebug() <<QString::fromLocal8Bit("图标")<<browser->icon()<<QString::fromLocal8Bit("标题")<<browser->title();
    });
    //标题改变
    connect(browser,&CusWebBrowser::titleChanged,[=](const QString &title){
        slot_setCurrentWebBarTitle(m_webTabWidget->indexOf(browser),title);
    });
    //图标改变
    connect(browser,&CusWebBrowser::iconChanged,[=](const QIcon &icon){
        slot_setCurrentWebBarIcon(m_webTabWidget->indexOf(browser),icon);
    });
    connect(browser,SIGNAL(sig_sendToNewUrl(QUrl&)),this,SLOT(slot_addToWebTabwidgetBrowser(QUrl&)));
    //加载网页进度
    connect(browser,SIGNAL(loadProgress(int)),m_titleBar,SLOT(slot_setWebProgressBarValue(int)));
    connect(browser,SIGNAL(loadProgress(int)),this,SLOT(slot_setWebProgreeBarValue(int)));
    //网页下载请求2
    connect(browser->page()->profile(),SIGNAL(downloadRequested(QWebEngineDownloadItem*)),NewWork::getInstance(),SLOT(slot_receiveDownloadRequested(QWebEngineDownloadItem*)),Qt::UniqueConnection);//都五个参数，防止多次请求
    //可回退
    connect(m_titleBar,SIGNAL(sig_sendCanGoBack()),this,SLOT(slot_canGoBack()));
    connect(this,SIGNAL(sig_canGoBack(bool)),m_titleBar,SLOT(slot_setCanGoBack(bool)));
    //可前进
    connect(m_titleBar,SIGNAL(sig_sendCanForward()),this,SLOT(slot_canGoForward()));
    connect(this,SIGNAL(sig_canGoForward(bool)),m_titleBar,SLOT(slot_setCanGoForward(bool)));
    //回车
    connect(m_titleBar,SIGNAL(sig_sendInputNewUrl(QString)),this,SLOT(slot_judgeCurrentBrowserIsActive_load(QString)));
    //后退
    connect(m_titleBar,SIGNAL(sig_sendUrlBack()),this,SLOT(slot_judgeCurrentBrowserIsActive_back()));
    //刷新
    connect(m_titleBar,SIGNAL(sig_sendUrlRefreshen()),this,SLOT(slot_judgeCurrentBrowserIsActive_freshen()));
    //前进
    connect(m_titleBar,SIGNAL(sig_sendUrlAdvance()),this,SLOT(slot_judgeCurrentBrowserIsActive_advance()));
    //返回主页
    connect(m_titleBar,SIGNAL(sig_sendUrlHome()),this,SLOT(slot_judgeCurrentBrowserIsActive_home()));
    //当前项改变
    connect(browser,SIGNAL(urlChanged(QUrl)),m_titleBar,SLOT(slot_setWebLineEditCurentUrl(QUrl)));
    //鼠标link
    connect(browser->page(),&QWebEnginePage::linkHovered,this,&MainWidget::slot_showLinkOnStatusBar);
    //URL改变
    connect(browser,&CusWebBrowser::urlChanged,[=](QUrl url){slot_showLinkOnStatusBar(url.toDisplayString());});
    //新增历史记录（浏览器点击链接跳转）
    connect(browser,&CusWebBrowser::urlChanged,[=](QUrl url){m_webHistory->slot_addToListHistoryWidget(url);});//添加历史记录
    //新添加的tab页面
    connect(browser,&CusWebBrowser::sig_sendToNewUrl,[=](QUrl url){m_webHistory->slot_addToListHistoryWidget(url);});
}

QIcon MainWidget::slot_getCurrentBrowserIcon()
{
    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
    if(!actWdgt->icon().isNull())
    {
        return  actWdgt->icon();
        qDebug() << QString::fromLocal8Bit("获取到的当前webicon")<<actWdgt->icon();
    }
    else
    {
        return  QIcon("://images/icon/engine.png");
        qDebug() << QString::fromLocal8Bit("当前图标为固定图标");
    }
}

QString MainWidget::slot_getCurrentBrowserTitle()
{
    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
    if(!actWdgt->title().isNull())
    {
        return  actWdgt->title();
        qDebug() << QString::fromLocal8Bit("获取到的当前webicon")<<actWdgt->title();
    }
    else
    {
        return  actWdgt->url().toDisplayString();
        qDebug() << QString::fromLocal8Bit("当前图标为固定图标");
    }
}

//过滤不是当前活跃的窗口--返回主页
void MainWidget::slot_judgeCurrentBrowserIsActive_home()
{
   CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
       actWdgt->slots_home();
       m_webStackWgt->setCurrentWidget(m_webWidget);
       //       delete actWdgt;
}

void MainWidget::slot_judgeCurrentBrowserIsActive_back()
{
    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
        actWdgt->slots_back();
        m_webStackWgt->setCurrentWidget(m_webWidget);
//        delete actWdgt;
}

void MainWidget::slot_judgeCurrentBrowserIsActive_freshen()
{
    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
        actWdgt->slots_refreshen();
        m_webStackWgt->setCurrentWidget(m_webWidget);
//        delete actWdgt;
}

void MainWidget::slot_judgeCurrentBrowserIsActive_advance()
{
    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
        actWdgt->slots_advance();
        m_webStackWgt->setCurrentWidget(m_webWidget);
        //        delete actWdgt;
}

//全屏显示
void MainWidget::slot_webbrowserShowFullscreen()
{
    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
        actWdgt->showFullScreen();
        qDebug() << "show fullscreen";
}

void MainWidget::slot_judgeCurrentBrowserIsActive_load(QString newUrl)
{
    qDebug() << "receive new url = "<< newUrl;
    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
        actWdgt->slots_loadNewUrl(newUrl);
//        delete actWdgt;
}

void MainWidget::slot_removeTabWidgetTab(int index)
{
    qDebug() << QString::fromLocal8Bit("要删除的选项索引是:") << index;
    if(index == 0) return;//永远不删除第一个，留一个
//    m_webTabWidget->tabBar()->tabButton(index,QTabBar::LeftSide);
    QWidget* currWidget = m_webTabWidget->widget(index);
    //大坑：在此delete后，就不需要removeTab()了，否则会删除所有的tab
    if(currWidget != nullptr)
    {
        delete currWidget;
        currWidget = nullptr;
    }
    slot_setRemoveTabLineEditText(index);//显示当前选中的web URL

//    m_webTabWidget->removeTab(index);//为什么主窗口删除，其他子窗口也被删除？
//    m_webTabWidget->tabBar()->hide();
//    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
//    m_titleBar->slot_setWebLineEditCurentUrl(actWdgt->url());//删除显示最新的tab的URL
//    delete actWdgt;
}

//处理信号与槽函数
void MainWidget::handleSignalAndSLots()
{
    //全局更新update,repaint,resize(this->size()),adjustSize
    connect(this,&MainWidget::sig_globalResize,[=](){
//        m_homeWidget->slot_globalResize();//推荐总界面更新
//        m_mainVideoMv->slot_globalResize();//视频推荐界面更新
//        m_webRecords->slot_globalResize();//收藏记录界面更新
//        m_webHistory->slot_globalResize();//历史记录界面更新
    });


    //点击托盘的信号
    connect(m_tray,&QSystemTrayIcon::activated,[=](QSystemTrayIcon::ActivationReason reason){slot_activeTray(reason);});

    //控制侧边栏显示
    connect(m_titleBar,&TitleBar::sig_sendHideSlider,[=](bool showed){
        if(showed)
        {
            m_stackWidget_left->hide();
        }
        else
        {
            m_stackWidget_left->show();
        }
    });

    //更换皮肤
    connect(m_leftSideBar,&LeftSideBar::sig_sendSkinMode,[=](bool day){
        if(day)
        {
            loadGlobalQss::loadAllUIQss(STYLETYPE::STYLE_BLACK);
        }
        else
        {
            loadGlobalQss::loadAllUIQss(STYLETYPE::STYLE_WHITE);
        }
    });

    //主界面resize
    connect(this,&MainWidget::sig_sendWindowResize,m_titleBar,&TitleBar::slot_clearAllPopupUi);

    //m_stackWidget_center改变
    connect(m_stackWidget_center,&QStackedWidget::currentChanged,[=](int index){
        m_leftSideBar->slot_setCurrentIndex(index);//左侧边栏跟着改变
        //切换时，hide，有些界面不需要
        if(!ScrollToTop::getInstance()->isHidden())//浏览器界面不需要
        {
            ScrollToTop::getInstance()->hide();
        }
        slot_updateStackWidgetPageData();//更新对应界面数据

    });

    //消息提界面---设置
    connect(MainNotice::getInstance(),&MainNotice::sig_sendSetting,[=](){
        help_stemAboutSetting();//显示设置界面
    });

    //侧边栏有关信号与槽函数处理
    connect(m_leftSideBar,&LeftSideBar::sig_sidebarItemChange,[=](int index)
    {
        slot_setCurrentCenterStackWidget(index);
        m_titleBar->isNecessaryShowSearch(index);//标题栏显示
    });

    //左侧边栏---消息处理
    connect(m_leftSideBar,&LeftSideBar::sig_sendPersonMessage,[=](bool done){
        updateLeftNoticeSliderBar(done);
    });

    //左侧边栏---设置
    connect(m_leftSideBar,&LeftSideBar::sig_sendSetting,[=](bool done){

    });

    //左侧边栏---更多
    connect(m_leftSideBar,&LeftSideBar::sig_sendMore,[=](){

    });

    //左侧边栏控制显示/隐藏的按钮
    connect(m_leftButton,&QPushButton::clicked,[=](){
        slot_on_leftButton_clicked();
//        emit sig_globalResize();
    });


    /**********************热点资讯************************/
    //热点资讯（显示用户信息）
    connect(m_shortVideo,&ShortVideo::sig_sendToUserInfo,[=](const QString& userid){
        m_stackWidget_center->setCurrentWidget(m_personForm);
        m_personForm->slot_showOtherUserInfo(userid);
    });

    //个人主页返回
    connect(m_personForm,&PersonFileForm::sig_sendReturnPage,[=](int numpage){
        m_stackWidget_center->setCurrentWidget(m_shortVideo);
    });

    //热点资讯查找主题视频
    connect(m_shortVideo,SIGNAL(sig_sendTheme(const QString&,int,int)),dataBase::getInstance(),SLOT(video_recDrama_of_theme(const QString&,int,int)));
    //热点视频(接收查找的主题视频)
    connect(dataBase::getInstance(),SIGNAL(sig_sendRecThemeVideocounts(int)),m_shortVideo,SLOT(slot_setCurThemeCounts(int)));//返回数量
    connect(dataBase::getInstance(),SIGNAL(sig_sendRecThemeVideos(QVariant&)),m_shortVideo,SLOT(slot_addShortVideoItem(QVariant&)));//返回相关主题媒体
    //热点资讯(加载推荐视频)
    connect(dataBase::getInstance(),SIGNAL(sig_sendVideoDramaInfo(QVariant&)),m_shortVideo,SLOT(slot_addShortVideoItem(QVariant&)));
    //短视频转到主播放器（777-url集合-url）
    connect(m_shortVideo,&ShortVideo::sig_sendToMainPlayer,MultipPlayer::getInstance(),&MultipPlayer::slot_addTempPlaylist);

    /**********************浮动桌面***************************/
    //桌面歌词关闭
    connect(this,&MainWidget::sig_startCloseAppliction,DesktopLyric::getInstance(),&DesktopLyric::close);

    //桌面歌词---上一首
    connect(DesktopLyric::getInstance(),&DesktopLyric::sig_sendPrevious,[=](){
        MultipPlayer::getInstance()->on_pushButton_previous_clicked();
    });

    //桌面歌词---下一首
    connect(DesktopLyric::getInstance(),&DesktopLyric::sig_sendNext,[=](){
        MultipPlayer::getInstance()->on_pushButton_next_clicked();
    });

    //桌面歌词---暂停、播放
    connect(DesktopLyric::getInstance(),&DesktopLyric::sig_sendPlay,[=](){
        MultipPlayer::getInstance()->on_pushButton_pauseStart_clicked();
    });

    //桌面歌词---回调设置--暂停、播放
    connect(MultipPlayer::getInstance(),&MultipPlayer::sig_currentMediaPlayStatus,[=](bool status){
        DesktopLyric::getInstance()->slot_setCurrentPlayStatus(status);
    });

    //桌面歌词---设置
    connect(DesktopLyric::getInstance(),&DesktopLyric::sig_sendSetting,[=](){
        m_systemSetting->exec();
    });

    //音量递增，递减
    connect(DesktopLyric::getInstance(),&DesktopLyric::sig_sendSound,[=](bool add){
        MultipPlayer::getInstance()->slot_receiveDesktopSoundValueChanged(add);
    });

    /*******************下载选择界面---更多设置****************/
    //文件下载配置
    connect(DownloadType::getInstance(),&DownloadType::sig_sendToconfig,[=](){
        help_stemAboutSetting();
    });

    //标题栏---全局搜索
    connect(m_titleBar,&TitleBar::sig_global_search,[=](QString text){
        m_stackWidget_center->setCurrentWidget(globalFindRlt);
    });

    //全局搜索界面---返回主页
    connect(globalFindRlt,&ResultLists::sig_return_home,[=](){
        m_stackWidget_center->setCurrentWidget(m_cusVideoBox);
    });

    /**********************************标题栏---热词搜索**************************************/
    connect(m_titleBar,&TitleBar::sig_SendToMoreHots,[=](){m_stackWidget_center->setCurrentWidget(m_hotSearch);});

    /*********************************标题栏----用户下线*************************************/
    connect(m_titleBar,&TitleBar::sig_userSign_out,[=](){
        userSignOut();
    });

    //登录
    connect(m_titleBar,&TitleBar::sig_userSign_in,[=](){
        userSignIn();
    });

    //弹幕处登录
    connect(MultipPlayer::getInstance(),&MultipPlayer::sig_userLogin,m_titleBar,&TitleBar::slot_showPersonLogin);

    //返回主界面
    connect(MultipPlayer::getInstance(),&MultipPlayer::sig_showMainForm,this,&MainWidget::tray_showMainWidget);

    //清除临时记录
    connect(m_titleBar,&TitleBar::sig_sendClearTempRecords,[=](){
        m_webRecords->slot_clearUserRecords();//清除6个分栏，1个总栏
        m_webHistory->slot_clearUserRecords();//清除用户历史记录
    });

    /************************************标题栏窗口控制按钮************************************/
    connect(this,&MainWidget::sig_startCloseAppliction,MultipPlayer::getInstance(),&MultipPlayer::slot_closeCurrentWindow);//转到重写事件
    connect(m_titleBar,&TitleBar::sig_winClose,this,&MainWidget::close);//转到重写事件
    connect(m_titleBar,&TitleBar::sig_winNormal,this,&MainWidget::chandleRestoreWindow);//根据不同状态处理窗口
    connect(m_titleBar,&TitleBar::sig_doubleClick,[=](){chandleRestoreWindow();});
    connect(m_titleBar,&TitleBar::sig_winMinimum,[=](){
//        if(!ScrollToTop::getInstance()->isHidden()) ScrollToTop::getInstance()->hide();
        if(!MainNotice::getInstance()->isHidden()) MainNotice::getInstance()->hide();
        this->showMinimized();
    });
    //响应 标题栏 帮助设置发来信号，弹出右键菜单
    connect(m_titleBar,SIGNAL(sig_settingHelpItem(int)),this,SLOT(chandleSetHelpItem(int)));


    /************************************浏览器部分************************************/
    //创建一个新的tab
//    connect(this,&MainWidget::sig_createNewWebTab,m_titleBar,&TitleBar::slot_receiveBlankWebTab);
    //新增历史记录（手动搜索）
    connect(m_titleBar,SIGNAL(sig_sendInputNewUrl(QString)),m_webHistory,SLOT(slot_addToListHistoryWidget(QString)));//添加历史记录
    //可回退
    connect(m_titleBar,SIGNAL(sig_sendCanGoBack()),this,SLOT(slot_canGoBack()));
    connect(this,SIGNAL(sig_canGoBack(bool)),m_titleBar,SLOT(slot_setCanGoBack(bool)));
    //可前进
    //处理浏览器部分发来的信号
    //回车
    connect(m_titleBar,SIGNAL(sig_sendInputNewUrl(QString)),this,SLOT(slot_judgeCurrentBrowserIsActive_load(QString)));
    //后退
    connect(m_titleBar,SIGNAL(sig_sendUrlBack()),this,SLOT(slot_judgeCurrentBrowserIsActive_back()));
    //刷新
    connect(m_titleBar,SIGNAL(sig_sendUrlRefreshen()),this,SLOT(slot_judgeCurrentBrowserIsActive_freshen()));
    //前进
    connect(m_titleBar,SIGNAL(sig_sendUrlAdvance()),this,SLOT(slot_judgeCurrentBrowserIsActive_advance()));
    //返回主页
    connect(m_titleBar,SIGNAL(sig_sendUrlHome()),this,SLOT(slot_judgeCurrentBrowserIsActive_home()));
    connect(m_titleBar,SIGNAL(sig_sendCanForward()),this,SLOT(slot_canGoForward()));
    connect(this,SIGNAL(sig_canGoForward(bool)),m_titleBar,SLOT(slot_setCanGoForward(bool)));
    //上传下载
    connect(m_titleBar,&TitleBar::sig_filesUploadDownLoad,[=](int index1,int index2){
       m_stackWidget_center->setCurrentWidget(m_personForm);//个人信息界面
//       m_personForm->getCurrentShowWidget_TW()->setCurrentIndex(index2);
    });
    //历史记录
    connect(m_titleBar,&TitleBar::sig_historyDownload,[=](int index1,int index2){
        m_stackWidget_center->setCurrentWidget(m_personForm);//个人信息界面
        m_personForm->getCurrentShowWidget_TW()->setCurrentIndex(index2);
    });
    //网页下载请求3
    connect(m_webBrowser->page()->profile(),SIGNAL(downloadRequested(QWebEngineDownloadItem*)),NewWork::getInstance(),SLOT(slot_receiveDownloadRequested(QWebEngineDownloadItem*)),Qt::UniqueConnection);//第五个参数，防止多次请求
    //标题栏---显示当前页面的地址
    connect(m_webBrowser,SIGNAL(urlChanged(QUrl)),m_titleBar,SLOT(setLineEditAddress(QUrl)));
    connect(m_webBrowser,&CusWebBrowser::urlChanged,[=](QUrl url){slot_showLinkOnStatusBar(url.toDisplayString());});
    //鼠标link
    connect(m_webBrowser->page(),&QWebEnginePage::linkHovered,this,&MainWidget::slot_showLinkOnStatusBar);
    //添加一个browser
    connect(m_webBrowser,SIGNAL(sig_sendToNewUrl(QUrl&)),this,SLOT(slot_addToWebTabwidgetBrowser(QUrl&)));// 创建浏览器tab

    //新增历史记录（本页面内浏览器点击链接跳转）
    connect(m_webBrowser,&CusWebBrowser::urlChanged,[=](QUrl url){m_webHistory->slot_addToListHistoryWidget(url);});//添加历史记录
    //新添加的tab页面
    connect(m_webBrowser,&CusWebBrowser::sig_sendToNewUrl,[=](QUrl url){m_webHistory->slot_addToListHistoryWidget(url);});

    //历史记录回显
    connect(m_webHistory,&WebHistory::sig_sendItemText,[=](QString url){
        slot_addToWebTabwidgetBrowser(url);
    });
    //收藏记录回显（两部分的信号）
    connect(m_webRecords,&CollectRecords::sig_sendItemText,[=](QString url){
        slot_addToWebTabwidgetBrowser(url);
    });

    //收藏记录删除（收藏记录发送信号（同时自己、总收藏删除）--->标题栏接收删除item）
    connect(m_webRecords,SIGNAL(sig_sendDeleteItemUrl(QString)),m_titleBar,SLOT(slot_deleteListCollectWidget(QString)));

    connect(m_webBrowser,&CusWebBrowser::loadFinished,[=](){
        qDebug() <<QString::fromLocal8Bit("图标")<<m_webBrowser->icon()<<QString::fromLocal8Bit("标题")<<m_webBrowser->title();
    });
    //标题改变
    connect(m_webBrowser,&CusWebBrowser::titleChanged,[=](const QString &title){
        slot_setCurrentWebBarTitle(m_webTabWidget->indexOf(m_webBrowser),title);
    });
    //图标改变
    connect(m_webBrowser,&CusWebBrowser::iconChanged,[=](const QIcon &icon){
        slot_setCurrentWebBarIcon(m_webTabWidget->indexOf(m_webBrowser),icon);
    });
    //加载网页进度
    connect(m_webBrowser,SIGNAL(loadProgress(int)),m_titleBar,SLOT(slot_setWebProgressBarValue(int)));
    connect(m_webBrowser,SIGNAL(loadProgress(int)),this,SLOT(slot_setWebProgreeBarValue(int)));
    connect(m_webBrowser,SIGNAL(urlChanged(QUrl)),m_titleBar,SLOT(slot_setWebLineEditCurentUrl(QUrl)));

    //tabbar点击改变
    connect(m_webTabWidget,SIGNAL(tabBarClicked(int)),this,SLOT(slot_switchCurrentTab_URL(int)));
    //tab关闭
    connect(m_webTabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(slot_removeTabWidgetTab(int)));


    /************************************浏览器---右键部分处理************************************/
    //网页全屏
    connect(m_titleBar,&TitleBar::sig_sendBrowserFullScreen,[=](){
//        slot_webbrowserShowFullscreen();
    });
    //显示收藏栏
    connect(m_titleBar,&TitleBar::sig_sendBrowserShowCollectRecords,[=](){m_cusTabbar->show(); qDebug() <<"show collectmarks";});
    //显示历史记录
    connect(m_titleBar,&TitleBar::sig_sendBrowserShowHistories,[=](){m_webStackWgt->setCurrentIndex(2);});
    //显示收藏菜单
     connect(m_titleBar,&TitleBar::sig_sendBrowserShowCollectList,[=](){m_webStackWgt->setCurrentIndex(1);});
     //添加空白网页（原意可以关联m_cusTabbar与m_webBrowser，改为sig_sendTabAddWebTabBar触发m_titleBar，中转触发m_webBrowser）
    connect(m_cusTabbar,&CusTabBar::sig_sendTabAddWebTabBar,m_titleBar,&TitleBar::slot_receiveBlankWebTab);
    //此处注意：qt4,qt5写法不能接收信号，只有拉姆达表达式可以，主要还无法区分槽函数（重载的时候）
    connect(m_titleBar,&TitleBar::sig_sendBlankUrl,[=](QString url){
        if(m_stackWidget_center->currentWidget() == m_webStackWgt && m_webStackWgt->currentWidget() == m_webWidget)
        slot_addToWebTabwidgetBrowser(url);
        m_titleBar->slot_clearWebLineEditText();//清除输入框文字（无用）
    });

    /************************************浏览器---收藏栏************************************/
    //收藏记录初始化(收藏栏隐藏部分)
    connect(dataBase::getInstance(),&dataBase::sig_sendRecordInfo,[=](QString nick, QString url,QString createtime){
        m_titleBar->slot_initCollectRecordListWgt(url);
    });
    //收藏菜单---返回按钮
    connect(m_webRecords,&CollectRecords::sig_returnPage,[=](){m_webStackWgt->setCurrentIndex(0);});
    //收藏菜单---修改按钮
//    connect(m_webRecords,&CollectRecords::sig_changeRecord,[=](){WebMessageBox::getInstance()->exec();});
    //标题栏---收藏地址（标题栏已经判断过有效去重后的地址）
    connect(m_titleBar,&TitleBar::sig_sendCollectRecord,[=](QString address){
        QIcon icon = slot_getCurrentBrowserIcon();
        QString title = slot_getCurrentBrowserTitle();
        m_webRecords->slot_addToRecordsListWidget(address,icon,title);
    });
    /************************************浏览器---历史记录栏************************************/
    //历史记录初始化
    connect(dataBase::getInstance(),&dataBase::sig_sendHisRecordInfo,[=](QString url,QString createtime){
        m_webHistory->slot_initHistoryRecordListWgt(url,createtime);
    });
    //历史记录---返回按钮
    connect(m_webHistory,&WebHistory::sig_returnPage,[=](){m_webStackWgt->setCurrentIndex(0);});
     //标签栏---展开收藏菜单
    connect(m_cusTabbar,&CusTabBar::sig_sendTabShowRecords,[=](){m_webStackWgt->setCurrentIndex(1);});

    /************************************浏览器---添加记录消息窗口************************************/


    /************************************主窗口关闭关联窗口动作************************************/
    //收到主窗口关闭信号(两种行为：隐藏 0 关闭 1)
//    connect(m_pExitDlg,&ExitDialog::sig_SendcloseMain,[=](bool close){
//        if(close)//直接关闭(双重检测)
//        {
//            m_isClose = true;
//        }
//        else
//        {
//            m_isClose = false;
//        }
//    });//确定关闭，需要做一些数据保存
//    //没收到主窗口关闭信号
//    connect(m_pExitDlg,&ExitDialog::sig_SendNotcloseMain,[=](){m_isClose = false;});//不关闭，数据暂时就不保存

    //关闭主窗口，先通知标题栏，再转发登录窗口关闭
    connect(this,&MainWidget::sig_startCloseAppliction,m_titleBar,&TitleBar::receiveMainFormClose);

    connect(this,SIGNAL(sig_winStatus(bool)),m_titleBar,SLOT(chandleMainWinStatus(bool)));//标题栏处理不同状态下样式
    //空白页---打开文件
    connect(m_videoBlank,&VideoBlank::sig_openLocalFile,[=]()
    {
        MultipPlayer::getInstance()->slot_openLocalFile();
//        MultipPlayer::getInstance()->show();
    });


    /************************************托盘+浮动控制界面---信号处理************************************/
    //播放次序选择界面接收信号
    connect(this,SIGNAL(sig_trayPlayOrder(int)),PlayOrderForm::getInstance(),SLOT(clearAndSetButtonCheckedStatus(int)));
    //接收播放次序选择界面发送过来信号
    connect(PlayOrderForm::getInstance(),SIGNAL(sig_playerOrder(int)),this,SLOT(tray_setCurrentPlayOrderStatus(int)));
    //托盘---上一首
    connect(m_systemTray,SIGNAL(sig_playStatusPrevious()),MultipPlayer::getInstance(),SLOT(on_pushButton_previous_clicked()));
    //浮动控制---上一首
    connect(FloatPlayCtl::getInstance(),SIGNAL(sig_sendPlayPrevious()),MultipPlayer::getInstance(),SLOT(on_pushButton_previous_clicked()));

    //托盘---下一首
    connect(m_systemTray,SIGNAL(sig_playStatusNext()),MultipPlayer::getInstance(),SLOT(on_pushButton_next_clicked()));
    //浮动控制---下一首
    connect(FloatPlayCtl::getInstance(),SIGNAL(sig_sendPlayNext()),MultipPlayer::getInstance(),SLOT(on_pushButton_next_clicked()));

    //01-播放器主界面---接收播放器发送的播放/暂停
//    connect(MultipPlayer::getInstance(),SIGNAL(sig_currentMediaPlayStatus(bool)),MultipPlayer::getInstance(),SLOT(slot_setPlayStatusStyle_main(bool)));
    //02-托盘---接收播放器发送的播放/暂停
    connect(MultipPlayer::getInstance(),SIGNAL(sig_currentMediaPlayStatus(bool)),m_systemTray,SLOT(slot_setCurrentPlayStatus(bool)));
    //03-浮动控制---接收播放器发送的播放/暂停
    connect(MultipPlayer::getInstance(),SIGNAL(sig_currentMediaPlayStatus(bool)),FloatPlayCtl::getInstance(),SLOT(slot_setCurrentPlayStatus(bool)));

    //托盘---播放/暂停
    connect(m_systemTray,SIGNAL(sig_playStatusPause(bool)),MultipPlayer::getInstance(),SLOT(on_pushButton_pauseStart_clicked()));
    //浮动控制---播放/暂停
    connect(FloatPlayCtl::getInstance(),SIGNAL(sig_sendPlayStartPause()),MultipPlayer::getInstance(),SLOT(on_pushButton_pauseStart_clicked()));

    //托盘---音量值改变-->播放界面值改变
    connect(m_systemTray,SIGNAL(sig_playProgressValue(int)),MultipPlayer::getInstance(),SLOT(slot_receiveSystemTraySendSoundValue(int)));
    //浮动控制---音量值改变-->播放界面值改变
    connect(FloatPlayCtl::getInstance(),SIGNAL(sig_sendProgress_voice(int)),MultipPlayer::getInstance(),SLOT(slot_receiveSystemTraySendSoundValue(int)));

    //托盘---静音按钮
    connect(m_systemTray,SIGNAL(sig_playStatusMuted(bool)),MultipPlayer::getInstance(),SLOT(slot_setCurrentMediaMuted()));
    //浮动控制---静音按钮
    connect(FloatPlayCtl::getInstance(),SIGNAL(sig_sendPlayMute(bool)),MultipPlayer::getInstance(),SLOT(slot_setCurrentMediaMuted()));
    //托盘---静音样式改变
    connect(MultipPlayer::getInstance(),SIGNAL(sig_playerIsMutedStatus(bool)),m_systemTray,SLOT(slot_setCurrentMediaMutedStyleSheet(bool)));
    //浮动控制---静音样式改变
    connect(MultipPlayer::getInstance(),SIGNAL(sig_playerIsMutedStatus(bool)),FloatPlayCtl::getInstance(),SLOT(slot_setCurrentMediaMutedStyleSheet(bool)));
    //托盘action组
    connect(m_actionGroup,&QActionGroup::triggered,[=](QAction *action)
    {
        tray_getCurrentPlayOrder(action);//发送信号
        tray_setCurrentPlayOrderStatus(action);
    });

    //播放主界面----》浮动窗口倍速设置

    //浮动窗口--发送弹幕（开关）
    connect(FloatPlayCtl::getInstance(),&FloatPlayCtl::sig_sendOpenDanmu,[=](bool on){
        MultipPlayer::getInstance()->slot_setDanmuOpenClose(on);
    });

    //播放器窗口--》浮动窗口接收播放器控制开关（开关）
    connect(MultipPlayer::getInstance(),&MultipPlayer::sig_videoDanmuStatus,[=](bool on){
        FloatPlayCtl::getInstance()->slot_setDanmuOn(on);
    });

    //浮动窗口--发送弹幕
    connect(FloatPlayCtl::getInstance(),&FloatPlayCtl::sig_sendDanmuText,[=](QString danmuText){
            MultipPlayer::getInstance()->slot_sendDanmuTextToScreen(danmuText);
    });

    /************************************播放器部分信号处理************************************/
    //接收播放器关闭
    connect(MultipPlayer::getInstance(),&MultipPlayer::sig_mainPlayerClose,[=](bool open){
        if(MultipPlayer::getInstance() != nullptr)
        {
            MultipPlayer::getInstance()->close();//实际没有删除，需要手动delete
        }
        if(open)//外部文件触发主播放器播放，但是主界面从未打开
        {
            this->close();
        }
        else//外部文件触发主播放器播放，且主界面已经打开
        {
            //不作处理
        }
    });


    //接收主界面（实际是音量界面发过来的值，做了中转）的音量值
    connect(MultipPlayer::getInstance(),SIGNAL(sig_currentMediaSoundValueChange(int)),m_systemTray,SLOT(slot_setCurrentPlaySoundValue(int)));
    //浮动控制---接收音量值改变（01.主界面调节 02.托盘调节）
    connect(MultipPlayer::getInstance(),SIGNAL(sig_currentMediaSoundValueChange(int)),FloatPlayCtl::getInstance(),SLOT(slot_setProgressbar_voice(int)));

    //MusicPlaylist显示数据(参数：QString--->QString)
//    connect(MultipPlayer::getInstance(),&MultipPlayer::sig_sendToMusicList,m_musicList,&MusicPlaylist::addFileInfoToListView);
    connect(MultipPlayer::getInstance(),&MultipPlayer::sig_sendToMusicList,[=](){
        if(dataBase::getInstance()->getSqlDataBase().isOpen())
           m_musicList->addFileInfoToListView();
    });
    //播放列表界面传来播放歌曲的信息
    connect(m_musicList,&MusicPlaylist::sig_selectRowIndex,[=](QModelIndex index)
    {
        QString name_song = index.data().toString();
        qDebug()<<name_song;
    });
}

void MainWidget::setInstallEventFilter()
{
    this->installEventFilter(this);
    m_webTabWidget->installEventFilter(this);
    m_stackWidget_center->installEventFilter(this);
}

//更新新增网页按钮的位置
void MainWidget::updateAddWebButtonPosition()
{
    //count:从1开始；
//    qDebug() << QString::fromLocal8Bit("插入的序号：") << m_webTabWidget->count();
//    QWidget *button = m_webTabWidget->tabBar()->tabButton(m_webTabWidget->count()-1,QTabBar::RightSide);
//    m_webTabWidget->tabBar()->setTabButton(m_webTabWidget->count()-1,QTabBar::RightSide,button);
}

/*槽函数：托盘菜单*/
void MainWidget::createTrayMenu()
{
    m_menuTray = new QMenu(this);
    m_menuTray->setWindowFlag(Qt::FramelessWindowHint);
    m_menuTray->setAttribute(Qt::WA_TranslucentBackground);
    m_menuTray->setWindowFlag(Qt::NoDropShadowWindowHint);
    m_menuTray->setObjectName(QString::fromLocal8Bit("m_menuTray"));//设置样式用
    m_systemTray = new SystemTray(this);//必须new 出来，不能获取单例方式
    m_playMode = new  QMenu(QString::fromLocal8Bit("播放模式"));
    m_playMode->setWindowFlag(Qt::FramelessWindowHint);
    m_playMode->setAttribute(Qt::WA_TranslucentBackground);
    m_playMode->setWindowFlag(Qt::NoDropShadowWindowHint);
    m_playMode->setObjectName(QString::fromLocal8Bit("m_playMode"));
    m_playMode->setIcon(QIcon("://images/tray/tray_playmode.png"));
    m_actionGroup = new QActionGroup(this);
    m_actionGroup->setExclusive(true);
    m_actionGroup->setObjectName(QString::fromLocal8Bit("m_actionGroup"));
    QAction *onceAction = new QAction(QString::fromLocal8Bit("单曲循环"));
    onceAction->setCheckable(true);
    QAction *sequAction = new QAction(QString::fromLocal8Bit("顺序播放"));
    sequAction->setCheckable(true);
    QAction *loopAction = new QAction(QString::fromLocal8Bit("循环播放"));
    loopAction->setCheckable(true);
    loopAction->setChecked(true);//默认循环播放
    QAction *rankAction = new QAction(QString::fromLocal8Bit("随机播放"));
    rankAction->setCheckable(true);
    m_playMode->addAction(onceAction);
    m_playMode->addAction(sequAction);
    m_playMode->addAction(loopAction);
    m_playMode->addAction(rankAction);
    //使用组容器以便达到互斥
    m_actionGroup->addAction(onceAction);
    m_actionGroup->addAction(sequAction);
    m_actionGroup->addAction(loopAction);
    m_actionGroup->addAction(rankAction);

    QWidgetAction *wgtAction = new QWidgetAction(m_menuTray);//还可以子类化QWidgetAction，paintEvent()重绘
    wgtAction->setDefaultWidget(m_systemTray);//添加自定义的widget_menu

    m_menuTray->addAction(wgtAction);
    m_menuTray->addAction(QIcon("://images/tray/tray_home.png"),QString::fromLocal8Bit("显示主界面"),this,SLOT(tray_showMainWidget()));
    m_menuTray->addMenu(m_playMode);//添加 子菜单 播放模式
    m_menuTray->addAction(QIcon("://images/tray/tray_lyric.png"),QString::fromLocal8Bit("显示桌面歌词"),this,SLOT(tray_showDesktopLyric()));
    m_menuTray->addSeparator();
    m_menuTray->addAction(QIcon("://images/tray/tray_setting.png"),QString::fromLocal8Bit("系统设置"),this,SLOT(tray_systemSettting()));
    m_menuTray->addAction(QIcon("://images/tray/tray_upgrade.png"),QString::fromLocal8Bit("在线升级"),this,SLOT(tray_onlineUpgrade()));//注意消息阻塞
    m_menuTray->addAction(QIcon("://images/tray/tray_logout.png"),QString::fromLocal8Bit("登录账号"),this,SLOT(tray_systemLogout()));
    m_menuTray->addSeparator();
    m_menuTray->addAction(QIcon("://images/tray/tray_exit.png"),QString::fromLocal8Bit("退出软件"),this,SLOT(tray_systemExitSoftware()));
    m_tray->setContextMenu(m_menuTray);//这样写自动显示在m_tray鼠标点击的地方
}

/*处理设置按钮菜单发过来的信号*/
void MainWidget::chandleSetHelpItem(int index)
{
    if(index == 0)//个人账户
    {
        qDebug() << "person login";
        m_stackWidget_center->setCurrentWidget(m_personForm);
    }
    else if(index == 1)//系统设置
    {
        help_stemAboutSetting();
    }
    else if(index == 2)//网络资源
    {
        qDebug() << "network source";
    }
    else if(index == 3)//问题帮助
    {
        help_questionAnswer();
    }
    else if(index == 4)//本地视频
    {
        help_aboutLocalFile();
    }
    else if(index == 5)//网络视频
    {
        help_aboutNetworklFile();
    }
    else if(index == 6)//软件下载
    {
        help_openWebSite();
    }
    else if(index == 7)//软件退出
    {
        this->close();
    }
    else
    {
        return;
    }
}

/*系统设置*/
void MainWidget::help_stemAboutSetting()
{
    m_systemSetting->exec();
}

/*问题帮助*/
void MainWidget::help_questionAnswer()
{
    QMessageBox::information(this,QString::fromLocal8Bit("问题帮助"),QString::fromLocal8Bit("为当前系统进行问题帮助。"));
}

/*门户网站*/
void MainWidget::help_openWebSite()
{
    QDesktopServices::openUrl(QUrl(QString("https://v.qq.com/biu/download#Windows")));
}

/*播放本地文件*/
void MainWidget::help_aboutLocalFile()
{
    if(MultipPlayer::getInstance())
    {
        if(MultipPlayer::getInstance()->isHidden())
        {
            MultipPlayer::getInstance()->slot_setMainCurrentIndex(0);//视频播放界面
            MultipPlayer::getInstance()->show();//只显示播放器界面
        }
        else
        {
            MultipPlayer::getInstance()->show();
        }
    }
}

/*播放网络资源*/
void MainWidget::help_aboutNetworklFile()
{
    qDebug() <<"PLAY NETWORK RESOURCE";
    MultipPlayer::getInstance()->show();
    MultipPlayer::getInstance()->slot_setVideTitleBar(1);//转到网络播放标题栏
}

void MainWidget::slot_canGoForward()
{
    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
    if(actWdgt->page()->history()->canGoForward())
    {
        emit sig_canGoForward(true);
    }
    else
    {
        emit sig_canGoForward(false);
    }
}

void MainWidget::slot_canGoBack()
{
    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
    if(actWdgt->page()->history()->canGoBack())
    {
        emit sig_canGoBack(true);
    }
    else
    {
        emit sig_canGoBack(false);
    }
}

//显示link
void MainWidget::slot_showLinkOnStatusBar(const QString &text)
{
    m_statusBar->showMessage(text);
}

/*私有槽函数：显示主界面*/
void MainWidget::tray_showMainWidget()
{
    if(this->isHidden())
    {
        this->showNormal();
    }
    else if(this->isMinimized())
    {
        this->showNormal();
    }
    qDebug() << "this is show main  UI ";
}

void MainWidget::tray_showDesktopLyric()
{
    DesktopLyric::getInstance()->show();
}

void MainWidget::tray_systemSettting()
{
    help_stemAboutSetting();
}

void MainWidget::tray_onlineUpgrade()
{
//    QMessageBox::information(this,QString::fromLocal8Bit("更新提示"),QString::fromLocal8Bit("请前往官网下载更新！"));
    Updater::getInstance()->exec_();
}

void MainWidget::tray_systemLogout()
{
    QAction *action = qobject_cast<QAction *>(sender());
    qDebug() << action->text();
    if(action->text() == QString::fromLocal8Bit("退出登录"))
    {
        userSignOut();
    }
    else if(action->text() == QString::fromLocal8Bit("登录账号"))
    {
//        m_titleBar->showLoginForm();
        NewLoginForm::getInstance()->show_c();
        userSignIn();
    }
}

void MainWidget::tray_systemExitSoftware()
{
    this->close();
}

void MainWidget::tray_setCurrentPlayOrderStatus(QAction *sendAction)
{
    sendAction->setChecked(true);
    qDebug() << sendAction->text();
}

void MainWidget::tray_setCurrentPlayOrderStatus(int index)
{
    m_actionGroup->actions().at(index-1)->setChecked(true);//互斥组内相互互斥，前提是设置checkable
}

bool MainWidget::tray_setUserLoginStatusText(const QString &previous, const QString &current)
{
    QList<QAction*> action_tray = m_menuTray->actions();
    foreach (QAction* action, action_tray)
    {
        if(action->text() == previous)
        {
            action->setText(current);
            return true;
        }
    }
}


void MainWidget::tray_getCurrentPlayOrder(QAction *sendAction)
{
    int num = 0;
    if(sendAction->text() == QString::fromLocal8Bit("单曲循环"))
    {
        num = 1;
    }
    else if(sendAction->text() == QString::fromLocal8Bit("顺序播放"))
    {
        num = 2;
    }
    else if(sendAction->text() == QString::fromLocal8Bit("循环播放"))
    {
        num = 3;
    }
    else if(sendAction->text() == QString::fromLocal8Bit("随机播放"))
    {
        num = 4;
    }
    emit sig_trayPlayOrder(num);
    qDebug() << "play order  = " << num;
}

/*设置全局tooltip*/
void MainWidget::setGlobalToolTip()
{

}

void MainWidget::userSignIn()
{
    tray_setUserLoginStatusText(QString::fromLocal8Bit("登录账号"),QString::fromLocal8Bit("退出登录"));
}

void MainWidget::userSignOut()
{
    m_titleBar->slot_clearColletRecords();//标题栏清除收藏,搜索历史
    m_webRecords->slot_clearUserRecords();//清除6个分栏，1个总栏
    m_webHistory->slot_clearUserRecords();//清除用户历史记录
    tray_setUserLoginStatusText(QString::fromLocal8Bit("退出登录"),QString::fromLocal8Bit("登录账号"));
    dataBase::getInstance()->login_setLoginStatus(0);//设置用户状态 -- 下线
    MultipPlayer::getInstance()->slot_clearRecItemLists();//清空推荐列表
}

void MainWidget::updateWebAddButtonGeometry()
{
    qDebug() << QString(u8"tabBar的宽度：")<<m_webTabWidget->tabBar()->width();
    int width   = m_webTabWidget->width() - m_webTabWidget->tabBar()->width() - 1;
    QRect rect  = QRect(0,0,m_webTabWidget->rect().width() - m_webTabWidget->tabBar()->width() - 30,26);
    sparcer_item->setGeometry(rect);
    qDebug() << QString::fromLocal8Bit("webTab剩余宽度：")<<width;
}

void MainWidget::updateWinTitleBarButtons()
{
    if(isMaximized())//如果最大化
    {
        emit sig_winStatus(false);
    }
    else//没有最大化
    {
        emit sig_winStatus(true);
    }
}

void MainWidget::updateLeftNoticeSliderBar(bool show)
{
    MainNotice::getInstance()->setMinimumSize(0,0);
    const int slider_x = m_leftSideBar->parentWidget()->mapToGlobal(m_leftSideBar->pos()).x();
    const int slider_y = m_leftSideBar->parentWidget()->mapToGlobal(m_leftSideBar->pos()).y();
    qDebug() << QString(u8"MainNotice::getInstance()是否隐藏：") << MainNotice::getInstance()->isHidden();
    if(MainNotice::getInstance()->isHidden())
    {
        qDebug() << "start animation";
//            MainNotice::getInstance()->setGeometry(slider_x + m_leftSideBar->width(),
//                                                   slider_y,
//                                                   MainNotice::getInstance()->width(),
//                                                   m_leftSideBar->height());
//        MainNotice::getInstance()->raise();
        MainNotice::getInstance()->show();//必须show出来，否则看不到动画
        QPropertyAnimation *pAnimation = new QPropertyAnimation(MainNotice::getInstance(),"geometry",this);
        pAnimation->setDuration(800);
//        pAnimation->setStartValue(QRect(slider_x + m_leftSideBar->width(),slider_y,0,m_leftSideBar->height()));
//        pAnimation->setEndValue(QRect(slider_x + m_leftSideBar->width(),slider_y,400,m_leftSideBar->height()));
//        pAnimation->setEasingCurve(QEasingCurve::OutQuad);//一般使用setKeyValueAt不要设置曲线
//        pAnimation->setKeyValueAt(0,QPoint(slider_x,slider_y));
//        pAnimation->setKeyValueAt(1,QPoint(slider_x + m_leftSideBar->width(),slider_y));
        pAnimation->setKeyValueAt(0,QRect(slider_x + m_leftSideBar->width(),slider_y,400,0));
        pAnimation->setKeyValueAt(1,QRect(slider_x + m_leftSideBar->width(),slider_y,400,m_leftSideBar->height()));
        pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    }
    else
    {
        qDebug() << "stop animation";
        qDebug() << MainNotice::getInstance()->pos();

        QPropertyAnimation *pAnimation = new QPropertyAnimation(MainNotice::getInstance(),"geometry",this);
        pAnimation->setDuration(800);
//        pAnimation->setStartValue(QRect(slider_x + m_leftSideBar->width(),slider_y,400,m_leftSideBar->height()));
//        pAnimation->setEndValue(QRect(slider_x + m_leftSideBar->width(),slider_y,0,m_leftSideBar->height()));
//        pAnimation->setEasingCurve(QEasingCurve::Linear);
//        pAnimation->setKeyValueAt(0,QPoint(slider_x + m_leftSideBar->width(),slider_y));
//        pAnimation->setKeyValueAt(1,QPoint(slider_x,slider_y));
        pAnimation->setKeyValueAt(0,QRect(slider_x + m_leftSideBar->width(),slider_y,400,m_leftSideBar->height()));
        pAnimation->setKeyValueAt(1,QRect(slider_x + m_leftSideBar->width(),slider_y + m_leftSideBar->height(),400,0));
        pAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        QTimer::singleShot(1000,0,[=](){MainNotice::getInstance()->close();});//先让动画演完，再关闭
    }
}

void MainWidget::updateRightScrollToTop()
{
    //可以采用设置父亲是用相对坐标来更新2023-02-05
//        ScrollToTop::getInstance()->setGeometry(this->pos().x() + width() - ScrollToTop::getInstance()->width()-15,
//                                                this->pos().y() + height() - ScrollToTop::getInstance()->height()-40,
//                                                ScrollToTop::getInstance()->width(),
//                                                ScrollToTop::getInstance()->height());
        ScrollToTop::getInstance()->move(this->width() - ScrollToTop::getInstance()->width() - 15,
                                         this->height() - ScrollToTop::getInstance()->height() - 15);
}

void MainWidget::connectToTopWidget(CToTopWidget *widget)
{
    //置顶按钮合适的出现或消失
    connect(widget,&CToTopWidget::sig_scroll_verticalbar,[=](bool s){
        slot_update_R_B_geometry(s);
    });
    //置顶
    connect(ScrollToTop::getInstance(),&ScrollToTop::sig_sendToTop,[=](){
        widget->setScrollBarToTop();
//        ScrollToTop::getInstance()->raise();
        ScrollToTop::getInstance()->show();//提升层次
    });
    //刷新
    connect(ScrollToTop::getInstance(),&ScrollToTop::sig_sendToFlush,[=](){
        RingWait1::getInstance()->move(this->width()/2 - RingWait1::getInstance()->width()/2,
                                       this->height()/2 - RingWait1::getInstance()->height()/2);
        RingWait1::getInstance()->raise();
        RingWait1::getInstance()->show();

        //手动显示出来，不被隐藏
//        ScrollToTop::getInstance()->raise();
        ScrollToTop::getInstance()->show();//提升层次

        QTimer::singleShot(2000,0,[=](){
        RingWait1::getInstance()->close();
        });
    });
}

void MainWidget::slot_updateStackWidgetPageData()
{
    QWidget* page = m_stackWidget_center->currentWidget();
    //以下添加一些数据更新操作
    if(page == m_cusVideoBox)
    {
        qDebug(u8"当前及显示界面：m_cusVideoBox");
    }
    else if(page == m_cusVideoBox2)
    {
        qDebug(u8"当前及显示界面：m_cusVideoBox2");
    }
    else if(page == m_cusVideoBox3)
    {
        qDebug(u8"当前及显示界面：m_cusVideoBox3");
    }
    else if(page == m_cusVideoBox4)
    {
        qDebug(u8"当前及显示界面：m_cusVideoBox4");
    }
    else if(page == m_cusVideoBox5)
    {
        qDebug(u8"当前及显示界面：m_cusVideoBox5");
    }
    else if(page == videoFindResult)
    {
        qDebug(u8"当前及显示界面：videoFindResult");
    }
    else if(page == m_videoMember)
    {
        qDebug(u8"当前及显示界面：m_videoMember");
    }
    else if(page == m_webStackWgt)
    {
        qDebug(u8"当前及显示界面：m_webStackWgt");
    }
    else if(page == m_hotSearch)
    {
        qDebug(u8"当前及显示界面：m_hotSearch");
    }
    else if(page == m_songlistSort)
    {
        qDebug(u8"当前及显示界面：m_songlistSort");
    }
    else if(page == m_shortVideo)
    {
        m_shortVideo->slot_setVideoMediaType(dataBase::getInstance()->getVideoMediaType());//获取视频类型
        qDebug(u8"当前及显示界面：m_shortVideo");
    }
    else if(page == m_musicList)
    {
        qDebug(u8"当前及显示界面：m_musicList");
    }
    else if(page == m_personForm)
    {
        qDebug(u8"当前及显示界面：m_personForm");
    }
    else if(page == m_fileTrans)
    {
        qDebug(u8"当前及显示界面：m_fileTrans");
    }
    else if(page == m_cusVideoBox6)
    {
        qDebug(u8"当前及显示界面：m_cusVideoBox6");
    }
    else if(page == m_cusVideoBox7)
    {
        qDebug(u8"当前及显示界面：m_cusVideoBox7");
    }
    else if(page == globalFindRlt)
    {
        qDebug(u8"当前及显示界面：globalFindRlt");
    }
}

void MainWidget::slot_activeTray(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::DoubleClick:
    {
//        m_tray->showMessage("Information",//消息窗口标题
//                            "There is a new message!",//消息内容
//                            QSystemTrayIcon::MessageIcon::Information,//消息窗口图标
//                            5000);//消息窗口显示时长
    }
        break;
    case QSystemTrayIcon::Trigger:
    {
        this->showNormal();
    }
        break;
    case QSystemTrayIcon::Context:
//        m_menuTray->show();
        break;
    }
}

void MainWidget::slot_update_R_B_geometry(bool on)
{
    if(on)
    {
        ScrollToTop::getInstance()->scrollToTopShow();
        updateRightScrollToTop();//按照不隐藏2个的位置计算
    }
    else
    {
        ScrollToTop::getInstance()->scrollToTopHide();
        updateRightScrollToTop();//按照隐藏1个的位置计算
    }
}

void MainWidget::slot_setWebProgreeBarValue(int value)
{
    opacity->setOpacity(1);//恢复透明度值
    m_progressBar->setValue(value);
    if(value == 100)
        slot_resetWebProgressBarValue();
}

void MainWidget::slot_resetWebProgressBarValue()
{
    opacity->setOpacity(0.5); //设置透明度0.5,透明范围：[0,1]
    m_progressBar->setGraphicsEffect(opacity);//应用到需要透明变化的控件；
    //使用属性动画类让控件在透明度范围内变化
    QPropertyAnimation *opacityAnimation = new QPropertyAnimation(opacity,"opacity",m_progressBar);//Opacity代表属性（透明度）
    opacityAnimation->setDuration(2000); //动效时长2s
    opacityAnimation->setStartValue(1);//Opacity(透明度)开始值
    opacityAnimation->setEndValue(0);//结束值
    opacityAnimation->start();//停止时删除动画QAbstractAnimation::DeleteWhenStopped
    connect(opacityAnimation,&QPropertyAnimation::finished,[=](){
    opacityAnimation->deleteLater();
    });
}


/*私有槽函数：点击tabbar,转化到当前的索引界面*/
void MainWidget::slot_switchCurrentTab_URL(int index)
{
    CusWebBrowser* widget = qobject_cast<CusWebBrowser *>(m_webTabWidget->widget(index));
//    qDebug() << widget->objectName();
//    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
    if(widget != nullptr)
    {
        m_titleBar->slot_setWebLineEditCurentUrl(widget->url());//删除显示最新的tab的URL
//        delete widget;
    }
    else
    {
        return;
    }
}

/*设置可用不可用*/
void MainWidget::slot_setCurrentTabWidgetEnable()
{
    for(int i = 0; i < m_webTabWidget->count(); i++)
    {
        CusWebBrowser* widget = qobject_cast<CusWebBrowser *>(m_webTabWidget->widget(i));
        widget->setEnabled(false);//非活动控件，设置为false
    }
    CusWebBrowser* widget = qobject_cast<CusWebBrowser *>(m_webTabWidget->currentWidget());
    if(widget != nullptr)
    {
        widget->setEnabled(true);//设置当前活跃的可用
        qDebug() <<QString::fromLocal8Bit("当前已设置为可用控件");
    }
    else
    {
        return;
    }
}

//web设置标题
void MainWidget::slot_setCurrentWebBarTitle(int index, const QString &title)
{
    if(title.isNull())
    {
        m_webTabWidget->setTabText(index,QString::fromLocal8Bit("新标题页"));
    }
    else
    {
        m_webTabWidget->setTabText(index,title);
        m_webTabWidget->setTabToolTip(index,title);
        qDebug() << QString(u8"标题以改变！")<<title;
    }
}

//web设置图标
void MainWidget::slot_setCurrentWebBarIcon(int index, const QIcon &icon)
{
    if(icon.isNull())
    {
        m_webTabWidget->setTabIcon(index,QIcon("://images/icon/engine.png"));
    }
    else
    {
        m_webTabWidget->setTabIcon(index,icon);
    }
}

/*删除某个tab后，标题栏显示URL*/
void MainWidget::slot_setRemoveTabLineEditText(int index)
{
    Q_UNUSED(index);
    CusWebBrowser* widget = qobject_cast<CusWebBrowser *>(m_webTabWidget->currentWidget());
    if(widget != nullptr)
    {
        m_titleBar->slot_setWebLineEditCurentUrl(widget->url());
    }
    else
    {
        return;
    }
}

//左侧边栏点击判断
void MainWidget::slot_on_leftButton_clicked()
{
    //隐藏设为宽度为1
    if(m_isHide)
    {
        m_stackWidget_left->show();//左侧边栏
        updateLeftButtonGeometry();
        setLeftButtonStyleSheetStatus();
        m_leftButton->hide();
    }
    else
    {
        m_stackWidget_left->hide();
        updateLeftButtonGeometry();
        setLeftButtonStyleSheetStatus();
        m_leftButton->hide();
    }
    m_isHide = !m_isHide;//状态置反
//    this->move(this->geometry().x()-1,this->geometry().y()-1);

}

//更新左侧边栏按钮样式
void MainWidget::setLeftButtonStyleSheetStatus()
{
    if(!m_isHide)
    {
        m_leftButton->setStyleSheet("QPushButton{background:rgba(81,81,81,0.3) url(:/images/icon/arrow_left.png) no-repeat center center;border:none;}");
    }
    else
    {
        m_leftButton->setStyleSheet("QPushButton{background:rgba(81,81,81,0.3) url(:/images/icon/arrow_right.png) no-repeat center center;border:none;}");
    }
}

//更新左侧边栏按钮位置
void MainWidget::updateLeftButtonGeometry()
{
    m_leftButton->setGeometry(0,
                              m_stackWidget_center->height()/2 - m_leftButton->height()/2 - 50,
                              25,50);
    m_leftButton->raise();
}

/*处理窗口还原*/
void MainWidget::chandleRestoreWindow()
{
        if(!m_winMax)//非最大化
        {
            this->showMaximized();
            emit sig_winStatus(m_winMax);//向标题栏发送最大化状态信号
        }
        else
        {
            this->showNormal();
            emit sig_winStatus(m_winMax);//向窗口发送正常状态信号
        }
        m_winMax = !m_winMax;
}


/*析构函数*/
MainWidget::~MainWidget()
{
//    if(m_webBrowser != nullptr)
//    {
//        delete m_webBrowser;
//        m_webBrowser = nullptr;
//    }

//    if(m_musicList != nullptr)
//    {
//        delete m_musicList;
//        m_musicList = nullptr;
//    }

//    if(m_shortVideo != nullptr)
//    {
//        delete m_shortVideo;
//        m_shortVideo = nullptr;
//    }

//    if(m_musicList != nullptr)
//    {
//        delete m_musicList;
//        m_musicList = nullptr;
//    }
//    if(m_tabWidget != nullptr)
//    {
//        delete m_tabWidget;
//        m_tabWidget = nullptr;
//    }

//    if(m_videoBlank != nullptr)
//    {
//        delete m_videoBlank;
//        m_videoBlank = nullptr;
//    }

//    if(m_cusVideoBox != nullptr)
//    {
//        delete m_cusVideoBox;
//        m_cusVideoBox = nullptr;
//    }

//    if(m_cusVideoBox2 != nullptr)
//    {
//        delete m_cusVideoBox2;
//        m_cusVideoBox2 = nullptr;
//    }

}

//bool MainWidget::nativeEvent(const QByteArray &eventType, void *message, long *result)
//{
//    Q_UNUSED(eventType)
//    MSG* param = static_cast<MSG*>(message);
//       switch (param->message)
//       {
//       case WM_NCHITTEST:
//       {
//           int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
//           int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();

//           // 如果鼠标位于子控件上，则不进行处理
//           if(nX > MARWIDTH && nX <this->width() - MARWIDTH &&
//                   nY > MARWIDTH && nY < this->height() - MARWIDTH)
//           {
//               if (childAt(nX, nY) != nullptr)
//                   return QWidget::nativeEvent(eventType, message, result);
//           }

//           // 鼠标区域位于窗体边框，进行缩放
//           if ((nX > 0) && (nX < MARWIDTH))//左边
//               *result = HTLEFT;

//           if ((nX > this->width() - MARWIDTH) && (nX < this->width()))
//               *result = HTRIGHT;

//           if ((nY > 0) && (nY < MARWIDTH))//上边
//               *result = HTTOP;

//           if ((nY > this->height() - MARWIDTH) && (nY < this->height()))
//               *result = HTBOTTOM;

//           if ((nX > 0) && (nX < MARWIDTH) && (nY > 0)
//                   && (nY < MARWIDTH))
//               *result = HTTOPLEFT;

//           if ((nX > this->width() - MARWIDTH) && (nX < this->width())
//                   && (nY > 0) && (nY < MARWIDTH))
//               *result = HTTOPRIGHT;

//           if ((nX > 0) && (nX < MARWIDTH)
//                   && (nY > this->height() - MARWIDTH) && (nY < this->height()))
//               *result = HTBOTTOMLEFT;

//           if ((nX > this->width() - MARWIDTH) && (nX < this->width())
//                   && (nY > this->height() - MARWIDTH) && (nY < this->height()))
//               *result = HTBOTTOMRIGHT;

////           updateWinTitleBarButtons();//判断是否最大化
//           return true;
//           }
//       }
//       return QWidget::nativeEvent(eventType,message,result);
//}

/*事件过滤器*/
bool MainWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)//捕捉事件和重写事件是不一样的
    {
        if(event->type() == QEvent::Move)
        {
            MainNotice::getInstance()->hide();
            RingWait1::getInstance()->hide();
        }
    }
    if(watched == m_stackWidget_center)
    {
        if(event->type() == QEvent::Enter)
        {
//            updateLeftButtonGeometry();
//            setLeftButtonStyleSheetStatus();
//            m_leftButton->show();
            setCursor(Qt::ArrowCursor);
        }
        else if(event->type() == QEvent::Leave)
        {
//            m_leftButton->hide();
        }
    }
    if(watched == m_webTabWidget)
    {
        if(event->type() ==  QEvent::Resize)
        {
//            updateWebAddButtonGeometry();
//            qDebug() << QString(u8"m_webTabWidget尺寸变了");
        }
    }
//    if(watched == m_tray)
//    {
//        if(event->type() == QEvent::Enter)
//        {
//            qDebug() << QString(u8"m_tray enter!");
//            m_tray->contextMenu()->show();
//        }
//        else if(event->type() == QEvent::Leave)
//        {
//            qDebug() << QString(u8"m_tray leave!");
//            m_tray->showMessage(QString(u8"提示"),QString(u8"有版本更新!"),
//                                QSystemTrayIcon::Information,10000);

//        }
//    }

    return QWidget::eventFilter(watched,event);
}

//void MainWidget::mousePressEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);
//    //    if (event->button() == Qt::LeftButton)
//    //    {
//    //        this->_isleftpressed = true;
//    //        QPoint temp = event->globalPos();
//    //        _plast = temp;
//    //        _curpos = countFlag(event->pos(), countRow(event->pos()));
//    //    }

////    if(ReleaseCapture())
////    {
////        QWidget* pWindow = this->window();
////        if(pWindow->isTopLevel())
////        {
////            SendMessage(HWND(pWindow->winId()),WM_SYSCOMMAND,SC_MOVE + HTCAPTION,0);
////        }
////    }
////    event->ignore();
//}

//void MainWidget::mouseMoveEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event)
////    //拖动之前判断是否串口处于最大化
////    if(this->isMaximized())
////    {
////        return;
////    }
////    if(this->isFullScreen()) return;	//窗口铺满全屏，直接返回，不做任何操作
////    int poss = countFlag(event->pos(), countRow(event->pos()));
////    setCursorType(poss);
////    if (_isleftpressed)//是否左击
////    {
////        QPoint ptemp = event->globalPos();
////        ptemp = ptemp - _plast;
////        if (_curpos == 22)//移动窗口
////        {
////            ptemp = ptemp + pos();
////            move(ptemp);
////        }
////        else
////        {
////            QRect wid = geometry();
////            switch (_curpos)//改变窗口的大小
////            {
////            case 11:wid.setTopLeft(wid.topLeft() + ptemp); break;//左上角
////            case 13:wid.setTopRight(wid.topRight() + ptemp); break;//右上角
////            case 31:wid.setBottomLeft(wid.bottomLeft() + ptemp); break;//左下角
////            case 33:wid.setBottomRight(wid.bottomRight() + ptemp); break;//右下角
////            case 12:wid.setTop(wid.top() + ptemp.y()); break;//中上角
////            case 21:wid.setLeft(wid.left() + ptemp.x()); break;//中左角
////            case 23:wid.setRight(wid.right() + ptemp.x()); break;//中右角
////            case 32:wid.setBottom(wid.bottom() + ptemp.y()); break;//中下角
////            }
////            setGeometry(wid);
////        }
////        _plast = event->globalPos();//更新位置
////    }
//}

//void MainWidget::mouseReleaseEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event);
//    if (_isleftpressed)
//        _isleftpressed = false;
//    setCursor(Qt::ArrowCursor);
//}

void MainWidget::changeEvent(QEvent *event)
{
    switch (event->type())
        {
        case QEvent::WindowStateChange:
            {
                this->update();//触发重绘事件
                this->repaint();
                event->ignore();
                break;
            }
        default:
            break;
    }
}

/*界面卡顿*/
void MainWidget::showEvent(QShowEvent *event)
{
    this->setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(event);
}

/*重写关闭事件---弹窗询问*/
void MainWidget::closeEvent(QCloseEvent *event)
{
    //重写关闭事件，就不需要关闭按钮的操作
    if(m_pExitDlg->isShow)//如果为isShow就是弹出提示界面
    {
        if(WebDownLoadList::getInstance()->getWorkCounts()>0)
        {
            m_pExitDlg->setCloseText(QString::fromLocal8Bit("当前有文件下载，是否确需关闭？"));
        }
        else
        {
            m_pExitDlg->setCloseText(QString::fromLocal8Bit("您确定要退出软件吗？"));
        }
       int ret = m_pExitDlg->exec();//程序阻塞，等待返回值做下一步判断
       qDebug() << QString(u8"是否关闭：") << ret;
       if(ret)
       {
           qDebug() << QString(u8"是否为直接关闭：") << m_pExitDlg->getCloseType();
           if(m_pExitDlg->getCloseType())
           {
               m_isClose = true;//不弹界面，但是确实是直接关闭
           }
           else
           {
               m_isClose = false;//不弹出界面，但是不是直接关闭（而是隐藏）
           }
       }
       else
       {
           m_isClose = false;
       }
    }
    else//如果为非isShow就是不弹出提示界面，还要根据配置做选择（直接关闭还是隐藏）
    {
        //没有退出界面提示，什么也不保存
        qDebug() << QString(u8"是否为直接关闭：") << m_pExitDlg->getCloseType();
        if(m_pExitDlg->getCloseType())
        {
            m_isClose = true;//不弹界面，但是确实是直接关闭
        }
        else
        {
            m_isClose = false;//不弹出界面，但是不是直接关闭（而是隐藏）
        }
    }

    //以下流程在有界面的情况下才执行
     if(!m_isClose)//取消
     {
//         this->hide();
         event->ignore();
     }
     else//确定退出 m_isClose = true
     {
         /*做一些数据保存*/
         emit sig_startCloseAppliction();
         m_pExitDlg->setIni();
         //此处最好做一个全局的通知信号
//         m_tray->hide();
         QSqlQuery query(dataBase::getSqlDataBase());
         //此处应该在数据库提供接口
//         query.exec("drop table if exists localmusic;");//sqlite
//         query.exec("drop table if exists logininfo;");//sqlite
         query.exec("truncate table localmusic;");//mysql
         qDebug()<<"localmusic,logininfo tables is drop!";
         dataBase::removeMysqlConnection();//关闭数据库，移除连接
         event->accept();
     }
     MainNotice::getInstance()->close();
     if(MultipPlayer::getInstance() != nullptr)
     {
         MultipPlayer::getInstance()->close();
     }
}

/*界面缩放调整事件*/
void MainWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    emit sig_sendWindowResize();
    RingWait1::getInstance()->hide();
    if(!MainNotice::getInstance()->isHidden())
    {
        MainNotice::getInstance()->hide();//左侧弹出消息菜单
    }
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_N)//全屏时按下ESC键盘
    {
//        if(m_stackWidget_center->currentWidget() == m_webStackWgt && m_webStackWgt->currentWidget() == m_webWidget)
//        emit sig_createNewWebTab();
    }
//    qDebug() << event->key();//78（key）需要鼠标焦点在标题栏
}

/*获取光标在窗口所在区域的 行   返回行数*/
int MainWidget::countRow(QPoint p)
{
    return (p.x()<MARGIN) ? 1 : (p.x()>(this->width() - MARGIN) ? 3 : 2);
}

/*获取光标在窗口所在区域的 列  返回行列坐标*/
int MainWidget::countFlag(QPoint p, int row)
{
    if(p.y()<MARGIN)
        return 10+row;
    else if(p.y()>this->height()-MARGIN)
        return 30+row;
    else
        return 20+row;
}

/*根据传入的坐标，设置光标样式*/
void MainWidget::setCursorType(int flag)
{
    switch(flag)
    {
    case 11:
    case 33:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case 13:
    case 31:
        setCursor(Qt::SizeBDiagCursor);break;//左下 右上
    case 21:
    case 23:
        setCursor(Qt::SizeHorCursor);break;//最左 最右
    case 12:
    case 32:
        setCursor(Qt::SizeVerCursor);break;//最上 最下
    case 22:
        setCursor(Qt::ArrowCursor);//正常区域
        QApplication::restoreOverrideCursor();//恢复鼠标指针性状
        break;
    default:
        break;
    }
}

