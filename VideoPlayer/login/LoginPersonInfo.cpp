#include "LoginPersonInfo.h"
#include "ui_LoginPersonInfo.h"
#include <QDebug>
#include <QTimer>
#include <QListView>
#include <QCompleter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QRegExpValidator>
#include <QAbstractItemView>

//类外初始化
LoginPersonInfo* LoginPersonInfo::m_pInstance = NULL;//初始化指针

LoginPersonInfo::LoginPersonInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginPersonInfo)

{
    ui->setupUi(this);
    this->setFixedSize(430,328);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    initWorkUI();
    chandleSignalsAndSLots();
}

/*析构函数*/
LoginPersonInfo::~LoginPersonInfo()
{
    delete ui;
    //删除创建的单例
    if(m_pInstance != NULL)
        delete m_pInstance;
    m_pInstance = NULL;
}

/*获取单例*/
LoginPersonInfo* LoginPersonInfo::getInstance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new LoginPersonInfo();
    }
    return m_pInstance;
}

void LoginPersonInfo::initWorkUI()
{
    ui->label_message->setAlignment(Qt::AlignCenter);//文字居中
    ui->stackedWidget_login->setCurrentIndex(0);

    ui->comboBox_net_address->setView(new QListView());
    ui->comboBox_net_type->setView(new QListView());
    ui->comboBox_ser_type->setView(new QListView());

    ui->login_BtnRegis->setToolTip(QString::fromLocal8Bit("注册用户"));
    ui->login_BtnQR->setToolTip(QString::fromLocal8Bit("二维码登录"));
    QStringList comlist;
    comlist<<"1238975230"<<"1238975235"<<"1238975236"<<"12348695"<<"12357984"<<"12368866"<<"25789412"<<"25468963"<<"25963654"<<"25896254";
    QCompleter *completer = new QCompleter(comlist,this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->popup()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    completer->popup()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    completer->popup()->setStyleSheet(
                        "QListView"
                        "{"
                        "min-height:80px;"
                        "font-size:15px;"
                        "outline:0px;"
                        "background-color:white;"
                        "border: 1px solid rgba(0,0,0,10%);"
                        "text-align:left;"
                        "margin-top:1px;"
                        "}"
                        "QListView::item:hover"
                        "{"
                        "color:green;"
                        "background-color:yellow;"
                        "}");
    completer->setMaxVisibleItems(4);//最大显示4
    ui->login_lineEditUser->setCompleter(completer);
    /*登录-登录账户*/
    ui->login_lineEditUser->setPlaceholderText(QString::fromLocal8Bit("账户"));
    QRegExp regExp("[A-Za-z0-9]{4,16}");//英文字母、数字
    ui->login_lineEditUser->setValidator(new QRegExpValidator(regExp, this));
    ui->login_lineEditUser->setFocus();
    /*注册-注册账户*/
    ui->gis_lineEditUser->setPlaceholderText(QString::fromLocal8Bit("输入新账户"));
    QRegExp regExp3("[A-Za-z0-9]{4,16}");
    ui->gis_lineEditUser->setValidator(new QRegExpValidator(regExp3, this));
    ui->gis_lineEditUser->setFocus();
    /*登录-登录密码*/
    ui->login_lineEditPasswd->setPlaceholderText(QString::fromLocal8Bit("密码"));
    QRegExp regExp2("[A-Za-z0-9]{6,10}");
    ui->login_lineEditPasswd->setValidator(new QRegExpValidator(regExp2, this));
    /*注册-注册密码*/
    ui->gis_lineEditPasswd->setPlaceholderText(QString::fromLocal8Bit("输入新密码"));
    QRegExp regExp4("[A-Za-z0-9]{6,10}");
    ui->gis_lineEditPasswd->setValidator(new QRegExpValidator(regExp4, this));

    /*注册---注册邮箱*/
    ui->gis_lineEditEmail->setPlaceholderText(QString::fromLocal8Bit("找回密码用"));
    QRegExp regExp5("^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+)+$");
    ui->gis_lineEditEmail->setValidator(new QRegExpValidator(regExp5, this));

    //重置--账号重置
    ui->reset_lineEditUser->setPlaceholderText(QString::fromLocal8Bit("重置的账号"));
    //重置--密码重置
    ui->reset_lineEditPasswd->setPlaceholderText(QString::fromLocal8Bit("重置的密码"));
    //重置--验证邮箱
    ui->reset_lineEditEmail->setPlaceholderText(QString::fromLocal8Bit("验证邮箱"));
}

void LoginPersonInfo::chandleSignalsAndSLots()
{
    /*登录--清除按钮*/
    QIcon icon_clear(":/images/icon/clear.png");
    clearAction1 = new QAction(icon_clear,"");
    clearAction1->setObjectName(QString::fromLocal8Bit("clearAction1"));
    connect(clearAction1,&QAction::triggered,[=](){ui->login_lineEditUser->clear();});
    connect(ui->login_lineEditUser,&QLineEdit::textChanged,[=](QString content)
    {
        if(!content.isEmpty())
        {
            clearAction1->setVisible(true);
            clearAction1->setEnabled(true);
            ui->login_lineEditUser->addAction(clearAction1, QLineEdit::TrailingPosition);// 右侧显示
        }
         else
         {
            clearAction1->setVisible(false);
            clearAction1->setEnabled(false);
         }
    });

    /*注册---注册账户清除按钮*/
    clearAction3 = new QAction(icon_clear,"");
    clearAction3->setObjectName(QString::fromLocal8Bit("clearAction3"));
    connect(clearAction3,&QAction::triggered,[=](){ui->gis_lineEditUser->clear();});
    connect(ui->gis_lineEditUser,&QLineEdit::textChanged,[=](QString content)
    {
        if(!content.isEmpty())
        {
            clearAction3->setVisible(true);
            clearAction3->setEnabled(true);
            ui->gis_lineEditUser->addAction(clearAction3, QLineEdit::TrailingPosition);// 右侧显示
        }
         else
         {
            clearAction3->setVisible(false);
            clearAction3->setEnabled(false);
         }
    });

    /*登录---显示密码按钮*/
    QIcon icon_passwd(":/images/icon/passwd_hide.png");
    clearAction2 = new QAction(icon_passwd,"");
    clearAction2->setObjectName(QString::fromLocal8Bit("clearAction2"));
    connect(ui->login_lineEditPasswd,&QLineEdit::textChanged,[=](QString content)
    {
        if(!content.isEmpty())
        {
            ui->login_lineEditPasswd->addAction(clearAction2, QLineEdit::TrailingPosition);// 右侧显示
            clearAction2->setVisible(true);
            clearAction2->setEnabled(true);
        }
        else
        {
            clearAction2->setVisible(false);
            clearAction2->setEnabled(false);
        }

    });

    connect(clearAction2,&QAction::triggered,[=]()
    {
        if(!passwdStatus)
        {
            clearAction2->setIcon(QIcon(":/images/icon/passwd_hide.png"));
            ui->login_lineEditPasswd->setEchoMode(QLineEdit::Password);
        }
        else
        {
            clearAction2->setIcon(QIcon(":/images/icon/passwd_show.png"));
            ui->login_lineEditPasswd->setEchoMode(QLineEdit::Normal);
        }
             passwdStatus =! passwdStatus;
    });

    /*注册---输入密码*/
    clearAction4 = new QAction(icon_passwd,"");
    clearAction4->setObjectName(QString::fromLocal8Bit("clearAction4"));
    connect(ui->gis_lineEditPasswd,&QLineEdit::textChanged,[=](QString content)
    {
        if(!content.isEmpty())
        {
            ui->gis_lineEditPasswd->addAction(clearAction4, QLineEdit::TrailingPosition);// 右侧显示
            clearAction4->setVisible(true);
            clearAction4->setEnabled(true);
        }
        else
        {
            clearAction4->setVisible(false);
            clearAction4->setEnabled(false);
        }

    });

    /*注册---显示密码功能*/
    connect(clearAction4,&QAction::triggered,[=]()
    {
        if(!passwdStatus2)
        {
            clearAction4->setIcon(QIcon(":/images/icon/passwd_hide.png"));
            ui->gis_lineEditPasswd->setEchoMode(QLineEdit::Password);
        }
        else
        {
            clearAction4->setIcon(QIcon(":/images/icon/passwd_show.png"));
            ui->gis_lineEditPasswd->setEchoMode(QLineEdit::Normal);
        }
             passwdStatus2 =! passwdStatus2;
    });

    /*登录---关闭按钮*/
    connect(ui->login_Btnclose,&QPushButton::clicked,[=]()
    {
        ui->login_lineEditUser->clear();
        ui->login_lineEditPasswd->clear();
        close();
    });

    /*注册---注册邮箱按钮*/
    clearAction5 = new QAction(icon_clear,"");
    clearAction5->setObjectName(QString::fromLocal8Bit("clearAction5"));
    connect(clearAction5,&QAction::triggered,[=](){ui->gis_lineEditEmail->clear();});
    connect(ui->gis_lineEditEmail,&QLineEdit::textChanged,[=](QString content)
    {
        if(!content.isEmpty())
        {
            clearAction5->setVisible(true);
            clearAction5->setEnabled(true);
            ui->gis_lineEditEmail->addAction(clearAction5, QLineEdit::TrailingPosition);// 右侧显示
        }
         else
         {
            clearAction5->setVisible(false);
            clearAction5->setEnabled(false);
         }
    });


    /*登录---登录按钮*/
    connect(ui->login_BtnLogin,&QPushButton::clicked,[=]()
    {
        QMessageBox::information(this,QString::fromLocal8Bit("登录提示"),QString::fromLocal8Bit("请稍等，正在核验个人信息！"));
    });

    connect(ui->login_BtnRegis,&QPushButton::clicked,[=]()
    {
       ui->stackedWidget_login->setCurrentIndex(1);
    });

    connect(ui->login_BtnQR,&QPushButton::clicked,[=]()
    {
       ui->stackedWidget_login->setCurrentIndex(2);
    });

    /*登录---最小化按钮*/
    connect(ui->login_Btnmin,&QPushButton::clicked,[=](){showMinimized();});

    /*设置按钮*/
    connect(ui->login_Btnset,&QPushButton::clicked,[=](){ui->stackedWidget_login->setCurrentIndex(4);});

    /*重置密码按钮*/
    connect(ui->login_BtnResetPwd,&QPushButton::clicked,[=](){ui->stackedWidget_login->setCurrentIndex(3);});
    /*服务测试按钮*/
    connect(ui->pushButton_test,&QPushButton::clicked,[=](){ slot_showWaringText(QString::fromLocal8Bit("正在测试连接中...")); });
}



void LoginPersonInfo::showLoginWindow()
{
    this->showNormal();
}

void LoginPersonInfo::showLoginWindow(int index)
{
    if(index ==0)//登录
    {
        ui->stackedWidget_login->setCurrentIndex(0);
        ui->login_lineEditUser->setFocus();
    }
    else if(index ==1)//注册
    {
        ui->stackedWidget_login->setCurrentIndex(1);
        ui->gis_lineEditUser->setFocus();
    }
    else if(index ==2)//二维码
    {
        ui->stackedWidget_login->setCurrentIndex(2);
    }
    else if(index ==3)//重置
    {
        ui->stackedWidget_login->setCurrentIndex(3);
        ui->reset_lineEditUser->setFocus();
    }
    else if(index ==4)//设置
    {
        ui->stackedWidget_login->setCurrentIndex(4);
    }
    this->show();
}

void LoginPersonInfo::receiveLoginAppClose()
{
    this->close();
}

/*使用移动功能会导致combobox下拉错位*/

/*按下事件*/
void LoginPersonInfo::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
//   QPoint winPos = this->pos();//界面位置
//    QPoint nowPos = event->globalPos();//鼠标位置
//    m_mvPos = nowPos - winPos;
}
/*移动事件*/
void LoginPersonInfo::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    //    this->move(event->globalPos() - m_mvPos);
}

