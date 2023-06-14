#include "MediaGroup.h"
#include "ui_MediaGroup.h"

MediaGroup::MediaGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaGroup)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

MediaGroup::MediaGroup(GROUPTYPE type, const QString& g_id, const QString& g_name, const QString& g_cover_url, QWidget *parent):
    QWidget(parent),
    m_type(type),
    m_groupid(g_id),
    m_name(g_name),
    m_pix_url(g_cover_url),
    ui(new Ui::MediaGroup)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    setItemType();
    setItemCover();
}

MediaGroup::~MediaGroup()
{
    delete ui;
}

void MediaGroup::initWorkUI()
{
    m_manager = new QNetworkAccessManager(this);

    ui->pushButton_intro->setToolTip(QString(u8"双击修改名称"));
    ui->pushButton_addnew->setToolTip(QString(u8"添加文件"));
    ui->pushButton_delete->setToolTip(QString(u8"删除合集"));
    ui->label_cover->setToolTip(QString(u8"右键单击更换封面"));
    ui->pushButton_return->setToolTip(QString(u8"返回"));
    ui->pushButton_addnew->hide();
    ui->pushButton_delete->hide();
}

void MediaGroup::handleSignalsAndSlots()
{
    //接收封面数据
    connect(m_manager,&QNetworkAccessManager::finished,this,&MediaGroup::slot_receiveGroupCover,Qt::UniqueConnection);

    //添加
    connect(ui->pushButton_addnew,&QPushButton::clicked,[=](){
        emit sig_item_additem();
    });

    //删除
    connect(ui->pushButton_delete,&QPushButton::clicked,[=](){
        emit sig_item_delete();
    });

    //回车
    connect(ui->lineEdit_rename,&QLineEdit::returnPressed,[=](){
        ui->pushButton_intro->setText(ui->lineEdit_rename->text());
        ui->stackedWidget_changed->setCurrentWidget(ui->page_name);
        emit sig_item_rename(ui->lineEdit_rename->text());
    });

    //返回
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){
        ui->stackedWidget_cover->setCurrentIndex(0);
    });

    //选择封面
    connect(ui->pushButton_opencover,&QPushButton::clicked,[=](){
        QString filepath =  QFileDialog::getOpenFileName();
        if(!filepath.isEmpty() && QUrl(filepath).isValid())
        {
            ui->label_cover->setPixmap(QPixmap(filepath));
            ui->label_cover->setScaledContents(true);
            ui->stackedWidget_cover->setCurrentIndex(0);
            m_cover = ui->label_cover->pixmap()->toImage();
            QByteArray imageArray;
            QBuffer buffer;
            buffer.open(QIODevice::WriteOnly);
            m_cover.save(&buffer,"png");//QImage存进buffer转为QByteArray
            imageArray.append(buffer.data());
            buffer.close();
            slot_uploadUserGroupCover(imageArray);//上传图片
        }
    });
}

void MediaGroup::setInstallEventFilter()
{
    this->installEventFilter(this);
    ui->pushButton_intro->installEventFilter(this);
    ui->label_cover->installEventFilter(this);
}

bool MediaGroup::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *mevent = static_cast<QMouseEvent*>(event);
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->pushButton_addnew->show();
            ui->pushButton_delete->show();

//            qDebug() << QString(u8"进入");
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->pushButton_addnew->hide();
            ui->pushButton_delete->hide();
//            qDebug() << QString(u8"离开");
        }
    }
    if(watched == ui->pushButton_intro)
    {
        if(event->type() == QEvent::MouseButtonDblClick && m_type != G_DISPLAY)
        {
            ui->stackedWidget_changed->setCurrentWidget(ui->page_rename);
            ui->lineEdit_rename->setText(ui->pushButton_intro->text());
            ui->lineEdit_rename->selectAll();
            ui->lineEdit_rename->setFocus();
        }
    }
    if(watched == ui->label_cover)
    {
        if(event->type() == QEvent::MouseButtonPress && mevent->buttons() & Qt::RightButton && m_type != G_DISPLAY)//右键单击
        {
            ui->stackedWidget_cover->setCurrentIndex(1);
//            ui->pushButton_opencover->click();//模拟点击
        }
        else if(event->type() == QEvent::MouseButtonPress && mevent->buttons() & Qt::LeftButton)//单左键击
        {
            emit sig_item_clicked();
        }
        else if(event->type() == QEvent::Enter)
        {
            setCursor(Qt::PointingHandCursor);
        }
        else if(event->type() == QEvent::Leave)
        {
            setCursor(Qt::ArrowCursor);
        }
    }
    return QWidget::eventFilter(watched,event);
}

