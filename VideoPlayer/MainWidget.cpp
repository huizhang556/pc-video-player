#include "MainWidget.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QActionGroup>
#include <QWidgetAction>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    m_isHide(false),
    m_winMax(false),
    m_firstOpen(true)
{
    setMinimumSize(1300,800);
    setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setWindowTitle(QString::fromLocal8Bit("Qt简易视频播放器主界面"));
    initOtherWidgetUi();//初始化界面
    setStackedWidgetPage();//设置StackedWidget布局每个page界面
    chandleSignalAndSlots();//处理所有的信号与槽函数
}

//初始化界面
void MainWidget::initOtherWidgetUi()
{
    m_titleBar = new TitleBar(this);
    m_titleBar->setFixedHeight(50);
    m_titleBar->setObjectName(QString::fromLatin1("m_titleBar"));

    m_leftSideBar = new LeftSideBar(this);
    m_leftSideBar->setObjectName(QString::fromLatin1("m_leftSideBar"));
    QStringList list;
    list << QString::fromLocal8Bit("主界面1")
         << QString::fromLocal8Bit("浏览器2")
         << QString::fromLocal8Bit("视频页3")
         << QString::fromLocal8Bit("视频页4")
         << QString::fromLocal8Bit("副界面5")
         << QString::fromLocal8Bit("副界面6")
         << QString::fromLocal8Bit("副界面7")
         << QString::fromLocal8Bit("副界面8")
         << QString::fromLocal8Bit("副界面9")
         << QString::fromLocal8Bit("副界面10")
         << QString::fromLocal8Bit("副界面11")
         << QString::fromLocal8Bit("副界面12")
         << QString::fromLocal8Bit("副界面13")
         << QString::fromLocal8Bit("副界面14")
         << QString::fromLocal8Bit("副界面15")
         << QString::fromLocal8Bit("副界面16")
         << QString::fromLocal8Bit("副界面17")
         << QString::fromLocal8Bit("副界面18")
         << QString::fromLocal8Bit("副界面19")
         << QString::fromLocal8Bit("副界面20");
    m_leftSideBar->setSlideBarListText(list);
    m_leftSideBar->setFixedWidth(170);

    m_stackWidget_center = new QStackedWidget(this);
    m_stackWidget_center->setObjectName(QString::fromLatin1("m_stackWidget_center"));
    m_stackWidget_center->setCurrentIndex(0);//默认显示第一个page页
    m_stackWidget_center->installEventFilter(this);//安装事件监听器
    //QStackedWidget此处不能指定父参数，否则界面会出问题

    m_leftButton = new QPushButton(m_stackWidget_center);
    m_leftButton->setObjectName(QString::fromLocal8Bit("m_leftButton"));
    m_leftButton->setFixedSize(20,50);

    m_mainPlayer = new MultipPlayer();
    m_mainPlayer->setObjectName(QString::fromLatin1("m_mainPlayer"));

    m_musicList = new MusicPlaylist();
    m_musicList->setObjectName(QString::fromLatin1("m_musicList"));

    m_musicShow = new MusicPlayShow();
    m_musicShow->setObjectName(QString::fromLatin1("m_musicShow"));

    m_tabWidget = new CusTabWidget();
    m_tabWidget->setObjectName(QString::fromLatin1("m_tabWidget"));

    m_videoBlank = new VideoBlank();
    m_videoBlank->setHideOpenButton(false);//隐藏打开文件按钮
    m_videoBlank->setObjectName(QString::fromLatin1("m_videoBlank"));

    m_webBrowser = new CusWebBrowser();
    m_webBrowser->setObjectName(QString::fromLatin1("m_webBrowser"));

    m_cusTabbar = new CusTabBar();
    m_cusTabbar->setObjectName(QString::fromLocal8Bit("m_cusTabbar"));
    m_cusTabbar->hide();

    m_statusBar = new QStatusBar();
    m_statusBar->setObjectName(QString::fromLocal8Bit("m_statusBar"));

    m_webTabWidget = new QTabWidget();
    m_webTabWidget->setObjectName(QString::fromLocal8Bit("m_webTabWidget"));
    m_webTabWidget->tabBar()->setObjectName(QString::fromLocal8Bit("m_webTabBar"));
    m_webTabWidget->insertTab(0,m_webBrowser,QString::fromLocal8Bit("default"));
    m_webTabWidget->setTabsClosable(true);//打开关闭按钮
    m_webTabWidget->setMovable(true);//标签可拖动
//    m_webTabWidget->tabBar()->hide();
//    m_webTabWidget->tabBar()->setTabButton(0,QTabBar::RightSide,m_addWebButton);
//    m_webTabWidget->setCornerWidget(m_addWebButton,Qt::TopRightCorner);
//    m_webTabWidget->setTabShape(QTabWidget::Triangular);//设置样式后，不起作用
    m_webVblayout = new QVBoxLayout();
    m_webVblayout->setSpacing(0);
    m_webVblayout->setContentsMargins(0,0,0,0);
    m_webVblayout->setMargin(0);
    m_webVblayout->addWidget(m_cusTabbar);
    m_webVblayout->addWidget(m_webTabWidget);
    m_webVblayout->addWidget(m_statusBar);

    m_webWidget  = new QWidget();
    m_webWidget->setObjectName(QString::fromLocal8Bit("m_webWidget"));
    m_webWidget->setLayout(m_webVblayout);

    m_webRecords = new CollectRecords();
    m_webRecords->setObjectName(QString::fromLocal8Bit("m_webRecords"));

    m_webHistory = new WebHistory();
    m_webHistory->setObjectName(QString::fromLocal8Bit("m_webHistory"));

    m_webMessage = new WebMessageBox();
    m_webMessage->setObjectName(QString::fromLocal8Bit("m_webMessage"));

    m_webStackWgt = new QStackedWidget();
    m_webStackWgt->setObjectName(QString::fromLocal8Bit("m_webStackWgt"));
    m_webStackWgt->addWidget(m_webWidget);// 0 浏览器
    m_webStackWgt->addWidget(m_webRecords);//1 浏览器收藏记录
    m_webStackWgt->addWidget(m_webHistory);//2 浏览器浏览历史
    m_webStackWgt->setCurrentWidget(m_webWidget);

    m_personForm = new PersonFileForm();
    m_personForm->setObjectName(QString::fromLatin1("m_personForm"));

    //弹出对话框
    m_pExitDlg = new ExitDialog(this);
    m_pExitDlg->setObjectName(QString::fromLatin1("m_pExitDlg"));

    m_systemSetting = new SystemSetting();
    m_systemSetting->setObjectName(QString::fromLocal8Bit("m_systemSetting"));

    m_homeWdgt = new CentralHomeForm();
    m_homeWdgt->setObjectName(QString::fromLocal8Bit("m_homeWdgt"));

    //托盘
    QIcon icno(":/images/icon/tray.png");
    m_tray = new QSystemTrayIcon(icno,this);
    m_tray->setToolTip(QString::fromLocal8Bit("subplayer"));
    m_tray->show();
    createTrayMenu();

    m_stackWidget_left = new QStackedWidget(this);
    m_stackWidget_left->setObjectName(QString::fromLocal8Bit("m_stackWidget_left"));
    m_stackWidget_left->setFixedWidth(170);//固定宽度170
    m_stackWidget_left->insertWidget(0,m_leftSideBar);

    m_vblayout = new QVBoxLayout(this);
    m_hblayout = new QHBoxLayout(this);
    //侧边栏+QStackedWidget--->水平布局
    m_hblayout->addWidget(m_stackWidget_left,0,Qt::AlignLeft);
//    m_hblayout->addWidget(m_stackWidget_center,1,Qt::AlignCenter);//此处不能添加布局，否则导致界面错乱
    m_hblayout->addWidget(m_stackWidget_center);
    m_hblayout->setSpacing(0);
    m_hblayout->setContentsMargins(0,0,0,0);
    m_hblayout->setMargin(0);
    //标题栏+水平布局--->垂直布局
    m_vblayout->addWidget(m_titleBar,0,Qt::AlignTop);
    m_vblayout->addLayout(m_hblayout,1);
    m_vblayout->setContentsMargins(2,2,2,2);
    m_vblayout->setSpacing(0);
    m_hblayout->setMargin(0);
    this->setLayout(m_vblayout);
}

