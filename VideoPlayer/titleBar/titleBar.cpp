#include "TitleBar.h"
#include "ui_TitleBar.h"
#include <QDebug>
#include <QDateTime>
#include <QRegExp>
#include <QRegExpValidator>
#include <QDesktopServices>

TitleBar::TitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TitleBar)
{
    ui->setupUi(this);
    this->setFixedHeight(40);
    initWorker();//初始化
    chandleSignalAndSLots();
}

/*析构*/
TitleBar::~TitleBar()
{
    delete ui;
    delete m_loginForm;
    delete m_searchForm;
}

/*初始化工作*/
void TitleBar::initWorker()
{
    ui->stackedWidget_login->setCurrentIndex(0);//左上角登录stackwidget
    ui->pushButton_userlogin->setFlat(true);
    ui->pushButton_userregis->setFlat(true);

    //LCD数字显示
    ui->lcdNumber->setDigitCount(20);//显示数量（个数）
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setPalette(Qt::red);//显示文字颜色，不怎么生效
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
    ui->pushButton_home->setToolTip(QString::fromLocal8Bit("主页"));
    //后退
    ui->pushButton_back->setFixedSize(20,20);
    ui->pushButton_back->setFlat(true);
    ui->pushButton_back->setToolTip(QString::fromLocal8Bit("后退"));
    //刷新
    ui->pushButton_freshen->setFixedSize(20,20);
    ui->pushButton_freshen->setFlat(true);
    ui->pushButton_freshen->setToolTip(QString::fromLocal8Bit("刷新"));
    //前进
    ui->pushButton_advance->setFixedSize(20,20);
    ui->pushButton_advance->setFlat(true);
    ui->pushButton_advance->setToolTip(QString::fromLocal8Bit("前进"));

    ui->lineEdit_webSearch->setFixedHeight(28);
    ui->lineEdit_webSearch->setText(QString::fromLocal8Bit("https://www.baidu.com/"));//默认显示的网址
    ui->lineEdit_webSearch->setPlaceholderText(QString::fromLocal8Bit("请输入网址"));
    //正则校验  url校验
//    QRegExp regExp("^[a-zA-z]+://(\w+(-\w+)*)(\.(\w+(-\w+)*))*(\?\S*)?$");
//    QRegExpValidator *expval = new QRegExpValidator(regExp,this);
//    ui->lineEdit_webSearch->setValidator(expval);
    ui->Btn_expand->setFixedSize(30,28);

    ui->Btn_expand->setFlat(true);
    ui->Btn_expand->setToolTip(QString::fromLatin1("点击查看历史记录"));
    ui->lineEditSearch->installEventFilter(this);//输入检索字
    ui->BtnSearch->installEventFilter(this);
    ui->lineEdit_webSearch->installEventFilter(this);//输入网址

    m_searchForm = new SearchForm();//不指定父控件，也不加布局，需要手动删除
    m_searchForm->setObjectName(QString::fromLocal8Bit("m_searchForm"));

    m_loginForm = new Login();
    m_loginForm->setObjectName(QString::fromLocal8Bit("m_loginForm"));

    m_mySkin = new MySkin();
    m_mySkin->setObjectName(QString::fromLocal8Bit("m_mySkin"));

    slot_switchToLoginPage(1,QString::fromLocal8Bit("测试测名称8020"));
}


