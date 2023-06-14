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

FilesItem::FilesItem(const FILEEDIT edit, const int id, const QUrl &url, const qint64 size, const QString &picpath, QWidget *parent):
    QWidget(parent),
    m_canedit(edit),
    m_fid(id),
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
    slot_setItemUrl(url);//本地url和网络url作以区别
    slot_setItemName();
    slot_setItemPicture();
    slot_setItemSize();
    slot_setItemStart(true);//默认显示"开始"
    slot_setItemStatus(m_status);
    slot_setItemStatusText();
    slot_setItemDuration();
    slot_setItemEdit(m_canedit);//设置状态
}

FilesItem::~FilesItem()
{
    delete ui;
}

void FilesItem::initWorkUI()
{
    videoTypeList = dataBase::getInstance()->getVideoMediaType();

    m_movie.setFileName(":/images/status/video_loading.gif");
    m_movie.setScaledSize(QSize(198,96));
    ui->label_pic->setMovie(&m_movie);
    m_movie.start();

//    this->setFocusPolicy(Qt::NoFocus);
    manager = new QNetworkAccessManager(this);

    ui->pushButton_remove->setToolTip(QString(u8"移除"));
    ui->label_pic->setAlignment(Qt::AlignCenter);

    ui->checkBox_selall->setCheckable(true);
    ui->checkBox_selall->setChecked(false);

    ui->progressBar->setValue(0);
    ui->progressBar->setRange(0,100);

    ui->pushButton_editinfo->setCheckable(true);
    ui->pushButton_editinfo->setChecked(false);
    ui->pushButton_editinfo->setText(QString(u8"编辑"));

    //文件名应该加正则限制
    ui->lineEdit_filename->setAlignment(Qt::AlignLeft);
    ui->lineEdit_filename->setToolTip(QString(u8"自定义文件名称"));
    ui->lineEdit_filename->setContextMenuPolicy(Qt::NoContextMenu);

    ui->lineEdit_displaytitle->setAlignment(Qt::AlignLeft);
    ui->lineEdit_displaytitle->setCursorPosition(0);
    ui->lineEdit_displaytitle->setContextMenuPolicy(Qt::NoContextMenu);

    ui->lineEdit_mduration->setAlignment(Qt::AlignLeft);
//    ui->lineEdit_mduration->setCursorPosition(0);
    ui->lineEdit_mduration->setContextMenuPolicy(Qt::NoContextMenu);

    ui->comboBox_mtype->setView(new QListView());
    ui->comboBox_mtype->addItem(QString(u8"电影"),QString(u8"movies"));
    ui->comboBox_mtype->addItem(QString(u8"网络剧"),QString(u8"netdrama"));
    ui->comboBox_mtype->addItem(QString(u8"短视频"),QString(u8"shortvideos"));
    ui->comboBox_mtype->addItem(QString(u8"中视频"),QString(u8"midvideos"));
    ui->comboBox_mtype->addItem(QString(u8"音乐"),QString(u8"musics"));
    ui->comboBox_mtype->addItem(QString(u8"图片"),QString(u8"pictures"));

    ui->comboBox_mtheme->setView(new QListView());
    foreach (QString type, videoTypeList)
    {
        ui->comboBox_mtheme->addItem(type,type);
    }

    //combobox 禁止垂直滚动条和竖直滚动条
    ui->comboBox_mtype->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->comboBox_mtype->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->comboBox_mtheme->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->comboBox_mtheme->view()->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->lineEdit_displaycover->setPlaceholderText(QString(u8"选择自定义封面"));
    ui->lineEdit_displaycover->setReadOnly(true);//只读
    ui->lineEdit_displaycover->setContextMenuPolicy(Qt::NoContextMenu);

    ui->stackedWidget_info->setCurrentIndex(0);
}

