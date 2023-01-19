#include "VideoSortType.h"
#include "ui_VideoSortType.h"
#include "MemberVideoItem.h"
#include "global/Global.h"
#include <QScrollBar>
#include <QDebug>

VideoSortType::VideoSortType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoSortType)
{
    ui->setupUi(this);
    initWorkUI();
    setFixedHeight(430);
    handleSignalsAndSlots();
    setInstallEventFilter();
}

VideoSortType::~VideoSortType()
{
    delete ui;
}

void VideoSortType::initWorkUI()
{
    ui->pushButton_flush->setIcon(QIcon(":/images/home/vtitle_switch.png"));
    ui->pushButton_flush->setText(QString(u8"换一换"));

    ui->listWidget_items->setViewMode(QListView::IconMode);
    ui->listWidget_items->setMovement(QListView::Static);
    ui->listWidget_items->setWrapping(false);
    ui->listWidget_items->setResizeMode(QListView::Adjust);
    ui->listWidget_items->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_items->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_items->setVerticalScrollMode(QListView::ScrollPerPixel);
    ui->listWidget_items->horizontalScrollBar()->setDisabled(true);
    ui->listWidget_items->setOffset(225,-100,0,0,45);
    ui->listWidget_items->setButtonControl(false);

    for(int i = 0; i < 17; i++)
    {
        //精选视频列表
//        QString path1 = Global::appDirPath + QString("/pictures/mylike/videos_list2/list_intro%1.png").arg(i);
        QString path2 = Global::appDirPath + QString("/pictures/mylike/videos_list2/list_intro%1.jpg").arg(i);
        MemberVideoItem *itemWidget = new MemberVideoItem(path2,QString(u8"沸腾人生%1").arg(i),QString(u8"再现中国重卡制造史"),QColor(14, 27, 44));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(225,360));
        ui->listWidget_items->addItem(item);
        ui->listWidget_items->setItemWidget(item,itemWidget);
    }
}

void VideoSortType::handleSignalsAndSlots()
{
    //换一换 document length = maximum() - minimum() + pageStep().
    connect(ui->pushButton_flush,&QPushButton::clicked,[=](){
        int step = ui->listWidget_items->horizontalScrollBar()->value();
        if(step == ui->listWidget_items->horizontalScrollBar()->maximum())
        {
//            ui->listWidget_items->horizontalScrollBar()->setValue(ui->listWidget_items->horizontalScrollBar()->minimum());//重头播放
            QPropertyAnimation *pAnimation = new QPropertyAnimation(ui->listWidget_items->horizontalScrollBar(),"value",this);
            pAnimation->setDuration(800);
            pAnimation->setStartValue(step);
            pAnimation->setEndValue(ui->listWidget_items->horizontalScrollBar()->minimum());
            pAnimation->start();
            connect(pAnimation,&QPropertyAnimation::finished,[=](){
            pAnimation->deleteLater();
            });
        }
        else
        {
//            ui->listWidget_items->horizontalScrollBar()->setValue(ui->listWidget_items->item(0)->sizeHint().width()*7 + step);
            QPropertyAnimation *pAnimation = new QPropertyAnimation(ui->listWidget_items->horizontalScrollBar(),"value",this);
            pAnimation->setDuration(800);
            pAnimation->setStartValue(step);
            pAnimation->setEndValue(ui->listWidget_items->item(0)->sizeHint().width()*7 + step);
            pAnimation->start();
            connect(pAnimation,&QPropertyAnimation::finished,[=](){
            pAnimation->deleteLater();
            });
        }
    });
}

void VideoSortType::setInstallEventFilter()
{
    ui->listWidget_items->installEventFilter(this);
}

//bool VideoSortType::eventFilter(QObject *watched, QEvent *event)
//{
//    if(watched == ui->listWidget_items)
//    {
//        if(event->type() == QEvent::Resize)
//        {
//            autoResizeListItems();
//        }
//    }
//    return QWidget::eventFilter(watched,event);
//}

void VideoSortType::autoResizeListItems()
{
    if(ui->listWidget_items->count() == 0) return;

}
