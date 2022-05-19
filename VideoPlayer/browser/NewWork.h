#ifndef NEWWORK_H
#define NEWWORK_H
#include "global/Global.h"
#include <QDialog>
#include <QAction>
#include <QBoxLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QListWidget>
#include <QWebEngineDownloadItem>

namespace Ui {
class NewWork;
}

class NewWork : public QDialog
{
    Q_OBJECT

public:
    ~NewWork();
    void initWorkUI();
    void chandleSignalsAndSlots();
    static NewWork* getInstance();
public slots:
    QString openLocalFileSystem();
    void slot_receivedNewWorkInfo(const QString &adress, const QString &filename);
    void slot_receiveDownloadRequested(QWebEngineDownloadItem* item);
//    void slot_downLoad_progress(qint64 bytesReceived, qint64 bytesTotal);
//    void slot_downLoad_finished();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
private slots:
    void slot_addPathToList(const QString &path);
    void slot_setLineEditText(QLineEdit *edit, const QString &text);
    bool slot_judgePathExist(const QString &path);
    void slot_updateShowListPathWidget();

private:
    explicit NewWork(QWidget *parent = nullptr);
    Ui::NewWork *ui;
    QPoint                  m_mvPos;
    QAction                 *m_spaceSize            =   nullptr;
    QAction                 *m_fileSize             =   nullptr;
    QListWidget             *m_listWdgt_path        =   nullptr;
    QPushButton             *m_clearBtn             =   nullptr;
    QWidget                 *m_hisWdgt              =   nullptr;
    static  NewWork         *m_pInstance;
signals:
    void        sig_download(const QString& filename, const QString& savepath);
    void        sig_downloadOpen();
    void        sig_cancel();
};

#endif // NEWWORK_H
