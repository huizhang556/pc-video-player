#include "RecVideoItem.h"
#include "ui_RecVideoItem.h"

#include <QFontMetrics>
#include <QPixmap>
#include <QDebug>

RecVideoItem::RecVideoItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecVideoItem)
{
    ui->setupUi(this);
    this->setFixedSize(260,85);
    handleSignalsAndSlots();
    manager = new QNetworkAccessManager(this);
    ui->label_videoPic->installEventFilter(this);
    ui->pushButton_videoInfo->setCheckable(true);
    ui->pushButton_videoInfo->setChecked(false);

    ui->pushButton_playAmount->setIcon(QIcon("://images/icon/recvideo_amount.png"));
}

RecVideoItem::RecVideoItem(const QString &url, const QString& path, const QString time, QString info, QString count, QWidget *parent) :
    QWidget(parent),
    m_videoUrl(url),
    m_picPath(path),
    m_picTime(time),
    m_picInfo(info),
    m_picCount(count),
    ui(new Ui::RecVideoItem)
{
    ui->setupUi(this);
    this->setFixedHeight(85);
    this->setFixedWidth(250);
    handleSignalsAndSlots();
    ui->label_videoPic->installEventFilter(this);//获取点击事件
    ui->pushButton_videoInfo->setCheckable(true);
    ui->pushButton_videoInfo->setChecked(false);
    m_movie.setFileName(":/images/status/video_loading.gif");
    m_movie.setScaledSize(QSize(103,80));
    ui->label_videoPic->setMovie(&m_movie);
    m_movie.start();

    manager = new QNetworkAccessManager(this);
    ui->pushButton_playAmount->setIcon(QIcon("://images/icon/recvideo_amount.png"));
    setVideoPicture(m_picPath);//视频封面
    setVideoTime(m_picTime);//视频时长
    setVideoText(m_picInfo);//视频简介
    setVideoUpvoye(m_picCount);//视频观看数
}

RecVideoItem::~RecVideoItem()
{
    delete ui;
}

void RecVideoItem::handleSignalsAndSlots()
{
    //点击 信息部分 获取播放连接
    connect(ui->pushButton_videoInfo,&QPushButton::clicked,[=](){emit sig_sendVideoUrl();});
    //点击 播放部分 获取播放连接
    connect(ui->pushButton_play,&QPushButton::clicked,[=](){emit sig_sendVideoUrl();});
}

//void RecVideoItem::setVideoCover(const char *file)
//{
//    AVFormatContext* fmt_ctx_ = nullptr;

//        qDebug() << "111" << avcodec_version();

//        //打开视频文件
//        int errCode = avformat_open_input(&fmt_ctx_, file, nullptr, nullptr);
//        if(errCode != 0){
//            qDebug() << "avformat_open_input fail" << errCode;
//            return;
//        }
//        qDebug() << "222" ;
//        //读取音视频流信息
//        errCode = avformat_find_stream_info(fmt_ctx_, nullptr);
//        if(errCode != 0){
//            qDebug() << "avformat_find_stream_info fail" << errCode;
//            avformat_close_input(&fmt_ctx_);
//            return;
//        }
//        qDebug() << "333" ;
//        //打印输出视频相关信息
//        av_dump_format(fmt_ctx_, 0, file, 0);
//        qDebug() << "444" ;

//        AVPacket* pkt = av_packet_alloc();
//        AVFrame* temp_frame = av_frame_alloc();
//        SwsContext* sws_ctx = nullptr;
//        int ret = 0;
//        QImage preview;
//        bool preview_done = false;

//        int videoStream = 0;
//        for (int i = 0; i<int(fmt_ctx_->nb_streams) && !preview_done; i++){
//            //只处理视频信息
//            if (fmt_ctx_->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
//                //查找视频解码器
//                videoStream = i;
//                const AVCodec* codec = avcodec_find_decoder(fmt_ctx_->streams[i]->codecpar->codec_id);
//                AVCodecContext *codec_ctx = avcodec_alloc_context3(codec);
//                //根据提供的编解码器参数的值填充编解码器上下文
//                avcodec_parameters_to_context(codec_ctx, fmt_ctx_->streams[i]->codecpar);
//                //打开解码器
//                avcodec_open2(codec_ctx, codec, nullptr);
//                qDebug() << "555" ;
//                //读取帧数据
//                while (av_read_frame(fmt_ctx_, pkt) >= 0){
//                    if (pkt->stream_index == videoStream) {

//                        av_frame_unref(temp_frame);
//                        qDebug() << "666" ;
//                        //对视频帧数据进行解码
//                        while ((ret = avcodec_receive_frame(codec_ctx, temp_frame)) == AVERROR(EAGAIN)){
//                            ret = avcodec_send_packet(codec_ctx, pkt);
//                            qDebug() << "777" ;
//                            if (ret < 0) {
//                                qCritical() << "Failed to send packet to decoder." << ret;
//                                break;
//                            }
//                        }

