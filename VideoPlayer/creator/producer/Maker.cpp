#include "Maker.h"
#include "ui_Maker.h"

Maker::Maker(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Maker)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
}

Maker::~Maker()
{
    delete ui;
    delete m_mediaBox;
}

void Maker::initWorkUI()
{
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

    m_signalMapper = new QSignalMapper(this);
    m_signalMapper->setObjectName(QString::fromUtf8("m_signalMapper"));
    m_signalMapper->setMapping(ui->pushButton_add_type,QString(u8"作品类型"));
    m_signalMapper->setMapping(ui->pushButton_add_theme,QString(u8"作品题材"));
    m_signalMapper->setMapping(ui->pushButton_add_time,QString(u8"作品时长"));

    m_mediaBox = new AddMediaInfo();
    m_mediaBox->setObjectName(QString::fromUtf8("m_mediaBox"));

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

    ui->pushButton_uploadFiles->setCheckable(true);
    ui->pushButton_uploadFiles->setChecked(false);
    ui->pushButton_uploadFiles->setText(QString(u8"上传"));
    ui->pushButton_uploadFiles->setProperty("enabled",false);

    ui->stackedWidget_upload->setCurrentWidget(ui->stacked_blank);
}

void Maker::handleSignalsAndSlots()
{
    connect(m_signalMapper,QOverload<const QString&>::of(&QSignalMapper::mapped),[&](const QString& type){addMediaType(type);});
    //作品题材（信号重载）
    connect(ui->pushButton_add_type,SIGNAL(clicked(bool)),m_signalMapper,SLOT(map()));
    connect(ui->pushButton_add_theme,SIGNAL(clicked(bool)),m_signalMapper,SLOT(map()));
    connect(ui->pushButton_add_time,SIGNAL(clicked(bool)),m_signalMapper,SLOT(map()));

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
            checkListItemsCounts();//核对数量
        }
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

    //上传列表（右键菜单）
    connect(ui->listWidget_videopolish,&CListWidget::customContextMenuRequested,[=](const QPoint &pos){
        qDebug() <<QString(u8"触发右键!");
        QMenu menu_rlist(this);
        menu_rlist.addAction(QIcon("://images/tray/tray_setting.png"),QString::fromLocal8Bit("添加文件"),this,SLOT(slot_addFileToList()));
        menu_rlist.addAction(QIcon("://images/tray/tray_setting.png"),QString::fromLocal8Bit("清除列表"),this,SLOT(slot_clearList()));
        menu_rlist.exec(QCursor::pos());
    });
}

void Maker::setInstallEventer()
{

}

void Maker::addMediaType(const QString &title)
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

void Maker::slot_addFileToList()
{
    ui->pushButton_openfile->click();//模拟按钮点击
}

void Maker::slot_clearList()
{
    //    emit sig_file_uploadall_clear();//（让自己清除，解除信号与槽函数关联）
        ui->listWidget_videopolish->clear();
        //问题，全部清空是真的清空吗？
        checkListItemsCounts();
}

void Maker::file_upload_pause()
{
    qDebug() << QString(u8"暂停上传");
}

void Maker::file_upload_stop()
{
    qDebug() << QString(u8"移除item");
}

void Maker::file_upload_start(const QUrlQuery media_url, const QByteArray &pic_url, FilesItem *fileItem)
{
    //视频部分(解析部分:url值进行判断)
    if(!media_url.queryItemValue("url").isEmpty() && !media_url.queryItemValue("url").startsWith(":/",Qt::CaseInsensitive))
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
        upWorker->slot_receiveData_accept(media_url);//本地的url
        //信号与槽函数
        connect(workThread,&QThread::finished,upWorker,&QObject::deleteLater);//线程结束时，工作对象自动删除
        connect(workThread,&QThread::finished,workThread,&QThread::deleteLater);//线程结束时，线程内对象自动删除
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

    //视频封面
    if(!pic_url.isNull() && !pic_url.isEmpty())
    {
        qDebug() << QString(u8"header:是合法数据！");
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
        qDebug() << QString(u8"header:是非法数据，无法获取文件！");
    }

    //文件上传完成（自动移除item）
//    connect(workThread,&QThread::finished,fileItem,&FilesItem::slot_statusButtonClick);//传输完成线程并不立即退出
}

QList<QUrl> Maker::getOpenFileSystem()
{
    QList<QUrl> fileList =  QFileDialog::getOpenFileUrls();
    return fileList;
}

void Maker::checkListItemsCounts()
{
    if(ui->listWidget_videopolish->count() == 0)
    {
        ui->stackedWidget_upload->setCurrentWidget(ui->stacked_blank);
        ui->pushButton_uploadFiles->setEnabled(false);
        ui->pushButton_uploadFiles->setProperty("enabled",false);
        ui->pushButton_uploadFiles->style()->polish(ui->pushButton_uploadFiles);
        qDebug() << QString(u8"列表为空，上传按钮不能用！");
    }
    else
    {
            ui->pushButton_uploadFiles->setEnabled(true);
            ui->pushButton_uploadFiles->setProperty("enabled",true);
            ui->pushButton_uploadFiles->style()->polish(ui->pushButton_uploadFiles);
            qDebug() << QString(u8"列表不为空，上传按钮可用！");
    }
}

