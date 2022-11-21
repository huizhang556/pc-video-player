#include "videosurface.h"

VideoSurface::VideoSurface(QObject *parent) : QAbstractVideoSurface(parent)
{

}

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const
{
    Q_UNUSED(type);
    QList<QVideoFrame::PixelFormat> list;
    list<<QVideoFrame::Format_RGB32<<QVideoFrame::Format_RGB32;
    return  list;
}

bool VideoSurface::present(const QVideoFrame &frame)
{
    if(frame.isValid())
    {
        QVideoFrame cloneFrame(frame);
        cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
        QImage img(cloneFrame.bits(),cloneFrame.width(),cloneFrame.height(),QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat()));
        cloneFrame.unmap();
        emit showImage(img);
        return true;
    }
    return  false;
}
