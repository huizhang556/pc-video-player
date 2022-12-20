#include "FilesItem.h"
#include "ui_FilesItem.h"

FilesItem::FilesItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilesItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

FilesItem::FilesItem(const FILEEDIT edit, const QUrl &url, const qint64 size, const QString &picpath, QWidget *parent):
    QWidget(parent),
    m_canedit(edit),
    m_furl(url.path().remove(0,1)),
    m_name(url.fileName()),
    m_size(size),
    m_picpath(picpath),
    m_status(READY),
    m_curStatus(QString(u8"待上传")),
    ui(new Ui::FilesItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    slot_setItemName();
    slot_setItemPicture();
    slot_setItemSize();
    slot_setItemStart(true);//默认显示"开始"
    slot_setItemStatus(m_status);
    slot_setItemStatusText();
    slot_setItemEdit(m_canedit);//设置状态
}

FilesItem::~FilesItem()
{
    delete ui;
}

void FilesItem::initWorkUI()
{
//    this->setFocusPolicy(Qt::NoFocus);

    ui->pushButton_remove->setToolTip(QString(u8"移除"));

    ui->progressBar->setValue(0);
    ui->progressBar->setRange(0,100);

    ui->pushButton_editinfo->setCheckable(true);
    ui->pushButton_editinfo->setChecked(false);
    ui->pushButton_editinfo->setText(QString(u8"编辑"));

    ui->lineEdit_filename->setAlignment(Qt::AlignLeft);
//    ui->lineEdit_filename->setCursorPosition(0);
    ui->lineEdit_filename->setToolTip(QString(u8"自定义文件名称"));

    ui->lineEdit_displaytitle->setAlignment(Qt::AlignLeft);
    ui->lineEdit_displaytitle->setCursorPosition(0);
    ui->lineEdit_mduration->setAlignment(Qt::AlignLeft);
//    ui->lineEdit_mduration->setCursorPosition(0);
    ui->comboBox_mtype->setView(new QListView());
    ui->comboBox_mtype->addItem(QString(u8"电影"),QString(u8"movies"));
    ui->comboBox_mtype->addItem(QString(u8"网络剧"),QString(u8"netdrama"));
    ui->comboBox_mtype->addItem(QString(u8"短视频"),QString(u8"shortvideos"));
    ui->comboBox_mtype->addItem(QString(u8"中视频"),QString(u8"midvideos"));
    ui->comboBox_mtype->addItem(QString(u8"音乐"),QString(u8"musics"));
    ui->comboBox_mtype->addItem(QString(u8"图片"),QString(u8"pictures"));

    ui->comboBox_mtheme->setView(new QListView());
    ui->comboBox_mtheme->addItem(QString(u8"搞笑"),QString(u8"搞笑"));
    ui->comboBox_mtheme->addItem(QString(u8"恐怖"),QString(u8"恐怖"));
    ui->comboBox_mtheme->addItem(QString(u8"科技"),QString(u8"科技"));
    ui->comboBox_mtheme->addItem(QString(u8"艺术"),QString(u8"艺术"));
    ui->comboBox_mtheme->addItem(QString(u8"体育"),QString(u8"体育"));
    ui->comboBox_mtheme->addItem(QString(u8"脱口秀"),QString(u8"脱口秀"));

    ui->lineEdit_displaycover->setReadOnly(true);//只读

    ui->stackedWidget_info->setCurrentIndex(0);
}

