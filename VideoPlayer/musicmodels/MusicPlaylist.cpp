#include "MusicPlaylist.h"
#include "ui_MusicPlaylist.h"
#include <QMenu>
#include <QDebug>
#include <QPoint>
#include <QHeaderView>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QAbstractItemModel>

MusicPlaylist::MusicPlaylist(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlaylist)
{
    ui->setupUi(this);
//    QIcon icon_clsong(":/images/icon/clear.png");
//    m_songAction = new QAction();
//    m_songAction->setObjectName(QString::fromLocal8Bit("m_songAction"));
//    ui->lineEdit_searchSong->addAction(m_songAction, QLineEdit::TrailingPosition);// 右侧显示
//    connect(m_songAction,&QAction::triggered,[=](){ui->lineEdit_searchSong->clear();});

    ui->listWidget_songer->installEventFilter(this);
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

    connect(ui->Btn_batch,&QPushButton::clicked,this,&MusicPlaylist::slots_btnBatchToNewUi);//批量操作
    connect(ui->Btn_bath_exit,&QPushButton::clicked,this,&MusicPlaylist::slots_btnBatchToNewUiExit);//退出批量操作
    connect(ui->lineEdit_searchSong,&QLineEdit::textChanged,this,&MusicPlaylist::selectTableAboutSongName);
    connect(ui->tableView_songList,SIGNAL(clicked(QModelIndex)),this,SLOT(slots_selectRowIndex(QModelIndex)));
    connect(ui->Btn_sort,&QPushButton::clicked,this,&MusicPlaylist::slots_btnSortCustomMenu);

    connect(ui->listWidget_songer,&QListWidget::itemClicked,[=](){
        qDebug() << "ui->listWidget_songer itemClicked";
    });

    connect(ui->listWidget_songer,&QListWidget::itemDoubleClicked,[=](){
        qDebug() << "ui->listWidget_songer itemDoubleClicked";
    });

    connect(ui->listWidget_songer,&QListWidget::itemChanged,[=](){
        qDebug() << "ui->listWidget_songer itemChanged";
    });

    connect(ui->listWidget_songer,&QListWidget::itemEntered,[=](){
        qDebug() << "ui->listWidget_songer itemEntered";
    });

    connect(ui->listWidget_songer,&QListWidget::itemPressed,[=](){
        qDebug() << "ui->listWidget_songer itemPressed";
    });


    QStringList list;
    list << "1" << "2";
    slots_addSonersToPage2(list);
}

MusicPlaylist::~MusicPlaylist()
{
    delete ui;
    //    delete m_songAction;
}

/*过滤事件*/
bool MusicPlaylist::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched,event);
}

/*判断播放列表是否为空*/
bool MusicPlaylist::playerListIsNull()
{
    return 0;
}

