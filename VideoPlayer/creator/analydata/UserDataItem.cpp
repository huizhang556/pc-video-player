#include "UserDataItem.h"
#include "ui_UserDataItem.h"

UserDataItem::UserDataItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserDataItem)
{
    ui->setupUi(this);
    initworkUI();
    handleSignalsAndSlots();
}

UserDataItem::UserDataItem(const UserDataType &type, const QUrlQuery &query, QWidget *parent):
    QWidget(parent),
    m_type(type),
    m_query(query),
    ui(new Ui::UserDataItem)
{
    ui->setupUi(this);
    initworkUI();
    handleSignalsAndSlots();
    set_user_id();
    set_user_grade();
    set_user_level();
    set_user_header();
    set_user_nick();
    set_user_ctime();
    set_user_motto();
    set_user_likeStatus();
    set_video_url();
}

UserDataItem::~UserDataItem()
{
    delete ui;
}

//初始化UI
void UserDataItem::initworkUI()
{
    m_manager = new QNetworkAccessManager(this);
    ui->frame_check->hide();
    ui->pushButton_tofans->setCheckable(true);
    ui->pushButton_sendmsg->setCheckable(true);
}

//处理信号与槽函数
void UserDataItem::handleSignalsAndSlots()
{
    //网络请求头像
    connect(m_manager,&QNetworkAccessManager::finished,this,&UserDataItem::slot_receivedUserHeader,Qt::UniqueConnection);

    //关注、取消关注
    connect(ui->pushButton_tofans,&QPushButton::clicked,[=](bool checked){
//        if(checked)
//        {
//            qDebug(u8"成为粉丝");
//            bool ok = dataBase::getInstance()->user_operate_setToFollow(true,m_usrid,dataBase::getInstance()->getCurrentUserID());
//            if(ok)
//            {
//                ui->pushButton_tofans->setText(QString(u8"已关注"));
//            }
//        }
//        else
//        {
//            qDebug(u8"取消粉丝");
//           bool ok = dataBase::getInstance()->user_operate_setToFollow(false,m_usrid,dataBase::getInstance()->getCurrentUserID());
//            if(ok)
//            {
//                ui->pushButton_tofans->setText(QString(u8"关注"));
//            }
//        }
    });
}

QString UserDataItem::get_user_nick()
{
    return m_nick;
}

QString UserDataItem::get_user_vurl()
{
    return m_videourl;
}

void UserDataItem::set_user_id()
{
    switch (m_type)
    {
    case FANS:
    {
    m_usrid = m_query.queryItemValue(u8"userid");
    }
        break;
    case WATCHES:
    {
    m_usrid = m_query.queryItemValue(u8"userid");
    }
        break;
    case VIDEO:
    {
    m_usrid = m_query.queryItemValue(u8"userid");
    }
        break;
    case COMMIT:
    {

    }
        break;
    default:
        break;
    }

}

void UserDataItem::set_user_grade()
{
    switch (m_type)
    {
    case FANS:
    {
        m_grade = m_query.queryItemValue(u8"usertype");
        ui->pushButton_grade->setText(QString(u8"等级：") + m_grade);
    }
        break;
    case WATCHES:
    {
        m_grade = m_query.queryItemValue(u8"usertype");
        ui->pushButton_grade->setText(QString(u8"等级：") + m_grade);
    }
        break;
    case VIDEO:
    {
        m_grade = m_query.queryItemValue(u8"playcount");
        ui->pushButton_grade->setText(QString(u8"播放量：")+m_grade);
    }
        break;
    case COMMIT:
    {

    }
        break;
    default:
        break;
    }

}

void UserDataItem::set_user_level()
{
    switch (m_type)
    {
    case FANS:
    {
        m_level = m_query.queryItemValue(u8"usertype");
        ui->pushButton_ulevel->setText(QString(u8"积分：") + m_level);
    }
        break;
    case WATCHES:
    {
        m_level = m_query.queryItemValue(u8"usertype");
        ui->pushButton_ulevel->setText(QString(u8"积分：") + m_level);
    }
        break;
    case VIDEO:
    {
        m_level = m_query.queryItemValue(u8"likecount");
        ui->pushButton_ulevel->setText(QString(u8"点赞量：")+m_level);
    }
        break;
    case COMMIT:
    {

    }
        break;
    default:
        break;
    }
}


