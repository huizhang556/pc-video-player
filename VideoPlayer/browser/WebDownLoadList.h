#ifndef WEBDOWNLOADLIST_H
#define WEBDOWNLOADLIST_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QListWidgetItem>

namespace Ui {
class WebDownLoadList;
}

class WebDownLoadList : public QWidget
{
    Q_OBJECT

public:
    explicit WebDownLoadList(QWidget *parent = nullptr);
    ~WebDownLoadList();
    void initWorkUI();
    void chandleSignalsAndSLots();
public slots:
    bool slot_addDownLoadRecordToList();//添加下载记录
    bool slot_setDownLoadStatus();
    bool slot_chandleCancel();
    bool slot_clearHistoryList();
    bool slot_setDownLoadConfig();
    void slot_searchDownloadHirtory(QString text);
private:
    Ui::WebDownLoadList *ui;
signals:
    void sig_cancel();
    void sig_pause();
    void sig_setConfig();
    void sig_delete();
private slots:
    void on_pushButton_min_clicked();
    void on_pushButton_close_clicked();
};

#endif // WEBDOWNLOADLIST_H
