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

    QListWidgetItem *item1 = new QListWidgetItem(QIcon("://images/user/user_zhuye.png"),QString::fromLocal8Bit("个人主页"));
    QListWidgetItem *item2 = new QListWidgetItem(QIcon("://images/user/user_vipcenter.png"),QString::fromLocal8Bit("会员中心"));
    QListWidgetItem *item3 = new QListWidgetItem(QIcon("://images/user/user_songlist.png"),QString::fromLocal8Bit("还原歌单"));
    QListWidgetItem *item4 = new QListWidgetItem(QIcon("://images/user/user_changepwd.png"),QString::fromLocal8Bit("修改密码"));
    QListWidgetItem *item5 = new QListWidgetItem(QIcon("://images/user/user_exit.png"),QString::fromLocal8Bit("退出登录"));
    ui->listWidget_menu->addItem(item1);
    ui->listWidget_menu->addItem(item2);
    ui->listWidget_menu->addItem(item3);
    ui->listWidget_menu->addItem(item4);
    ui->listWidget_menu->addItem(item5);

    slots_setUserIcon(1);

    //遮罩
    QRegion maskRegion(ui->label_head->rect(),QRegion::Ellipse);//创建圆形遮罩
    ui->label_head->setMask(maskRegion);//设置圆形遮罩
}

void HeadHover::handleSignalsAndSlots()
{
    connect(ui->listWidget_menu,&QListWidget::itemClicked,[=](QListWidgetItem *item){
        emit sig_itemChanged(item->text());
        this->hide();
    });
}

//设置个人信息
void HeadHover::slot_setCurrentUserInfo(const QString &head="", const QString &nick=QString::fromLocal8Bit("新用户"), int grade = 1, const QString &info=QString::fromLocal8Bit("快点听歌去吧^_^"))
{
    slots_setUserHead(head);
    slots_setUserName(nick);
    slots_setUserIcon(grade);
    slot_setUserInfo(info);
}

void HeadHover::slots_setUserHead(const QString &head)
{

    m_manager->get(QNetworkRequest(QUrl(head)));
    connect(m_manager,&QNetworkAccessManager::finished,[=](QNetworkReply *reply){
        if (reply->error() == QNetworkReply::NoError)
        {
            //获取字节流构造 QPixmap 对象
            m_headPixmap.loadFromData(reply->readAll());
            ui->label_head->setPixmap(m_headPixmap);
            ui->label_head->setScaledContents(true);
        }
        else//请求失败，加载默认图片
        {
            qDebug() <<  QString::fromLocal8Bit("请求错误：")<<reply->errorString();
            QPixmap pixmap("://images/user/default_woman00.png");//默认图标
            ui->label_head->setPixmap(pixmap);
            ui->label_head->setScaledContents(true);
        }
    });
}

void HeadHover::slots_setUserName(const QString& nick)
{
    QFont font;
    font.setPixelSize(13);
    QFontMetrics   fontMetric = QFontMetrics(font);
    QString text = fontMetric.elidedText(nick,Qt::ElideRight,100,0);//19个字宽以后，省略为...(10x19，字号x字数)
    ui->pushButton_userName->setText(text);
    ui->pushButton_userName->setToolTip(nick);
    ui->pushButton_userName->setText(nick);
}

void HeadHover::slots_setUserIcon(int grade)
{
//    ui->pushButton_userName->setLayoutDirection(Qt::RightToLeft);//图标放在右侧
    switch (grade)
    {
    case 0:
        ui->pushButton_userName->setIcon(QIcon("://images/user/user_visitor.png"));
        break;
    case 1:
        ui->pushButton_userName->setIcon(QIcon("://images/user/user_vip.png"));
        break;
    case 2:
        ui->pushButton_userName->setIcon(QIcon("://images/user/user_suvip.png"));
        break;
    case 3:
        ui->pushButton_userName->setIcon(QIcon("://images/user/user_ssvip.png"));
        break;
    default:
        ui->pushButton_userName->setIcon(QIcon("://images/user/user_vipcenter.png"));
        break;
    }
}

void HeadHover::slot_setUserInfo(const QString &info)
{
    ui->pushButton_otherInfo->setText(info);
}

void HeadHover::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->hide();
}
