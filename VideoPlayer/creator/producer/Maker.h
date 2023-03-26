#ifndef MAKER_H
#define MAKER_H

//不要定义同名的宏
#define ITEMSIZE QSize(212,170)

#include <QWidget>
#include <QMenu>
#include <QThread>
#include <QPushButton>
#include <QSignalMapper>
#include <QButtonGroup>
#include <QScrollBar>
#include <QListWidget>
#include <QFileDialog>
#include <QDebug>

#include "creator/producer/FilesItem.h"
#include "creator/producer/UploadWork.h"
#include "creator/producer/CloseButton.h"
#include "creator/producer/AddMediaInfo.h"

namespace Ui {
class Maker;
}

class Maker : public QWidget
{
    Q_OBJECT

public:
    explicit Maker(QWidget *parent = nullptr);
    ~Maker();
    void            initWorkUI();
    void            handleSignalsAndSlots();
    void            setInstallEventer();

private slots:
    void            addMediaType(const QString& title);
    void            slot_addFileToList();
    void            slot_clearList();

private:
private:
    void            file_upload_pause();//暂停
    void            file_upload_stop();//移除
    void            file_upload_start(const QUrlQuery media_url, const QByteArray &pic_url, FilesItem *fileItem);//上传文件到服务器
    QList<QUrl>     getOpenFileSystem();
    void            checkListItemsCounts();
    void            file_createItemToAnotherListWgt(const fileBody& body);
    void            addFileItemsToList(const QList<QUrl> urlLists);
    void            addFileItemsToList(QUrl& fileUrl);
    QString         file_getFileSuffix(const QString& suffix);//获取文件类型
    QPushButton*    getCurrentItemButton(QListWidgetItem* item, const QString& objname);

private:
    Ui::Maker *ui;
    QSignalMapper   *m_signalMapper =   nullptr;
    AddMediaInfo    *m_mediaBox      =   nullptr;
    QButtonGroup    *m_buttonGroup1  =   nullptr;
    QButtonGroup    *m_buttonGroup2  =   nullptr;
    QButtonGroup    *m_buttonGroup3  =   nullptr;

signals:
    void    sig_file_uploadall_clear();
    void    sig_file_uploadall_start();
    void    sig_file_uploadall_stop();
};

#endif // MAKER_H
