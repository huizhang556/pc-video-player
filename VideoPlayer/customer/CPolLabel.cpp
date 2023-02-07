#include "CPolLabel.h"

CPolLabel::CPolLabel(QWidget *parent) :
    QLabel(parent)
{

}

CPolLabel::CPolLabel(const QSize &size, const QString &pic, const int radius, QWidget *parent):
    QLabel(parent),
    m_picpath(pic),
    m_radius(radius)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(size);
//    //阴影效果
//    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
//    shadowEffect->setColor(Qt::darkGreen);
//    shadowEffect->setOffset(0, 0);
//    shadowEffect->setBlurRadius(10);
//    this->setGraphicsEffect(shadowEffect);
//    //模糊效果
//    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect(this);
//    blurEffect->setBlurRadius(0);
//    blurEffect->setBlurHints(QGraphicsBlurEffect::QualityHint);
//    this->setGraphicsEffect(blurEffect);
}

CPolLabel::~CPolLabel()
{

}

bool CPolLabel::eventFilter(QObject *watched, QEvent *event)
{

    return QLabel::eventFilter(watched,event);
}

void CPolLabel::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.begin(this);
    // 抗锯齿 + 平滑边缘处理
    painter.setRenderHints(QPainter::Antialiasing, true);
    painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
    // 裁剪为圆角
    QPainterPath path;
    path.addEllipse(5, 5, this->width()-10, this->height()-10);
    painter.setClipPath(path);
    painter.drawPixmap(10, 10, this->width()-20, this->height()-20, QPixmap(m_picpath));
//    painter.save();
    painter.setPen(QPen(Qt::red,6));
    painter.setBrush(Qt::red);
    painter.drawArc(QRect(5,5,this->width()-10,this->height()-10),0,16*360);//矩形区域 起始角度 占用角度（每度：16度）
}

//压缩图片为指定宽高
QPixmap CPolLabel::scaledPixmap(const QPixmap &src, int width, int height)
{
    return src.scaled(width, (height == 0 ? width : height),
            Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}


/**
 * 圆角图片
 * src 原图片
 * radius 图片半径
 */
QPixmap CPolLabel::generatePixmap(const QPixmap &src, const int &radius) {

    // 无效图片不处理
    if (src.isNull()) {
        return src;
    }

    // 压缩图片
    QPixmap pixmap = scaledPixmap(src, radius * 2,radius * 2);

    QPixmap dest(2*radius, 2*radius);
    dest.fill(Qt::transparent);
    QPainter painter(&dest);
    // 抗锯齿 + 平滑边缘处理
    painter.setRenderHints(QPainter::Antialiasing, true);
    painter.setRenderHints(QPainter::SmoothPixmapTransform, true);
    // 裁剪为圆角
    QPainterPath path;
    path.addEllipse(0, 0, 2*radius, 2*radius);
    painter.setClipPath(path);
    painter.drawPixmap(0, 0, 2*radius, 2*radius, pixmap);

    return dest;
}
