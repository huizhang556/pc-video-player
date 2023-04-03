#include "RefreshButton.h"

RefreshButton::RefreshButton(QWidget *parent)
    : QPushButton(parent),
      m_pixmap(":/images/home/vtitle_switch.png"),
      m_interval(1),
      m_angle(0)
{
    initWorkUI();
    handleSignalsAndSLots();
}

RefreshButton::~RefreshButton()
{

}

void RefreshButton::initWorkUI()
{
    installEventFilter(this);
    m_timer.setInterval(m_interval);//单位： ms
}

void RefreshButton::handleSignalsAndSLots()
{
    //单击，刷新
//    connect(this,&RefreshButton::clicked,[=](){
//        m_timer.start();
//        QTimer::singleShot(1000,0,[=](){
//            m_timer.stop();
//            m_angle = 0;//角度设置为0度
//            this->update();//防止停止的位置不对，最后再更新一次
//        });
//    });

    connect(&m_timer,&QTimer::timeout,[=](){
//        qDebug() << QString(u8"定时器触发");
        on_refreshButton();
    });
}

void RefreshButton::setPixmap(const QPixmap& pixmap, const QSize& size)
{
    m_pixmap = pixmap;
    m_pixmap.scaled(size,Qt::KeepAspectRatio,Qt::SmoothTransformation);
}

void RefreshButton::setInterval(int msec)
{
    m_interval = msec;
}

void RefreshButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    //0.创建画家
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    //1.设定旋转中心点
    QRect rect((this-> width() - m_pixmap.width()) / 2,
               (this-> height() - m_pixmap.height()) / 2,
               m_pixmap.width(),
               m_pixmap.height());

    //2.我们使用 translate 把参考点设置为图形的中心点坐标
    painter.translate(0 + rect.x() + rect.width() / 2,
                      0 + rect.y() + rect.height() / 2);

    //3.设置旋转的角度
    painter.rotate(m_angle);

    //4.恢复中心点
    painter.translate(0 - (rect.x() + rect.width() / 2),
                      0 - (rect.y() + rect.height() / 2));

    //5.绘图操作
    painter.drawPixmap(rect,m_pixmap);
}

bool RefreshButton::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            m_pixmap.load(":/images/home/vtitle_switch_hover.png");
            this->update();
        }
        else if(event->type() == QEvent::Leave)
        {
            if(m_timer.isActive())//定时器在运行
            {
                m_pixmap.load(":/images/home/vtitle_switch_hover.png");
            }
            else
            {
                m_pixmap.load(":/images/home/vtitle_switch.png");
            }
            this->update();
        }
        else if(event->type() == QEvent::MouseButtonPress && mouseEvent->buttons() & Qt::LeftButton)
        {
            m_timer.start();
            QTimer::singleShot(1000,0,[=](){
                m_timer.stop();
                m_angle = 0;//角度设置为0度
                m_pixmap.load(":/images/home/vtitle_switch.png");
                this->update();//防止停止的位置不对，最后再更新一次
            });
        }
    }
    return QPushButton::eventFilter(watched,event);
}

void RefreshButton::on_refreshButton()
{
    if(m_angle++ == 360)
    {
        m_angle = 0;
    }
    this->update();
}