void UserDataItem::set_user_header()
{
    switch (m_type)
    {
    case FANS:
    case WATCHES:
    {
        m_header = m_query.queryItemValue(u8"userhead");
        m_manager->get(QNetworkRequest(QUrl(m_header)));
    }
        break;
    case VIDEO:
    {
        m_header = m_query.queryItemValue(u8"cover");
        m_manager->get(QNetworkRequest(QUrl(m_header)));
    }
        break;
    case COMMIT:
    {

    }
        break;
    default:
        break;
    }
}

void UserDataItem::set_user_nick()
{
    switch (m_type)
    {
    case FANS:
    {
        m_nick = m_query.queryItemValue(u8"username");
        ui->pushButton_uname->setText(m_nick);
    }
        break;
    case WATCHES:
    {
        m_nick = m_query.queryItemValue(u8"username");
        ui->pushButton_uname->setText(m_nick);
    }
        break;
    case VIDEO:
    {
        m_nick = m_query.queryItemValue(u8"username");
        ui->pushButton_uname->setText(m_nick);
    }
        break;
    case COMMIT:
    {

    }
        break;
    default:
        break;
    }

}

void UserDataItem::set_user_ctime()
{
    switch (m_type)
    {
    case FANS:
    {
        m_ctime = m_query.queryItemValue(u8"usertime");
        ui->pushButton_createtime->setText(m_ctime);
    }
        break;
    case WATCHES:
    {
        m_ctime = m_query.queryItemValue(u8"usertime");
        ui->pushButton_createtime->setText(m_ctime);
    }
        break;
    case VIDEO:
    {
        m_ctime = m_query.queryItemValue(u8"usertime");
        ui->pushButton_createtime->setText(m_ctime);
    }
        break;
    case COMMIT:
    {

    }
        break;
    default:
        break;
    }

}

void UserDataItem::set_user_motto()
{
    switch (m_type)
    {
    case FANS:
    {
        m_motto = m_query.queryItemValue(u8"usermotto");
        ui->pushButton_umotto->setText(m_motto);
    }
        break;
    case WATCHES:
    {
        m_motto = m_query.queryItemValue(u8"usermotto");
        ui->pushButton_umotto->setText(m_motto);
    }
        break;
    case VIDEO:
    {
        m_motto = m_query.queryItemValue(u8"alias");
        ui->pushButton_umotto->setText(m_motto);
    }
        break;
    case COMMIT:
    {

    }
        break;
    default:
        break;
    }

}

void UserDataItem::set_video_url()
{
    switch (m_type)
    {
    case FANS:
    {

    }
        break;
    case WATCHES:
    {

    }
        break;
    case VIDEO:
    {
        m_videourl = m_query.queryItemValue(u8"url");
    }
        break;
    case COMMIT:
    {

    }
        break;
    default:
        break;
    }
}

void UserDataItem::set_user_likeStatus()
{
    switch (m_type)
    {
    case FANS:
    case WATCHES:
    {
        if(m_query.queryItemValue(u8"userstatus") == "1")
        {
            ui->pushButton_tofans->setChecked(true);
            ui->pushButton_tofans->setText(QString(u8"已关注"));
        }
        else
        {
            ui->pushButton_tofans->setChecked(false);
            ui->pushButton_tofans->setText(QString(u8"关注"));
        }
    }
        break;
    case VIDEO:
    {
        if(m_query.queryItemValue(u8"userstatus") == "1")
        {
            ui->pushButton_tofans->setChecked(true);
            ui->pushButton_tofans->setText(QString(u8"已收藏"));
        }
        else
        {
            ui->pushButton_tofans->setChecked(false);
            ui->pushButton_tofans->setText(QString(u8"未收藏"));
        }
    }
        break;
    case COMMIT:
    {

    }
        break;
    default:
        break;
    }

}




void UserDataItem::slot_receivedUserHeader(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        ui->label_header->setPixmap_(pixmap);
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("粉丝：用户头网络图片像请求错误：")<<reply->errorString();
        QPixmap pixmap(":/images/bgpic/dieji3.png");//默认图标
        ui->label_header->setPixmap_(pixmap);
    }
}

