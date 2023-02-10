#include "CreateCenter.h"
#include "ui_CreateCenter.h"

//#ifdef Q_OS_WIN
//#include <qt_windows.h>
//#include <Windows.h>
//#include <windowsx.h>
//#pragma comment (lib,"user32.lib")
//#endif
CreateCenter* CreateCenter::m_pInstance = nullptr;

CreateCenter::CreateCenter(QWidget *parent) :
    BaseWidget(parent),
    ui(new Ui::CreateCenter)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
    this->resize(1100,700);
    this->setMinimumSize(QSize(1100,700));
    this->setTitleBarMoveArea(m_ctitleBar,1);
    this->setWindowTitle(QString::fromLocal8Bit("创作中心"));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint);

}

CreateCenter::~CreateCenter()
{
    delete ui;
    delete m_mediaBox;
    delete m_calendar;
    delete m_wgtAction;
    delete m_menuDataTime;
    delete m_miniPlayer;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

CreateCenter *CreateCenter::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new CreateCenter();
    }
    return m_pInstance;
}

void CreateCenter::initWorkUI()
{
    this->setContentsMargins(1,1,1,1);
    m_miniPlayer = new MiniPlayer();

    ui->pushButton_uploadFiles->setCheckable(true);
    ui->pushButton_uploadFiles->setChecked(false);
    ui->pushButton_uploadFiles->setText(QString(u8"上传"));

    m_buttonGroup1 = new QButtonGroup(this);
    m_buttonGroup1->setExclusive(true);
    m_buttonGroup1->addButton(ui->pushButton_mtype1,0);
    m_buttonGroup1->addButton(ui->pushButton_mtype2,1);
    m_buttonGroup1->addButton(ui->pushButton_mtype3,2);
    m_buttonGroup1->addButton(ui->pushButton_mtype4,3);
    m_buttonGroup1->addButton(ui->pushButton_mtype5,4);

    for(int i = 0; i < 5; i++)
    {
        m_buttonGroup1->button(i)->setCheckable(true);
    }
    m_buttonGroup1->button(0)->setChecked(true);

    m_buttonGroup2 = new QButtonGroup(this);
    m_buttonGroup2->setExclusive(true);
    m_buttonGroup2->addButton(ui->pushButton_mtheme1,0);
    m_buttonGroup2->addButton(ui->pushButton_mtheme2,1);
    m_buttonGroup2->addButton(ui->pushButton_mtheme3,2);
    m_buttonGroup2->addButton(ui->pushButton_mtheme4,3);
    m_buttonGroup2->addButton(ui->pushButton_mtheme5,4);

    for(int i = 0; i < 5; i++)
    {
        m_buttonGroup2->button(i)->setCheckable(true);
    }
    m_buttonGroup2->button(0)->setChecked(true);

    m_buttonGroup3 = new QButtonGroup(this);
    m_buttonGroup3->setExclusive(true);
    m_buttonGroup3->addButton(ui->pushButton_mtime1,0);
    m_buttonGroup3->addButton(ui->pushButton_mtime2,1);
    m_buttonGroup3->addButton(ui->pushButton_mtime3,2);

    for(int i = 0; i < 3; i++)
    {
        m_buttonGroup3->button(i)->setCheckable(true);
    }
    m_buttonGroup3->button(0)->setChecked(true);

    m_signalMapper = new QSignalMapper(this);
    m_signalMapper->setObjectName(QString::fromUtf8("m_signalMapper"));
    m_signalMapper->setMapping(ui->pushButton_add_type,QString(u8"作品类型"));
    m_signalMapper->setMapping(ui->pushButton_add_theme,QString(u8"作品题材"));
    m_signalMapper->setMapping(ui->pushButton_add_time,QString(u8"作品时长"));

    m_mediaBox = new AddMediaInfo();
    m_mediaBox->setObjectName(QString::fromUtf8("m_mediaBox"));

    m_ctitleBar = new CreTitleBar(this);
    m_ctitleBar->setObjectName(QString::fromUtf8("m_ctitleBar"));
    ui->verticalLayout->insertWidget(0,m_ctitleBar);

    m_calendar = new CusCalendar();
    m_calendar->setObjectName(QString::fromUtf8("m_calendar"));

    m_menuDataTime = new QMenu();//不指定父亲，不继承父亲样式
    m_menuDataTime->setObjectName(QString::fromUtf8("m_menuDataTime"));
    m_wgtAction = new QWidgetAction(m_menuDataTime);
    m_wgtAction->setDefaultWidget(m_calendar);
    m_menuDataTime->addAction(m_wgtAction);
    m_menuDataTime->installEventFilter(this);

    ui->stackedWidget_switch->setCurrentWidget(ui->page_login);
    ui->tabWidget_create->setCurrentIndex(0);
    ui->stackedWidget_upload->setCurrentWidget(ui->stacked_blank);

    ui->toolBox_center->layout()->setSpacing(1);//item之间的间距
    ui->toolBox_center->setItemIcon(0,QIcon(""));
    ui->toolBox_center->setItemIcon(1,QIcon(""));
    ui->toolBox_center->setItemIcon(2,QIcon(""));
    ui->toolBox_center->setItemIcon(3,QIcon(""));

    for(int i = 0; i < ui->listWidget_perCenter->count(); i++)
    {
        ui->listWidget_perCenter->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }

    for(int i = 0; i < ui->listWidget_shortVideo->count(); i++)
    {
        ui->listWidget_shortVideo->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }

    for(int i = 0; i < ui->listWidget_midVideo->count(); i++)
    {
        ui->listWidget_midVideo->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }

    for(int i = 0; i < ui->listWidget_musics->count(); i++)
    {
        ui->listWidget_musics->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }

    for(int i = 0; i < ui->listWidget_producelist->count(); i++)
    {
        ui->listWidget_producelist->item(i)->setTextAlignment(Qt::AlignCenter | Qt::AlignCenter);
    }

    //上传列表
    ui->listWidget_videopolish->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_videopolish->setViewMode(QListView::IconMode);
    ui->listWidget_videopolish->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_videopolish->setResizeMode(QListWidget::Adjust);
    ui->listWidget_videopolish->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_videopolish->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_videopolish->horizontalScrollBar()->setDisabled(true);
    ui->listWidget_videopolish->setSelectionMode(QAbstractItemView::SingleSelection);//设置选择模式为单选
    ui->listWidget_videopolish->setDragEnabled(true);//启用拖拽
    ui->listWidget_videopolish->viewport()->setAcceptDrops(true);//设置接受拖放
    ui->listWidget_videopolish->setDropIndicatorShown(true);//设置显示将要被放置的位置
    ui->listWidget_videopolish->setDragDropMode(QAbstractItemView::InternalMove);//设置拖放模式为移动项目，如果不设置，默认为复制项


    //作品列表--左侧
    for(int i = 0; i<m_producelist.count();i++)
    {
        QListWidgetItem *item = new QListWidgetItem(m_producelist.at(i));
        item->setTextAlignment(Qt::AlignCenter);
        ui->listWidget_producelist->addItem(item);//添加列表
    }


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

    //tableWidget_records
    ui->tableWidget_records->setColumnCount(5);//先设置列数
    ui->tableWidget_records->setHorizontalHeaderLabels(m_header);
    ui->tableWidget_records->verticalHeader()->setDefaultSectionSize(26);//垂直固定高度26
    ui->tableWidget_records->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);//垂直表头固定高度
    ui->tableWidget_records->setSelectionBehavior(QAbstractItemView::SelectRows);//只能行选择
    ui->tableWidget_records->setColumnWidth(0,220);
    ui->tableWidget_records->setColumnWidth(1,350);
    ui->tableWidget_records->setColumnWidth(2,150);
    ui->tableWidget_records->setColumnWidth(3,150);
    ui->tableWidget_records->setColumnWidth(4,150);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Fixed);
}

