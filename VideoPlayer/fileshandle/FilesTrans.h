#ifndef FILESTRANS_H
#define FILESTRANS_H

#include "fileshandle/MyAllFile.h"
#include "fileshandle/MyLastFile.h"
#include "fileshandle/MyVideosFile.h"
#include "fileshandle/MyMusicsFile.h"
#include "fileshandle/MyPicFile.h"
#include "fileshandle/MyDocFile.h"
#include "fileshandle/DownLoadFile.h"
#include "fileshandle/UploadFile.h"
#include "fileshandle/CompletedFiles.h"
#include "browser/CusWebBrowser.h"

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class FilesTrans;
}

class FilesTrans : public QWidget
{
    Q_OBJECT

public:
    explicit FilesTrans(QWidget *parent = nullptr);
    ~FilesTrans();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setCurrentShowPage(QString page);
    void    setCurrentShowPage(QListWidgetItem *item);

private:
    Ui::FilesTrans *ui;
    MyAllFile           *m_myAllFiles       =   nullptr;
    MyLastFile          *m_myLastFiles      =   nullptr;
    MyVideosFile        *m_myVideoFiles     =   nullptr;
    MyMusicsFile        *m_myMusicFiles     =   nullptr;
    MyPicFile           *m_myPicFiles       =   nullptr;
    MyDocFile           *m_myDocFiles       =   nullptr;
    CompletedFiles      *m_completeFiles    =   nullptr;
    DownLoadFile        *m_downloadFiles    =   nullptr;
    UploadFile          *m_uploadFiles      =   nullptr;
    CusWebBrowser       *m_managerWeb       =   nullptr;
};

#endif // FILESTRANS_H