void FilesItem::handleSignalsAndSlots()
{
    connect(ui->pushButton_remove,&QPushButton::clicked,[=](){
        emit sig_sendItem_remove();
    });

    connect(ui->pushButton_pause,&QPushButton::clicked,[=](bool checked){
        if(m_canedit == FILEEDIT::CANWRITE)
        {
            if(!checked)
            {
                ui->pushButton_pause->setText(QString(u8"暂停"));
            }
            else
            {
                ui->pushButton_pause->setText(QString(u8"开始"));
            }
            qDebug() <<QString(u8"发送下载的URL：%1").arg(m_furl);
            emit sig_sendItem_pause(checked,QUrl(m_furl),QUrl(m_picpath));
        }
        else if(m_canedit == FILEEDIT::CANEDIT)
        {
            emit sig_sendItem_play();
        }
    });

//    connect(ui->pushButton_finish,&QPushButton::clicked,[=](){
//        ui->pushButton_editinfo->click();
//    });

    //媒体信息编辑
    connect(ui->pushButton_editinfo,&QPushButton::clicked,[=](bool checked){
        if(checked)
        {
            ui->stackedWidget_info->setCurrentIndex(1);
            ui->pushButton_editinfo->setText(QString(u8"返回"));
        }
        else
        {
            if(m_canedit == FILEEDIT::CANEDIT)
            {
                ui->pushButton_editinfo->setText(QString(u8"详细"));
            }
            else if(m_canedit == FILEEDIT::CANWRITE)
            {
                ui->pushButton_editinfo->setText(QString(u8"编辑"));
            }
            ui->stackedWidget_info->setCurrentIndex(0);

        }
    });

    //文件重命名
    connect(ui->lineEdit_filename,&QLineEdit::returnPressed,[=](){
        if(!ui->lineEdit_filename->text().trimmed().isEmpty())
        {
            ui->lineEdit_filename->setText(ui->lineEdit_filename->text().trimmed());
            ui->label_pic->setToolTip(ui->lineEdit_filename->text().trimmed());
            if(ui->lineEdit_filename->hasFocus()) ui->lineEdit_filename->clearFocus();
        }
    });

    //自定义标题
    connect(ui->lineEdit_displaytitle,&QLineEdit::returnPressed,[=](){
        if(!ui->lineEdit_displaytitle->text().trimmed().isEmpty())
        {
            ui->lineEdit_displaytitle->setText(ui->lineEdit_displaytitle->text().trimmed());
            if(ui->lineEdit_displaytitle->hasFocus()) ui->lineEdit_displaytitle->clearFocus();
        }
    });

    //自定义封面
    connect(ui->lineEdit_displaycover,&QLineEdit::returnPressed,[=](){
        if(!ui->lineEdit_displaycover->text().trimmed().isEmpty())
        {
            ui->lineEdit_displaycover->setText(ui->lineEdit_displaycover->text().trimmed());
            if(ui->lineEdit_displaycover->hasFocus()) ui->lineEdit_displaycover->clearFocus();
        }
    });


    //时长修改
    connect(ui->lineEdit_mduration,&QLineEdit::returnPressed,[=](){
        if(!ui->lineEdit_mduration->text().trimmed().isEmpty())
        {
            ui->lineEdit_mduration->setText(ui->lineEdit_mduration->text().trimmed());
            if(ui->lineEdit_mduration->hasFocus()) ui->lineEdit_mduration->clearFocus();
        }
    });


    //媒体类型选择
    connect(ui->comboBox_mtype,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int index){
         qDebug() << QString(u8"当前项发生改变：%1").arg(ui->comboBox_mtype->itemText(index));
         qDebug() << QString(u8"当前项发生改变,item data：%1").arg(ui->comboBox_mtype->currentData().toString());
    });

    //媒体题材选
    connect(ui->comboBox_mtheme,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int index){
        qDebug() << QString(u8"当前项发生改变：%1").arg(ui->comboBox_mtheme->itemText(index));
        qDebug() << QString(u8"当前项发生改变,item data：%1").arg(ui->comboBox_mtheme->currentData().toString());
    });

    //自定义封面
    connect(ui->pushButton_opencover,&QPushButton::clicked,[=](){
        QString filename_cover = QFileDialog::getOpenFileName();
        qDebug() << filename_cover;
        if(filename_cover.isEmpty())
        {
            return;
        }
        else
        {
            m_picpath = filename_cover;
            slot_setItemPicture();
        }
    });
}

void FilesItem::setInstallEventFilter()
{

}

void FilesItem::initFileItem(const fileBody &body)
{
    ui->lineEdit_displaytitle->setText(body.fnick);
    ui->comboBox_mtype->setCurrentIndex(getCurtentComboBoxIndex(ui->comboBox_mtype,body.fmedtype));
    ui->comboBox_mtheme->setCurrentIndex(getCurtentComboBoxIndex(ui->comboBox_mtheme,body.fmedtheme));
    ui->lineEdit_mduration->setText(body.fduration);
    ui->comboBox_mtype->setDisabled(true);
    ui->comboBox_mtheme->setDisabled(true);
    ui->lineEdit_displaytitle->setReadOnly(true);
    ui->lineEdit_mduration->setReadOnly(true);
}

