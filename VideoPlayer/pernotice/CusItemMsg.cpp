#include "CusItemMsg.h"
#include "ui_CusItemMsg.h"

//chat list
CusItemMsg::CusItemMsg(const QString &header, const QString &author, const QString &Newcontent, const QString &datatime, const bool read, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CusItemMsg)
{
    ui->setupUi(this);
    setFixedHeight(70);
    setMaximumWidth(400);
    initWorkUI();
    handleSignalsAndSlots();
    setReadStatus(read);
    ui->pushButton_authName->setText(author);
    ui->label_pubTime->setText(datatime);
    ui->pushButton_describle->setText(Newcontent);
    ui->stackedWidget_msgType->setCurrentWidget(ui->page_chat);
}

//reply list
CusItemMsg::CusItemMsg(const QString &header, const QString &author, const QString &newContent, const QString &oldContent, const QString &datatime, QWidget *parent):
    QWidget(parent),
    ui(new Ui::CusItemMsg)
{
    ui->setupUi(this);
    setFixedHeight(70);
    setMaximumWidth(400);
    initWorkUI();
    handleSignalsAndSlots();
    ui->pushButton_author_reply->setText(author);
    ui->pushButton_replyContent->setText(newContent);
    ui->textBrowser_replyContent->setPlainText(oldContent);
    ui->label_time_reply->setText(datatime);
    ui->stackedWidget_msgType->setCurrentWidget(ui->page_reply);
}

//like list
CusItemMsg::CusItemMsg(const QString &header, const QStringList &authors, const QString &oldContent, const QString &datatime, QWidget *parent):
    QWidget(parent),
    ui(new Ui::CusItemMsg)
{
    ui->setupUi(this);
    setFixedHeight(70);
    initWorkUI();
    handleSignalsAndSlots();
    QString string_autor = "";
    foreach (QString var, authors)
    {
        string_autor.append(var);
        string_autor.append("\,");
    }
    ui->pushButton_author_like->setText(string_autor);
    ui->textBrowser_likeContent->setPlainText(oldContent);
    ui->label_time_like->setText(datatime);
    ui->stackedWidget_msgType->setCurrentWidget(ui->page_like);
}

CusItemMsg::~CusItemMsg()
{
    delete ui;
}

void CusItemMsg::initWorkUI()
{
    ui->label_pubTime->setAlignment(Qt::AlignCenter);
    ui->label_readStatus->setAlignment(Qt::AlignCenter);

    ui->label_abooutCtl_reply->setAlignment(Qt::AlignLeft);
    ui->label_abooutCtl_reply->setText(QString(u8"回复了我的评论"));
    ui->label_abooutCtl_about->setAlignment(Qt::AlignLeft);
    ui->label_abooutCtl_about->setText(QString(u8"@了我的评论"));
    ui->label_abooutCtl_like->setAlignment(Qt::AlignLeft);
    ui->label_abooutCtl_like->setText(QString(u8"点赞了我的评论"));

    ui->pushButton_reply->setIcon(QIcon("://images/fileitem/fileitem_reply.png"));
    ui->pushButton_like->setIcon(QIcon("://images/fileitem/fileitem_like.png"));
    ui->pushButton_delete->setIcon(QIcon("://images/fileitem/fileitem_delete.png"));
}

void CusItemMsg::handleSignalsAndSlots()
{
    connect(ui->pushButton_describle,&QPushButton::clicked,[=](){
        setReadStatus(true);
        emit sig_sendClicked();
    });
    connect(ui->pushButton_expand,&QPushButton::clicked,[=](){
        setReadStatus(true);
        emit sig_sendClicked();
    });
}

void CusItemMsg::setReadStatus(bool read)
{
    if(read)
    {
        ui->label_readStatus->setText(QString(u8"[已读]"));
        ui->label_readStatus->setProperty("read",true);
        ui->label_readStatus->style()->polish(ui->label_readStatus);
    }
    else
    {
        ui->label_readStatus->setText(QString(u8"[未读]"));
        ui->label_readStatus->setProperty("read",false);
        ui->label_readStatus->style()->polish(ui->label_readStatus);
    }
}

bool *CusItemMsg::getArroy_ON_Mark()
{
    return array_on;
}

