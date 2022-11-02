#include "TitleBar.h"
#include "ui_TitleBar.h"

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windows.h>
#include <windowsx.h>
#pragma comment (lib,"user32.lib")
#endif

#include <QDebug>
#include <QDateTime>
#include <QRegExp>
#include <QPalette>
#include <QProcess>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    m_signStatus(false),
    m_headUrl("https://www.baidu.com/s?wd="),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);
    installEventFilter(this);
    this->setFixedHeight(40);
    initWorker();//初始化
    handleSignalAndSLots();
}

/*析构*/
TitleBar::~TitleBar()
{
    delete ui;
    delete m_loginForm;
    delete m_searchForm;
    delete m_headHover;
}

/*初始化工作*/
void TitleBar::initWorker()
{
    //网络请求
    manager = new QNetworkAccessManager(this);

    //遮罩
    QRegion maskRegion(ui->label_userHead->rect(),QRegion::Ellipse);//创建圆形遮罩
    ui->label_userHead->setMask(maskRegion);//设置圆形遮罩
    ui->label_defaultHead->setMask(maskRegion);
    ui->label_userHead->installEventFilter(this);
    ui->stackedWidget_title->setCurrentIndex(0);
    ui->label_usermark->hide();

    //tooltip
    ui->pushButton_resume->setToolTip(QString::fromLocal8Bit("恢复"));
    ui->pushButton_favorites->setToolTip(QString::fromLocal8Bit("收藏记录"));
    ui->pushButton_records->setToolTip(QString::fromLocal8Bit("浏览历史"));
    ui->pushButton_webSkin->setToolTip(QString::fromLocal8Bit("皮肤"));
    ui->pushButton_more->setToolTip(QString::fromLocal8Bit("浏览控制"));
    ui->pushButton_webdownload->setToolTip(QString::fromLocal8Bit("下载"));

    ui->pushButton_userlogin->setFlat(true);
    ui->pushButton_userregis->setFlat(true);

    ui->Btnlogin->installEventFilter(this);
    ui->BtnHistory->installEventFilter(this);

    ui->webProgressBar->setHidden(true);
    //LCD数字显示
    ui->lcdNumber->setDigitCount(20);//显示数量（个数）
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);//设置数字字体
//    ui->lcdNumber->setPalette(Qt::red);//显示文字颜色，不怎么生效
    QPalette lcdpat = ui->lcdNumber->palette();
    lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::green);
    ui->lcdNumber->setPalette(lcdpat);
    //初始化定时器
    m_timer3 = new QTimer(this);
    m_timer3->start(1000);//0.1s更新发送一次时间,放在下面合适
    ui->Btnhelp->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->pushButton_close->setFlat(true);
    ui->stackedWidget->setCurrentIndex(0);//默认显示第一个page
    setShowToolTip();//增加提示

    //home
    ui->pushButton_home->setFixedSize(20,20);
    ui->pushButton_home->setFlat(true);

    //后退
    ui->pushButton_back->setFixedSize(20,20);
    ui->pushButton_back->setFlat(true);
    ui->pushButton_back->installEventFilter(this);
    //刷新
    ui->pushButton_freshen->setFixedSize(20,20);
    ui->pushButton_freshen->setFlat(true);

    //前进
    ui->pushButton_advance->setFixedSize(20,20);
    ui->pushButton_advance->setFlat(true);
    ui->pushButton_advance->installEventFilter(this);
    //网址栏
    ui->lineEdit_webSearch->setFixedHeight(28);
    ui->lineEdit_webSearch->installEventFilter(this);

    ui->lineEdit_webSearch->setPlaceholderText(QString::fromLocal8Bit("请输入有效网址或要搜索的内容-_-"));
    ui->lineEdit_webSearch->setCursorPosition(0);
    //正则校验  url校验
//    QRegExp regExp("^[a-zA-z]+://(\w+(-\w+)*)(\.(\w+(-\w+)*))*(\?\S*)?$");
//    QRegExpValidator *expval = new QRegExpValidator(regExp,this);
//    ui->lineEdit_webSearch->setValidator(expval);
    //快速搜索栏
    ui->lineEdit_simpSearch->setPlaceholderText(QString::fromLocal8Bit("快速搜索^_^"));
    ui->lineEdit_simpSearch->installEventFilter(this);
    //网址栏目中的小按钮
    m_actSafeMode = new QAction(QIcon("://images/icon/safelocked.png"),"");
    m_actSafeMode->setObjectName(QString::fromLocal8Bit("m_actSafeMode"));
    m_actCollect = new QAction(QIcon(":/images/icon/url_collection.png"),"");
    m_actCollect->setObjectName(QString::fromLocal8Bit("m_actCollect"));
    m_actRecords = new QAction(QIcon(":/images/icon/downwards_hover.png"),"");
    m_actRecords->setObjectName(QString::fromLocal8Bit("m_actRecords"));
    ui->lineEdit_webSearch->addAction(m_actSafeMode, QLineEdit::LeadingPosition);//安全锁
    ui->lineEdit_webSearch->addAction(m_actRecords, QLineEdit::TrailingPosition);//显示搜索历史
    ui->lineEdit_webSearch->addAction(m_actCollect, QLineEdit::TrailingPosition);//收藏网址
    //简要搜索栏中的小按钮
    m_actEngine = new QAction(QIcon("://images/function/engine_baidu.png"),"");
    m_actEngine->setObjectName(QString::fromLocal8Bit("m_actEngine"));
    m_actSSearch = new QAction(QIcon(":/images/icon/sousuo.png"),"");
    m_actSSearch->setObjectName(QString::fromLocal8Bit("m_actSSearch"));
    ui->lineEdit_simpSearch->addAction(m_actEngine, QLineEdit::LeadingPosition);//左侧
    ui->lineEdit_simpSearch->addAction(m_actSSearch, QLineEdit::TrailingPosition);//右侧

//    m_actHotRank = new QAction(QIcon("://images/home/rank_alllist.png"),"");
//    ui->lineEditSearch->addAction(m_actHotRank,QLineEdit::TrailingPosition);//显示在右侧
    ui->lineEditSearch->installEventFilter(this);//输入检索字
    ui->BtnSearch->installEventFilter(this);
    ui->BtnSearch->setHidden(true);//被隐藏掉
    ui->lineEdit_webSearch->installEventFilter(this);//输入网址

    m_searchForm = new SearchForm();//不指定父控件，也不加布局，需要手动删除
    m_searchForm->setObjectName(QString::fromLocal8Bit("m_searchForm"));

    m_loginForm = new Login();
    m_loginForm->setObjectName(QString::fromLocal8Bit("m_loginForm"));

    m_headHover = new HeadHover();
    m_headHover->setObjectName(QString::fromLocal8Bit("m_headHover"));

    m_mySkin = new MySkin();
    m_mySkin->setObjectName(QString::fromLocal8Bit("m_mySkin"));

    //收藏列表
    m_listWdgt_colloect = new QListWidget();
    m_listWdgt_colloect->setObjectName(QString::fromLocal8Bit("m_listWdgt_colloect"));
    m_listWdgt_colloect->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWdgt_colloect->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWdgt_colloect->setWindowFlags(Qt::FramelessWindowHint);
    m_listWdgt_colloect->installEventFilter(this);

    //历史记录列表
    m_listWdgt_history = new QListWidget();
    m_listWdgt_history->setObjectName(QString::fromLocal8Bit("m_listWdgt_history"));
    m_listWdgt_history->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWdgt_history->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWdgt_history->setWindowFlags(Qt::FramelessWindowHint);
    m_listWdgt_history->installEventFilter(this);

    //引擎列表
    m_listWdgt_engine = new QListWidget();
    m_listWdgt_engine->setWindowFlags(Qt::Tool);
    m_listWdgt_engine->setObjectName(QString::fromLocal8Bit("m_listWdgt_engine"));
    m_listWdgt_engine->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWdgt_engine->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_listWdgt_engine->setWindowFlags(Qt::FramelessWindowHint);
    m_listWdgt_engine->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    m_listWdgt_engine->installEventFilter(this);
    m_engineSetBtn = new QPushButton(QString::fromLocal8Bit("设置"));
    m_engineSetBtn->setObjectName(QString::fromLocal8Bit("m_engineSetBtn"));
    m_engineSetBtn->setFixedHeight(26);
    slot_addWebEngine();

    slot_switchToLoginPage(0,QString::fromLocal8Bit(""));//0 注册 1登录
}


