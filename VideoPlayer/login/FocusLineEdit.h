#ifndef FOCUSLINEEDIT_H
#define FOCUSLINEEDIT_H

#include <QLineEdit>
#include <QFocusEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>

class FocusLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    explicit FocusLineEdit(QWidget *parent = nullptr);
    ~FocusLineEdit();

protected:
    void    focusInEvent(QFocusEvent* event)override;
    void    focusOutEvent(QFocusEvent* event)override;
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:


signals:
    void    sig_focusIn();
    void    sig_focusOut();
    void    sig_mouseButtonPress();

};

#endif // FOCUSLINEEDIT_H
