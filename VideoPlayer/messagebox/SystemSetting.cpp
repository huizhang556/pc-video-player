#include "SystemSetting.h"
#include "ui_SystemSetting.h"
#include <QButtonGroup>
#include <QMouseEvent>
#include <QStringList>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

SystemSetting::SystemSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SystemSetting)
{
    ui->setupUi(this);
    this->setFixedSize(700,520);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Tool);
    loadDefaultConfig();
    initWorkUI();
    chandleSignalAndSlot();//处理信号与槽函数
}

SystemSetting::~SystemSetting()
{
    delete ui;
}

void SystemSetting::initWorkUI()
{
    ui->stackedWidget->setCurrentIndex(0);//显示第一项
    ui->tabWidget->setCurrentIndex(0);//显示第一项
    //有些按钮需要设置互斥选择，有些事共同不需要互斥
    //    QButtonGroup *btnGroup1 = new QButtonGroup;
    //    btnGroup1->addButton(ui->radioButton_exit,0);
    //    btnGroup1->addButton(ui->radioButton_tray,1);

//    ui->label_warning->setAlignment(Qt::AlignCenter);//无用，不添加布局，需要设置padding
}

void SystemSetting::chandleSignalAndSlot()
{
    //选项变化
    connect(ui->listWidget,&QListWidget::currentRowChanged,ui->stackedWidget,&QStackedWidget::setCurrentIndex);
    //close
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
//    setTitleWarningText(QString::fromLocal8Bit("您当前的配置有改动，请选择保存或取消再退出！"),7000);
//        if(true)
//        {
//            //退出 0  取消 1
//            int code = QMessageBox::warning(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("您确定要退出吗？"),QString::fromLocal8Bit("退出"), QString::fromLocal8Bit("取消"));
//            //            qDebug() << code;
//            if(code == 0)
//            {
//                //保存文件设置
//                savesSettingConfigFile();
//                //退出设置界面
//                this->close();
//            }
//        }
        savesSettingConfigFile();
        this->close();
    });

    //画面设置 -- 柔和
    connect(ui->pushButton_rouhe,&QPushButton::clicked,[=](){

        qDebug() <<"rouhe";
    });
    //画面设置 -- 明亮
    connect(ui->pushButton_mingliang,&QPushButton::clicked,[=](){

        qDebug() <<"minliang";
    });
    //画面设置 -- 恢复默认
    connect(ui->pushButton_recover,&QPushButton::clicked,[=](){

        qDebug() <<"huifumoren";
    });

    //视频管理 -- 下载目录
    connect(ui->pushButton_v_down_open,&QPushButton::clicked,[=](){
        QString fpath = openLocalFileSystem();
        if(!fpath.isEmpty())
        {
            ui->lineEdit_savevideopath->setText(fpath);
            ui->lineEdit_savevideopath->setToolTip(fpath);
            qDebug() <<fpath;
        }
    });
    //视频管理 -- 缓存目录
    connect(ui->pushButton_v_his_open,&QPushButton::clicked,[=](){
        QString fpath = openLocalFileSystem();
        if(!fpath.isEmpty())
        {
            ui->lineEdit_watchedsavepath->setText(fpath);
            ui->lineEdit_watchedsavepath->setToolTip(fpath);
            qDebug() <<fpath;
        }
    });
    //游戏管理 -- 下载目录
    connect(ui->pushButton_gdown_open,&QPushButton::clicked,[=](){
        QString fpath = openLocalFileSystem();
        if(!fpath.isEmpty())
        {
            ui->lineEdit_savegamepath->setText(fpath);
            ui->lineEdit_savegamepath->setToolTip(fpath);
            qDebug() <<fpath;
        }
    });

    //取消设置
    connect(ui->pushButton_cancelset,&QPushButton::clicked,[=](){
        this->close();
    });

    //应用设置
    connect(ui->pushButton_apply,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"应用设置");
    });

    //恢复设置
    connect(ui->pushButton_recover,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"恢复设置");
    });
}

/*打开本地文件系统*/
QString SystemSetting::openLocalFileSystem()
{
    QString fpath = QFileDialog::getExistingDirectory(this,
                                                QString::fromLocal8Bit("选择路径"),
                                                QString::fromLocal8Bit("C:\\Users\\24939\\Desktop"));
    if(!fpath.isEmpty())//不为空
    {
        fpath = fpath + QString(tr("/"));
        return fpath;
    }
}

void SystemSetting::setTitleWarningText(QString text, int msec)
{
    ui->label_warning->setText(text);
    QTimer *m_timer = new QTimer(this);
    m_timer->start(msec);//持续5秒,按毫秒算
    connect(m_timer,&QTimer::timeout,[=](){ ui->label_warning->clear(); });
}


