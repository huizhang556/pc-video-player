#include "NewListItem.h"
#include "ui_NewListItem.h"

NewListItem::NewListItem(QWidget *parent) :
    QWidget(parent),
    m_id(0),
    m_name(QString(u8"新建列表")),
    m_selfHeight(160),
    ui(new Ui::NewListItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

NewListItem::NewListItem(FINSTATUS type, const int id, const QString &name, QWidget *parent):
    QWidget(parent),
    m_status(type),
    m_id(id),
    m_name(name),
    m_selfHeight(160),
    ui(new Ui::NewListItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    setFinishedStatus();
}

NewListItem::~NewListItem()
{
    delete ui;
    delete m_rMenu;
}

void NewListItem::initWorkUI()
{
    //初始化
    setFixedHeight(160);
    ui->label_listName->setText(m_name);
    ui->lineEdit_listName->setText(m_name);
    ui->lineEdit_listName->selectAll();
    ui->lineEdit_listName->setFocus();
    ui->lineEdit_listName->installEventFilter(this);
    ui->stackedWidget_listName->setCurrentWidget(ui->page_name2);
    ui->stackedWidget_content->setCurrentWidget(ui->page_black);
    ui->pushButton_add_local->setIcon(QIcon(":/images/player/player_itemlist_add_music.png"));
    ui->pushButton_add_directory->setIcon(QIcon(":/images/player/player_itemlist_add_dir.png"));

    ui->listWidget_songerlist->setMovement(QListView::Static);
    ui->listWidget_songerlist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_songerlist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_songerlist->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

   createRightMenu();

    ui->pushButton_switch->setCheckable(true);
    ui->pushButton_rmenu->setCheckable(true);
    ui->pushButton_switch->setChecked(true);//默认是展开状态

//    for(int i = 0; i < m_id; i++)
//    {
//        songListItem *itemWidget = new songListItem();
//        QListWidgetItem *item = new QListWidgetItem(QString(u8"早安，世界--周杰伦%1").arg(i+1));
////        item->setSizeHint(QSize(ui->listWidget_songerlist->width() - ui->listWidget_songerlist->verticalScrollBar()->width() - 1,28));
//        item->setSizeHint(itemWidget->size());
//        ui->listWidget_songerlist->addItem(item);
//        ui->listWidget_songerlist->setItemWidget(item,itemWidget);

//        //信号与槽函数
//        connect(itemWidget,&songListItem::sig_item_selected,[=](QString sname){
//            ui->listWidget_songerlist->setCurrentItem(item);
//        });
//    }
}

void NewListItem::handleSignalsAndSlots()
{
    //列表名称--回车
    connect(ui->lineEdit_listName,&QLineEdit::returnPressed,[=](){
        slot_finishedRename();
    });

    connect(ui->pushButton_add_directory,&QPushButton::clicked,[=](){
        ui->pushButton_add_local->clicked();
    });


    //添加文件
    connect(ui->pushButton_add_local,&QPushButton::clicked,[=](){
        QStringList list  =  QFileDialog::getOpenFileNames(0,//不指定父窗口，设置自己的样式
                                                                        QString::fromLocal8Bit("选择文件"),
                                                                        QString::fromLocal8Bit("/"),
                                                                        QString::fromLocal8Bit("Videos(*avi *mp4 *flv *mp3 *wmv)"),
                                                                        0);//QFileDialog::DontUseNativeDialog
        m_playlist  = list;//添加进列表
        if(list.isEmpty()) return;
        foreach (QString fpath, list)
        {
            QFileInfo fileInfo(fpath);
            songListItem *itemWidget = new songListItem(fpath);
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(Qt::UserRole,fileInfo.fileName());
            item->setData(Qt::UserRole+1,fpath);
            item->setSizeHint(itemWidget->size());
            ui->listWidget_songerlist->addItem(item);
            ui->listWidget_songerlist->setItemWidget(item,itemWidget);


            //信号与槽函数
            //单击播放（改为button鼠标穿透，listwidget响应）
            connect(itemWidget,&songListItem::sig_item_selected,[=](QString sname){
                ui->listWidget_songerlist->setCurrentItem(item);
                emit sig_item_newPlaylist(m_id,m_playlist,item->data(Qt::UserRole+1).toString());
                qDebug() <<QString(u8"当前item已被设定！点击的item名称：%1,真实路径：%2").arg(sname).arg(item->data(Qt::UserRole+1).toString());
            });

            //添加信号（中继）
            connect(itemWidget,&songListItem::sig_item_addtolist,[=](){
                QMenu *addlist_Menu = new QMenu(this);
                addlist_Menu->setObjectName(QString::fromUtf8("addlist_Menu"));
                addlist_Menu->addAction(QString(u8"添加到我的收藏"),this,SLOT(slot_menu_newList()));
                addlist_Menu->addAction(QString(u8"添加到我的喜欢"),this,SLOT(slot_menu_deleteList()));
                addlist_Menu->addAction(QString(u8"添加到清脆悠远"),this,SLOT(slot_menu_clearList()));
                addlist_Menu->addAction(QString(u8"添加到热门DJ"),this,SLOT(slot_menu_renameList()));
                addlist_Menu->exec(QCursor::pos());
                delete addlist_Menu;
                addlist_Menu = nullptr;
            });

        }
        if(ui->listWidget_songerlist->count() > 0)//真的添加了内容
        {
            ui->stackedWidget_content->setCurrentWidget(ui->page_content);
            checkListCounts();
            emit sig_item_addeditems();
        }
    });

    //开关
    connect(ui->pushButton_switch,&QPushButton::clicked,[=](bool checked){
        qDebug() << QString(u8"status：") << checked;
        if(checked)
        {
            ui->stackedWidget_content->show();//显示
            checkListCounts();
        }
        else
        {
            ui->stackedWidget_content->hide();//隐藏
            setFixedHeight(ui->frame_ltitle->height());
        }
        m_switch = !m_switch;
        emit sig_item_expand(m_switch);
        qDebug() << QString(u8"open switch status：") << m_switch;
    });

    //右键菜单
    connect(ui->pushButton_rmenu,&QPushButton::clicked,[=](){
        const int x = ui->pushButton_rmenu->parentWidget()->mapToGlobal(ui->pushButton_rmenu->pos()).x();
        const int y = ui->pushButton_rmenu->parentWidget()->mapToGlobal(ui->pushButton_rmenu->pos()).y();
        m_rMenu->setGeometry(x-m_rMenu->width()+ui->pushButton_rmenu->width(),
                                  y+ui->pushButton_rmenu->height(),
                                  m_rMenu->width(),
                                  m_rMenu->height()+5);
        m_rMenu->exec();
//            m_rMenu->exec(QCursor::pos());
    });

    //滚动条
    connect(ui->listWidget_songerlist->verticalScrollBar(),&QScrollBar::valueChanged,[=](int value){
        emit sig_item_scrollbar(value);
    });

    //双击播放
//    connect(ui->listWidget_songerlist,&QListWidget::itemDoubleClicked,[=](QListWidgetItem *item){
//        emit sig_item_newPlaylist(m_id,m_playlist,item->data(Qt::UserRole+1).toString());
//        qDebug() <<QString(u8"当前item已被设定！点击的item名称：%1,真实路径：%2").arg(QFileInfo(item->data(Qt::UserRole+1).toString()).fileName()).arg(item->data(Qt::UserRole+1).toString());
//    });
}

void NewListItem::setInstallEventFilter()
{
    ui->label_listName->installEventFilter(this);
}

int NewListItem::getItemId() const
{
    return m_id;
}

void NewListItem::setItemId(int id)
{
    m_id = id;
}

QString NewListItem::getItemName() const
{
    return m_name;
}

QListWidget& NewListItem::getCurListWidget()
{
    return *ui->listWidget_songerlist;
}

void NewListItem::scrollItemToPosition()
{
    if(ui->listWidget_songerlist->currentItem() != nullptr)
        ui->listWidget_songerlist->scrollToItem(ui->listWidget_songerlist->currentItem(),QAbstractItemView::PositionAtCenter);
}

QList<QString> NewListItem::getPlaylist()
{
    return m_playlist;
}

void NewListItem::setListFold()
{
    checkListCounts();
    ui->stackedWidget_content->hide();//隐藏
    setFixedHeight(ui->frame_ltitle->height());
    ui->pushButton_switch->setChecked(false);
    m_switch = false;
}

void NewListItem::slot_setNodeCounts(int num)
{
    m_selfHeight = num;

    qDebug() << QString(u8"接收到的高度：%1").arg(m_selfHeight);
}

void NewListItem::slot_finishedRename()
{
    ui->stackedWidget_listName->setCurrentWidget(ui->page_name1);
    ui->label_listName->setText(ui->lineEdit_listName->text());
}

bool NewListItem::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    if(watched == ui->label_listName && event->type() == QEvent::MouseButtonDblClick && mouseEvent->buttons() & Qt::LeftButton)//左键双击
    {
        ui->lineEdit_listName->setFocus();
        ui->lineEdit_listName->selectAll();
        ui->stackedWidget_listName->setCurrentWidget(ui->page_name2);
    }
    else if(watched == ui->label_listName && event->type() == QEvent::MouseButtonPress && mouseEvent->buttons() & Qt::LeftButton)//左键单击
    {
        ui->pushButton_switch->click();
    }
    else if(watched == ui->label_listName && event->type() == QEvent::MouseButtonPress && mouseEvent->buttons() & Qt::RightButton)//右键单击
    {
//        ui->pushButton_rmenu->click();
    }

    return QWidget::eventFilter(watched,event);
}