/*处理信号与槽函数*/
void TitleBar::chandleSignalAndSLots()
{
    connect(ui->pushButton_logo,&QPushButton::clicked,[=](){ ui->stackedWidget_login->setCurrentIndex(1);});
    connect(ui->pushButton_logo2,&QPushButton::clicked,[=](){ ui->stackedWidget_login->setCurrentIndex(0);});
    //登录
    connect(ui->pushButton_userlogin,&QPushButton::clicked,[=](){
        LoginPersonInfo::getInstance()->showLoginWindow(0);
    });

    //注册
    connect(ui->pushButton_userregis,&QPushButton::clicked,[=](){
        LoginPersonInfo::getInstance()->showLoginWindow(1);
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
    connect(ui->BtnDownload,&QPushButton::clicked,[=](){emit sig_filesUploadDownLoad(5,4);});//上传下载
    //历史记录
    connect(ui->BtnHistory,&QPushButton::clicked,[=](){emit sig_historyDownload(5,0);});//历史记录
    //截屏
    connect(ui->BtnScreen,&QPushButton::clicked,[=](){emit sig_screenPicture();});//截屏


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
    connect(ui->Btnlogin,&QPushButton::clicked,[=](){qDebug() << "login had clicked!"; showLoginForm();});
    //历史记录记录搜索历史
//    connect(this,&TitleBar::sig_sendNewSearch,m_searchForm,&SearchForm::addHistoryItem);

    //网址输入框---回车键处理
    connect(ui->lineEdit_webSearch,&QLineEdit::returnPressed,[=](){
        QString url = ui->lineEdit_webSearch->text().trimmed();
        emit sig_sendInputNewUrl(url);
        qDebug() << "emit sig_sendInputNewUrl(url);"<< url;
    });

    connect(ui->lineEditSearch,&QLineEdit::returnPressed,[=](){
        QString his = ui->lineEditSearch->text().trimmed();
        m_searchForm->addHistoryItem(his);
        qDebug() << "emit sig_sendNewSearch(his);";
        //处理其他事件
        //鼠标进入样式改变
    });
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

/*设置tooltip*/
void TitleBar::setShowToolTip()
{
    ui->Btnhelp->setToolTip(QString::fromLocal8Bit("帮助"));
    ui->Btnlogin->setToolTip(QString::fromLocal8Bit("登录"));
    ui->Btnskin->setToolTip(QString::fromLocal8Bit("皮肤"));
    ui->BtnDownload->setToolTip(QString::fromLocal8Bit("上传下载"));
    ui->BtnHistory->setToolTip(QString::fromLocal8Bit("历史记录"));
    ui->BtnScreen->setToolTip(QString::fromLocal8Bit("截屏"));
}

/*重写鼠标双击事件*/
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit sig_doubleClick();//主窗口调整界面大小
}

/*监听事件*/
bool TitleBar::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);//转换为鼠标事件
    mouseIsEnterLeaveLineEdit(watched,mouseEvent);//搜索框鼠标进入离开,处理样式
    mouseIsPressReleaseLineEdit(watched,mouseEvent);//搜索框鼠标按下释放，处理历史记录
//    if(watched == ui->lineEdit_webSearch)
//    {
//        if(event->type() == QEvent::Enter)
//        {
//            connect(ui->lineEdit_webSearch,&QLineEdit::returnPressed,[=](){
//                QString url = ui->lineEdit_webSearch->text().trimmed();
//                emit sig_sendNewUrl(url);
//                qDebug() << "emit sig_sendNewUrl(url);";
//                //处理其他事件
//                //鼠标进入样式改变

//            });
//        }
//    }

//    if(watched == ui->lineEditSearch)
//    {
//        if(event->type() == QEvent::Enter)
//        {
//            connect(ui->lineEditSearch,&QLineEdit::returnPressed,[=](){
//                QString his = ui->lineEditSearch->text().trimmed();
//                m_searchForm->addHistoryItem(his);
//                qDebug() << "emit sig_sendNewSearch(his);";
//                //处理其他事件
//                //鼠标进入样式改变

//            });
//        }
//    }
    return QWidget::eventFilter(watched,event);
}

void TitleBar::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    this->setFocusPolicy(Qt::NoFocus);
    ui->lineEditSearch->setFocus();
    ui->lineEditSearch->setFocusPolicy(Qt::StrongFocus);
    ui->lineEdit_webSearch->setFocus();
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
        ui->stackedWidget->setCurrentIndex(2);
    }
}

