#include "WebMessageBox.h"
#include "ui_WebMessageBox.h"

WebMessageBox* WebMessageBox::m_pInstance = nullptr;

WebMessageBox::WebMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WebMessageBox)
{
    ui->setupUi(this);
    this->setFixedSize(520,465);
    setWindowFlags(Qt::FramelessWindowHint);
    initWorkUI();
    chandleSignalsAndSLots();
}

WebMessageBox::~WebMessageBox()
{
    delete ui;
    //删除单例
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void WebMessageBox::initWorkUI()
{
    ui->checkBox_addCollect->setText(QString::fromLocal8Bit("将本条收藏固定到快捷收藏栏"));
    ui->lineEdit_address->setReadOnly(true);
}

void WebMessageBox::chandleSignalsAndSLots()
{
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){this->hide();});
    //确定
    connect(ui->pushButton_sure,&QPushButton::clicked,[=](){
        emit sig_sendTitleChanged(ui->lineEdit_address->text().trimmed(),ui->lineEdit_nickName->text().trimmed());
        this->close();
    });
    //取消
    connect(ui->pushButton_cancel,&QPushButton::clicked,[=](){this->close();});
}

WebMessageBox *WebMessageBox::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new WebMessageBox();
    }
    return m_pInstance;
}

void WebMessageBox::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    ui->lineEdit_nickName->setFocus();
}

void WebMessageBox::setWebMessageInforation(QString address, QString name)
{
    ui->lineEdit_address->setText(address);
    ui->lineEdit_nickName->setText(name);
}
