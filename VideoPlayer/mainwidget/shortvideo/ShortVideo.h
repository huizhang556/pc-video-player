#ifndef SHORTVIDEO_H
#define SHORTVIDEO_H

#include "global/Global.h"
#include "fileshandle/DownloadType.h"
#include "videomodels/RecVideoItem.h"
#include "videomodels/RecomVideoTab.h" //引入结构体
#include <QListWidgetItem>
#include <QScrollBar>
#include <QWidget>
#include <QTimer>
#include <QMovie>
#include <QVariant>
#include <QUrlQuery>
#include <QDebug>


namespace Ui {
class ShortVideo;
}

class ShortVideo : public QWidget
{
    Q_OBJECT

public:
    explicit ShortVideo(QWidget *parent = nullptr);
    ~ShortVideo();
    void            initWorkUI();
    void            handleSignalsAndSLots();

public  slots:
    void    slot_addSelectTypeToList(const QStringList& typelist);
    bool    slot_addShortVideoItem(QVariant& musicVariant);//通过结构体传递信息
    bool    slot_addShortVideoItem(QString url, QString path, QString time, QString info, QString count);//添加item
    void    slot_setCurThemeCounts(int num);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    QPushButton*    getListWidgetItemButton(QListWidgetItem* item, QString objname);//在item中查找指定按钮
    void            setContentTips(const QString& tips);

private slots:


private:
    Ui::ShortVideo *ui;
    QStringList typelist =
    {
        QString(u8"科技"),
        QString(u8"体育"),
        QString(u8"军事"),
        QString(u8"艺术"),
        QString(u8"搞笑"),
        QString(u8"恐怖"),
        QString(u8"古装"),
        QString(u8"脱口秀")
    };

    QString     m_curMediaName;
    QString     m_curMediaUrl;


signals:
    void    sig_sendToMainPlayer(int,const QStringList&,const QUrlQuery&);
    void    sig_sendTheme(const QString&);

};

#endif // SHORTVIDEO_H
