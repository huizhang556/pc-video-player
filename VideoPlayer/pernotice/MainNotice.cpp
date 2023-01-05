#include "MainNotice.h"
#include "ui_MainNotice.h"

MainNotice* MainNotice::m_pInstance = nullptr;

MainNotice::MainNotice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainNotice)
{
    ui->setupUi(this);
    setFixedSize(400,1000);
    setAttribute(Qt::WA_NoMouseReplay);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool |Qt::WindowStaysOnTopHint | Qt::Popup);
    initWorkUI();
    handleSignalsAndSlots();
}

MainNotice::~MainNotice()
{
    delete ui;
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void MainNotice::initWorkUI()
{
    m_buttonGroup1 = new QButtonGroup(this);
    m_buttonGroup1->setExclusive(true);
    ui->pushButton_chat->setCheckable(true);
    ui->pushButton_chat->setChecked(true);
    ui->pushButton_reply->setCheckable(true);
    ui->pushButton_focus->setCheckable(true);
    ui->pushButton_like->setCheckable(true);
    m_buttonGroup1->addButton(ui->pushButton_chat,0);
    m_buttonGroup1->addButton(ui->pushButton_reply,1);
    m_buttonGroup1->addButton(ui->pushButton_focus,2);
    m_buttonGroup1->addButton(ui->pushButton_like,3);
    ui->stackedWidget_switch->setCurrentWidget(ui->page_switch_allmessage);
    ui->stackedWidget_notice->setCurrentWidget(ui->stackedWidget_noticePage1);

    ui->listWidget_chat->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_reply->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_focus->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_like->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_details->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_chat->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_reply->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_focus->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_like->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_details->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    slot_addAboutUserMessages(MSGTYPE::MSG_SYS);
    slot_addAboutUserMessages(MSGTYPE::MSG_NOR);
    slot_addAboutUserMessages(MSGTYPE::MSG_REPLY);
    slot_addAboutUserMessages(MSGTYPE::MSG_ABOUT);
    slot_addAboutUserMessages(MSGTYPE::MSG_LIKE);

}

void MainNotice::handleSignalsAndSlots()
{
    connect(m_buttonGroup1,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        qDebug() << button->text()<<button->objectName();
        button->setChecked(true);
        switchStackPageof_notice(button);
    });

    connect(ui->lineEdit_send,&QLineEdit::textChanged,[=](const QString &content){
        if(content.trimmed().isEmpty())
            ui->pushButton_send->setDisabled(true);
        else
            ui->pushButton_send->setDisabled(false);
    });

    connect(ui->lineEdit_send,&QLineEdit::returnPressed,[=](){
        ui->pushButton_send->click();
    });

    connect(ui->pushButton_send,&QPushButton::clicked,[=](){
        QString content = ui->lineEdit_send->text().trimmed();
        QString datatime = QDateTime::currentDateTime().toString("MM-dd hh:mm");
        if(!content.isEmpty())
        {
            switchToDetailMessage(NOTICETYPE::NOTICE_R,
                                  QString(u8""),
                                  datatime,
                                  content);
        }
        ui->listWidget_details->scrollToBottom();//滚到最底部
        ui->lineEdit_send->clear();
    });

    connect(ui->pushButton_setting,&QPushButton::clicked,[=](){ui->stackedWidget_switch->setCurrentWidget(ui->page_switch_details);});
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){
        ui->stackedWidget_switch->setCurrentWidget(ui->page_switch_allmessage);
        ui->listWidget_details->clear();
    });
}

MainNotice *MainNotice::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new MainNotice();
    }
    return m_pInstance;
}

