#include "Login.h"
#include "ui_Login.h"
#include "mainwidget/vipmember/BuyVip.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

Login::Login(QWidget *parent) :
    QDialog(parent),
    m_startX(140),
    m_startY(20),
    m_triangleWidth(20),
    m_triangleHeight(15),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    installEventFilter(this);
    this->setFixedSize(300,400);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Popup | Qt::Tool | Qt::WindowStaysOnTopHint);
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
//    ui->stackwidget_login->setCurrentIndex(1);
}

void Login::handleSignalsAndSlots()
{

    //收到关闭程序信号
    connect(this,&Login::sig_LoginWinClose,NewLoginForm::getInstance(),&NewLoginForm::receiveLoginAppClose);

    //开通vip
    connect(ui->pushButton_openvip,&QPushButton::clicked,[=](){
        BuyVip::getInstance()->exec();
    });
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
//    ui->stackwidget_login->setCurrentIndex(index);
}

void Login::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(48, 48, 48));
    //小三角区域
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_startX , m_startY);
    trianglePolygon << QPoint(m_startX + m_triangleWidth / 2, 20 - m_triangleHeight);
    trianglePolygon << QPoint(m_startX + m_triangleWidth, m_startY);
    QPainterPath drawPath;
    //调整三角形高度：1.界面留出空白高度 2.三角形起点高度 3.三角形高度一致
    drawPath.addRoundRect(0,m_startY,width(),height()-20,4,4);
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);
}