void FilesItem::slot_setItemEdit(const FILEEDIT edit)
{
    switch (edit)
    {
    case CANWRITE:
    {
        ui->pushButton_pause->setCheckable(true);
        ui->pushButton_pause->setChecked( true);
    }
        break;
    case CANEDIT:
    {
        ui->lineEdit_filename->setReadOnly(true);
        ui->progressBar->setHidden(true);
        ui->pushButton_editinfo->setText(QString(u8"详细"));
        ui->pushButton_pause->setText(QString(u8"播放"));
        ui->pushButton_pause->setCheckable(false);
        ui->pushButton_finish->setText(QString(u8"已上传"));
        ui->pushButton_finish->setDisabled(true);
        ui->pushButton_opencover->setDisabled(true);
    }
        break;
    default:
        break;
    }
}

void FilesItem::slot_setItemStatus(FILESTATUS status)
{
    if(m_status == status)
    {
//        qDebug() << QString(u8"与之前状态一样");
        return;
    }
    else
    {
//        qDebug() << QString(u8"与之前状态不一样");
       m_status = status;
       emit sig_sendItem_statusChanged(m_status);
    }
    switch (status)
    {
    case READY:
    {
        m_curStatus = QString(u8"待上传");
    }
        break;
    case WAITING:
    {
        m_curStatus = QString(u8"等待中");
    }
        break;
    case UPLOADING:
    {
        m_curStatus = QString(u8"上传中");
    }
        break;
    case FINISHED:
    {
        m_canedit = FILEEDIT::CANEDIT;
        m_curStatus = QString(u8"已完成");
        ui->pushButton_editinfo->setText(QString(u8"详细"));
        ui->pushButton_pause->setText(QString(u8"播放"));
    }
        break;
    case UNKNOW:
    {
        m_curStatus = QString(u8"未知");
    }
        break;
    default:
        break;
    }
}

void FilesItem::slot_setItemStatusText()
{
    ui->pushButton_finish->setText(m_curStatus);
}

void FilesItem::slot_setItemStart(bool start)
{
        if(!start)
        {
            ui->pushButton_pause->setText(QString(u8"暂停"));
        }
        else
        {
            ui->pushButton_pause->setText(QString(u8"开始"));
        }
}

void FilesItem::slot_setItemSize()
{
    ui->label_size->setText(QString(u8"大小：%1").arg(calCurrentFileSize(m_size)));
}

void FilesItem::slot_setItemName()
{
    ui->lineEdit_filename->setText(m_name);
//    ui->lineEdit_filename->setCursorPosition(0);鼠标到达最左边
    ui->lineEdit_filename->setFocusPolicy(Qt::ClickFocus);
    ui->label_pic->setToolTip(m_name);
}

void FilesItem::slot_setItemPicture()
{
    qDebug() << "new picpath =" << m_picpath;
    ui->lineEdit_displaycover->setText(m_picpath);
    ui->label_pic->setPixmap(QPixmap(m_picpath));
    ui->label_pic->setScaledContents(true);
}

void FilesItem::slot_updateProgress(qint64 bytesSent, qint64 bytesTotal)
{
    if(bytesSent > 0 && bytesTotal != 0 )
    {
        ui->progressBar->setValue(bytesSent*100/bytesTotal);//下载进度百分比（进度条）
    }
}

void FilesItem::slot_updateProgress_header(qint64 bytesSent, qint64 bytesTotal)
{
    if(bytesSent > 0 && bytesTotal != 0 )
    {
        qDebug() << QString(u8"图片上传进度：") << (bytesSent*100/bytesTotal);//下载进度百分比（进度条）
    }
}

void FilesItem::slot_updateStatus(qint64 bytesSent, qint64 bytesTotal)
{
    if(bytesSent > 0 && bytesTotal > 0)
    {
        slot_setItemStatus(UPLOADING);
        if(bytesSent == bytesTotal)
        {
            slot_setItemStatus(FINISHED);

            //延时移除
            QTimer::singleShot(1000,0,[=](){
                slot_statusButtonClick();//移除
            });
        }
    }
    slot_setItemStatusText();

    //状态改变
    connect(this,&FilesItem::sig_sendItem_statusChanged,[=](FILESTATUS status){
        if(status == FINISHED)
        {
            ui->pushButton_pause->setDisabled(true);
            ui->pushButton_finish->setDisabled(true);
        }
    });
}

