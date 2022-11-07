#include "MusicPlaylist.h"
#include "ui_MusicPlaylist.h"
#include "database/dataBase.h"

#include <QMenu>
#include <QDebug>
#include <QPoint>
#include <QCheckBox>
#include <QHeaderView>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QAbstractItemModel>

MusicPlaylist::MusicPlaylist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlaylist)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

MusicPlaylist::~MusicPlaylist()
{
    delete ui;
    //    delete m_songAction;
}

void MusicPlaylist::initWorkUI()
{
    //    QIcon icon_clsong(":/images/icon/clear.png");
    //    m_songAction = new QAction();
    //    m_songAction->setObjectName(QString::fromLocal8Bit("m_songAction"));
    //    ui->lineEdit_searchSong->addAction(m_songAction, QLineEdit::TrailingPosition);// 右侧显示
    //    connect(m_songAction,&QAction::triggered,[=](){ui->lineEdit_searchSong->clear();});

    //创建下拉菜单
        ui->Btn_sort->setContextMenuPolicy(Qt::CustomContextMenu);
        ui->Btn_sort->setPopupMode(QToolButton::MenuButtonPopup);
        ui->Btn_sort->setToolButtonStyle(Qt::ToolButtonTextOnly);
        ui->Btn_sort->setAutoRaise(false);
        ui->Btn_sort->setAutoRepeat(false);
        ui->Btn_sort->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//文本显示在图标旁边（左右还得设置布局方式）
//        ui->Btn_sort->setArrowType(Qt::UpArrow);//箭头类型（上下左右）

        QMenu *menuSelection = new QMenu(this);
        menuSelection->setObjectName(QString(u8"menuSelection"));
        menuSelection->addAction(new QAction(QString(u8"默认排序")));
        menuSelection->addAction(new QAction(QString(u8"按歌名")));
        menuSelection->addAction(new QAction(QString(u8"按歌手")));
        menuSelection->addAction(new QAction(QString(u8"按专辑")));
        menuSelection->addAction(new QAction(QString(u8"按音质")));
//        ui->Btn_sort->setDefaultAction(menuSelection->actions().at(0));//默认是 默认排序选项 不设置就没有
        ui->Btn_sort->setText(QString(u8"默认排序"));
        ui->Btn_sort->setIcon(QIcon("://images/music/song_default.png"));
        ui->Btn_sort->setMenu(menuSelection);//点击右侧小箭头才弹出

        connect(menuSelection,&QMenu::triggered,[=](QAction *action){
            setToolButtonTextAndIcon(action);
        });


        //点击歌手排序
        ui->checkBox_song->setLayoutDirection(Qt::RightToLeft);
         //三种状态
        ui->checkBox_song->setTristate(true);

        //三种状态
        ui->checkBox_selectall->setTristate(false);

        //全选标签（默认）
        ui->stackedWidget_select->setCurrentIndex(0);

        ui->listWidget_songer->setViewMode(QListView::ListMode);
        ui->listWidget_songer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        ui->listWidget_songer->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
        ui->listWidget_songer->setContextMenuPolicy(Qt::CustomContextMenu);//自定义菜单

        ui->lineEdit_searchSong->setEnabled(false);//空时不能搜索
        ui->tableView_songList->setMouseTracking(true);
        ui->tableView_songList->setContextMenuPolicy(Qt::CustomContextMenu);
        ui->lineEdit_searchSong->setPlaceholderText(QString::fromLocal8Bit("搜索想听的歌曲吧^_^"));
        ui->tableView_songList->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格不可编辑
        ui->tableView_songList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        delegate = new Delegate(this);
        connect(this,&MusicPlaylist::hoverIndexChanged,delegate,&Delegate::onHoverIndexChanged);
    //    ui->tableView_songList->setItemDelegate(delegate);//使用自定义代理

    //    ui->Btn_inStep->setFlat(true);
    //    ui->Btn_edit->setFlat(true);
        ui->tabWidget->setCurrentIndex(0);
        QStringList list;
        list << "1" << "2";
        slots_addSonersToPage2(list);
        ui->label_order->setText(QString::number(ui->listWidget_songer->count()));
}

