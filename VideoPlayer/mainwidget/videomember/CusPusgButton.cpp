#include "CusPusgButton.h"
#include <QDebug>
CusPusgButton::CusPusgButton(QWidget *parent) :
    QPushButton(parent)
{
    installEventFilter(this);
}

CusPusgButton::~CusPusgButton()
{

}

void CusPusgButton::setButtonId(int id)
{
    m_id = id;
}

int CusPusgButton::slot_getButtonId()
{
    return m_id;
}

bool CusPusgButton::eventFilter(QObject *watched, QEvent *event)
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
