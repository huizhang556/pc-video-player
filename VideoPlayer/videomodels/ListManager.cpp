#include "ListManager.h"
#include "ui_ListManager.h"

ListManager::ListManager(QWidget *parent) :
    QWidget(parent),
    m_counts(0),
    ui(new Ui::ListManager)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

ListManager::~ListManager()
{
    delete ui;
}

void ListManager::initWorkUI()
{
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setContextMenuPolicy(Qt::NoContextMenu);

//    m_verScrollbar  = new QScrollBar(Qt::Vertical,ui->scrollArea);
//    m_verScrollbar->setObjectName(QString::fromUtf8("m_verScrollbar"));
//    m_verScrollbar->setFixedSize(8,ui->scrollArea->height());
//    m_verScrollbar->setMinimum(ui->scrollArea->verticalScrollBar()->minimum());
//    m_verScrollbar->setMaximum(ui->scrollArea->verticalScrollBar()->maximum());
////    m_verScrollbar->setValue(ui->scrollArea->verticalScrollBar()->value());
//    m_verScrollbar->setStyleSheet("QScrollBar#m_verScrollbar{"
//                                  "background-color: rgba(64, 66, 68,0.0);"
//                                  "}"
//                                  "QScrollBar#m_verScrollbar::add-page:vertical{"
//                                  "background-color: transparent;"
//                                  "}"
//                                  "QScrollBar#m_verScrollbar::sub-page:vertical{"
//                                  "background-color: transparent;"
//                                  "}"
//                                  "QScrollBar#m_verScrollbar::handle:vertical{"
//                                  "border: 0px;"
//                                  "min-width:6px;"
//                                  "min-height:200px;"
//                                  "border-radius:4px;"
//                                  "background-color: rgba(70,70,70,50%);"
//                                  "}");

    m_findFrame = new QFrame(ui->scrollArea);
    m_findFrame->setFixedSize(ui->scrollArea->width(),30);
    m_findFrame->setObjectName(QString::fromUtf8("m_findFrame"));
    m_findFrame->setStyleSheet("#m_findFrame{"
                              "background-color: rgba(223, 223, 223,0.9);"
                              "}"
                               "#m_findFrame:hover{"
                               "background-color: rgba(231, 231, 231,0.7);"
                               "}");
    m_findFrame->hide();


    m_searchEdit = new QLineEdit(m_findFrame);
    m_searchEdit->setMinimumSize(230,24);
    m_searchEdit->setPlaceholderText(QString(u8"请输入查找的内容^_^"));
    m_searchEdit->setObjectName(QString::fromUtf8("m_searchEdit"));
    m_searchEdit->setStyleSheet("#m_searchEdit{"
                                "border-radius: 5px;"
                                "background-color: transparent;"
                                "border: 1px solid blue;"
                                "}");

    m_hideButton = new QPushButton(m_findFrame);
    m_hideButton->setFixedSize(24,24);
//    m_hideButton->setText(QString(u8"关闭"));
    m_hideButton->setObjectName(QString::fromUtf8("m_hideButton"));
    m_hideButton->setStyleSheet("#m_hideButton{"
                                "background-color: transparent;"
                                "image: url(:/images/player/player_itemlist_close.png);"
                                "}");

    m_hblayout = new QHBoxLayout(m_findFrame);
    m_hblayout->setSpacing(3);
    m_hblayout->setContentsMargins(6,2,6,2);//左上右下
    m_hblayout->addWidget(m_searchEdit);
    m_hblayout->addWidget(m_hideButton);


    m_posFrame = new QFrame(ui->scrollArea);
    m_posFrame->setFixedSize(34,76);
    m_posFrame->setObjectName(QString::fromUtf8("m_posFrame"));
    m_posFrame->setStyleSheet("#m_posFrame{"
                              "background-color: rgba(132, 37, 225,0.2);"
                              "border-radius: 15px;"
                              "border: 2px solid rgb(157, 235, 29);"
                              "}");

    m_findButton = new QPushButton(m_posFrame);
    m_findButton->setFixedSize(26,26);
//    m_findButton->setText(QString(u8"查找"));
    m_findButton->setObjectName(QString::fromUtf8("m_findButton"));
    m_findButton->setStyleSheet("#m_findButton{"
                                "border-radius: 13px;"
                                "background-color: transparent;"
                                "image: url(:/images/player/player_itemlist_search.png);"
                                "}");

    m_locateButton = new QPushButton(m_posFrame);
    m_locateButton->setFixedSize(26,26);
//    m_locateButton->setText(QString(u8"定位"));
    m_locateButton->setObjectName(QString::fromUtf8("m_locateButton"));
    m_locateButton->setStyleSheet("#m_locateButton{"
                                  "border-radius: 13px;"
                                  "background-color: transparent;"
                                  "image: url(:/images/player/player_itemlist_locate.png);"
                                  "}");

    m_vblayout = new QVBoxLayout(m_posFrame);
    m_vblayout->setSpacing(5);
    m_vblayout->setContentsMargins(2,0,0,0);
    m_vblayout->addWidget(m_findButton);
    m_vblayout->addWidget(m_locateButton);

    createNewSongList(FINSTATUS::STA_FINISHED,QString(u8"默认列表"));
}

