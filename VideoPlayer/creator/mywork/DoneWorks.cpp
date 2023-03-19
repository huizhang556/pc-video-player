#include "DoneWorks.h"
#include "ui_DoneWorks.h"

DoneWorks::DoneWorks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoneWorks)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
}

DoneWorks::~DoneWorks()
{
    delete ui;
}

void DoneWorks::initWorkUI()
{
    //完成列表--电影
    ui->listWidget_prod_movies->setViewMode(QListView::IconMode);
    ui->listWidget_prod_movies->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_prod_movies->setResizeMode(QListWidget::Adjust);
    ui->listWidget_prod_movies->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_prod_movies->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_prod_movies->horizontalScrollBar()->setDisabled(true);
    //完成列表--网络剧
    ui->listWidget_prod_netdrama->setViewMode(QListView::IconMode);
    ui->listWidget_prod_netdrama->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_prod_netdrama->setResizeMode(QListWidget::Adjust);
    ui->listWidget_prod_netdrama->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_prod_netdrama->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_prod_netdrama->horizontalScrollBar()->setDisabled(true);
    //完成列表--短视频
    ui->listWidget_prod_shortvideos->setViewMode(QListView::IconMode);
    ui->listWidget_prod_shortvideos->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_prod_shortvideos->setResizeMode(QListWidget::Adjust);
    ui->listWidget_prod_shortvideos->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_prod_shortvideos->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_prod_shortvideos->horizontalScrollBar()->setDisabled(true);
    //完成列表--中视频
    ui->listWidget_prod_midvideos->setViewMode(QListView::IconMode);
    ui->listWidget_prod_midvideos->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_prod_midvideos->setResizeMode(QListWidget::Adjust);
    ui->listWidget_prod_midvideos->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_prod_midvideos->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_prod_midvideos->horizontalScrollBar()->setDisabled(true);
    //完成列表--音乐
    ui->listWidget_prod_musics->setViewMode(QListView::IconMode);
    ui->listWidget_prod_musics->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_prod_musics->setResizeMode(QListWidget::Adjust);
    ui->listWidget_prod_musics->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_prod_musics->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_prod_musics->horizontalScrollBar()->setDisabled(true);
    //完成列表--图片
    ui->listWidget_prod_pictures->setViewMode(QListView::IconMode);
    ui->listWidget_prod_pictures->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_prod_pictures->setResizeMode(QListWidget::Adjust);
    ui->listWidget_prod_pictures->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_prod_pictures->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_prod_pictures->horizontalScrollBar()->setDisabled(true);


    //作品列表--左侧
    for(int i = 0; i<m_producelist.count();i++)
    {
        slot_addItemToList(m_producelist.at(i),m_datalist.at(i),666);
    }
//    ui->listWidget_prod_pictures->setCurrentItem(ui->listWidget_producelist->item(0));//选中第一个
}

void DoneWorks::handleSignalsAndSlots()
{

    //接收查询到的媒体信息
    connect(dataBase::getInstance(),&dataBase::sig_sendUserDoneWorks,this,&DoneWorks::slot_receivedData_findTypeResult);

    //媒体列表
    connect(ui->listWidget_producelist,&QListWidget::currentItemChanged,[=](QListWidgetItem *current, QListWidgetItem *previous){
        if(current != nullptr)
        {
            m_curItem = current;
            qDebug()<< QString(u8"当前点击的item信息：") << current->text() << current->data(Qt::UserRole).toString();
            if(m_curItem->text() == QString(u8"电影"))
            {
                ui->stackedWidget_produce->setCurrentIndex(0);
                ui->listWidget_prod_movies->clear();
            }
            else if(m_curItem->text() == QString(u8"网络剧"))
            {
                ui->stackedWidget_produce->setCurrentIndex(1);
                ui->listWidget_prod_netdrama->clear();
            }
            else if(m_curItem->text() == QString(u8"短视频"))
            {
                ui->stackedWidget_produce->setCurrentIndex(2);
                ui->listWidget_prod_shortvideos->clear();
            }
            else if(m_curItem->text() == QString(u8"中视频"))
            {
                ui->stackedWidget_produce->setCurrentIndex(3);
                ui->listWidget_prod_midvideos->clear();
            }
            else if(m_curItem->text() == QString(u8"音乐"))
            {
                ui->stackedWidget_produce->setCurrentIndex(4);
                ui->listWidget_prod_musics->clear();
            }
            else if(m_curItem->text() == QString(u8"图片"))
            {
                ui->stackedWidget_produce->setCurrentIndex(5);
                ui->listWidget_prod_pictures->clear();
            }
            QStringList list_tags_counts = dataBase::getInstance()->creator_getAllTagsWorkCounts();
            setUserTagsWorkCounts(list_tags_counts);
            m_items = dataBase::getInstance()->creator_getdoneWorkCounts(current->data(Qt::UserRole).toString());//查询某个类型数量

            if(m_items == -1)
            {
                qDebug() <<QString(u8"数量查询失败！");
                showErrorPageMessage(ui->page_blank,QString(u8"该类型资源没找到！"));
            }
            else if(m_items == 0)
            {
                qDebug() <<QString(u8"查询暂无该类型资源！");
                showErrorPageMessage(ui->page_blank,QString(u8"暂无该类型资源！"));
            }
            else if(m_items > 0)
            {
                dataBase::getInstance()->creator_getdoneWorks(current->data(Qt::UserRole).toString());//查询具体get信息,返回查询到的信息
                qDebug() << QString(u8"找到个%1资源！").arg(m_items);
                QLabel *lab_counts = getCurrentItem(current,"label_counts");
                if(lab_counts != nullptr)
                {
                    lab_counts->setText(QString::number(m_items));//设置查询到的数量
                }
                else
                {
                    qDebug() << QString(u8"设置数量的item 没找到！");
                }

            }
        }
    });
}

