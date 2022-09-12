#include "PicWallItem.h"
#include "ui_PicWallItem.h"
#include <QDebug>
#include <QPixmap>
#include <QRegion>

PicWallItem::PicWallItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicWallItem)
{
    ui->setupUi(this);
    installEventFilter(this);
}

PicWallItem::~PicWallItem()
{
    delete ui;
}

QPushButton* PicWallItem::getWallItemTextButton()
{
    return ui->pushButton_wall_title1;
}


void PicWallItem::setPicItemWall(QString path)
{
    QPixmap pix(path);
//    ui->label_wallitem1->setPixmap(pix);
//    ui->label_wallitem1->setScaledContents(true);//自适应
}

void PicWallItem::setPicItemWallText(QString text)
{
    ui->pushButton_wall_title1->setText(text);
}

void PicWallItem::setPicItemWall2(QString path)
{
    QPixmap pix(path);
//    ui->label_wallitem2->setPixmap(pix);
//    ui->label_wallitem2->setScaledContents(true);//自适应
}

void PicWallItem::setPicItemWallText2(QString text)
{
    ui->pushButton_wall_title2->setText(text);
}

CusLabelItem *PicWallItem::getItemPic_1Label()
{
    return ui->label_wallitem1;
}

CusLabelItem *PicWallItem::getItemPic_2Label()
{
    return ui->label_wallitem2;
}

void PicWallItem::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    emit sig_sizeChange(this->size());
}

void PicWallItem::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing,true);
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(QColor(56, 67, 99));//50 77 91
//    QPainterPath drawPath;

//    drawPath.addRoundedRect(this->rect(),10,10);//嵌入按钮中时，按钮也要设置圆角
//    painter.drawPath(drawPath);
}

bool PicWallItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Resize)
        {
            setItemMask();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void PicWallItem::setItemMask()
{
//    QRegion maskRegion(this->rect(),QRegion::Rectangle);
//    this->setMask(maskRegion);
    update();
}