void MusicPlaylist::handleSignalsAndSlots()
{
    connect(ui->Btn_batch,&QPushButton::clicked,this,&MusicPlaylist::slots_btnBatchToNewUi);//批量操作
    connect(ui->Btn_bath_exit,&QPushButton::clicked,this,&MusicPlaylist::slots_btnBatchToNewUiExit);//退出批量操作
    connect(ui->lineEdit_searchSong,&QLineEdit::textChanged,this,&MusicPlaylist::selectTableAboutSongName);
    connect(ui->tableView_songList,SIGNAL(clicked(QModelIndex)),this,SLOT(slots_selectRowIndex(QModelIndex)));
//    connect(ui->Btn_sort,&QPushButton::clicked,this,&MusicPlaylist::slots_btnSortCustomMenu);
    //选择排序
    connect(ui->Btn_sort,&QToolButton::triggered,[=](QAction *action){
        setToolButtonTextAndIcon(action);
    });

    //排序按钮点击（默认是恢复到默认设置的选项,现改为弹出菜单）
    connect(ui->Btn_sort,&QToolButton::clicked,[=](){
        QPoint menuPoint = QPoint(ui->Btn_sort->parentWidget()->mapToGlobal(ui->Btn_sort->pos()).x(),
                                  ui->Btn_sort->parentWidget()->mapToGlobal(ui->Btn_sort->pos()).y()+ui->Btn_sort->height()+2);
        ui->Btn_sort->menu()->exec(menuPoint);
    });

    //歌名排序（normal desc asc）
    connect(ui->checkBox_song,&QCheckBox::stateChanged,[=](int status){
        if(status == 1)
        {
        //半选中--desc
            qDebug() << QString(u8"歌名排序按钮选中状态：升序");
        }
        else if(status == 2)
        {
        //选中--asc
            qDebug() << QString(u8"歌名排序按钮选中状态：降序");
        }
        else if(status == 0)
        {
        //未选中状态---normal
            qDebug() << QString(u8"歌名排序按钮选中状态：正常");
        }
    });

    //全选/不全选
    connect(ui->checkBox_selectall,&QCheckBox::clicked,[=](bool checked){
        if(checked)
        {
            for(int i = 0; i < ui->listWidget_songer->count(); i++)
            {
                getItem_CheckBox(ui->listWidget_songer->item(i),"checkBox")->setChecked(true);
            }
        }
        else
        {
            for(int i = 0; i < ui->listWidget_songer->count(); i++)
            {
                getItem_CheckBox(ui->listWidget_songer->item(i),"checkBox")->setChecked(false);
            }
        }
    });

    //全选
    connect(ui->label_order,&QPushButton::clicked,[=](){
        for(int i = 0; i < ui->listWidget_songer->count(); i++)
        {
            QWidget *widget = ui->listWidget_songer->itemWidget(ui->listWidget_songer->item(i));//此时的item是删除后已经排好序的
            QStackedWidget* stack_num = widget->findChild<QStackedWidget*>("stackedWidget_num");
            if(stack_num != nullptr)
            stack_num->setCurrentIndex(1);
            getItem_CheckBox(ui->listWidget_songer->item(i),"checkBox")->setChecked(true);
        }
        ui->stackedWidget_select->setCurrentIndex(1);
        ui->checkBox_selectall->setChecked(true);
    });

    //更新歌曲总数

}

void MusicPlaylist::setInstallEventFilter()
{
    ui->listWidget_songer->installEventFilter(this);
}

void MusicPlaylist::sortCurrentIndex(int index)
{
    int count = ui->listWidget_songer->count();//删除后的item总数
    for(int i = index-1; i < count-index+1; i++)
    {
        QWidget *widget = ui->listWidget_songer->itemWidget(ui->listWidget_songer->item(i));//此时的item是删除后已经排好序的
        QLabel* label_sort = widget->findChild<QLabel*>("label_order");
        qDebug() << label_sort->text();
        label_sort->setText(addPrefixNum(QString::number(i+1)));
    }
}

QString MusicPlaylist::addPrefixNum(QString num)
{
    if(num.length() == 1)
    {
        return QString::fromLocal8Bit("00")+num;
    }
    else if(num.length() == 2)
    {
        return QString::fromLocal8Bit("0")+num;
    }
    else
    {
        return num;
    }
}

/*过滤事件*/
bool MusicPlaylist::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_songer)
    {
        if(event->type() == QEvent::Resize)
        {
            ui->listWidget_songer->updateGeometry();
        }
    }
    return QWidget::eventFilter(watched,event);
}

