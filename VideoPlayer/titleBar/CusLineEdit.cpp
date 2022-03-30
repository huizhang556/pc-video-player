#include "CusLineEdit.h"
#include "ui_CusLineEdit.h"
#include <QDebug>

CusLineEdit::CusLineEdit(QWidget *parent) :
    QLineEdit(parent),
    ui(new Ui::CusLineEdit)
{
    ui->setupUi(this);
    this->setFocus();
}

CusLineEdit::~CusLineEdit()
{
    delete ui;
}

/*聚焦事件*/
void CusLineEdit::focusInEvent(QFocusEvent *e)
{
        emit sig_focusInEvent();
        qDebug() << "emit sig_focusInEvent();";
}

/*去焦事件*/
void CusLineEdit::focusOutEvent(QFocusEvent *e)
{
        emit sig_focusOutEvent();
    qDebug() << "emit sig_focusOutEvent();";
}


