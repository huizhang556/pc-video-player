#ifndef CUSHSLIDER_H
#define CUSHSLIDER_H

#include "ValueToImage.h"
#include <QSlider>
#include <QImage>
#include <QTimer>
#include <QPushButton>
#include <QMouseEvent>
#include <QDebug>

//以下ffmpeg获取视频信息使用
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libswresample/swresample.h>
}

class CusHSlider : public QSlider
{
    Q_OBJECT

public:
    explicit CusHSlider(QWidget *parent = nullptr);
    ~CusHSlider();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();
    void    setSpacing(int spacing);
    void    setOpenTipImage(bool on);
    void    setLoadingStatus(const QString &text);
    void    updateValueToImage(QImage& image);//显示图像

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

protected:
    void    updateSeekPosition(QMouseEvent *event);//游标+图像更新
    void    updateVernierPosition(QMouseEvent *event);//更新游标的位置
    void    updateValueImagePosition(QMouseEvent *event);//更细固定位置图显示的图像

signals:
    void    sig_valueToPosition(int);
    void    sig_anyValuePosition(int);

private:
    void    ffmpeg_getVideoImageFrom_pos(const char *file, int seconds);

private:
    int     m_spacing   = 0;//画面与slider间隔
    bool    m_isImage   = false;//是否开始画面，默认开启
    bool    m_use       = false;//是否显示游标，默认不显示
    QPushButton     *m_seekBtn =  nullptr;
    ValueToImage    *m_frameImages = nullptr;

    QString style_hslider = R"(QSlider:horizontal
                            {
                            margin: 0px 0px 0px 0px;
                            }

                            /*整个进度条*/
                            QSlider::groove:horizontal
                            {
                            background-color: rgba(255,255,255,0.1);
                            height: 1px;
                            border-radius:1px;
                            }


                            /*整个进度条-hover*/
                            QSlider::groove:horizontal:hover
                            {
                            background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5,
                            stop:0.6 #45ADED, stop:0.778409 rgba(255, 255, 255, 255));
                            height: 2px;
                            border-radius:1px;
                            }

                            /*J拖动按钮*/
                            QSlider::handle:horizontal
                            {
                            background-color:qlineargradient(spread:pad,x1:0,y1:0,x2:1,y2:0,stop:0 rgba(0, 205, 76,1.0), stop:1  rgba(24, 247, 51,1.0));
                            height:14px;
                            width:14px;
                            margin-top: -7px;
                            margin-bottom: -7px;
                            margin-left: -3px;
                            margin-right: -3px;
                            border-radius:7px;
                            border-image: url(:/images/icon/player_slider_normal.png);
                            background-color: transparent;
                            }

                            /*J拖动按钮-hover,只跟groove的hover时高度影响*/
                            QSlider::handle:horizontal:hover
                            {
                            height:14px;
                            width:14px;
                            margin-top: -7px;
                            margin-bottom: -7px;
                            margin-left: -3px;
                            margin-right: -3px;
                            border-radius:7px;
                            border-image: url(:/images/icon/player_slider_hover.png);
                            background-color: transparent;
                            }

                            /*未划过的区域，右边界线*/
                            QSlider::add-page:horizontal,QSlider::add-line:horizontal
                            {
                            border-radius:2px;
                            background-color:yellow;
                            }

                            /*已划过的区域，左边界线*/
                            QSlider::sub-page:horizontal,QSlider::sub-line:horizontal
                            {
                            border-radius:2px;
                            background-color:qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(231,80,229, 255), stop:1 rgba(7,208,255, 255));
                            }
                        )";

};

#endif // CUSHSLIDER_H
