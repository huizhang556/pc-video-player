#include "ExitDialog.h"
#include "ui_ExitDialog.h"

//构造函数1
ExitDialog::ExitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitDialog)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

//构造函数2
ExitDialog::ExitDialog(QString title, QString warn, QWidget *parent):
    QDialog(parent),
    ui(new Ui::ExitDialog)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    ui->label->setText(title);
    ui->label_warning->setText(warn);
}


ExitDialog::~ExitDialog()
{
    delete ui;
}

void ExitDialog::initWorkUI()
{
    //去掉边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(FIXSIZE);
    this->setAttribute(Qt::WA_Hover);//必须要有这句，否则按钮选中无效

    //设置边框阴影，影响部分功能（按钮选中就无效）
//    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
//    shadow_effect->setOffset(0,0);//阴影往边外（下和右）移出的距离
//    shadow_effect->setColor(QColor(93, 95, 96));
//    shadow_effect->setBlurRadius(8);//设置阴影圆角
//    this->setGraphicsEffect(shadow_effect);
//    this->setContentsMargins(3,3,3,3);//设置为0时，就看不到边框的阴影

    ui->pushButton_cancel->setCheckable(true);
    ui->pushButton_ok->setCheckable(true);

    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(ui->pushButton_cancel,0);
    m_buttonGroup->addButton(ui->pushButton_ok,1);
    m_buttonGroup->setExclusive(true);
    ui->pushButton_ok->setChecked(true);

    if(Global::readCloseAction())//真的关闭
    {
        ui->radioButton_exitApp->setChecked(true);
        ui->radioButton_miniSysTron->setChecked(false);
        qDebug() <<QString(u8"读取配置文件结果：直接退出");
    }
    else
    {
        ui->radioButton_exitApp->setChecked(false);
        ui->radioButton_miniSysTron->setChecked(true);
        qDebug() <<QString(u8"读取配置文件结果：最小化托盘");
    }

    m_iniPath = Global::appDirPath + "/config/config.ini";

    if(readIni() == "1")
        isShow = true;
    else
        isShow = false;
}

void ExitDialog::handleSignalsAndSlots()
{
    //确定关闭
    connect(ui->pushButton_ok,&QPushButton::clicked,[=](){
        /*可以做一些类似数据保存的其他操作*/
        setIni();
        setCloseType();//设置 m_closeType 值
        emit sig_SendcloseMain(m_closeType);//给主窗口发送关闭窗口信号
        this->accept();
    });
    //确定取消
    connect(ui->pushButton_cancel,&QPushButton::clicked,[=](){
        emit sig_SendNotcloseMain();//发送不关闭主窗口信号
        ui->pushButton_ok->setChecked(true);//将选中行为设为“确定”按钮
        this->reject();

    });
    //close
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        emit sig_SendNotcloseMain();
        this->close();
    });
}

/*读取配置文件值*/
QString ExitDialog::readIni() const
{
   return Global::readIni_exit();
}

/*设置配置文件值*/
void ExitDialog::setIni()
{
    //只有被沟上，才将配置文件设为1
    if(ui->checkBox->isChecked())
    {
       Global::setIni_exit(false);
    }
}

void ExitDialog::setCloseType()
{
    if(ui->radioButton_miniSysTron->isChecked())
    {
        m_closeType = false;
        Global::setCloseAction(false);//隐藏
    }
    else if(ui->radioButton_exitApp->isChecked())
    {
        m_closeType = true;
        Global::setCloseAction(true);//真关闭
    }
}

bool ExitDialog::getCloseType()
{
    if(ui->radioButton_miniSysTron->isChecked())
    {
        return false;
    }
    else if(ui->radioButton_exitApp->isChecked())
    {
        return true;
    }
}

void ExitDialog::setCloseText(QString waring)
{
    ui->label_warning->setText(waring);
}

/*按下事件*/
void ExitDialog::mousePressEvent(QMouseEvent *event)
{
    m_mvPoint = event->globalPos() - this->pos();
}
/*移动事件*/
void ExitDialog::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - m_mvPoint);
}
