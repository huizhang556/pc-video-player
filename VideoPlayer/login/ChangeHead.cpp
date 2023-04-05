#include "ChangeHead.h"
#include "ui_ChangeHead.h"
//类外初始化
ChangeHead* ChangeHead::m_pInstance = nullptr;

ChangeHead::ChangeHead(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::ChangeHead)
{
    ui->setupUi(this);
    setTitleBarMoveArea(ui->frame_title,2);
    setFixedSize(330,520);
    initWorkUI();
    handleSignalsAndSlots();
}

ChangeHead::~ChangeHead()
{
    delete ui;
    //删除创建的单例
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

ChangeHead *ChangeHead::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new ChangeHead();
    }
    return m_pInstance;
}

void ChangeHead::exec_(OPENTYPE type)
{
    ui->listWidget_hispix->clear();
    ui->listWidget_manpix->clear();
    ui->listWidget_womanpix->clear();
    ui->listWidget_gifpix->clear();

    dataBase::getInstance()->header_initHeader();
    QPixmap pix_user = dataBase::getInstance()->getCurrentUserHeadPix();
    if(!pix_user.isNull())
    {
        slot_setCurViewHeader(pix_user);
    }

    switch (type)
    {
    case OPENTYPE::PER_INFO:
    {
       ui->tabWidget_change->setCurrentIndex(0);
    }
        break;
    case OPENTYPE::PER_HEAD:
    {
       ui->tabWidget_change->setCurrentIndex(1);
    }
        break;
    case OPENTYPE::GENERAL:
    {
       ui->tabWidget_change->setCurrentIndex(2);
    }
        break;
    default:
        break;
    }

    this->exec();
}

void ChangeHead::initWorkUI()
{
    ui->pushButton_add->setToolTip(QString(u8"放大"));
    ui->pushButton_sub->setToolTip(QString(u8"缩小"));
    ui->pushButton_roate_L->setToolTip(QString(u8"左旋90°"));
    ui->pushButton_roate_R->setToolTip(QString(u8"右旋90°"));
    ui->pushButton_cutpix->setToolTip(QString(u8"剪裁"));
    ui->comboBox_type->setView(new QListView());
    ui->comboBox_type->hide();

    ui->pushButton_localpix->setIcon(QIcon("://images/user/user_loadheader.png"));
    ui->pushButton_localpix->setIconSize(QSize(17,17));
    ui->pushButton_localpix->setLayoutDirection(Qt::RightToLeft);

    ui->listWidget_hispix->setViewMode(QListView::IconMode);
    ui->listWidget_hispix->setWrapping(false);
    ui->listWidget_hispix->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_hispix->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_manpix->setViewMode(QListView::IconMode);
    ui->listWidget_manpix->setWrapping(false);
    ui->listWidget_manpix->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_manpix->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_womanpix->setViewMode(QListView::IconMode);
    ui->listWidget_womanpix->setWrapping(false);
    ui->listWidget_womanpix->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_womanpix->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_gifpix->setViewMode(QListView::IconMode);
    ui->listWidget_gifpix->setWrapping(false);
    ui->listWidget_gifpix->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_gifpix->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->horizontalSlider->setEnabled(false);//禁止鼠标拖动
    ui->horizontalSlider->setRange(0,100);
    ui->horizontalSlider->setValue(0);
    ui->horizontalSlider->setSingleStep(10);
    ui->horizontalSlider->setTickInterval(10);
    ui->horizontalSlider->setTickPosition(QSlider::TicksAbove);
    ui->tabWidget_change->setCurrentWidget(ui->tab_change);
    m_scence = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scence);

//    m_scence->setForegroundBrush(QColor(19, 26, 35,100));//前景层颜色
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->horizontalScrollBar()->setEnabled(false);
    ui->graphicsView->verticalScrollBar()->setEnabled(false);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);//拖动时鼠标为手型
}

