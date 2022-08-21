#ifndef FILESTRANS_H
#define FILESTRANS_H

#include "fileshandle/CompletedFiles.h"
#include "fileshandle/DownLoadFile.h"
#include "fileshandle/UploadFile.h"

#include <QWidget>

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

private:
    Ui::FilesTrans *ui;
    CompletedFiles      *m_completeFiles    =   nullptr;
    DownLoadFile        *m_downloadFiles    =   nullptr;
    UploadFile          *m_uploadFiles      =   nullptr;
};

#endif // FILESTRANS_H
