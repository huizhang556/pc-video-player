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
    //通用
    set_user_id();
    set_user_page();
    set_user_grade();
    set_user_level();
    set_user_header();
    set_user_nick();
    set_user_ctime();
    set_user_motto();
    set_user_likeStatus();
    set_video_url();
    set_user_theme();
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

QString UserDataItem::get_user_keywords()
{
    switch (m_type)
    {
    case FANS:
    case WATCHES:
    {
        return ui->pushButton_uname->text();//检索的是用户名称
    }
        break;
    case VIDEO:
    {
        return ui->label_vintro->text();//检索到的是视频介绍
    }
        break;
    case COMMIT:
    {
        return ui->pushButton_oldcomment->text();//检索到的是评论内容
    }
        break;
    default:
        break;
    }
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
    m_usrid = m_query.queryItemValue(u8"userid");
    }
        break;
    default:
        break;
    }

}

//初始化一些设置
void UserDataItem::set_user_page()
{
    switch (m_type)
    {
    case FANS:
    case WATCHES:
    {
        ui->stackedWidget_data->setCurrentWidget(ui->page_dianzan);
    }
        break;
    case VIDEO:
    {
        m_movie.setFileName(":/images/status/video_loading.gif");
        m_movie.setScaledSize(QSize(165,100));
        ui->label_vcover->setMovie(&m_movie);
        m_movie.start();
        ui->stackedWidget_data->setCurrentWidget(ui->page_colvideo);
    }
        break;
    case COMMIT:
    {
        ui->stackedWidget_data->setCurrentWidget(ui->page_comment);
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
        m_playcount = m_query.queryItemValue(u8"playcount");
        ui->pushButton_vplaycount->setText(m_playcount);
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
        m_likecount = m_query.queryItemValue(u8"likecount");
        ui->pushButton_vlikecount->setText(m_likecount);
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
        m_cover = m_query.queryItemValue(u8"cover");
        m_manager->get(QNetworkRequest(QUrl(m_cover)));
    }
        break;
    case COMMIT:
    {
        m_cover = m_query.queryItemValue(u8"cover");
        m_manager->get(QNetworkRequest(QUrl(m_cover)));
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
        ui->pushButton_vusername->setText(m_nick);
        ui->pushButton_commentnick->setText(m_nick);//测试
    }
        break;
    case COMMIT:
    {
        m_nick = m_query.queryItemValue(u8"username");
        ui->pushButton_commentnick->setText(m_nick);
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
        ui->pushButton_vctime->setText(m_ctime);
    }
        break;
    case COMMIT:
    {
        m_ctime = m_query.queryItemValue(u8"usertime");
        ui->pushButton_comtime->setText(m_ctime);
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
        ui->label_vintro->setText(m_motto);
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

void UserDataItem::set_user_theme()
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
        m_vtheme = m_query.queryItemValue(u8"theme");
        ui->pushButton_vtype->setText(m_vtheme);
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
        switch (m_type)
        {
        case FANS:
        case WATCHES:
        {
            ui->label_header->setPixmap_(pixmap);
            ui->label_header->setScaledContents(true);
        }
            break;
        case VIDEO:
        {
            ui->label_vcover->setPixmap(pixmap);
            ui->label_vcover->setScaledContents(true);
            ui->label_comheader->setPixmap_(pixmap.copy());//测试
            ui->label_comheader->setScaledContents(true);
            if(m_movie.state() == QMovie::Running)
            {
                m_movie.stop();
            }
        }
            break;
        case COMMIT:
        {
            ui->label_comheader->setPixmap_(pixmap);
            ui->label_comheader->setScaledContents(true);
        }
            break;
        default:
            break;
        }

    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString(u8"粉丝：用户头网络图片像请求错误：")<<reply->errorString();
        QPixmap pixmap(":/images/user/default_header.png");//默认图标
        switch (m_type)
        {
        case FANS:
        case WATCHES:
        {
            ui->label_header->setPixmap_(pixmap);
        }
            break;
        case VIDEO:
        {
            ui->label_vcover->setPixmap(pixmap);
            if(m_movie.state() == QMovie::Running)
            {
                m_movie.stop();
            }
        }
            break;
        case COMMIT:
        {
            ui->label_comheader->setPixmap_(pixmap);
        }
            break;
        default:
            break;
        }

    }
}