void ChangeHead::handleSignalsAndSlots()
{
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){this->close();});
    connect(ui->pushButton_min,&QPushButton::clicked,[=](){this->showMinimized();});

    //打开本地文件
    connect(ui->pushButton_localpix,&QPushButton::clicked,[=](){
        m_curPixPath = QFileDialog::getOpenFileName(this,//不指定父窗口，设置自己的样式
                                                    QString::fromLocal8Bit("选择文件"),
                                                    QApplication::applicationDirPath(),
                                                    QString(u8"*.png *.jpg *.jpeg *.bmp")
                                                    );
        if(!m_curPixPath.isEmpty())
        {
           slot_setCurViewHeader(m_curPixPath);
        }
    });

    //使用推荐头像
    connect(ui->pushButton_recpix,&QPushButton::clicked,[=](){
        ui->tabWidget_change->setCurrentWidget(ui->tab_general);
    });

    //头像--向左旋转
    connect(ui->pushButton_roate_L,&QPushButton::clicked,[=](){
        if(m_pixItem == nullptr)
            {
            setOperateTip(QString(u8"请添加图片资源！"),1500);
            return;
        }

        ui->graphicsView->rotate(-90);
        m_viewRotate -= 90;
    });

    //头像--向右旋转
    connect(ui->pushButton_roate_R,&QPushButton::clicked,[=](){
        if(m_pixItem == nullptr)
            {
            setOperateTip(QString(u8"请添加图片资源！"),1500);
            return;
        }
        ui->graphicsView->rotate(90);
        m_viewRotate += 90;
    });

    //头像--缩小
    connect(ui->pushButton_sub,&QPushButton::clicked,[=](){
        if(m_pixItem == nullptr)
            {
            setOperateTip(QString(u8"请添加图片资源！"),1500);
            return;
        }
        if(ui->horizontalSlider->value() == 0) return;
        ui->graphicsView->scale(0.93,0.93);
        ui->horizontalSlider->setValue(ui->horizontalSlider->value()-10);
    });

    //头像--放大
    connect(ui->pushButton_add,&QPushButton::clicked,[=](){
        if(m_pixItem == nullptr)
            {
            setOperateTip(QString(u8"请添加图片资源！"),1500);
            return;
        }
        if(ui->horizontalSlider->value() == 100) return;
        ui->graphicsView->scale(1.075,1.075);
        ui->horizontalSlider->setValue(ui->horizontalSlider->value()+10);
    });

    //操作--取消
    connect(ui->pushButton_cancel,&QPushButton::clicked,[=](){
        this->close();
    });

    //操作--确定
    connect(ui->pushButton_ok,&QPushButton::clicked,[=](){
        if(m_pixItem == nullptr)
            {
            setOperateTip(QString(u8"请添加图片资源！"),1500);
            return;
        }

        QPixmap pixmap = ui->graphicsView->grab();
        QByteArray bytes;
        QBuffer buffer(&bytes);//此句等同于：bytes.append(buffer.data());
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG");
        buffer.close();
        bool isOK = uplaodUserCurHeader(bytes);
        if(isOK)
        setOperateTip(QString(u8"恭喜您，头像设置成功^_^"),1500);

    });

    //操作--剪裁
    connect(ui->pushButton_cutpix,&QPushButton::clicked,[=](){
        if(m_pixItem == nullptr)
            {
            setOperateTip(QString(u8"请添加图片资源！"),1500);
            return;
        }
        QPixmap pixmap = ui->graphicsView->grab();
        HeadLabel *itemWidget = new HeadLabel(pixmap,true,true);
        QListWidgetItem* item = new QListWidgetItem();
        item->setSizeHint(QSize(70,70));
        item->setData(Qt::UserRole,QDateTime::currentDateTime().toString("yyyy-MM-dd"));
        ui->listWidget_hispix->addItem(item);
        ui->listWidget_hispix->setItemWidget(item,itemWidget);

        //信号与槽函数
        connect(itemWidget,&HeadLabel::sig_item_delete,[=](){
            itemWidget->deleteLater();
            ui->listWidget_hispix->takeItem(ui->listWidget_hispix->row(item));
            delete item;
        });


        connect(itemWidget,&HeadLabel::sig_item_pix,[=](QPixmap& pixmap){
            slot_setCurViewHeader(pixmap);
            ui->listWidget_hispix->setCurrentItem(item);
        });

        ui->listWidget_hispix->scrollToItem(item);//默认滚动到可见区域       
    });


    connect(ui->horizontalSlider,&QSlider::valueChanged,[=](int value){
//        qDebug() << QString(u8"当前进度条值:%1").arg(value);
    });

    //历史item改变
    connect(ui->listWidget_hispix,&QListWidget::currentItemChanged,[=](QListWidgetItem *current, QListWidgetItem *previous){
        if(current != nullptr)
        {
            QPushButton* delBtn = getDeleteButton(current,"pushButton_checked");
            if(delBtn != nullptr)
            {
                delBtn->setProperty("selected",true);
                delBtn->style()->polish(delBtn);
            }
        }
        if(previous != nullptr)
        {
            QPushButton* delBtn = getDeleteButton(previous,"pushButton_checked");
            if(delBtn != nullptr)
            {
                delBtn->setProperty("selected",false);
                delBtn->style()->polish(delBtn);
            }
        }
    });

    //响应数据库返回数据
    //历史头像
    connect(dataBase::getInstance(),&dataBase::sig_header_history,this,&ChangeHead::slot_addHeader_history);

    //通用男头像
    connect(dataBase::getInstance(),&dataBase::sig_header_man,this,&ChangeHead::slot_addHeader_man);

    //通用女头像
    connect(dataBase::getInstance(),&dataBase::sig_header_woman,this,&ChangeHead::slot_addHeader_woman);

    //通用动态头像
    connect(dataBase::getInstance(),&dataBase::sig_header_gif,this,&ChangeHead::slot_addHeader_gif);
}