void CreateCenter::handleSignalsAndSlots()
{
    //接收标题栏
    //关闭
    connect(m_ctitleBar,&CreTitleBar::sig_win_close,[=](){this->close();});
    //最小化
    connect(m_ctitleBar,&CreTitleBar::sig_win_min,[=](){this->showMinimized();});
    //还原
    connect(m_ctitleBar,&CreTitleBar::sig_win_restore,[=](bool restore){
        if(restore)
        {
            this->showMaximized();
        }
        else
        {
            this->showNormal();
        }
    });


    //小窗口关闭
    connect(ui->label_loginbg,&MoveLabel::sig_sendClose,[=](){this->close();});

    //登录
    connect(ui->label_loginbg,&MoveLabel::sig_sendLogin,[=](){ui->stackedWidget_switch->setCurrentWidget(ui->page_create);});

    //选择文件
    connect(ui->pushButton_openfile,&QPushButton::clicked,[=](){
        QList<QUrl> fileList = getOpenFileSystem();
        if(fileList.isEmpty())
        {
            return;
        }
        else
        {
            addFileItemsToList(fileList);//添加item
            ui->stackedWidget_upload->setCurrentWidget(ui->stacked_upload);
        }
    });


    //显示日历
    connect(ui->pushButton_date1,&QPushButton::clicked,[=](){
        m_menuDataTime->exec(QCursor::pos());
    });

    connect(ui->pushButton_date2,&QPushButton::clicked,[=](){
        m_menuDataTime->exec(QCursor::pos());
    });

    //日期填充
    connect(m_calendar,&CusCalendar::sig_calendar1,[=](QDate date){
        ui->dateEdit_start->setDate(date);
    });

    connect(m_calendar,&CusCalendar::sig_calendar2,[=](QDate date){
        ui->dateEdit_end->setDate(date);
    });

    //全部上传
    connect(ui->pushButton_uploadFiles,&QPushButton::clicked,[=](bool checked){
        if(checked)
        {
            emit sig_file_uploadall_start();
            ui->pushButton_uploadFiles->setText(QString(u8"全部暂停"));
        }
        else
        {
            emit sig_file_uploadall_stop();
            ui->pushButton_uploadFiles->setText(QString(u8"全部开始"));
        }
    });

    //作品题材（信号重载）
    connect(ui->pushButton_add_type,SIGNAL(clicked(bool)),m_signalMapper,SLOT(map()));
    connect(ui->pushButton_add_theme,SIGNAL(clicked(bool)),m_signalMapper,SLOT(map()));
    connect(ui->pushButton_add_time,SIGNAL(clicked(bool)),m_signalMapper,SLOT(map()));

//    connect(m_signalMapper,SIGNAL(mapped(QString)),this,SLOT(addMediaType(QString)));
    connect(m_signalMapper,QOverload<const QString&>::of(&QSignalMapper::mapped),[&](const QString& type){addMediaType(type);});


    //上传列表（右键菜单）
    connect(ui->listWidget_videopolish,&CListWidget::customContextMenuRequested,[=](const QPoint &pos){
        qDebug() <<QString(u8"触发右键!");
        QMenu menu_rlist(this);
        menu_rlist.addAction(QIcon("://images/tray/tray_setting.png"),QString::fromLocal8Bit("添加文件"),this,SLOT(slot_addFileToList()));
        menu_rlist.addAction(QIcon("://images/tray/tray_setting.png"),QString::fromLocal8Bit("清除列表"),this,SLOT(slot_clearList()));
        menu_rlist.exec(QCursor::pos());
    });

    //媒体列表
    connect(ui->listWidget_producelist,&QListWidget::itemClicked,[=](QListWidgetItem *item){
        if(item->text() == QString(u8"电影"))
        {
            ui->stackedWidget_produce->setCurrentIndex(0);
        }
        else if(item->text() == QString(u8"网络剧"))
        {
            ui->stackedWidget_produce->setCurrentIndex(1);
        }
        else if(item->text() == QString(u8"短视频"))
        {
            ui->stackedWidget_produce->setCurrentIndex(2);
        }
        else if(item->text() == QString(u8"中视频"))
        {
            ui->stackedWidget_produce->setCurrentIndex(3);
        }
        else if(item->text() == QString(u8"音乐"))
        {
            ui->stackedWidget_produce->setCurrentIndex(4);
        }
        else if(item->text() == QString(u8"图片"))
        {
            ui->stackedWidget_produce->setCurrentIndex(5);
        }
    });
}

