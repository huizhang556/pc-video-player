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
    m_loginMain = new LoginPersonInfo;
    connect(ui->BtnLogin,&QPushButton::clicked,[=]()
    {
        this->hide();
        m_loginMain->showLoginWindow();
    });

    connect(this,&Login::sig_LoginWinClose,m_loginMain,&LoginPersonInfo::receiveLoginAppClose);

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
    this->close();
    emit sig_LoginWinClose();
}

void Login::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/mainback2.png"));
}
