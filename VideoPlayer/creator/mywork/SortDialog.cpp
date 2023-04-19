#include "SortDialog.h"
#include "ui_SortDialog.h"

//类外初始化
SortDialog* SortDialog::m_pInstance = nullptr;

SortDialog::SortDialog(QWidget *parent) :
    BaseDialog(parent),
    ui(new Ui::SortDialog)
{
    ui->setupUi(this);
    resize(1225,680);
    setTitleBarMoveArea(ui->frame_title,2);
    setContentsMargins(2,2,2,2);
    setWindowTitle(QString(u8"视频归类"));
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

SortDialog::~SortDialog()
{
    delete ui;
    //删除创建的单例
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void SortDialog::initWorkUI()
{
    ui->stackedWidget_heji_ctl->setCurrentWidget(ui->page_operate_heji);
    ui->stackedWidget_medias_ctl->setCurrentWidget(ui->page_operate_medias);


    ui->splitter->setStretchFactor(0,2);
    ui->splitter->setStretchFactor(1,8);
    ui->splitter->setChildrenCollapsible(false);

    ui->comboBox_heji->setView(new QListView());
    ui->comboBox_medias->setView(new QListView());

    ui->comboBox_medias->addItem(QString(u8"电影"),QString(u8"movies"));
    ui->comboBox_medias->addItem(QString(u8"网络剧"),QString(u8"netdrama"));
    ui->comboBox_medias->addItem(QString(u8"短视频"),QString(u8"shortvideos"));
    ui->comboBox_medias->addItem(QString(u8"中视频"),QString(u8"midvideos"));
    ui->comboBox_medias->addItem(QString(u8"音乐"),QString(u8"musics"));
    ui->comboBox_medias->addItem(QString(u8"图片"),QString(u8"pictures"));

    //左侧合集列表
    ui->listWidget_content_L->setViewMode(QListView::IconMode);
    ui->listWidget_content_L->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_content_L->setResizeMode(QListWidget::Adjust);
    ui->listWidget_content_L->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_content_L->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_content_L->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_content_L->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_content_L->horizontalScrollBar()->setDisabled(true);

    //右侧分类列表
    ui->listWidget_content_R->setViewMode(QListView::IconMode);
    ui->listWidget_content_R->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_content_R->setResizeMode(QListWidget::Adjust);
    ui->listWidget_content_R->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_content_R->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_content_R->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_content_R->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_content_R->horizontalScrollBar()->setDisabled(true);

    ui->lineEdit_heji_search->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_heji_search->setPlaceholderText(QString(u8"请输入搜索关键字"));

    ui->lineEdit_medias_search->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_medias_search->setPlaceholderText(QString(u8"请输入搜索关键字"));
}

void SortDialog::handleSignalsAndSlots()
{
    //初始化
    connect(this,&SortDialog::sig_init,[=](){
        slot_initCurUserGroups();
    });

    //最小化
    connect(ui->pushButton_min,&QPushButton::clicked,[=](){
        this->showMinimized();
    });

    //关闭
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        ui->comboBox_heji->clear();
        ui->lineEdit_heji_search->clear();
        ui->lineEdit_medias_search->clear();
        ui->listWidget_content_L->clear();
        ui->listWidget_content_R->clear();
        qDebug() << QString(u8"关闭");
        this->close();
    });


    //合集--批量操作
    connect(ui->pushButton_heji_operate,&QPushButton::clicked,[=](){
        ui->stackedWidget_heji_ctl->setCurrentWidget(ui->page_operate_heji_all);
        ui->comboBox_heji->setEnabled(false);
        for(int i = 0; i < ui->listWidget_content_L->count(); i++)
        {
            getItemWidget(ui->listWidget_content_L->item(i),"FilesItem")->slot_setSelButtonChecked(true);
        }

    });

    //合集--退出批量操作
    connect(ui->pushButton_heji_exit,&QPushButton::clicked,[=](){
        ui->stackedWidget_heji_ctl->setCurrentWidget(ui->page_operate_heji);
        ui->comboBox_heji->setEnabled(true);
        for(int i = 0; i < ui->listWidget_content_L->count(); i++)
        {
            getItemWidget(ui->listWidget_content_L->item(i),"FilesItem")->slot_setSelButtonChecked(false);
        }
    });

    //合集--全选
    connect(ui->pushButton_heji_selall,&QPushButton::clicked,[=](){
        ui->comboBox_heji->setEnabled(false);
        for(int i = 0; i < ui->listWidget_content_L->count(); i++)
        {
            if(!ui->listWidget_content_L->isRowHidden(i))
            getItemWidget(ui->listWidget_content_L->item(i),"FilesItem")->slot_setSelButtonChecked(true);
        }
    });

    //合集--清除选中项
    connect(ui->pushButton_heji_seldel,&QPushButton::clicked,[=](){
        for(int i = 0; i < ui->listWidget_content_L->count(); i++)
        {
            if(getItemCheckedButton(ui->listWidget_content_L->item(i),"checkBox_selall")->isChecked())
            {
                getItemWidget(ui->listWidget_content_L->item(i),"FilesItem")->slot_setSelButtonChecked(false);
            }
        }
        ui->comboBox_heji->setEnabled(true);
    });

    //合集--移除（部分选中移除）
    connect(ui->pushButton_heji_del,&QPushButton::clicked,[=](){
        slot_removeItemsFromHJ_DB_UI();//遍历循环单个移除(部分选中的情况)
    });

    //合集--移除合集内所有item
    connect(ui->pushButton_clear_HJ,&QPushButton::clicked,[=](){
        slot_removeItemsFromHJ_DB_UI();//遍历循环单个移除(全选中的情况)
    });

    //分类--批量操作
    connect(ui->pushButton_medias_operate,&QPushButton::clicked,[=](){
        ui->stackedWidget_medias_ctl->setCurrentWidget(ui->page_operate_medias_all);
        ui->comboBox_medias->setEnabled(false);
        for(int i = 0; i < ui->listWidget_content_R->count(); i++)
        {
            getItemWidget(ui->listWidget_content_R->item(i),"FilesItem")->slot_setSelButtonChecked(true);
        }
    });

    //分类--退出批量操作
    connect(ui->pushButton_medias_exit,&QPushButton::clicked,[=](){
        ui->stackedWidget_medias_ctl->setCurrentWidget(ui->page_operate_medias);
        ui->comboBox_medias->setEnabled(true);
        for(int i = 0; i < ui->listWidget_content_R->count(); i++)
        {
            getItemWidget(ui->listWidget_content_R->item(i),"FilesItem")->slot_setSelButtonChecked(false);
        }
    });

    //分类--全选
    connect(ui->pushButton_medias_selall,&QPushButton::clicked,[=](){
        ui->comboBox_medias->setEnabled(false);
        for(int i = 0; i < ui->listWidget_content_R->count(); i++)
        {
            if(!ui->listWidget_content_R->isRowHidden(i))
            getItemWidget(ui->listWidget_content_R->item(i),"FilesItem")->slot_setSelButtonChecked(true);
        }
    });

    //分类--清除选中项
    connect(ui->pushButton_medias_seldel,&QPushButton::clicked,[=](){
        for(int i = 0; i < ui->listWidget_content_R->count(); i++)
        {
            if(getItemCheckedButton(ui->listWidget_content_R->item(i),"checkBox_selall")->isChecked())
            {
                getItemWidget(ui->listWidget_content_R->item(i),"FilesItem")->slot_setSelButtonChecked(false);
            }
        }
        ui->comboBox_medias->setEnabled(true);
    });

    //分类--移除(部分选中移除)
    connect(ui->pushButton_medias_del,&QPushButton::clicked,[=](){
        slot_removeItemsFromSort_DB_UI();//从对应分类数据库删除所有勾选的item并更新UI
    });

    //分类--分类选中媒体添加到合集(部分选中)
    connect(ui->pushButton_addtoHJ,&QPushButton::clicked,[=](){
        //数据库插入新的items数据
        slot_addCheckedItemsFromSortToHJ_DB();
        //右侧分类列表所有items添加完毕后，左侧合集列表进行更新（不管是否插入成功，都要进行更新）
        slot_combobox_HJ_changed(ui->comboBox_heji->currentIndex());
    });

    //分类--全部添加到对应合集(所有选中的items)
    connect(ui->pushButton_addtoHJ_all,&QPushButton::clicked,[=](){
        //数据库插入新的items数据
        slot_addCheckedItemsFromSortToHJ_DB();
        //右侧分类列表添加完毕，左侧合集列表进行更新（不管是否插入成功，都要进行更新）
        slot_combobox_HJ_changed(ui->comboBox_heji->currentIndex());
    });

    //合集选择
    connect(ui->comboBox_heji,QOverload<int>::of(&QComboBox::activated),[=](int index){
        slot_combobox_HJ_changed(index);
    });

    //类型选择
    connect(ui->comboBox_medias,QOverload<int>::of(&QComboBox::activated),[=](int index){
        slot_combobox_SORT_changed(index);

    });

    //关键字检索--合集
    connect(ui->lineEdit_heji_search,&QLineEdit::textChanged,[=](const QString &text){
        findKeyWordResult(ui->listWidget_content_L,text);
    });

    //关键字检索--分类
    connect(ui->lineEdit_medias_search,&QLineEdit::textChanged,[=](const QString &text){
        findKeyWordResult(ui->listWidget_content_R,text);
    });
}

