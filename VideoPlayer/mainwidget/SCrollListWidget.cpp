#include "SCrollListWidget.h"
#include "ui_SCrollListWidget.h"

SCrollListWidget::SCrollListWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::SCrollListWidget)
{
    ui->setupUi(this);
//    setMinimumSize(666,80);
//    setFixedSize(666,80);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();

}

SCrollListWidget::~SCrollListWidget()
{
    delete ui;
}

void SCrollListWidget::initWorkUI()
{
    ui->pushButton_left->setFixedSize(30,30);
    ui->pushButton_right->setFixedSize(30,30);

    ui->listWidget_walls->setWrapping(false);
    ui->listWidget_walls->setMouseTracking(true);
    ui->listWidget_walls->setMovement(QListView::Static);
    ui->listWidget_walls->setFrameShape(QFrame::NoFrame);
    ui->listWidget_walls->setViewMode(QListView::IconMode);

    ui->listWidget_walls->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_walls->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_walls->horizontalScrollBar()->setDisabled(true);
    ui->listWidget_walls->setHorizontalScrollMode(QAbstractItemView::ScrollPerItem);
    ui->listWidget_walls->setAutoScroll(false);
}

void SCrollListWidget::handleSignalsAndSlots()
{
//    connect(ui->listWidget_walls,&QListWidget::itemEntered,[=](QListWidgetItem *curitem){
//        if(curitem == nullptr) return;
//        int index = ui->listWidget_walls->row(curitem);
//        ui->listWidget_walls->setCurrentItem(curitem);
//        emit sig_sendCurIndex(index);
//        qDebug() <<QString(u8"当前选中的索引：%1").arg(index);
//    });

    connect(ui->listWidget_walls,&QListWidget::currentItemChanged,[=](QListWidgetItem *current, QListWidgetItem *previous){
        if(current != nullptr)
        {
            getMaskWidget(current,"widget_mask")->setStyleSheet("#widget_mask{"
                                                                "background-color: transparent;"
                                                                "}");
//            qDebug() <<QString(u8"当前已经设置样式！");
        }
        if(previous != nullptr)
        {
            getMaskWidget(previous,"widget_mask")->setStyleSheet("#widget_mask{"
                                                                "background-color: rgba(20, 20, 20,0.6);"
                                                                "}");
//            qDebug() <<QString(u8"上一个已经设置样式！");
        }
    });

    connect(ui->pushButton_left,&QPushButton::clicked,[=](){
//        if(ui->listWidget_walls->horizontalScrollBar()->value() == ui->listWidget_walls->horizontalScrollBar()->minimum()) return;

        int step = ui->listWidget_walls->horizontalScrollBar()->value();
        QPropertyAnimation *pAnimation = new QPropertyAnimation(ui->listWidget_walls->horizontalScrollBar(),"value",this);
        pAnimation->setDuration(500);
        pAnimation->setStartValue(step);
        pAnimation->setEndValue(step - ui->listWidget_walls->item(0)->sizeHint().width());
        pAnimation->start();
        connect(pAnimation,&QPropertyAnimation::finished,[=](){
        pAnimation->deleteLater();
        });
//            ui->listWidget_walls->horizontalScrollBar()->setValue(step - ui->listWidget_walls->item(0)->sizeHint().width());
//            qDebug() <<QString(u8"左按钮");
    });

    connect(ui->pushButton_right,&QPushButton::clicked,[=](){
//        if(ui->listWidget_walls->horizontalScrollBar()->value() == ui->listWidget_walls->horizontalScrollBar()->maximum()) return;

        int step = ui->listWidget_walls->horizontalScrollBar()->value();
        QPropertyAnimation *pAnimation = new QPropertyAnimation(ui->listWidget_walls->horizontalScrollBar(),"value",this);
        pAnimation->setDuration(500);
        pAnimation->setStartValue(step);
        pAnimation->setEndValue(step + ui->listWidget_walls->item(0)->sizeHint().width());
        pAnimation->start();
        connect(pAnimation,&QPropertyAnimation::finished,[=](){
        pAnimation->deleteLater();
        });
//            ui->listWidget_walls->horizontalScrollBar()->setValue(step + ui->listWidget_walls->item(0)->sizeHint().width());
//            qDebug() <<QString(u8"右按钮");
    });
}

void SCrollListWidget::setInstallEventFilter()
{
    ui->listWidget_walls->installEventFilter(this);
}