/*处理信号与槽函数*/
void TitleBar::handleSignalAndSLots()
{
    //个人信息选择改变
    connect(m_headHover,&HeadHover::sig_itemChanged,[=](QString text){
        if(QString::fromLocal8Bit("个人主页") == text)
        {
            emit sig_filesUploadDownLoad(5,4);//主界面反应
        }
        else if(QString::fromLocal8Bit("会员中心") == text)
        {
            emit sig_filesUploadDownLoad(5,4);//主界面反应
        }
        else if(QString::fromLocal8Bit("注销账号") == text)
        {

        }
        else if(QString::fromLocal8Bit("重置密码") == text)
        {
//            LoginPersonInfo::getInstance()->showLoginWindow(3);
            NewLoginForm::getInstance()->slot_switchWinType(ShowType::ReSetWin);
        }
        else if(QString::fromLocal8Bit("退出登录") == text)
        {
            slot_receivedSign_out();
        }
        qDebug() << "current select item ="<< text;
    });

    //账号退出
    connect(m_loginForm,&Login::sig_sendSign_out,[=](){ slot_receivedSign_out(); });

    //左上角---用户登录
    connect(ui->pushButton_userlogin,&QPushButton::clicked,[=](){
//        LoginPersonInfo::getInstance()->showLoginWindow(0);
        NewLoginForm::getInstance()->slot_switchWinType(ShowType::LoginWin_2);
    });
    //登录回显登录信息
    connect(LoginPersonInfo::getInstance(),&LoginPersonInfo::sig_sendLoginOK,[=](QString nick, QString head, int grade){
        slot_receivedLoginInfo(nick,head,grade);
    });

    //new 登录回显登录信息
    connect(NewLoginForm::getInstance(),&NewLoginForm::sig_sendLoginOK,[=](QString nick, QString head, int grade){
        slot_receivedLoginInfo(nick,head,grade);
    });

    //登陆之前清除痕迹
    connect(LoginPersonInfo::getInstance(),&LoginPersonInfo::sig_sendClearTempRecords,[=](){
        m_listWdgt_history->clear();//清除搜索历史记录
        m_listWdgt_colloect->clear();//清除收藏历史记录
        slot_setCurrentWebSiteCollectStatus(ui->lineEdit_webSearch->text());
        emit sig_sendClearTempRecords();
    });


    //new 登陆之前清除痕迹
    connect(NewLoginForm::getInstance(),&NewLoginForm::sig_sendClearTempRecords,[=](){
        m_listWdgt_history->clear();//清除搜索历史记录
        m_listWdgt_colloect->clear();//清除收藏历史记录
        slot_setCurrentWebSiteCollectStatus(ui->lineEdit_webSearch->text());
        emit sig_sendClearTempRecords();
    });

    //左上角---用户注册
    connect(ui->pushButton_userregis,&QPushButton::clicked,[=](){
//        slot_showPersonLogin();
        NewLoginForm::getInstance()->slot_switchWinType(ShowType::RegisWin);
    });

    /*关于窗口大小调整*/
    //发送窗口关闭信号
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){emit sig_winClose();});
    //发送窗口还原信号
    connect(ui->pushButton_normal,&QPushButton::clicked,[=](){emit sig_winNormal();});
    //发送窗口最小化信号
    connect(ui->pushButton_min,&QPushButton::clicked,[=](){emit sig_winMinimum();});
    //关闭程序关闭历史搜索框
    connect(this,&TitleBar::sig_winClose,m_searchForm,&SearchForm::closeSearchForm);
    //关闭搜索历史记录、引擎记录
    connect(this,&TitleBar::sig_winClose,[=](){
        if(!m_listWdgt_history->isHidden())     m_listWdgt_history->close();
        if(!m_listWdgt_engine->isHidden())      m_listWdgt_engine->close();
        if(!m_headHover->isHidden())            m_headHover->close();
        //这里需要做判断，是否有下载文件
        if(!WebDownLoadList::getInstance()->isHidden()) WebDownLoadList::getInstance()->close();
    });
    //还原时，关闭历史搜索框
    connect(this,&TitleBar::sig_winNormal,m_searchForm,&SearchForm::closeSearchForm);
    //还原时，关闭登录界面
    connect(this,&TitleBar::sig_winNormal,m_loginForm,&Login::close);
    //更新时间
    connect(m_timer3,&QTimer::timeout,this,&TitleBar::getSystemTimeShow);

    /*关于标题栏功能性按钮*/
    //帮助
    connect(ui->Btnhelp,&QPushButton::clicked,[=](){createHelpMenu();});//帮助菜单
    //调用登录提示板
    connect(ui->Btnlogin,&QPushButton::clicked,[=](){emit sig_callLogin();});//登录选择界面
    //皮肤设置
    connect(ui->Btnskin,&QPushButton::clicked,[=](){showMySkin();});//显示皮肤
    //下载记录
    connect(ui->BtnDownload,&QPushButton::clicked,[=](){emit sig_filesUploadDownLoad(6,4);});//上传下载
    //历史记录
    connect(ui->BtnHistory,&QPushButton::clicked,[=](){emit sig_historyDownload(5,0);});//历史记录
    //截屏
    connect(ui->BtnScreen,&QPushButton::clicked,[=](){
       qDebug()<< "emit sig_screenPicture();";
//        QProcess process;
//        process.setWorkingDirectory(Global::appDirPath + "/capture" );
//        process.start( Global::appDirPath + "/capture/CaptureTool.exe");
//        process.start("E:\\QtProjects\\000QtDemo_51ctodemo\\04_20SubVideoPlayer\\VideoPlayer\\capture\\CaptureTool.exe");

    });//截屏


    //腾讯主页
//    connect(ui->Btn_logo,&QPushButton::clicked,[=](){QDesktopServices::openUrl(QUrl(QString("https://v.qq.com/")));});

    /*关于浏览器*/
    //返回主页
    connect(ui->pushButton_home,&QPushButton::clicked,[=](){emit sig_sendUrlHome();});
    //后退 浏览器处理
    connect(ui->pushButton_back,&QPushButton::clicked,[=](){emit sig_sendUrlBack();});
    //刷新 浏览器处理
    connect(ui->pushButton_freshen,&QPushButton::clicked,[=](){emit sig_sendUrlRefreshen();});
    //前进 浏览器处理
    connect(ui->pushButton_advance,&QPushButton::clicked,[=](){emit sig_sendUrlAdvance();});
    //显示登录窗口
//    connect(ui->Btnlogin,&QPushButton::clicked,[=](){qDebug() << "login had clicked!"; showLoginForm();});
    //恢复
    connect(ui->pushButton_resume,&QPushButton::clicked,[=](){});
    //历史记录记录搜索历史
