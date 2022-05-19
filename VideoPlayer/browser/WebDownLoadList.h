#ifndef WEBDOWNLOADLIST_H
#define WEBDOWNLOADLIST_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QProgressBar>
#include <QPushButton>
#include <QListWidgetItem>

namespace Ui {
class WebDownLoadList;
}

class WebDownLoadList : public QWidget
{
    Q_OBJECT

public:    
    ~WebDownLoadList();
    void initWorkUI();
    void chandleSignalsAndSLots();
    static  WebDownLoadList* getInstance();
public slots:
    bool slot_addDownLoadRecordToList();//添加下载记录
    bool slot_setDownLoadStatus();
    bool slot_chandleCancel();
    void slot_searchDownloadHirtory(QString text);
    void slot_setDownloadProgressbar(qint64 bytesReceived, qint64 bytesTotal);
    void slot_receivedNewWorkFinished();
protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
private:
    explicit WebDownLoadList(QWidget *parent = nullptr);
    Ui::WebDownLoadList *ui;
    QPoint              m_mvPos;
    bool                m_start;
    static  WebDownLoadList* m_pInstance;

private slots:
    void on_pushButton_min_clicked();
    void on_pushButton_close_clicked();
    void slot_setStartStatus(QPushButton *button,bool status);
    void slot_openFile(const QString &filepath);
signals:
    void        sig_cancel();
    void        sig_pause();
    void        sig_setConfig();
    void        sig_delete();
    void        sig_receiveProgressbar(int value);
};

#endif // WEBDOWNLOADLIST_H
