#include "SubUnitItem.h"
#include "ui_SubUnitItem.h"

SubUnitItem::SubUnitItem(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::SubUnitItem)
{
    ui->setupUi(this);
}

SubUnitItem::SubUnitItem(const QString &picpath, QWidget *parent):
    QLabel(parent),
    m_picPath(picpath),
    ui(new Ui::SubUnitItem)
{
    ui->setupUi(this);
}

SubUnitItem::~SubUnitItem()
{
    delete ui;
}

void SubUnitItem::setItemPicture(const QString &path)
{
    m_picPath = path;
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
        //如果不绘制图片（其上面叠加的部分会被覆盖），通过setPixmap添加的图片，圆角失效，只能重绘（但是通过样式设置的图片是圆角生效的）
        painter.drawPixmap(0,0,width(),height(),QPixmap(m_picPath));
        painter.fillPath(drawPath,QBrush(QColor(14, 27, 44)));
}