void CreateCenter::setInstallEventer()
{
    ui->dateEdit_start->installEventFilter(this);
    ui->dateEdit_end->installEventFilter(this);
}

//void CreateCenter::mousePressEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event)
//    if(ReleaseCapture())
//    {
//        QWidget* pWindow = this->window();
//        if(pWindow->isTopLevel())
//        {
//            SendMessage(HWND(pWindow->winId()),WM_SYSCOMMAND,SC_MOVE + HTCAPTION,0);
//        }
//    }
//    event->ignore();
//}

bool CreateCenter::eventFilter(QObject *watched, QEvent *event)
{
//    if(watched == ui->dateEdit_start)
//    {
//        if(event->type() == QEvent::MouseButtonPress)
//        {
//            qDebug() << QString(u8"鼠标按下");
//            m_menuDataTime->exec(QCursor::pos());
//        }
//    }
//    else if(watched == ui->dateEdit_end)
//    {
//        if(event->type() == QEvent::MouseButtonPress)
//        {
//            qDebug() << QString(u8"鼠标按下");
//            m_menuDataTime->exec(QCursor::pos());
//        }
//    }
//    if(watched == m_menuDataTime)
//    {
//        if(event->type() == QEvent::Leave)
//            m_menuDataTime->hide();
//    }
    return QWidget::eventFilter(watched,event);
}