void ChangeHead::slot_setCurViewHeader(const QString &pixmap)
{
    QPixmap pix(pixmap);
    slot_setCurViewHeader(pix);
}

void ChangeHead::slot_setCurViewHeader(QPixmap pixmap)
{
//    qDebug() << QString(u8"显示的图像信息：") << pixmap.size();
//    qDebug() <<QString(u8"当前VIEW大小：") << ui->graphicsView->size();
    if(m_pixItem != nullptr)
    {
        delete m_pixItem;
    }
    resetRotate();
    ui->horizontalSlider->setValue(0);//因为是新的item，所以又回到初始角度
    ui->graphicsView->resetTransform();//先恢复缩放比例
    m_pixItem = m_scence->addPixmap(pixmap.scaled(ui->graphicsView->size(),Qt::KeepAspectRatio,Qt::FastTransformation));
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    //QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable
//            m_pixItem->setFlags(QGraphicsItem::ItemIsSelectable);
//    m_scence->setForegroundBrush(QColor(19, 26, 35,100));//前景层颜色
}

//添加历史头像
void ChangeHead::slot_addHeader_history(const QString &pixid,const QString &headers)
{
    HeadLabel *itemWidget = new HeadLabel(headers,true,true);
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(70,70));
    item->setData(Qt::UserRole,pixid);
    ui->listWidget_hispix->addItem(item);
    ui->listWidget_hispix->setItemWidget(item,itemWidget);

    //信号与槽函数
    connect(itemWidget,&HeadLabel::sig_item_delete,[=](){
        itemWidget->deleteLater();
        qDebug() << QString(u8"item图片ID：") << item->data(Qt::UserRole).toString();
        //数据库进行删除(目前只假移除，数据库不删除)
//        bool isOK =  dataBase::getInstance()->header_deleteUserHisHeader(dataBase::getInstance()->getCurrentUserID(),item->data(Qt::UserRole).toString());
//        if(isOK)
//        {
            ui->listWidget_hispix->takeItem(ui->listWidget_hispix->row(item));
            delete item;
//        }
    });


    connect(itemWidget,&HeadLabel::sig_item_pix,[=](QPixmap& pixmap){
        slot_setCurViewHeader(pixmap);
        ui->listWidget_hispix->setCurrentItem(item);
    });
}

//添加通用男头像
void ChangeHead::slot_addHeader_man(const QString &headers)
{
    HeadLabel *itemWidget = new HeadLabel(headers,false,false);
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(70,70));
    item->setData(Qt::UserRole,headers);
    ui->listWidget_manpix->addItem(item);
    ui->listWidget_manpix->setItemWidget(item,itemWidget);

    //信号与槽函数
    connect(itemWidget,&HeadLabel::sig_item_pix,[=](QPixmap& pixmap){
        slot_setCurViewHeader(pixmap);
        ui->listWidget_manpix->setCurrentItem(item);
    });
}

