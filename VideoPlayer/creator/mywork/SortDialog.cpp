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

    ui->listWidget_content_L->setViewMode(QListView::IconMode);
    ui->listWidget_content_L->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_content_L->setResizeMode(QListWidget::Adjust);
    ui->listWidget_content_L->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_content_L->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_content_L->horizontalScrollBar()->setDisabled(true);

    ui->listWidget_content_R->setViewMode(QListView::IconMode);
    ui->listWidget_content_R->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_content_R->setResizeMode(QListWidget::Adjust);
    ui->listWidget_content_R->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_content_R->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_content_R->horizontalScrollBar()->setDisabled(true);

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
    });
    //分类--添加到(部分选中)
    connect(ui->pushButton_addtoHJ,&QPushButton::clicked,[=](){
        for(int i = 0; i < ui->listWidget_content_R->count(); i++)
        {
            if(!ui->listWidget_content_R->isRowHidden(i))
            {
                if(getItemCheckedButton(ui->listWidget_content_R->item(i),"checkBox_selall")->isChecked())
                {
                    qDebug() << getItemWidget(ui->listWidget_content_R->item(i),"FilesItem")->getItem_furl();
                }
            }
        }
    });

    //分类--添加到(全部选中)
    connect(ui->pushButton_addtoHJ_all,&QPushButton::clicked,[=](){
        for(int i = 0; i < ui->listWidget_content_R->count(); i++)
        {
            if(getItemCheckedButton(ui->listWidget_content_R->item(i),"checkBox_selall")->isChecked())
            {
                qDebug() << getItemWidget(ui->listWidget_content_R->item(i),"FilesItem")->getItem_furl();
            }
        }
    });

    //合集选择
    connect(ui->comboBox_heji,QOverload<int>::of(&QComboBox::activated),[=](int index){
        ui->listWidget_content_L->clear();
        qDebug() << QString(u8"heji索引改变了,index data:") << ui->comboBox_heji->itemData(index).toString();
        if(index != -1)
        {
            QString group_name = ui->comboBox_heji->itemText(index);
            QString group_id   = ui->comboBox_heji->itemData(index).toString();
            if(!group_name.isEmpty())
            {
                QList<QVariant> medias = dataBase::getInstance()->group_getCurUserOneGroupAllMedias(group_id);
                qDebug() << QString(u8"当前用户下查找到合集下面items的个数：%1").arg(medias.count());
                if(!medias.isEmpty())
                {
                    slot_addItemsTo_MEDIA(medias);
                }
            }
        }
    });

    //类型选择
    connect(ui->comboBox_medias,QOverload<int>::of(&QComboBox::activated),[=](int index){
        ui->listWidget_content_R->clear();
        qDebug() << QString(u8"medias索引改变了,index data:") << ui->comboBox_medias->itemData(index).toString();
        if(index != -1)
        {
            QString type_name = ui->comboBox_medias->itemText(index);
            QString type_data   = ui->comboBox_medias->itemData(index).toString();
            QList<QVariant> sort_medias = dataBase::getInstance()->group_getCurUserOneSortAllMedias(type_data);
            qDebug() << QString(u8"当前用户下查找到合集下面items的个数：%1").arg(sort_medias.count());
            if(!type_name.isEmpty())
            {
                slot_addItemsTo_SORTMEDIA(sort_medias);
            }
        }
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

QCheckBox *SortDialog::getItemCheckedButton(QListWidgetItem *item, const QString &objname)
{
    QWidget* itemWidget = item->listWidget()->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QCheckBox *itemBtn = itemWidget->findChild<QCheckBox*>(objname);//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != itemBtn)
        {
            qDebug() << QString(u8"找到checkedbox");
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

FilesItem *SortDialog::getItemWidget(QListWidgetItem *item, const QString &objname)
{
    QWidget* itemWidget = item->listWidget()->itemWidget(item);
    if(nullptr != itemWidget)
    {
        qDebug() << QString(u8"找到FilesItem");
        return qobject_cast<FilesItem*>(itemWidget);
    }
    else
    {
        return nullptr;
    }
}

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
        FilesItem *itemWidget = new FilesItem(FILEEDIT::CANEDIT,body.furl,body.fsize,body.fcover);
        itemWidget->initFileItem(body);
        item->setSizeHint(QSize(155,115));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
        ui->listWidget_content_L->addItem(item);
        ui->listWidget_content_L->setItemWidget(item,itemWidget);
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
        FilesItem *itemWidget = new FilesItem(FILEEDIT::CANEDIT,body.furl,body.fsize,body.fcover);
        itemWidget->initFileItem(body);
        item->setSizeHint(QSize(155,115));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
        ui->listWidget_content_R->addItem(item);
        ui->listWidget_content_R->setItemWidget(item,itemWidget);
    }
}