void NewListItem::createRightMenu()
{
    m_rMenu = new QMenu();
    m_rMenu->setFixedWidth(95);
//    m_rMenu->setWindowFlags(Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);//圆角需要
//    m_rMenu->setAttribute(Qt::WA_TranslucentBackground);

    m_rMenu->setObjectName(QString::fromUtf8("listmanager_rMenu"));
    m_rMenu->addAction(QIcon(":/images/player/player_itemlist_add.png"),QString::fromLocal8Bit("新建列表"),this,SLOT(slot_menu_newList()));
    m_rMenu->addAction(QIcon(":/images/player/player_itemlist_delete.png"),QString::fromLocal8Bit("删除列表"),this,SLOT(slot_menu_deleteList()));
    m_rMenu->addAction(QIcon(":/images/music/song_clear.png"),QString::fromLocal8Bit("清空列表"),this,SLOT(slot_menu_clearList()));
    m_rMenu->addAction(QIcon("://images/player/player_itemlist_rename.png"),QString::fromLocal8Bit("重命名"),this,SLOT(slot_menu_renameList()));
}

void NewListItem::setFinishedStatus()
{
    switch (m_status)
    {
    case STA_FINISHED:
    {
        slot_finishedRename();//回车完成设置
    }
        break;
    case STA_UNFINISHED:
    {
        //保持默认
    }
        break;
    default:
        break;
    }
}

