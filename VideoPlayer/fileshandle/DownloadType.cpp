#include "DownloadType.h"
#include "ui_DownloadType.h"
#include "global/Global.h"

#ifdef Q_OS_WIN
#include <qt_windows.h>
#pragma comment (lib,"user32.lib")
#endif

DownloadType* DownloadType::m_pInstance = nullptr;

DownloadType::DownloadType(QWidget *parent) :
    QDialog(parent),
    m_userRow(0),
    m_userType(1),
    m_sourceVip(0),
    m_sourceType(0),
    ui(new Ui::DownloadType)
{
    ui->setupUi(this);
    qRegisterMetaType<QVector<QVariant>>("QVector<QVariant>");
    qRegisterMetaType<QVariant>("QVariant");
    this->setFixedSize(650,460);
    this->setAttribute(Qt::WA_Hover);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    initWorkUI();
    handleSignalsAndSlots();
}

DownloadType::~DownloadType()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void DownloadType::initWorkUI()
{
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(ui->pushButton_ok,0);
    m_buttonGroup->addButton(ui->pushButton_cancel,1);
    m_buttonGroup->setExclusive(true);

    ui->comboBox_savePath->setView(new QListView());//保证样式生效
    ui->comboBox_savePath->addItem(Global::appDirPath + "/download");
    m_curOpenPath = ui->comboBox_savePath->currentText();
    ui->lineEdit_downloadUrl->setText("https://82.156.175.81/study/index.html");
    ui->pushButton_ok->setCheckable(true);
    ui->pushButton_cancel->setCheckable(true);
    ui->pushButton_ok->installEventFilter(this);
    ui->pushButton_cancel->installEventFilter(this);
    ui->pushButton_ok->setChecked(true);
    ui->lineEdit_downloadUrl->setReadOnly(true);
    ui->lineEdit_downloadUrl->setContextMenuPolicy(Qt::NoContextMenu);

    ui->tableWidget_source->setLineWidth(0);
    ui->tableWidget_source->setGridStyle(Qt::NoPen);//网线类型
    ui->tableWidget_source->setRowCount(6);
    ui->tableWidget_source->setColumnCount(5);
    ui->tableWidget_source->horizontalHeader()->hide();
    ui->tableWidget_source->verticalHeader()->hide();
    ui->tableWidget_source->setSelectionBehavior(QAbstractItemView::SelectRows);//点击表头选中规则
    ui->tableWidget_source->setSelectionMode(QAbstractItemView::NoSelection);//鼠标左键扩选规则
    ui->tableWidget_source->setEditTriggers(QAbstractItemView::NoEditTriggers);//表格不可编辑

    ui->tableWidget_source->setColumnWidth(0,80);
    ui->tableWidget_source->setColumnWidth(1,12);
    ui->tableWidget_source->setColumnWidth(2,100);
    ui->tableWidget_source->setColumnWidth(3,40);
    ui->tableWidget_source->setColumnWidth(4,120);

    ui->tableWidget_source->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tableWidget_source->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    ui->tableWidget_source->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->tableWidget_source->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    ui->tableWidget_source->horizontalHeader()->setSectionResizeMode(4,QHeaderView::ResizeToContents);

    addSongQualityItem_1(true,QString(u8"25.5MB/无损"));
    addSongQualityItem_2(false,QString(u8"8.43MB/320K"));
    addSongQualityItem_3(true,QString(u8"3.37MB/128K"));
    addSongQualityItem_4(true,QString(u8"2.91MB"));
    //第4行空一行
    VideoBody clarity1;
    clarity1.videoText = QString(u8"标清(480P)");
    clarity1.videoVip = false;
    clarity1.videoSize = QString(u8"70M/MP4");
    QVariant varClarity1;
    varClarity1.setValue(clarity1);

    VideoBody clarity2;
    clarity2.videoText = QString(u8"高清(540P)");
    clarity2.videoVip = true;
    clarity2.videoSize = QString(u8"80M/MP4");
    QVariant varClarity2;
    varClarity2.setValue(clarity2);

    VideoBody clarity3;
    clarity3.videoText = QString(u8"超清(720P)");
    clarity3.videoVip = true;
    clarity3.videoSize = QString(u8"90M/MP4");
    QVariant varClarity3;
    varClarity3.setValue(clarity3);

    VideoBody clarity4;
    clarity4.videoText = QString(u8"蓝光(1080P)");
    clarity4.videoVip = true;
    clarity4.videoSize = QString(u8"96M/MP4");
    QVariant varClarity4;
    varClarity4.setValue(clarity4);

    m_videoVector.append(varClarity1);
    m_videoVector.append(varClarity2);
    m_videoVector.append(varClarity3);
    m_videoVector.append(varClarity4);

    addVideoQualityItem_1(m_videoVector);
    ui->tableWidget_source->setCellWidget(0,0,new QLabel(u8"歌曲资源："));


    //默认选中下载资源类型
    QRadioButton *defRadioBtn =  qobject_cast<QRadioButton*>(ui->tableWidget_source->cellWidget(0,1));
    defRadioBtn->setChecked(true);
}