void MusicPlaylist::addFileInfoToListView()
{
//    model_songInfo->clear();//加载前先清空上次模型中存放的内容,交给数据库
    //列名称必须与数据库中字段对应上，否则使用其他的只读模型
    model_songInfo = new QSqlTableModel(this);
    model_songInfo->setTable("LocalMusic");
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

//    ui->tableView_songList->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);//自动调整列宽
    ui->tableView_songList->setSelectionBehavior(QAbstractItemView::SelectRows);//只能行选择

    //setSectionResizeMode(QHeaderView::ResizeToContents)
    //interactive（互动的）,Stretch（等宽）,Fixed（固定）,ResizeToContents（根据内容调整）,Custom（自定义）
    //一下代码实现对各列(section)的自定义规则分配，记得包含头文件 QHeaderView
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
    pmenu_sort->setStyleSheet("font-size:12px;"
                              "background-color:#3d3d3d;"
                              "color:green;");//font:bold italic 18px "微软雅黑";
    pmenu_sort->addAction(QString::fromLocal8Bit("升序"),this,SLOT(slots_btnSortAscOrder()));
    pmenu_sort->addSeparator();
    pmenu_sort->addAction(QString::fromLocal8Bit("降序"),this,SLOT(slots_btnSortDescOrder()));
    ui->Btn_sort->setContextMenuPolicy(Qt::CustomContextMenu);
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
    Q_UNUSED(pos);
    QMenu *pmenu_right = new QMenu(this);
    QMenu *pmenu_addto = new QMenu(QString::fromLocal8Bit("添加到"));
    QMenu *pmenu_moveto = new QMenu(QString::fromLocal8Bit("移动到"));
    pmenu_addto->addAction(QString::fromLocal8Bit("本地列表"),this,SLOT(slots_rightMenu_player()));
    pmenu_addto->addAction(QString::fromLocal8Bit("云端列表"),this,SLOT(slots_rightMenu_player()));
    pmenu_moveto->addAction(QString::fromLocal8Bit("我的收藏"),this,SLOT(slots_rightMenu_player()));
    pmenu_moveto->addAction(QString::fromLocal8Bit("我的喜好"),this,SLOT(slots_rightMenu_player()));
    pmenu_right->setStyleSheet("font-size:12px;"
                               "background-color:#3d3d3d;"
                               "color:green;");//font:bold italic 18px "微软雅黑";
    pmenu_addto->setStyleSheet("font-size:12px;"
                               "background-color:#3d3d3d;"
                               "color:green;");//font:bold italic 18px "微软雅黑";
    pmenu_moveto->setStyleSheet("font-size:12px;"
                               "background-color:#3d3d3d;"
                               "color:green;");//font:bold italic 18px "微软雅黑";
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
    Q_UNUSED(pos);
    QMenu *pmenu_songer = new QMenu(this);
    QMenu *pmenu_addto = new QMenu(QString::fromLocal8Bit("添加到"));
    QMenu *pmenu_sort = new QMenu(QString::fromLocal8Bit("歌曲排序"));
    QMenu *pmenu_playmode = new QMenu(QString::fromLocal8Bit("播放模式"));
    QMenu *pmenu_muctool = new QMenu(QString::fromLocal8Bit("音乐工具"));

    pmenu_addto->addAction(QString::fromLocal8Bit("本地列表"),this,SLOT(slots_rightMenu_player()));
    pmenu_addto->addAction(QString::fromLocal8Bit("云端列表"),this,SLOT(slots_rightMenu_player()));
    pmenu_addto->addAction(QString::fromLocal8Bit("我的收藏"),this,SLOT(slots_rightMenu_player()));
    pmenu_addto->addAction(QString::fromLocal8Bit("我的喜好"),this,SLOT(slots_rightMenu_player()));
    pmenu_addto->addAction(QString::fromLocal8Bit("播放列表"),this,SLOT(slots_rightMenu_player()));
    pmenu_addto->addAction(QString::fromLocal8Bit("默认列表"),this,SLOT(slots_rightMenu_player()));

    pmenu_sort->addAction(QString::fromLocal8Bit("默认排序"),this,SLOT(slots_rightMenu_player()));
    pmenu_sort->addAction(QString::fromLocal8Bit("按歌名"),this,SLOT(slots_rightMenu_player()));
    pmenu_sort->addAction(QString::fromLocal8Bit("按歌手"),this,SLOT(slots_rightMenu_player()));
    pmenu_sort->addAction(QString::fromLocal8Bit("按专辑"),this,SLOT(slots_rightMenu_player()));
    pmenu_sort->addAction(QString::fromLocal8Bit("按音质"),this,SLOT(slots_rightMenu_player()));
    pmenu_sort->addAction(QString::fromLocal8Bit("随机"),this,SLOT(slots_rightMenu_player()));

    pmenu_playmode->addAction(QString::fromLocal8Bit("单曲播放"),this,SLOT(slots_rightMenu_player()));
    pmenu_playmode->addAction(QString::fromLocal8Bit("单曲循环"),this,SLOT(slots_rightMenu_player()));
    pmenu_playmode->addAction(QString::fromLocal8Bit("顺序播放"),this,SLOT(slots_rightMenu_player()));
    pmenu_playmode->addAction(QString::fromLocal8Bit("循环播放"),this,SLOT(slots_rightMenu_player()));
    pmenu_playmode->addAction(QString::fromLocal8Bit("随机播放"),this,SLOT(slots_rightMenu_player()));

    pmenu_muctool->addAction(QString::fromLocal8Bit("制作铃声"),this,SLOT(slots_rightMenu_player()));
    pmenu_muctool->addAction(QString::fromLocal8Bit("定时关机"),this,SLOT(slots_rightMenu_player()));

    pmenu_songer->setStyleSheet("font-size:12px;"
                               "background-color:#3d3d3d;"
                               "color:green;");//font:bold italic 18px "微软雅黑";
    pmenu_addto->setStyleSheet("font-size:12px;"
                               "background-color:#3d3d3d;"
                               "color:green;");//font:bold italic 18px "微软雅黑";
    pmenu_sort->setStyleSheet("font-size:12px;"
                               "background-color:#3d3d3d;"
                               "color:green;");//font:bold italic 18px "微软雅黑";
    pmenu_playmode->setStyleSheet("font-size:12px;"
                               "background-color:#3d3d3d;"
                               "color:green;");//font:bold italic 18px "微软雅黑";
    pmenu_muctool->setStyleSheet("font-size:12px;"
                               "background-color:#3d3d3d;"
                               "color:green;");//font:bold italic 18px "微软雅黑";

    pmenu_songer->addAction(QString::fromLocal8Bit("播放"),this,SLOT(slots_rightMenu_player()));
    pmenu_songer->addAction(QString::fromLocal8Bit("下一首播放"),this,SLOT(slots_rightMenu_delete()));
    pmenu_songer->addAction(QString::fromLocal8Bit("播放MV"),this,SLOT(slots_rightMenu_download()));
    pmenu_songer->addSeparator();
    pmenu_songer->addAction(QString::fromLocal8Bit("下载"),this,SLOT(slots_rightMenu_next()));
    pmenu_songer->addAction(QString::fromLocal8Bit("我要收藏"),this,SLOT(slots_rightMenu_next()));
    pmenu_songer->addAction(QString::fromLocal8Bit("分享"),this,SLOT(slots_rightMenu_next()));
    pmenu_songer->addAction(QString::fromLocal8Bit("传歌"),this,SLOT(slots_rightMenu_next()));
    pmenu_songer->addMenu(pmenu_addto);
    pmenu_songer->addAction(QString::fromLocal8Bit("查看评论"),this,SLOT(slots_rightMenu_next()));
    pmenu_songer->addAction(QString::fromLocal8Bit("删除"),this,SLOT(slots_rightMenu_next()));
    pmenu_songer->addMenu(pmenu_sort);
    pmenu_songer->addSeparator();
    pmenu_songer->addMenu(pmenu_playmode);
    pmenu_songer->addAction(QString::fromLocal8Bit("清空歌单"),this,SLOT(slots_rightMenu_clearAllList()));
    pmenu_songer->addMenu(pmenu_muctool);
    pmenu_songer->exec(QCursor::pos());
    delete pmenu_songer;
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
    for(int i = 0; i < 60; i++)
    {
        QListWidgetItem *item  = new QListWidgetItem();
        SongItemForm *son_item = new SongItemForm(QString::fromLocal8Bit("%1").arg(i+1),
                                                  QString::fromLocal8Bit("林俊杰").arg(i+1),
                                                  true,
                                                  QString::fromLocal8Bit("张辉").arg(i+1),
                                                  QString::fromLocal8Bit("天使之约").arg(i+1));
        item->setSizeHint(son_item->size());
        ui->listWidget_songer->addItem(item);
        ui->listWidget_songer->setItemWidget(item,son_item);
    }

    return 0;
}