void FilesItem::handleSignalsAndSlots()
{
    connect(ui->pushButton_remove,&QPushButton::clicked,[=](){
        emit sig_sendItem_remove();
    });

    //取消勾选(带回来的状态是勾选以后的状态)
    connect(ui->checkBox_selall,&QCheckBox::clicked,[=](bool checked){
        qDebug() <<QString(u8"勾选状态:") << checked;
        if(!checked)
        {
            slot_setSelButtonChecked(false);
        }
    });

    connect(ui->pushButton_pause,&QPushButton::clicked,[=](bool checked){
        if(m_canedit == FILEEDIT::CANWRITE)
        {
            //可修改状态下
            if(!checked)
            {
                ui->pushButton_pause->setText(QString(u8"暂停"));
            }
            else
            {
                ui->pushButton_pause->setText(QString(u8"开始"));
            }
            qDebug() <<QString(u8"发送下载的URL：%1").arg(m_furl);
            // emit sig_sendItem_pause(checked,QUrl(m_furl),QUrl(m_picpath));
            QByteArray imageArray;
            QBuffer buffer;
            buffer.open(QIODevice::WriteOnly);
            m_cover.save(&buffer,"png");//QImage存进buffer转为QByteArray
            imageArray.append(buffer.data());
            QUrlQuery urlQuery;
            urlQuery.addQueryItem(QString(u8"url"),m_furl);//url
            //别名应该有特殊字符转换，且在输入文件的别名的时候就应该使用正则限制
//            urlQuery.addQueryItem(QString(u8"rename"),ui->lineEdit_filename->text().replace(" ","_").trimmed());//别名去空格（格式应为： xxx.flv等，加后缀）
            //改用将QString 转换为 Base64 特殊字符也能包含进去，只是将名称改变
            QString rename  = QStrToBase64(ui->lineEdit_filename->text());
            urlQuery.addQueryItem(QString(u8"rename"),rename);
            emit sig_sendItem_upload(checked,urlQuery,imageArray);
        }
        else if(m_canedit == FILEEDIT::CANEDIT)
        {
            //只读状态下
            emit sig_sendItem_play();
        }
        else if(m_canedit == FILEEDIT::DISPLAY)
        {
            //展示状态
            emit sig_sendItem_play();
        }

    });

    //下载
    connect(ui->pushButton_finish,&QPushButton::clicked,[=](){
        QUrlQuery query;
        query.addQueryItem(QString(u8"nick"),ui->lineEdit_displaytitle->text());
        query.addQueryItem(QString(u8"url"),m_furl);
        emit sig_sendItem_download(query);
        qDebug() << QString(u8"下载");
    });

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
            else if(m_canedit == FILEEDIT::DISPLAY)
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
//    connect(ui->lineEdit_displaycover,&QLineEdit::returnPressed,[=](){
//        if(!ui->lineEdit_displaycover->text().trimmed().isEmpty())
//        {
//            ui->lineEdit_displaycover->setText(ui->lineEdit_displaycover->text().trimmed());
//            if(ui->lineEdit_displaycover->hasFocus()) ui->lineEdit_displaycover->clearFocus();
//        }
//    });


    //自定义封面
    connect(ui->pushButton_opencover,&QPushButton::clicked,[=](){
        QString filename_cover = QFileDialog::getOpenFileName();
        qDebug() <<QString(u8"封面路径：") << filename_cover;
        if(filename_cover.isEmpty())
        {
            return;
        }
        else
        {
//            m_picpath = filename_cover;
//            slot_setItemPicture();
            ui->label_pic->setPixmap(QPixmap(filename_cover));
            ui->label_pic->setScaledContents(true);
            m_cover = ui->label_pic->pixmap()->toImage();//选择以后需要将选择的图片转换为QImage
            ui->lineEdit_displaycover->setText(filename_cover);
            if(ui->lineEdit_mduration->hasFocus()) ui->lineEdit_mduration->clearFocus();
            qDebug() <<QString(u8"封面设置成功！");
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


}

void FilesItem::setInstallEventFilter()
{
    this->installEventFilter(this);
    ui->label_pic->installEventFilter(this);
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

int FilesItem::getItem_fid()
{
    return m_fid;
}

QString FilesItem::getItem_furl()
{
    return m_furl;
}

void FilesItem::slot_setItemEdit(const FILEEDIT edit)
{
    switch (edit)
    {
    case CANWRITE://上传展示
    {
        ui->pushButton_pause->setCheckable(true);
        ui->pushButton_pause->setChecked( true);
        ui->stackedWidget_check->setCurrentWidget(ui->page_close);
    }
        break;
    case DISPLAY://对外展示
    {
        m_rmenu = true;//可以右键
        ui->lineEdit_filename->setReadOnly(true);
        ui->progressBar->setHidden(true);
        ui->pushButton_editinfo->setText(QString(u8"详细"));
        ui->pushButton_pause->setText(QString(u8"播放"));
        ui->pushButton_pause->setCheckable(false);
        ui->pushButton_finish->setText(QString(u8"下载"));
        ui->pushButton_finish->setDisabled(false);
        ui->pushButton_opencover->setDisabled(true);//封面不能更换
        ui->stackedWidget_check->setCurrentWidget(ui->page_close);//显示关闭按钮
        ui->pushButton_editinfo->hide();
        ui->stackedWidget_check->hide();
    }
        break;
    case CANEDIT://完成展示
    {
        m_rmenu = true;//可以右键
        ui->lineEdit_filename->setReadOnly(true);
        ui->progressBar->setHidden(true);
        ui->pushButton_editinfo->setText(QString(u8"详细"));
        ui->pushButton_pause->setText(QString(u8"播放"));
        ui->pushButton_pause->setCheckable(false);
        ui->pushButton_finish->setText(QString(u8"下载"));
        ui->pushButton_finish->setDisabled(false);
        ui->pushButton_opencover->setDisabled(true);
        ui->stackedWidget_check->setCurrentWidget(ui->page_close);
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
        ui->label_pic->setLabWarnText(QString(u8"待上传"));
    }
        break;
    case WAITING:
    {
        m_curStatus = QString(u8"等待中");
        ui->label_pic->setLabWarnText(QString(u8"等待中"));
    }
        break;
    case UPLOADING:
    {
        m_curStatus = QString(u8"上传中");
        ui->label_pic->setLabWarnText(QString(u8"上传中"));
    }
        break;
    case FINISHED:
    {
        m_canedit = FILEEDIT::CANEDIT;
        m_curStatus = QString(u8"已完成");
        ui->label_pic->setLabWarnText(QString(u8"已完成"));
        ui->pushButton_editinfo->setText(QString(u8"详细"));
        ui->pushButton_pause->setText(QString(u8"播放"));
    }
        break;
    case UNKNOW:
    {
        m_curStatus = QString(u8"上传错误");
        ui->label_pic->setLabWarnText(QString(u8"上传失败！"));
        ui->pushButton_pause->setText(QString(u8"重传"));
    }
        break;
    default:
        break;
    }
    slot_setItemStatusText();
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

//本地url和网络url作以区别
void FilesItem::slot_setItemUrl(QUrl url)
{
    if(m_canedit == FILEEDIT::CANEDIT || m_canedit == FILEEDIT::DISPLAY)
        m_furl = url.toString();
        else
        m_furl = url.path().remove(0,1);
}

void FilesItem::slot_setItemSize()
{
    ui->label_size->setText(QString(u8"大小：%1").arg(calCurrentFileSize(m_size)));
}


void FilesItem::slot_setItemName()
{
    if(m_canedit == FILEEDIT::CANWRITE)//上传时不加密
    {
        ui->lineEdit_filename->setText(m_name);
        ui->lineEdit_displaytitle->setText(m_name.split(".").first());
    //    ui->lineEdit_filename->setCursorPosition(0);鼠标到达最左边
        ui->lineEdit_filename->setFocusPolicy(Qt::ClickFocus);
        ui->label_pic->setToolTip(m_name);
    }
    else//需要解析（CANEDIT情况 + DISPLAY情况）
    {
        ui->lineEdit_filename->setText(Base64ToQStr(m_name));//filename直接解析出来
        ui->lineEdit_filename->setToolTip(nullptr);
        ui->lineEdit_displaytitle->setText(Base64ToQStr(m_name).split(".").first());//解析出来的文件名去后缀
    //    ui->lineEdit_filename->setCursorPosition(0);鼠标到达最左边
        ui->lineEdit_filename->setFocusPolicy(Qt::ClickFocus);
        ui->label_pic->setToolTip(nullptr);
    }
}

//根据不同情况加载图片（视频截取或者自定义封面）
void FilesItem::slot_setItemPicture()
{
    switch (m_canedit) {
    case DISPLAY:
    case CANEDIT:
    {
        manager->get(QNetworkRequest(QUrl(m_picpath)));//网络路径
        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_replyCoverFinished(QNetworkReply*)));
    }
        break;
    case CANWRITE://上传时获取视频封面的方法
    {
        QFileInfo info(m_furl);
        QString suffix = info.suffix();
        qDebug() << QString(u8"完成的item：url = %1, 后缀：%2").arg(m_furl).arg(suffix);
        if(suffix == "mp3")
        {
            ui->label_pic->setPixmap(QPixmap(":/images/creator/fileitem_music.png"));
        }
        else if(suffix == "aac")
        {
            ui->label_pic->setPixmap(QPixmap(":/images/creator/fileitem_music.png"));
        }
        else if(suffix == "mp4")
        {
            slot_getVideoPicure(m_furl.toStdString().c_str(),ui->label_pic);
        }
        else if(suffix == "flv")
        {
            slot_getVideoPicure(m_furl.toStdString().c_str(),ui->label_pic);
        }
        else if(suffix == "wav")
        {
            slot_getVideoPicure(m_furl.toStdString().c_str(),ui->label_pic);
        }
        else if(suffix == "3gp")
        {
            slot_getVideoPicure(m_furl.toStdString().c_str(),ui->label_pic);
        }
        else if(suffix == "avi")
        {
            slot_getVideoPicure(m_furl.toStdString().c_str(),ui->label_pic);
        }
        else if(suffix == "png")
        {
            ui->label_pic->setPixmap(QPixmap("://images/creator/fileitem_picture.png"));
            if(m_canedit ==FILEEDIT::CANEDIT || m_canedit ==FILEEDIT::DISPLAY)
                ui->pushButton_pause->setHidden(true);
        }
        else if(suffix == "gif")
        {
            ui->label_pic->setPixmap(QPixmap("://images/creator/fileitem_picture.png"));
            if(m_canedit ==FILEEDIT::CANEDIT || m_canedit ==FILEEDIT::DISPLAY)
                ui->pushButton_pause->setHidden(true);
        }
        else if(suffix == "jpg")
        {
            ui->label_pic->setPixmap(QPixmap("://images/creator/fileitem_picture.png"));
            if(m_canedit ==FILEEDIT::CANEDIT || m_canedit ==FILEEDIT::DISPLAY)
                ui->pushButton_pause->setHidden(true);
        }

        else
        {
            ui->label_pic->setPixmap(QPixmap(":/images/creator/fileitem_videos.png"));
            if(m_canedit ==FILEEDIT::CANEDIT || m_canedit ==FILEEDIT::DISPLAY)
                ui->pushButton_pause->setHidden(true);
        }
        ui->label_pic->setScaledContents(true);
    }
        break;
    default:
        break;
    }

//    if(m_canedit == FILEEDIT::CANEDIT)//作品展示时，获取视频封面的方法（使用网络封面）
//    {
//        manager->get(QNetworkRequest(QUrl(m_picpath)));//网络路径
//        connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_replyCoverFinished(QNetworkReply*)));
//    }
//    else if(m_canedit == FILEEDIT::CANWRITE)//上传时获取视频封面的方法
//    {
//        QFileInfo info(m_furl);
//        QString suffix = info.suffix();
//        qDebug() << QString(u8"完成的item：url = %1, 后缀：%2").arg(m_furl).arg(suffix);
//        if(suffix == "mp3")
//        {
//            ui->label_pic->setPixmap(QPixmap(":/images/creator/fileitem_music.png"));
//        }
//        else if(suffix == "aac")
//        {
//            ui->label_pic->setPixmap(QPixmap(":/images/creator/fileitem_music.png"));
//        }
//        else if(suffix == "mp4")
//        {
//            slot_getVideoPicure(m_furl.toStdString().c_str(),ui->label_pic);
//        }
//        else if(suffix == "flv")
//        {
//            slot_getVideoPicure(m_furl.toStdString().c_str(),ui->label_pic);
//        }
//        else if(suffix == "wav")
//        {
//            slot_getVideoPicure(m_furl.toStdString().c_str(),ui->label_pic);
//        }
//        else if(suffix == "3gp")
//        {
//            slot_getVideoPicure(m_furl.toStdString().c_str(),ui->label_pic);
//        }
//        else if(suffix == "avi")
//        {
//            slot_getVideoPicure(m_furl.toStdString().c_str(),ui->label_pic);
//        }
//        else if(suffix == "png")
//        {
//            ui->label_pic->setPixmap(QPixmap("://images/creator/fileitem_picture.png"));
//            if(m_canedit ==FILEEDIT::CANEDIT)
//                ui->pushButton_pause->setHidden(true);
//        }
//        else if(suffix == "gif")
//        {
//            ui->label_pic->setPixmap(QPixmap("://images/creator/fileitem_picture.png"));
//            if(m_canedit ==FILEEDIT::CANEDIT)
//                ui->pushButton_pause->setHidden(true);
//        }
//        else if(suffix == "jpg")
//        {
//            ui->label_pic->setPixmap(QPixmap("://images/creator/fileitem_picture.png"));
//            if(m_canedit ==FILEEDIT::CANEDIT)
//                ui->pushButton_pause->setHidden(true);
//        }
//        else
//        {
//            ui->label_pic->setPixmap(QPixmap(":/images/creator/fileitem_videos.png"));
//            if(m_canedit ==FILEEDIT::CANEDIT)
//                ui->pushButton_pause->setHidden(true);
//        }
//        ui->label_pic->setScaledContents(true);
//    }
}

void FilesItem::slot_setItemDuration()
{
    ui->lineEdit_mduration->setText(m_duration);
}

void FilesItem::slot_getVideoPicure(const char *file, QLabel *label)
{

    AVFormatContext* fmt_ctx_ = nullptr;

        qDebug() << "111" << avcodec_version();

        //打开视频文件
        int errCode = avformat_open_input(&fmt_ctx_, file, nullptr, nullptr);
        if(errCode != 0){
            qDebug() << "avformat_open_input fail" << errCode;
            return;
        }
        qDebug() << "222" ;
        //读取音视频流信息
        errCode = avformat_find_stream_info(fmt_ctx_, nullptr);
        switchFormatTime(fmt_ctx_->duration/1000000);
        qDebug() << QString(u8"视频时长：%1 ").arg(m_duration);
        if(errCode != 0){
            qDebug() << "avformat_find_stream_info fail" << errCode;
            avformat_close_input(&fmt_ctx_);
            return;
        }
        qDebug() << "333" ;
        //打印输出视频相关信息
        av_dump_format(fmt_ctx_, 0, file, 0);
        qDebug() << "444" ;

        AVPacket* pkt = av_packet_alloc();
        AVFrame* temp_frame = av_frame_alloc();
        SwsContext* sws_ctx = nullptr;
        int ret = 0;
        QImage preview;
        bool preview_done = false;

        int videoStream = 0;
        for (int i = 0; i<int(fmt_ctx_->nb_streams) && !preview_done; i++){
            //只处理视频信息
            if (fmt_ctx_->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                //查找视频解码器
                videoStream = i;
                const AVCodec* codec = avcodec_find_decoder(fmt_ctx_->streams[i]->codecpar->codec_id);
                AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
                //根据提供的编解码器参数的值填充编解码器上下文
                avcodec_parameters_to_context(codec_ctx, fmt_ctx_->streams[i]->codecpar);
                //打开解码器
                avcodec_open2(codec_ctx, codec, nullptr);
                qDebug() << "555" ;
                //读取帧数据
                while (av_read_frame(fmt_ctx_, pkt) >= 0){
                    if (pkt->stream_index == videoStream) {

                        av_frame_unref(temp_frame);
                        qDebug() << "666" ;
                        //对视频帧数据进行解码
                        while ((ret = avcodec_receive_frame(codec_ctx, temp_frame)) == AVERROR(EAGAIN)){
                            ret = avcodec_send_packet(codec_ctx, pkt);
                            qDebug() << "777" ;
                            if (ret < 0) {
                                qCritical() << "Failed to send packet to decoder." << ret;
                                break;
                            }
                        }

                        if(ret < 0 && ret != AVERROR_EOF){
                            qDebug() << "Failed to receive packet from decoder." << ret;
                            continue;
                        }

                        qDebug() << "777" << QString(u8"视频宽：") << temp_frame->width
                                 <<  QString(u8"视频高：") << temp_frame->height;
                        //等比例缩放
                        int dstH = 240;
                        int dstW = qRound(dstH * (float(temp_frame->width)/float(temp_frame->height)));
                        //消除可能的告警
                        dstH = (dstH >> 4) << 4;
                        dstW = (dstW >> 4) << 4;

                        qDebug() << "777" << dstW << dstH;

                        sws_ctx = sws_getContext(
                                    temp_frame->width,
                                    temp_frame->height,
                                    static_cast<AVPixelFormat>(temp_frame->format),
                                    dstW,
                                    dstH,
                                    static_cast<AVPixelFormat>(AV_PIX_FMT_RGBA),
                                    SWS_FAST_BILINEAR,
                                    nullptr,
                                    nullptr,
                                    nullptr
                                    );
                        int linesize[AV_NUM_DATA_POINTERS];
                        linesize[0] = dstW*4;
                        qDebug() << "888" ;
                        //生成图片
                        preview = QImage(dstW, dstH, QImage::Format_RGBA8888);
                        uint8_t* data = preview.bits();
                        sws_scale(sws_ctx,
                                  temp_frame->data,
                                  temp_frame->linesize,
                                  0,
                                  temp_frame->height,
                                  &data,
                                  linesize);
                        sws_freeContext(sws_ctx);

                        qDebug() << "9999" ;
                        avcodec_close(codec_ctx);
                        avcodec_free_context(&codec_ctx);
                        preview_done = true;
                        break;
                    }
                }
            }
        }

        qDebug() << "10" ;
        av_frame_free(&temp_frame);
        av_packet_free(&pkt);
        avformat_close_input(&fmt_ctx_);
        if(preview_done){
            m_cover = preview;
            label->setPixmap(QPixmap::fromImage(m_cover));
        }
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
            //此时完成
        }
    }
//    slot_setItemStatusText();

    //状态改变
    connect(this,&FilesItem::sig_sendItem_statusChanged,[=](FILESTATUS status){
        if(status == FINISHED)
        {
            ui->pushButton_pause->setDisabled(true);
            ui->pushButton_finish->setDisabled(true);
        }
    });
}

//回传回来的上传文件信息
void FilesItem::slot_update_url_md5(bool sucess, const QString &url, const QString &md5)
{
    if(sucess)//成功上传
    {
        m_body.furl     = url;//文件url
        m_body.fmd5     = md5;//文件md5
        m_body.fname    =  ui->lineEdit_filename->text();//重命名以后的名称
        m_body.fcover   =  ui->lineEdit_displaycover->text();//body创建新的item用的本地路径
        m_body.fsize    =  m_size;//int，不是转换为时分秒的字符串
        m_body.fnick    =  ui->lineEdit_displaytitle->text();//重新修改以后的介绍
        m_body.fmedtype =  ui->comboBox_mtype->currentData().toString();//是data数据，英文（movies）
        m_body.fmedtheme=  ui->comboBox_mtheme->currentData().toString();
        m_body.fduration=  ui->lineEdit_mduration->text();//加载文件时候计算好的
        //插入数据
        file_insertItemDataTodb(m_body);//插入数据库用的http传回来的路径
    //    emit sig_sendItem_finished(m_body);//创建新的完成的item（暂时无用了）
    }
    else//上传解析失败
    {

        slot_setItemStatus(UNKNOW);//设置为UNKNOW，数据库插入失败也是如此处理！
    }
}

void FilesItem::slot_update_header(bool success,const QString &url_header, const QString &md5)
{
    //必须保证header的回传信息在video之前接收到
    qDebug() << QString(u8"header接收到传回的信息：")<< url_header << md5;
    m_picpath = url_header;
//    m_body.fcover = m_picpath;
}

/*插入数据库媒体信息*/
void FilesItem::file_insertItemDataTodb(const fileBody &body)
{
    qDebug() <<QString(u8"准备往数据库插入数据，确认信息：");
    qDebug() << "alias      = :" << body.fnick;
    qDebug() << "url        = :" << body.furl;
    qDebug() << "fcover      = :" << body.fcover;
    qDebug() << "duration   = :" << body.fduration;
    qDebug() << "type       = :" << body.fmedtype;
    qDebug() << "theme      = :" << body.fmedtheme;
    qDebug() << "size       = :" << body.fsize;
    QStringList parma = {body.fnick.toUtf8(),body.furl.toUtf8(),body.fduration,m_picpath,QString(u8"8.8万"),body.fmedtype,body.fmedtheme,QString::number(body.fsize)};
    bool success = dataBase::getInstance()->video_insertRecDramaListDB(parma);//插入数据
    if(success)
    {
        slot_setItemStatus(FINISHED);//设置为完成状态
        //延时移除
        QTimer::singleShot(1000,0,[=](){
            slot_statusButtonClick();//应该由数据库插入成功通知移除
        });
    }
    else
    {
        slot_setItemStatus(UNKNOW);//设置为完成状态
    }
}

QString FilesItem::QStrToBase64(QString str)
{
    QByteArray byteA;
    byteA=str.toUtf8();
    byteA=byteA.toBase64();
    char* cbyteA=byteA.data();
    return QString(cbyteA);
}

QString FilesItem::Base64ToQStr(QString base64Str)
{
    QByteArray byteA;
    std::string stdStr = base64Str.toStdString();
    byteA=QByteArray(stdStr.c_str() );
    byteA=byteA.fromBase64(byteA);
    return  QString::fromUtf8(byteA);
}

void FilesItem::createContextMenu(const QStringList &menulist)
{
    QMenu menu;
    for(int i = 0; i < menuList.count(); i++)
    {
        menu.addAction(menulist.at(i));
    }
    menu.exec(QCursor::pos());
}

void FilesItem::slot_replyCoverFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        ui->label_pic->setPixmap(pixmap);
        ui->label_pic->setScaledContents(true);//内容自适应
        if(m_movie.state() == QMovie::Running)
        {
            m_movie.stop();
        }
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("请求错误：")<<reply->errorString();
        QPixmap pixmap("://images/status/video_pixfaild.png");
        ui->label_pic->setPixmap(pixmap);
        ui->label_pic->setScaledContents(true);//内容自适应
        if(m_movie.state() == QMovie::Running)
        {
            m_movie.stop();
        }
    }
}