//设置StackedWidget布局每个page界面
void MainWidget::setStackedWidgetPage()
{
    m_stackWidget_center->insertWidget(0,m_homeWdgt);//m_mainShowForm
    m_stackWidget_center->insertWidget(1,m_webStackWgt);//m_webStackWgt
    m_stackWidget_center->insertWidget(2,m_tabWidget);//m_tabWidget
    m_stackWidget_center->insertWidget(3,m_musicShow);//musicshow
    m_stackWidget_center->insertWidget(4,m_musicList);//musiclist
    m_stackWidget_center->insertWidget(5,m_personForm);//personform 个人管理
}

//重载函数1：添加一个browser---参数为QUrl
void MainWidget::slot_addToWebTabwidgetBrowser(QUrl &url)
{
    if(url.isEmpty()) return;
    CusWebBrowser *browser = new CusWebBrowser();
    browser->setObjectName(QString::fromLocal8Bit("browser"));
    browser->load(url);
    m_titleBar->slot_setWebLineEditCurentUrl(url);
    qDebug() <<QString::fromLocal8Bit("当前browser:") <<browser->icon()<<browser->title();
    m_webTabWidget->insertTab(m_webTabWidget->currentIndex()+1,browser,browser->icon(),browser->title());
    m_webTabWidget->setCurrentIndex(m_webTabWidget->currentIndex()+1);
//    updateAddWebButtonPosition();
//    //标题改变
//    connect(browser,&CusWebBrowser::titleChanged,[=](QString &title){
//        slot_setCurrentWebBarTitle(m_webTabWidget->indexOf(browser),title);
//    });
//    //图标改变
//    connect(browser,&CusWebBrowser::iconChanged,[=](QIcon &icon){
//        slot_setCurrentWebBarIcon(m_webTabWidget->indexOf(browser),icon);
//    });
    connect(browser,SIGNAL(sig_sendToNewUrl(QUrl&)),this,SLOT(slot_addToWebTabwidgetBrowser(QUrl&)));
    //加载网页进度
    connect(browser,SIGNAL(loadProgress(int)),m_titleBar,SLOT(slot_setWebProgressBarValue(int)));
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
    qDebug() <<QString::fromLocal8Bit("当前browser:") <<browser->icon()<<browser->title();
    m_webTabWidget->insertTab(m_webTabWidget->currentIndex()+1,browser,browser->icon(),browser->title());//当前选中项的隔壁插入
    m_webTabWidget->setCurrentIndex(m_webTabWidget->currentIndex()+1);//新插入的为当前选中项
//    updateAddWebButtonPosition();
    connect(browser,SIGNAL(sig_sendToNewUrl(QUrl&)),this,SLOT(slot_addToWebTabwidgetBrowser(QUrl&)));
    //加载网页进度
    connect(browser,SIGNAL(loadProgress(int)),m_titleBar,SLOT(slot_setWebProgressBarValue(int)));
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
}