/*判断播放列表是否为空*/
bool MusicPlaylist::playerListIsNull()
{
    return 0;
}

void MusicPlaylist::addFileInfoToListView()
{
    qDebug() << "model data received data from multipplayer";
//    model_songInfo->clear();//加载前先清空上次模型中存放的内容,交给数据库
    //列名称必须与数据库中字段对应上，否则使用其他的只读模型
    model_songInfo = new QSqlTableModel(this,dataBase::getSqlDataBase());//数据库能连接上，且是打开的
    model_songInfo->setTable("localmusic");//注意表名区分大小写
    model_songInfo->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("歌曲序号"));
    model_songInfo->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("歌曲名称"));
    model_songInfo->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("本地路径"));
    model_songInfo->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("歌曲音质"));
//    model_songInfo->removeColumn(1);
//    model_songInfo->canFetchMore();//默认加载256条数据，加载更多需要使用这个函数
    ui->tableView_songList->setModel(model_songInfo);
    model_songInfo->select();

    ui->tableView_songList->verticalHeader()->hide();//隐藏第0列
    ui->tableView_songList->resizeRowsToContents();//行高度自适应

    ui->tableView_songList->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);//垂直表头固定高度
    ui->tableView_songList->verticalHeader()->setDefaultSectionSize(26);
//    ui->tableView_songList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//自动调整列宽
    ui->tableView_songList->setSelectionBehavior(QAbstractItemView::SelectRows);//只能行选择

    //setSectionResizeMode(QHeaderView::ResizeToContents)
    //interactive（互动的）,Stretch（等宽）,Fixed（固定）,ResizeToContents（根据内容调整）,Custom（自定义）
    //以下代码实现对各列(section)的自定义规则分配，记得包含头文件 QHeaderView
    //2021-12-06：出现QHeaderView报错，注释
    ui->tableView_songList->setColumnWidth(0,75);
    ui->tableView_songList->setColumnWidth(1,350);
    ui->tableView_songList->setColumnWidth(2,350);
    ui->tableView_songList->setColumnWidth(3,75);
    ui->tableView_songList->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tableView_songList->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableView_songList->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);
    ui->tableView_songList->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);

    ui->tableView_songList->show();
    ui->lineEdit_searchSong->setEnabled(true);
    qDebug()<<"all rowcount ="<<model_songInfo->rowCount();
    qDebug()<<"now page columncount ="<<model_songInfo->columnCount();
}

void MusicPlaylist::selectTableAboutSongName(QString name)
{
    name.remove(QRegExp("\\s"));
    if(name.isEmpty())
    {
        for(int i = 0; i < ui->tableView_songList->model()->rowCount(); i++)
            ui->tableView_songList->setRowHidden(i,false);
    }
    else
    {
        for(int i = 0; i <ui->tableView_songList->model()->rowCount(); i++)
        {
            ui->tableView_songList->setRowHidden(i,true);
            QString curname = "";
            QAbstractItemModel *model = ui->tableView_songList->model();
            QModelIndex index;
            for(int j = 0; j <ui->tableView_songList->model()->columnCount(); j++)
            {
                index = model->index(i,j);
                curname += model->data(index).toString();
            }
            curname.remove(QRegExp("\\s"));
            if(curname.contains(name,Qt::CaseInsensitive)) //CaseSensitive:敏感
               ui->tableView_songList->setRowHidden(i,false);
        }
    }

//    QSqlTableModel * model = new QSqlTableModel(this);//新建model
//        model->setTable("LocalMusic");//设置表
//        if(!name.isEmpty())//搜索栏为空
//            model->setFilter("MusicName ='"+name+"'");//model过滤表中符合的数据
//        ui->tableView_songList->setModel(model);
//        model->select();//显示修改后的数据

}

void MusicPlaylist::on_tableView_songList_entered(const QModelIndex &index)
{
    emit hoverIndexChanged(index);
}

void MusicPlaylist::slots_selectRowIndex(const QModelIndex &index)
{
//    emit sig_selectRowIndex(index);
    //    qDebug()<<index.data().toString();
}

