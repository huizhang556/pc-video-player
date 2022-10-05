#include "CusListItem.h"
#include "ui_CusListItem.h"

CusListItem::CusListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CusListItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusListItem::CusListItem(const QString &icon, const QString &content, QWidget *parent):
    QWidget(parent),
    ui(new Ui::CusListItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    ui->pushButton_icon->setIcon(QIcon(icon));
    ui->pushButton_text->setText(content);
}

CusListItem::~CusListItem()
{
    delete ui;
}

void CusListItem::initWorkUI()
{
//    ui->pushButton_close->hide();
}

void CusListItem::handleSignalsAndSlots()
{
    connect(ui->pushButton_icon,&QPushButton::clicked,[=](){
        emit sig_sendItemText(ui->pushButton_text->text());
    });

    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        emit sig_sendItemClose();
    });

    connect(ui->pushButton_text,&QPushButton::clicked,[=](){
        emit sig_sendItemText(ui->pushButton_text->text());
    });
}

void CusListItem::setInstallEventFilter()
{
    this->installEventFilter(this);

}

bool CusListItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            qDebug() << QString(u8"进入item");
            ui->pushButton_close->setStyleSheet("#pushButton_close{"
                                                "border:none;"
                                                "border-image: url(:/images/icon/closehover.png);"
                                                "background-color: transparent;"
                                                "}");
        }
        else if(event->type() == QEvent::Leave)
        {
            qDebug() << QString(u8"离开item");
             ui->pushButton_close->setStyleSheet("#pushButton_close{"
                                                 "border:none;"
                                                 "background-color: transparent;"
                                                 "}");
        }
    }
    return QWidget::eventFilter(watched,event);
}