//过滤不是当前活跃的窗口--返回主页
void MainWidget::slot_judgeCurrentBrowserIsActive_home()
{
   CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
       actWdgt->slots_home();
//       delete actWdgt;
}

void MainWidget::slot_judgeCurrentBrowserIsActive_back()
{
    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
        actWdgt->slots_back();
//        delete actWdgt;
}

void MainWidget::slot_judgeCurrentBrowserIsActive_freshen()
{
    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
        actWdgt->slots_refreshen();
//        delete actWdgt;
}

void MainWidget::slot_judgeCurrentBrowserIsActive_advance()
{
    CusWebBrowser *actWdgt = qobject_cast<CusWebBrowser*>(m_webTabWidget->currentWidget());
        actWdgt->slots_advance();
//        delete actWdgt;
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
void MainWidget::chandleSignalAndSlots()
{
    /************************************标题栏窗口控制按钮************************************/
    connect(this,&MainWidget::sig_startCloseAppliction,m_mainPlayer,&MultipPlayer::slot_closeCurrentWindow);//转到重写事件
    connect(m_titleBar,&TitleBar::sig_winClose,this,&MainWidget::close);//转到重写事件
    connect(m_titleBar,&TitleBar::sig_winNormal,this,&MainWidget::chandleRestoreWindow);//根据不同状态处理窗口
    connect(m_titleBar,&TitleBar::sig_winMinimum,[=](){this->showMinimized();});
    connect(m_titleBar,&TitleBar::sig_doubleClick,[=](){chandleRestoreWindow();});
    //响应 标题栏 帮助设置发来信号，弹出右键菜单
    connect(m_titleBar,SIGNAL(sig_settingHelpItem(int)),this,SLOT(chandleSetHelpItem(int)));


    /************************************浏览器部分************************************/
    //收藏网址

    //新增历史记录
    connect(m_titleBar,SIGNAL(sig_sendInputNewUrl(QString)),m_webHistory,SLOT(slot_addToListHistoryWidget(QString)));
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
       m_stackWidget_center->setCurrentIndex(index1);//个人信息界面
       m_personForm->getCurrentShowWidget_TW()->setCurrentIndex(index2);
    });
    //历史记录
    connect(m_titleBar,&TitleBar::sig_historyDownload,[=](int index1,int index2){
        m_stackWidget_center->setCurrentIndex(index1);//个人信息界面
        m_personForm->getCurrentShowWidget_TW()->setCurrentIndex(index2);
    });
    //网页下载请求3
    connect(m_webBrowser->page()->profile(),SIGNAL(downloadRequested(QWebEngineDownloadItem*)),NewWork::getInstance(),SLOT(slot_receiveDownloadRequested(QWebEngineDownloadItem*)),Qt::UniqueConnection);//第五个参数，防止多次请求
    //标题栏---显示当前页面的地址
    connect(m_webBrowser,SIGNAL(urlChanged(QUrl)),m_titleBar,SLOT(setLineEditAddress(QUrl)));
    //browser 标题 改变