//模拟点击
void FilesItem::slot_pauseButtonClick()
{
    ui->pushButton_pause->click();
}

//上传完成
void FilesItem::slot_statusButtonClick()
{
    ui->pushButton_remove->click();//完成即移除
    //    slot_setItemEdit(FILEEDIT::CANEDIT);
}

void FilesItem::slot_setSelButtonChecked(const bool checked)
{
    if(checked)
    {
        ui->checkBox_selall->setChecked(true);
        ui->stackedWidget_check->setCurrentWidget(ui->page_check);
    }
    else
    {
        ui->checkBox_selall->setChecked(false);
        ui->stackedWidget_check->setCurrentWidget(ui->page_close);
    }
}

bool FilesItem::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *mevent = static_cast<QMouseEvent*>(event);
    if(watched == this && event->type() == QEvent::Enter)
    {

    }
    if(watched == ui->label_pic)
    {
        if(event->type() == QEvent::MouseButtonPress && mevent->buttons() & Qt::RightButton && m_rmenu)
        {
//            createContextMenu(menuList);
        }
        else if(event->type() == QEvent::MouseButtonPress && mevent->buttons() & Qt::LeftButton && m_canedit == FILEEDIT::CANEDIT)
        {
            //FILEEDIT::CANEDIT有两种情况：只在分类的时候才展示
            emit sig_sendItem_clicked();
        }
        else if(event->type() == QEvent::Enter)
        {
            setCursor(Qt::PointingHandCursor);
        }
        else if(event->type() == QEvent::Leave)
        {
            setCursor(Qt::ArrowCursor);
        }
    }
    return QWidget::eventFilter(watched,event);
}

//秒转时分秒
QString FilesItem::switchFormatTime(qint64 total)
{
    //换算公式：1s = 10^3 ms = 10^6 us
    int hh = total / (60 * 60);
        int mm = (total- (hh * 60 * 60)) / 60;
        int ss = (total - (hh * 60 * 60)) - mm * 60;

        QString hour = QString::number(hh, 10);
        QString min = QString::number(mm, 10);
        QString sec = QString::number(ss, 10);

        if (hour.length() == 1)
            hour = "0" + hour;
        if (min.length() == 1)
            min = "0" + min;
        if (sec.length() == 1)
            sec = "0" + sec;

        QString strTime = hour + ":" + min + ":" + sec;
        m_duration = strTime;
        return strTime;
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