void DownloadType::handleSignalsAndSlots()
{
    //关闭
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        this->close();
    });

    // 确定下载
    connect(ui->pushButton_ok,&QPushButton::clicked,[=](){
        if(m_sourceVip)//vip资源
        {
            ui->label_tips->setText(QString(u8"该资源为付费资源，请先开通会员！"));
            QTimer::singleShot(1500,0,[=](){
                ui->label_tips->clear();
            });
            return;
        }
        m_sourceUrl = ui->lineEdit_downloadUrl->text().trimmed();
        emit sig_source_song_download(m_sourceType,m_sourceUrl,m_quality,m_curOpenPath);
        emit sig_source_video_download(m_sourceType,m_sourceUrl,m_quality,m_curOpenPath);
        qDebug() << QString(u8"要下载的资源选择的信息：类型：%1，路径：%2，质量：%3，会员类型：%4").arg(m_sourceType).arg(m_sourceUrl).arg(m_quality).arg(m_sourceVip);
        this->accept();
        this->close();
    });

    // 取消下载
    connect(ui->pushButton_cancel,&QPushButton::clicked,[=](){
        ui->pushButton_ok->setChecked(true);
        this->reject();
        this->close();
    });

    //copy下载路径
    connect(ui->pushButton_copyUrl,&QPushButton::clicked,[=](){
        ui->label_tips->setText(QString(u8"该资源链接已复制！"));
        QTimer::singleShot(1500,0,[=](){
            ui->label_tips->clear();
        });
    });

    //选择路径
    connect(ui->pushButton_openPath,&QPushButton::clicked,[=](){
        QString path = openLocalFileSystem();
        qDebug() <<QString(u8"返回路径：") << path;
        if(path.isEmpty()) return;
        ui->comboBox_savePath->setCurrentText(path);
        if(!judgePathExist(path))
        {
            ui->comboBox_savePath->insertItem(ui->comboBox_savePath->count(),path);
        }
            ui->comboBox_savePath->setCurrentText(path);
            m_curOpenPath = path;
    });

    //更多设置
    connect(ui->pushButton_moreSet,&QPushButton::clicked,[=](){
        emit sig_sendToconfig();
    });
}

void DownloadType::showDownloadForm(int type, const QString &name)
{
    if(type == 0)//歌曲
    {
        QRadioButton *defRadioBtn =  qobject_cast<QRadioButton*>(ui->tableWidget_source->cellWidget(0,1));
        defRadioBtn->setChecked(true);
    }
    else if(type == 1)//视频
    {
        QRadioButton *defRadioBtn =  qobject_cast<QRadioButton*>(ui->tableWidget_source->cellWidget(5,1));
        defRadioBtn->setChecked(true);
    }
    else//其他
    {
        QRadioButton *defRadioBtn =  qobject_cast<QRadioButton*>(ui->tableWidget_source->cellWidget(0,1));
        defRadioBtn->setChecked(true);
    }
    ui->pushButton_songName->setText(name);
    this->show();
}

bool DownloadType::judgePathExist(const QString &path)
{
    for(int i = 0; i < ui->comboBox_savePath->count(); i++)
    {
        if(path == ui->comboBox_savePath->itemText(i))
            return true;//存在
    }
    return false;//不存在
}