//bool CreateCenter::nativeEvent(const QByteArray &eventType, void *message, long *result)
//{
//    Q_UNUSED(eventType)
////    qDebug() <<"enter nativeEvent";
//    MSG* param = static_cast<MSG*>(message);

//    switch (param->message)
//    {
//    case WM_NCHITTEST:
//    {
//        int nX = GET_X_LPARAM(param->lParam) - this->geometry().x();
//        int nY = GET_Y_LPARAM(param->lParam) - this->geometry().y();

//        // 如果鼠标位于子控件上，则不进行处理
//        if(nX > MARWIDTH && nX <this->width() - MARWIDTH &&
//                nY > MARWIDTH && nY < this->height() - MARWIDTH)
//        {
//            if (childAt(nX, nY) != nullptr)
//                return QWidget::nativeEvent(eventType, message, result);
//        }

//        // 鼠标区域位于窗体边框，进行缩放
//        if ((nX > 0) && (nX < MARWIDTH))//左边
//            *result = HTLEFT;

//        if ((nX > this->width() - MARWIDTH) && (nX < this->width()))
//            *result = HTRIGHT;

//        if ((nY > 0) && (nY < MARWIDTH))//上边
//            *result = HTTOP;

//        if ((nY > this->height() - MARWIDTH) && (nY < this->height()))
//            *result = HTBOTTOM;

//        if ((nX > 0) && (nX < MARWIDTH) && (nY > 0)
//                && (nY < MARWIDTH))
//            *result = HTTOPLEFT;

//        if ((nX > this->width() - MARWIDTH) && (nX < this->width())
//                && (nY > 0) && (nY < MARWIDTH))
//            *result = HTTOPRIGHT;

//        if ((nX > 0) && (nX < MARWIDTH)
//                && (nY > this->height() - MARWIDTH) && (nY < this->height()))
//            *result = HTBOTTOMLEFT;

//        if ((nX > this->width() - MARWIDTH) && (nX < this->width())
//                && (nY > this->height() - MARWIDTH) && (nY < this->height()))
//            *result = HTBOTTOMRIGHT;

//        return true;
//        }
//    }
//    return QWidget::nativeEvent(eventType, message, result);
//}

void CreateCenter::addMediaType(const QString &title)
{
    int code = m_mediaBox->c_exec(title);
    qDebug() << code;
    //添加类型
    connect(m_mediaBox,&AddMediaInfo::sig_addMediaText,[=](QString title, QString buttontext){
        qDebug() << QString(u8"接收到添加信号");
        CloseButton *button = new CloseButton();
        button->setText(buttontext);
        button->setFixedSize(80,30);
        if(title == QString(u8"作品类型"))
        {
            ui->horizontalLayout_mediatype->insertWidget(ui->horizontalLayout_mediatype->count()-2,button);
        }
        else if(title == QString(u8"作品题材"))
        {
            ui->horizontalLayout_mediatheme->insertWidget(ui->horizontalLayout_mediatheme->count()-2,button);
        }
        else if(title == QString(u8"作品时长"))
        {
            ui->horizontalLayout_mediatime->insertWidget(ui->horizontalLayout_mediatime->count()-2,button);
        }
    });
}

void CreateCenter::slot_addFileToList()
{
    ui->pushButton_openfile->click();//模拟按钮点击
}

void CreateCenter::slot_clearList()
{
    ui->listWidget_videopolish->clear();
    checkListItemsCounts();
}

//void CreateCenter::slot_receiveThreadStarted()
//{
//    qDebug() << QString(u8"文件上传开始！");
//}

//void CreateCenter::slot_receiveThreadFinished()
//{
//    qDebug() << QString(u8"文件上传结束，线程退出！");
//}