void SCrollListWidget::slot_addItemToList(const QString &picpath)
{
    //添加图片(路径+背景色+radius+是否收藏)
    CusLabel1 *label_pic = new CusLabel1(picpath,QColor(64, 66, 68),6,true);//此处需用指针，临时对象不行
//    label_pic->setPixmap(QPixmap(picpath).scaled(QSize(135,80)));
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(ITEMWIDTH,65));//高度一致，宽度留出spacing
    ui->listWidget_walls->addItem(item);//item要比图片大，包含边界
    ui->listWidget_walls->setItemWidget(item,label_pic);
    //信号与槽函数
    connect(label_pic,&CusLabel1::sig_item_enter,[=](){
       ui->listWidget_walls->setCurrentItem(item);
       int index = ui->listWidget_walls->currentRow();
       emit sig_sendCurIndex(index);//外部发送当前索引
       qDebug() <<QString(u8"当前选中的索引：%1").arg(index);
    });
}

void SCrollListWidget::slot_addItemsToList(const QStringList& list_pic)
{
    for(int i = 0; i < list_pic.count(); ++i)
    {
        slot_addItemToList(list_pic.at(i));
    }
}

//由外部主轮播图大小的改变带动小轮播图的大小改变
void SCrollListWidget::slot_update_RL_ITEM_geometry(const QSize& size)
{
    this->setFixedSize(size.width()*ITEMSACLE + ui->listWidget_walls->count()*6,80);//外部轮播图的大小乘以缩放比例
    setButtons_LR_Geometry();//更新左右箭头位置
    autoResizeListItems();//调整item大小
}

void SCrollListWidget::slot_setCurrentItem(int index)
{
    if(index >= ui->listWidget_walls->count()) return;
    QListWidgetItem *citem = ui->listWidget_walls->item(index);
    if(citem != nullptr)
    ui->listWidget_walls->setCurrentItem(citem);
}

bool SCrollListWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_walls)
    {
        if(event->type() == QEvent::Resize)
        {
//           autoResizeListItems();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void SCrollListWidget::autoResizeListItems()
{
    if(ui->listWidget_walls->count() == 0) return;
    if(ui->listWidget_walls->count() > 0)
    {
        int avgWidth = calAvgWidth();
        if(avgWidth < ITEMWIDTH)
        {
             avgWidth = ITEMWIDTH;
        }

        for(int i = 0; i < ui->listWidget_walls->count(); i++)
        {
            ui->listWidget_walls->item(i)->setSizeHint(QSize(avgWidth,65));
        }
    }
        ui->listWidget_walls->horizontalScrollBar()->setValue(0);
//    qDebug() << QString(u8"item更新了位置");
}

void SCrollListWidget::setButtons_LR_Geometry()
{
    ui->pushButton_left->move(this->contentsMargins().left(),this->height()/2 - ui->pushButton_left->height()/2 - 5);
    ui->pushButton_right->move(this->width() - this->contentsMargins().right() - ui->pushButton_right->width(),
                               this->height()/2 - ui->pushButton_left->height()/2 - 5);
//    qDebug() <<QString(u8"左右按钮更新了位置！");
}

int SCrollListWidget::calAvgWidth()
{
    int Width = (int)(ui->listWidget_walls->width() - ui->listWidget_walls->verticalScrollBar()->width()-1);
    int sizeHint_w = ITEMWIDTH;

    int avgWidth = 0;
    if(Width < sizeHint_w*3)//小于3个默认宽度，默认按2个宽度拉升
    {
        avgWidth = (int)(Width/3);
    }
    else if(Width < sizeHint_w*4)
    {
        avgWidth = (int)(Width/4);
    }
    else if(Width < sizeHint_w*5)
    {
        avgWidth = (int)(Width/5);
    }
    else if(Width < sizeHint_w*6)
    {
        avgWidth = (int)(Width/6);
    }
    else if(Width < sizeHint_w*7)
    {
        avgWidth = (int)(Width/7);
    }
    else if(Width < sizeHint_w*8)
    {
        avgWidth = (int)(Width/8);
    }
    else
    {
        avgWidth = sizeHint_w;
    }
    return avgWidth;
}

//查找mask_widget
QWidget *SCrollListWidget::getMaskWidget(QListWidgetItem* item, const QString& objname)
{
    QWidget* itemWidget = item->listWidget()->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QWidget *itemMask = itemWidget->findChild<QWidget*>(objname);//查找指定名称的按钮
        if(nullptr != itemMask)
        {
//            qDebug() << QString(u8"找到了CusLabel");
            return itemMask;
        }
    }
}
