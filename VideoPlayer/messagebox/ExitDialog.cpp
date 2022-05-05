#include "ExitDialog.h"
#include "ui_ExitDialog.h"
#include <QDir>
#include <QDebug>
#include <QPixmap>
#include <QCursor>
#include <QSettings>
#include <QMouseEvent>

ExitDialog::ExitDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExitDialog)
{
    ui->setupUi(this);
    //去掉边框
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setFixedSize(404,152);

//    QPixmap pixmap(":/images/icon/cursor.png");
//    QSize size(5,5);
//    pixmap.scaled(5,5,Qt::KeepAspectRatio);
//    QCursor *myCursor = new QCursor(pixmap,0,0);    //-1,-1表示热点位于图片中心
//    this->setCursor(*myCursor);

    ui->pushButton_ok->setFocus();//显示选中状态
    ui->pushButton_ok->setDefault(1);//按回车会关闭窗口
    ui->pushButton_ok->setStyleSheet("border:2px solid #9e9e9e;background-color:rgb(101,210,105);font-size:14px;");
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

ExitDialog::~ExitDialog()
{
    delete ui;
}

/*读取配置文件值*/
QString ExitDialog::readIni() const
{
    QSettings *pSet = new QSettings(m_iniPath,QSettings::IniFormat);
    QString statusValue = pSet->value("/check_status/status").toString();
    delete pSet;
    return statusValue;
}

/*设置配置文件值*/
void ExitDialog::setIni()
{
    //只有被沟上，才将配置文件设为1
    if(ui->checkBox->isChecked())
    {
        QSettings *pSet = new QSettings(m_iniPath,QSettings::IniFormat);
        pSet->setValue("/check_status/status","0");
        delete pSet;
        pSet = NULL;
    }

}

/*按下事件*/
void ExitDialog::mousePressEvent(QMouseEvent *event)
{
    winPos = this->pos();//界面位置
    nowPos = event->globalPos();//鼠标位置
    m_mvPoint = nowPos - winPos;
}
/*移动事件*/
void ExitDialog::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - m_mvPoint);
}