/*槽函数 --public 处理鼠标进入离开的样式*/
void TitleBar::mouseIsEnterLeaveLineEdit(QObject *watched, QEvent *event)
{
    if(watched == ui->lineEditSearch)
    {
        if(event->type() == QEvent::Leave)
        {
            ui->lineEditSearch->setStyleSheet("QLineEdit{"
                                              "color:#cccccc;"
                                              "font: 10pt Microsoft YaHei;"
                                              "margin-right:-3px;"
                                              "padding-left:15px;"
                                              "background-color: #3c3842;"
                                              "border:1px solid transparent;"
                                              "border-top-left-radius:18;"
                                              "border-bottom-left-radius:18;"
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
                                              "margin-right:-3px;"
                                              "border-right:-2px;"
                                              "background-color: #3a2f36;"
                                              "border:1px solid #ff5c38;"
                                              "border-top-left-radius:18;"
                                              "border-bottom-left-radius:18;"
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
                                              "margin-right:-3px;"
                                              "padding-left:15px;"
                                              "background-color: #3c3842;"
                                              "border:1px solid transparent;"
                                              "border-top-left-radius:18;"
                                              "border-bottom-left-radius:18;"
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
                                              "margin-right:-3px;"
                                              "padding-left:15px;"
                                              "border-right:-2px;"
                                              "background-color: #3a2f36;"
                                              "border:1px solid #ff5c38;"
                                              "border-top-left-radius:18;"
                                              "border-bottom-left-radius:18;"
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
    if(watched == ui->lineEditSearch)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            int x = this->mapToGlobal(ui->lineEditSearch->pos()+ui->stackedWidget->pos()+this->pos()).x();
            int y = this->mapToGlobal(ui->lineEditSearch->pos()+ui->stackedWidget->pos()+this->pos()).y();
            int height = ui->lineEditSearch->height();
            m_searchForm->setGeometry(x+10,y+height-2,ui->lineEditSearch->width()+ui->BtnSearch->width()-26,m_searchForm->height());
            m_searchForm->raise();//必须提升界面所处层次
            m_searchForm->show();
        }
    }
}

void TitleBar::serarchLineEditFacous(QObject *watched, QEvent *event)
{

}

/*左上角登陆*/
void TitleBar::slot_switchToLoginPage(int mark, QString nick)
{
    if(mark  == 0)//未登录
    {
        ui->stackedWidget_login->setCurrentIndex(0);
    }
    else if(mark  == 1)//已登录
    {
        ui->stackedWidget_login->setCurrentIndex(1);
        ui->pushButton_usernick->setText(nick);
    }

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
        emit sig_settingHelpItem(5);
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

void TitleBar::slot_setWebLineEditCurentUrl(QUrl url)
{
    qDebug() <<QString::fromLocal8Bit("接收到最新的地址是：")<< url;
    if(!url.isEmpty())
    {
        ui->lineEdit_webSearch->setText(url.toString());
    }
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
    qDebug() << "show login form";
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
            m_loginForm->setGeometry(x-310/2,y+h+10,m_loginForm->width(),m_loginForm->height());
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
            int x = ui->Btnskin->parentWidget()->mapToGlobal(ui->Btnskin->pos()).x();
            int y = ui->Btnskin->parentWidget()->mapToGlobal(ui->Btnskin->pos()).y();
            int h = ui->Btnskin->height();
            m_mySkin->setGeometry(x-150,y+h+10,m_mySkin->width(),m_mySkin->height());
            m_mySkin->raise();
            m_mySkin->show();
        }
    }
    else
    {
        m_mySkin = new MySkin();
        int x = ui->Btnskin->parentWidget()->mapToGlobal(ui->Btnskin->pos()).x();
        int y = ui->Btnskin->parentWidget()->mapToGlobal(ui->Btnskin->pos()).y();
        int h = ui->Btnskin->height();
        m_mySkin->setGeometry(x-150,y+h+10,m_mySkin->width(),m_mySkin->height());
        m_mySkin->raise();
        m_mySkin->show();
    }
}



void TitleBar::receiveMainFormClose()
{
    m_loginForm->close();
    m_loginForm->receiveMainWinCloseAppSignal();
}