//    connect(this,&TitleBar::sig_sendNewSearch,m_searchForm,&SearchForm::addHistoryItem);
    //显示搜索历史记录
    connect(m_actRecords,&QAction::triggered,this,&TitleBar::slot_updateShowListHistoryWidget);
    //显示可用搜索引擎
    connect(m_actEngine,&QAction::triggered,this,&TitleBar::slot_updateShowListEngineWidget);
    //网络文件下载记录
    connect(ui->pushButton_webdownload,&QPushButton::clicked,[=](){
//        WebDownLoadList::getInstance()->setWindowModality(Qt::ApplicationModal);
        if(WebDownLoadList::getInstance()->isHidden())
        {
            WebDownLoadList::getInstance()->show();
        }
        else
        {
            WebDownLoadList::getInstance()->hide();
        }
    });
    //皮肤
    connect(ui->pushButton_webSkin,&QPushButton::clicked,[=](){ emit sig_sendWebSkin(); });
    //收藏记录
    connect(ui->pushButton_favorites,&QPushButton::clicked,[=](){ emit sig_sendBrowserShowCollectList(); });
    //历史记录
    connect(ui->pushButton_records,&QPushButton::clicked,[=](){ emit sig_sendBrowserShowHistories(); });
    //浏览控制
    connect(ui->pushButton_more,&QPushButton::clicked,this,&TitleBar::slot_updateShowListSettigMenu);//右键菜单显示
    //网址输入框---回车键处理
    connect(ui->lineEdit_webSearch,&QLineEdit::returnPressed,[=](){
        QString newurl = judgeUrlType(ui->lineEdit_webSearch->text().trimmed());
        if(newurl.isEmpty()) return;
        slot_addToListHistoryWidget(ui->lineEdit_webSearch->text().trimmed());//添加进历史记录
        emit sig_sendInputNewUrl(newurl);//补充的url
        qDebug() << "emit sig_sendInputNewUrl(url);"<< newurl;
    });

    //快速搜索框---搜索处理
    connect(m_actSSearch,&QAction::triggered,this,[=](){
        QString newurl = judgeUrlType(ui->lineEdit_simpSearch->text().trimmed());
        if(newurl.isEmpty()) return;
        slot_addToListHistoryWidget(ui->lineEdit_simpSearch->text().trimmed());//添加进历史记录
        emit sig_sendInputNewUrl(newurl);//补充的url
    });

    //网址输入框---文本改变,判断是否收藏当前网址
    connect(ui->lineEdit_webSearch,&QLineEdit::textChanged,[=](QString text)
    {
              slot_setCurrentWebSiteCollectStatus(text);//设置样式
    });

    //搜索框---回车
    connect(ui->lineEditSearch,&CusLineEdit::returnPressed,[=](){
        QString his = ui->lineEditSearch->text().trimmed();
        m_searchForm->addHistoryItem(his);
        qDebug() << "emit sig_sendNewSearch(his);";
        //处理其他事件
        //鼠标进入样式改变
    });

    //搜索框---搜索按钮
    connect(ui->lineEditSearch,&CusLineEdit::sig_Search,[=](QString text){
        m_searchForm->addHistoryItem(text.trimmed());
        qDebug() << QString(u8"手动点击按钮搜索");
    });

    //网址收藏----单击收藏，双击显示列表
    connect(m_actCollect,&QAction::triggered,this,[=](){
        bool valid = judgeCollectUrlType(ui->lineEdit_webSearch->text());
        if(valid)//有效地址
        {
            slot_addToListCollectWidget(ui->lineEdit_webSearch->text());
        }
        else
        {
            return;
        }
    });

    //下载设置
    connect(WebDownLoadList::getInstance(),&WebDownLoadList::sig_setConfig,[=](){
        emit sig_settingHelpItem(1);//1  代表系统设置
    });

    //历史记录选中回显----回显选择的历史记录到lineEdit
    connect(m_listWdgt_history,&QListWidget::itemClicked,[=](QListWidgetItem *item)
    {
        if(item->text().isEmpty()) return;
        QString addUrl = judgeUrlType(item->text());
        ui->lineEdit_webSearch->setText(item->text());
        emit sig_sendInputNewUrl(addUrl);
        m_listWdgt_history->hide();
    });

    //收藏菜单选中回显----回显选择的记录到lineEdit
    connect(m_listWdgt_colloect,&QListWidget::itemClicked,[=](QListWidgetItem *item)
    {
        if(item->text().isEmpty()) return;
        ui->lineEdit_webSearch->setText(item->text());
        emit sig_sendInputNewUrl(item->text());
        m_listWdgt_colloect->hide();
    });

    //引擎选择
    connect(m_listWdgt_engine,&QListWidget::itemClicked,[=](QListWidgetItem *item)
    {
        if(item->text().isEmpty()) return;
        slot_changeEngineIcon(item->text());
    });

    //引擎设置
    connect(m_engineSetBtn,&QPushButton::clicked,this,[=](){
        emit sig_settingHelpItem(1);//转到系统设置
    });

    //获取网络头像
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_replyFinished(QNetworkReply*)),Qt::UniqueConnection);

    //转到热搜界面
    connect(m_searchForm,&SearchForm::sig_SendToMoreHots,[=](){emit sig_SendToMoreHots();});

}

void TitleBar::setWebDefUrl(const QString& title)
{
        ui->lineEdit_webSearch->setText(title);//默认显示的网址
}

/*创建菜单*/
void TitleBar::createHelpMenu()
{
    pmenu_help1 = new QMenu(this);
    pmenu_help1->setObjectName(QString::fromLocal8Bit("pmenu_help1"));//样式表中设置样式必须设置对象名称才能生效
    pmenu_help2 = new QMenu(QString::fromLocal8Bit("播放视频"),this);
    pmenu_help2->setObjectName(QString::fromLocal8Bit("pmenu_help2"));
    pmenu_help2->setIcon(QIcon("://images/icon/help_play.png"));
    pmenu_help1->addAction(QIcon("://images/icon/help_account.png"),QString::fromLocal8Bit("个人账户"),this,SLOT(slot_setButtonHelpEmitItem()));
    pmenu_help1->addAction(QIcon("://images/icon/setlogin.png"),QString::fromLocal8Bit("系统设置"),this,SLOT(slot_setButtonHelpEmitItem()));//注意：槽函数不加分号，且不能带参数
    pmenu_help1->addAction(QIcon("://images/icon/help_internet.png"),QString::fromLocal8Bit("网络资源"),this,SLOT(slot_setButtonHelpEmitItem()));//接收端使用sendor()判断
    pmenu_help1->addAction(QIcon("://images/icon/help_qahelp.png"),QString::fromLocal8Bit("问题帮助"),this,SLOT(slot_setButtonHelpEmitItem()));
    pmenu_help2->addAction(QIcon("://images/icon/help_local.png"),QString::fromLocal8Bit("本地视频"),this,SLOT(slot_setButtonHelpEmitItem()));
    pmenu_help2->addAction(QIcon("://images/icon/help_v_net.png"),QString::fromLocal8Bit("网络视频"),this,SLOT(slot_setButtonHelpEmitItem()));
    pmenu_help1->addMenu(pmenu_help2);
    pmenu_help1->addAction(QIcon("://images/icon/help_download.png"),QString::fromLocal8Bit("软件下载"),this,SLOT(slot_setButtonHelpEmitItem()));
    pmenu_help1->addSeparator();
    pmenu_help1->addAction(QIcon("://images/icon/help_exit.png"),QString::fromLocal8Bit("退出软件"),this,SLOT(slot_setButtonHelpEmitItem()));
    int x = ui->Btnhelp->parentWidget()->mapToGlobal(ui->Btnhelp->pos()).x();
    int y = ui->Btnhelp->parentWidget()->mapToGlobal(ui->Btnhelp->pos()).y();
//    QPoint point4 = QPoint(QCursor::pos().x()-70,QCursor::pos().y()+25);
    pmenu_help1->setGeometry(x-60,y+25,pmenu_help1->width(),pmenu_help1->height());
    pmenu_help1->exec();
    delete pmenu_help1;
    delete pmenu_help2;
}

//判断输入框输入内容，并做适当的调整，返回url
QString TitleBar::judgeUrlType(QString url)
{
    if(url.startsWith("http://"))//判断开头，这里用正则表达式做最好
    {
        return url;
    }
    else if(url.startsWith("https://"))
    {
        return url;
    }
    else if(url.startsWith("www."))
    {
        return QString::fromLocal8Bit("http://") + url;
    }
    else
    {
        return m_headUrl + url;
    }
}

