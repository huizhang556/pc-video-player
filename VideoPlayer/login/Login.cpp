#include "Login.h"
#include "ui_Login.h"
#include <QPainter>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    installEventFilter(this);
    this->setFixedSize(260,200);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    initWorkUI();
    handleSignalsAndSlots();

}

Login::~Login()
{
    delete ui;
}

void Login::initWorkUI()
{
    ui->label_vipwarning->setAlignment(Qt::AlignCenter);
    QListWidgetItem *item1 = new QListWidgetItem(QIcon("://images/user/user_zhuye.png"),QString::fromLocal8Bit("我的个人频道"));
    QListWidgetItem *item2 = new QListWidgetItem(QIcon("://images/function/collect_list_item.png"),QString::fromLocal8Bit("我的订阅"));
    QListWidgetItem *item3 = new QListWidgetItem(QIcon("://images/icon/url_collection.png"),QString::fromLocal8Bit("我的收藏"));
    ui->listWidget_person->addItem(item1);
    ui->listWidget_person->addItem(item2);
    ui->listWidget_person->addItem(item3);
    ui->stackwidget_login->setCurrentIndex(0);
}

void Login::handleSignalsAndSlots()
{
    connect(ui->BtnLogin,&QPushButton::clicked,[=]()
    {
        if(NewLoginForm::getInstance())
        {
            if(!NewLoginForm::getInstance()->isHidden())//正常显示
            {
                NewLoginForm::getInstance()->hide();
            }
            else//隐藏
            {
                NewLoginForm::getInstance()->raise();
//                NewLoginForm::getInstance()->setWindowModality(Qt::ApplicationModal);
                NewLoginForm::getInstance()->slot_switchWinType(ShowType::LoginWin_1);
            }
        }

    });

    //收到关闭程序信号
    connect(this,&Login::sig_LoginWinClose,NewLoginForm::getInstance(),&NewLoginForm::receiveLoginAppClose);
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

void Login::slot_setPersonVipPage(int index)
{
    ui->stackwidget_login->setCurrentIndex(index);
}

void Login::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
//    QPainter painter(this);
//    painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(":/images/bgpic/login_bgpic.png"));
}
