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
    this->setFixedHeight(50);
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
    //LCD数字显示
    ui->lcdNumber->setDigitCount(20);//显示数量（个数）
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setPalette(Qt::red);//显示文字颜色，不怎么生效
    //初始化定时器
    m_timer1 = new QTimer(this);
    m_timer2 = new QTimer(this);
    m_timer3 = new QTimer(this);
    m_timer3->start(100);//0.1s更新发送一次时间,放在下面合适
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
}


/*处理信号与槽函数*/
void TitleBar::chandleSignalAndSLots()
{
    //发送窗口关闭信号
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){emit sig_winClose();});
    //发送窗口还原信号
    connect(ui->pushButton_normal,&QPushButton::clicked,[=](){emit sig_winNormal();});
    //发送窗口最小化信号
    connect(ui->pushButton_min,&QPushButton::clicked,[=](){emit sig_winMinimum();});
    //更新时间
    connect(m_timer3,&QTimer::timeout,this,&TitleBar::getSystemTimeShow);
    //调用登录提示板
    connect(ui->Btnlogin,&QPushButton::clicked,[=](){emit sig_callLogin();});
    //历史记录
    connect(ui->BtnHistory,&QPushButton::clicked,[=](){emit sig_historyDownload();});
    //帮助设置
    connect(ui->Btnhelp,&QPushButton::clicked,[=](){emit sig_settingHelp();});
    //腾讯主页
    connect(ui->Btn_logo,&QPushButton::clicked,[=](){QDesktopServices::openUrl(QUrl(QString("https://v.qq.com/")));});
\
    //返回主页
    connect(ui->pushButton_home,&QPushButton::clicked,[=](){emit sig_sendUrlHome();});
    //后退 浏览器处理
    connect(ui->pushButton_back,&QPushButton::clicked,[=](){emit sig_sendUrlBack();});
    //刷新 浏览器处理
    connect(ui->pushButton_freshen,&QPushButton::clicked,[=](){emit sig_sendUrlRefreshen();});
    //前进 浏览器处理
    connect(ui->pushButton_advance,&QPushButton::clicked,[=](){emit sig_sendUrlAdvance();});
    //显示登录窗口
    connect(ui->Btnlogin,&QPushButton::clicked,[=](){qDebug() << "login clicked!"; showLoginForm();});
    //历史记录记录搜索历史
//    connect(this,&TitleBar::sig_sendNewSearch,m_searchForm,&SearchForm::addHistoryItem);
    //关闭程序关闭历史搜索框
    connect(this,&TitleBar::sig_winClose,m_searchForm,&SearchForm::closeSearchForm);
    //还原时，关闭历史搜索框
    connect(this,&TitleBar::sig_winNormal,m_searchForm,&SearchForm::closeSearchForm);
    connect(ui->lineEdit_webSearch,&QLineEdit::returnPressed,[=](){
        QString url = ui->lineEdit_webSearch->text().trimmed();
        emit sig_sendNewUrl(url);
        qDebug() << "emit sig_sendNewUrl(url);";
    });

    connect(ui->lineEditSearch,&QLineEdit::returnPressed,[=](){
        QString his = ui->lineEditSearch->text().trimmed();
        m_searchForm->addHistoryItem(his);
        qDebug() << "emit sig_sendNewSearch(his);";
        //处理其他事件
        //鼠标进入样式改变
    });
}

/*设置tooltip*/
void TitleBar::setShowToolTip()
{
    ui->Btn_logo->setToolTip(QString::fromLocal8Bit("转至网页"));
    ui->Btnhelp->setToolTip(QString::fromLocal8Bit("帮助"));
    ui->Btnlogin->setToolTip(QString::fromLocal8Bit("登录"));
    ui->Btnskin->setToolTip(QString::fromLocal8Bit("皮肤"));
    ui->BtnDownload->setToolTip(QString::fromLocal8Bit("云端"));
    ui->BtnHistory->setToolTip(QString::fromLocal8Bit("历史记录"));
    ui->BtnScreen->setToolTip(QString::fromLocal8Bit("截屏"));
}

/*重写鼠标双击事件*/
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit sig_doubleClick();
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
    if(watched == ui->lineEditSearch)
    {

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
    ui->lineEdit_webSearch->clear();
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

void TitleBar::receiveMainFormClose()
{
    m_loginForm->close();
    m_loginForm->receiveMainWinCloseAppSignal();
}


