#include "HeadLabel.h"
#include "ui_HeadLabel.h"

HeadLabel::HeadLabel(QWidget *parent) :
    QLabel(parent),
    ui(new Ui::HeadLabel)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

HeadLabel::HeadLabel(const QString &url, const bool on_del, const bool on_checked, QWidget *parent):
    QLabel(parent),
    m_url(url),
    m_del(on_del),
    m_checked(on_checked),
    ui(new Ui::HeadLabel)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setDeleteOn();
    setCheckedOn();
    m_manager = new QNetworkAccessManager(this);
    if(QUrl(m_url).isValid())
    {
        m_manager->get(QNetworkRequest(QUrl(m_url)));
    }
    connect(m_manager,&QNetworkAccessManager::finished,this,&HeadLabel::slot_setUserHeaderPix,Qt::UniqueConnection);
}

HeadLabel::HeadLabel(const QPixmap &pix, const bool on_del, const bool on_checked, QWidget *parent):
    QLabel(parent),
    m_pix(pix),
    m_del(on_del),
    m_checked(on_checked),
    ui(new Ui::HeadLabel)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setDeleteOn();
    setCheckedOn();
    this->setPixmap(pix);
    this->setScaledContents(true);
}

HeadLabel::~HeadLabel()
{
    delete ui;
}

void HeadLabel::initWorkUI()
{
    this->installEventFilter(this);
}

void HeadLabel::handleSignalsAndSlots()
{


    connect(ui->pushButton_delete,&QPushButton::clicked,[=](){
        emit sig_item_delete();
    });

    connect(ui->pushButton_checked,&QPushButton::clicked,[=](){
        if(!this->pixmap()->isNull())
        {
//            emit sig_item_pix(m_pix);
        }
    });
}

bool HeadLabel::eventFilter(QObject *watched, QEvent *event)
{
    QMouseEvent *mevent = static_cast<QMouseEvent*>(event);
    if(watched == this)
    {
        if(event->type() == QEvent::MouseButtonPress && mevent->buttons() & Qt::LeftButton)
        {
            emit sig_item_pix(m_pix);
        }
        else if(event->type() == QEvent::Enter && m_del)
        {
            ui->pushButton_delete->show();
        }
        else if(event->type() == QEvent::Leave && m_del)
        {
            ui->pushButton_delete->hide();
        }
    }
    return QLabel::eventFilter(watched,event);
}

void HeadLabel::slot_setUserHeaderPix(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        this->setPixmap(pixmap);
        this->setScaledContents(true);
        qDebug() <<QString::fromLocal8Bit("通用头像列表：网络请求图片设置成功！");
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("用户列表：请求错误：")<<reply->errorString();
        QPixmap pixmap("://images/user/default_woman00.png");//默认图标
        this->setPixmap(pixmap);
        this->setScaledContents(true);
    }
}

void HeadLabel::setDeleteOn()
{
    if(!m_del)//没有删除按钮
    {
        ui->pushButton_delete->hide();
    }
    else
    {
        ui->pushButton_delete->show();
    }
}

void HeadLabel::setCheckedOn()
{
    if(!m_checked)//没有删除按钮
    {
        ui->pushButton_checked->hide();
    }
    else
    {
        ui->pushButton_checked->show();
    }
}
