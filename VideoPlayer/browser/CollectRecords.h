#ifndef COLLECTRECORDS_H
#define COLLECTRECORDS_H

#include "database/dataBase.h"
#include "browser/RecordItem.h"
#include "browser/MiniRecordItem.h"

#include <QWidget>
#include <QUrl>
#include <QListWidget>
#include <QPushButton>
#include <QListWidgetItem>

namespace Ui {
class CollectRecords;
}

class CollectRecords : public QWidget
{
    Q_OBJECT

public:   
    ~CollectRecords();
    explicit CollectRecords(QWidget *parent = nullptr);
    bool                judgeCollectRecordsUrlExist(const QString &url);//判断当前的网址是否已经在收藏栏
    void                initWorkUI();
    void                chandleSignalsAndSlots();
    QString             getCurrentRecordItemButtonText(QListWidgetItem* item);//传入QListWidgetItem，返回按钮文本
    QPushButton*        getCurrentRecordItemButton(QListWidgetItem* item);//传入QListWidgetItem，返回按钮
    QString             getCurrentRecordItemText(QListWidget *listWidget, QString &text);//传入按钮文本，返回QListWidgetItem文本
    QListWidgetItem*    getCurrentRecordParentItem(QListWidget *listWidget, QString &text);//传入按钮文本，返回QListWidgetItem
    void                slot_initToRecordsListWidget(const QString &url, QIcon icon,const QString &title, const QString & createtime);//初始化历史记录

public slots:
    void                slot_clearUserRecords();//用户退出清除历史记录
    void                slot_addToRecordsListWidget(QUrl url);
    void                slot_showWebMessageWindow(QString url, QString name);
    void                slot_updateCurrentRecord_recordItem(QListWidgetItem* item,const QString &url, const QString& rename);
    void                slot_updateCurrentRecord_miniRecordItem(QListWidgetItem* item,const QString &url, const QString& rename);
    void                slot_addToRecordsListWidget(const QString &url, QIcon icon,const QString &title);
    QString             slot_getCurrentRecordItemText(const QString &text);//传入按钮文本，返回QListWidgetItem文本，供收藏栏调用

protected:
//    void                mousePressEvent(QMouseEvent *event) override;

private:
    Ui::CollectRecords *ui;
    int                 m_count;
    static  int         m_singleCount;
    QListWidget*        m_currentListWidget     =   nullptr;
    bool                m_isFirst;

private:
    void                findSearchCollectRecords(QString name);
    QListWidget*        getCurrentListWidget();
    int                 getCurrentRecordsCounts();

signals:
    void                sig_returnPage();
    void                sig_changeRecord();
    void                sig_sendItemText(QString text);
    void                sig_sendDeleteItemUrl(QString text);

};

#endif // COLLECTRECORDS_H
