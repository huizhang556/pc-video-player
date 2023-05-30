#include "PersonFileForm.h"
#include "ui_PersonFileForm.h"
#include <QDebug>

PersonFileForm::PersonFileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PersonFileForm)
{
    ui->setupUi(this);
    initWorkUI();
    chandleSignalsAndSLots();
}

PersonFileForm::~PersonFileForm()
{
    delete ui;
}

void PersonFileForm::initWorkUI()
{
    ui->stackedWidget->setCurrentIndex(0);
    m_manager = new QNetworkAccessManager(this);
    //设置bar四个图标
    ui->tabWidget->tabBar()->setTabIcon(0,QIcon(":/images/icon/his_pic.png"));
    ui->tabWidget->tabBar()->setTabIcon(1,QIcon(":/images/icon/collect_video_hover.png"));
    ui->tabWidget->tabBar()->setTabIcon(2,QIcon(":/images/icon/dingyue_hover.png"));
    ui->tabWidget->tabBar()->setTabIcon(3,QIcon(":/images/icon/skin_hover.png"));
    ui->tabWidget->tabBar()->setTabIcon(4,QIcon(":/images/icon/download_video_hover.png"));

    ui->pushButton_usrLevel->setIconSize(QSize(ui->pushButton_usrLevel->size()));
}

void PersonFileForm::chandleSignalsAndSLots()
{
    //网络请求头像
    connect(m_manager,&QNetworkAccessManager::finished,this,&PersonFileForm::slot_receivedUserHeader,Qt::UniqueConnection);

    //返回页
    connect(ui->pushButton_returnpage,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(0);
        emit sig_sendReturnPage(0);
    });

    //看过---全部历史
    connect(ui->pushButton_his_all,&QPushButton::clicked,[=](){ ui->stackedWidget_history->setCurrentIndex(0);});
    //看过---本地视频
    connect(ui->pushButton_his_localfile,&QPushButton::clicked,[=](){ ui->stackedWidget_history->setCurrentIndex(1);});
    //看过---选择文件
    connect(ui->pushButton_his_select,&QPushButton::clicked,[=](){qDebug() << "HIS_SELECT_FILES"; });
    //看过---全部清空
    connect(ui->pushButton_his_alldelete,&QPushButton::clicked,[=](){qDebug() << "HIS_DELETE_FILES"; });

    //收藏---全部收藏按钮
    connect(ui->pushButton_coll_all,&QPushButton::clicked,[=](){ ui->stackedWidget_collect->setCurrentIndex(0);});
    //收藏---电影收藏按钮
    connect(ui->pushButton_coll_movies,&QPushButton::clicked,[=](){ ui->stackedWidget_collect->setCurrentIndex(1);});
    //收藏---其他收藏按钮
    connect(ui->pushButton_coll_other,&QPushButton::clicked,[=](){ui->stackedWidget_collect->setCurrentIndex(2); });
    //收藏---选择文件按钮
    connect(ui->pushButton_coll_select,&QPushButton::clicked,[=](){ qDebug() << "COLL_SELECT_FILES";});
    //收藏---全部清空按钮
    connect(ui->pushButton_coll_alldelete,&QPushButton::clicked,[=](){qDebug() << "COLL_DELETE_FILES"; });

    //订阅---电影订阅按钮
    connect(ui->pushButton_order_videos,&QPushButton::clicked,[=](){ ui->stackedWidget_order->setCurrentIndex(0);});
    //订阅---音乐订阅按钮
    connect(ui->pushButton_order_musics,&QPushButton::clicked,[=](){ ui->stackedWidget_order->setCurrentIndex(1);});
    //订阅---删除按钮
    connect(ui->pushButton_order_delete,&QPushButton::clicked,[=](){qDebug() << "ORDER_DELETE_FILES"; });

    //换肤---电影
    connect(ui->pushButton_skin_videos,&QPushButton::clicked,[=](){ ui->stackedWidget_skin->setCurrentIndex(0);});
    //换肤---音乐
    connect(ui->pushButton_skin_musics,&QPushButton::clicked,[=](){ ui->stackedWidget_skin->setCurrentIndex(1);});
    //换肤---删除
    connect(ui->pushButton_skin_delete,&QPushButton::clicked,[=](){qDebug() << "SKIN_DELETE_FILES"; });

    //下载---视频
    connect(ui->pushButton_down_videos,&QPushButton::clicked,[=](){ ui->stackedWidget_down->setCurrentIndex(0);});
    //下载---音乐
    connect(ui->pushButton_down_musics,&QPushButton::clicked,[=](){ ui->stackedWidget_down->setCurrentIndex(1);});
    //下载---打开选择文件
    connect(ui->pushButton_down_open,&QPushButton::clicked,[=](){qDebug() << "DOWN_OPEN_FILES";});
    //下载---设置
    connect(ui->pushButton_down_set,&QPushButton::clicked,[=](){ qDebug() << "DOWN_SET_FILES";});
    //下载---全部开始
    connect(ui->pushButton_down_allstart,&QPushButton::clicked,[=](){qDebug() << "DOWN_ALLSTART_FILES"; });
    //下载---全部暂停
    connect(ui->pushButton_down_allpause,&QPushButton::clicked,[=](){ qDebug() << "DOWN_ALLPAUSE_FILES"; });
    //下载---全部删除
    connect(ui->pushButton_down_alldel,&QPushButton::clicked,[=](){ qDebug() << "DOWN_ALLDELETE_FILES";});
}


