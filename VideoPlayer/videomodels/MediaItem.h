#ifndef MEDIAITEM_H
#define MEDIAITEM_H

#include <QWidget>
#include <QIcon>
#include <QFontMetrics>

namespace Ui {
class MediaItem;
}

class MediaItem : public QWidget
{
    Q_OBJECT

public:
    explicit MediaItem(QWidget *parent = nullptr);
    explicit MediaItem(const QString& mediaurl, const QString& icon, const QString& mediaName, bool islove, QWidget *parent = nullptr);
    ~MediaItem();
    void            initWorkUI();
    void            handleSignalAndSlots();

    const QString   getMedia_url();

private:
    void            setMedia_icon();
    void            setMedia_name();
    void            setMedia_islove();

private:
    Ui::MediaItem *ui;
    QString     m_mediaUrl;
    QString     m_mediaIcon;
    QString     m_mediaName;
    bool        m_isLove;//是否收藏

signals:
    void    sig_media_collect(bool);
    void    sig_media_delete();
    void    sig_media_download();

};

#endif // MEDIAITEM_H
