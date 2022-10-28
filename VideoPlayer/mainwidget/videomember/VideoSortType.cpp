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

    for(int i = 0; i < 17; i++)
    {
//        QString path1 = Global::appDirPath + QString("/pictures/mylike/videos_list2/list_intro%1.png").arg(i);
        QString path2 = Global::appDirPath + QString("/pictures/mylike/videos_list2/list_intro%1.jpg").arg(i);
        MemberVideoItem *itemWidget = new MemberVideoItem(path2,QString(u8"沸腾人生%1").arg(i),QString(u8"再现中国重卡制造史"));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());
        ui->listWidget_items->addItem(item);
        ui->listWidget_items->setItemWidget(item,itemWidget);
    }
}

void VideoSortType::handleSignalsAndSlots()
{
    //换一换 document length = maximum() - minimum() + pageStep().
    connect(ui->pushButton_flush,&QPushButton::clicked,[=](){
        int step = ui->listWidget_items->horizontalScrollBar()->value();
//        qDebug() << QString(u8"当前step:") << step << QString(u8"滚动条总长度：")<<ui->listWidget_items->horizontalScrollBar()->maximum();
        if(step == ui->listWidget_items->horizontalScrollBar()->maximum())
        {
            ui->listWidget_items->horizontalScrollBar()->setValue(ui->listWidget_items->horizontalScrollBar()->minimum());
//            ui->listWidget_items->scrollToBottom();
        }
        else
        {
            ui->listWidget_items->horizontalScrollBar()->setValue(ui->listWidget_items->item(0)->sizeHint().width()*7 + step);
        }
    });
}

void VideoSortType::setInstallEventFilter()
{

}