void MusicPlaylist::slots_btnSortCustomMenu()
{
    QMenu *pmenu_sort = new QMenu(this);
    pmenu_sort->setObjectName(QString::fromLocal8Bit("pmenu_sort"));
    pmenu_sort->addAction(QString::fromLocal8Bit("默认排序"),this,SLOT(slots_btnSortAscOrder()));
    pmenu_sort->addSeparator();
    pmenu_sort->addAction(QString::fromLocal8Bit("按歌名"),this,SLOT(slots_btnSortDescOrder()));
    pmenu_sort->addSeparator();
    pmenu_sort->addAction(QString::fromLocal8Bit("按歌手"),this,SLOT(slots_btnSortDescOrder()));
    pmenu_sort->addSeparator();
    pmenu_sort->addAction(QString::fromLocal8Bit("按专辑"),this,SLOT(slots_btnSortDescOrder()));
    pmenu_sort->addSeparator();
    pmenu_sort->addAction(QString::fromLocal8Bit("按音质"),this,SLOT(slots_btnSortDescOrder()));

    QPoint point4 = QPoint(QCursor::pos().x()-50,QCursor::pos().y()+25);
    pmenu_sort->exec(point4);
    delete pmenu_sort;
}

void MusicPlaylist::slots_btnSortAscOrder()
{
    //模型需要有数据，否则报错
    if(model_songInfo->rowCount() != 0)
    {
        model_songInfo->setSort(0,Qt::AscendingOrder);
        model_songInfo->select();
    }
}

void MusicPlaylist::slots_btnSortDescOrder()
{
    if(model_songInfo->rowCount() != 0)
    {
        model_songInfo->setSort(1,Qt::DescendingOrder);
        model_songInfo->select();
    }
}

void MusicPlaylist::slots_btnBatchToNewUi()
{
    ui->stackedWidget_3->setCurrentIndex(1);
    qDebug()<<"enter frame_batch";
}

void MusicPlaylist::slots_btnBatchToNewUiExit()
{
    ui->stackedWidget_3->setCurrentIndex(0);
    qDebug()<<"exit frame_batch";
}

void MusicPlaylist::slots_btnBatchModelUpdate()
{

}

/*不用关联直接邮件可以打开*/
void MusicPlaylist::on_tableView_songList_customContextMenuRequested(const QPoint &pos)
{
//    if(model_songInfo->rowCount() < 0) return;
    Q_UNUSED(pos);
    QMenu *pmenu_right = new QMenu(this);
    pmenu_right->setObjectName(QString::fromUtf8("pmenu_right"));
    QMenu *pmenu_addto = new QMenu(QString::fromLocal8Bit("添加到"));
    pmenu_addto->setObjectName(QString::fromUtf8("pmenu_addto"));
    QMenu *pmenu_moveto = new QMenu(QString::fromLocal8Bit("移动到"));
    pmenu_moveto->setObjectName(QString::fromUtf8("pmenu_moveto"));
    pmenu_addto->addAction(QString::fromLocal8Bit("本地列表"),this,SLOT(slots_rightMenu_player()));
    pmenu_addto->addAction(QString::fromLocal8Bit("云端列表"),this,SLOT(slots_rightMenu_player()));
    pmenu_moveto->addAction(QString::fromLocal8Bit("我的收藏"),this,SLOT(slots_rightMenu_player()));
    pmenu_moveto->addAction(QString::fromLocal8Bit("我的喜好"),this,SLOT(slots_rightMenu_player()));
    pmenu_right->addAction(QString::fromLocal8Bit("播放"),this,SLOT(slots_rightMenu_player()));
    pmenu_right->addSeparator();
    pmenu_right->addAction(QString::fromLocal8Bit("删除"),this,SLOT(slots_rightMenu_delete()));
    pmenu_right->addSeparator();
    pmenu_right->addAction(QString::fromLocal8Bit("下载"),this,SLOT(slots_rightMenu_download()));
    pmenu_right->addSeparator();
    pmenu_right->addAction(QString::fromLocal8Bit("下一首"),this,SLOT(slots_rightMenu_next()));
    pmenu_right->addSeparator();
    pmenu_right->addMenu(pmenu_addto);
    pmenu_right->addSeparator();
    pmenu_right->addMenu(pmenu_moveto);
    pmenu_right->addSeparator();
    pmenu_right->addAction(QString::fromLocal8Bit("清空列表"),this,SLOT(slots_rightMenu_clearAllList()));
    pmenu_right->addSeparator();
    pmenu_right->addAction(QString::fromLocal8Bit("文件路径"),this,SLOT(slots_rightMenu_openFilePath()));
    pmenu_right->addSeparator();
    pmenu_right->exec(QCursor::pos());
    delete pmenu_right;
}

