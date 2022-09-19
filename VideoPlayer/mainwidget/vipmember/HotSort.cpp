#include "HotSort.h"
#include "ui_HotSort.h"

#include "global/Global.h"
#include "mainwidget/songlistsort/TagsItem.h"
#include <QListWidgetItem>
#include <QScrollBar>
#include <QDebug>

HotSort::HotSort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HotSort)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    this->setMinimumHeight(230*2 + 60);
}

HotSort::~HotSort()
{
    delete ui;
}

void HotSort::initWorkUI()
{
    ui->pushButton_marks->setIcon(QIcon("://images/user/itemmark_new2.png"));
    ui->pushButton_marks->setIconSize(QSize(36,36));

    ui->listWidget_vipItems->setViewMode(QListView::IconMode);
    ui->listWidget_vipItems->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_vipItems->setResizeMode(QListWidget::Adjust);
    ui->listWidget_vipItems->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_vipItems->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_vipItems->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_vipItems->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    for(int i = 0; i < 18; i++)
    {
        QString path1 = QString(Global::appDirPath +"/pictures/musics/style/music%1.png").arg(i);
        slot_addSongItem("www.hao123.com",path1,QString::fromLocal8Bit("遥远的故事 | 远方的人儿"),QString::fromLocal8Bit("故事中的人%1").arg(i));
    }
}

void HotSort::handleSignalsAndSlots()
{

}

void HotSort::setInstallEventFilter()
{
    ui->listWidget_vipItems->installEventFilter(this);
}

void HotSort::slot_addSongItem(const QString &url, const QString &path, const QString &tags, const QString &mark)
{
    TagsItem *itemWidget = new TagsItem(path,tags,mark);
    QListWidgetItem *item = new QListWidgetItem(url);
    item->setSizeHint(itemWidget->size());
    ui->listWidget_vipItems->addItem(item);
    ui->listWidget_vipItems->setItemWidget(item,itemWidget);

    //信号与槽
    connect(itemWidget,&TagsItem::sig_sendMarkItem,[=](){
        emit sig_sendTags(url);
        qDebug() << QString::fromLocal8Bit("已发送url==>%1").arg(tags);
    });
}

bool HotSort::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_vipItems)
    {
        if(event->type() == QEvent::Resize)
        {
            resizeListWidgetItemWidget();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void HotSort::resizeListWidgetItemWidget()
{
    int width = ui->listWidget_vipItems->width();
    //滚动条宽度默认17
    //最小显示6个item,最大刚好显示10个item
    //6~7 1116~1302 7~8 1302~1488 8~9 1488~1674 9~10 1674~1860
    for(int i = 0; i < ui->listWidget_vipItems->count(); i++)
    {
        //vip 会员分类下载
        int avgWidth = calculateItemWidth(width - ui->listWidget_vipItems->verticalScrollBar()->width() + 100);
        ui->listWidget_vipItems->item(i)->setSizeHint(QSize(avgWidth,avgWidth*SCALE));
//        qDebug() << QString::fromLocal8Bit("动态更新后的item大小：宽度%1，高度%2").arg(avgWidth).arg(avgWidth*SCALE);
    }
}

int HotSort::calculateItemWidth(int width)
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
        return  (int)(width/7);;
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
