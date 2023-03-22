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
    bool isOnline = dataBase::getInstance()->getCurrentUserOnline();
    if(isOnline)//在线
    {
        ui->label_loginbg->setLoginTips(true);
        m_ctitleBar->setUserIcon(true,dataBase::getInstance()->getCurrentUserHead());
    }
    else
    {
        ui->label_loginbg->setLoginTips(false);
        m_ctitleBar->setUserIcon(false,"://images/icon/kugou.ico");
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

    ui->tabWidget_create->addTab(m_perCenter,QString(u8"个人中心"));
    ui->tabWidget_create->addTab(m_maker,QString(u8"创作中心"));
    ui->tabWidget_create->addTab(m_doneWorks,QString(u8"我的作品"));
    ui->tabWidget_create->addTab(m_income,QString(u8"创作收益"));

    m_ctitleBar = new CreTitleBar(this);
    m_ctitleBar->setObjectName(QString::fromUtf8("m_ctitleBar"));
    ui->verticalLayout_all->insertWidget(0,m_ctitleBar);//垂直布局插入到顶端

    ui->stackedWidget_switch->setCurrentWidget(ui->page_login);//整体转换
    ui->tabWidget_create->setCurrentIndex(0);
}

void CreateCenter::handleSignalsAndSlots()
{
    //tab切换
    connect(ui->tabWidget_create,&QTabWidget::tabBarClicked,[=](int index){
        if(ui->tabWidget_create->widget(index) == m_doneWorks)
        {
           QStringList list_counts = dataBase::getInstance()->creator_getAllTagsWorkCounts();
           m_doneWorks->slot_setUserTagsWorkCounts(list_counts);
        }
        else if(ui->tabWidget_create->widget(index) == m_perCenter)
        {

        }
        else if(ui->tabWidget_create->widget(index) == m_maker)
        {

        }
        else if(ui->tabWidget_create->widget(index) == m_income)
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
        ui->tabWidget_create->setCurrentIndex(0);
    });

}

void CreateCenter::setInstallEventer()
{
    m_ctitleBar->installEventFilter(this);
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
    return QWidget::eventFilter(watched,event);
}
