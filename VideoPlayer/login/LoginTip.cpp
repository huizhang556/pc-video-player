#include "LoginTip.h"
#include "ui_LoginTip.h"
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

LoginTip* LoginTip::m_pInstance = nullptr;

LoginTip::LoginTip(QWidget *parent) :
    QWidget(parent),
    m_startX(300),
    m_startY(40),
    m_triangleWidth(20),
    m_triangleHeight(15),
    ui(new Ui::LoginTip)
{
    ui->setupUi(this);
    setFixedSize(380,193);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::Popup | Qt::Tool | Qt::WindowStaysOnTopHint);
    initWorkUI();
    handleSignalsAndSlots();
}

LoginTip::~LoginTip()
{
    delete ui;
    //删除创建的单例
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void LoginTip::initWorkUI()
{

}

void LoginTip::handleSignalsAndSlots()
{
    connect(ui->pushButton_quicklogin,&QPushButton::clicked,[=](){userLogin(); });
}

LoginTip *LoginTip::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new LoginTip();
    }
    return m_pInstance;
}

bool LoginTip::eventFilter(QObject *watch, QEvent *event)
{
    return QWidget::eventFilter(watch,event);
}

void LoginTip::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(216, 217, 218));
    //小三角区域
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(m_startX , m_startY);// 30 30
    trianglePolygon << QPoint(m_startX + m_triangleWidth / 2, 40 - m_triangleHeight);
    trianglePolygon << QPoint(m_startX + m_triangleWidth, m_startY);
    QPainterPath drawPath;
    //调整三角形高度：1.界面留出空白高度 2.三角形起点高度 3.三角形高度一致
    drawPath.addRoundRect(0,m_startY,width(),height()-40,6,6);
//    drawPath.addRoundRect(this->rect(),8);
    drawPath.addPolygon(trianglePolygon);
    painter.drawPath(drawPath);

}

void LoginTip::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->close();
}

void LoginTip::userLogin()
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
}
