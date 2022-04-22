#include "Login.h"
#include "ui_Login.h"
#include <QPainter>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    installEventFilter(this);
    this->setFixedSize(310,200);    
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);

    connect(ui->BtnLogin,&QPushButton::clicked,[=]()
    {
        if(LoginPersonInfo::getInstance())
        {
            if(!LoginPersonInfo::getInstance()->isHidden())//正常显示
            {
                LoginPersonInfo::getInstance()->hide();
            }
            else//隐藏
            {
//                LoginPersonInfo::getInstance()->showNormal();
                LoginPersonInfo::getInstance()->raise();
                LoginPersonInfo::getInstance()->show();
            }
        }
//        else
//        {
//            m_loginMain = new LoginPersonInfo;
//            m_loginMain->raise();
//            m_loginMain->show();
//        }

    });

    connect(this,&Login::sig_LoginWinClose,LoginPersonInfo::getInstance(),&LoginPersonInfo::receiveLoginAppClose);

}

Login::~Login()
{
    delete ui;
}


void Login::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->close();
}

//bool Login::eventFilter(QObject *watch, QEvent *event)
//{
//    if(event->type() == QEvent::Leave)
//    {
//        this->hide();
//    }

//    return QDialog::eventFilter(watch,event);
//}

void Login::receiveMainWinCloseAppSignal()
{
    emit sig_LoginWinClose();//向登录信息窗口发送信号
}

void Login::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
//    QPainter painter(this);
//    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/bgpic/login_bgpic.png"));
}
