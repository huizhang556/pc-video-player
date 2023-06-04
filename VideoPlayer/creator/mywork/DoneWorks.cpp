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
    //专辑展示列表
    ui->listWidget_albumitems->setViewMode(QListView::IconMode);
    ui->listWidget_albumitems->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_albumitems->setResizeMode(QListWidget::Adjust);
    ui->listWidget_albumitems->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_albumitems->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_albumitems->horizontalScrollBar()->setDisabled(true);

    //合集展示items列表
    ui->listWidget_medgroups->setViewMode(QListView::IconMode);
    ui->listWidget_medgroups->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_medgroups->setResizeMode(QListWidget::Adjust);
    ui->listWidget_medgroups->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_medgroups->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_medgroups->horizontalScrollBar()->setDisabled(true);

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

    //专辑列表
    ui->listWidget_albums->setViewMode(QListView::IconMode);
    ui->listWidget_albums->setMovement(QListView::Static);
    ui->listWidget_albums->setResizeMode(QListWidget::Adjust);
    ui->listWidget_albums->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_albums->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_albums->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_albums->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_albums->horizontalScrollBar()->setDisabled(true);
    ui->listWidget_albums->hide();//默认隐藏

    //合集列表
    ui->listWidget_groups->setViewMode(QListView::IconMode);
    ui->listWidget_groups->setMovement(QListView::Static);
    ui->listWidget_groups->setResizeMode(QListWidget::Adjust);
    ui->listWidget_groups->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_groups->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_groups->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_groups->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_groups->horizontalScrollBar()->setDisabled(true);
    ui->listWidget_groups->hide();//默认隐藏

    ui->pushButton_doneworks->setCheckable(true);
    ui->pushButton_doneworks->setChecked(true);
    ui->pushButton_donegroup->setCheckable(true);
    ui->pushButton_album->setCheckable(true);

    //作品列表--左侧
    for(int i = 0; i<m_producelist.count();i++)
    {
        slot_addItemToList(m_producelist.at(i),m_datalist.at(i),666);
    }
//    ui->listWidget_prod_pictures->setCurrentItem(ui->listWidget_producelist->item(0));//选中第一个
}

void DoneWorks::handleSignalsAndSlots()
{
    //显示作品
    connect(ui->pushButton_doneworks,&QPushButton::clicked,[=](){
        ui->listWidget_groups->setHidden(true);
        ui->listWidget_albums->setHidden(true);
        ui->listWidget_producelist->setHidden(false);
        ui->pushButton_album->setChecked(false);
        ui->pushButton_donegroup->setChecked(false);
        ui->pushButton_doneworks->setChecked(true);
        ui->stackedWidget_produce->setCurrentIndex(0);
    });

    //显示专辑
    connect(ui->pushButton_album,&QPushButton::clicked,[=](){
        ui->listWidget_groups->setHidden(true);
        ui->listWidget_producelist->setHidden(true);
        ui->listWidget_albums->setHidden(false);
        ui->pushButton_doneworks->setChecked(false);
        ui->pushButton_donegroup->setChecked(false);
        ui->pushButton_album->setChecked(true);
        ui->stackedWidget_produce->setCurrentIndex(0);
    });

    //显示合集
    connect(ui->pushButton_donegroup,&QPushButton::clicked,[=](){
        ui->listWidget_groups->setHidden(false);
        ui->listWidget_albums->setHidden(true);
        ui->listWidget_producelist->setHidden(true);
        ui->pushButton_doneworks->setChecked(false);
        ui->pushButton_album->setChecked(false);
        ui->pushButton_donegroup->setChecked(true);
        ui->stackedWidget_produce->setCurrentWidget(ui->page_groups);
    });

    //创建专辑
    connect(ui->pushButton_menu_album,&QPushButton::clicked,[=](){

    });

    //创建合集
    connect(ui->pushButton_menu_hehi,&QPushButton::clicked,[=](){
//        createHJ_ContextMenu();
        QString groupid = dataBase::getInstance()->group_insertGroups(dataBase::getInstance()->getCurrentUserID(),QString(u8"自定义合集"),QString(u8"http://43.143.226.251:8080/group1/header_pic/20230403180134795.png"));
        if(!groupid.isEmpty())
        {
            slot_addItemToGroupList(GROUPTYPE::G_CUSTOM,QString(u8"自定义合集"), QString(""), groupid);
        }
        else
        {
            qDebug() << QString(u8"数据库返回groupid为空!");
            return;
        }
    });

    //接收查询到某个类型的媒体数量+信息
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
                QLabel *lab_counts = getCurrentItem(current,"label_medcounts");
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


    //接收当前请用户下group集合
    connect(dataBase::getInstance(),&dataBase::sig_group_allgroups,[=](QString g_name,QString g_pix,QString g_id){
        slot_addItemToGroupList(GROUPTYPE::G_NORMAL,g_name, g_pix, g_id);
    });

    //接收到对应的group传回来的items
    connect(dataBase::getInstance(),&dataBase::sig_group_groupMedias,[=](QVariant& var){
        slot_addItmeToGroupIDList(var);
    });

}

