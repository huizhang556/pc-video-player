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
    explicit WebDownLoadList(QWidget *parent = nullptr);
    ~WebDownLoadList();
    void initWorkUI();
    void chandleSignalsAndSLots();
public slots:
    bool slot_addDownLoadRecordToList(int order);//添加下载记录
    bool slot_setDownLoadStatus();
    bool slot_chandleCancel();
    void slot_searchDownloadHirtory(QString text);
    void slot_setDownloadProgressbar(int value);
protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
private:
    Ui::WebDownLoadList *ui;
    QPoint              m_mvPos;
    bool                m_start;

private slots:
    void on_pushButton_min_clicked();
    void on_pushButton_close_clicked();
    void slot_setStartStatus(QPushButton *button,bool status);
    void slot_openFile(const QString &filepath);
signals:
    void sig_cancel();
    void sig_pause();
    void sig_setConfig();
    void sig_delete();

};

#endif // WEBDOWNLOADLIST_H
