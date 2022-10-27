#include "NewLoginForm.h"
#include "ui_NewLoginForm.h"
#include "database/dataBase.h"
//#ifdef Q_OS_WIN
//#include <qt_windows.h>
//#include <Windows.h>
//#include <windowsx.h>
//#pragma comment (lib,"user32.lib")
//#endif
#include <QTimer>
#include <QAbstractItemView>

//类外初始化
NewLoginForm* NewLoginForm::m_pInstance = nullptr;

NewLoginForm::NewLoginForm(QWidget *parent):
    QDialog(parent),
    ui(new Ui::NewLoginForm)
{
    ui->setupUi(this);
    setFixedSize(700,455);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowMinMaxButtonsHint | Qt::WindowStaysOnTopHint);
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

    ui->tabWidget_login->setCurrentIndex(0);
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


    //登录
    connect(ui->pushButton_login,&QPushButton::clicked,[=](){
        if(ui->tabWidget_login->currentIndex() == 0)//短信登录
        {
            if(ui->lineEdit_telNumber->text().isEmpty())
            {
                setType(TipType::Error);
                showCText(TipType::Correct,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-230,70),QString(u8"手机号不能为空"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
            }
            else if(ui->lineEdit_checkCode->text().isEmpty())
            {
                setType(TipType::Error);
                showCText(TipType::Normal,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-230,70),QString(u8"验证码不能为空"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
            }
        setUser_login();
        }
        else if(ui->tabWidget_login->currentIndex() == 1)//账号登录
        {
            if(ui->lineEdit_account->text().isEmpty())
            {
                setType(TipType::Error);
                showCText(TipType::Correct,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-230,70),QString(u8"登录账号不能为空"),ui->pushButton_login,ui->lineEdit_account->rect(),2000);
            }
            else if(ui->lineEdit_userpwd->text().isEmpty())
            {
                setType(TipType::Error);
                showCText(TipType::Normal,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-230,70),QString(u8"登录密码不能为空"),ui->pushButton_login,ui->lineEdit_userpwd->rect(),2000);
            }
            setUser_login();
        }
    });
    //注册
    connect(ui->pushButton_regis,&QPushButton::clicked,[=](){
        if(ui->stackedWidget_right->currentIndex() == 1)//账号注册
        {
            if(ui->lineEdit_regis_telNumber->text().isEmpty())
            {
                setType(TipType::Error);
                showCText(TipType::Correct,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,70),QString(u8"注册账号不能为空"),ui->pushButton_regis,ui->lineEdit_regis_telNumber->rect(),2000);
            }
            else if(ui->lineEdit_regis_checkCode->text().isEmpty())
            {
                setType(TipType::Error);
                showCText(TipType::Normal,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,70),QString(u8"验证码不能为空"),ui->pushButton_regis,ui->lineEdit_regis_checkCode->rect(),2000);
            }
            else if(ui->lineEdit_regis_email->text().isEmpty())
            {
                setType(TipType::Error);
                showCText(TipType::Normal,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,70),QString(u8"注册邮箱不能为空"),ui->pushButton_regis,ui->lineEdit_regis_email->rect(),2000);
            }
            setUser_register();
        }
    });

    //重置
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

