#include "Installer.h"
#include "ui_Installer.h"
#include "global/Global.h"

//#ifdef Q_OS_WIN
//#include <qt_windows.h>
//#pragma comment (lib,"user32.lib")
//#endif

Installer* Installer::m_pInstance = nullptr;

Installer::Installer(QWidget *parent) :
    BaseDialog(parent),
    m_curPageIndex(0),
    ui(new Ui::Installer)
{
    ui->setupUi(this);
    setFixedSize(620,360);
    setWindowTitle(QString(u8"安装器"));
    this->setAttribute(Qt::WA_Hover);
//    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setTitleBarMoveArea(ui->frame_title,0);
    initWorkUI();
    handleSignalsAndSlots();
}

Installer::~Installer()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

Installer *Installer::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new Installer();
    }
    return m_pInstance;
}

void Installer::initWorkUI()
{
    ui->stackedWidget_page->setCurrentIndex(0);
    ui->pushButton_back->setCheckable(true);//上一步
    ui->pushButton_forward->setCheckable(true);//下一步
    ui->pushButton_forward->setChecked(true);//默认选中
    ui->pushButton_cancel->setCheckable(true);
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->setExclusive(true);
    m_buttonGroup->addButton(ui->pushButton_back,0);
    m_buttonGroup->addButton(ui->pushButton_forward,1);
    m_buttonGroup->addButton(ui->pushButton_cancel,2);
    ui->pushButton_install->hide();
    ui->lineEdit_installpath->setText(QString(u8"C:/Program Files (x86)/VideoPlayer"));
    ui->stackedWidget_customset->setCurrentIndex(0);

    for(int i = 0; i < 4; i++)
    {
        QTreeWidgetItem *item1 = new QTreeWidgetItem();
        item1->setText(0,QString(u8"安装的插件---%1").arg(i+1));
        item1->setTextAlignment(0,Qt::AlignLeft);
        item1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        item1->setCheckState(0,Qt::Checked);
        ui->treeWidget_plugin->addTopLevelItem(item1);
    }
}

void Installer::handleSignalsAndSlots()
{
    connect(ui->stackedWidget_page,&QStackedWidget::currentChanged,[=](int index){
        if(index == 3)
        {
            ui->pushButton_back->hide();
            ui->pushButton_forward->hide();
            ui->pushButton_cancel->setText(QString(u8"完成"));
        }
    });

    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        this->close();
    });

    connect(ui->pushButton_min,&QPushButton::clicked,[=](){
        this->hide();
    });

    //完成1
    connect(ui->pushButton_cancel,&QPushButton::clicked,[=](){
        if(ui->pushButton_cancel->text() == QString(u8"取消"))
        {
            this->close();
        }
        else if(ui->pushButton_cancel->text() == QString(u8"完成"))
        {
            emit sig_sendFinished();
            this->accept();
        }
    });

    //完成2(立即体验)
    connect(ui->pushButton_experiance,&QPushButton::clicked,[=](){
            ui->pushButton_cancel->click();
    });

    //下一步
    connect(ui->pushButton_forward,&QPushButton::clicked,[=](){
        m_curPageIndex++;
        ui->stackedWidget_page->setCurrentIndex(m_curPageIndex);
        ui->pushButton_forward->setChecked(true);
        if(m_curPageIndex == ui->stackedWidget_page->count()-2)//到倒数第2页，到倒数第1页，卸载界面
        {
            ui->pushButton_forward->setEnabled(false);
        }
        if(!ui->pushButton_back->isEnabled())
            ui->pushButton_back->setEnabled(true);
    });

    //上一步
    connect(ui->pushButton_back,&QPushButton::clicked,[=](){
        m_curPageIndex--;
        ui->stackedWidget_page->setCurrentIndex(m_curPageIndex);
        ui->pushButton_forward->setChecked(true);
        if(m_curPageIndex == 0)//最后一页
            ui->pushButton_back->setEnabled(false);
        if(!ui->pushButton_forward->isEnabled())
            ui->pushButton_forward->setEnabled(true);
    });

    //自定义安装
    connect(ui->pushButton_custom,&QPushButton::clicked,[=](){
        ui->stackedWidget_customset->setCurrentIndex(1);
    });

    //自定义安装--返回
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){
        ui->stackedWidget_customset->setCurrentIndex(0);
    });

    //自定义安装--立即安装
    connect(ui->pushButton_install,&QPushButton::clicked,[=](){
    qDebug() <<QString(u8"自定义安装--立即安装");
    });

    //浏览安装目录
    connect(ui->pushButton_browserpath,&QPushButton::clicked,[=](){
        QString fpath = QFileDialog::getExistingDirectory(this,
                                                        QString::fromLocal8Bit("选择路径"),
                                                        QApplication::applicationDirPath());//默认打开程序所在路径
            if(!fpath.isEmpty())//不为空
            {
                ui->lineEdit_installpath->setText(fpath);
            }
    });

}

//void Installer::mousePressEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event)
//    m_mvPos = event->globalPos() - this->pos();
//}

//void Installer::mouseMoveEvent(QMouseEvent *event)
//{
//    Q_UNUSED(event)
//    this->move(event->globalPos() - m_mvPos);
//}