QList<QUrl> CreateCenter::getOpenFileSystem()
{
    QList<QUrl> fileList =  QFileDialog::getOpenFileUrls();
    return fileList;
}

void CreateCenter::checkListItemsCounts()
{
    if(ui->listWidget_videopolish->count() == 0)
    {
        ui->stackedWidget_upload->setCurrentWidget(ui->stacked_blank);
    }
}

//添加将要上传的作品
void CreateCenter::addFileItemsToList(const QList<QUrl> urlLists)
{
    foreach (QUrl fileUrl, urlLists)
    {
        qDebug() << QString(u8"文件名：")<<fileUrl.fileName();
        QString filepath = QDir::toNativeSeparators(fileUrl.path().remove(0,1));//移除第一个/
        qDebug() << QString(u8"文件路径：")<<filepath;
        QFileInfo file(filepath);//file必须是堆
        qDebug() << QString(u8"文件大小：%1字节").arg(file.size());
        QString suffixpic  = file_getFileSuffix(file.suffix());
        FilesItem *itemWidget = new FilesItem(FILEEDIT::CANWRITE,fileUrl,file.size(),suffixpic);//文件名 大小 图标
        QListWidgetItem *item = new QListWidgetItem();
        item->setData(Qt::UserRole,fileUrl);
        item->setSizeHint(QSize(225,155));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
//        item->setToolTip(fileUrl.fileName());
        ui->listWidget_videopolish->addItem(item);
        ui->listWidget_videopolish->setItemWidget(item,itemWidget);
        //关联信号槽
        //移除item(1.未上传时移除2.上传进度100%时，模拟按钮点击移除)
        connect(itemWidget,&FilesItem::sig_sendItem_remove,[=](){
            itemWidget->deleteLater();
            item->listWidget()->takeItem(item->listWidget()->row(item));
            delete item;
            checkListItemsCounts();
        });

        //完成添加进入另一个list（url回传回来的时候body齐全，发出finished）
        connect(itemWidget,&FilesItem::sig_sendItem_finished,[=](fileBody body){
            file_createItemToAnotherListWgt(body);//上传以后的body信息
        });

        //全部上传（点击按钮）
        connect(this,&CreateCenter::sig_file_uploadall_start,[=](){
            itemWidget->slot_pauseButtonClick();
            qDebug() << QString(u8"全部上传");
        });
        //全部暂停
        connect(this,&CreateCenter::sig_file_uploadall_stop,[=](){
            itemWidget->slot_pauseButtonClick();
            qDebug() << QString(u8"全部暂停");
        });

        //开始上传（单个）
        connect(itemWidget,&FilesItem::sig_sendItem_pause,[=](bool start,QUrl media_url,QUrl media_cover){
            qDebug() << start;
            if(!start)
            {
                file_upload_start(media_url,media_cover,itemWidget);
                qDebug() << QString(u8"开始上传") <<media_url<< endl << media_cover ;
            }
            else
            {
//                file_upload_pause();
                qDebug() << QString(u8"暂停上传");
            }
        });
    }
}

