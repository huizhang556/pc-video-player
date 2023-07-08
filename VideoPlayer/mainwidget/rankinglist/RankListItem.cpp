#include "RankListItem.h"
#include "ui_RankListItem.h"

#include "global/Global.h"
#include "mainwidget/songlistsort/TagsItem.h"
#include <QListWidgetItem>
#include <QScrollBar>
#include <QDebug>

RankListItem::RankListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RankListItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEvevtFilter();
    this->setMinimumHeight(230*2 + 60);
}

RankListItem::~RankListItem()
{
    delete ui;
}

void RankListItem::initWorkUI()
{
    ui->listWidget_rankItem->setViewMode(QListView::IconMode);
    ui->listWidget_rankItem->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_rankItem->setResizeMode(QListWidget::Adjust);
//    ui->listWidget_rankItem->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_rankItem->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_rankItem->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_rankItem->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    slot_addRankListItem();
}

void RankListItem::handleSignalsAndSlots()
{
    connect(ui->pushButton_left,&QPushButton::clicked,[=](){
        int step = ui->listWidget_rankItem->horizontalScrollBar()->value();
        ui->listWidget_rankItem->horizontalScrollBar()->setValue(step - ui->listWidget_rankItem->item(0)->sizeHint().width());
    });
    connect(ui->pushButton_right,&QPushButton::clicked,[=](){
        int step = ui->listWidget_rankItem->horizontalScrollBar()->value();
        ui->listWidget_rankItem->horizontalScrollBar()->setValue(step + ui->listWidget_rankItem->item(0)->sizeHint().width());
    });
}

void RankListItem::setInstallEvevtFilter()
{
    ui->listWidget_rankItem->installEventFilter(this);
}

void RankListItem::slot_addRankListItem()
{
    for(int i = 0; i < 18; i++)
    {
        QString path1 = QString(Global::appDirPath +"/pictures/musics/style/music%1.png").arg(i);
        slot_addSongItem_recommend("www.hao123.com",path1,QString::fromLocal8Bit("遥远的故事 | 远方的人儿"),QString::fromLocal8Bit("故事中的人%1").arg(i));
    }
}

void RankListItem::slot_addSongItem_recommend(const QString &url, const QString &path, const QString &tags, const QString &mark)
{
    TagsItem *itemWidget = new TagsItem(path,tags,mark);
    QListWidgetItem *item = new QListWidgetItem(url);
    item->setSizeHint(itemWidget->size());
    ui->listWidget_rankItem->addItem(item);
    ui->listWidget_rankItem->setItemWidget(item,itemWidget);
    //调整大小

}

bool RankListItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_rankItem)
    {
        if(event->type() == QEvent::Resize)
        {
            resizeListWidgetItemWidget();
            emit sig_itemSizeChanged(QSize(this->width(), this->height()));
        }
    }
    return QWidget::eventFilter(watched,event);
}

void RankListItem::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    resizeListWidgetItemWidget();
}

void RankListItem::resizeListWidgetItemWidget()
{
    int width = ui->listWidget_rankItem->width();
    //滚动条宽度默认17
    //最小显示6个item,最大刚好显示10个item
    //6~7 1116~1302 7~8 1302~1488 8~9 1488~1674 9~10 1674~1860
    for(int i = 0; i < ui->listWidget_rankItem->count(); i++)
    {
        int avgWidth = calculateItemWidth(width - ui->listWidget_rankItem->verticalScrollBar()->width() + 99);
        ui->listWidget_rankItem->item(i)->setSizeHint(QSize(avgWidth,avgWidth*SCALE));
//        qDebug() << QString::fromLocal8Bit("动态更新后的item大小：宽度%1，高度%2").arg(avgWidth).arg(avgWidth*SCALE);
    }
}

int RankListItem::calculateItemWidth(int width)
{
    if(width < MINSIZE.width()*6)// 1116及其以下 显示6个
    {
        return  MINSIZE.width();
    }
    else if(width < MINSIZE.width()*7)//显示7个
    {
        return  (int)(width/6);
    }
    else if(width < MINSIZE.width()*8)//显示8个
    {
        return  (int)(width/7);
    }
    else if(width < MINSIZE.width()*9)//显示9个
    {
        return  (int)(width/8);
    }
    else if(width < MINSIZE.width()*10)//显示10个
    {
        return  (int)(width/9);
    }
    else if(width < MINSIZE.width()*11)//显示10个
    {
        return  (int)(width/10);
    }
}
