#include "HeaderPic.h"
#include "ui_HeaderPic.h"

HeaderPic::HeaderPic(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::HeaderPic)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
}

HeaderPic::~HeaderPic()
{
    delete ui;
}

void HeaderPic::setHeaderPicture(const QString &path)
{
    m_picPath = path;
}

void HeaderPic::setHeaderBGColor(const QColor &color)
{
    m_bgColor = color;
}

void HeaderPic::setStatusButtonStatus(bool read)
{
    if(!read)
    {
        ui->pushButton_status->setStyleSheet("#pushButton_status{"
                                             "background-color: rgb(255, 0, 0);"
                                             "border-radius: 7px;"
                                             "}");
    }
    else
    {
        ui->pushButton_status->setStyleSheet("#pushButton_status{"
                                             "background-color: rgb(0, 255, 0);"
                                             "border-radius: 7px;"
                                             "}");
    }
}

void HeaderPic::setHeaderRadius(int radius)
{
    m_radius = radius;
}

void HeaderPic::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.setPen(Qt::NoPen);
        painter.setBrush(m_bgColor);//rgba 背景色一致

        QPainterPath drawPath;
        drawPath.addRoundedRect(this->rect(),m_radius,m_radius);
        drawPath.addRect(this->rect());
        //如果不绘制图片（其上面叠加的部分会被覆盖），通过setPixmap添加的图片，圆角失效，只能重绘（但是通过样式设置的图片是圆角生效的）
        painter.drawPixmap(0,0,width(),height(),QPixmap(m_picPath));
        painter.fillPath(drawPath,QBrush(m_bgColor));
}
