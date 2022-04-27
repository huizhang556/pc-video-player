#include "StackItem.h"
#include "ui_StackItem.h"

StackItem::StackItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackItem)
{
    ui->setupUi(this);
    this->setFixedSize(300,26);
    ui->pushButton_name->installEventFilter(this);
    ui->pushButton_intro->installEventFilter(this);
//    ui->pushButton_name->setAttribute(Qt::WA_TransparentForMouseEvents,true);
//    ui->pushButton_intro->setAttribute(Qt::WA_TransparentForMouseEvents,true);
}

StackItem::~StackItem()
{
    delete ui;
}

void StackItem::setlistBtn_NameText(QString text)
{
    ui->pushButton_name->setText(text);
}

void StackItem::setlistBtn_IntroText(QString text)
{
    ui->pushButton_intro->setText(text);
}

void StackItem::setlistBtn_NameIcon(QString path)
{
    ui->pushButton_name->setIcon(QIcon(path));
    ui->pushButton_name->setIconSize(QSize(18,18));
}

bool StackItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->pushButton_name)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->pushButton_name->setStyleSheet("QPushButton{"
                                               "background-color:transparent;"
                                               "padding-left:5px;"
                                               "font-size:16px;"
                                               "text-align:left;"
                                               "color:#ff0000;"
                                               "}");
            ui->pushButton_intro->setStyleSheet("QPushButton{"
                                                "background-color:transparent;"
                                               "color:#ff0000;"
                                                "text-align:left;"
                                                "font-size:13px;"
                                               "}");
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->pushButton_name->setStyleSheet("QPushButton{"
                                               "background-color:transparent;"
                                               "padding-left:5px;"
                                               "text-align:left;"
                                               "font-size:15px;"
                                               "color:#9b9ca0;"
                                               "}");
            ui->pushButton_intro->setStyleSheet("QPushButton{"
                                               "background-color:transparent;"
                                                "text-align:left;"
                                                "font-size:13px;"
                                                "color:transparent;"
                                               "}");
        }
    }
    else if(watched == ui->pushButton_intro)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->pushButton_name->setStyleSheet("QPushButton{"
                                               "background-color:transparent;"
                                               "padding-left:5px;"
                                               "font-size:16px;"
                                               "text-align:left;"
                                               "color:#ff0000;"
                                               "}");
            ui->pushButton_intro->setStyleSheet("QPushButton{"
                                                "background-color:transparent;"
                                               "color:#ff0000;"
                                                "text-align:left;"
                                                "font-size:13px;"
                                               "}");
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->pushButton_name->setStyleSheet("QPushButton{"
                                               "background-color:transparent;"
                                               "padding-left:5px;"
                                               "text-align:left;"
                                               "font-size:15px;"
                                               "color:#9b9ca0;"
                                               "}");
            ui->pushButton_intro->setStyleSheet("QPushButton{"
                                               "background-color:transparent;"
                                                "text-align:left;"
                                                "font-size:13px;"
                                                "color:transparent;"
                                               "}");
        }
    }
    return QWidget::eventFilter(watched,event);
}
