#include "HeadHover.h"
#include "ui_HeadHover.h"
#include <QListWidgetItem>


HeadHover::HeadHover(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HeadHover)
{
    ui->setupUi(this);
    setFixedSize(240,310);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    initWorkUI();
    handleSignalsAndSlots();
}

HeadHover::~HeadHover()
{
    delete ui;
}

void HeadHover::initWorkUI()
{
    m_manager = new QNetworkAccessManager(this);

    QListWidgetItem *item1 = new QListWidgetItem(QIcon("://images/user/user_zhuye.png"),QString::fromLocal8Bit("创作中心"));
    QListWidgetItem *item2 = new QListWidgetItem(QIcon("://images/user/user_vipcenter.png"),QString::fromLocal8Bit("个人主页"));
    QListWidgetItem *item3 = new QListWidgetItem(QIcon("://images/user/user_changepwd.png"),QString::fromLocal8Bit("重置密码"));
    QListWidgetItem *item4 = new QListWidgetItem(QIcon("://images/user/user_songlist.png"),QString::fromLocal8Bit("注销账号"));
    QListWidgetItem *item5 = new QListWidgetItem(QIcon("://images/user/user_exit.png"),QString::fromLocal8Bit("退出登录"));
    ui->listWidget_menu->addItem(item1);
    ui->listWidget_menu->addItem(item2);
    ui->listWidget_menu->addItem(item3);
    ui->listWidget_menu->addItem(item4);
    ui->listWidget_menu->addItem(item5);
    ui->listWidget_menu->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_menu->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_menu->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    slots_setUserIcon(1,"visitor");

    //遮罩
//    ui->label_head->setFixedSize(QSize(50,50));//遮罩矩形要使用这个大小
//    QRegion maskRegion(ui->label_head->rect(),QRegion::Ellipse);//创建圆形遮罩
//    ui->label_head->setMask(maskRegion);//设置圆形遮罩
    ui->label_head->setToolTip(QString(u8"单击修改头像"));
}

void HeadHover::handleSignalsAndSlots()
{
    //修改头像
    connect(ui->label_head,&RoundLab::sig_clicked,[=](){
        ChangeHead::getInstance()->exec_(OPENTYPE::PER_HEAD);
    });

    connect(ui->listWidget_menu,&QListWidget::itemClicked,[=](QListWidgetItem *item){
        emit sig_itemChanged(item->text());
        this->hide();
    });

    connect(m_manager,&QNetworkAccessManager::finished,this,&HeadHover::slot_receivedNetworkPicture,Qt::UniqueConnection);
}

//设置个人信息
void HeadHover::slot_setCurrentUserInfo(const QString &head="", const QString &nick=QString::fromLocal8Bit("新用户"), int grade = 1, const QString &info=QString::fromLocal8Bit("快点听歌去吧^_^"))
{
    slots_setUserHead(head);
    slots_setUserName(nick);
    slots_setUserIcon(grade,nick);
    slot_setUserInfo(info);
}

void HeadHover::slots_setUserHead(const QString &head)
{
    m_manager->get(QNetworkRequest(QUrl(head)));
}

void HeadHover::slots_setUserName(const QString& nick)
{
    QFont font;
    font.setPixelSize(13);
    QFontMetrics   fontMetric = QFontMetrics(font);
    QString text = fontMetric.elidedText(nick,Qt::ElideRight,130,0);
    ui->pushButton_userName->setText(text);
}

void HeadHover::slots_setUserIcon(int grade,const QString &nick)
{
//    ui->pushButton_userName->setLayoutDirection(Qt::RightToLeft);//图标放在右侧
    switch (grade)
    {
    case 0:
    {
        ui->pushButton_userName->setIcon(QIcon("://images/user/user_visitor.png"));
        ui->pushButton_userName->setToolTip(nick + QString::fromLocal8Bit("(普通游客)"));
    }
        break;
    case 1:
    {
        ui->pushButton_userName->setIcon(QIcon("://images/user/user_vip.png"));
        ui->pushButton_userName->setToolTip(nick + QString::fromLocal8Bit("(注册用户)"));
    }
        break;
    case 2:
    {
        ui->pushButton_userName->setIcon(QIcon("://images/user/user_suvip.png"));
        ui->pushButton_userName->setToolTip(nick + QString::fromLocal8Bit("(普通会员)"));
    }
        break;
    case 3:
    {
        ui->pushButton_userName->setIcon(QIcon("://images/user/user_ssvip.png"));
        ui->pushButton_userName->setToolTip(nick + QString::fromLocal8Bit("(超级会员)"));
    }
        break;
    default:
        ui->pushButton_userName->setIcon(QIcon("://images/user/user_zhuye.png"));
        break;
    }
}

void HeadHover::slot_setUserInfo(const QString &info)
{
    ui->pushButton_otherInfo->setText(info);
}

void HeadHover::slot_receivedNetworkPicture(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        //获取字节流构造 QPixmap 对象
        m_headBytes = reply->readAll();
        m_headPixmap.loadFromData(m_headBytes);
        ui->label_head->setPixmap_(m_headPixmap);
        ui->label_head->setScaledContents(true);
        qDebug() <<QString::fromLocal8Bit("网络请求图片设置成功！");
        qDebug() <<QString::fromLocal8Bit("本次网络请求图片的大小：")<<m_headBytes.size()<<endl
                <<QString::fromLocal8Bit("pixmap真正大小：")<< m_headPixmap.size();
    }
    else//请求失败，加载默认图片
    {
        qDebug() <<  QString::fromLocal8Bit("请求错误：")<<reply->errorString();
        QPixmap pixmap("://images/user/default_woman00.png");//默认图标
        ui->label_head->setPixmap_(pixmap);
        ui->label_head->setScaledContents(true);
    }
}

void HeadHover::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->hide();
}