bool TitleBar::judgeCollectUrlType(QString url)
{
    if(url.startsWith("http://"))//判断开头，这里用正则表达式做最好
    {
        return true;
    }
    else if(url.startsWith("https://"))
    {
        return true;
    }
    else if(url.startsWith("www."))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TitleBar::judgeCollectUrlExist(const QString &url)
{
    for(int i = 0; i < m_listWdgt_colloect->count(); i++)
    {
        if(m_listWdgt_colloect->item(i)->text() == url)
        {
            return true;//有，返回true
        }
    }
    return false;//没有返回false
}

bool TitleBar::judgeHistorytUrlType(QString url)
{
    if(url.startsWith("http"))
    {
        return true;
    }

    else if(url.startsWith("https"))
    {
        return true;
    }
    else if(url.startsWith("www."))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool TitleBar::judgeHistoryUrlExist(const QString &url)
{
    for(int i = 0; i < m_listWdgt_history->count(); i++)
    {
        if(m_listWdgt_history->item(i)->text() == url)
            return true;//代表有
    }
    return false;//代表无
}

//判断收藏状态
void TitleBar::slot_setCurrentWebSiteCollectStatus(const QString &url)
{
    if(url.isEmpty()) return;
    bool valid = judgeCollectUrlExist(url);
    if(valid)
    {
//        ui->pushButton_webcollect->setStyleSheet("#pushButton_webcollect{"
//                                                 "border-image: url(:/images/icon/url_collect_hover.png);"
//                                                 "}");
        m_actCollect->setIcon(QIcon(":/images/icon/url_collect_hover.png"));
    }
    else
    {
//        ui->pushButton_webcollect->setStyleSheet("#pushButton_webcollect{"
//                                                 "border-image: url(:/images/icon/url_collection.png);"
//                                                 "}");
        m_actCollect->setIcon(QIcon(":/images/icon/url_collection.png"));
    }
}

//显示收藏列表
//void TitleBar::slot_updateShowListCollectWidget()
//{
//    if(m_listWdgt_colloect)
//        if(m_listWdgt_colloect->isHidden())
//        {
//            int x = ui->pushButton_more->parentWidget()->mapToGlobal(ui->pushButton_more->pos()).x();
//            int y = ui->pushButton_more->parentWidget()->mapToGlobal(ui->pushButton_more->pos()).y();
//            m_listWdgt_colloect->setGeometry(x - 130,y + 58,
//                                             300,500);
//            m_listWdgt_colloect->raise();
//            m_listWdgt_colloect->show();
//        }
//        else
//        {
//            m_listWdgt_colloect->hide();
//        }
//}

void TitleBar::slot_addToListCollectWidget(const QString &text)
{
    if(text.isEmpty()) return;
    bool valid = judgeCollectUrlExist(text);//判断是否存在
    if(!valid)//没有则收藏
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon(":/images/function/collect_list_item.png"),text);
        m_listWdgt_colloect->insertItem(0,item);
        emit sig_sendCollectRecord(ui->lineEdit_webSearch->text());//记录栏添加收藏记录
    }
    else//有，则不做任何处理
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),
                                 QString::fromLocal8Bit("网址已收藏！"),
                                 QString::fromLocal8Bit("是"));
    }
    slot_setCurrentWebSiteCollectStatus(text);//收藏以后，样式在做一次处理
}


//删除一条记录
void TitleBar::slot_deleteListCollectWidget(const QString &url)
{
    for(int i = 0; i < m_listWdgt_colloect->count();i++)
    {
        if(m_listWdgt_colloect->item(i)->text() == url)
        {
            QListWidgetItem *t_item = m_listWdgt_colloect->takeItem(i);
            delete t_item;
        }
    }
    slot_setCurrentWebSiteCollectStatus(url);
}


//显示历史记录
void TitleBar::slot_updateShowListHistoryWidget()
{
    if(m_listWdgt_history)
        if(m_listWdgt_history->isHidden())
        {
            int x = ui->lineEdit_webSearch->parentWidget()->mapToGlobal(ui->lineEdit_webSearch->pos()).x();
            int y = ui->lineEdit_webSearch->parentWidget()->mapToGlobal(ui->lineEdit_webSearch->pos()).y();
            m_listWdgt_history->setGeometry(x,y + ui->lineEdit_webSearch->height(),
                                            ui->lineEdit_webSearch->width(),200);
            m_listWdgt_history->raise();
            m_listWdgt_history->show();
        }
        else
        {
            m_listWdgt_history->hide();
        }
}

/*搜索历史记录*/
void TitleBar::slot_addToListHistoryWidget(const QString &text)
{
    if(text.isEmpty()) return;
    if(!judgeHistoryUrlExist(text))//没有找到才添加
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon("://images/function/history_list_item.png"),text);
        m_listWdgt_history->insertItem(0,item);
    }
}

void TitleBar::slot_updateShowListEngineWidget()
{
    if(m_listWdgt_engine)
        if(m_listWdgt_engine->isHidden())
        {
            int x = ui->lineEdit_simpSearch->parentWidget()->mapToGlobal(ui->lineEdit_simpSearch->pos()).x();
            int y = ui->lineEdit_simpSearch->parentWidget()->mapToGlobal(ui->lineEdit_simpSearch->pos()).y();
            m_listWdgt_engine->setGeometry(x,y + ui->lineEdit_simpSearch->height(),
                                            ui->lineEdit_simpSearch->width(),130);
            m_listWdgt_engine->raise();
            m_listWdgt_engine->show();
        }
        else
        {
            m_listWdgt_engine->hide();
        }
}

void TitleBar::slot_changeEngineIcon(const QString &text)
{
    if(!text.isEmpty())
    {
        if(text == QString::fromLocal8Bit("360搜索"))
        {
            m_actEngine->setIcon(QIcon("://images/function/engine_360.png"));
            m_headUrl = "https://www.so.com/s?q=";
        }
        else if(text == QString::fromLocal8Bit("百度搜索"))
        {
            m_actEngine->setIcon(QIcon("://images/function/engine_baidu.png"));
            m_headUrl = "https://www.baidu.com/s?wd=";
        }
        else if(text == QString::fromLocal8Bit("Google搜索"))
        {
            m_actEngine->setIcon(QIcon("://images/function/engine_google.png"));
            m_headUrl = "https://www.google.com/search?q=";
        }
        else if(text == QString::fromLocal8Bit("必应搜索"))
        {
            m_actEngine->setIcon(QIcon("://images/function/engine_biying.png"));
            m_headUrl = "https://cn.bing.com/search?q=";
        }
        else
        {

        }
    }

}

//显示浏览器设置
void TitleBar::slot_updateShowListSettigMenu()
{
    QMenu *pmenu_funclist = new QMenu(this);
    pmenu_funclist->setWindowFlag(Qt::FramelessWindowHint);        //重要
    pmenu_funclist->setAttribute(Qt::WA_TranslucentBackground);    //重要
    pmenu_funclist->setObjectName(QString::fromLocal8Bit("pmenu_funclist"));

    QMenu *pmenu_func_tool = new QMenu(QString::fromLocal8Bit("工具"));
    pmenu_func_tool->setWindowFlag(Qt::FramelessWindowHint);        //重要
    pmenu_func_tool->setAttribute(Qt::WA_TranslucentBackground);    //重要
    pmenu_func_tool->setObjectName(QString::fromLocal8Bit("pmenu_func_tool"));

    pmenu_funclist->addAction(QIcon("://images/icon/help_account.png"),QString::fromLocal8Bit("新建窗口(Shift+C)"),this,SLOT(slot_browser_setMenu_createTab()));
    pmenu_funclist->addAction(QIcon("://images/icon/help_account.png"),QString::fromLocal8Bit("新建隐身窗口"),this,SLOT(slot_browser_setMenu_createHiddenTab()));
    pmenu_funclist->addSeparator();
    pmenu_funclist->addAction(QIcon("://images/icon/setlogin.png"),QString::fromLocal8Bit("保存网页"),this,SLOT(slot_browser_setMenu_savePage()));//注意：槽函数不加分号，且不能带参数
    pmenu_funclist->addAction(QIcon("://images/icon/help_internet.png"),QString::fromLocal8Bit("查找"),this,SLOT(slot_browser_setMenu_findText()));
    pmenu_funclist->addAction(QIcon("://images/icon/help_qahelp.png"),QString::fromLocal8Bit("全屏"),this,SLOT(slot_browser_setMenu_fullScreen()));
    pmenu_funclist->addSeparator();
    pmenu_funclist->addAction(QIcon("://images/icon/help_local.png"),QString::fromLocal8Bit("显示收藏栏(Alt+S)"),this,SLOT(slot_browser_setMenu_showCollectRecords()));
    pmenu_funclist->addAction(QIcon("://images/icon/help_local.png"),QString::fromLocal8Bit("清空搜索记录"),this,SLOT(slot_browser_setMenu_clearSearchRecords()));
    pmenu_funclist->addAction(QIcon("://images/icon/help_local.png"),QString::fromLocal8Bit("显示收藏夹"),this,SLOT(slot_browser_setMenu_showCollectList()));
    pmenu_funclist->addAction(QIcon("://images/icon/help_local.png"),QString::fromLocal8Bit("显示历史记录"),this,SLOT(slot_browser_setMenu_showHistories()));
    pmenu_funclist->addMenu(pmenu_func_tool);
    pmenu_func_tool->addAction(QIcon("://images/icon/help_download.png"),QString::fromLocal8Bit("管理扩展"),this,SLOT(slot_browser_setMenu_manageExtensions()));
    pmenu_func_tool->addAction(QIcon("://images/icon/help_exit.png"),QString::fromLocal8Bit("清除上网痕迹"),this,SLOT(slot_browser_setMenu_clearHistories()));
    pmenu_func_tool->addAction(QIcon("://images/icon/help_exit.png"),QString::fromLocal8Bit("查看源代码"),this,SLOT(slot_browser_setMenu_viewSourceCode()));
    pmenu_func_tool->addAction(QIcon("://images/icon/help_exit.png"),QString::fromLocal8Bit("任务管理器"),this,SLOT(slot_browser_setMenu_workerManager()));
    pmenu_func_tool->addAction(QIcon("://images/icon/help_exit.png"),QString::fromLocal8Bit("控制台选项"),this,SLOT(slot_browser_setMenu_consoleOptions()));
    pmenu_func_tool->addAction(QIcon("://images/icon/help_exit.png"),QString::fromLocal8Bit("internet选项"),this,SLOT(slot_browser_setMenu_internetOptions()));
    pmenu_funclist->addSeparator();
    pmenu_funclist->addAction(QIcon("://images/icon/help_v_net.png"),QString::fromLocal8Bit("退出登录"),this,SLOT(slot_browser_setMenu_logOut()));
    pmenu_funclist->addSeparator();
    pmenu_funclist->addAction(QIcon("://images/icon/help_v_net.png"),QString::fromLocal8Bit("常见问题"),this,SLOT(slot_browser_setMenu_FAQ()));
    pmenu_funclist->addAction(QIcon("://images/icon/help_v_net.png"),QString::fromLocal8Bit("帮助"),this,SLOT(slot_browser_setMenu_help()));
    //设置快捷键
//    QList<QAction*> actions = pmenu_funclist->actions();
//    foreach (QAction* arg, actions)
//    {
//        if(arg->text() == QString::fromLocal8Bit("新建窗口(Ctrl+N)"))
//                {
//                    arg->setShortcut(QKeySequence(tr("Ctrl+N")));
//                }
//    }
    int x = ui->pushButton_more->parentWidget()->mapToGlobal(ui->pushButton_more->pos()).x();
    int y = ui->pushButton_more->parentWidget()->mapToGlobal(ui->pushButton_more->pos()).y();
    pmenu_funclist->setGeometry(x-60, y + 30,
                                 pmenu_funclist->width(),pmenu_funclist->height());
    pmenu_funclist->exec();
    delete pmenu_funclist;
    delete pmenu_func_tool;
}

