#include "MultipType.h"
#include "ui_MultipType.h"
#include "global/Global.h"
#include "mainwidget/videosmv/VideoItem.h"
#include <QListWidgetItem>
#include <QScrollBar>
#include <QDebug>

MvType::MvType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MvType)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

MvType::MvType(const QString &title, const QString &leftpic, const QString &info1, const QString &info2, QWidget *parent):
    QWidget(parent),
    m_title(title),
    m_leftpic(leftpic),
    m_info1(info1),
    m_info2(info2),
    ui(new Ui::MvType)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    setItemTitle();
    setItemLeftPicture();
    setItemInfo1();
    setItemInfo2();
}

MvType::~MvType()
{
    delete ui;
}

void MvType::initWorkUI()
{
    ui->listWidget_list->setViewMode(QListView::IconMode);
    ui->listWidget_list->setMovement(QListView::Static);
    ui->listWidget_list->setResizeMode(QListView::Adjust);
//    ui->listWidget_list->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_list->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_list->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    for(int i = 0; i < 6; i++)
    {
        QString picpath = QString("://images/videosmv/reclist/music%1.png").arg(i);
        QString introduce = QString(u8"《烟火里的中国》--%1").arg(i+1);
        QString author = QString(u8"王莉and胡夏and群星--%1").arg(i+1);
        VideoItem *itemWidget = new VideoItem(picpath,introduce,author);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size());

        ui->listWidget_list->addItem(item);
        ui->listWidget_list->setItemWidget(item,itemWidget);
    }
}

void MvType::handleSignalsAndSlots()
{

}

void MvType::setInstallEventFilter()
{
    ui->listWidget_list->installEventFilter(this);
}

bool MvType::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_list)
    {
        if(event->type() == QEvent::Resize)
        {
            resizeListWidgetItemSize();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void MvType::resizeListWidgetItemSize()
{
    int width = ui->listWidget_list->width();
    int fitWidth = (width - ui->listWidget_list->verticalScrollBar()->width() +99)/3;
    if(fitWidth < 300)
    {
        int Width_4 = (width - ui->listWidget_list->verticalScrollBar()->width() +99)/2;
        for(int i = 0; i< ui->listWidget_list->count(); i++)
        {
            ui->listWidget_list->item(i)->setSizeHint(QSize(Width_4,(Width_4)*SCALE));
        }
    }
    else
    {
        for(int i = 0; i< ui->listWidget_list->count(); i++)
        {
            ui->listWidget_list->item(i)->setSizeHint(QSize(fitWidth,(fitWidth)*SCALE));
        }
    }
}

void MvType::setItemTitle()
{
    ui->pushButton_title->setText(m_title);
}

void MvType::setItemLeftPicture()
{
//    ui->label_picMv->setPixmap(QPixmap(m_leftpic));
//    ui->label_picMv->setScaledContents(true);
    ui->label_picMv->setItemPicture(m_leftpic);
}

void MvType::setItemInfo1()
{
    ui->pushButton_bigName->setText(m_info1);
}

void MvType::setItemInfo2()
{
    ui->pushButton_bigAuthor->setText(m_info2);
}
