#include "SubUnitItem.h"
#include "ui_SubUnitItem.h"

SubUnitItem::SubUnitItem(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::SubUnitItem)
{
    ui->setupUi(this);
    installEventFilter(this);
    setItemMask(false);
    setItemCanScale(true);
}

SubUnitItem::SubUnitItem(const QString &picpath, QWidget *parent):
    QLabel(parent),
    m_picPath(picpath),
    ui(new Ui::SubUnitItem)
{
    ui->setupUi(this);
    installEventFilter(this);
    setItemMask(false);
    setItemCanScale(true);
}

SubUnitItem::~SubUnitItem()
{
    delete ui;
}

void SubUnitItem::setItemPicture(const QString &path)
{
    m_picPath = path;
}

void SubUnitItem::setItemMask(bool enabled)
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

void SubUnitItem::setItemCanScale(bool can)
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

bool SubUnitItem::eventFilter(QObject *watched, QEvent *event)
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
        }
        else if(event->type() == QEvent::Leave)
        {
            this->setCursor(Qt::ArrowCursor);
            if(m_canScale)
            {
                m_iscaled = false;//不进行缩放
                update();
            }
        }
    }
    return QLabel::eventFilter(watched,event);
}

void SubUnitItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(14, 27, 44,10));//rgba 背景色一致

        QPainterPath drawPath;
        drawPath.addRoundedRect(this->rect(),8,8);
        drawPath.addRect(this->rect());
        if(!m_iscaled)
        {
            //如果不绘制图片（其上面叠加的部分会被覆盖），通过setPixmap添加的图片，圆角失效，只能重绘（但是通过样式设置的图片是圆角生效的）
            painter.drawPixmap(0,0,width(),height(),QPixmap(m_picPath));
        }
        else
        {
            //如果不绘制图片（其上面叠加的部分会被覆盖），通过setPixmap添加的图片，圆角失效，只能重绘（但是通过样式设置的图片是圆角生效的）
            painter.drawPixmap(-5,-5,width()+10,height()+10,QPixmap(m_picPath));//虽然超出了范围，但是超出的部分会被剪裁掉，不会放大绘制
        }
        painter.fillPath(drawPath,QBrush(QColor(14, 27, 44)));
}