/*不用关联直接右键可以打开*/
void MusicPlaylist::on_listWidget_songer_customContextMenuRequested(const QPoint &pos)
{
    if(ui->listWidget_songer->count() == 0) return;
    Q_UNUSED(pos);
    QMenu *pmenu_songer = new QMenu(this);
    pmenu_songer->setObjectName(QString::fromLocal8Bit("pmenu_songer"));
    QMenu *pmenu_son_addto = new QMenu(QString::fromLocal8Bit("添加到"));
    pmenu_son_addto->setObjectName(QString::fromLocal8Bit("pmenu_son_addto"));
    pmenu_son_addto->setIcon(QIcon("://images/music/song_add.png"));
    QMenu *pmenu_son_sort = new QMenu(QString::fromLocal8Bit("歌曲排序"));
    pmenu_son_sort->setObjectName(QString::fromLocal8Bit("pmenu_son_sort"));
    pmenu_son_sort->setIcon(QIcon("://images/music/song_order.png"));
    QMenu *pmenu_son_playmode = new QMenu(QString::fromLocal8Bit("播放模式"));
    pmenu_son_playmode->setObjectName(QString::fromLocal8Bit("pmenu_son_playmode"));
    pmenu_son_playmode->setIcon(QIcon("://images/music/song_playmode.png"));
    QMenu *pmenu_son_muctool = new QMenu(QString::fromLocal8Bit("音乐工具"));
    pmenu_son_muctool->setObjectName(QString::fromLocal8Bit("pmenu_son_muctool"));
    pmenu_son_muctool->setIcon(QIcon("://images/music/song_tools.png"));

    pmenu_son_addto->addAction(QString::fromLocal8Bit("本地列表"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_addto->addAction(QString::fromLocal8Bit("云端列表"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_addto->addAction(QString::fromLocal8Bit("我的收藏"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_addto->addAction(QString::fromLocal8Bit("我的喜好"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_addto->addAction(QString::fromLocal8Bit("播放列表"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_addto->addAction(QString::fromLocal8Bit("默认列表"),this,SLOT(slots_rightMenu_player()));

    pmenu_son_sort->addAction(QString::fromLocal8Bit("默认排序"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_sort->addAction(QString::fromLocal8Bit("按歌名"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_sort->addAction(QString::fromLocal8Bit("按歌手"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_sort->addAction(QString::fromLocal8Bit("按专辑"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_sort->addAction(QString::fromLocal8Bit("按音质"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_sort->addAction(QString::fromLocal8Bit("随机"),this,SLOT(slots_rightMenu_player()));

    pmenu_son_playmode->addAction(QString::fromLocal8Bit("单曲播放"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_playmode->addAction(QString::fromLocal8Bit("单曲循环"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_playmode->addAction(QString::fromLocal8Bit("顺序播放"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_playmode->addAction(QString::fromLocal8Bit("循环播放"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_playmode->addAction(QString::fromLocal8Bit("随机播放"),this,SLOT(slots_rightMenu_player()));

    pmenu_son_muctool->addAction(QString::fromLocal8Bit("制作铃声"),this,SLOT(slots_rightMenu_player()));
    pmenu_son_muctool->addAction(QString::fromLocal8Bit("定时关机"),this,SLOT(slots_rightMenu_player()));

    pmenu_songer->addAction(QIcon("://images/music/song_play.png"),QString::fromLocal8Bit("播放"),this,SLOT(slots_rightMenu_player()));
    pmenu_songer->addAction(QIcon("://images/music/song_next.png"),QString::fromLocal8Bit("下一首播放"),this,SLOT(slots_rightMenu_delete()));
    pmenu_songer->addAction(QIcon("://images/music/song_mv.png"),QString::fromLocal8Bit("播放MV"),this,SLOT(slots_rightMenu_download()));
    pmenu_songer->addSeparator();
    pmenu_songer->addAction(QIcon("://images/music/song_download.png"),QString::fromLocal8Bit("下载"),this,SLOT(slots_rightMenu_next()));
    pmenu_songer->addAction(QIcon("://images/music/song_collect.png"),QString::fromLocal8Bit("我要收藏"),this,SLOT(slots_rightMenu_next()));
    pmenu_songer->addAction(QIcon("://images/music/song_share.png"),QString::fromLocal8Bit("分享"),this,SLOT(slots_rightMenu_next()));
    pmenu_songer->addAction(QIcon("://images/music/song_chuange.png"),QString::fromLocal8Bit("传歌"),this,SLOT(slots_rightMenu_next()));
    pmenu_songer->addMenu(pmenu_son_addto);
    pmenu_songer->addAction(QIcon("://images/music/song_commit.png"),QString::fromLocal8Bit("查看评论"),this,SLOT(slots_rightMenu_next()));
    pmenu_songer->addAction(QIcon("://images/music/song_delete.png"),QString::fromLocal8Bit("删除"),this,SLOT(slots_rightMenu_next()));
    pmenu_songer->addMenu(pmenu_son_sort);
    pmenu_songer->addSeparator();
    pmenu_songer->addMenu(pmenu_son_playmode);
    pmenu_songer->addAction(QIcon("://images/music/song_clear.png"),QString::fromLocal8Bit("清空歌单"),this,SLOT(slots_rightMenu_clearAllList()));
    pmenu_songer->addMenu(pmenu_son_muctool);
    pmenu_songer->exec(QCursor::pos());
    delete pmenu_songer;
}

//播放
void MusicPlaylist::slot_listWidget_songer_Play()
{

}

//播放MV
void MusicPlaylist::slot_listWidget_songer_MV()
{

}

//收藏
void MusicPlaylist::slot_listWidget_songer_Collect()
{

}

//下载
void MusicPlaylist::slot_listWidget_songer_Download()
{

}

//删除
void MusicPlaylist::slot_listWidget_songer_Delete(QListWidget *listWgt, QWidget *itemWgt, QListWidgetItem *item)
{
    itemWgt->deleteLater();
    listWgt->takeItem(listWgt->row(item));
    delete item;
    slot_listWidget_songer_sort(listWgt);
}

//删除后排序
void MusicPlaylist::slot_listWidget_songer_sort(QListWidget *listWgt)
{
    int itemCounts = listWgt->count();
    if(itemCounts  == 0) return;
    for(int i = 0; i < itemCounts; i++)
    {
        getItem_Label(listWgt->item(i),"label_order")->setText(addPrefixNum(QString::number(i+1)));
    }
}

//更多信息
void MusicPlaylist::slot_listWidget_songer_More()
{

}

//音质
void MusicPlaylist::slot_listWidget_songer_Quality()
{

}

void MusicPlaylist::slot_updateSongerAllCounts()
{
    ui->label_order->setText(QString::number(ui->listWidget_songer->count()));
}

QPushButton *MusicPlaylist::getItem_Button(QListWidgetItem *item, const QString &objname)
{
    QWidget* itemWidget = item->listWidget()->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QPushButton *itemBtn = itemWidget->findChild<QPushButton*>(objname);//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != itemBtn)
        return itemBtn;
    }
}

QLabel *MusicPlaylist::getItem_Label(QListWidgetItem *item, const QString &objname)
{
    QWidget* itemWidget = item->listWidget()->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QLabel *itemLabel = itemWidget->findChild<QLabel*>(objname);//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != itemLabel)
        return itemLabel;
    }
}

QCheckBox *MusicPlaylist::getItem_CheckBox(QListWidgetItem *item, const QString &objname)
{
    QWidget* itemWidget = item->listWidget()->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QCheckBox *itemCheckBox = itemWidget->findChild<QCheckBox*>(objname);//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != itemCheckBox)
        return itemCheckBox;
    }
}

void MusicPlaylist::setToolButtonTextAndIcon(const QAction *action)
{
    if(action->text() == QString(u8"默认排序"))
    {
        ui->Btn_sort->setIcon(QIcon("://images/music/song_default.png"));
    }
    else if(action->text() == QString(u8"按歌名"))
    {
        ui->Btn_sort->setIcon(QIcon("://images/music/song_songName.png"));
    }
    else if(action->text() == QString(u8"按歌手"))
    {
        ui->Btn_sort->setIcon(QIcon("://images/music/song_songer.png"));
    }
    else if(action->text() == QString(u8"按专辑"))
    {
        ui->Btn_sort->setIcon(QIcon("://images/music/song_album.png"));
    }
    else if(action->text() == QString(u8"按音质"))
    {
        ui->Btn_sort->setIcon(QIcon("://images/music/song_quality.png"));
    }
    ui->Btn_sort->setText(action->text());
}


/*播放当前歌曲*/
void MusicPlaylist::slots_rightMenu_player()
{
    qDebug()<<"this is the play";
}

/*删除当前歌曲*/
void MusicPlaylist::slots_rightMenu_delete()
{
    int curRow = ui->tableView_songList->currentIndex().row();
    model_songInfo->removeRow(curRow);
    model_songInfo->submitAll();//提交数据库，数据库数据变更
    ui->tableView_songList->reset();
//    ui->tableView_songList->setModel(model_songInfo);//不用再次绑定，绑定一次就可以
    model_songInfo->select();//这句是更新界面的重点
}

/*下载当前歌曲*/
void MusicPlaylist::slots_rightMenu_download()
{
    qDebug()<<"this is the download";
}

/*清空整张列表*/
void MusicPlaylist::slots_rightMenu_clearAllList()
{
    ui->listWidget_songer->clear();
    qDebug()<<"this is the clearAllList";
}

/*播放下一首歌曲*/
void MusicPlaylist::slots_rightMenu_next()
{
    qDebug()<<"this is the next";
}

/*复制当前歌曲信息到另一张表*/
void MusicPlaylist::slots_rightMenu_addtolist()
{
    qDebug()<<"this is the addtolist";
}

/*移动当前歌曲至另一张表*/
void MusicPlaylist::slots_rightMenu_movetolist()
{
    qDebug()<<"this is the movetolist";
//    if(curIndex.isValid())
//    {
//        QMessageBox::information(this,"menu","movetolist");
    //    }
}

void MusicPlaylist::slots_rightMenu_openFilePath()
{
    qDebug()<<"this is the openfilepath";
}

/*public槽函数：page2添加内容*/
bool MusicPlaylist::slots_addSonersToPage2(const QStringList &list)
{
    Q_UNUSED(list);
    for(int i = 0; i < 100; i++)
    {
        QListWidgetItem  *item  = new QListWidgetItem(ui->listWidget_songer);
        SongItemForm *son_item = new SongItemForm(QString(u8"%1").arg(i+1),
                                                  QString(u8"林俊杰&&张英俊&&张辉&&群星&&广而告知大众"),
                                                  true,
                                                  false,
                                                  QString(u8"林俊杰&&周杰伦&&高进&&小沈阳&&沈春阳&&李宇春&&孙燕姿"),
                                                  QString(u8"听妈妈的话不让妈妈受伤，让世界都有一份真挚的爱在身边"),
                                                  QString(u8"无损音质"),
                                                  this);
        item->setSizeHint(QSize(ITEMSIZE)+ QSize(0,1));//在此可以微调整item的宽高
        ui->listWidget_songer->addItem(item);
        ui->listWidget_songer->setItemWidget(item,son_item);


        //播放
        connect(son_item,&SongItemForm::sig_son_playbtn_clicked,[=](int index){
            slot_listWidget_songer_Play();
            qDebug() << "received on_son_playbtn_clicked = " << index;
        });
        //播放视频MV
        connect(son_item,&SongItemForm::sig_son_mvbtn_clicked,[=](int index){
            slot_listWidget_songer_MV();
            qDebug() << "received on_son_mvbtn_clicked = " << index;
        });
        //收藏
        connect(son_item,&SongItemForm::sig_son_collectbtn_clicked,[=](int index){
            slot_listWidget_songer_Collect();
            qDebug() << "received on_son_collectbtn_clicked = " << index;
        });
        //删除
        connect(son_item,&SongItemForm::sig_son_deletebtn_clicked,[=](int index){//index总是比真实索引大1
            slot_listWidget_songer_Delete(ui->listWidget_songer,son_item,item);
            qDebug() << "received on_son_deletebtn_clicked = " << index;

        });
        //下载
        connect(son_item,&SongItemForm::sig_son_downloadbtn_clicked,[=](int index){
            slot_listWidget_songer_Download();
            qDebug() << "received on_son_downloadbtn_clicked = " << index;
        });
        //更多信息
        connect(son_item,&SongItemForm::sig_son_morebtn_clicked,[=](int index){
            slot_listWidget_songer_More();
            qDebug() << "received on_son_morebtn_clicked = " << index;
        });

        //音质
        connect(son_item,&SongItemForm::sig_son_qualityBtn_clicked,[=](int index){
            slot_listWidget_songer_More();
            qDebug() << "received on_son_qualitybtn_clicked = " << index;
        });
    }

    return 0;
}