void TitleBar::slot_setCanGoForward(bool status)
{
    if(status)
    {
        ui->pushButton_advance->setStyleSheet("#pushButton_advance{"
                                              "border-image: url(:/images/icon/advance_hover.png);"
                                              "}");
    }
    else
    {
        return;
    }
}

void TitleBar::slot_setCanGoBack(bool status)
{
    if(status)
    {
        ui->pushButton_back->setStyleSheet("#pushButton_back{"
                                           "border-image: url(:/images/icon/back_hover.png);"
                                           "}");
    }
    else
    {
        return;
    }
}

//新建窗口
void TitleBar::slot_browser_setMenu_createTab()
{
//    emit sig_sendBrowserCreateTab();
    slot_receiveBlankWebTab();
}

//新建隐身窗口
void TitleBar::slot_browser_setMenu_createHiddenTab()
{
    emit sig_sendBrowserCreateHiddenTab();
    slot_receiveBlankWebTab();
}

//保存网页
void TitleBar::slot_browser_setMenu_savePage()
{
    emit sig_sendBrowserSavePage();
}

//网页查找
void TitleBar::slot_browser_setMenu_findText()
{
    emit sig_sendBrowserFindText();
}

//网页全屏
void TitleBar::slot_browser_setMenu_fullScreen()
{
    emit sig_sendBrowserFullScreen();
}

//显示收藏栏
void TitleBar::slot_browser_setMenu_showCollectRecords()
{
    emit sig_sendBrowserShowCollectRecords();
}

//清空搜索记录
void TitleBar::slot_browser_setMenu_clearSearchRecords()
{
    emit sig_sendBrowserClearSearchRecords();
}

//显示收藏列表
void TitleBar::slot_browser_setMenu_showCollectList()
{
    emit sig_sendBrowserShowCollectList();
}

//显示历史记录
void TitleBar::slot_browser_setMenu_showHistories()
{
    emit sig_sendBrowserShowHistories();
}

//管理扩展
void TitleBar::slot_browser_setMenu_manageExtensions()
{
    emit sig_sendBrowserManageExtensions();
}

//清除上网痕迹
void TitleBar::slot_browser_setMenu_clearHistories()
{
    emit sig_sendBrowserClearHistories();
}

//查看源代码
void TitleBar::slot_browser_setMenu_viewSourceCode()
{
    emit sig_sendBrowserViewSourceCode();
}

//任务管理器
void TitleBar::slot_browser_setMenu_workerManager()
{
    emit sig_sendBrowserWorkerManager();
}

//控制台选项
void TitleBar::slot_browser_setMenu_consoleOptions()
{
    emit sig_sendBrowserConsoleOptions();
}

//internet选项
void TitleBar::slot_browser_setMenu_internetOptions()
{
    emit sig_sendBrowserInternetOptions();
}

//退出登录
void TitleBar::slot_browser_setMenu_logOut()
{
    emit sig_sendBrowserLogOut();
}

//常见问题
void TitleBar::slot_browser_setMenu_FAQ()
{
    emit sig_sendBrowserFAQ();
}

//帮助
void TitleBar::slot_browser_setMenu_help()
{
    emit sig_sendBrowserHelp();
}

//添加搜索引擎
void TitleBar::slot_addWebEngine()
{
        QListWidgetItem *item_0 = new QListWidgetItem(QIcon("://images/function/engine_baidu.png"),QString::fromLocal8Bit("百度搜索"));
        QListWidgetItem *item_1 = new QListWidgetItem(QIcon("://images/function/engine_360.png"),QString::fromLocal8Bit("360搜索"));
        QListWidgetItem *item_2 = new QListWidgetItem(QIcon("://images/function/engine_biying.png"),QString::fromLocal8Bit("必应搜索"));
        QListWidgetItem *item_3 = new QListWidgetItem(QIcon("://images/function/engine_google.png"),QString::fromLocal8Bit("Google搜索"));
        QListWidgetItem *item_4 = new QListWidgetItem();
        item_0->setSizeHint(QSize(m_listWdgt_engine->width(),26));
        item_1->setSizeHint(QSize(m_listWdgt_engine->width(),26));
        item_2->setSizeHint(QSize(m_listWdgt_engine->width(),26));
        item_3->setSizeHint(QSize(m_listWdgt_engine->width(),26));
        item_4->setSizeHint(QSize(m_listWdgt_engine->width(),26));
        m_listWdgt_engine->addItem(item_0);
        m_listWdgt_engine->addItem(item_1);
        m_listWdgt_engine->addItem(item_2);
        m_listWdgt_engine->addItem(item_3);
        m_listWdgt_engine->addItem(item_4);
        m_listWdgt_engine->setItemWidget(item_4,m_engineSetBtn);
}

/*设置tooltip*/
void TitleBar::setShowToolTip()
{
    ui->Btnhelp->setToolTip(QString::fromLocal8Bit("帮助"));
//    ui->Btnlogin->setToolTip(QString::fromLocal8Bit("登录"));
    ui->Btnskin->setToolTip(QString::fromLocal8Bit("皮肤"));
    ui->BtnDownload->setToolTip(QString::fromLocal8Bit("上传下载"));
//    ui->BtnHistory->setToolTip(QString::fromLocal8Bit("历史记录"));
    ui->BtnScreen->setToolTip(QString::fromLocal8Bit("截屏"));
}

void TitleBar::setUserHeadPicture(const QString &path)
{
    manager->get(QNetworkRequest(QUrl(path)));
    //获取网络图片(注意：使用的是manager的finished信号)
}

/*重写鼠标双击事件*/
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if(event->button() == Qt::LeftButton)
    emit sig_doubleClick();//主窗口调整界面大小
}

