#include "CreateCenter.h"
#include "ui_CreateCenter.h"

//#ifdef Q_OS_WIN
//#include <qt_windows.h>
//#include <Windows.h>
//#include <windowsx.h>
//#pragma comment (lib,"user32.lib")
//#endif
CreateCenter* CreateCenter::m_pInstance = nullptr;

CreateCenter::CreateCenter(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::CreateCenter)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
    this->resize(1350,830);
    this->setMinimumSize(QSize(1100,700));
    this->setTitleBarMoveArea(m_ctitleBar,1);
    this->setWindowTitle(QString::fromLocal8Bit("创作中心"));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);
    this->setAttribute(Qt::WA_StyledBackground,true);
}

CreateCenter::~CreateCenter()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

CreateCenter *CreateCenter::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new CreateCenter();
    }
    return m_pInstance;
}

void CreateCenter::exec_()
{
    ui->stackedWidget_switch->setCurrentWidget(ui->page_login);
    ui->tabWidget_create->setCurrentWidget(m_perCenter);
    //清空上一次用户下旧内容
    m_doneWorks->clearOldContent();
    m_dataAnaly->clearContents();

    bool isOnline = dataBase::getInstance()->getCurrentUserOnline();
    if(isOnline)//在线
    {
        ui->label_loginbg->setLoginTips(true);
//        m_ctitleBar->setUserIcon(true,dataBase::getInstance()->getCurrentUserHead());
    }
    else
    {
        ui->label_loginbg->setLoginTips(false);
//        m_ctitleBar->setUserIcon(false,"://images/icon/kugou.ico");
    }
    this->show();
}

void CreateCenter::initWorkUI()
{
    this->layout()->setContentsMargins(1,1,1,1);

    m_perCenter = new PerCenter();
    m_perCenter->setObjectName(QString::fromUtf8("m_perCenter"));

    m_maker = new Maker();
    m_maker->setObjectName(QString::fromUtf8("m_maker"));

    m_doneWorks = new DoneWorks();
    m_doneWorks->setObjectName(QString::fromUtf8("m_doneWorks"));

    m_income = new Income();
    m_income->setObjectName(QString::fromUtf8("m_income"));

    m_dataAnaly = new DataAnalysis();
    m_dataAnaly->setObjectName(QString::fromUtf8("m_dataAnaly"));

    ui->tabWidget_create->addTab(m_perCenter,QString(u8"个人中心"));
    ui->tabWidget_create->addTab(m_maker,QString(u8"创作中心"));
    ui->tabWidget_create->addTab(m_doneWorks,QString(u8"我的作品"));
    ui->tabWidget_create->addTab(m_income,QString(u8"创作收益"));
    ui->tabWidget_create->addTab(m_dataAnaly,QString(u8"我的数据"));

    m_ctitleBar = new CreTitleBar(this);
    m_ctitleBar->setObjectName(QString::fromUtf8("m_ctitleBar"));
    ui->verticalLayout_all->insertWidget(0,m_ctitleBar);//垂直布局插入到顶端

    ui->stackedWidget_switch->setCurrentWidget(ui->page_login);//整体转换
    ui->tabWidget_create->setCurrentWidget(m_perCenter);
}

void CreateCenter::handleSignalsAndSlots()
{
    //tab切换
    connect(ui->tabWidget_create,&QTabWidget::currentChanged,[=](int index){
        if(ui->tabWidget_create->widget(index) == m_doneWorks)//已完成作品列表
        {
           m_doneWorks->slot_initUserAlbums();//初始化对应用户的专辑组
           m_doneWorks->slot_initUserGroups();//初始化对应用户的合集组
           QStringList list_counts = dataBase::getInstance()->creator_getAllTagsWorkCounts();//获取各个类型的媒体数量
           m_doneWorks->slot_setUserTagsWorkCounts(list_counts);
        }
        else if(ui->tabWidget_create->widget(index) == m_perCenter)//个人中心
        {
            m_perCenter->setCurUserInfo(dataBase::getInstance()->getCurrentUserName(),dataBase::getInstance()->getCurrentUserHeadPix());
        }
        else if(ui->tabWidget_create->widget(index) == m_maker)//上传列表
        {

        }
        else if(ui->tabWidget_create->widget(index) == m_income)//个人收入
        {
//            m_income->getUserIncomeRecord();
        }
        else if(ui->tabWidget_create->widget(index) == m_dataAnaly)//数据分析
        {

        }
        qDebug() << QString(u8"当前tab索引号：%1").arg(index);
    });

    //接收标题栏
    //关闭
    connect(m_ctitleBar,&CreTitleBar::sig_win_close,[=](){this->close();});
    //最小化
    connect(m_ctitleBar,&CreTitleBar::sig_win_min,[=](){this->showMinimized();});
    //还原
    connect(m_ctitleBar,&CreTitleBar::sig_win_restore,[=](bool restore){
        if(restore)
        {
            this->showMaximized();
        }
        else
        {
            this->showNormal();
        }
    });


    //小窗口关闭
    connect(ui->label_loginbg,&MoveLabel::sig_sendClose,[=](){
        this->close();
    });

    //登录
    connect(ui->label_loginbg,&MoveLabel::sig_sendLogin,[=](){
        ui->stackedWidget_switch->setCurrentWidget(ui->page_create);
        ui->tabWidget_create->setCurrentWidget(m_perCenter);
    });

    //跳转页面
    connect(m_perCenter,&PerCenter::sig_person_topage,[=](int numpage){
        switch (numpage) {
        case 0://我的首页
        {
            ui->tabWidget_create->setCurrentWidget(m_perCenter);
        }
            break;
        case 1://账号数据
        {
            ui->tabWidget_create->setCurrentWidget(m_dataAnaly);
        }
            break;
        case 2://等级权益
        {
            ui->tabWidget_create->setCurrentWidget(m_perCenter);
        }
            break;
        case 3://视频管理
        {
            ui->tabWidget_create->setCurrentWidget(m_doneWorks);
        }
            break;
        case 4://专辑管理
        {
            ui->tabWidget_create->setCurrentWidget(m_doneWorks);
//            SortDialog::getInstance()->exec();
        }
            break;
        case 5://合集管理
        {
            ui->tabWidget_create->setCurrentWidget(m_doneWorks);
        }
            break;
        case 6://视频数据
        {
            ui->tabWidget_create->setCurrentWidget(m_perCenter);
        }
            break;
        case 7://收益数据
        {
            ui->tabWidget_create->setCurrentWidget(m_income);
        }
            break;
        default:
            break;
        }
    });

    connect(m_perCenter,&PerCenter::sig_person_polish,[=](){
        ui->tabWidget_create->setCurrentWidget(m_maker);
    });
}

void CreateCenter::setInstallEventer()
{
    m_ctitleBar->installEventFilter(this);
    ui->tabWidget_create->installEventFilter(this);
}


bool CreateCenter::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_ctitleBar)
    {
        if(event->type() == QEvent::Enter)
        {
            this->setCursor(Qt::ArrowCursor);
        }
    }
    if(watched == ui->tabWidget_create && event->type() == QEvent::Enter)
    {
        ui->tabWidget_create->setCursor(Qt::ArrowCursor);
    }
    return QWidget::eventFilter(watched,event);
}