void NewListItem::checkListCounts()
{
    if(ui->listWidget_songerlist->count() == 0)
    {
        ui->stackedWidget_content->setCurrentWidget(ui->page_black);
        setFixedHeight(160);//固定的160
    }
    else
    {
        ui->stackedWidget_content->setCurrentWidget(ui->page_content);
        setFixedHeight(ui->listWidget_songerlist->count()*28 + ui->frame_ltitle->height());//这里的高度由父容器计算并实时通知（增加或者删除时都通知）
        qDebug() << QString(u8"items总高度大于视图区域，设置为了视图高度");
    }
}

bool NewListItem::getFoldStatus()
{
    return m_switch;
}

void NewListItem::slot_menu_newList()
{
    emit sig_item_create();
    qDebug() <<QString(u8"新建列表");
}

void NewListItem::slot_menu_deleteList()
{
    emit sig_item_delete();
    qDebug() <<QString(u8"删除列表");
}

void NewListItem::slot_menu_clearList()
{
//    emit sig_item_clear();
    ui->listWidget_songerlist->clear();
    checkListCounts();
    qDebug() <<QString(u8"清空列表");
}

void NewListItem::slot_menu_renameList()
{
//    emit sig_item_rename();
    ui->lineEdit_listName->setFocus();
    ui->lineEdit_listName->selectAll();
    ui->stackedWidget_listName->setCurrentWidget(ui->page_name2);
}