void NewLoginForm::setUser_login()
{
    QString account;
    QString passwd ;
    if(ui->tabWidget_login->currentIndex() == 0)//短信登录
    {
        account = ui->lineEdit_telNumber->text().trimmed();
        passwd  = ui->lineEdit_checkCode->text().trimmed();
    }
    else if(ui->tabWidget_login->currentIndex() == 1)//账号登陆
    {
        account = ui->lineEdit_account->text().trimmed();
        passwd  = ui->lineEdit_userpwd->text().trimmed();
    }

    bool valiable = dataBase::getInstance()->login_checked_usernameAndPasswd(account,passwd);//核对账号是否存在
    if(valiable)//信息核对成功！
    {
        //发送名称，头像连接, 等级
        emit sig_sendClearTempRecords();//清除临时记录（如果用户不登录，则切换用户时会用到）
        dataBase::getInstance()->login_verification(account,passwd);//将用户所有信息查询出来，并初始化
        QString nickname =  dataBase::getInstance()->getCurrentUserName();
        QString head     =  dataBase::getInstance()->getCurrentUserHead();
        int     grade    =  dataBase::getInstance()->getCurrentUserGrade();
        emit sig_sendLoginOK(nickname,head,grade);
//        slot_addLoginHisUsers(account);
        slot_clearTempInputText();
        this->close();
    }
    else//信息核对失败！
    {
        setType(TipType::Error);
        showCText(TipType::Normal,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-230,70),QString(u8"验证码不能为空"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
        return;
    }
}

void NewLoginForm::setUser_register()
{
    QString name;
    QString pwd ;
    QString email;
    if(ui->stackedWidget_right->currentIndex() == 1)//注册界面
    {
       name    = ui->lineEdit_regis_telNumber->text().trimmed();
       pwd     = ui->lineEdit_regis_checkCode->text().trimmed();
       email   = ui->lineEdit_regis_email->text().trimmed();
    }

    bool isOK = dataBase::getInstance()->register_userInfo(name,pwd,email);
    if(isOK)//插入成功
    {
        QTimer::singleShot(0,0,[=](){
            slot_clearTempInputText();
//            showLoginWindow(0);
        });//转到登录界面
    }
    else//插入失败
    {
        setType(TipType::Error);
        showCText(TipType::Normal,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,70),QString(u8"注册失败，请重新注册！"),ui->pushButton_regis,ui->lineEdit_telNumber->rect(),2000);
    }
}

void NewLoginForm::setUser_reSet()
{

}

void NewLoginForm::setUser_findPwd()
{

}

void NewLoginForm::slot_clearTempInputText()
{
    ui->lineEdit_telNumber->clear();
    ui->lineEdit_checkCode->clear();
    ui->lineEdit_regis_telNumber->clear();
    ui->lineEdit_regis_checkCode->clear();
    ui->lineEdit_regis_email->clear();
    ui->lineEdit_account->clear();
    ui->lineEdit_userpwd->clear();
    ui->lineEdit_fpwd_account->clear();
    ui->lineEdit_fpwd_checkCode->clear();
    ui->lineEdit_firstpwd->clear();
    ui->lineEdit_secondpwd->clear();
}

void NewLoginForm::showCText(TipType type, const QPoint &pos, const QString &text, QWidget *w, const QRect &rect, int msecShowTime)
{
    QToolTip::showText(pos,text,w,rect,msecShowTime);
}

void NewLoginForm::setType(TipType type)
{
    switch (type)
    {
    case TipType::Normal:
    {
//        QString st = "<b style=\"background:rgb(230, 92, 54);color:red;\">%1</b>";
//        return st;
//        QToolTip::setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
        setStyleSheet("QWidget{background-color: #2c2d36;}"
                      "QToolTip{background-color: rgb(112, 113, 116);color: black;}");
    }
        break;
    case TipType::Error:
    {
//        QString st = "<b style=\"background:rgb(230, 92, 54);color:red;\">%1</b>";
//        return st;
//        QToolTip::setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
        setStyleSheet("QWidget{background-color: #2c2d36;}"
                      "QToolTip{background-color: #2c2d36;  color: black;}");
    }
        break;
    case TipType::Correct:
    {
//        QString st = "<b style=\"background:rgb(246, 188, 63);color:green;\">%1</b>";
//        return st;
//        QToolTip::setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
        setStyleSheet("QWidget{background-color: #2c2d36;}"
                      "QToolTip{background-color: rgb(112, 113, 116);color: rgb(65, 205, 82);}");
    }
        break;
    default:
    {
//        QString st = "<b style=\"background:rgb(255, 214, 22);color:white;\">%1</b>";
//        return st;
//        QToolTip::setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
        setStyleSheet("QWidget{background-color: #2c2d36;}"
                      "QToolTip{background-color: rgb(112, 113, 116);color: black;}");
    }
        break;
    }

//  pal.setColor(QPalette::ToolTipBase, Qt::red);
//  pal.setColor(QPalette::ToolTipText, Qt::green);
}
