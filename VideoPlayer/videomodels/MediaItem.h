#ifndef MEDIAITEM_H
#define MEDIAITEM_H

#include <QWidget>
#include <QIcon>
#include <QFontMetrics>

//item根据不同类型显示
enum  MEDTYPE
{
    MED_NORMAL,//正常（带删除，下载，收藏）
    MED_COLLECT,//收藏（带收藏，下载）
    MED_HISTORY//播放记录（带时长）
};

namespace Ui {
class MediaItem;
}

class MediaItem : public QWidget
{
    Q_OBJECT

public:
    explicit MediaItem(QWidget *parent = nullptr);
    explicit MediaItem(MEDTYPE type, const QString& mediaurl, const QString& icon, const QString& mediaName, bool islove, const QString& mediaDuration, QWidget *parent = nullptr);
    ~MediaItem();
    void            initWorkUI();
    void            handleSignalAndSlots();
    void            setMediaTypeStackPage(MEDTYPE type);
    const QString   getMedia_url();

private:
    void            setMedia_type();
    void            setMedia_icon();
    void            setMedia_name();
    void            setMedia_islove();
    void            setMedia_duration();

private:
    Ui::MediaItem *ui;
    MEDTYPE     m_mediaType;
    QString     m_mediaUrl;
    QString     m_mediaIcon;
    QString     m_mediaName;
    QString     m_mediaDuration;
    bool        m_isLove;//是否收藏

signals:
    void    sig_media_collect(bool);
    void    sig_media_delete();
    void    sig_media_download();

};

#endif // MEDIAITEM_H