void DoneWorks::slot_addItemToList(const QString text, const QVariant &data, int counts)
{
    LeftItem *itemWgt = new LeftItem(text,counts);
    QListWidgetItem *item = new QListWidgetItem(text);
    item->setData(Qt::UserRole,data);
    item->setSizeHint(QSize(200,50));
    ui->listWidget_producelist->addItem(item);//添加列表
    ui->listWidget_producelist->setItemWidget(item,itemWgt);

    //信号与槽函数
    connect(itemWgt,&LeftItem::sig_item_selected,[=](){
        ui->listWidget_producelist->setCurrentItem(item);
    });
}

void DoneWorks::slot_insertItemToList(int index, QString &text, const QVariant &data, int counts)
{
    LeftItem *itemWgt = new LeftItem(text,counts);
    QListWidgetItem *item = new QListWidgetItem(text);
    item->setData(Qt::UserRole,data);
    item->setSizeHint(QSize(200,50));
    item->setTextAlignment(Qt::AlignCenter);
    ui->listWidget_producelist->insertItem(index,item);//添加列表
    ui->listWidget_producelist->setItemWidget(item,itemWgt);

    //信号与槽函数
    connect(itemWgt,&LeftItem::sig_item_selected,[=](){
        ui->listWidget_producelist->setCurrentItem(item);
    });
}

void DoneWorks::setInstallEventer()
{
    ui->listWidget_producelist->installEventFilter(this);
}

void DoneWorks::slot_receivedData_findTypeResult(QVariant& media)
{
        fileBody body = media.value<fileBody>();//通用类型转为专用类型
        qDebug() << QString(u8"接收到数据库查询返回的信息，要被创建新的ITEM信息如下:") << endl;
        qDebug() << "fnick" << body.fnick << endl;
        qDebug() << "furl"  << body.furl << endl;
        qDebug() << "fduration" << body.fduration << endl;
        qDebug() << "fcover" << body.fcover << endl;
        qDebug() << "fmedtype" << body.fmedtype << endl;
        qDebug() << "fmedtheme" << body.fmedtheme << endl;
        qDebug() << "fsize" << body.fsize << endl;

        QListWidgetItem *item = new QListWidgetItem(body.fnick);//介绍
        item->setData(Qt::UserRole,body.furl);
        FilesItem *itemWidget = new FilesItem(FILEEDIT::CANEDIT,body.furl,body.fsize,body.fcover);
        itemWidget->initFileItem(body);
        item->setSizeHint(DITEMSIZE);
        item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
        if(body.fmedtype == QString("movies"))
        {
            ui->listWidget_prod_movies->addItem(item);
            ui->listWidget_prod_movies->setItemWidget(item,itemWidget);
        }
        else if(body.fmedtype == QString("netdrama"))
        {
            ui->listWidget_prod_netdrama->addItem(item);
            ui->listWidget_prod_netdrama->setItemWidget(item,itemWidget);
        }
        else if(body.fmedtype == QString("shortvideos"))
        {
            ui->listWidget_prod_shortvideos->addItem(item);
            ui->listWidget_prod_shortvideos->setItemWidget(item,itemWidget);
        }
        else if(body.fmedtype == QString("midvideos"))
        {
            ui->listWidget_prod_midvideos->addItem(item);
            ui->listWidget_prod_midvideos->setItemWidget(item,itemWidget);
        }
        else if(body.fmedtype == QString("musics"))
        {
            ui->listWidget_prod_musics->addItem(item);
            ui->listWidget_prod_musics->setItemWidget(item,itemWidget);
        }
        else if(body.fmedtype == QString("pictures"))
        {
            ui->listWidget_prod_pictures->addItem(item);
            ui->listWidget_prod_pictures->setItemWidget(item,itemWidget);
        }
//        checkListItemsCounts(m_curItem,m_items);//按照item数量加载情况，显示动画


        //信号与槽函数
        //移除
        connect(itemWidget,&FilesItem::sig_sendItem_remove,[=](){
            itemWidget->disconnect();
            itemWidget->deleteLater();
            item->listWidget()->takeItem(item->listWidget()->row(item));
            delete item;
        });
        //播放
        connect(itemWidget,&FilesItem::sig_sendItem_play,[=](){
        MultipPlayer::getInstance()->slot_addTempPlaylist(666,QStringList{item->data(Qt::UserRole).toString()},item->text());//url + 介绍
        });
}


