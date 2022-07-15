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
private:
    Ui::WebHistory *ui;

signals:
    void    sig_returnPage();
};

#endif // WEBHISTORY_H