//    connect(m_webBrowser,SIGNAL(titleChanged(QString)),m_webTabWidget,SLOT());
    //browser 图标 改变
//    connect(m_webBrowser,SIGNAL(iconChanged(QIcon)),m_webTabWidget,SLOT());
    //URL改变
    connect(m_webBrowser,&CusWebBrowser::urlChanged,[=](QUrl url){slot_showLinkOnStatusBar(url.toDisplayString());});
    //鼠标link
    connect(m_webBrowser->page(),&QWebEnginePage::linkHovered,this,&MainWidget::slot_showLinkOnStatusBar);
    //添加一个browser
    connect(m_webBrowser,SIGNAL(sig_sendToNewUrl(QUrl&)),this,SLOT(slot_addToWebTabwidgetBrowser(QUrl&)));
    //加载网页进度
    connect(m_webBrowser,SIGNAL(loadProgress(int)),m_titleBar,SLOT(slot_setWebProgressBarValue(int)));
    /*网页tab改变信号*/
    //当前项改变
    connect(m_webBrowser,SIGNAL(urlChanged(QUrl)),m_titleBar,SLOT(slot_setWebLineEditCurentUrl(QUrl)));
    //tabbar点击改变
    connect(m_webTabWidget,SIGNAL(tabBarClicked(int)),this,SLOT(slot_switchCurrentTab_URL(int)));
    //tab关闭
    connect(m_webTabWidget,SIGNAL(tabCloseRequested(int)),this,SLOT(slot_removeTabWidgetTab(int)));


    /************************************浏览器---右键部分处理************************************/
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
        slot_addToWebTabwidgetBrowser(url);
        m_titleBar->slot_clearWebLineEditText();//清除输入框文字（无用）
    });

    /************************************浏览器---收藏栏************************************/
    //收藏菜单---返回按钮
    connect(m_webRecords,&CollectRecords::sig_returnPage,[=](){m_webStackWgt->setCurrentIndex(0);});
    //收藏菜单---修改按钮
    connect(m_webRecords,&CollectRecords::sig_changeRecord,[=](){m_webMessage->exec();});

    /************************************浏览器---历史记录栏************************************/
    //历史记录---返回按钮
    connect(m_webHistory,&WebHistory::sig_returnPage,[=](){m_webStackWgt->setCurrentIndex(0);});
     //标签栏---展开收藏菜单
    connect(m_cusTabbar,&CusTabBar::sig_sendTabShowRecords,[=](){m_webStackWgt->setCurrentIndex(1);});

    /************************************浏览器---添加记录消息窗口************************************/


    /************************************主窗口关闭关联窗口动作************************************/
    //收到主窗口关闭信号
    connect(m_pExitDlg,&ExitDialog::sig_SendcloseMain,[=](){m_isClose = true;});
    //没收到主窗口关闭信号
    connect(m_pExitDlg,&ExitDialog::sig_SendNotcloseMain,[=](){m_isClose = false;});

    //关闭主窗口，先通知标题栏，再转发登录窗口关闭
    connect(this,&MainWidget::sig_startCloseAppliction,m_titleBar,&TitleBar::receiveMainFormClose);
    //侧边栏有关信号与槽函数处理
    connect(m_leftSideBar,&LeftSideBar::sig_sidebarItemChange,[=](int index)
    {
        m_stackWidget_center->setCurrentIndex(index);
        m_titleBar->isNecessaryShowSearch(index);
    });
    //左侧边栏控制显示/隐藏的按钮
    connect(m_leftButton,&QPushButton::clicked,[=](){
        slot_on_leftButton_clicked();
    });
    connect(this,SIGNAL(sig_winStatus(bool)),m_titleBar,SLOT(chandleMainWinStatus(bool)));//标题栏处理不同状态下样式
    //空白页---打开文件
    connect(m_videoBlank,&VideoBlank::sig_openLocalFile,[=]()
    {
        m_mainPlayer->slot_openLocalFile();
//        m_mainPlayer->show();
    });


    /************************************托盘+浮动控制界面---信号处理************************************/
    //播放次序选择界面接收信号
    connect(this,SIGNAL(sig_trayPlayOrder(int)),PlayOrderForm::getInstance(),SLOT(clearAndSetButtonCheckedStatus(int)));
    //接收播放次序选择界面发送过来信号
    connect(PlayOrderForm::getInstance(),SIGNAL(sig_playerOrder(int)),this,SLOT(tray_setCurrentPlayOrderStatus(int)));
    //托盘---上一首
    connect(m_systemTray,SIGNAL(sig_playStatusPrevious()),m_mainPlayer,SLOT(on_pushButton_previous_clicked()));
    //浮动控制---上一首
    connect(FloatPlayCtl::getInstance(),SIGNAL(sig_sendPlayPrevious()),m_mainPlayer,SLOT(on_pushButton_previous_clicked()));

    //托盘---下一首
    connect(m_systemTray,SIGNAL(sig_playStatusNext()),m_mainPlayer,SLOT(on_pushButton_next_clicked()));
    //浮动控制---下一首
    connect(FloatPlayCtl::getInstance(),SIGNAL(sig_sendPlayNext()),m_mainPlayer,SLOT(on_pushButton_next_clicked()));

    //01-播放器主界面---接收播放器发送的播放/暂停
    connect(m_mainPlayer,SIGNAL(sig_currentMediaPlayStatus(bool)),m_mainPlayer,SLOT(slot_setPlayStatusStyle_main(bool)));
    //02-托盘---接收播放器发送的播放/暂停
    connect(m_mainPlayer,SIGNAL(sig_currentMediaPlayStatus(bool)),m_systemTray,SLOT(slot_setCurrentPlayStatus(bool)));
    //03-浮动控制---接收播放器发送的播放/暂停
    connect(m_mainPlayer,SIGNAL(sig_currentMediaPlayStatus(bool)),FloatPlayCtl::getInstance(),SLOT(slot_setCurrentPlayStatus(bool)));

    //托盘---播放/暂停
    connect(m_systemTray,SIGNAL(sig_playStatusPause(bool)),m_mainPlayer,SLOT(on_pushButton_pauseStart_clicked()));
    //浮动控制---播放/暂停
    connect(FloatPlayCtl::getInstance(),SIGNAL(sig_sendPlayStartPause()),m_mainPlayer,SLOT(on_pushButton_pauseStart_clicked()));

    //托盘---音量值改变-->播放界面值改变
    connect(m_systemTray,SIGNAL(sig_playProgressValue(int)),m_mainPlayer,SLOT(slot_receiveSystemTraySendSoundValue(int)));
    //浮动控制---音量值改变-->播放界面值改变
    connect(FloatPlayCtl::getInstance(),SIGNAL(sig_sendProgress_voice(int)),m_mainPlayer,SLOT(slot_receiveSystemTraySendSoundValue(int)));

    //托盘---静音按钮
    connect(m_systemTray,SIGNAL(sig_playStatusMuted(bool)),m_mainPlayer,SLOT(on_setCurrentMediaSoundSatus()));
    //浮动控制---静音按钮
    connect(FloatPlayCtl::getInstance(),SIGNAL(sig_sendPlayMute(bool)),m_mainPlayer,SLOT(on_setCurrentMediaSoundSatus()));

    //托盘action组
    connect(m_actionGroup,&QActionGroup::triggered,[=](QAction *action)
    {
        tray_getCurrentPlayOrder(action);//发送信号
        tray_setCurrentPlayOrderStatus(action);
    });


    /************************************播放器部分信号处理************************************/
    //接收播放器关闭
    connect(m_mainPlayer,&MultipPlayer::sig_mainPlayerClose,[=](){
        if(m_mainPlayer!=nullptr)
        {
            m_mainPlayer->close();//实际没有删除，需要手动delete
        }
    });


    //接收主界面（实际是音量界面发过来的值，做了中转）的音量值
    connect(m_mainPlayer,SIGNAL(sig_currentMediaSoundValueChange(int)),m_systemTray,SLOT(slot_setCurrentPlaySoundValue(int)));
    //浮动控制---接收音量值改变（01.主界面调节 02.托盘调节）
    connect(m_mainPlayer,SIGNAL(sig_currentMediaSoundValueChange(int)),FloatPlayCtl::getInstance(),SLOT(slot_setProgressbar_voice(int)));
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
    m_menuTray->setObjectName(QString::fromLocal8Bit("m_menuTray"));//设置样式用
    m_systemTray = new SystemTray(this);//必须new 出来，不能获取单例方式
    m_playMode = new  QMenu(QString::fromLocal8Bit("播放模式"));
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
    wgtAction->setDefaultWidget(m_systemTray);