//保存设置
void SystemSetting::savesSettingConfigFile()
{
    qDebug() << "the file Settings are saved!";
}

//加载配置
void SystemSetting::loadDefaultConfig()
{
    //基本设置
    //最小化后任务栏显示
    ui->radioButton_showinrwl->setChecked(true);
    //点击关闭按钮后退出
    ui->radioButton_exit->setChecked(true);

    //播放设置
    QStringList strStep;
    strStep << "10" << "20" << "30";
    ui->comboBox_step->addItems(strStep);

    //画面设置
    //亮度
    ui->horizontalSlider_liangdu->setValue(25);
    //饱和度
    ui->horizontalSlider_baohedu->setValue(30);
    //对比度
    ui->horizontalSlider_duibidu->setValue(20);
    //色相
    ui->horizontalSlider_sexaing->setValue(20);

    //音频设置
    QStringList strAudio;
    strAudio << QString::fromLocal8Bit("主声音驱动")
             << QString::fromLocal8Bit("扬声器")
             << QString::fromLocal8Bit("输出到默认设备");
    ui->comboBox_shucushebei->addItems(strAudio);

    //网络设置
    ui->radioButton_fulldown->setChecked(true);
    QStringList maxdown;
    maxdown << "1024" << "2048" << "4096";
    ui->comboBox_max_down_speed->addItems(maxdown);
    ui->comboBox_max_up_speed->addItems(maxdown);

    //下载设置
    //下载视频保存路径
    ui->lineEdit_savevideopath->setText("E:\\QLDownload\\");
    //最大同时下载数量
    QStringList maxvdowncounts;
    maxvdowncounts << "3" << "5" << "7";
    ui->comboBox_startcommon->addItems(maxvdowncounts);
    //下载完成后提示
    ui->checkBox_downloadedprompt->setChecked(true);
    //缓存路径
    ui->lineEdit_watchedsavepath->setText("E:\\QLDownload\\");
    //缓存空间
    ui->lineEdit_cachespace->setText("4096");

    //游戏设置
    //游戏存储路径
    ui->lineEdit_savegamepath->setText("E:\\QLDownloadGame\\");
    //游戏最大同时下载数量
    ui->comboBox_gamestartcounts->addItems(maxvdowncounts);
    //游戏下载完成后自动提示
    ui->checkBox_diownloadedprompt->setChecked(true);

    //热键设置
    //播放暂停
    ui->lineEdit_pauseplayer->setText("Alt + P");
    //全屏
    ui->lineEdit_fullgreen->setText("Alt + F");
    //快退
    ui->lineEdit_fastreverse->setText("Ctrl +Left");
    //快进
    ui->lineEdit_fastforward->setText("Ctrl + Right");
    //下一个
    ui->lineEdit_next->setText("Alt + PD");
    //增加音量
    ui->lineEdit_volumeup->setText("Alt + Up");
    //减少音量
    ui->lineEdit_volumedown->setText("Alt + Down");
    //老板键
    ui->lineEdit_oldkey->setText("Alt + O");

    //高级设置
    ui->checkBox_localvideodefault->setChecked(true);
    ui->checkBox_tuisong->setChecked(true);

    //自动关机
    //下载完影片自动关机
    ui->radioButton_offinedownclose->setChecked(false);
    //定时关机
    ui->radioButton_timeclose->setChecked(true);
    //定时关机 -- 设置小时
    QStringList strHour;
    strHour << "00" ;
    ui->comboBox_hour->addItems(strHour);
    //定时关机 -- 设置分钟
    QStringList strMinite;
    strMinite << "00" ;
    ui->comboBox_minite->addItems(strMinite);
    //取消自动关机
    ui->radioButton_cancelautoclose->setChecked(true);
    //所有设置完毕
    //左侧设置列表
    QStringList strList;
    strList<<QString::fromLocal8Bit("基本设置")<<QString::fromLocal8Bit("播放设置")
           <<QString::fromLocal8Bit("画面设置")<<QString::fromLocal8Bit("音频设置")
           <<QString::fromLocal8Bit("网络设置")<<QString::fromLocal8Bit("下载设置")
           <<QString::fromLocal8Bit("热键设置")<<QString::fromLocal8Bit("高级设置")
           <<QString::fromLocal8Bit("自动关机");
    for(auto const item:strList)
    {
        QListWidgetItem *pitem = new QListWidgetItem(item);
        pitem->setTextAlignment(Qt::AlignCenter);//文字水平和垂直方向都居中
        ui->listWidget->addItem(pitem);
    }
    ui->listWidget->setCurrentRow(0);//内容填充完设置才生效
    qDebug() << "the file config are loaded!";
}

void SystemSetting::setObjectShowTip(QObject *obj, QString &text)
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit *>(obj);
    lineEdit->setText(text);
}
