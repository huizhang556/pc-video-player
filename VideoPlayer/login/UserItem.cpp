#include "UserItem.h"
#include "ui_UserItem.h"

UserItem::UserItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSLots();

}

UserItem::UserItem(const QString &user_nick, const QString &user_pwd, const QString &user_header, QWidget *parent):
    QWidget(parent),
    m_userName(user_nick),
    m_userPwd(user_pwd),
    m_userHeader(user_header),
    ui(new Ui::UserItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSLots();
    setUserName(user_nick);
    setUserPwd(user_pwd);
    setUserHeader(user_header);
}

UserItem::~UserItem()
{
    delete ui;
}

void UserItem::initWorkUI()
{
    m_manager = new QNetworkAccessManager(this);
}

void UserItem::handleSignalsAndSLots()
{
    connect(m_manager,&QNetworkAccessManager::finished,this,&UserItem::slot_setUserHeaderPix,Qt::UniqueConnection);

    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        emit sig_item_remove(ui->pushButton_name->text());
    });

    connect(ui->pushButton_name,&QPushButton::clicked,[=](){
        emit sig_item_clicked(ui->pushButton_name->text());
    });
}

void UserItem::setUserName(const QString &name)
{
    m_userName = name;
    ui->pushButton_name->setText(m_userName);
}

void UserItem::setUserPwd(const QString& pwd)
{
    m_userPwd = pwd;
}

void UserItem::setUserHeader(const QString& header)
{
    m_userHeader = header;
    m_manager->get(QNetworkRequest(QUrl(m_userHeader)));
}

void UserItem::slot_setUserHeaderPix(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        ui->label_header->setPixmap_(pixmap);
        ui->label_header->setScaledContents(true);
        qDebug() <<QString::fromLocal8Bit("用户列表：网络请求图片设置成功！");
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("用户列表：请求错误：")<<reply->errorString();
        QPixmap pixmap("://images/user/default_woman00.png");//默认图标
        ui->label_header->setPixmap_(pixmap);
        ui->label_header->setScaledContents(true);
    }
}
