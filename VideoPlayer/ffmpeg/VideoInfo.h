#ifndef VIDEOINFO_H
#define VIDEOINFO_H

#include <QObject>
#include <QLabel>
#include <QImage>
#include <QDebug>

//以下ffmpeg获取视频信息使用
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

class VideoInfo : public QObject
{
    Q_OBJECT
public:
    explicit VideoInfo(QObject *parent = nullptr);
//    static QImage      getVideo_image(const char* file);//获取视频第一帧图像
//    static QImage      getVideo_pos_image(const char* file,int pos);//获取视频任意一帧图像
//    static int         getVideo_duration(const char* file);//获取视频总时长

signals:

public slots:
};

#endif // VIDEOINFO_H
