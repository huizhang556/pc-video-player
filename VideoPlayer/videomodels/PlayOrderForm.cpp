#include "PlayOrderForm.h"
#include "ui_PlayOrderForm.h"

#include <QDebug>

//类外初始化静态变量
PlayOrderForm*    PlayOrderForm::m_pInstance = NULL;

PlayOrderForm::PlayOrderForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayOrderForm)
{
    ui->setupUi(this);
    this->setFixedSize(114,138);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);    //重要
    initWorkUI();
    chandleSignalsAndSlots();
}

PlayOrderForm::~PlayOrderForm()
{
    delete ui;
    //删除创建的单例
    if(m_pInstance != NULL)
        delete m_pInstance;
    m_pInstance = NULL;
}

void PlayOrderForm::initWorkUI()
{
    ui->pushButton_danqu->setFlat(true);
    ui->pushButton_xunhuan->setFlat(true);
    ui->pushButton_suiji->setFlat(true);
    ui->pushButton_shunxu->setFlat(true);

    ui->pushButton_danqu->setCheckable(true);
    ui->pushButton_xunhuan->setCheckable(true);
    ui->pushButton_suiji->setCheckable(true);
    ui->pushButton_shunxu->setCheckable(true);

    ui->pushButton_xunhuan->setChecked(true);//默认选中

    m_btnGroup = new QButtonGroup(this);
    m_btnGroup->addButton(ui->pushButton_danqu,0);
    m_btnGroup->addButton(ui->pushButton_shunxu,1);
    m_btnGroup->addButton(ui->pushButton_xunhuan,2);
    m_btnGroup->addButton(ui->pushButton_suiji,3);
    m_btnGroup->setExclusive(true);
}

void PlayOrderForm::chandleSignalsAndSlots()
{
//    QObject::connect(m_btnGroup,&QButtonGroup::buttonClicked,[=](QAbstractButton *btn)
//    {
//        clearAndSetButtonCheckedStatus(m_btnGroup->id(btn));
//        emit sig_playerOrder(m_btnGroup->id(btn)+1);

//    });
    connect(ui->pushButton_danqu,&QPushButton::clicked,[=](){
//        clearButtonCheckedStatus();
//        setButtonChedkedStatus(1);
        clearAndSetButtonCheckedStatus(1);
//        emit sig_playerOrder(1);
        qDebug() << "emit sig_playerOrder(1);";
    });//单曲
    connect(ui->pushButton_xunhuan,&QPushButton::clicked,[=](){
//        clearButtonCheckedStatus();
//        setButtonChedkedStatus(3);
        clearAndSetButtonCheckedStatus(3);
//        emit sig_playerOrder(3);
        qDebug() << "emit sig_playerOrder(3);";
    });//循环
    connect(ui->pushButton_shunxu,&QPushButton::clicked,[=](){
//        clearButtonCheckedStatus();
//        setButtonChedkedStatus(2);
        clearAndSetButtonCheckedStatus(2);
//        emit sig_playerOrder(2);
        qDebug() << "emit sig_playerOrder(2);";
    });//顺序
    connect(ui->pushButton_suiji,&QPushButton::clicked,[=](){
//        clearButtonCheckedStatus();
//        setButtonChedkedStatus(4);
        clearAndSetButtonCheckedStatus(4);
//        emit sig_playerOrder(4);
        qDebug() << "emit sig_playerOrder(4);";
    });//随机
}

PlayOrderForm *PlayOrderForm::getInstance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new PlayOrderForm();
    }
    return m_pInstance;
}

bool PlayOrderForm::clearAndSetButtonCheckedStatus(int index)
{
    clearButtonCheckedStatus();
    setButtonChedkedStatus(index);
    emit sig_playerOrder(index);
    return 0;
}

void PlayOrderForm::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->hide();
}


bool PlayOrderForm::clearButtonCheckedStatus()
{
    ui->pushButton_danqu->setChecked(false);
    ui->pushButton_xunhuan->setChecked(false);
    ui->pushButton_suiji->setChecked(false);
    ui->pushButton_shunxu->setChecked(false);
    return true;
}

/*设置选中状态*/
bool PlayOrderForm::setButtonChedkedStatus(int index)
{
//    if(index == 1)
//    {
//        ui->pushButton_danqu->setChecked(true);
//    }
//    else if(index == 2)
//    {
//        ui->pushButton_shunxu->setChecked(true);
//    }
//    else if(index == 3)
//    {
//        ui->pushButton_xunhuan->setChecked(true);
//    }
//    else if(index == 4)
//    {
//        ui->pushButton_suiji->setChecked(true);
//    }
    m_btnGroup->button(index-1)->setChecked(true);
    return true;
}