void FilesItem::slot_update_url_md5(const QString &url, const QString &md5)
{
//    qDebug() << QString(u8"video接收到传回的信息：")<< url << md5;
    m_body.furl     = url;
    m_body.fmd5     = md5;
    m_body.fname    =  ui->lineEdit_filename->text();
    m_body.fcover   =  ui->lineEdit_displaycover->text();//body创建新的item用的本地路径
    m_body.fsize    =  m_size;
    m_body.fnick    =  ui->lineEdit_displaytitle->text();
    m_body.fmedtype =  ui->comboBox_mtype->currentData().toString();
    m_body.fmedtheme=  ui->comboBox_mtheme->currentData().toString();
    m_body.fduration=  ui->lineEdit_mduration->text();
    //插入数据
    file_insertItemDataTodb(m_body);//插入数据库用的http传回来的路径
    emit sig_sendItem_finished(m_body);//创建新的完成的item
}

void FilesItem::slot_update_header(const QString &url_header, const QString &md5)
{
    //必须保证header的回传信息在video之前接收到
    qDebug() << QString(u8"header接收到传回的信息：")<< url_header << md5;
    m_picpath = url_header;
//    m_body.fcover = m_picpath;
}

/*插入数据库媒体信息*/
void FilesItem::file_insertItemDataTodb(const fileBody &body)
{
    qDebug() <<QString(u8"数据库插入前接收到的数据：");
    qDebug() << "alias      = :" << body.fnick;
    qDebug() << "url        = :" << body.furl;
    qDebug() << "fcover      = :" << body.fcover;
    qDebug() << "duration   = :" << body.fduration;
    qDebug() << "part of    = :" << body.fmedtheme;
    QStringList parma = {body.fnick,body.furl,body.fduration,m_picpath,QString(u8"8.8万"),body.fmedtheme};
//    dataBase::getInstance()->video_insertRecDramaListDB(parma);//插入数据
}

//模拟点击
void FilesItem::slot_pauseButtonClick()
{
    ui->pushButton_pause->click();
}

void FilesItem::slot_statusButtonClick()
{
    ui->pushButton_remove->click();//完成即移除
//    slot_setItemEdit(FILEEDIT::CANEDIT);
}

QString FilesItem::calCurrentFileSize(qint64 bytesTotal)
{
    int integer = 0;  //整数位
    int decimal = 0;  //小数位，保留三位
    char unit ='B';
    qint64 standardSize = bytesTotal;//qint64 long long int
    qint64 curSize = bytesTotal;

    if(standardSize > 1024) {
        curSize = standardSize * 1000;//目的是扩大为整数求取小数部分好计算
        curSize /= 1024;//curSize = curSize/1024 curSize单位为（B）
        integer = curSize / 1000;//变为B大小后，求整数部分
        decimal = curSize % 1000;//求余数mod()
        standardSize /= 1024;//整正的大小 standardSize
        unit = 'K';
        if(standardSize > 1024) {//KB大大小大于1024
            curSize = standardSize * 1000;
            curSize /= 1024;
            integer = curSize / 1000;
            decimal = curSize % 1000;
            standardSize /= 1024;
            unit = 'M';
            if(standardSize > 1024) {
                curSize = standardSize * 1000;
                curSize /= 1024;
                integer = curSize / 1000;
                decimal = curSize % 1000;
                unit = 'G';
            }
        }
    }

    QString dec = "0";
    if (0 <= decimal && decimal <= 9) {
        dec = dec + dec + QString::number(decimal);
    }

    if (10 <= decimal && decimal <= 99) {
        dec = "0" + QString::number(decimal);
    }

    if (100 <= decimal && decimal <= 999) {
        dec = QString::number(decimal);
    }

    return QString::number(integer) + "." + dec + unit;
}

int FilesItem::getCurtentComboBoxIndex(const QComboBox *combobox, const QString &itemtext)
{
    qDebug() << QString(u8"接收到的item data:")<<itemtext;
    for(int i = 0; i < combobox->count(); i++)
    {
        if(combobox->itemData(i,Qt::UserRole) == itemtext)
        {
            return i;//返回索引号
        }
    }
}

QString FilesItem::getCurtentComboBoxText(const QComboBox *combobox, const QString &itemtext)
{
    qDebug() << QString(u8"接收到的item data:")<<itemtext;
    for(int i = 0; i < combobox->count(); i++)
    {
        if(combobox->itemData(i,Qt::UserRole) == itemtext)
        {
            return combobox->itemText(i);//返回item文字
        }
    }
}


