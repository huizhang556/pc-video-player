#include "MySkin.h"
#include "ui_MySkin.h"

MySkin::MySkin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MySkin)
{
    ui->setupUi(this);
    installEventFilter(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

MySkin::~MySkin()
{
    delete ui;
}

bool MySkin::eventFilter(QObject *watch, QEvent *event)
{
    if(event->type() == QEvent::Leave)
    {
        this->hide();
    }

    return QDialog::eventFilter(watch,event);
}
