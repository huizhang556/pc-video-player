#ifndef DOWNLOADTYPE_H
#define DOWNLOADTYPE_H

#include <QDialog>
#include <QTimer>
#include <QEvent>
#include <QVector>
#include <QVariant>
#include <QListView>
#include <QComboBox>
#include <QClipboard>
#include <QRadioButton>
#include <QButtonGroup>
#include <QFileDialog>
#include <QMouseEvent>
#include <QTableWidgetItem>
#include <QDebug>

struct VideoBody
{
    QString videoText;//VIP类型
    bool    videoVip;//是否需要会员
    QString videoSize;//大小
};
Q_DECLARE_METATYPE(VideoBody)

namespace Ui {
class DownloadType;
}

class DownloadType : public QDialog
{
    Q_OBJECT

public:
    ~DownloadType();
    static DownloadType* getInstance();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    showDownloadForm(int type, const QString& name = "",const QString& url = "");

protected:
   void  mousePressEvent(QMouseEvent *event) override;
   bool  eventFilter(QObject *watched, QEvent *event) override;

private:
   explicit DownloadType(QWidget *parent = nullptr);
    Ui::DownloadType *ui;
    static DownloadType* m_pInstance;
    QButtonGroup    *m_buttonGroup = nullptr;
    QComboBox       *m_comboBox    = nullptr;
    QRadioButton    *m_radioBtn1   = nullptr;
    QRadioButton    *m_radioBtn2   = nullptr;
    QRadioButton    *m_radioBtn3   = nullptr;
    QRadioButton    *m_radioBtn4   = nullptr;
    QRadioButton    *m_radioBtn5   = nullptr;

    int                m_userRow;//已占用行
    int                m_userType;//用户等级
    int                m_sourceType;//资源类型 0 song 1 video
    bool               m_sourceVip;//是否为vip资源 0 否 1 是
    QString            m_sourceUrl;//资源路径
    QString            m_quality;//质量
    QString            m_curOpenPath;//当前下载文件存储路径
    QVector<QVariant>  m_videoVector;//视频类信息

private:
    const   QString openLocalFileSystem();
    bool    judgePathExist(const QString &path);//判断路径是否存在

    void    addSongQualityItem_1(bool vip, const QString& size);//流畅
    void    addSongQualityItem_2(bool vip, const QString& size);//高品
    void    addSongQualityItem_3(bool vip, const QString& size);//超品
    void    addSongQualityItem_4(bool vip, const QString& size);//无损

    void    addVideoQualityItem_1(QVector<QVariant>& videoBody);//视频

signals:
    void    sig_source_song_download(int,QString,QString,QString);//类型（视频or歌曲），下载url,品质,保存路劲
    void    sig_source_video_download(int,QString,QString,QString);//类型（视频or歌曲），下载url,品质,保存路劲
    void    sig_sendToconfig();//设置
};

#endif // DOWNLOADTYPE_H
