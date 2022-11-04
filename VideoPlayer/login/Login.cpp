#include "Login.h"
#include "ui_Login.h"
#include "mainwidget/vipmember/BuyVip.h"
#include "login/MessageItem.h"
#include "global/Global.h"
#include <QPainter>
#include <QScrollBar>
#include <QPainterPath>
#include <QDebug>

Login::Login(QWidget *parent) :
    QDialog(parent),
    m_startX(140),
    m_startY(15),
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
    ui->pushButton_exit->setText(QString(u8"退出登录"));
    ui->label_vipwarning->setAlignment(Qt::AlignCenter);
    ui->listWidget_person->setViewMode(QListView::ListMode);
    ui->listWidget_person->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_person->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_person->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_person->verticalScrollBar()->setDisabled(true);
    QListWidgetItem *item1 = new QListWidgetItem(QIcon("://images/user/user_zhuye.png"),QString(u8"我的个人频道"));
//    item1->setTextAlignment(Qt::AlignCenter);//文字居中显示
    QListWidgetItem *item2 = new QListWidgetItem(QIcon("://images/function/collect_list_item.png"),QString(u8"我的订阅"));
//    item2->setTextAlignment(Qt::AlignCenter);
    QListWidgetItem *item3 = new QListWidgetItem(QIcon("://images/icon/url_collection.png"),QString(u8"我的收藏"));
//    item3->setTextAlignment(Qt::AlignCenter);
    QListWidgetItem *item4 = new QListWidgetItem(QIcon("://images/function/user_watched.png"),QString(u8"我的关注"));
//    item4->setTextAlignment(Qt::AlignCenter);
    ui->listWidget_person->addItem(item1);
    ui->listWidget_person->addItem(item2);
    ui->listWidget_person->addItem(item3);
    ui->listWidget_person->addItem(item4);
    ui->tabWidget_login->setCurrentIndex(0);

    ui->listWidget_comment->setViewMode(QListView::ListMode);
    ui->listWidget_comment->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_comment->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0; i < 20; i++)
    {
        QString headPath = Global::appDirPath + QString("/pictures/musics/recommend3/music%1.png").arg(i+1);
        QString userName = QString(u8"超级爱评论%1").arg(i+1);
        QString dataTime = QString(u8"2020年10月%1日").arg(i+1);
        QString message  = QString(u8"评论：开通会员，尽享尊贵权益和VIP特权！");
        MessageItem *itemWidget = new MessageItem(headPath,userName,dataTime,message);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(ITEMSIZE);
        ui->listWidget_comment->addItem(item);
        ui->listWidget_comment->setItemWidget(item,itemWidget);
    }
    ui->listWidget_comment->setCurrentRow(0);

    ui->listWidget_aboutme->setViewMode(QListView::ListMode);
    ui->listWidget_aboutme->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_aboutme->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0; i < 20; i++)
    {
        QString headPath = Global::appDirPath + QString("/pictures/musics/recommend2/music%1.png").arg(i+1);
        QString userName = QString(u8"超级爱@me%1").arg(i+1);
        QString dataTime = QString(u8"2021年11月%1日").arg(i+1);
        QString message  = QString(u8"@我：开通会员，尽享尊贵权益和VIP特权！");
        MessageItem *itemWidget = new MessageItem(headPath,userName,dataTime,message);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(ITEMSIZE);
        ui->listWidget_aboutme->addItem(item);
        ui->listWidget_aboutme->setItemWidget(item,itemWidget);
    }
    ui->listWidget_aboutme->setCurrentRow(0);

    ui->listWidget_notify->setViewMode(QListView::ListMode);
    ui->listWidget_notify->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_notify->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0; i < 20; i++)
    {
        QString headPath = Global::appDirPath + QString("/pictures/musics/recommend/music%1.png").arg(i+1);
        QString userName = QString(u8"爱玩的张三%1").arg(i+1);
        QString dataTime = QString(u8"2022年12月%1日").arg(i+1);
        QString message  = QString(u8"通知:开通会员，尽享尊贵权益和VIP特权！");
        MessageItem *itemWidget = new MessageItem(headPath,userName,dataTime,message);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(ITEMSIZE);
        ui->listWidget_notify->addItem(item);
        ui->listWidget_notify->setItemWidget(item,itemWidget);
    }
    ui->listWidget_notify->setCurrentRow(0);
}

void Login::handleSignalsAndSlots()
{

    //收到关闭程序信号
    connect(this,&Login::sig_LoginWinClose,NewLoginForm::getInstance(),&NewLoginForm::receiveLoginAppClose);

    //开通vip
    connect(ui->pushButton_openvip,&QPushButton::clicked,[=](){
        BuyVip::getInstance()->exec();
    });

    //退出此账号
    connect(ui->pushButton_exit,&QPushButton::clicked,[=](){
        emit sig_sendSign_out();
        this->hide();
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

void Login::slot_addMessageItemToBox(MessType mtype, const QString &pic, const QString &nickname, const QString &datatime, const QString &message)
{
    switch (mtype) {
    case MessType::M_COMMENT:
    {
        MessageItem *itemWidget = new MessageItem(pic,nickname,datatime,message);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(ITEMSIZE);
        ui->listWidget_comment->addItem(item);
        ui->listWidget_comment->setItemWidget(item,itemWidget);
    }
        break;
    case MessType::M_ABOUTME:
    {
        MessageItem *itemWidget = new MessageItem(pic,nickname,datatime,message);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(ITEMSIZE);
        ui->listWidget_aboutme->addItem(item);
        ui->listWidget_aboutme->setItemWidget(item,itemWidget);
    }
        break;
    case MessType::M_NOTIFY:
    {
        MessageItem *itemWidget = new MessageItem(pic,nickname,datatime,message);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(ITEMSIZE);
        ui->listWidget_notify->addItem(item);
        ui->listWidget_notify->setItemWidget(item,itemWidget);
    }
        break;
    default:
        break;
    }
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
