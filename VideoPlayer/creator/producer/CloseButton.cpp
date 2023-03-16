#include "CloseButton.h"

CloseButton::CloseButton(QWidget *parent) :
    QPushButton(parent)
{
   initWorkUI();
   handleSignalsAndSLots();
}

CloseButton::~CloseButton()
{

}

void CloseButton::initWorkUI()
{
    this->installEventFilter(this);
    m_remButton = new QPushButton("X",this);
    m_remButton->setObjectName(QString::fromUtf8("m_remButton"));
    m_remButton->setFixedSize(6,6);
    m_remButton->hide();
    m_remButton->setStyleSheet("#m_remButton{"
                               "border: none;"
                               "color: black;"
                               "}"
                               "#m_remButton:hover{"
                               "border: none;"
                               "color: red;"
                               "}");
}

void CloseButton::handleSignalsAndSLots()
{

}

bool CloseButton::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {

        if(event->type() == QEvent::Resize)
        {
            resizeRemoveButtonGeometry();
            qDebug() << QString(u8"resize");
        }
        else if(event->type() == QEvent::Enter)
        {
            m_remButton->show();
            qDebug() << QString(u8"Enter");
        }
        else if(event->type() == QEvent::Leave)
        {
            m_remButton->hide();
            qDebug() << QString(u8"Leave");
        }
    }
    return QWidget::eventFilter(watched,event);
}

void CloseButton::resizeRemoveButtonGeometry()
{
    m_remButton->move(this->x()-m_remButton->width(),this->y() - m_remButton->height());//指定父亲的情况下
//    m_remButton->setGeometry(this->mapToGlobal(this->pos()).x(),
//                             this->mapToGlobal(this->pos()).y()- m_remButton->height(),
//                             m_remButton->width(),
//                             m_remButton->height()
//                             );
}
