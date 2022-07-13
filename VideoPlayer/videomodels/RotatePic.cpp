#include "RotatePic.h"
#include <QDebug>

RotatePic::RotatePic(QWidget *parent) :
    QWidget(parent),
    m_roate(0)
{
    m_timer = new QTimer(this);
    m_labelpic = new QLabel();
    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addWidget(m_labelpic);
    vlayout->setSpacing(0);
    vlayout->setMargin(0);
    vlayout->setContentsMargins(0,0,0,0);
    this->setLayout(vlayout);
//    setFixedSize(50,50);
//    this->setMask(QRegion(0,0,50,50,QRegion::Ellipse).boundingRect());
    connect(m_timer,&QTimer::timeout,[=](){
        m_roate++;
        if(m_roate == 360)
            m_roate = 0;
    });
}

RotatePic::~RotatePic()
{

}

int RotatePic::getRoate()
{
    return m_roate;
}

void RotatePic::resetRoate(int roate)
{
    m_roate = roate;
}

void RotatePic::start()
{
    m_timer->start(50);
    m_roate = m_tempRoate;
}

void RotatePic::pause()
{
    m_timer->stop();
    m_tempRoate = m_roate;
}

void RotatePic::setSize(int width, int height)
{
    this->setFixedSize(width,height);
}

void RotatePic::setPicture(QString path)
{
    pix.load(path);
}

void RotatePic::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    pix.load(":/images/bgpic/dieji3.png");
//    m_roate = m_roate >= 360 ? 0 : m_roate;
    int imageWidth = pix.width();
    int imageHeight = pix.height();
    QPixmap temp(pix.size());
    temp.fill(Qt::transparent);
    QPainter  painter(&temp);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.translate(imageWidth / 2, imageHeight / 2); //让图片的中心作为旋转的中心
    painter.rotate(m_roate); //这个是将绘制坐标旋转到指定的角度
    painter.translate(-(imageWidth / 2), -(imageHeight / 2)); //使原点复原
    QRegion maskRegion(temp.rect(),QRegion::Ellipse);
    painter.setClipRegion(maskRegion);
    painter.drawPixmap(0, 0, pix);
//    painter.drawArc(temp.rect().adjusted(-3,-3,3,3),0,static_cast<int>(m_roate * 16));//进度圈
    painter.end();
    m_labelpic->setScaledContents(true);//图片自动调整大小
    m_labelpic->setPixmap(temp);
}