void LoginPersonInfo::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    ui->login_lineEditUser->setFocus();
}

/*page2返回*/
void LoginPersonInfo::on_pushButton_return_page2_clicked()
{
    ui->stackedWidget_login->setCurrentIndex(0);
    ui->login_lineEditUser->setFocus();
}

/*page3返回*/
void LoginPersonInfo::on_pushButton_return_page3_clicked()
{
    ui->stackedWidget_login->setCurrentIndex(0);
    ui->login_lineEditUser->setFocus();
}

/*注册按钮*/
void LoginPersonInfo::on_gis_BtnRegister_clicked()
{
    QMessageBox::information(this,"register","register");
}

/*重置密码按钮*/
void LoginPersonInfo::on_reset_BtnReset_clicked()
{
    QMessageBox::information(this,"reset","reset passwoed!");
}

/*page4返回*/
void LoginPersonInfo::on_pushButton_return_page4_clicked()
{
    ui->stackedWidget_login->setCurrentIndex(0);
}

/*page5返回*/
void LoginPersonInfo::on_set_BtnReturn_clicked()
{
    ui->stackedWidget_login->setCurrentIndex(0);
}

void LoginPersonInfo::slot_showWaringText(const QString &text)
{
    ui->label_message->setText(text);
    QTimer::singleShot(3000,this,SLOT(slot_clearWarningText()));//只显示3秒，过后清除显示
}

void LoginPersonInfo::slot_clearWarningText()
{
    ui->label_message->clear();
}

