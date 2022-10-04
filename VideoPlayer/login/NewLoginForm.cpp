#include "NewLoginForm.h"
#include "ui_NewLoginForm.h"

//#ifdef Q_OS_WIN
//#include <qt_windows.h>
//#include <Windows.h>
//#include <windowsx.h>
//#pragma comment (lib,"user32.lib")
//#endif

#include <QAbstractItemView>
#include <QDebug>
//类外初始化
NewLoginForm* NewLoginForm::m_pInstance = nullptr;

NewLoginForm::NewLoginForm(QWidget *parent):
    QDialog(parent),
    ui(new Ui::NewLoginForm)
{
    ui->setupUi(this);
    setFixedSize(700,455);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool |Qt::WindowMinMaxButtonsHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    initWorkUI();
    chandleSignalsAndSLots();
}

NewLoginForm::~NewLoginForm()
{
    delete ui;
    //删除创建的单例
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void NewLoginForm::initWorkUI()
{
    //登录部分
    m_actionShowPwd = new QAction(QIcon(":/images/icon/passwd_hide.png"),"");
    m_actionShowPwd->setObjectName(QString("m_actionShowPwd"));
    m_actionShowPwd->setCheckable(true);
    m_actionShowPwd->setChecked(false);
    ui->lineEdit_telNumber->setPlaceholderText(QString(u8"请输入手机号码"));
    ui->lineEdit_checkCode->setPlaceholderText(QString(u8"请输入验证码"));
    ui->lineEdit_account->setPlaceholderText(QString(u8"手机/邮箱/账户名"));
    ui->lineEdit_userpwd->setPlaceholderText(QString(u8"登陆密码"));
    ui->lineEdit_userpwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_userpwd->addAction(m_actionShowPwd,QLineEdit::TrailingPosition);
    //注册部分
    ui->lineEdit_regis_telNumber->setPlaceholderText(QString(u8"请输入注册手机号码"));
    ui->lineEdit_regis_checkCode->setPlaceholderText(QString(u8"请输入验证码"));
    ui->lineEdit_regis_checkCode->setEchoMode(QLineEdit::Password);
    //重置部分
    ui->lineEdit_fpwd_account->setPlaceholderText(QString(u8"请输入账号"));
    ui->lineEdit_fpwd_checkCode->setPlaceholderText(QString(u8"请输入验证码"));
    ui->lineEdit_firstpwd->setPlaceholderText(QString(u8"请输入新的密码"));
    ui->lineEdit_secondpwd->setPlaceholderText(QString(u8"再次输入新的密码"));
    ui->lineEdit_firstpwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_secondpwd->setEchoMode(QLineEdit::Password);
    ui->stackedWidget_right->setCurrentIndex(0);
    //解决QLineEdit回车键退出
    ui->pushButton_close->setFocusPolicy(Qt::NoFocus);//默认具有焦点
    ui->pushButton_register->setFocusPolicy(Qt::NoFocus);//默认具有焦点

    //combobox弹框问题
    ui->comboBox_area->installEventFilter(this);
    ui->comboBox_area->setFocusPolicy(Qt::NoFocus);
    ui->comboBox_regis_area->installEventFilter(this);
    ui->comboBox_regis_area->setFocusPolicy(Qt::NoFocus);

    //勾选协议（默认勾选）
    ui->radioButton_check->setCheckable(true);
    ui->radioButton_check->setChecked(true);
    ui->radioButton_regis_check->setCheckable(true);
    ui->radioButton_regis_check->setChecked(true);
}

void NewLoginForm::chandleSignalsAndSLots()
{
    //关闭
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){this->close();});
    //注册
    connect(ui->pushButton_register,&QPushButton::clicked,[=](){
        ui->stackedWidget_right->setCurrentIndex(1);
        qDebug() << QString(u8"注册按钮");
    });
    //获取验证码
    connect(ui->pushButton_checkCode,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"获取验证码");
    });
    //忘记密码
    connect(ui->pushButton_forgotPwd,&QPushButton::clicked,[=](){
        ui->stackedWidget_right->setCurrentIndex(2);
        qDebug() << QString(u8"忘记密码");
    });
    //扫码登录
    connect(ui->pushButton_scanCode,&QPushButton::clicked,[=](){
        ui->stackedWidget_right->setCurrentIndex(0);
    });
    //登录遇到问题
    connect(ui->pushButton_questions,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"遇到问题");
    });
    //查看密码
    connect(m_actionShowPwd,&QAction::triggered,[=](bool checked)
    {
        if(checked)
        {
            m_actionShowPwd->setIcon(QIcon(":/images/icon/passwd_show.png"));
            ui->lineEdit_userpwd->setEchoMode(QLineEdit::Normal);
            m_actionShowPwd->setChecked(true);
        }
        else
        {
            m_actionShowPwd->setIcon(QIcon(":/images/icon/passwd_hide.png"));
            ui->lineEdit_userpwd->setEchoMode(QLineEdit::Password);
            m_actionShowPwd->setChecked(false);
        }
    });

}

NewLoginForm *NewLoginForm::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new NewLoginForm();
    }
    return m_pInstance;
}

void NewLoginForm::receiveLoginAppClose()
{
    this->close();
}

void NewLoginForm::slot_switchWinType(ShowType type)
{
    switch (type) {
    case ShowType::LoginWin_0://扫码登录
    {
        ui->tabWidget_login->setCurrentIndex(0);
        ui->stackedWidget_right->setCurrentIndex(0);
    }
        break;
    case ShowType::LoginWin_1://短信登录
    {
        ui->tabWidget_login->setCurrentIndex(0);
        ui->stackedWidget_right->setCurrentIndex(0);
        ui->lineEdit_telNumber->setFocus();
    }
        break;
    case ShowType::LoginWin_2://账号登录
    {
        ui->tabWidget_login->setCurrentIndex(1);
        ui->stackedWidget_right->setCurrentIndex(0);
        ui->lineEdit_account->setFocus();
    }
        break;
    case ShowType::RegisWin://注册窗口
    {
        ui->tabWidget_login->setCurrentIndex(1);
        ui->stackedWidget_right->setCurrentIndex(1);
        ui->lineEdit_regis_telNumber->setFocus();
    }
        break;
    case ShowType::ReSetWin://重置窗口
    {
        ui->tabWidget_login->setCurrentIndex(1);
        ui->stackedWidget_right->setCurrentIndex(2);
        ui->lineEdit_fpwd_account->setFocus();
    }
        break;
    default:
        break;
    }
    this->exec();
}

void NewLoginForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(56, 67, 99,10));//rgba

    QPainterPath drawPath;
    drawPath.addRoundedRect(this->rect(),5,5);
    drawPath.addRect(this->rect());
//    painter.fillPath(drawPath,Qt::black);//先绘图片再填充外部边缘（准确来说叫颜色压住覆盖）
    painter.setClipPath(drawPath);
}

void NewLoginForm::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
//    QPoint orign_point = this->pos();
//    QPoint new_point = event->globalPos();
//    m_mvPos = new_point - orign_point;
}

void NewLoginForm::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
//    this->move(event->globalPos() - m_mvPos);
//    if(ReleaseCapture())
//    {
//        QWidget* pWindow = this->window();
//        if(pWindow->isTopLevel())
//        {
//            SendMessage(HWND(pWindow->winId()),WM_SYSCOMMAND,SC_MOVE + HTCAPTION,0);
//        }
//    }
//    event->ignore();
}

bool NewLoginForm::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == ui->comboBox_area)
    {

    }
    return QWidget::eventFilter(obj,ev);
}
