#include "MessageItem.h"
#include "ui_MessageItem.h"
#include <QFontMetrics>

MessageItem::MessageItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageItem)
{
    ui->setupUi(this);
    setFixedSize(290,60);
    setInstallEventFilter();
}

MessageItem::MessageItem(const QString &pic, const QString &nickname, const QString &datatime, const QString &message, QWidget *parent):
    QWidget(parent),
    m_picPath(pic),
    m_nickName(nickname),
    m_dataTime(datatime),
    m_message(message),
    ui(new Ui::MessageItem)
{
    ui->setupUi(this);
    setFixedSize(286,60);
    setInstallEventFilter();
    setItemPicture();
    setItemNickName();
    setItemTime();
    setItemMessage();
}

MessageItem::~MessageItem()
{
    delete ui;
}

void MessageItem::setInstallEventFilter()
{
    ui->labInform->installEventFilter(this);
}

void MessageItem::setItemPicture()
{
//    ui->label_header->setPixmap(QPixmap(m_picPath));
//    ui->label_header->setScaledContents(true);
    ui->label_header->setHeaderPicture(m_picPath);
    ui->label_header->setHeaderBGColor(QColor(41,41,41));
    ui->label_header->setHeaderRadius(23);
}

void MessageItem::setItemNickName()
{
    ui->labNameMess->setText(m_nickName);
}

void MessageItem::setItemTime()
{
    ui->labTimer->setText(m_dataTime);
}

void MessageItem::setItemMessage()
{
    QFontMetrics fontMetric(ui->labInform->font());
    QString text = fontMetric.elidedText(m_message,Qt::ElideRight,13*15);
    ui->labInform->setText(text);
}

bool MessageItem::eventFilter(QObject *watched, QEvent *event)
{
   if(watched == ui->labInform && event->type() == QEvent::MouseButtonPress)
   {
        ui->label_header->setStatusButtonStatus(true);
   }
    return QWidget::eventFilter(watched,event);
}
