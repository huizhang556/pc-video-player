#include "MainNotice.h"
#include "ui_MainNotice.h"

MainNotice* MainNotice::m_pInstance = nullptr;

MainNotice::MainNotice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainNotice)
{
    ui->setupUi(this);
    setMinimumSize(0,0);
    setAttribute(Qt::WA_NoMouseReplay);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool |Qt::WindowStaysOnTopHint | Qt::Popup);
    initWorkUI();
    handleSignalsAndSlots();
}

MainNotice::~MainNotice()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void MainNotice::initWorkUI()
{
    m_buttonGroup1 = new QButtonGroup(this);
    m_buttonGroup1->setExclusive(true);
    ui->pushButton_chat->setCheckable(true);
    ui->pushButton_chat->setChecked(true);
    ui->pushButton_reply->setCheckable(true);
    ui->pushButton_focus->setCheckable(true);
    ui->pushButton_like->setCheckable(true);
    m_buttonGroup1->addButton(ui->pushButton_chat,0);
    m_buttonGroup1->addButton(ui->pushButton_reply,1);
    m_buttonGroup1->addButton(ui->pushButton_focus,2);
    m_buttonGroup1->addButton(ui->pushButton_like,3);
    ui->stackedWidget_title->setCurrentWidget(ui->stackapge_main);
    ui->stackedWidget_notice->setCurrentWidget(ui->stackedWidget_noticePage1);
}

void MainNotice::handleSignalsAndSlots()
{
    connect(m_buttonGroup1,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        qDebug() << button->text()<<button->objectName();
        button->setChecked(true);
        switchStackPageof_notice(button);
    });
}

MainNotice *MainNotice::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new MainNotice();
    }
    return m_pInstance;
}

void MainNotice::switchStackPageof_notice(QAbstractButton *button)
{
    if(!button->text().isEmpty())
    {
        if(button->objectName() == QString(u8"pushButton_chat"))
        {
            ui->stackedWidget_notice->setCurrentWidget(ui->stackedWidget_noticePage1);
        }
        else if(button->objectName() == QString(u8"pushButton_reply"))
        {
            ui->stackedWidget_notice->setCurrentWidget(ui->stackedWidget_noticePage2);
        }
        else if(button->objectName() == QString(u8"pushButton_focus"))
        {
            ui->stackedWidget_notice->setCurrentWidget(ui->stackedWidget_noticePage3);
        }
        else if(button->objectName() == QString(u8"pushButton_like"))
        {
            ui->stackedWidget_notice->setCurrentWidget(ui->stackedWidget_noticePage4);
        }
    }
}
