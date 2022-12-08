#ifndef CUSCALENDAR_H
#define CUSCALENDAR_H

#include <QDialog>
#include <QDate>
#include <QEvent>

namespace Ui {
class CusCalendar;
}

class CusCalendar : public QDialog
{
    Q_OBJECT

public:
    explicit CusCalendar(QWidget *parent = nullptr);
    ~CusCalendar();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::CusCalendar *ui;

signals:
    void    sig_calendar1(QDate);
    void    sig_calendar2(QDate);
};

#endif // CUSCALENDAR_H
