#include "Container01.h"
#include "ui_Container01.h"
#include "global/Global.h"
#include "mainwidget/subunititems/SubModules.h"

Container01::Container01(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Container01)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

Container01::Container01( const QString &titleText, const QString &leftPicPath, QWidget *parent):
    QWidget(parent),
    ui(new Ui::Container01)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    if(!titleText.isEmpty())
        ui->pushButton_title->setText(titleText);
    if(!leftPicPath.isEmpty())
    {
     ui->label_leftpic->setPixmap(QPixmap(leftPicPath));
     ui->label_leftpic->setScaledContents(true);
    }
}

Container01::~Container01()
{
    delete ui;
}

void Container01::initWorkUI()
{
    ui->listWidget_container01->setViewMode(QListView::IconMode);
    ui->listWidget_container01->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_container01->setResizeMode(QListWidget::Adjust);
    ui->listWidget_container01->setWrapping(false);//自动换行 所有itm在一行显示
    ui->listWidget_container01->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_container01->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_container01->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_container01->horizontalScrollBar()->setDisabled(true);//禁用横向滚动条


    ui->listWidget_container02->setViewMode(QListView::IconMode);
    ui->listWidget_container02->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_container02->setResizeMode(QListWidget::Adjust);
    ui->listWidget_container02->setWrapping(false);//自动换行 所有itm在一行显示
    ui->listWidget_container02->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_container02->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_container02->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_container02->horizontalScrollBar()->setDisabled(true);//禁用横向滚动条

    for(int i = 0; i < 10; i++)
    {
        QString path1 = QString(Global::appDirPath +"/pictures/musics/recommend2/music%1.png").arg(i);
        QString path2 = QString(Global::appDirPath +"/pictures/musics/recommend2/music%1.png").arg(11+i);
        slot_addItemToListWidget_top("www.hao123.com",path1,QString(u8"《只对你有感觉》--对唱%1").arg(i+1),QString(u8"《山河图》%1").arg(i+1));
        slot_addItemToListWidget_bottom("www.baidu.com",path2,QString(u8"这才是国漫配乐%1").arg(i+11),QString(u8"一首唢呐火遍全网%1").arg(i+11));
    }

}

void Container01::handleSignalsAndSlots()
{
    connect(ui->pushButton_left,&QPushButton::clicked,[=](){
        int step1 = ui->listWidget_container01->horizontalScrollBar()->value();
        ui->listWidget_container01->horizontalScrollBar()->setValue(step1 - ui->listWidget_container01->item(0)->sizeHint().width());

        int step2 = ui->listWidget_container02->horizontalScrollBar()->value();
        ui->listWidget_container02->horizontalScrollBar()->setValue(step2 - ui->listWidget_container02->item(0)->sizeHint().width());
    });

    connect(ui->pushButton_right,&QPushButton::clicked,[=](){
        int step1 = ui->listWidget_container01->horizontalScrollBar()->value();
        ui->listWidget_container01->horizontalScrollBar()->setValue(step1 + ui->listWidget_container01->item(0)->sizeHint().width());

        int step2 = ui->listWidget_container02->horizontalScrollBar()->value();
        ui->listWidget_container02->horizontalScrollBar()->setValue(step2 + ui->listWidget_container02->item(0)->sizeHint().width());
    });
}

void Container01::slot_addItemToListWidget_top(const QString &url, const QString &picpath, const QString &info1, const QString &info2)
{
    SubModules *itemWidget1 = new SubModules(picpath,info1,info2);
    QListWidgetItem *item1 = new QListWidgetItem(url);
    item1->setSizeHint(itemWidget1->size());
    ui->listWidget_container01->addItem(item1);
    ui->listWidget_container01->setItemWidget(item1,itemWidget1);

}

void Container01::slot_addItemToListWidget_bottom(const QString &url, const QString &picpath, const QString &info1, const QString &info2)
{
    SubModules *itemWidget2 = new SubModules(picpath,info1,info2);
    QListWidgetItem *item2 = new QListWidgetItem(url);
    item2->setSizeHint(itemWidget2->size());
    ui->listWidget_container02->addItem(item2);
    ui->listWidget_container02->setItemWidget(item2,itemWidget2);
}
