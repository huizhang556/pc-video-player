#include "GalleryItemForm.h"
#include "ui_GalleryItemForm.h"

#include <QDebug>
#include <QListWidgetItem>

GalleryItemForm::GalleryItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalleryItemForm)
{
    ui->setupUi(this);
    ui->listWidget_itempic->setFixedHeight(360);
    ui->widget_rec_title->setFixedHeight(60);
    this->setFixedHeight(420);
    initWorkUI();
    chandleSignalsAndSlots();
}

GalleryItemForm::~GalleryItemForm()
{
    delete ui;
}

void GalleryItemForm::chandleSignalsAndSlots()
{

}

void GalleryItemForm::initWorkUI()
{
    ui->listWidget_itempic->setViewMode(QListView::IconMode);//图表模式
    ui->listWidget_itempic->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_itempic->setResizeMode(QListWidget::Adjust);
//    ui->listWidget_itempic->setWrapping(true);//自动换行
//    ui->listWidget_itempic->setFlow(QListView::LeftToRight);//从左到右布局
    ui->listWidget_itempic->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_itempic->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0; i < 16; i++)
    {
        PicWallItem *pitem = new PicWallItem();
        QString path = QString("E:/QtProjects/000QtDemo_51ctodemo/04_20SubVideoPlayer/VideoPlayer/pictures/recommend/recommend%1.png").arg(i);
        pitem->setPicItemWall(path);
        pitem->setPicItemWallText(QString::fromLocal8Bit("美好的歌曲%1").arg(i+1));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(pitem->size().width()+15,pitem->size().height()));
        ui->listWidget_itempic->addItem(item);
        ui->listWidget_itempic->setItemWidget(item,pitem);
    }
//    adjustListWidgetItemsSize();
}

void GalleryItemForm::adjustListWidgetItemsSize()
{
    int row = 0;
    while(row < (ui->listWidget_itempic->count()))
    {
        QListWidgetItem *item = ui->listWidget_itempic->item(row);//在这里一个iconMode的item就是一个PicWallItem
        QWidget* widget = ui->listWidget_itempic->itemWidget(item);
        row++;
    }
}

void GalleryItemForm::setHeaderTitle(QString title)
{
    ui->pushButton_title->setText(title);
}



void GalleryItemForm::resizeEvent(QResizeEvent *event)
{
//    adjustListWidgetItemsSize();
}