/*重载槽函数1：*/
void PersonFileForm::setShowCurrentWidget(QObject *obj1, int index1, QObject *obj2, int index2)
{

}

/*重载槽函数2：*/
void PersonFileForm::setShowCurrentWidget(QObject *obj1, QWidget *wdgt1, QObject *obj2, QWidget *wdgt2)
{

}

//接收用户头像数据
void PersonFileForm::slot_receivedUserHeader(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        ui->label_otherUsrHead->setPixmap_(pixmap);
        qDebug() <<QString::fromLocal8Bit("mini放器播当前媒体用户头网络图片设置成功！");
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("mini播放器播当前媒体用户头网络图片像请求错误：")<<reply->errorString();
        QPixmap pixmap(":/images/bgpic/dieji3.png");//默认图标
        ui->label_otherUsrHead->setPixmap_(pixmap);
    }
}

void PersonFileForm::setOtherUser_grade(const int grade)
{
    QString pixpath = "";
    QString gradeName = "";
    switch (grade) {
    case 0://游客
    {
        pixpath = QString("://images/user/user_visitor.png");
        gradeName = QString(u8"普通游客");
    }
        break;
    case 1://普通
    {
        pixpath = QString("://images/user/user_vip.png");
        gradeName = QString(u8"注册用户");
    }
        break;
    case 2://会员
    {
        pixpath = QString("://images/user/user_suvip.png");
        gradeName = QString(u8"普通会员");
    }
        break;
    case 3://超级会员
    {
        pixpath = QString("://images/user/user_ssvip.png");
        gradeName = QString(u8"超级会员");
    }
        break;
    default:
        break;
    }
    ui->pushButton_usrLevel->setIcon(QIcon(pixpath));
    ui->pushButton_lvName->setText(gradeName);
}

/*获取QStackedWidget*/
QStackedWidget *PersonFileForm::getgetCurrentShowWidget_SW()
{

    return new QStackedWidget();
}

/*获取QListWidget*/
QListWidget *PersonFileForm::getCurrentShowWidget_LW()
{
    return new QListWidget();
}

/*获取QTabWidget*/
QTabWidget *PersonFileForm::getCurrentShowWidget_TW()
{
    return ui->tabWidget;
}

void PersonFileForm::slot_showOtherUserInfo(const QString &userid)
{
    ui->stackedWidget->setCurrentIndex(1);
    QUrlQuery quer_user = dataBase::getInstance()->user_getCurMediaUserInfo(userid);
//    QString     m_userId        =   quer_user.queryItemValue(u8"userid");
    QString     m_usrName       =   quer_user.queryItemValue(u8"username");
    QString     m_usrHead       =   quer_user.queryItemValue(u8"userhead");
    QString     m_usrType       =   quer_user.queryItemValue(u8"usertype");
    QString     m_usrwatch      =   quer_user.queryItemValue(u8"userwatch");
    QString     m_usrfans       =   quer_user.queryItemValue(u8"userfans");
    QString     m_usrlove       =   quer_user.queryItemValue(u8"userlove");
    QString     m_usrmotto      =   quer_user.queryItemValue(u8"usermotto");

    ui->pushButton_usrName->setText(m_usrName);
    setOtherUser_grade(m_usrType.toInt());//图标+等级
    ui->label_motto->setText(m_usrmotto);
    ui->toolButton_watch_counts->setText(m_usrwatch);
    ui->toolButton_fans_counts->setText(m_usrfans);
    ui->toolButton_love_counts->setText(m_usrlove);

    m_manager->get(QNetworkRequest(QUrl(m_usrHead)));

    qDebug() <<QString(u8"当前用id户为：") << userid;
}