//    m_menuTray->setStyleSheet("QMenu{"
//                              "background-color:white;"
//                              "color:#cdcdcd;"
//                              "font:bold normal 15px '微软雅黑';"
//                              "border:1px solid transparent;"
//                              "}");//font:bold italic 18px "微软雅黑";
//    m_playMode->setStyleSheet("QMenu{"
//                              "background-color:white;"
//                              "color:#cdcdcd;"
//                              "font:bold normal 15px '微软雅黑';"
//                              "border:1px solid transparent;"
//                              "}");//font:bold italic 18px "微软雅黑";
    m_menuTray->addAction(wgtAction);
    m_menuTray->addAction(QIcon("://images/tray/tray_home.png"),QString::fromLocal8Bit("显示主界面"),this,SLOT(tray_showMainWidget()));
    m_menuTray->addMenu(m_playMode);//添加 子菜单 播放模式
    m_menuTray->addAction(QIcon("://images/tray/tray_lyric.png"),QString::fromLocal8Bit("显示桌面歌词"),this,SLOT(tray_showDesktopLyric()));
    m_menuTray->addSeparator();
    m_menuTray->addAction(QIcon("://images/tray/tray_setting.png"),QString::fromLocal8Bit("系统设置"),this,SLOT(tray_systemSettting()));
    m_menuTray->addAction(QIcon("://images/tray/tray_upgrade.png"),QString::fromLocal8Bit("在线升级"),this,SLOT(tray_onlineUpgrade()));//注意消息阻塞
    m_menuTray->addAction(QIcon("://images/tray/tray_logout.png"),QString::fromLocal8Bit("退出登录"),this,SLOT(tray_systemLogout()));
    m_menuTray->addSeparator();
    m_menuTray->addAction(QIcon("://images/tray/tray_exit.png"),QString::fromLocal8Bit("退出软件"),this,SLOT(tray_systemExitSoftware()));
    m_tray->setContextMenu(m_menuTray);
}