void MediaGroup::setItemCover()
{
    switch (m_type) {
    case G_NORMAL:
    case G_DISPLAY:
    {
    //非新建item需要获取网络图片
     m_manager->get(QNetworkRequest(QUrl(m_pix_url)));
    }
        break;
    case G_CUSTOM:
    {
    //自定义暂时不需要
    QPixmap pixmap("://images/bgpic/cusvideoitem4.png");//默认图标
    ui->label_cover->setPixmap(pixmap);
    ui->label_cover->setScaledContents(true);
    }
        break;
    default:
        break;
    }
}

void MediaGroup::setItemType()
{
    switch (m_type) {
    case G_NORMAL:
    {
    //保持默认
        ui->stackedWidget_cover->setCurrentIndex(0);
        ui->stackedWidget_changed->setCurrentWidget(ui->page_name);
        ui->pushButton_intro->setText(m_name);
    }
        break;
    case G_DISPLAY:
    {
    //保持默认
        ui->stackedWidget_cover->setCurrentIndex(0);
        ui->stackedWidget_changed->setCurrentWidget(ui->page_name);
        ui->pushButton_intro->setText(m_name);
        ui->label_cover->setToolTip(nullptr);
        ui->frame_add->hide();
        ui->frame_del->hide();
    }
        break;
    case G_CUSTOM:
    {
    //自定义需要选中
        ui->stackedWidget_cover->setCurrentIndex(0);
        ui->stackedWidget_changed->setCurrentWidget(ui->page_rename);
        ui->lineEdit_rename->setText(m_name);
        ui->lineEdit_rename->selectAll();
        ui->lineEdit_rename->setFocus();
    }
        break;
    default:
        break;
    }
}

//网络接收封面
void MediaGroup::slot_receiveGroupCover(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap(ui->label_cover->size());//默认图标
        pixmap.loadFromData(reply->readAll());
        ui->label_cover->setPixmap(pixmap);
        ui->label_cover->setScaledContents(true);
        m_cover = ui->label_cover->pixmap()->toImage();
        qDebug() <<QString::fromLocal8Bit("group封面网络请求图片设置成功！");

    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("group封面网络请求错误：")<<reply->errorString();
        QPixmap pixmap("://images/bgpic/cusvideoitem4.png");//默认图标
        ui->label_cover->setPixmap(pixmap);
        ui->label_cover->setScaledContents(true);
    }
}

bool MediaGroup::slot_uploadUserGroupCover(const QByteArray &pic_bytedata)
{
    if(pic_bytedata.isNull() || pic_bytedata.isEmpty())
    {
        qDebug() << QString(u8"[封面]图片数据为空有误！");
        return false;
    }
    //创建工作对象
    UploadWork* upWorker = new UploadWork();
    //创建线程
    QThread *workThread = new QThread();
    //工作对象移动到线程中
    upWorker->moveToThread(workThread);
    //开启线程
    workThread->start();//开启线程
    //工作线程开始上传
    upWorker->slot_receiveData_accept(pic_bytedata,"user_cover");//图片数据 + 自定义路径
    //信号与槽函数
    connect(workThread,&QThread::finished,upWorker,&QObject::deleteLater);//线程结束时，工作对象自动删除
    connect(workThread,&QThread::finished,workThread,&QThread::deleteLater);//线程结束时，线程内对象自动删除
    //上传完成--传回信息()
    connect(upWorker,&UploadWork::sig_work_finished,[=](bool success, QString pix_url, QString md5){
        if(success)
        {
            m_pix_url = pix_url;
            emit sig_item_newCover(m_groupid,m_pix_url);
            qDebug() <<QString(u8"[封面]--服务器封面上传成功！新封面链接：%1").arg(pix_url);
        }
        else
        {
            qDebug() <<QString(u8"[封面]--服务器封面上传失败！");
        }
    });
}
