#include "CusPushButton.h"
#include <QDebug>
CusPushButton::CusPushButton(QWidget *parent) :
    QPushButton(parent)
{
    installEventFilter(this);
}

CusPushButton::CusPushButton(const QString &text, const int id, QWidget *parent):
    QPushButton(parent)
{
    installEventFilter(this);
    this->setText(text);
    this->setButtonId(id);
}

CusPushButton::~CusPushButton()
{

}

void CusPushButton::setButtonId(int id)
{
    m_id = id;
}

int CusPushButton::slot_getButtonId()
{
    return m_id;
}

bool CusPushButton::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
        if(event->type() == QEvent::Enter)
        {
            emit    sig_buttonHover(this->text());
            emit    sig_buttonHover(m_id);
        }
        else if(event->type() == QEvent::Leave)
        {
            emit    sig_buttonHover(this->text());
            emit    sig_buttonHover(m_id);
        }
    return  QWidget::eventFilter(watched,event);
}
