#include "PicWallItem.h"
#include "ui_PicWallItem.h"
#include <QPixmap>

PicWallItem::PicWallItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PicWallItem)
{
    ui->setupUi(this);
//    this->setMinimumSize(150,150);
//    this->setMaximumSize(180,180);
    this->setFixedSize(200,180);
//    addPicPathToMap();
    setPicItemWall("");
}

PicWallItem::~PicWallItem()
{
    delete ui;
}

void PicWallItem::addPicPathToMap()
{
    for(int  i = 0; i < 16; i++)
    {
        QString path = QString("E:/QtProjects/000QtDemo_51ctodemo/04_20SubVideoPlayer/VideoPlayer/pictures/recommend/commend%1.png").arg(i);
        m_picpath.insert(i,path);
    }

    for(QMap<int,QString>::iterator iter = m_picpath.begin(); iter!= m_picpath.end(); iter++)
    {
        setPicItemWall(iter.value());
        setPicItemWallText(QString::fromLocal8Bit("美好的歌曲%").arg(iter.key()));
    }
}

void PicWallItem::setPicItemWall(QString path)
{
    QPixmap pix("E:/QtProjects/000QtDemo_51ctodemo/04_20SubVideoPlayer/VideoPlayer/pictures/recommend/recommend4.png");
    ui->label_wallitem->setPixmap(pix);
    ui->label_wallitem->setScaledContents(true);//自适应
}

void PicWallItem::setPicItemWallText(QString text)
{
    ui->pushButton_wall_title->setText(text);
}