/*监听事件*/
bool TitleBar::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress && watched == this)
    {
       //搜索框---鼠标单击空白处，获得焦点
        ui->lineEditSearch->clearFocus();
        this->setFocus();
        slot_clearAllPopupUi();
    }
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);//转换为鼠标事件
    mouseIsEnterLeaveLineEdit(watched,mouseEvent);//搜索框鼠标进入离开,处理样式
    mouseIsPressReleaseLineEdit(watched,mouseEvent);//搜索框鼠标按下释放，处理历史记录
    setSelectAllTextStatus(watched,mouseEvent);//lineedit选中文本
    slot_showUserInfoWgt(watched,mouseEvent);//显示登录用户信息
    slot_callLoginTipsShow(watched,mouseEvent);//登陆提示界面
    slot_callWatchRecordShow(watched,mouseEvent);//观看历史提示界面
    if(watched == m_listWdgt_history)
    {
        if(event->type() == QEvent::Leave)
        {
            m_listWdgt_history->hide();
        }
    }

    if(watched == m_listWdgt_engine)
    {
        if(event->type() == QEvent::Leave)
        {
            m_listWdgt_engine->hide();
        }
    }
    if(watched == ui->pushButton_back)//返回按钮
        {
        if(event->type() == QEvent::Enter)
        {
            emit sig_sendCanGoBack();
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->pushButton_back->setStyleSheet("#pushButton_back{"
                                               "border-image: url(:/images/icon/back.png);"
                                               "}");
        }
    }
    if(watched == ui->pushButton_advance)//前进按钮
        {
        if(event->type() == QEvent::Enter)
        {
            emit sig_sendCanForward();
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->pushButton_advance->setStyleSheet("#pushButton_advance{"
                                                  "border-image: url(:/images/icon/advance.png);"
                                                  "}");
        }
    }

    return QWidget::eventFilter(watched,event);
}

void TitleBar::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    this->setFocusPolicy(Qt::NoFocus);
    //搜索框---设置焦点
    ui->lineEditSearch->setFocus();
    ui->lineEditSearch->setFocusPolicy(Qt::StrongFocus);
    ui->lineEdit_webSearch->setFocus();
}

void TitleBar::keyPressEvent(QKeyEvent *event)
{
    if(ui->stackedWidget->currentIndex() != 1) return;
     //Shift +  C 组合键--->添加新web tab
    if(event->key() == Qt::Key_C  &&  event->modifiers() == Qt::ShiftModifier)
    {
        slot_browser_setMenu_createTab();
    }
    //显示收藏栏
    else if(event->key() == Qt::Key_S  &&  event->modifiers() == Qt::AltModifier)
    {
        slot_browser_setMenu_showCollectRecords();
    }
//    //显示收藏夹
//    else if(event->key() == Qt::Key_D  &&  event->modifiers() == Qt::ShiftModifier)
//    {
//        slot_browser_setMenu_showCollectList();
//    }
//    //显示历史记录
//    else if(event->key() == Qt::Key_Z  &&  event->modifiers() == Qt::ShiftModifier)
//    {
//        slot_browser_setMenu_showHistories();
//    }
    qDebug() << event->key();//78（key）需要鼠标焦点在标题栏
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    if(ReleaseCapture())
    {
        QWidget* pWindow = this->window();
        if(pWindow->isTopLevel())
        {
            SendMessage(HWND(pWindow->winId()),WM_SYSCOMMAND,SC_MOVE + HTCAPTION,0);
        }
    }
    event->ignore();
}

/*根据窗口状态设置样式*/
void TitleBar::chandleMainWinStatus(bool status)
{
    if(!status)
    {
        ui->pushButton_normal->setStyleSheet("QPushButton{"
                                             "background-color: transparent;"
                                             "border-image: url(:/images/icon/normal.png);}"
                                             "QPushButton:hover{"
                                             "border: 1px solid #3C80B1;"
                                             "border-image: url(:/images/icon/normalhover.png);}");
    }
    else
    {
        ui->pushButton_normal->setStyleSheet("QPushButton{"
                                             "background-color: transparent;"
                                             "border-image: url(:/images/icon/normalmax.png);}"
                                             "QPushButton:hover{"
                                             "border: 1px solid #3C80B1;"
                                             "border-image: url(:/images/icon/normalmaxhover.png);}");
    }
}

/*槽函数 --- 处理是否显示搜索框*/
void TitleBar::isNecessaryShowSearch(int index)
{
    if(index == 0)
    {
        ui->stackedWidget->setCurrentIndex(0);//显示主页搜索框item
    }
    else if(index == 1)
    {
        ui->stackedWidget->setCurrentIndex(1);//浏览器搜索按钮
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(0);
    }
}

/*槽函数 --public 处理鼠标进入离开的样式*/
void TitleBar::mouseIsEnterLeaveLineEdit(QObject *watched, QEvent *event)
{
    //搜索框---监视
    if(watched == ui->lineEditSearch)
    {
        if(event->type() == QEvent::Leave)
        {
            ui->lineEditSearch->setStyleSheet("QLineEdit{"
                                              "color:#cccccc;"
                                              "font: 10pt Microsoft YaHei;"
                                              "padding-left:15px;"
                                              "background-color: #3c3842;"
                                              "border:1px solid transparent;"
                                              "border-top-left-radius:18;"
                                              "border-bottom-left-radius:18;"
                                              "border-top-right-radius:18;"
                                              "border-bottom-right-radius:18;"
                                              "}");
            ui->BtnSearch->setStyleSheet("QPushButton{"
                                         "background-color:#44444f;"
                                         "color:#ff5c38;"
                                         "border-top-right-radius:18;"
                                         "border-bottom-right-radius:18;"
                                         "}");
        }
        else if(event->type() == QEvent::Enter)
        {
            ui->lineEditSearch->setStyleSheet("QLineEdit{"
                                              "color:#aeada7;"
                                              "font: 10pt Microsoft YaHei;"
                                              "padding-left:15px;"
                                              "background-color: #3a2f36;"
                                              "border:1px solid #00beff;"
                                              "border-top-left-radius:18;"
                                              "border-bottom-left-radius:18;"
                                              "border-top-right-radius:18;"
                                              "border-bottom-right-radius:18;"
                                              "}");
            ui->BtnSearch->setStyleSheet("QPushButton{"
                                         "background-color:#ff5246;"
                                         "color:white;"
                                         "padding:-1px;"
                                         "border-top-right-radius:18;"
                                         "border-bottom-right-radius:18;"
                                         "}");
        }
    }

    if(watched == ui->BtnSearch)
    {
        if(event->type() == QEvent::Leave)
        {
            ui->lineEditSearch->setStyleSheet("QLineEdit{"
                                              "color:#cccccc;"
                                              "font: 10pt Microsoft YaHei;"
                                              "padding-left:15px;"
                                              "background-color: #3c3842;"
                                              "border:1px solid transparent;"
                                              "border-top-left-radius:18;"
                                              "border-bottom-left-radius:18;"
                                              "border-top-right-radius:18;"
                                              "border-bottom-right-radius:18;"
                                              "}");
            ui->BtnSearch->setStyleSheet("QPushButton{"
                                         "background-color:#44444f;"
                                         "color:#aeada7;"
                                         "border-top-right-radius:18;"
                                         "border-bottom-right-radius:18;"
                                         "}");
        }
        else if(event->type() == QEvent::Enter)
        {
            ui->lineEditSearch->setStyleSheet("QLineEdit{"
                                              "font: 10pt Microsoft YaHei;"
                                              "padding-left:15px;"
                                              "background-color: #3a2f36;"
                                              "border:1px solid #00beff;"
                                              "border-top-left-radius:18;"
                                              "border-bottom-left-radius:18;"
                                              "border-top-right-radius:18;"
                                              "border-bottom-right-radius:18;"
                                              "}");
            ui->BtnSearch->setStyleSheet("QPushButton{"
                                         "background-color:#ff5246;"
                                         "color:white;"
                                         "padding:-1px;"
                                         "border-top-right-radius:18;"
                                         "border-bottom-right-radius:18;"
                                         "}");
        }
    }
}

