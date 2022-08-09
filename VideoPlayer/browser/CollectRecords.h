#ifndef COLLECTRECORDS_H
#define COLLECTRECORDS_H

#include <QWidget>
#include <QUrl>
#include <QListWidget>

namespace Ui {
class CollectRecords;
}

class CollectRecords : public QWidget
{
    Q_OBJECT

public:   
    ~CollectRecords();
    explicit CollectRecords(QWidget *parent = nullptr);
    bool    judgeCollectRecordsUrlExist(const QString &url);//判断当前的网址是否已经在收藏栏
    void    initWorkUI();
    void    chandleSignalsAndSlots();

public slots:
    void    slot_addToRecordsListWidget(QUrl url);

    void    slot_addToRecordsListWidget(const QString &text, QIcon icon);

private:
    Ui::CollectRecords *ui;
    int             m_count;
    static  int     m_singleCount;
    QListWidget*    m_currentListWidget     =   nullptr;

private:
    void        findSearchCollectRecords(QString name);
    QListWidget* getCurrentListWidget();
    int         getCurrentRecordsCounts();

signals:
    void    sig_returnPage();
    void    sig_changeRecord();
    void    sig_sendItemText(QString text);
};

#endif // COLLECTRECORDS_H
