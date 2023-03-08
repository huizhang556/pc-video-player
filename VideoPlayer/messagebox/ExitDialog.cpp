#include "ExitDialog.h"
#include "ui_ExitDialog.h"

//构造函数1
ExitDialog::ExitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitDialog)
{
    ui->setupUi(this);
    //去掉边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::Window);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(FIXSIZE);

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0,0);//阴影往边外（下和右）移出的距离
    shadow_effect->setColor(QColor(93, 95, 96));
    shadow_effect->setBlurRadius(8);//设置阴影圆角
    this->setGraphicsEffect(shadow_effect);
    this->setContentsMargins(3,3,3,3);//设置为0时，就看不到边框的阴影

//    QPixmap pixmap(":/images/icon/cursor.png");
//    QSize size(5,5);
//    pixmap.scaled(5,5,Qt::KeepAspectRatio);
//    QCursor *myCursor = new QCursor(pixmap,0,0);    //-1,-1表示热点位于图片中心
//    this->setCursor(*myCursor);
    ui->radioButton_miniSysTron->setChecked(true);
    ui->pushButton_ok->setFocus();//显示选中状态
    ui->pushButton_ok->setDefault(true);//按回车会关闭窗口
    ui->pushButton_ok->setStyleSheet("border:2px solid #9e9e9e; border-radius:5px; background-color:#d44e7d; color: white; font-size:14px;");
    m_iniPath = Global::appDirPath + "/config/config.ini";
    qDebug() << "config file path = " << m_iniPath;
    //此处有bug,只要点击，不管沟上还是没有勾上，都是设置为 1
//    connect(ui->checkBox,&QCheckBox::clicked,[=](){

//            setIni();//状态设置

//    });

    if(readIni() == "1")
    {
        isShow = true;
    }
    else
    {
        isShow = false;
    }

    //确定关闭
    connect(ui->pushButton_ok,&QPushButton::clicked,[=](){
        /*可以做一些类似数据保存的其他操作*/

        emit sig_SendcloseMain();//给主窗口发送关闭窗口信号
        this->close();
    });
    //确定取消
    connect(ui->pushButton_cancel,&QPushButton::clicked,[=](){
        emit sig_SendNotcloseMain();//发送不关闭主窗口信号
        this->close();

    });
    //close
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        emit sig_SendNotcloseMain();
        close();
    });
}

//构造函数2
ExitDialog::ExitDialog(QString title, QString warn, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitDialog)
{
    ui->setupUi(this);
    //去掉边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::Window);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(FIXSIZE);

    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0,0);//阴影往边外（下和右）移出的距离
    shadow_effect->setColor(QColor(93, 95, 96));
    shadow_effect->setBlurRadius(8);//设置阴影圆角
    this->setGraphicsEffect(shadow_effect);
    this->setContentsMargins(3,3,3,3);//设置为0时，就看不到边框的阴影

    ui->radioButton_miniSysTron->setChecked(true);
    ui->pushButton_ok->setFocus();//显示选中状态
    ui->pushButton_ok->setDefault(true);//按回车会关闭窗口
    ui->pushButton_ok->setStyleSheet("border:2px solid #9e9e9e; border-radius:5px; background-color:#d44e7d; color: white; font-size:14px;");
    m_iniPath = Global::appDirPath + "/config/config.ini";
    ui->label->setText(title);
    ui->label_warning->setText(warn);
    //确定关闭
    connect(ui->pushButton_ok,&QPushButton::clicked,[=](){
        /*可以做一些类似数据保存的其他操作*/
        emit sig_SendcloseMain();//给主窗口发送关闭窗口信号
        this->close();
    });
    //确定取消
    connect(ui->pushButton_cancel,&QPushButton::clicked,[=](){
        emit sig_SendNotcloseMain();//发送不关闭主窗口信号
        this->close();

    });
    //close
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        emit sig_SendNotcloseMain();
        this->close();
    });
}


ExitDialog::~ExitDialog()
{
    delete ui;
}

/*读取配置文件值*/
QString ExitDialog::readIni() const
{
//    qDebug() << QString(u8"读取到勾选退出窗口值：")<<Global::readIni_exit();
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
