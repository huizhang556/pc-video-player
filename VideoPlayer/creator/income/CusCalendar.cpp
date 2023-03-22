#include "CusCalendar.h"
#include "ui_CusCalendar.h"

CusCalendar::CusCalendar(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CusCalendar)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(500,230);
//    setAttribute(Qt::WA_StyledBackground);
    ui->calendarWidget1->installEventFilter(this);
    ui->calendarWidget2->installEventFilter(this);
    connect(ui->calendarWidget1,&QCalendarWidget::clicked,[=](const QDate &data){
        emit sig_calendar1(data);
    });

    connect(ui->calendarWidget2,&QCalendarWidget::clicked,[=](const QDate &data){
        emit sig_calendar2(data);
    });
}

CusCalendar::~CusCalendar()
{
    delete ui;
}

bool CusCalendar::eventFilter(QObject *watched, QEvent *event)
{
//    if(watched == this)
//    {
//        if(event->type() == QEvent::Leave)
//        {
//            this->hide();
//        }

//    }
    return QWidget::eventFilter(watched,event);
}