void MainNotice::slot_addAboutUserMessages(MSGTYPE type)
{
    switch (type) {
    case MSG_SYS://系统消息
    {
        for(int i = 0; i < 10; i++)
        {
            CusItemMsg *itemWidget = new CusItemMsg(QString(u8":/images/bgpic/dieji.png"),
                                                    QString(u8"系统消息%1").arg(i+1),
                                                    QString(u8"从零基础学习UI设计，平面设计，更多资料，请联系作者"),
                                                    QString(u8"11月%1日").arg(i+1));
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(Qt::UserRole,QString(u8"系统消息%1").arg(i+1));
            item->setSizeHint(itemWidget->size());
            ui->listWidget_chat->addItem(item);
            ui->listWidget_chat->setItemWidget(item,itemWidget);
            //信号与槽函数
            connect(itemWidget,&CusItemMsg::sig_sendClicked,[=](){
                switchToDetailMessageList(NOTICETYPE::NOTICE_SYS,item->data(Qt::UserRole).toString());
            });
        }
    }
        break;
    case MSG_NOR://普通消息
    {
        for(int i = 0; i < 10; i++)
        {
            CusItemMsg *itemWidget = new CusItemMsg(QString(u8":/images/bgpic/dieji.png"),
                                                    QString(u8"普通消息%1").arg(i+1),
                                                    QString(u8"从零基础学习UI设计，平面设计，更多资料，请联系作者"),
                                                    QString(u8"11月%1日").arg(i+1));
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(Qt::UserRole,QString(u8"普通消息%1").arg(i+1));
            item->setSizeHint(itemWidget->size());
            ui->listWidget_chat->addItem(item);
            ui->listWidget_chat->setItemWidget(item,itemWidget);
            //信号与槽函数
            connect(itemWidget,&CusItemMsg::sig_sendClicked,[=](){
                switchToDetailMessageList(NOTICETYPE::NOTICE_R,item->data(Qt::UserRole).toString());
            });
        }
    }
        break;
    case MSG_REPLY://回复我的消息
    {
        for(int i = 0; i < 20; i++)
        {
            CusItemMsg *itemWidget = new CusItemMsg(QString(u8":/images/bgpic/dieji2.png"),
                                                    QString(u8"回复我的消息%1").arg(i+1),
                                                    QString(u8"嗯嗯，谢谢，你的建议很值得借鉴，我会下次采纳你的建议的~~~"),
                                                    QString(u8"QT模仿酷我音乐高仿程序"),
                                                    QString(u8"10月%1日").arg(i+1));
            QListWidgetItem *item = new QListWidgetItem();
            item->setSizeHint(itemWidget->size());
            ui->listWidget_reply->addItem(item);
            ui->listWidget_reply->setItemWidget(item,itemWidget);
        }
    }
        break;
    case MSG_ABOUT://@我的消息
    {
        for(int i = 0; i < 20; i++)
        {
            QStringList nameList = {QString(u8"小蜜蜂"),QString(u8"海盗"),QString(u8"风一样")};
            CusItemMsg *itemWidget = new CusItemMsg(QString(u8":/images/bgpic/dieji2.png"),
                                                    nameList,
                                                    QString(u8"QT模仿酷我音乐高仿程序"),
                                                    QString(u8"9月%1日").arg(i+1));
            QListWidgetItem *item = new QListWidgetItem();
            item->setSizeHint(itemWidget->size());
            ui->listWidget_focus->addItem(item);
            ui->listWidget_focus->setItemWidget(item,itemWidget);
        }
    }
        break;
    case MSG_LIKE://点赞我的消息
    {
        for(int i = 0; i < 20; i++)
        {
            QStringList nameList = {QString(u8"小黄蜂"),QString(u8"海军1号"),QString(u8"特种部队")};
            CusItemMsg *itemWidget = new CusItemMsg(QString(u8":/images/bgpic/dieji3.png"),
                                                    nameList,
                                                    QString(u8"QT模仿酷我音乐高仿程序"),
                                                    QString(u8"9月%1日").arg(i+1));
            QListWidgetItem *item = new QListWidgetItem();
            item->setSizeHint(itemWidget->size());
            ui->listWidget_like->addItem(item);
            ui->listWidget_like->setItemWidget(item,itemWidget);
        }
    }
        break;
    default:
        break;
    }
}

void MainNotice::switchStackPageof_notice(QAbstractButton *button)
{
    if(!button->text().isEmpty())
    {
        if(button->objectName() == QString(u8"pushButton_chat"))
        {
            ui->stackedWidget_notice->setCurrentWidget(ui->stackedWidget_noticePage1);
        }
        else if(button->objectName() == QString(u8"pushButton_reply"))
        {
            ui->stackedWidget_notice->setCurrentWidget(ui->stackedWidget_noticePage2);
        }
        else if(button->objectName() == QString(u8"pushButton_focus"))
        {
            ui->stackedWidget_notice->setCurrentWidget(ui->stackedWidget_noticePage3);
        }
        else if(button->objectName() == QString(u8"pushButton_like"))
        {
            ui->stackedWidget_notice->setCurrentWidget(ui->stackedWidget_noticePage4);
        }
    }
}