//添加通用女头像
void ChangeHead::slot_addHeader_woman(const QString &headers)
{
    HeadLabel *itemWidget = new HeadLabel(headers,false,false);
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(70,70));
    item->setData(Qt::UserRole,headers);
    ui->listWidget_womanpix->addItem(item);
    ui->listWidget_womanpix->setItemWidget(item,itemWidget);

    //信号与槽函数
    connect(itemWidget,&HeadLabel::sig_item_pix,[=](QPixmap& pixmap){
        slot_setCurViewHeader(pixmap);
        ui->listWidget_womanpix->setCurrentItem(item);
    });
}

//添加通用动态头像
void ChangeHead::slot_addHeader_gif(const QString &headers)
{
    HeadLabel *itemWidget = new HeadLabel(headers,false,false);
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(70,70));
    item->setData(Qt::UserRole,headers);
    ui->listWidget_gifpix->addItem(item);
    ui->listWidget_gifpix->setItemWidget(item,itemWidget);


    //信号与槽函数
    connect(itemWidget,&HeadLabel::sig_item_pix,[=](QPixmap& pixmap){
        slot_setCurViewHeader(pixmap);
        ui->listWidget_gifpix->setCurrentItem(item);
        setOperateTip(QString(u8"动态头像不支持剪裁!"),5000);
    });
}

void ChangeHead::slot_inserHeadToDB(bool success, QString url, QString md5)
{
    if(!success)//不成功
    {
        setOperateTip(QString(u8"返回数有误！"),1500);
        return;
    }
    bool  isOK = dataBase::getInstance()->header_inserUsrHeaderToDB(url,"custom");
    if(isOK)
    {
        setOperateTip(QString(u8"头像上传成功！"),1500);
    }
    else
    {
        setOperateTip(QString(u8"头像上传失败！"),1500);
    }
}

//重写滚轮事件
void ChangeHead::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
    {
//        ui->pushButton_add->click();
    }
    else
    {
//        ui->pushButton_sub->click();
    }
}

void ChangeHead::resetRotate()
{
    if(m_viewRotate != 0)//场景进行了旋转
    {
        qreal rotate_adj = (m_viewRotate > 0)?(360 - m_viewRotate):(-m_viewRotate);
        ui->graphicsView->rotate(rotate_adj);//要继续旋转恢复到0度时的场景
        m_viewRotate = 0;
    }
}

void ChangeHead::setOperateTip(const QString &tip, const int duration)
{
    ui->pushButton_tips->setText(tip);
    QTimer::singleShot(duration,0,[=](){
        ui->pushButton_tips->setText("");
    });
}

QPushButton *ChangeHead::getDeleteButton(QListWidgetItem *item, const QString &objName)
{
    QWidget *itemWidget = ui->listWidget_hispix->itemWidget(item);
    if(itemWidget != nullptr)
    {
        QPushButton* delBtn = itemWidget->findChild<QPushButton*>(objName);
        if(delBtn != nullptr)
        {
            return delBtn;
        }
        else
        {
            return nullptr;
        }
    }
    return nullptr;
}

bool ChangeHead::uplaodUserCurHeader(const QByteArray &pic_bytedata)
{
    if(pic_bytedata.isNull() || pic_bytedata.isEmpty())
    {
        setOperateTip(QString(u8"图像资源为空！"),1500);
        return false;
    }
    //创建工作对象
    UploadWork* upWorker = new UploadWork();
    //创建线程
    QThread *workThread = new QThread();
    //工作对象移动到线程中
    upWorker->moveToThread(workThread);
    //开启线程
    workThread->start();//开启线程
    //工作线程开始上传
    upWorker->slot_receiveData_accept(pic_bytedata,"user_header");//图片数据 + 自定义路径
    //信号与槽函数
    connect(workThread,&QThread::finished,upWorker,&QObject::deleteLater);//线程结束时，工作对象自动删除
    connect(workThread,&QThread::finished,workThread,&QThread::deleteLater);//线程结束时，线程内对象自动删除
    //上传完成--传回信息,插入数据库
    connect(upWorker,&UploadWork::sig_work_finished,this,&ChangeHead::slot_inserHeadToDB);

}