void SortDialog::setInstallEventFilter()
{
    this->installEventFilter(this);
    ui->frame_title->installEventFilter(this);
}

SortDialog *SortDialog::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new SortDialog();
    }
    return m_pInstance;
}

void SortDialog::exec_(const QString &group_id)
{
    m_groupid = group_id;
    emit sig_init();
    this->exec();
}

bool SortDialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            setCursor(Qt::ArrowCursor);
        }
    }
    if(watched == ui->frame_title)
    {
        if(event->type() == QEvent::MouseButtonDblClick)
        {
            if(m_isMax)
            {
                this->showNormal();
                this->move(QPoint(m_oldRect.x(),m_oldRect.y()));
            }
            else
            {
                m_oldRect = this->geometry();
                this->showMaximized();
            }
            m_isMax = !m_isMax;
        }
        else if(event->type() == QEvent::Enter)
        {
            setCursor(Qt::ArrowCursor);
        }
    }
    return QWidget::eventFilter(watched,event);
}

void SortDialog::findKeyWordResult(QListWidget *listwidget, QString keyword)
{
    if(listwidget->count() == 0) return;
    keyword.remove(QRegExp("\\s"));
    if(keyword.isEmpty())
    {
        for(int i = 0; i < listwidget->model()->rowCount(); i++)
            listwidget->setRowHidden(i,false);

    }
    else
    {
        for(int i = 0; i < listwidget->model()->rowCount(); i++)
        {
            listwidget->setRowHidden(i,true);
            QString curname = "";
            QAbstractItemModel *model = listwidget->model();
            QModelIndex index;
            for(int j = 0; j < listwidget->model()->columnCount(); j++)
            {
                index = model->index(i,j);
                curname += model->data(index,Qt::DisplayRole).toString();//默认是DisplayRole
            }
            curname.remove(QRegExp("\\s"));
            if(curname.contains(keyword,Qt::CaseInsensitive)) //CaseSensitive:敏感
               listwidget->setRowHidden(i,false);
        }
    }
}

