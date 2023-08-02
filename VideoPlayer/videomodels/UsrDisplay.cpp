#include "UsrDisplay.h"
#include "ui_UsrDisplay.h"
//类外初始化
UsrDisplay* UsrDisplay::m_pInstance = nullptr;

UsrDisplay::UsrDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsrDisplay)
{
    ui->setupUi(this);
    setFixedSize(360,260);
    setAttribute(Qt::WA_TranslucentBackground);//必须背景透明
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint);
    initWorkUI();
    handleSignalAndSlot();
}

UsrDisplay::~UsrDisplay()
{
    delete ui;
    //删除创建的单例
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void UsrDisplay::initWorkUI()
{
    ui->pushButton_towatch->setCheckable(true);

    m_manager = new QNetworkAccessManager(this);
}

void UsrDisplay::handleSignalAndSlot()
{
    //加载网络头像
    connect(m_manager,&QNetworkAccessManager::finished,this,&UsrDisplay::slot_receivedUserHeader,Qt::UniqueConnection);
    //关注/取消关注
    connect(ui->pushButton_towatch,&QPushButton::clicked,[=](bool checked){
        if(checked)
        {
            qDebug(u8"关注");
            bool ok = dataBase::getInstance()->user_operate_setToFollow(true,dataBase::getInstance()->getCurrentUserID(),m_usrQueryUrl.queryItemValue(u8"userid"));
            if(ok)
            {
                ui->pushButton_towatch->setText(QString(u8"已关注"));
            }
        }
        else
        {
            qDebug(u8"取消关注");
           bool ok = dataBase::getInstance()->user_operate_setToFollow(false,dataBase::getInstance()->getCurrentUserID(),m_usrQueryUrl.queryItemValue(u8"userid"));
            if(ok)
            {
                ui->pushButton_towatch->setText(QString(u8"+ 关注"));
            }
        }
        slot_reloadWatchesCounts(m_usrQueryUrl.queryItemValue(u8"userid"));//更新粉丝数量
    });
}

void UsrDisplay::updateUsrUiInfo(QUrlQuery queryUrl)
{
    //0.赋予成员变量新值
    m_usrQueryUrl = queryUrl;
    //1.更新头像
    m_manager->get(QNetworkRequest(QUrl(m_usrQueryUrl.queryItemValue(u8"userhead"))));
    //2.更新用户名
    ui->pushButton_unick->setText(m_usrQueryUrl.queryItemValue(u8"username"));
    //3.更新等级
    slot_setUserGrade(m_usrQueryUrl.queryItemValue(u8"usertype").toInt());
    //4.更新关注数
    ui->pushButton_uwatch->setText(m_usrQueryUrl.queryItemValue(u8"userwatch")+QString(u8" 关注"));
    //5.更新粉丝数
    ui->pushButton_ufans->setText(m_usrQueryUrl.queryItemValue(u8"userfans")+QString(u8" 粉丝"));
    //6.更新获赞数
    ui->pushButton_ulike->setText(m_usrQueryUrl.queryItemValue(u8"userlove")+QString(u8" 获赞"));
    //7.更新认证信息
    ui->pushButton_certInfo->setText(QString(u8"bilibili个人认证：晟唐影视官方账号..."));
    //8.更新座右铭
    QString motto = m_usrQueryUrl.queryItemValue(u8"usermotto");
    QFontMetrics fontMetric = QFontMetrics(ui->pushButton_uIntroduce->font());
    QString motto_t = fontMetric.elidedText(motto,Qt::ElideRight,270,0);
    ui->pushButton_uIntroduce->setText(motto_t);
    ui->pushButton_uIntroduce->setToolTip(motto);
    //9.更新关注状态
    slot_setUserWatchedStatus(m_usrQueryUrl.queryItemValue(u8"userid"),dataBase::getInstance()->getCurrentUserID());
}

UsrDisplay *UsrDisplay::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new UsrDisplay();
    }
    return m_pInstance;
}

void UsrDisplay::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->close();
}


void UsrDisplay::slot_receivedUserHeader(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        QPixmap pixmap;
        pixmap.loadFromData(reply->readAll());
        ui->label_usrheader->setPixmap_(pixmap);
        ui->label_usrheader->setScaledContents(true);
        qDebug() <<QString(u8"个人信息显示---网络头像请求图片设置成功！");
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString(u8"个人信息显示---网络头像请求错误：")<<reply->errorString();
        QPixmap pixmap("://images/user/default_woman00.png");//默认图标
        ui->label_usrheader->setPixmap_(pixmap);
        ui->label_usrheader->setScaledContents(true);
    }
}

void UsrDisplay::slot_setUserGrade(const int grade)
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
    ui->pushButton_ulevel->setIcon(QIcon(pixpath));
    ui->pushButton_ulevel->setText(gradeName);
}

void UsrDisplay::slot_setUserWatchedStatus(const QString &user_id, const QString &follow_id)
{

    if(!dataBase::getInstance()->getCurrentUserOnline() || dataBase::getInstance()->getCurrentUserID() ==  user_id)
    {
        ui->pushButton_towatch->setText(QString(u8"+ 关注"));
        ui->pushButton_towatch->setChecked(false);
        ui->pushButton_towatch->setEnabled(false);
        return;
    }
    else
    {
        ui->pushButton_towatch->setEnabled(true);
        bool isok = dataBase::getInstance()->user_operate_getFollow(user_id,follow_id);
        if(isok)
        {
            ui->pushButton_towatch->setText(QString(u8"已关注"));
            ui->pushButton_towatch->setChecked(true);
        }
        else
        {
            ui->pushButton_towatch->setText(QString(u8"+ 关注"));
            ui->pushButton_towatch->setChecked(false);
        }
        slot_reloadWatchesCounts(m_usrQueryUrl.queryItemValue(u8"userid"));
    }
}

void UsrDisplay::slot_reloadWatchesCounts(const QString &userid)
{
    QUrlQuery quer_user = dataBase::getInstance()->user_getCurMediaUserInfo(userid);
    ui->pushButton_ufans->setText(quer_user.queryItemValue(u8"userfans")+QString(u8" 粉丝"));
}
