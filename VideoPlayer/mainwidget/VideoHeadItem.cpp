#include "VideoHeadItem.h"
#include "ui_VideoHeadItem.h"

#include <QPainter>
#include <QPainterPath>
#include <QDebug>

VideoHeadItem::VideoHeadItem(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::VideoHeadItem)
{
    ui->setupUi(this);
    resize(200,270);
    initWorkUI();
    handleSignalsAndSlots();
    setEventFilter();
    setItemMask(true);
    setItemCanScale(false);
}

VideoHeadItem::~VideoHeadItem()
{
    delete ui;
    if(m_videoItemHover != nullptr)
        delete m_videoItemHover;
    m_videoItemHover = nullptr;
}

void VideoHeadItem::initWorkUI()
{
//    this->setAttribute(Qt::WA_TranslucentBackground,true);
    ui->pushButton_mainPlayer->hide();
    m_videoItemHover = new VideoItemHover();//指定父亲，就用相对坐标
    m_videoItemHover->setObjectName(QString::fromUtf8("m_videoItemHover"));
}

void VideoHeadItem::handleSignalsAndSlots()
{
    connect(ui->pushButton_mainPlayer,&QPushButton::clicked,[=](){
        qDebug() << "player clicked";
        emit sig_sendPlayer();
    });
}

void VideoHeadItem::setEventFilter()
{
    this->installEventFilter(this);
}

void VideoHeadItem::setItemPicture(const QString path)
{
    m_picPath = path;
}

void VideoHeadItem::setItemBGColor(const QColor &color)
{
    m_bgColor = color;
}

void VideoHeadItem::setItemMask(bool enabled)
{
    if(enabled)
    {
        ui->widget_mask->setStyleSheet("#widget_mask"
                                       "{"
                                       "background-color: rgba(20, 20, 20,0.0);"
                                       "}"
                                       "#widget_mask:hover"
                                       "{"
                                       "background-color: rgba(20, 20, 20,0.6);"
                                       "}"
                                       );
    }
    else
    {
        ui->widget_mask->setStyleSheet("#widget_mask"
                                       "{"
                                       "background-color: rgba(20, 20, 20,0.0);"
                                       "}");
    }
}

void VideoHeadItem::setItemCanScale(bool can)
{
    if(can)
    {
        m_canScale = true;
    }
    else
    {
        m_canScale = false;
    }
}

bool VideoHeadItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            this->setCursor(Qt::PointingHandCursor);
            if(m_canScale)
            {
                m_iscaled = true;//进行缩放
                update();
            }

            ui->pushButton_mainPlayer->show();
//            m_videoItemHover->resize(this->size() + QSize(40,40));
            int x = this->mapToGlobal(this->pos()).x();
            int y = this->mapToGlobal(this->pos()).y();
            m_videoItemHover->setGeometry(x-20,y-20,this->width()+40,this->height()+40);
            if(m_videoItemHover->isHidden())
            {
                //超出边界如何处理？show or not show ?
//                m_videoItemHover->show();
            }
        }
        else if(event->type() == QEvent::Leave)
        {
            this->setCursor(Qt::ArrowCursor);
            if(m_canScale)
            {
                m_iscaled = false;//不进行缩放
                update();
            }

            //BUG:这里不能用leave事件，会造成反复hide和show，应该把hide交给m_videoItemHover去处理
            ui->pushButton_mainPlayer->hide();
//            if(!m_videoItemHover->isHidden())
//                m_videoItemHover->hide();
        }
    }
    return QLabel::eventFilter(watched,event);
}

void VideoHeadItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(14, 27, 44,10));//rgba 背景色一致

        QPainterPath drawPath;
        drawPath.addRoundedRect(this->rect(),7,7);
        drawPath.addRect(this->rect());
        if(m_iscaled)
        {
            //如果不绘制图片（其上面叠加的部分会被覆盖），通过setPixmap添加的图片，圆角失效，只能重绘（但是通过样式设置的图片是圆角生效的）
            painter.drawPixmap(-5,-5,width()+10,height()+10,QPixmap(m_picPath));
        }
        else
        {
            painter.drawPixmap(0,0,width(),height(),QPixmap(m_picPath));
        }
        painter.fillPath(drawPath,QBrush(m_bgColor));//先绘图片再填充外部边缘（准确来说叫颜色压住覆盖）
}