void ListManager::handleSignalsAndSlots()
{
//    connect(ui->scrollArea->verticalScrollBar(),&QScrollBar::valueChanged,[=](int value){
//        m_verScrollbar->setValue(value);
//        qDebug() <<QString(u8"当前值滚动条：") << value;
//    });

//    connect(m_verScrollbar,&QScrollBar::valueChanged,[=](int value){

//        ui->scrollArea->verticalScrollBar()->setValue(value);

//        int spaceHeight;
//        if(m_curListItem != nullptr)
//        {
//            int cur_id = m_curListItem->getItemId();
//            spaceHeight = (m_listItems.count() - cur_id)*36;
//        }
//        qDebug() <<QString(u8"当前滚动条值：%1---\n,当前item该有高度:%2").arg(value).arg(spaceHeight);
//        if(spaceHeight < value)
//        {
//            ui->scrollArea->verticalScrollBar()->setValue(spaceHeight-36);
//        }
//        else
//        {
//            ui->scrollArea->verticalScrollBar()->setValue(value);
//        }
//    });


    //查找
    connect(m_findButton,&QPushButton::clicked,[=](){
        if(m_expand)
        {
            m_findFrame->raise();
            m_findFrame->show();
            qDebug() <<QString(u8"查找...");
        }
    });

    //关闭查找
    connect(m_hideButton,&QPushButton::clicked,[=](){
        m_findFrame->hide();
        m_searchEdit->clear();
    });

    //查找内容
    connect(m_searchEdit,&QLineEdit::textChanged,[=](const QString &text){
        findContentTextItems(text);
        ui->scrollArea->verticalScrollBar()->setValue(0);
    });

    //定位
    connect(m_locateButton,&QPushButton::clicked,[=](){
        qDebug() <<QString(u8"定位触发！，列表的ID：%1， 列表选中的item的ROW: %2").arg( m_curListItem->getItemId()).arg(m_curListItem->getCurListWidget().currentRow());
        ui->scrollArea->verticalScrollBar()->setValue(0);
//        ui->scrollArea->verticalScrollBar()->setValue(36+(m_curListItem->getCurListWidget().currentRow()+1)*36+ui->scrollArea->verticalScrollBar()->minimum());//所有的位置统一由外部scrollArea设置，内部的listwidget没用
//        m_curListItem->scrollItemToPosition();//滚动到当前列表可视区域中央位置
    });
}

void ListManager::setInstallEventFilter()
{
    this->installEventFilter(this);
    ui->scrollArea->installEventFilter(this);
}

void ListManager::slot_setCurPlayListSelectedRow(int row)
{
    m_playListItem->getCurListWidget().setCurrentRow(row);
}

