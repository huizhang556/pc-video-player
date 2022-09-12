#include "GalleryItemForm.h"
#include "ui_GalleryItemForm.h"

#include <QFont>
#include <QDebug>
#include <QMargins>
#include <QScrollBar>
#include <QListWidgetItem>

GalleryItemForm::GalleryItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GalleryItemForm)
{
    ui->setupUi(this);
    this->setMinimumHeight(432);
    ui->listWidget_itempic->setViewMode(QListView::IconMode);
    ui->listWidget_itempic->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_itempic->setResizeMode(QListWidget::Adjust);
    ui->listWidget_itempic->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_itempic->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_itempic->installEventFilter(this);
//    ui->widget_rec_title->setFixedHeight(60);
    initWorkUI();
    chandleSignalsAndSlots();
}

GalleryItemForm::~GalleryItemForm()
{
    delete ui;
}

void GalleryItemForm::chandleSignalsAndSlots()
{
    connect(ui->listWidget_itempic,&QListWidget::itemEntered,[=](QListWidgetItem *item){
//        item->setSizeHint(item->sizeHint()+QSize(15,15));
        update();
        qDebug() << "enter item";
    });

    connect(ui->listWidget_itempic,&QListWidget::itemChanged,[=](QListWidgetItem *item){
        qDebug() <<"item leave";

    });
}

void GalleryItemForm::initWorkUI()
{
    ui->listWidget_itempic->setViewMode(QListView::IconMode);//图表模式
    ui->listWidget_itempic->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_itempic->setResizeMode(QListWidget::Adjust);
    ui->listWidget_itempic->setWrapping(false);//自动换行 所有itm在一行显示
//    ui->listWidget_itempic->setIconSize(QSize(260,260));
    ui->listWidget_itempic->setFlow(QListView::LeftToRight);//从左到右布局  多行显示变成一行显示( 与模式有关)
    ui->listWidget_itempic->setMouseTracking(true);
    ui->listWidget_itempic->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_itempic->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

//    for(int i = 0; i < 18; i=i+2)
//    {
//        PicWallItem *pitem = new PicWallItem();
//        QString path = QString(Global::appDirPath + "/pictures/recommend/recommend%1.png").arg(i);
//        pitem->setPicItemWall(path);
//        pitem->setPicItemWall2(path);
//        pitem->setPicItemWallText(QString::fromLocal8Bit("美好的歌曲%1").arg(i+1));
//        pitem->setPicItemWallText2(QString::fromLocal8Bit("美好的歌曲%1").arg(i+2));
//        QListWidgetItem *item = new QListWidgetItem();
//        item->setSizeHint(QSize(pitem->size().width()+10,pitem->size().height()));
////        QPixmap pix(path);
////        pix.scaled(200,170,Qt::KeepAspectRatio);
////        item->icon().addPixmap(pix);
////        item->setText(QString::fromLocal8Bit("美好的歌曲%1").arg(i+1));
////        item->setSizeHint(QSize(270,350));
////        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
////        item->setTextAlignment(Qt::AlignCenter);
//        ui->listWidget_itempic->addItem(item);
//        ui->listWidget_itempic->setItemWidget(item,pitem);
//    }
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

void GalleryItemForm::setItemPictures(int size,QString path)
{
   for(int i = 0; i < size; i++)
   {
       QString path1 = QString(Global::appDirPath + path + "/music%1.png").arg(i);
       QString path2 = QString(Global::appDirPath + path + "/music%1.png").arg(i+1);
       QString info1 = QString(u8"美好的歌曲%1").arg(i);
       QString info2 = QString(u8"美好的歌曲%1").arg(i+1);
       slot_addGalleryItem("www.hao123.com",path1,path2,info1,info2);
   }
}

void GalleryItemForm::slot_addGalleryItem(const QString &url, const QString &pic1, const QString &pic2, const QString &text1, const QString &text2)
{
    PicWallItem *pitem = new PicWallItem();
    //设置图片
    pitem->setPicItemWall(pic1);
    pitem->setPicItemWall2(pic2);
    //设置文字
    pitem->setPicItemWallText(text1);
    pitem->setPicItemWallText2(text2);
    //设置开关
    pitem->getItemPic_1Label()->constructItem("://images/user/itemmark_new.png",QString(u8"6.6"),true,true,false);
    pitem->getItemPic_2Label()->constructItem("://images/user/itemmark_vyp.png",QString(u8"6.6"),true,true,false);

    QListWidgetItem *item = new QListWidgetItem(url);
//    item->setData(Qt::UserRole,url);
    item->setSizeHint(QSize(pitem->size().width()+10,pitem->size().height()));
    //        QPixmap pix(path);
    //        pix.scaled(200,170,Qt::KeepAspectRatio);
    //        item->icon().addPixmap(pix);
    //        item->setText(QString::fromLocal8Bit("美好的歌曲%1").arg(i+1));
    //        item->setSizeHint(QSize(270,350));
    //        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    //        item->setTextAlignment(Qt::AlignCenter);
    ui->listWidget_itempic->addItem(item);
    ui->listWidget_itempic->setItemWidget(item,pitem);
}

void GalleryItemForm::resizeGalleryItemSize()
{
    int width = ui->listWidget_itempic->width();
//    滚动条宽度默认17
    int colWidth  = (int)((width - ui->listWidget_itempic->verticalScrollBar()->width() - 1)/7);
    for(int i = 0; i < ui->listWidget_itempic->count(); i++)
    {
//        if( colWidth - 1 < MINSIZE.width())
//        {
//            emit sig_itemResizeChanged(QSize(MINSIZE.width()*7,MINSIZE.height()+ui->listWidget_itempic->horizontalScrollBar()->height()+20));
//            ui->listWidget_itempic->item(i)->setSizeHint(QSize(150,350));
//        }
//        else
//        {
            emit sig_itemResizeChanged(QSize((colWidth-1)*7,(colWidth-1)*SCALE + ui->listWidget_itempic->horizontalScrollBar()->height()+20));
            ui->listWidget_itempic->item(i)->setSizeHint(QSize(colWidth - 1,(colWidth-1)*SCALE));
//            qDebug() << QString::fromLocal8Bit("动态更新后的item大小：宽度%1，高度%2").arg(colWidth-1).arg(colWidth*SCALE);
//        }
    }

}


void GalleryItemForm::setHeaderTitle(QString title)
{
    ui->pushButton_title->setText(title);//主题
}



void GalleryItemForm::resizeEvent(QResizeEvent *event)
{
    //    adjustListWidgetItemsSize();
}

bool GalleryItemForm::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_itempic)
    {
        if( event->type() == QEvent::Wheel)
        {
            ui->listWidget_itempic->horizontalScrollBar()->setEnabled(false);
        }
        else if(event->type() == QEvent::Resize)
        {
            resizeGalleryItemSize();
        }
    }
    return  QWidget::eventFilter(watched,event);
}

//下一个item
void GalleryItemForm::on_pushButton_itemnext_clicked()
{
    int step = ui->listWidget_itempic->horizontalScrollBar()->value();
    ui->listWidget_itempic->horizontalScrollBar()->setValue(step + ui->listWidget_itempic->item(0)->sizeHint().width());
}

//上一个item
void GalleryItemForm::on_pushButton_itemprevious_clicked()
{
    int step = ui->listWidget_itempic->horizontalScrollBar()->value();
    ui->listWidget_itempic->horizontalScrollBar()->setValue(step - ui->listWidget_itempic->item(0)->sizeHint().width());
}
