#ifndef CUSLINEEDIT_H
#define CUSLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QFocusEvent>

namespace Ui {
class CusLineEdit;
}

class CusLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit CusLineEdit(QWidget *parent = nullptr);
    ~CusLineEdit();
protected:
    void focusInEvent(QFocusEvent *e) override;
    void focusOutEvent(QFocusEvent *e) override;
private:
    Ui::CusLineEdit *ui;

signals:
    void sig_focusInEvent();
    void sig_focusOutEvent();

};

#endif // CUSLINEEDIT_H