//流畅
void DownloadType::addSongQualityItem_1(bool vip, const QString& size)
{
    m_radioBtn1   = new QRadioButton(ui->tableWidget_source);
    ui->tableWidget_source->setCellWidget(m_userRow,1, m_radioBtn1);
    ui->tableWidget_source->setCellWidget(m_userRow,2,new QPushButton(u8"流畅音质"));
    if(vip)
    {
        ui->tableWidget_source->setCellWidget(m_userRow,3,new QPushButton(QIcon("://images/home/file_music_vip.png"),""));
    }
    else
    {
        ui->tableWidget_source->setCellWidget(m_userRow,3,new QPushButton(QIcon("://images/home/file_music_free.png"),""));
    }

    ui->tableWidget_source->setCellWidget(m_userRow,4,new QPushButton(size));
    m_userRow++;
    connect(m_radioBtn1,&QRadioButton::clicked,[=](bool checked){
        if(checked)
        {
            m_sourceType = 0;
            m_sourceVip = vip;
            m_quality = QString(u8"流畅");
        }
    });
}

//高品
void DownloadType::addSongQualityItem_2(bool vip, const QString& size)
{
    m_radioBtn2   = new QRadioButton(ui->tableWidget_source);
    ui->tableWidget_source->setCellWidget(m_userRow,1, m_radioBtn2);
    ui->tableWidget_source->setCellWidget(m_userRow,2,new QPushButton(u8"高品音质"));
    if(vip)
    {
        ui->tableWidget_source->setCellWidget(m_userRow,3,new QPushButton(QIcon("://images/home/file_music_vip.png"),""));
    }
    else
    {
        ui->tableWidget_source->setCellWidget(m_userRow,3,new QPushButton(QIcon("://images/home/file_music_free.png"),""));
    }
    ui->tableWidget_source->setCellWidget(m_userRow,4,new QPushButton(size));
    m_userRow++;
    connect(m_radioBtn2,&QRadioButton::clicked,[=](bool checked){
        if(checked)
        {
            m_sourceType = 0;
            m_sourceVip = vip;
            m_quality = QString(u8"高品");
        }
    });
}

//超品
void DownloadType::addSongQualityItem_3(bool vip, const QString& size)
{
    m_radioBtn3   = new QRadioButton(ui->tableWidget_source);
    ui->tableWidget_source->setCellWidget(m_userRow,1, m_radioBtn3);
    ui->tableWidget_source->setCellWidget(m_userRow,2,new QPushButton(u8"超品音质"));
    if(vip)
    {
        ui->tableWidget_source->setCellWidget(m_userRow,3,new QPushButton(QIcon("://images/home/file_music_vip.png"),""));
    }
    else
    {
        ui->tableWidget_source->setCellWidget(m_userRow,3,new QPushButton(QIcon("://images/home/file_music_free.png"),""));
    }
    ui->tableWidget_source->setCellWidget(m_userRow,4,new QPushButton(size));
    m_userRow++;
    connect(m_radioBtn3,&QRadioButton::clicked,[=](bool checked){
        if(checked)
        {
            m_sourceType = 0;
            m_sourceVip = vip;
            m_quality = QString(u8"超品");
        }
    });
}

//无损
void DownloadType::addSongQualityItem_4(bool vip, const QString &size)
{
    m_radioBtn4   = new QRadioButton(ui->tableWidget_source);
    ui->tableWidget_source->setCellWidget(m_userRow,1, m_radioBtn4);
    ui->tableWidget_source->setCellWidget(m_userRow,2,new QPushButton(u8"无损音质"));
    if(vip)
    {
        ui->tableWidget_source->setCellWidget(m_userRow,3,new QPushButton(QIcon("://images/home/file_music_vip.png"),""));
    }
    else
    {
        ui->tableWidget_source->setCellWidget(m_userRow,3,new QPushButton(QIcon("://images/home/file_music_free.png"),""));
    }
    ui->tableWidget_source->setCellWidget(m_userRow,4,new QPushButton(size));
    m_userRow++;
    connect(m_radioBtn4,&QRadioButton::clicked,[=](bool checked){
        if(checked)
        {
            m_sourceType = 0;
            m_sourceVip = vip;
            m_quality = QString(u8"无损");
        }
    });
}

