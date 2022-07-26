#ifndef WEBHISTORY_H
#define WEBHISTORY_H

#include <QWidget>

namespace Ui {
class WebHistory;
}

class WebHistory : public QWidget
{
    Q_OBJECT

public:
    explicit WebHistory(QWidget *parent = nullptr);
    ~WebHistory();

    void    chandleSignalsAndSLots();

public slots:
    void    slot_addToListHistoryWidget(const QString &text);

private:
    Ui::WebHistory *ui;
    bool    judgeHistoryUrlExist(const QString &url);//判断当前的网址是否已经在收藏栏


signals:
    void    sig_returnPage();
    void    sig_sendItemText(QString text);
};

#endif // WEBHISTORY_H