//获取QCheckBox
QCheckBox *SortDialog::getItemCheckedButton(QListWidgetItem* item, const QString& objname)
{
    QWidget* itemWidget = item->listWidget()->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QCheckBox *itemBtn = itemWidget->findChild<QCheckBox*>(objname);//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != itemBtn)
        {
//            qDebug() << QString(u8"找到checkedbox");
            return itemBtn;
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
}

//获取FilesItem
FilesItem *SortDialog::getItemWidget(QListWidgetItem *item, const QString &objname)
{
    QWidget* itemWidget = item->listWidget()->itemWidget(item);
    if(nullptr != itemWidget)
    {
//        qDebug() << QString(u8"找到FilesItem");
        return qobject_cast<FilesItem*>(itemWidget);
    }
    else
    {
        return nullptr;
    }
}

//添加当前用户下用户合集
void SortDialog::slot_initCurUserGroups()
{
    //添加所有合集
    QList<QUrlQuery> querys = dataBase::getInstance()->group_getCurUserAllGroups(dataBase::getInstance()->getCurrentUserID());
    qDebug() << QString(u8"当前用户下查找到合集的个数：%1").arg(querys.count());
    if(!querys.isEmpty())
    {
        slot_addItemsTo_HJ(querys,m_groupid);
    }
}

//添加某个用户下所有合集
void SortDialog::slot_addItemsTo_HJ(QList<QUrlQuery>& querys, const QString& g_id)
{
    for(int i = 0; i < querys.count(); i++)
    {
        ui->comboBox_heji->addItem(querys.at(i).queryItemValue(u8"group_name"),querys.at(i).queryItemValue(u8"group_id"));
    }
    for(int i = 0; i < ui->comboBox_heji->count(); i++)
    {
        if(ui->comboBox_heji->itemData(i).toString() == g_id)
        {
            ui->comboBox_heji->setCurrentIndex(i);
        }
    }
}

//添加某个用户下某个合集所有items
void SortDialog::slot_addItemsTo_MEDIA(QList<QVariant>& medias)
{
    for(int i = 0; i < medias.count(); i++)
    {
        fileBody body = medias.at(i).value<fileBody>();
        QListWidgetItem *item = new QListWidgetItem(body.fnick);//介绍
        item->setData(Qt::UserRole,body.furl);
        FilesItem *itemWidget = new FilesItem(FILEEDIT::CANEDIT,body.fid,body.furl,body.fsize,body.fcover);
        itemWidget->initFileItem(body);
        itemWidget->setFixedSize(QSize(190,135));
        item->setSizeHint(QSize(195,140));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
        ui->listWidget_content_L->addItem(item);
        ui->listWidget_content_L->setItemWidget(item,itemWidget);

        //点击勾选
        connect(itemWidget,&FilesItem::sig_sendItem_clicked,[=](){
            if(!getItemCheckedButton(item,"checkBox_selall")->isChecked())
            {
                itemWidget->slot_setSelButtonChecked(true);
            }
            else
            {
                itemWidget->slot_setSelButtonChecked(false);
            }
        });

        //播放
        connect(itemWidget,&FilesItem::sig_sendItem_play,[=](){
        QUrlQuery query;
        query.addQueryItem(u8"url",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"nick",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"pos","0");
        this->hide();
        MultipPlayer::getInstance()->slot_addTempPlaylist(666,QStringList{item->data(Qt::UserRole).toString()},query);
        });
        //下载（此处不弹出下载提示框，直接下载）
        connect(itemWidget,&FilesItem::sig_sendItem_download,[=](QUrlQuery query){
            QString nick = query.queryItemValue(QString(u8"nick"));
            QString url = query.queryItemValue(QString(u8"url"));
            qDebug() << QString(u8"要下载的item的名称：%1，下载地址：%2").arg(nick).arg(url);
        });
        //此处不做移除操作，由勾选遍历去移除
    }
}

//添加某个用户下某个分类类型下所有items
void SortDialog::slot_addItemsTo_SORTMEDIA(QList<QVariant> &medias)
{
    for(int i = 0; i < medias.count(); i++)
    {
        fileBody body = medias.at(i).value<fileBody>();
        QListWidgetItem *item = new QListWidgetItem(body.fnick);//介绍
        item->setData(Qt::UserRole,body.furl);
        FilesItem *itemWidget = new FilesItem(FILEEDIT::CANEDIT,body.fid,body.furl,body.fsize,body.fcover);
        itemWidget->initFileItem(body);
        itemWidget->setFixedSize(QSize(190,135));
        item->setSizeHint(QSize(195,140));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
        ui->listWidget_content_R->addItem(item);
        ui->listWidget_content_R->setItemWidget(item,itemWidget);

        //点击勾选
        connect(itemWidget,&FilesItem::sig_sendItem_clicked,[=](){
            if(!getItemCheckedButton(item,"checkBox_selall")->isChecked())
            {
                itemWidget->slot_setSelButtonChecked(true);
            }
            else
            {
                itemWidget->slot_setSelButtonChecked(false);
            }
        });

        //播放
        connect(itemWidget,&FilesItem::sig_sendItem_play,[=](){
        QUrlQuery query;
        query.addQueryItem(u8"url",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"nick",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"pos","0");
        this->hide();
        MultipPlayer::getInstance()->slot_addTempPlaylist(666,QStringList{item->data(Qt::UserRole).toString()},query);
        });
        //下载
        connect(itemWidget,&FilesItem::sig_sendItem_download,[=](QUrlQuery query){
            QString nick = query.queryItemValue(QString(u8"nick"));
            QString url = query.queryItemValue(QString(u8"url"));
            qDebug() << QString(u8"要下载的item的名称：%1，下载地址：%2").arg(nick).arg(url);
        });
        //此处不做移除操作，由勾选遍历去移除
    }
}

//往数对应合集据库添加新的(已经勾选的)itmes，并刷新
void SortDialog::slot_addCheckedItemsFromSortToHJ_DB()
{
    for(int i = 0; i < ui->listWidget_content_R->count(); i++)
    {
        if(!ui->listWidget_content_R->isRowHidden(i))
        {
            if(getItemCheckedButton(ui->listWidget_content_R->item(i),"checkBox_selall")->isChecked())
            {
                int f_id = getItemWidget(ui->listWidget_content_R->item(i),"FilesItem")->getItem_fid();
                bool isOK = dataBase::getInstance()->group_insertOneToGroups(m_groupid,f_id);
                if(isOK)
                {
                    qDebug() <<QString(u8"文件ID为：%1 插入合集ID为：%2 的合集成功~！").arg(f_id).arg(m_groupid);
                }
                else
                {
                    qDebug() << QString(u8"文件ID:%1已存在或者数据插入失败！").arg(f_id);
                }
            }
        }
    }
}

//从对应合集数据库删除所有勾选的item并更新UI
void SortDialog::slot_removeItemsFromHJ_DB_UI()
{
    for(int i = 0; i < ui->listWidget_content_L->count(); i++)
    {
        if(!ui->listWidget_content_L->isRowHidden(i))
        {
            if(getItemCheckedButton(ui->listWidget_content_L->item(i),"checkBox_selall")->isChecked())
            {
                int f_id = getItemWidget(ui->listWidget_content_L->item(i),"FilesItem")->getItem_fid();
                qDebug() << QString(u8"合集：%1要删除的文件的ID:%2").arg(m_groupid).arg(f_id);
                bool OK = dataBase::getInstance()->group_removeOneFromGroups(m_groupid,f_id);
                if(OK)
                {
                    //数据库删除成功后，列表显示再移除
                    getItemWidget(ui->listWidget_content_L->item(i),"FilesItem")->disconnect();
                    getItemWidget(ui->listWidget_content_L->item(i),"FilesItem")->deleteLater();
                    delete ui->listWidget_content_L->takeItem(i);
                    qDebug() <<QString(u8"文件ID为：%1 从合集ID为：%2 的合集删除成功~！").arg(f_id).arg(m_groupid);
                }
                else
                {
                    qDebug() <<QString(u8"从合集：%1 中删除ID为：%2 的文件失败！").arg(m_groupid).arg(f_id);
                }
            }
        }
    }
}

//从对应分类数据库删除所有勾选的item并更新UI
void SortDialog::slot_removeItemsFromSort_DB_UI()
{
    for(int i = 0; i < ui->listWidget_content_R->count(); i++)
    {
        if(!ui->listWidget_content_R->isRowHidden(i))
        {
            if(getItemCheckedButton(ui->listWidget_content_R->item(i),"checkBox_selall")->isChecked())
            {
                int f_id = getItemWidget(ui->listWidget_content_R->item(i),"FilesItem")->getItem_fid();
                qDebug() << QString(u8"分类列表：%1要删除的文件的ID:%2").arg(m_curtype).arg(f_id);
                bool OK = dataBase::getInstance()->creator_removeOneMediaFromSort(m_curtype,f_id);
                if(OK)
                {
                    //数据库删除成功后，列表显示再移除
                    getItemWidget(ui->listWidget_content_R->item(i),"FilesItem")->disconnect();
                    getItemWidget(ui->listWidget_content_R->item(i),"FilesItem")->deleteLater();
                    delete ui->listWidget_content_R->takeItem(i);
                    qDebug() <<QString(u8"文件ID为：%1 从分类列表为：%2 的列表删除成功~！").arg(f_id).arg(m_curtype);
                }
                else
                {
                    qDebug() <<QString(u8"文件ID为：%1 从分类列表为：%2 的列表删除失败~！").arg(f_id).arg(m_curtype);
                }
            }
        }
    }
}

//响应合集改变
void SortDialog::slot_combobox_HJ_changed(int index)
{
    ui->listWidget_content_L->clear();
    qDebug() << QString(u8"heji索引改变了,index data:") << ui->comboBox_heji->itemData(index).toString();
    if(index != -1)//索引有效
    {
        QString group_name = ui->comboBox_heji->itemText(index);
        QString group_id   = ui->comboBox_heji->itemData(index).toString();
        m_groupid = group_id;//随着item改变m_groupid也跟着改变
        if(!group_name.isEmpty())
        {
            //如果数据量比较大，会产生阻塞，界面不能动（需改进）
            QList<QVariant> medias = dataBase::getInstance()->group_getCurUserOneGroupAllMedias(group_id);
            qDebug() << QString(u8"当前用户下查找到合集下面items的个数：%1").arg(medias.count());
            if(medias.count() == 0)
            {
                ui->stackedWidget_context_L->setCurrentIndex(1);
                ui->label_L_blank->setPixmap(QPixmap(":/images/bgpic/nothing.png"));
                ui->label_L_blank->setScaledContents(true);
                ui->pushButton_heji_blank->setText(QString(u8"该类型暂无资源！"));
            }
            else
            {
                ui->stackedWidget_context_L->setCurrentIndex(1);
                ui->label_L_blank->setPixmap(QPixmap(":/images/bgpic/nothing.png"));
                ui->label_L_blank->setScaledContents(true);
                ui->pushButton_heji_blank->setText(QString(u8"资源加载中..."));
                QTimer::singleShot(1500,0,[=](){
                    ui->stackedWidget_context_L->setCurrentIndex(0);
                });
            }
            //正式添加媒体
            if(!medias.isEmpty())
            {
                slot_addItemsTo_MEDIA(medias);
            }
        }
    }
}

//响应分类改变
void SortDialog::slot_combobox_SORT_changed(int index)
{
    ui->listWidget_content_R->clear();
    qDebug() << QString(u8"medias索引改变了,index data:") << ui->comboBox_medias->itemData(index).toString();
    m_curtype = ui->comboBox_medias->itemData(index).toString();
    if(index != -1)//索引有效
    {
        QString type_name   = ui->comboBox_medias->itemText(index);
        QString type_data   = ui->comboBox_medias->itemData(index).toString();
        //如果数据量比较大，会产生阻塞，界面不能动（需改进）
        QList<QVariant> sort_medias = dataBase::getInstance()->group_getCurUserOneSortAllMedias(type_data);
        qDebug() << QString(u8"当前用户下查找到合集下面items的个数：%1").arg(sort_medias.count());
        if(sort_medias.count() == 0)
        {
            ui->stackedWidget_context_R->setCurrentIndex(1);
            ui->label_R_blank->setPixmap(QPixmap(":/images/bgpic/nothing.png"));
            ui->label_R_blank->setScaledContents(true);
            ui->pushButton_medias_blank->setText(QString(u8"该类型暂无资源！"));
        }
        else
        {
            ui->stackedWidget_context_R->setCurrentIndex(1);
            ui->label_R_blank->setPixmap(QPixmap(":/images/bgpic/nothing.png"));
            ui->label_R_blank->setScaledContents(true);
            ui->pushButton_medias_blank->setText(QString(u8"资源加载中..."));
            QTimer::singleShot(1500,0,[=](){
                ui->stackedWidget_context_R->setCurrentIndex(0);
            });
        }
        //正式添加媒体
        if(!type_name.isEmpty())
        {
            slot_addItemsTo_SORTMEDIA(sort_medias);
        }
    }
}