void Maker::file_createItemToAnotherListWgt(const fileBody &body)
{
//    qDebug() << QString(u8"已经上传完成的视频，要被创建新的ITEM信息如下:");
//    qDebug()<< "new body =" << endl << body.fname << endl << body.fsize  << endl << body.fcover;
//    QListWidgetItem *item = new QListWidgetItem();
//    item->setData(Qt::UserRole,body.furl);
//    FilesItem *itemWidget = new FilesItem(FILEEDIT::CANEDIT,body.furl,body.fsize,body.fcover);
//    itemWidget->initFileItem(body);
//    item->setSizeHint(ITEMSIZE);
//    if(body.fmedtype == QString("movies"))
//    {
//        ui->listWidget_prod_movies->addItem(item);
//        ui->listWidget_prod_movies->setItemWidget(item,itemWidget);
//    }
//    else if(body.fmedtype == QString("netdrama"))
//    {
//        ui->listWidget_prod_netdrama->addItem(item);
//        ui->listWidget_prod_netdrama->setItemWidget(item,itemWidget);
//    }
//    else if(body.fmedtype == QString("shortvideos"))
//    {
//        ui->listWidget_prod_shortvideos->addItem(item);
//        ui->listWidget_prod_shortvideos->setItemWidget(item,itemWidget);
//    }
//    else if(body.fmedtype == QString("midvideos"))
//    {
//        ui->listWidget_prod_midvideos->addItem(item);
//        ui->listWidget_prod_midvideos->setItemWidget(item,itemWidget);
//    }
//    else if(body.fmedtype == QString("musics"))
//    {
//        ui->listWidget_prod_musics->addItem(item);
//        ui->listWidget_prod_musics->setItemWidget(item,itemWidget);
//    }
//    else if(body.fmedtype == QString("pictures"))
//    {
//        ui->listWidget_prod_pictures->addItem(item);
//        ui->listWidget_prod_pictures->setItemWidget(item,itemWidget);
//    }

//    //信号与槽函数
//    //移除
//    connect(itemWidget,&FilesItem::sig_sendItem_remove,[=](){
//        itemWidget->disconnect();
//        itemWidget->deleteLater();
//        item->listWidget()->takeItem(item->listWidget()->row(item));
//        delete item;
//    });
//    //播放
//    connect(itemWidget,&FilesItem::sig_sendItem_play,[=](){
////        m_miniPlayer->resize(1000,666);
////        m_miniPlayer->move((QApplication::desktop()->width() - m_miniPlayer->width())/2,(QApplication::desktop()->height() - m_miniPlayer->height())/2);//居中显示
////        m_miniPlayer->c_show();//关闭按钮处出现
////        m_miniPlayer->slot_receivePlayMediaFile(item->data(Qt::UserRole).toString(),QUrl(item->data(Qt::UserRole).toString()).fileName());
////        qDebug() << QString(u8"接收到的播放地址：")<< item->data(Qt::UserRole).toString();
//    });

}

//添加将要上传的作品
void Maker::addFileItemsToList(const QList<QUrl> urlLists)
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
        item->setSizeHint(ITEMSIZE);
        item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
//        item->setToolTip(fileUrl.fileName());
        ui->listWidget_videopolish->addItem(item);
        ui->listWidget_videopolish->setItemWidget(item,itemWidget);
        //关联信号槽
        //移除item(1.未上传时移除2.上传进度100%时，模拟按钮点击移除)
        connect(itemWidget,&FilesItem::sig_sendItem_remove,[=](){
            itemWidget->disconnect();//断开与itemWidget关联的所有信号槽（否则移除之后，如果在没有delete的情况下，还是会触发信号槽）
            itemWidget->deleteLater();
            item->listWidget()->takeItem(item->listWidget()->row(item));
            delete item;
            checkListItemsCounts();
        });

        //全部清除
        connect(this,&Maker::sig_file_uploadall_clear,[=](){
            itemWidget->disconnect();
            itemWidget->deleteLater();
            item->listWidget()->takeItem(item->listWidget()->row(item));
            delete item;
            qDebug() <<QString(u8"接收到清除全部的信号！");
        });

        //完成添加进入另一个list（url回传回来的时候body齐全，发出finished）
        connect(itemWidget,&FilesItem::sig_sendItem_finished,[=](fileBody body){
//            file_createItemToAnotherListWgt(body);//上传以后的body信息
        });

        //全部上传（点击按钮）
        connect(this,&Maker::sig_file_uploadall_start,[=](){
            itemWidget->slot_pauseButtonClick();
            qDebug() << QString(u8"全部上传");
        });
        //全部暂停
        connect(this,&Maker::sig_file_uploadall_stop,[=](){
            itemWidget->slot_pauseButtonClick();
            qDebug() << QString(u8"全部暂停");
        });

        //开始上传（单个）
        connect(itemWidget,&FilesItem::sig_sendItem_upload,[=](bool start,QUrlQuery media_url,QByteArray& media_cover){
            qDebug() << start;
            if(!start)
            {
                file_upload_start(media_url,media_cover,itemWidget);
                qDebug() << QString(u8"开始上传") <<media_url.queryItemValue("url") << endl << media_cover ;
            }
            else
            {
                file_upload_pause();
                qDebug() << QString(u8"暂停上传");
            }
        });
    }
}

QString Maker::file_getFileSuffix(const QString &suffix)
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