//                        if(ret < 0 && ret != AVERROR_EOF){
//                            qDebug() << "Failed to receive packet from decoder." << ret;
//                            continue;
//                        }

//                        qDebug() << "777" << temp_frame->width << temp_frame->height;
//                        //等比例缩放
//                        int dstH = 240;
//                        int dstW = qRound(dstH * (float(temp_frame->width)/float(temp_frame->height)));
//                        //消除可能的告警
//                        dstH = (dstH >> 4) << 4;
//                        dstW = (dstW >> 4) << 4;

//                        qDebug() << "777" << dstW << dstH;

//                        sws_ctx = sws_getContext(
//                                    temp_frame->width,
//                                    temp_frame->height,
//                                    static_cast<AVPixelFormat>(temp_frame->format),
//                                    dstW,
//                                    dstH,
//                                    static_cast<AVPixelFormat>(AV_PIX_FMT_RGBA),
//                                    SWS_FAST_BILINEAR,
//                                    nullptr,
//                                    nullptr,
//                                    nullptr
//                                    );
//                        int linesize[AV_NUM_DATA_POINTERS];
//                        linesize[0] = dstW*4;
//                        qDebug() << "888" ;
//                        //生成图片
//                        preview = QImage(dstW, dstH, QImage::Format_RGBA8888);
//                        uint8_t* data = preview.bits();
//                        sws_scale(sws_ctx,
//                                  temp_frame->data,
//                                  temp_frame->linesize,
//                                  0,
//                                  temp_frame->height,
//                                  &data,
//                                  linesize);
//                        sws_freeContext(sws_ctx);

//                        qDebug() << "9999" ;
//                        avcodec_close(codec_ctx);
//                        avcodec_free_context(&codec_ctx);
//                        preview_done = true;
//                        break;
//                    }
//                }
//            }
//        }

//        qDebug() << "10" ;
//        av_frame_free(&temp_frame);
//        av_packet_free(&pkt);
//        avformat_close_input(&fmt_ctx_);
//        if(preview_done){
//            ui->label_videoPic->setPixmap(QPixmap::fromImage(preview));
//            ui->label_videoPic->setScaledContents(true);
//        }
//}

void RecVideoItem::setVideoPicture(const QString path)
{
    //方法1.常规网络获取图片（上传的时候已将封面作为图片存储在服务器上，此处只需要下载即可）
    manager->get(QNetworkRequest(QUrl(path)));
    //获取网络图片(注意：使用的是manager的finished信号)
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_replyFinished(QNetworkReply*)));
    //方法2.ffmpeg根据url获取视频封面(这里用的是成员函数,也可以是非成员函数)
//    QFuture<bool> result = QtConcurrent::run(this,&RecVideoItem::setVideoCover,m_videoUrl.toStdString().c_str());
//    result.waitForFinished();
//    qDebug() << QString(u8"图片加载的结果：") << result.result();
}

void RecVideoItem::setItemPicture(const QString path)
{
    ui->label_videoPic->setPixmap(QPixmap(path));
    ui->label_videoPic->setScaledContents(true);
}

void RecVideoItem::setVideoTime(const QString &time)
{
    ui->label_videoTime->setText(time);
}

void RecVideoItem::setVideoText(QString info)
{
    //参数使用引用导致成员数据改变，所以指定为值传递
    if(info.length() > 10)
    {
        info = info.insert(10,"\n");
    }
    QFont font;
    font.setPixelSize(10);
    QFontMetrics fontMetric = QFontMetrics(font);
    QString text = fontMetric.elidedText(info,Qt::ElideRight,190,0);//19个字宽以后，省略为...(10x19，字号x字数)
    ui->pushButton_videoInfo->setText(text);
}

void RecVideoItem::setVideoUpvoye(const QString &count)
{
    ui->pushButton_playAmount->setText(count);
}

void RecVideoItem::slot_replyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        ui->label_videoPic->setPixmap(pixmap);
        ui->label_videoPic->setScaledContents(true);//内容自适应
        if(m_movie.state() == QMovie::Running)
        {
            m_movie.stop();
        }
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("请求错误：")<<reply->errorString();
        QPixmap pixmap("://images/status/video_pixfaild.png");
        ui->label_videoPic->setPixmap(pixmap);
        ui->label_videoPic->setScaledContents(true);//内容自适应
        if(m_movie.state() == QMovie::Running)
        {
            m_movie.stop();
        }
    }
}


bool RecVideoItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->label_videoPic)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            emit sig_sendVideoUrl();
        }
    }
    return QWidget::eventFilter(watched,event);

}
