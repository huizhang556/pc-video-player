#include "VideoProgressBar.h"
#include "ui_VideoProgressBar.h"
#include <QTimer>
#include <QPainter>
#include <QBitmap>

//类外初始化
VideoProgressBar* VideoProgressBar::m_pInstance = NULL;

VideoProgressBar::VideoProgressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoProgressBar)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(80,80);
//    this->setWindowOpacity(0.2);
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    QTimer *timer = new QTimer;
    timer->start(3);//3毫秒一次
    connect(timer,&QTimer::timeout,[=](){slot_updaterRotation();});
}

VideoProgressBar::~VideoProgressBar()
{
    delete ui;
    //删除创建的单例
    if(m_pInstance != NULL)
        delete m_pInstance;
    m_pInstance = NULL;
}

/*获取唯一单例*/
VideoProgressBar *VideoProgressBar::getInstance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new VideoProgressBar();
    }
    return m_pInstance;
}

//根据QPaintPath画出渐变色的圆弧
void VideoProgressBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);//取两者最小值
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);//设置渲染属性 反锯齿  文本反锯齿
    painter.translate(width / 2, height / 2);//绘制位置的圆心 平移至中心位置
    painter.scale(side / 120.0, side / 120.0);//按照最小的长度或高度缩放

    QConicalGradient gra(QPoint(0,0),0);//角度渐变
    gra.setColorAt(0,QColor("#3BB6FE"));//开始色彩
    gra.setColorAt(1,QColor("#FFFFFF"));//结束色彩
    QBrush brush(gra);//画刷

    int radis = 40;//角度
    int sider = 5;
    QRect rect(-radis,-radis,radis*2,radis*2);//-40 -40 80 80
    QPainterPath path;//绘画路劲
    path.arcTo(rect,0, 270);//在矩形内，以0度开始画 逆时针画270度

    QPainterPath subPath;
    subPath.addEllipse(rect.adjusted(sider, sider, -sider, -sider));//画椭圆 现在是画圆 四个点是矩形的四点个坐标

    path = path-subPath;
    painter.setBrush(brush);//QColor("#66CFFF")
    painter.setPen(Qt::NoPen);
    painter.rotate(rotation);//绘制角度
    painter.drawPath(path);//绘制路径
}

//循环坐标旋转体系
void VideoProgressBar::slot_updaterRotation()
{
    rotation++;
    if(rotation == 360)
    {
        rotation = 0;
    }
    update();//每update一次，执行paintEvent()
}
