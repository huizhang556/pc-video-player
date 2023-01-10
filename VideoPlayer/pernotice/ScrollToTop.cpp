#include "ScrollToTop.h"
#include "ui_ScrollToTop.h"

ScrollToTop* ScrollToTop::m_pInstance = nullptr;

ScrollToTop::ScrollToTop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScrollToTop)
{
    ui->setupUi(this);
    setFixedSize(55,110);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground,true);//透明
    initWorkUI();
    handleSignalsAndSlots();
}

ScrollToTop::~ScrollToTop()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void ScrollToTop::initWorkUI()
{
    ui->pushButton_totop->hide();//默认先隐藏起来
}

void ScrollToTop::handleSignalsAndSlots()
{
    connect(ui->pushButton_flush,&QPushButton::clicked,[=](){
        emit sig_sendToFlush();
    });

    connect(ui->pushButton_totop,&QPushButton::clicked,[=](){
        emit sig_sendToTop();
    });
}

ScrollToTop *ScrollToTop::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new ScrollToTop();
    }
    return m_pInstance;
}

void ScrollToTop::scrollToTopShow()
{
    this->setFixedHeight(110);
    ui->pushButton_totop->show();
    this->show();
}

void ScrollToTop::scrollToTopHide()
{
    ui->pushButton_totop->hide();
    this->setFixedHeight(55);
    this->show();
}