bool ListManager::eventFilter(QObject *watched, QEvent *event)
{
//    if(watched == ui->scrollArea && event->type() == QEvent::Enter)
//    {
//        qDebug() << QString(u8"滚动条进入");
//        m_verScrollbar->show();

//    }
//    if(watched == ui->scrollArea && event->type() == QEvent::Leave)
//    {
//        qDebug() << QString(u8"滚动条移出");
//        m_verScrollbar->hide();
//    }
    if(watched == ui->scrollArea && event->type() == QEvent::Resize)
    {
        autoResizeGeometry();
        updateScrollbarGeomotry();
        qDebug() << QString(u8"滚动条resize");
    }
    if(watched == this && event->type() == QEvent::Resize)
    {
        emit sig_send_height(this->height());
        qDebug() << QString(u8"已发最新高度：%1").arg(this->height());
    }
    return QWidget::eventFilter(watched,event);
}

int ListManager::calSpaceExpandHeight()
{
    int height = ui->scrollArea->height() - (m_counts-1)*42;
    return height;
}

//创建item
void ListManager::createNewSongList(FINSTATUS status, QString sname)
{
    NewListItem *itemWidget = new NewListItem(status,m_counts,sname);
    ui->m_itemVLayout->insertWidget(0,itemWidget);
    setItemWidgetCloseStatus(itemWidget);//其他没有关闭的先关闭
    m_curListItem = itemWidget;//新建的item 默认被选中
    m_listItems.insert(m_counts,itemWidget);
    m_counts++;

    connect(itemWidget,&NewListItem::sig_item_addeditems,[=](){
        hideAllItemWidgets(itemWidget);
       m_posFrame->show();
    });

    connect(this,&ListManager::sig_send_height,[=](int height){
        itemWidget->slot_setNodeCounts(height);
        qDebug() << QString(u8"视图显示区域高度：%1").arg(height);
    });

//    itemWidget->slot_setNodeCounts(calSpaceExpandHeight());//通知item展开时该有的高度

    //自己展开，其余关闭
    connect(itemWidget,&NewListItem::sig_item_expand,[=](bool on){
        qDebug() <<QString(u8"received sig_item_expand") << on;
        m_expand = on;
        m_curListItem = itemWidget;
//        setItemWidgetCloseStatus(itemWidget);//关闭其他item
        if(!m_expand)//没有展开
        {
            showAllItemWidgets(itemWidget);
            m_posFrame->hide();
            m_findFrame->hide();
            m_searchEdit->clear();
        }
        else//展开
        {
            hideAllItemWidgets(itemWidget);
            if(m_curListItem->getCurListWidget().count() != 0) m_posFrame->show();
        }
        qDebug() << QString(u8"变化后的item id=")<< itemWidget->getItemId();
    });

    //新建
    connect(itemWidget,&NewListItem::sig_item_create,[=](){
        qDebug() <<QString(u8"received sig_item_create");
        createNewSongList(FINSTATUS::STA_UNFINISHED,QString(u8"默认列表"));
    });

    //删除
    connect(itemWidget,&NewListItem::sig_item_delete,[=](){
        qDebug() <<QString(u8"received sig_item_delete");
        if(ui->m_itemVLayout->count() == 2) return;//不能删除最后一个，得留一个
        itemWidget->disconnect();
        itemWidget->deleteLater();
        ui->m_itemVLayout->removeWidget(itemWidget);
        m_listItems.removeAt(itemWidget->getItemId());
        m_counts--;
        for(int i = itemWidget->getItemId(); i < m_listItems.count(); i++)
        {
           m_listItems.at(i)->setItemId(i);
        }
    });

    //item被点击，播放器播放媒体
    connect(itemWidget,&NewListItem::sig_item_newPlaylist,[=](int id,QStringList list,QString url){
        m_playListItem = itemWidget;
        emit sig_play_newPlayist(id,list,url);
    });

    //联动滚动条
    connect(itemWidget,&NewListItem::sig_item_scrollbar,[=](int value){
//        qDebug() <<QString(u8"received sig_item_scrollbar");
//        m_verScrollbar->setValue(value);
    });
}