/*搜索框按下释放*/
void TitleBar::mouseIsPressReleaseLineEdit(QObject *watched, QEvent *event)
{
    //搜索框---监视
    if(watched == ui->lineEditSearch)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            int x = this->mapToGlobal(ui->lineEditSearch->pos()+ui->stackedWidget->pos()+this->pos()).x();
            int y = this->mapToGlobal(ui->lineEditSearch->pos()+ui->stackedWidget->pos()+this->pos()).y();
            int height = ui->lineEditSearch->height();
            m_searchForm->setGeometry(x+10,y+height-2,ui->lineEditSearch->width()-26,m_searchForm->height());
            m_searchForm->raise();//必须提升界面所处层次
            m_searchForm->show();
        }
        else if(event->type() == QEvent::FocusOut)
        {
            m_searchForm->hide();
        }
    }
}

//void TitleBar::serarchLineEditFacous(QObject *watched, QEvent *event)
//{

//}

/*左上角登陆*/
void TitleBar::slot_switchToLoginPage(int mark, QString nick)
{
    if(mark  == 0)//未登录
    {
        ui->stackedWidget_login->setCurrentIndex(0);
    }
    else if(mark  == 1)//已登录
    {
        ui->stackedWidget_login->setCurrentIndex(1);//用户信息界面
        QFont font;
        font.setPixelSize(10);
        QFontMetrics   fontMetric = QFontMetrics(font);
        QString text = fontMetric.elidedText(nick,Qt::ElideRight,80,0);//19个字宽以后，省略为...(10x19，字号x字数,设置像素，字点大小就为-1，设置字点大小，像素就为-1)
        ui->pushButton_usernick->setText(text);
        ui->pushButton_usernick->setToolTip(nick);
        m_loginForm->slot_setPersonVipPage(1);
        emit sig_userSign_in(nick);//上线 发出带用户名
        m_signStatus = true;//登录状态
    }

}

//设置当前用户等级
void TitleBar::slot_setCurrentUserGrade(int grade)
{
    QPixmap pix;
    switch (grade) {
    case 0://游客
    {
        pix.load("://images/icon/comment_vip.png");
    }
        break;
    case 1://普通
    {
        pix.load("://images/icon/comment_vip.png");
    }
        break;
    case 2://会员
    {
        pix.load("://images/icon/comment_vip.png");
    }
        break;
    case 3://超级会员
    {
        pix.load("://images/icon/comment_vip.png");
    }
        break;
    default:
        break;
    }
    ui->label_usermark->setPixmap(pix);
    ui->label_usermark->setScaledContents(true);
}

void TitleBar::slot_setButtonHelpEmitItem()
{
    QAction *action = qobject_cast<QAction *>(sender());
    qDebug() << action->text();
    if(action->text() == QString::fromLocal8Bit("个人账户"))
    {
        emit sig_filesUploadDownLoad(5,4);
    }
    else if(action->text() == QString::fromLocal8Bit("系统设置"))
    {
        emit sig_settingHelpItem(1);
    }
    else if(action->text() == QString::fromLocal8Bit("网络资源"))
    {
        emit sig_settingHelpItem(2);
    }
    else if(action->text() == QString::fromLocal8Bit("问题帮助"))
    {
        emit sig_settingHelpItem(3);
    }
    else if(action->text() == QString::fromLocal8Bit("本地视频"))
    {
        emit sig_settingHelpItem(4);
    }
    else if(action->text() == QString::fromLocal8Bit("网络视频"))
    {
//        emit sig_settingHelpItem(5);
    }
    else if(action->text() == QString::fromLocal8Bit("软件下载"))
    {
        emit sig_settingHelpItem(6);
    }
    else if(action->text() == QString::fromLocal8Bit("退出软件"))
    {
        emit sig_settingHelpItem(7);
    }
}

void TitleBar::slot_receivedListItemText(QString text)
{
    if(text.isEmpty()) return;
    QString addUrl = judgeUrlType(text);//加head
    ui->lineEdit_webSearch->setText(addUrl);
    emit sig_sendInputNewUrl(addUrl);
}

void TitleBar::slot_setWebLineEditCurentUrl(QUrl url)
{
    qDebug() <<QString::fromLocal8Bit("标题栏地址显示接收到最新的地址是：")<< url;
    if(!url.isEmpty())
    {
        ui->lineEdit_webSearch->setText(url.toString());
        ui->lineEdit_webSearch->setCursorPosition(0);
    }  
}

void TitleBar::slot_clearWebLineEditText()
{
    ui->lineEdit_webSearch->clear();
    ui->lineEdit_webSearch->setCursorPosition(0);
}

void TitleBar::slot_setWebProgressBarValue(int value)
{
    ui->webProgressBar->setValue(value);
    if(value == 100)
    {
//        QTimer::singleShot(1000,this,SLOT(slot_resetWebProgressBarValue()));
    }
}

void TitleBar::slot_resetWebProgressBarValue()
{
    ui->webProgressBar->setValue(0);
    QGraphicsOpacityEffect *opacity = new QGraphicsOpacityEffect(this);
//    opacity->setOpacity(0.5); //设置透明度0.5,透明范围：[0,1]
    ui->webProgressBar->setGraphicsEffect(opacity);//应用到需要透明变化的控件；
    //使用属性动画类让控件在透明度范围内变化
    QPropertyAnimation *opacityAnimation = new QPropertyAnimation(opacity, "opacity");
    opacityAnimation->setDuration(30000); //动效时长3s
    opacityAnimation->setStartValue(0);
    opacityAnimation->setEndValue(1);
    opacityAnimation->start();
}

//设置头像
void TitleBar::slot_replyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        m_headPixmap.loadFromData(reply->readAll());
        ui->label_userHead->setPixmap(m_headPixmap);
        ui->label_userHead->setScaledContents(true);
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("请求错误：")<<reply->errorString();
        QPixmap pixmap(":/images/icon/kugou.ico");
        ui->label_userHead->setPixmap(pixmap);
        ui->label_userHead->setScaledContents(true);
    }
}

//接收tabbar添加一个空白网页的请求
void TitleBar::slot_receiveBlankWebTab()
{
    QString blankUrl = judgeUrlType("");//无搜索内容
    if(blankUrl.isEmpty()) return;
    emit sig_sendBlankUrl(blankUrl);
    qDebug() << "m_titleBar received add blankurl = " << blankUrl;
}

void TitleBar::slot_clearAllPopupUi()
{
    if(!m_loginForm->isHidden())        m_loginForm->hide();
    if(!m_searchForm->isHidden())       m_searchForm->hide();
    if(!m_listWdgt_history->isHidden()) m_listWdgt_history->hide();
    if(!m_listWdgt_engine->isHidden())  m_listWdgt_engine->hide();
    if(!LoginTip::getInstance()->isHidden()) LoginTip::getInstance()->hide();
}

void TitleBar::slot_initCollectRecordListWgt(const QString &text)
{
    if(text.isEmpty()) return;
    bool valid = judgeCollectUrlExist(text);//判断是否存在
    if(!valid)//没有则收藏
    {
        QListWidgetItem *item = new QListWidgetItem(QIcon(":/images/function/collect_list_item.png"),text);
        m_listWdgt_colloect->insertItem(0,item);
    }
    else//有，则不做任何处理
    {
        QMessageBox::information(this,QString::fromLocal8Bit("提示"),
                                 QString::fromLocal8Bit("网址已收藏！"),
                                 QString::fromLocal8Bit("是"));
    }
    slot_setCurrentWebSiteCollectStatus(text);//收藏以后，样式在做一次处理
}

void TitleBar::slot_clearColletRecords()
{
    ui->stackedWidget_login->setCurrentIndex(0);//返回登录注册界面
    m_listWdgt_history->clear();
    m_listWdgt_colloect->clear();
    slot_setCurrentWebSiteCollectStatus(ui->lineEdit_webSearch->text());//切换用户以后，样式在做一次处理
}

void TitleBar::slot_showPersonLogin()
{
//    LoginPersonInfo::getInstance()->showLoginWindow(0);
    NewLoginForm::getInstance()->slot_switchWinType(ShowType::LoginWin_1);
}