//加载左侧类型列表自定义刷新item
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

//特定位置加载左侧类型列表自定义刷新item
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

//创建合集
void DoneWorks::slot_addItemToGroupList(GROUPTYPE TYPE, const QString &name, const QString &pix_url, const QString& group_id)
{
    MediaGroup *itemWidget = new MediaGroup(TYPE,group_id,name,pix_url);
    itemWidget->setFixedSize(200,120);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole,group_id);
    item->setSizeHint(itemWidget->size() + QSize(10,10));
    ui->listWidget_groups->addItem(item);
    ui->listWidget_groups->setItemWidget(item,itemWidget);
    ui->listWidget_groups->setCurrentItem(item);
    //关联信号与槽函数
    //添加媒体
    connect(itemWidget,&MediaGroup::sig_item_additem,[=](){
        SortDialog::getInstance()->exec_(group_id);
    });
    //合集点击重新展示合集下的items
    connect(itemWidget,&MediaGroup::sig_item_clicked,[=](){
        ui->listWidget_medgroups->clear();//先清除items
        ui->stackedWidget_produce->setCurrentWidget(ui->page_groups);
        dataBase::getInstance()->group_getCurUserGroupMedias(group_id);//加载对应group_id下的items
    });
    //合集重命名
    connect(itemWidget,&MediaGroup::sig_item_rename,[=](const QString name){
        dataBase::getInstance()->group_updateGroupsName(group_id,name);//合集重命名
    });
    //合集删除
    connect(itemWidget,&MediaGroup::sig_item_delete,[=](){
        bool ok = dataBase::getInstance()->group_removeGroups(group_id);
        if(ok)
        {
            itemWidget->disconnect();
            itemWidget->deleteLater();
            ui->listWidget_groups->takeItem(ui->listWidget_groups->row(item));
            delete item;
            ui->listWidget_medgroups->clear();
        }
    });

    //合集替换新封面，更新封面链接
    connect(itemWidget,&MediaGroup::sig_item_newCover,dataBase::getInstance(),&dataBase::group_updateGroupsCover);
}

//合集列表展示
void DoneWorks::slot_addItmeToGroupIDList(QVariant& media)
{
    fileBody body = media.value<fileBody>();//通用类型转为专用类型
    qDebug() << QString(u8"[group_id]接收到数据库查询返回的信息，要被创建新的ITEM信息如下:") << endl;
    qDebug() << "fid" << body.fid << endl;
    qDebug() << "fnick" << body.fnick << endl;
    qDebug() << "furl"  << body.furl << endl;
    qDebug() << "fduration" << body.fduration << endl;
    qDebug() << "fcover" << body.fcover << endl;
    qDebug() << "fmedtype" << body.fmedtype << endl;
    qDebug() << "fmedtheme" << body.fmedtheme << endl;
    qDebug() << "fsize" << body.fsize << endl;

    QListWidgetItem *item = new QListWidgetItem(body.fnick);//介绍
    item->setData(Qt::UserRole,body.furl);
    FilesItem *itemWidget = new FilesItem(FILEEDIT::CANEDIT,body.fid,body.furl,body.fsize,body.fcover);
    itemWidget->initFileItem(body);
    item->setSizeHint(DITEMSIZE);
    item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);

    ui->listWidget_medgroups->addItem(item);
    ui->listWidget_medgroups->setItemWidget(item,itemWidget);

    //信号与槽函数
    //播放
    connect(itemWidget,&FilesItem::sig_sendItem_play,[=](){
    QUrlQuery query;
    query.addQueryItem(u8"id",QString::number(body.fid));
    query.addQueryItem(u8"url",item->data(Qt::UserRole).toString());
    query.addQueryItem(u8"nick",body.fnick);
    query.addQueryItem(u8"pos","0");
    MultipPlayer::getInstance()->slot_addTempPlaylist(666,QStringList{item->data(Qt::UserRole).toString()},query);
    });
    //下载
    connect(itemWidget,&FilesItem::sig_sendItem_download,[=](QUrlQuery query){
        QString nick = query.queryItemValue(QString(u8"nick"));
        QString url = query.queryItemValue(QString(u8"url"));
        DownloadType::getInstance()->showDownloadForm(1,nick,url);
    });
}

