#ifndef SHORTVIDEO_H
#define SHORTVIDEO_H

#include "global/Global.h"
#include "fileshandle/DownloadType.h"
#include "videomodels/RecVideoItem.h"
#include "videomodels/RecomVideoTab.h" //引入结构体
#include <QListWidgetItem>
#include <QScrollBar>
#include <QWidget>
#include <QVariant>
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
    bool    slot_addRecVideoItem(QVariant   musicVariant);//通过结构体传递信息
    bool    slot_addRecVideoItem(QString url, QString path,QString time,QString info,QString count);//添加item

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    QPushButton*    getListWidgetItemButton(QListWidgetItem* item, QString objname);//在item中查找指定按钮

private:
    Ui::ShortVideo *ui;
    QStringList typelist =
    {
        QString(u8"为你推荐"),
        QString(u8"热点"),
        QString(u8"军事"),
        QString(u8"人文"),
        QString(u8"财经"),
        QString(u8"社会"),
        QString(u8"历史"),
        QString(u8"奇闻异事")
    };

    QString     m_curMediaName;
    QString     m_curMediaUrl;

signals:
    void    sig_sendToMainPlayer(int,const QStringList&,const QString&);

};

#endif // SHORTVIDEO_H