void ListManager::findContentTextItems(QString name)
{
    if(m_curListItem != nullptr)
    {
        name.remove(QRegExp("\\s"));
        if(name.isEmpty())
        {
            for(int i = 0; i < m_curListItem->getCurListWidget().model()->rowCount(); i++)
                m_curListItem->getCurListWidget().setRowHidden(i,false);

        }
        else
        {
            for(int i = 0; i <m_curListItem->getCurListWidget().model()->rowCount(); i++)
            {
                m_curListItem->getCurListWidget().setRowHidden(i,true);
                QString curname = "";
                QAbstractItemModel *model = m_curListItem->getCurListWidget().model();
                QModelIndex index;
                for(int j = 0; j < m_curListItem->getCurListWidget().model()->columnCount(); j++)
                {
                    index = model->index(i,j);
                    curname += model->data(index,Qt::UserRole).toString();//默认是DisplayRole
                }
                curname.remove(QRegExp("\\s"));
                if(curname.contains(name,Qt::CaseInsensitive)) //CaseSensitive:敏感
                   m_curListItem->getCurListWidget().setRowHidden(i,false);
            }
        }
    }
}

void ListManager::hideAllItemWidgets(NewListItem *myself)
{
    for(int i = 0; i < ui->m_itemVLayout->count(); i++)
    {
        QWidget* itemWgt = ui->m_itemVLayout->itemAt(i)->widget();
        if(itemWgt != nullptr && itemWgt != myself)//除了自己以外的全部折叠
        {
            qDebug() <<QString(u8"找到itemWgt") << itemWgt;
            NewListItem *newListItem = static_cast<NewListItem*>(itemWgt);
            newListItem->slot_finishedRename();
            newListItem->setListFold();
            newListItem->hide();
                qDebug() <<QString(u8"找到了");
        }
    }
}

void ListManager::showAllItemWidgets(NewListItem *myself)
{
    for(int i = 0; i < ui->m_itemVLayout->count(); i++)
    {
        QWidget* itemWgt = ui->m_itemVLayout->itemAt(i)->widget();
        if(itemWgt != nullptr && itemWgt != myself)//除了自己以外的全部折叠
        {
            qDebug() <<QString(u8"找到itemWgt") << itemWgt;
            NewListItem *newListItem = static_cast<NewListItem*>(itemWgt);
            newListItem->slot_finishedRename();
            newListItem->setListFold();//先折叠
            newListItem->show();//再显示
                qDebug() <<QString(u8"找到了");
        }
    }
}

void ListManager::setItemWidgetCloseStatus(NewListItem *myself)
{
    for(int i = 0; i < ui->m_itemVLayout->count(); i++)
    {
        QWidget* itemWgt = ui->m_itemVLayout->itemAt(i)->widget();
        if(itemWgt != nullptr && itemWgt != myself)//除了自己以外的全部折叠
        {
            qDebug() <<QString(u8"找到itemWgt") << itemWgt;
            NewListItem *newListItem = static_cast<NewListItem*>(itemWgt);
            newListItem->slot_finishedRename();
            newListItem->setListFold();

                qDebug() <<QString(u8"找到了");
        }
    }
}

void ListManager::updateScrollbarGeomotry()
{/*
    m_verScrollbar->move(ui->scrollArea->x()+ui->scrollArea->width()-m_verScrollbar->width()-1,
                         0);


    m_verScrollbar->setFixedSize(10,ui->scrollArea->height());
    m_verScrollbar->setMinimum(ui->scrollArea->verticalScrollBar()->minimum());
    m_verScrollbar->setMaximum(ui->scrollArea->verticalScrollBar()->maximum());
    m_verScrollbar->setValue(ui->scrollArea->verticalScrollBar()->value());
//    m_verScrollbar->setMinimumHeight(10);
    m_verScrollbar->raise();
    //    m_verScrollbar->show();*/
}

void ListManager::autoResizeGeometry()
{
    m_posFrame->move(ui->scrollArea->x()+ui->scrollArea->width()-m_posFrame->width()-15,
                     ui->scrollArea->y()+ui->scrollArea->height()-m_posFrame->height()-30);
    m_posFrame->raise();


    m_findFrame->setFixedSize(ui->scrollArea->width(),30);
    m_findFrame->move(0,
                     ui->scrollArea->y()+ui->scrollArea->height()-m_findFrame->height());
    m_findFrame->raise();
}
