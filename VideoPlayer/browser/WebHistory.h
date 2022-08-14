#ifndef WEBHISTORY_H
#define WEBHISTORY_H

#include <QWidget>
#include <QUrl>
#include <QLabel>
#include <QLayout>
#include <QPushButton>

namespace Ui {
class WebHistory;
}

class WebHistory : public QWidget
{
    Q_OBJECT

public:
    explicit WebHistory(QWidget *parent = nullptr);
    ~WebHistory();
    void    initWorkUI();
    void    chandleSignalsAndSLots();

public slots:
    void    slot_addToListHistoryWidget(QUrl url);
    void    slot_initHistoryRecordListWgt(const QString &text);//初始化
    void    slot_addToListHistoryWidget(const QString &text);


private slots:
    void        slot_clearMarks();//清除痕迹

private:
    Ui::WebHistory *ui;
    void        findSearchRecordsHittories(QString name);
    bool        judgeHistoryUrlExist(const QString &url);//判断当前的网址是否已经在收藏栏


signals:
    void    sig_returnPage();
    void    sig_sendItemText(QString text);

};

#endif // WEBHISTORY_H