void DoneWorks::setInstallEventer()
{
    ui->listWidget_producelist->installEventFilter(this);
}

//加载对应类型媒体下item
void DoneWorks::slot_receivedData_findTypeResult(QVariant& media)
{
        fileBody body = media.value<fileBody>();//通用类型转为专用类型
        qDebug() << QString(u8"接收到数据库查询返回的信息，要被创建新的ITEM信息如下:") << endl;
        qDebug() << "fid" << body.fid << endl;
        qDebug() << "fnick" << body.fnick << endl;
        qDebug() << "furl"  << body.furl << endl;
        qDebug() << "fduration" << body.fduration << endl;
        qDebug() << "fcover" << body.fcover << endl;
        qDebug() << "fmedtype" << body.fmedtype << endl;
        qDebug() << "fmedtheme" << body.fmedtheme << endl;
        qDebug() << "fsize" << body.fsize << endl;

        QListWidgetItem *item = new QListWidgetItem(body.fnick);//介绍
        item->setData(Qt::UserRole,body.furl);
        FilesItem *itemWidget = new FilesItem(FILEEDIT::CANEDIT,body.fid,body.furl,body.fsize,body.fcover);
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
        //播放
        connect(itemWidget,&FilesItem::sig_sendItem_play,[=](){
        QUrlQuery query;
        query.addQueryItem(u8"id",QString::number(body.fid));
        query.addQueryItem(u8"url",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"nick",body.fnick);
        query.addQueryItem(u8"pos","0");
        MultipPlayer::getInstance()->slot_addTempPlaylist(666,QStringList{item->data(Qt::UserRole).toString()},query);
        });
        //下载
        connect(itemWidget,&FilesItem::sig_sendItem_download,[=](QUrlQuery query){
            QString nick = query.queryItemValue(QString(u8"nick"));
            QString url = query.queryItemValue(QString(u8"url"));
            DownloadType::getInstance()->showDownloadForm(1,nick,url);
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
            qDebug() <<QString(u8"lab_medcounts");
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

void DoneWorks::createHJ_ContextMenu()
{
    QMenu cmenu;
    cmenu.addAction(QString(u8"新建合集"),this,SLOT(slot_createNewHJ()));
    cmenu.exec(QCursor::pos());
}


void DoneWorks::slot_createNewHJ()
{
    slot_addItemToGroupList(GROUPTYPE::G_CUSTOM,QString(u8"自定义合集"), QString(""), "-1");
}


void DoneWorks::slot_setUserTagsWorkCounts(QStringList &list_counts)
{
    for(int i = 0; i < list_counts.count(); i++)
    {
        QLabel *lab_counts = getCurrentItem(ui->listWidget_producelist->item(i),"label_medcounts");
        if(lab_counts != nullptr)
        {
            lab_counts->setText(list_counts.at(i));//设置查询到的数量
            if(list_counts.at(i).toInt() == 0)
            {
                lab_counts->setProperty("cirle",false);          }
            else
            {
                lab_counts->setProperty("cirle",true);
            }
            lab_counts->style()->polish(lab_counts);
        }
        else
        {
            qDebug() << QString(u8"设置数量的item 没找到！");
        }
    }
}

//查询初始化当前用户下合集组
void DoneWorks::slot_initUserGroups()
{
    ui->listWidget_groups->clear();
    dataBase::getInstance()->group_getCurUserGroups(dataBase::getInstance()->getCurrentUserID());//获取当前用户下合集
}