/*处理设置按钮发过来的信号*/
void MainWidget::chandleSetHelpItem(int index)
{
    if(index == 0)//个人账户
    {
        qDebug() << "person login";
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
//    m_mainPlayer->openLocalFile();
    m_mainPlayer->slot_setMainCurrentIndex(0);//视频播放界面
    m_mainPlayer->show();//只显示播放器界面
}

/*播放网络资源*/
void MainWidget::help_aboutNetworklFile()
{
    qDebug() <<"PLAY NETWORK RESOURCE";
    m_mainPlayer->show();
    m_mainPlayer->slot_setVideTitleBar(1);//转到网络播放标题栏
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
        this->showNormal();
    qDebug() << "this is show";
}

void MainWidget::tray_showDesktopLyric()
{
    QMessageBox::information(this,QString::fromLocal8Bit("功能提示"),QString::fromLocal8Bit("功能暂未开放，敬请期待！"));
}

void MainWidget::tray_systemSettting()
{
    help_stemAboutSetting();
}

void MainWidget::tray_onlineUpgrade()
{
    QMessageBox::information(this,QString::fromLocal8Bit("更新提示"),QString::fromLocal8Bit("请前往官网下载更新！"));
}

void MainWidget::tray_systemLogout()
{
    QMessageBox::information(this,QString::fromLocal8Bit("登出提示"),QString::fromLocal8Bit("您已成功退出登录！"));
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
    m_webTabWidget->setTabText(index,title);
}

//web设置图标
void MainWidget::slot_setCurrentWebBarIcon(int index, const QIcon &icon)
{
    m_webTabWidget->setTabIcon(index,icon);
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
    if(m_isHide)
    {
        m_stackWidget_left->show();
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
    if(m_webBrowser != nullptr)
    {
        delete m_webBrowser;
        m_webBrowser = nullptr;
    }

    if(m_musicList != nullptr)
    {
        delete m_musicList;
        m_musicList = nullptr;
    }

    if(m_musicShow != nullptr)
    {
        delete m_musicShow;
        m_musicShow = nullptr;
    }

    if(m_tabWidget != nullptr)
    {
        delete m_tabWidget;
        m_tabWidget = nullptr;
    }

    if(m_videoBlank != nullptr)
    {
        delete m_videoBlank;
        m_videoBlank = nullptr;
    }

    if(m_mainPlayer != nullptr)
    {
        delete m_mainPlayer;
        m_mainPlayer = nullptr;
    }
}

/*事件过滤器*/
bool MainWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_stackWidget_center)
    {
        if(event->type() == QEvent::Enter)
        {
            updateLeftButtonGeometry();
            setLeftButtonStyleSheetStatus();
            m_leftButton->show();
        }
        else if(event->type() == QEvent::Leave)
        {
            m_leftButton->hide();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void MainWidget::mousePressEvent(QMouseEvent *event)
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

void MainWidget::mouseMoveEvent(QMouseEvent *event)
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

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (_isleftpressed)
        _isleftpressed = false;
    setCursor(Qt::ArrowCursor);
}

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
         //此处最好做一个全局的通知信号
//         m_tray->hide();
         QSqlQuery query;
         //此处应该在数据库提供接口
         query.exec("DROP TABLE IF EXISTS 'LocalMusic'");
         query.exec("DROP TABLE IF EXISTS 'LoginInfo'");
         qDebug()<<"LocalMusic,LoginInfo tables is drop!";
         event->accept();
     }
}

/*界面缩放调整事件*/
void MainWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
//    if(m_webBrowser!=nullptr)
//    m_webBrowser->resize(this->size());
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

