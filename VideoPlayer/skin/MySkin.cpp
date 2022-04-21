#include "MySkin.h"
#include "ui_MySkin.h"
#include <QListWidgetItem>

MySkin::MySkin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MySkin)
{
    ui->setupUi(this);
    installEventFilter(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);//自动消失 Popup
    this->setFixedSize(345,235);
    initWorkUI();
    chandleSignalAndSlot();
}

MySkin::~MySkin()
{
    delete ui;
}

void MySkin::initWorkUI()
{
    ui->tabWidget->setCurrentIndex(0);//显示第一个项目
    ui->listWidget_zhuti->setViewMode(QListView::IconMode);//显示模式 图标模式
    ui->listWidget_zhuti->setMovement(QListView::Static);//图标不可拖动
//    ui->listWidget_zhuti->setIconSize(QSize(110,100));//icon 大小
//    ui->listWidget_zhuti->setGridSize( QSize(110, 100));//网格大小
//    ui->listWidget_zhuti->setResizeMode(QListWidget::Adjust);//图标的调整模式，默认是固定的
    ui->listWidget_zhuti->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_zhuti->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->listWidget_yuzhi->setViewMode(QListView::IconMode);//显示模式 图标模式
    ui->listWidget_yuzhi->setMovement(QListView::Static);//图标不可拖动
//    ui->listWidget_yuzhi->setIconSize(QSize(110,100));//icon 大小
//    ui->listWidget_yuzhi->setGridSize( QSize(320, 180));//网格大小
//    ui->listWidget_yuzhi->setResizeMode(QListWidget::Adjust);//图标的调整模式，默认是固定的
    ui->listWidget_yuzhi->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_yuzhi->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    ui->listWidget_custom->setViewMode(QListView::IconMode);//显示模式 图标模式
    ui->listWidget_custom->setMovement(QListView::Static);//图标不可拖动
//    ui->listWidget_custom->setIconSize(QSize(110,100));//icon 大小
//    ui->listWidget_custom->setGridSize( QSize(320, 180));//网格大小
//    ui->listWidget_custom->setResizeMode(QListWidget::Adjust);//图标的调整模式，默认是固定的
    ui->listWidget_custom->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_custom->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0; i < 5; i++)
    {
        MySkinItem *skitem = new MySkinItem(110,100,20,20,0,this);
        skitem->setSkinPicture(QString::fromLocal8Bit(":/images/skin/title%1.jpg").arg(i+1));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(110,100));//两列 宽110*3  高100*2
        ui->listWidget_zhuti->addItem(item);
        ui->listWidget_zhuti->setItemWidget(item,skitem);
    }

    for(int i = 0; i < 5; i++)
    {
        MySkinItem *skitem = new MySkinItem(110,100,20,20,0,this);
        skitem->setSkinPicture(QString::fromLocal8Bit(":/images/skin/title%1.jpg").arg(i+1));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(110,100));
        ui->listWidget_yuzhi->addItem(item);
        ui->listWidget_yuzhi->setItemWidget(item,skitem);
    }

    for(int i = 0; i < 5; i++)
    {
        MySkinItem *skitem = new MySkinItem(110,100,20,20,0,this);
        skitem->setSkinPicture(QString::fromLocal8Bit(":/images/skin/title%1.jpg").arg(i+1));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(110,100));
        ui->listWidget_custom->addItem(item);
        ui->listWidget_custom->setItemWidget(item,skitem);
    }
}

void MySkin::chandleSignalAndSlot()
{

}


bool MySkin::eventFilter(QObject *watch, QEvent *event)
{
    if(watch ==  this)
    {
        if(event->type() == QEvent::Leave)
        {
            this->close();
        }
    }


    return QDialog::eventFilter(watch,event);
}
