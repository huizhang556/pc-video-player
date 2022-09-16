#include "TrianButton.h"
#include "ui_TrianButton.h"

#include <QLinearGradient>
#include <QPolygon>

TrianButton::TrianButton(QWidget *parent) :
    QPushButton(parent),
    m_offset(60),
    m_triangleWidth(20),
    m_triangleHeight(15),
    m_type(ButtonType::LeftType),
    ui(new Ui::TrianButton)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

TrianButton::~TrianButton()
{
    delete ui;
}

void TrianButton::initWorkUI()
{
    setFixedHeight(80);
    setText(QString(u8"设置一个测试按钮"));
}

void TrianButton::handleSignalsAndSlots()
{

}

void TrianButton::setButtonType(ButtonType type)
{
    m_type = type;
}

void TrianButton::setButtonPicture(const QString &path)
{
    ui->label_pic->setPixmap(QPixmap(path));
    ui->label_pic->setScaledContents(true);
}

void TrianButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    //小三角区域
    QPolygon trianglePolygon;
    trianglePolygon << QPoint(0,height()- m_triangleHeight);
    trianglePolygon << QPoint(m_offset,0);
    trianglePolygon << QPoint(this->width(),0);
    trianglePolygon << QPoint(this->width()-m_offset,height()- m_triangleHeight);
    trianglePolygon << QPoint(width()/2+m_triangleWidth/2 , height()- m_triangleHeight);
    trianglePolygon << QPoint(width()/2,height());
    trianglePolygon << QPoint(width()/2-m_triangleWidth/2 , height()- m_triangleHeight);
    QPainterPath drawPath;
    //调整三角形高度：1.界面留出空白高度 2.三角形起点高度 3.三角形高度一致