void TitleBar::slot_receivedLoginInfo(const QString &name, const QString &head, int grade)
{
    //标题栏
    setUserHeadPicture(head);//设置用户头像
    slot_switchToLoginPage(1,name);//设置用户名称
    slot_setCurrentUserGrade(grade);//设置等级图标
    //浮动界面
    m_headHover->slot_setCurrentUserInfo(head,name,grade,QString::fromLocal8Bit("欢迎回来^_^"));
}

//退出登录
void TitleBar::slot_receivedSign_out()
{
    emit sig_userSign_out(ui->pushButton_usernick->text());//下线带用户名
//    m_loginForm->slot_setPersonVipPage(0);
    m_signStatus = false;//未登录状态
}

/*槽函数 --- 获取系统时间并且显示*/
void TitleBar::getSystemTimeShow()
{
    QDateTime curtime = QDateTime::currentDateTime();
    QString strTime = curtime.toString("yyyy-MM-dd hh:mm:ss");
    ui->lcdNumber->display(strTime);
}

/*槽函数 --- 地址栏显示当前url*/
void TitleBar::setLineEditAddress(const QUrl url)
{
    Q_UNUSED(url);
//    ui->lineEdit_webSearch->setText(url.toString());
}

void TitleBar::showLoginForm()
{
    if(m_loginForm)
    {
        if(!m_loginForm->isHidden())
        {
            m_loginForm->hide();
        }
        else
        {
            int x = ui->Btnlogin->parentWidget()->mapToGlobal(ui->Btnlogin->pos()).x();
            int y = ui->Btnlogin->parentWidget()->mapToGlobal(ui->Btnlogin->pos()).y();
            int h = ui->Btnlogin->height();
            m_loginForm->setGeometry(x-m_loginForm->width()/2+8,y+h-2,m_loginForm->width(),m_loginForm->height());
            m_loginForm->raise();
            m_loginForm->show();
        }
    }
    else
    {
        m_loginForm = new Login();
        int x = ui->Btnlogin->parentWidget()->mapToGlobal(ui->Btnlogin->pos()).x();
        int y = ui->Btnlogin->parentWidget()->mapToGlobal(ui->Btnlogin->pos()).y();
        int h = ui->Btnlogin->height();
        m_loginForm->setGeometry(x-310/2,y+h+10,m_loginForm->width(),m_loginForm->height());
        m_loginForm->raise();
        m_loginForm->show();
    }
}

/*皮肤设置*/
void TitleBar::showMySkin()
{
    if(m_mySkin)
    {
        if(!m_mySkin->isHidden())
        {
            m_mySkin->hide();
        }
        else
        {
//            int x = ui->Btnskin->parentWidget()->mapToGlobal(ui->Btnskin->pos()).x();
//            int y = ui->Btnskin->parentWidget()->mapToGlobal(ui->Btnskin->pos()).y();
//            int h = ui->Btnskin->height();
//            m_mySkin->setGeometry(x-150,y+h+10,m_mySkin->width(),m_mySkin->height());
            m_mySkin->raise();
            m_mySkin->exec();
        }
    }
    else
    {
        m_mySkin = new MySkin();
//        int x = ui->Btnskin->parentWidget()->mapToGlobal(ui->Btnskin->pos()).x();
//        int y = ui->Btnskin->parentWidget()->mapToGlobal(ui->Btnskin->pos()).y();
//        int h = ui->Btnskin->height();
//        m_mySkin->setGeometry(x-150,y+h+10,m_mySkin->width(),m_mySkin->height());
        m_mySkin->raise();
        m_mySkin->exec();
    }
}



void TitleBar::receiveMainFormClose()
{
    m_loginForm->close();
    m_loginForm->receiveMainWinCloseAppSignal();
}

/*观看历史提示界面*/
void TitleBar::slot_callWatchRecordShow(QObject *watched, QEvent *event)
{
    if(watched == ui->BtnHistory)//登录按钮
    {
        if(event->type() == QEvent::Enter)//进入
        {
            int x = ui->BtnHistory->parentWidget()->mapToGlobal(ui->BtnHistory->pos()).x();
            int y = ui->BtnHistory->parentWidget()->mapToGlobal(ui->BtnHistory->pos()).y();
            int h = ui->BtnHistory->height();
            WatchRecords::getInstance()->setGeometry(x- WatchRecords::getInstance()->width()/2+8,
                                                 y+h-2,//留出5px防止鼠标超出按钮位置
                                                 WatchRecords::getInstance()->width(),
                                                 WatchRecords::getInstance()->height());
            WatchRecords::getInstance()->show();

        }
        else if(event->type() == QEvent::Leave)//离开
        {
            qDebug() << QString(u8"鼠标(转换为局部坐标)：") << mapFromGlobal(QCursor::pos());
            QRect rect = QRect(ui->BtnHistory->geometry().x()+135,ui->BtnHistory->geometry().y(),25,400+20);//鼠标真实横坐标比控件横坐标大140
            qDebug() <<QString(u8"处理后的矩形：") << rect;
            if(!rect.contains(mapFromGlobal(QCursor::pos())))
            {
                WatchRecords::getInstance()->hide();
            }
        }
    }
}

//登陆提示界面
void TitleBar::slot_callLoginTipsShow(QObject *watched, QEvent *event)
{
    if(watched == ui->Btnlogin)//登录按钮
    {
        if(event->type() == QEvent::Enter)//进入
        {
            if(!m_signStatus)//未登录状态
            {
                int x = ui->Btnlogin->parentWidget()->mapToGlobal(ui->Btnlogin->pos()).x();
                int y = ui->Btnlogin->parentWidget()->mapToGlobal(ui->Btnlogin->pos()).y();
                int h = ui->Btnlogin->height();
                LoginTip::getInstance()->setGeometry(x- LoginTip::getInstance()->width() + 78,
                                                     y,//留出2px防止鼠标超出按钮位置
                                                     LoginTip::getInstance()->width(),
                                                     LoginTip::getInstance()->height());
                LoginTip::getInstance()->show();
            }
            else//登录状态
            {
                showLoginForm();
            }
        }
        else if(event->type() == QEvent::Leave)//离开
        {
            if(!m_signStatus)
            {
                //这里的意思是：虽然离开按钮，但是鼠标却在矩形内，依旧不能隐藏界面
                qDebug() << QString(u8" 登录框矩形：") << ui->Btnlogin->geometry();//1132 15, 20 ,20
                qDebug() << QString(u8"鼠标(转换为局部坐标)：") << mapFromGlobal(QCursor::pos());
                QRect rect = QRect(ui->Btnlogin->geometry().x()+135,ui->Btnlogin->geometry().y(),25,193+20);//鼠标真实横坐标比控件横坐标大140
                qDebug() <<QString(u8"处理后的矩形：") << rect;
                if(!rect.contains(mapFromGlobal(QCursor::pos())))
                {
                    LoginTip::getInstance()->hide();//1275 - 1295  15-35
                    //                qDebug() << QString(u8"鼠标不在矩形内");
                }
            }
            else
            {
                QRect rect = QRect(ui->Btnlogin->geometry().x()+135,ui->Btnlogin->geometry().y(),25,400+20);//鼠标真实横坐标比控件横坐标大140
                if(!rect.contains(mapFromGlobal(QCursor::pos())))
                {
                   m_loginForm->hide();
                }

            }
        }
    }
}


void TitleBar::slot_showUserInfoWgt(QObject *watched, QEvent *event)
{
    if(watched == ui->label_userHead && event->type() == QEvent::Enter)
    {
        if(m_headHover)
        {
            int x = ui->label_userHead->parentWidget()->mapToGlobal(ui->label_userHead->pos()).x();
            int y = ui->label_userHead->parentWidget()->mapToGlobal(ui->label_userHead->pos()).y();
            m_headHover->setGeometry(x,y,m_headHover->width(),m_headHover->height());
            m_headHover->raise();
            m_headHover->show();
        }
    }
}

//鼠标按下选中文字
void TitleBar::setSelectAllTextStatus(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEdit_webSearch)
    {
        if(event->type() == QEvent::FocusIn)
        {
            //FocusIn屏蔽了全选功能
            QTimer::singleShot(0,this,[=](){ui->lineEdit_webSearch->selectAll();});
        }
    }
    if(watched == ui->lineEdit_simpSearch)
    {
        if(event->type() == QEvent::FocusIn)
        {
            QTimer::singleShot(0,this,[=](){ui->lineEdit_simpSearch->selectAll();});
        }
    }
}