//视频
void DownloadType::addVideoQualityItem_1(QVector<QVariant> &videoBody)
{
    QPushButton *vipBtn = new QPushButton();
    QPushButton *sizeBtn = new QPushButton();
    m_radioBtn5   = new QRadioButton(ui->tableWidget_source);
    ui->tableWidget_source->setCellWidget(5,0,new QLabel(u8"视频资源："));
    ui->tableWidget_source->setCellWidget(5,1, m_radioBtn5);
    m_comboBox = new QComboBox(ui->tableWidget_source);

    for(int i = 0; i < videoBody.count(); i++)
    {
//        qDebug() << videoBody.size();
        QVariant variant_t = videoBody.at(i);//takeAt(i) 取走数据
        VideoBody data = variant_t.value<VideoBody>();// 通用类型转为专用类型
        m_comboBox->addItem(data.videoText,QVariant(data.videoSize));
//        qDebug() << data.videoText << data.videoVip << data.videoSize;
        if(0 == i)//设置第一个item的信息
        {
            if(data.videoVip)//是vip
            {
                vipBtn->setIcon(QIcon("://images/home/file_video_vip.png"));
                sizeBtn->setText(data.videoSize);
                m_sourceVip = data.videoVip;
            }
            else//非vip
            {
                vipBtn->setIcon(QIcon("://images/home/file_music_free.png"));
                sizeBtn->setText(data.videoSize);
                m_sourceVip = data.videoVip;
            }
        }
    }
    m_comboBox->setCurrentIndex(0);
    ui->tableWidget_source->setCellWidget(5,2,m_comboBox);
    ui->tableWidget_source->setCellWidget(5,3,vipBtn);
    ui->tableWidget_source->setCellWidget(5,4,sizeBtn);

    connect(m_radioBtn5,&QRadioButton::clicked,[=](bool checked){
        if(checked)
        {
            m_sourceType = 1;
            QVariant variant_ttt = videoBody.at(m_comboBox->currentIndex());
            VideoBody data_tt = variant_ttt.value<VideoBody>();// 通用类型转为专用类型
            m_sourceVip = data_tt.videoVip;
        }
    });

    //重载是，参数必须和声明时一模一样，包括：const限制，引用，指针
    connect(m_comboBox,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int index){
         m_quality = m_comboBox->itemText(index);
         qDebug() << QString(u8"当前项发生改变：%1").arg(m_comboBox->itemText(index));

            QVariant variant_tt = videoBody.at(index);
            VideoBody data_t = variant_tt.value<VideoBody>();// 通用类型转为专用类型
            if(data_t.videoVip)//是vip
            {
                vipBtn->setIcon(QIcon("://images/home/file_video_vip.png"));
            }
            else//非vip
            {
                vipBtn->setIcon(QIcon("://images/home/file_music_free.png"));
            }
            m_sourceVip = data_t.videoVip;
            sizeBtn->setText(m_comboBox->itemData(index,Qt::UserRole).toString());
    });
}

const QString DownloadType::openLocalFileSystem()
{
    QString fpath = QFileDialog::getExistingDirectory(this,
                                                QString::fromLocal8Bit("选择路径"),
                                                m_curOpenPath);//默认打开软件路径(每次都会变)
    if(!fpath.isEmpty())//不为空
    {
        return fpath;
    }
    else
    {
        return false;//打开不选择有问题
    }
}


DownloadType *DownloadType::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new DownloadType();
    }
    return m_pInstance;
}


void DownloadType::mousePressEvent(QMouseEvent *event)
{
    if(ReleaseCapture())
    {
        QWidget* pWindow = this->window();
        if(pWindow->isTopLevel())
        {
            SendMessage(HWND(pWindow->winId()),WM_SYSCOMMAND,SC_MOVE + HTCAPTION,0);
        }
    }
    event->ignore();
}

bool DownloadType::eventFilter(QObject *watched, QEvent *event)
{

    return QWidget::eventFilter(watched,event);
}


