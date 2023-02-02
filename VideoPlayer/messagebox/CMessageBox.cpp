#include "CMessageBox.h"
#include "ui_CMessageBox.h"

CMessageBox::CMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMessageBox)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setFixedSize(270,125);
    initWorkUI();
    handleSignalsAndSlots();
//     this->exec();
}

CMessageBox::CMessageBox(MessageType mtype, const QString &title, const QString &query, const QString &button1Text, const QString &button2Text, QWidget *parent):
    QDialog(parent),
    m_type(mtype),
    m_titleText(title),
    m_checkQuery(query),
    m_btn1Text(button1Text),
    m_btn2Text(button2Text),
    ui(new Ui::CMessageBox)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setFixedSize(270,125);
    initWorkUI();
    handleSignalsAndSlots();
    setMessageType(m_type);
    setTitleText(m_titleText);
    setCheckQuery(m_checkQuery);
    setButton1Text(m_btn1Text);
    setButton2Text(m_btn2Text);
//    this->exec();
}

CMessageBox::~CMessageBox()
{
    delete ui;
}

void CMessageBox::initWorkUI()
{
    ui->label_checkText->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
}

void CMessageBox::handleSignalsAndSlots()
{
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        close();
    });
    connect(ui->pushButton_ok,&QPushButton::clicked,[=](){
        this->accept();
        close();
    });

    connect(ui->pushButton_cancel,&QPushButton::clicked,[=](){
        this->reject();
        close();
    });
}

void CMessageBox::setMessageType(MessageType mtype)
{
    QString iconpPath = "";
    switch (mtype)
    {
    case MessageType::CNoIcon:
    {
        iconpPath = "";
        ui->label_icon->hide();
    }
        break;
    case MessageType::CError:
    {
        iconpPath = ":/images/icon/message_error.png";
    }
        break;
    case MessageType::CWarning:
    {
        iconpPath = ":/images/icon/message_warning.png";
    }
        break;
    case MessageType::CQuestion:
    {
        iconpPath = ":/images/icon/message_question.png";
    }
        break;
    default:
    {
        iconpPath = "";
        ui->label_icon->hide();
    }
        break;
    }
    ui->label_icon->setPixmap(QPixmap(iconpPath));
    ui->label_icon->setScaledContents(true);
}

void CMessageBox::setTitleText(const QString &title)
{
    ui->pushButton_warning->setText(title);
}

void CMessageBox::setCheckQuery(const QString &query)
{
    ui->label_checkText->setText(query);
}

void CMessageBox::setButton1Text(const QString &btn1text)
{
    if(btn1text.isEmpty())
        ui->pushButton_ok->hide();
    ui->pushButton_ok->setText(btn1text);
}

void CMessageBox::setButton2Text(const QString &btn2text)
{
    if(btn2text.isEmpty())
        ui->pushButton_cancel->hide();
    ui->pushButton_cancel->setText(btn2text);
}
