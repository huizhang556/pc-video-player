/**用户创作中心**/
#ifndef CREATECENTER_H
#define CREATECENTER_H
#define MARWIDTH 2 //窗口边距,进过测试最小需要2px
#define ITEMSIZE QSize(212,170)

#include "creator/CreTitleBar.h"
#include "creator/CusCalendar.h"
#include "creator/FilesItem.h"
#include "creator/UploadWork.h"
#include "creator/CloseButton.h"
#include "creator/AddMediaInfo.h"
#include "customer/BaseWidget.h"
#include "miniplayer/MiniPlayer.h"

#include <QLayout>
#include <QWidget>
#include <QEvent>
#include <QCursor>
#include <QMenu>
#include <QDate>
#include <QList>
#include <QFileInfo>
#include <QThread>
#include <QButtonGroup>
#include <QFileDialog>
#include <QWidgetAction>
#include <QListWidgetItem>
#include <QScrollBar>
#include <QMouseEvent>
#include <QSignalMapper>
#include <QDebug>

namespace Ui {
class CreateCenter;
}

class CreateCenter : public BaseWidget
{
    Q_OBJECT

    explicit CreateCenter(QWidget *parent = nullptr);
public:
    ~CreateCenter();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();
    static CreateCenter* getInstance();

protected:
//    void    mousePressEvent(QMouseEvent *event)override;
    bool    eventFilter(QObject *watched, QEvent *event) override;
//    bool    nativeEvent(const QByteArray& eventType, void* message, long* result) override;

private slots:
    void            addMediaType(const QString& title);
//    void            slot_receiveThreadStarted();
//    void            slot_receiveThreadFinished();
    void            slot_addFileToList();
    void            slot_clearList();

private:
    QList<QUrl>    getOpenFileSystem();
    void           checkListItemsCounts();
    void           addFileItemsToList(const QList<QUrl> urlLists);
    void           file_upload_start(const QUrl media_url,const QUrl pic_url, FilesItem *fileItem);//上传文件到服务器
    void           file_upload_pause();//暂停
    void           file_upload_stop();//移除
    void           file_createItemToAnotherListWgt(const fileBody& body);
    QString        file_getFileSuffix(const QString& suffix);//获取文件类型


private:
    Ui::CreateCenter *ui;
    static  CreateCenter*  m_pInstance;
    MiniPlayer      *m_miniPlayer   =   nullptr;
    CreTitleBar     *m_ctitleBar    =   nullptr;
    CusCalendar     *m_calendar     =   nullptr;
    QMenu           *m_menuDataTime =   nullptr;
    QWidgetAction   *m_wgtAction    =   nullptr;
    QSignalMapper   *m_signalMapper =   nullptr;
    AddMediaInfo   *m_mediaBox      =   nullptr;
    QButtonGroup   *m_buttonGroup1  =   nullptr;
    QButtonGroup   *m_buttonGroup2  =   nullptr;
    QButtonGroup   *m_buttonGroup3  =   nullptr;
    QStringList m_header =
    {
        QString(u8"提取时间"),
        QString(u8"类型"),
        QString(u8"金额(元)"),
        QString(u8"状态"),
        QString(u8"操作")
    };

    QStringList m_producelist =
    {
        QString(u8"电影"),
        QString(u8"网络剧"),
        QString(u8"短视频"),
        QString(u8"中视频"),
        QString(u8"音乐"),
        QString(u8"图片")
    };

//    UploadWork  *upWorker   =   nullptr;
//    QThread     *workThread =   nullptr;

signals:
    void    sig_file_uploadall_start();
    void    sig_file_uploadall_stop();
    void    sig_file_uploadall_clear();
};

#endif // CREATECENTER_H
