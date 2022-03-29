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
    setWindowFlags(Qt::FramelessWindowHint);

    connect(ui->BtnLogin,&QPushButton::clicked,[=]()
    {
        if(m_loginMain)
        {
            if(!m_loginMain->isHidden())//正常显示
            {
                m_loginMain->hide();
            }
            else//隐藏
            {
//                m_loginMain->showNormal();
                m_loginMain->raise();
                m_loginMain->show();
            }
        }
        else
        {
            m_loginMain = new LoginPersonInfo;
            m_loginMain->raise();
            m_loginMain->show();
        }

    });

    connect(this,&Login::sig_LoginWinClose,m_loginMain,&LoginPersonInfo::receiveLoginAppClose);

}

Login::~Login()
{
    delete ui;
    delete m_loginMain;
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
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/mainback2.png"));
}
