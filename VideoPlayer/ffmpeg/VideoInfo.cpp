#include "VideoInfo.h"

VideoInfo::VideoInfo(QObject *parent) : QObject(parent)
{

}

//QImage VideoInfo::getVideo_image(const char *file)
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
//            return preview;
//        }
//}

//QImage VideoInfo::getVideo_pos_image(const char *file, int pos)
//{

//}

//int VideoInfo::getVideo_duration(const char *file)
//{

//}