//    drawPath.addRoundedRect(0,0,width(),height()- m_triangleHeight,5,5);//嵌入按钮中时，按钮也要设置圆角
//     painter.drawPath(drawPath);

    switch (m_type)
    {
    case ButtonType::RoundRect://默认矩形
        {
            QLinearGradient lineGradient(0,0,400,400);
            lineGradient.setColorAt(0.0,Qt::white);
            lineGradient.setColorAt(0.5,Qt::yellow);
            lineGradient.setColorAt(0.0,Qt::blue);
            lineGradient.setSpread(QGradient::PadSpread);
            painter.setBrush(lineGradient);

            painter.setFont(QFont("Mircrosoft YaHei", 12));
            painter.setPen(QColor(255, 255, 255,0));

            if(isChecked())
            {
                drawPath.addPolygon(trianglePolygon);
//                drawPath.addRoundedRect(0,0,width(),height()- m_triangleHeight,5,5);
                painter.drawPath(drawPath);
                painter.drawText(this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QString(u8""));
            }
            else
            {
//                drawPath.addRoundedRect(0,0,width(),height()- m_triangleHeight,5,5);
                painter.drawPath(drawPath);
                painter.drawText(this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QString(u8""));
            }
        }
        break;
    case ButtonType::LeftType://左边按钮
        {
            QLinearGradient lineGradient(0,0,400,400);
            lineGradient.setColorAt(0.0,QColor(94, 133, 216));
            lineGradient.setColorAt(0.5,QColor(94, 133, 216));
            lineGradient.setColorAt(0.0,QColor(94, 133, 216));
            lineGradient.setSpread(QGradient::PadSpread);
            painter.setBrush(lineGradient);

            painter.setFont(QFont("Mircrosoft YaHei", 16));
            painter.setPen(QColor(255, 255, 255,0));

            if(isChecked())
            {
                drawPath.addPolygon(trianglePolygon);
//                drawPath.addRoundedRect(0,0,width(),height()- m_triangleHeight,5,5);
                painter.drawPath(drawPath);
//                painter.drawText(this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QString(u8"飙升榜"));
//                painter.drawPixmap(this->rect(),QPixmap("://images/home/rank_raisesong.png"));
//                ui->label_pic->setPixmap(QPixmap("://images/home/rank_raisesong.png"));
//                ui->label_pic->setScaledContents(true);
            }
            else
            {
//                drawPath.addRoundedRect(0,0,width(),height()- m_triangleHeight,5,5);
                painter.drawPath(drawPath);
//                painter.drawText(this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QString(u8"飙升榜"));
//                painter.drawPixmap(this->rect(),QPixmap("://images/home/rank_raisesong.png"));
//                ui->label_pic->setPixmap(QPixmap("://images/home/rank_raisesong.png"));
//                ui->label_pic->setScaledContents(true);
            }

        }
        break;
    case ButtonType::MidType://中间按钮
        {
            QLinearGradient lineGradient(0,0,400,400);
            lineGradient.setColorAt(0.0,QColor(230, 92, 68));
            lineGradient.setColorAt(0.5,QColor(230, 92, 68));
            lineGradient.setColorAt(0.0,QColor(230, 92, 68));
            lineGradient.setSpread(QGradient::PadSpread);
            painter.setBrush(lineGradient);

            painter.setFont(QFont("Mircrosoft YaHei", 16));
            painter.setPen(QColor(255, 255, 255,0));

            if(isChecked())
            {
                drawPath.addPolygon(trianglePolygon);
//                drawPath.addRoundedRect(0,0,width(),height()- m_triangleHeight,5,5);
                painter.drawPath(drawPath);
//                painter.drawPixmap(this->rect(),QPixmap("://images/home/rank_newsong.png"));
//                painter.drawText(this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QString(u8"新歌榜"));
//                ui->label_pic->setPixmap(QPixmap("://images/home/rank_newsong.png"));
//                ui->label_pic->setScaledContents(true);
            }
            else
            {
//                drawPath.addRoundedRect(0,0,width(),height()- m_triangleHeight,5,5);
                painter.drawPath(drawPath);
//                painter.drawPixmap(this->rect(),QPixmap("://images/home/rank_newsong.png"));
//                painter.drawText(this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QString(u8"新歌榜"));
//                ui->label_pic->setPixmap(QPixmap("://images/home/rank_newsong.png"));
//                ui->label_pic->setScaledContents(true);
            }
        }
        break;
    case ButtonType::rightType://右边按钮
        {
                QLinearGradient lineGradient(0,0,400,400);
                lineGradient.setColorAt(0.0,QColor(230, 92, 68));
                lineGradient.setColorAt(0.5,QColor(230, 92, 68));
                lineGradient.setColorAt(0.0,QColor(230, 92, 68));
                lineGradient.setSpread(QGradient::PadSpread);
                painter.setBrush(lineGradient);

                painter.setFont(QFont("Mircrosoft YaHei", 16));
                painter.setPen(QColor(255, 255, 255,0));

                if(isChecked())
                {
                    drawPath.addPolygon(trianglePolygon);
//                    drawPath.addRoundedRect(0,0,width(),height()- m_triangleHeight,5,5);
                    painter.drawPath(drawPath);
//                    painter.drawPixmap(this->rect(),QPixmap("://images/home/rank_hotsong.png"));
//                    painter.drawText(this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QString(u8"热歌榜"));
//                    ui->label_pic->setPixmap(QPixmap("://images/home/rank_hotsong.png"));
//                    ui->label_pic->setScaledContents(true);
                }
                else
                {
//                    drawPath.addRoundedRect(0,0,width(),height()- m_triangleHeight,5,5);
                    painter.drawPath(drawPath);
//                    painter.drawPixmap(this->rect(),QPixmap("://images/home/rank_hotsong.png"));
//                    painter.drawText(this->rect(), Qt::AlignVCenter | Qt::AlignHCenter, QString(u8"热歌榜"));
//                    ui->label_pic->setPixmap(QPixmap("://images/home/rank_hotsong.png"));
//                    ui->label_pic->setScaledContents(true);
                }
        }
        break;
    default:
        {
                drawPath.addRoundedRect(0,0,width(),height()- m_triangleHeight,5,5);
                painter.drawPath(drawPath);
        }
        break;
    }

    update();
}