bool DoneWorks::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_producelist && event->type() == QEvent::Enter)
    {
        setCursor(Qt::ArrowCursor);
    }
    return QWidget::eventFilter(watched,event);
}

QListWidget *DoneWorks::getConnectListWidget(const QString &type)
{
    if(type == QString("movies"))
    {
       return ui->listWidget_prod_movies;
    }
    else if(type == QString("netdrama"))
    {
        return ui->listWidget_prod_netdrama;
    }
    else if(type == QString("shortvideos"))
    {
        return ui->listWidget_prod_shortvideos;
    }
    else if(type == QString("midvideos"))
    {
        return ui->listWidget_prod_midvideos;
    }
    else if(type == QString("musics"))
    {
        return ui->listWidget_prod_musics;
    }
    else if(type == QString("pictures"))
    {
        return ui->listWidget_prod_pictures;
    }
}

void DoneWorks::checkListItemsCounts(QListWidgetItem *item, int allcounts)
{
    //查找对应类型对应的listwidget
    if(getConnectListWidget(item->data(Qt::UserRole).toString())->count() != allcounts)//还未加载够
    {
//        getProgresslable(item,"label_status")->startRun();
//        qDebug() << QString(u8"已经开始等待加载动画。。。");
    }
    else//加载够了
    {
        getProgresslable(item,"label_status")->stopRun();
        qDebug() << QString(u8"已经结束等待加载动画。。。");
    }
}

QLabel *DoneWorks::getCurrentItem(QListWidgetItem *item, const QString& objname)
{
    QWidget* itemWidget = ui->listWidget_producelist->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QLabel*lab_counts = itemWidget->findChild<QLabel*>(objname);//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != lab_counts)
        {
            qDebug() <<QString(u8"lab_counts");
            return lab_counts;
        }
    }
    else
    {
        qDebug() <<QString(u8"没找到LeftItem");
        return nullptr;
    }
}

LabLoading *DoneWorks::getProgresslable(QListWidgetItem *item, const QString &objname)
{
    QWidget* itemWidget = ui->listWidget_producelist->itemWidget(item);
    if(nullptr != itemWidget)
    {
        LabLoading*lab_counts = itemWidget->findChild<LabLoading*>(objname);//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != lab_counts)
        {
            qDebug() <<QString(u8"LabLoading 找到！");
            return lab_counts;
        }
    }
    else
    {
        qDebug() <<QString(u8"没找到LabLoading");
        return nullptr;
    }
}

void DoneWorks::showErrorPageMessage(QWidget *page, const QString &message)
{
    ui->stackedWidget_produce->setCurrentWidget(page);
    ui->pushButton_error->setText(message);
}

void DoneWorks::setUserTagsWorkCounts(QStringList &list_counts)
{
    for(int i = 0; i < list_counts.count(); i++)
    {
        QLabel *lab_counts = getCurrentItem(ui->listWidget_producelist->item(i),"label_counts");
        if(lab_counts != nullptr)
        {
            lab_counts->setText(list_counts.at(i));//设置查询到的数量
        }
        else
        {
            qDebug() << QString(u8"设置数量的item 没找到！");
        }
    }
}
