#include "SubModules.h"
#include "ui_SubModules.h"

SubModules::SubModules(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubModules)
{
    ui->setupUi(this);
    installEventFilter(this);
    setMinimumSize(130,100);
}

SubModules::SubModules(const QString &picpath, const QString &info1, const QString &info2, QWidget *parent):
    QWidget(parent),
    m_header(picpath),
    m_info1(info1),
    m_info2(info2),
    ui(new Ui::SubModules)
{
     ui->setupUi(this);
     installEventFilter(this);
     setMinimumSize(130,100);
     setPicture();
     setInfo1();
     setInfo2();
}

SubModules::~SubModules()
{
    delete ui;
}

bool SubModules::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched,event);
}

void SubModules::setPicture()
{
//    ui->label_header->setPixmap(QPixmap(m_header));
//    ui->label_header->setScaledContents(true);
    ui->label_header->setItemPicture(m_header);
}

void SubModules::setInfo1()
{
    ui->pushButton_info1->setText(m_info1);
}

void SubModules::setInfo2()
{
    ui->pushButton_info2->setText(m_info2);
}
