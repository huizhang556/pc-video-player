#include "FocusLineEdit.h"

FocusLineEdit::FocusLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    this->installEventFilter(this);
}

FocusLineEdit::~FocusLineEdit()
{

}

void FocusLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    emit sig_focusIn();
}

void FocusLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    emit sig_focusOut();
}

bool FocusLineEdit::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    if(watched == this && event->type() == QEvent::MouseButtonPress && mouseEvent->buttons() & Qt::LeftButton)
    {
        emit sig_mouseButtonPress();
    }
    return  QLineEdit::eventFilter(watched,event);
}
