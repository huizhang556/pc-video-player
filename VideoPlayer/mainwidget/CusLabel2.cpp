#include "CusLabel2.h"
#include "ui_CusLabel2.h"

CusLabel2::CusLabel2(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::CusLabel2)
{
    ui->setupUi(this);
    installEventFilter(this);
}

CusLabel2::~CusLabel2()
{
    delete ui;
}

bool CusLabel2::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            emit sig_buttonClicked();
        }
    }
    return QWidget::eventFilter(watched,event);
}
