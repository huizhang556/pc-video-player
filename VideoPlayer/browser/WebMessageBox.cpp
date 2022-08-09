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
}

WebMessageBox *WebMessageBox::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new WebMessageBox();
    }
    return m_pInstance;
}