void MainNotice::switchToDetailMessageList(NOTICETYPE type, const QString &authorName)
{
    ui->stackedWidget_switch->setCurrentWidget(ui->page_switch_details);
    ui->pushButton_name->setText(authorName);
    ui->listWidget_details->clear();
    switch (type) {
    case NOTICE_SYS:
    {
        ui->pushButton_menu->hide();
        ui->frame_send->hide();
            for(int i = 0; i < 10; i++)
            {
                switchToDetailMessage(QString(u8"国庆双旦，欢乐来袭！双重大奖等你来领~~"),
                                      QString(u8"12月12日"),
                                      QString(u8"庆双旦，欢乐来袭！好礼送不停！快来抢购吧！庆双旦，欢乐来袭！好礼送不停！快来抢购吧！庆双旦，欢乐来袭！好礼送不停！快来抢购吧！庆双旦，欢乐来袭！好礼送不停！快来抢购吧！庆双旦，欢乐来袭！好礼送不停！快来抢购吧！"));
            }
    }
        break;
    case NOTICE_L:
    {
        ui->pushButton_menu->show();
        ui->frame_send->show();
        for(int i = 0; i < 10; i++)
        {
            if(array[i] == true)
            switchToDetailMessage(NOTICETYPE::NOTICE_L,
                                  QString(u8"庆双旦，欢乐来袭！"),
                                  QString(u8"12月12日"),
                                  QString(u8"好礼送不停！快来抢购吧！庆双旦，欢乐来袭！好礼送不停！快来抢购吧！"));
            else
            switchToDetailMessage(NOTICETYPE::NOTICE_R,
                                  QString(u8"过大年，欢乐来袭！"),
                                  QString(u8"12月12日"),
                                  QString(u8"好礼送不停！快来抢购吧！庆双旦，欢乐来袭！好礼送不停！快来抢购吧！！"));
        }
    }
        break;
    case NOTICE_R:
    {
        ui->pushButton_menu->show();
        ui->frame_send->show();
        for(int i = 0; i < 10; i++)
        {
            if(array[i] == true)
            switchToDetailMessage(NOTICETYPE::NOTICE_L,
                                  QString(u8"庆双旦，欢乐来袭！"),
                                  QString(u8"12月12日"),
                                  QString(u8"好礼送不停！快来抢购吧！庆双旦，欢乐来袭！好礼送不停！快来抢购吧！庆双旦，欢乐来袭！好礼送不停！快来抢购吧！"));
            else
            switchToDetailMessage(NOTICETYPE::NOTICE_R,
                                  QString(u8"过大年，欢乐来袭！"),
                                  QString(u8"12月12日"),
                                  QString(u8"好礼送不停！快来抢购吧！庆双旦，欢乐来袭！好礼送不停！快来抢购吧！庆双旦，欢乐来袭！好礼送不停！快来抢购吧！！"));
        }
    }
        break;
    default:
        break;
    }
}

void MainNotice::switchToDetailMessage(const QString &title, const QString &datatime, const QString &content)
{
    CusMessage *itemWidget = new CusMessage(title,datatime,content);
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(itemWidget->size()+QSize(0,40));
    ui->listWidget_details->addItem(item);
    ui->listWidget_details->setItemWidget(item,itemWidget);
}

void MainNotice::switchToDetailMessage(NOTICETYPE type, const QString &header, const QString &datatime, const QString &content)
{
    switch (type) {
    case NOTICE_L:
    {
        CusMessage *itemWidget = new CusMessage(NEWSTYPE::NEWS_LEFT,
                                                header,
                                                datatime,
                                                content);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size()+QSize(0,40));
        ui->listWidget_details->addItem(item);
        ui->listWidget_details->setItemWidget(item,itemWidget);
    }
        break;
    case NOTICE_R:
    {
        CusMessage *itemWidget = new CusMessage(NEWSTYPE::NEWS_RIGHT,
                                                header,
                                                datatime,
                                                content);
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(itemWidget->size()+QSize(0,40));
        ui->listWidget_details->addItem(item);
        ui->listWidget_details->setItemWidget(item,itemWidget);
    }
        break;
    default:
        break;
    }
}