//开始上传
void CreateCenter::file_upload_start(const QUrl media_url, const QUrl pic_url, FilesItem *fileItem)
{
    if(!media_url.toString().isEmpty() && !media_url.toString().startsWith(":/",Qt::CaseInsensitive))
    {
        qDebug() << QString(u8"video:合法路径，文件路径：-->%1").arg(media_url.toString());
        //创建工作对象
        UploadWork* upWorker = new UploadWork();
        //创建线程
        QThread *workThread = new QThread();
        //工作对象移动到线程中
        upWorker->moveToThread(workThread);
        //开启线程
        workThread->start();//开启线程
        qDebug() << QString(u8"新的线程启动(thread_1)，地址：")<< workThread;
        upWorker->slot_receiveData_accept(media_url);
        //信号与槽函数
        connect(workThread,&QThread::finished,upWorker,&QObject::deleteLater);//线程结束时，工作对象自动删除

        //上传进度
        connect(upWorker,SIGNAL(sig_work_uploadprogress(qint64,qint64)),fileItem,SLOT(slot_updateProgress(qint64,qint64)));
        //关联文件状态()
        connect(upWorker,SIGNAL(sig_work_uploadprogress(qint64,qint64)),fileItem,SLOT(slot_updateStatus(qint64,qint64)));
        //上传完成--传回信息
        connect(upWorker,SIGNAL(sig_work_finished(QString,QString)),fileItem,SLOT(slot_update_url_md5(QString,QString)));
    }
    else
    {
        qDebug() << QString(u8"video:非法路径，无法获取文件-->%1").arg(media_url.toString());
    }

    if(!pic_url.toString().isEmpty() && !pic_url.toString().startsWith(":/",Qt::CaseInsensitive))
    {
        qDebug() << QString(u8"header:合法路径，文件路径：-->%1").arg(pic_url.toString());
        UploadWork* upWorker2 = new UploadWork();
        QThread *workThread2 = new QThread();
        upWorker2->moveToThread(workThread2);
        workThread2->start();
        qDebug() << QString(u8"新的线程启动(thread_2)，地址：")<< workThread2;
        upWorker2->slot_receiveData_accept(pic_url);
        connect(workThread2,&QThread::finished,upWorker2,&QThread::deleteLater);
        connect(workThread2,&QThread::finished,workThread2,&QObject::deleteLater);
        connect(upWorker2,SIGNAL(sig_work_uploadprogress(qint64,qint64)),fileItem,SLOT(slot_updateProgress_header(qint64,qint64)));
        connect(upWorker2,SIGNAL(sig_work_finished(QString,QString)),fileItem,SLOT(slot_update_header(QString,QString)));
    }
    else
    {
        qDebug() << QString(u8"header:非法路径，无法获取文件-->%1").arg(pic_url.toString());
    }

    //文件上传完成（自动移除item）
//    connect(workThread,&QThread::finished,fileItem,&FilesItem::slot_statusButtonClick);//传输完成线程并不立即退出
}

//暂停上传
void CreateCenter::file_upload_pause()
{
    qDebug() << QString(u8"暂停上传");
}

//移除
void CreateCenter::file_upload_stop()
{
    qDebug() << QString(u8"移除item");
}

//展示已完成作品
void CreateCenter::file_createItemToAnotherListWgt(const fileBody &body)
{
    qDebug() << QString(u8"新的完成的item被创建");
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole,body.furl);
    qDebug()<< "new body =" << body.fname << body.fsize << body.fcover;
    FilesItem *itemWidget = new FilesItem(FILEEDIT::CANEDIT,body.furl,body.fsize,body.fcover);
    itemWidget->initFileItem(body);
    item->setSizeHint(QSize(225,155));
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

    //信号与槽函数
    //移除
    connect(itemWidget,&FilesItem::sig_sendItem_remove,[=](){
        itemWidget->deleteLater();
        item->listWidget()->takeItem(item->listWidget()->row(item));
        delete item;
    });
    //播放
    connect(itemWidget,&FilesItem::sig_sendItem_play,[=](){
//        m_miniPlayer->resize(1000,666);
//        m_miniPlayer->move((QApplication::desktop()->width() - m_miniPlayer->width())/2,(QApplication::desktop()->height() - m_miniPlayer->height())/2);//居中显示
//        m_miniPlayer->c_show();//关闭按钮处出现
//        m_miniPlayer->slot_receivePlayMediaFile(item->data(Qt::UserRole).toString(),QUrl(item->data(Qt::UserRole).toString()).fileName());
//        qDebug() << QString(u8"接收到的播放地址：")<< item->data(Qt::UserRole).toString();
    });

}

QString CreateCenter::file_getFileSuffix(const QString &suffix)
{
    if(suffix == "mp3")
    {
        return ":/images/creator/fileitem_music.png";
    }
    else if(suffix == "aac")
    {
        return ":/images/creator/fileitem_music.png";
    }
    else if(suffix == "mp4")
    {
        return ":/images/creator/fileitem_videos.png";
    }
    else if(suffix == "flv")
    {
        return ":/images/creator/fileitem_videos.png";
    }
    else if(suffix == "wav")
    {
        return ":/images/creator/fileitem_videos.png";
    }
    else if(suffix == "3gp")
    {
        return ":/images/creator/fileitem_videos.png";
    }
    else if(suffix == "avi")
    {
        return ":/images/creator/fileitem_videos.png";
    }
    else if(suffix == "png")
    {
        return "://images/creator/fileitem_picture.png";
    }
    else if(suffix == "gif")
    {
        return "://images/creator/fileitem_picture.png";
    }
    else if(suffix == "jpg")
    {
        return "://images/creator/fileitem_picture.png";
    }

    else
    {
        return ":/images/creator/fileitem_videos.png";
    }
}

