#ifndef DONEWORKS_H
#define DONEWORKS_H

//不要定义同名的宏
#define DITEMSIZE QSize(212,170)

#include "database/dataBase.h"
#include "creator/producer/FilesItem.h"
#include "videomodels/MultipPlayer.h"

#include <QSize>
#include <QWidget>
#include <QVariant>
#include <QScrollBar>
#include <QListWidgetItem>

namespace Ui {
class DoneWorks;
}

class DoneWorks : public QWidget
{
    Q_OBJECT

public:
    explicit DoneWorks(QWidget *parent = nullptr);
    ~DoneWorks();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();

public slots:
    void    slot_receivedData_findTypeResult(QVariant media);

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::DoneWorks *ui;

    QStringList m_producelist =
    {
        QString(u8"电影"),
        QString(u8"网络剧"),
        QString(u8"短视频"),
        QString(u8"中视频"),
        QString(u8"音乐"),
        QString(u8"图片")
    };

    QStringList m_datalist =
    {
        QString(u8"movies"),
        QString(u8"netdrama"),
        QString(u8"shortvideos"),
        QString(u8"midvideos"),
        QString(u8"musics"),
        QString(u8"pictures")
    };

    QStringList mediaList = {};
};

#endif // DONEWORKS_H
