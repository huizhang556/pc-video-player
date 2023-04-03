#include "MainNotice.h"
#include "ui_MainNotice.h"
//#include "facebread/myemotionwindow.h"

MainNotice* MainNotice::m_pInstance = nullptr;

MainNotice::MainNotice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainNotice)
{
    ui->setupUi(this);
    setFixedSize(400,1000);
    setAttribute(Qt::WA_NoMouseReplay);
    setFocusPolicy(Qt::NoFocus);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
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
//    qRegisterMetaType<QVariant>("QVariant");    
    ui->lineEdit_send->setPlaceholderText(QString(u8"按回车键(enter)发送消息~~~"));
    ui->pushButton_menu->setFixedSize(36,36);
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

    slot_addAboutUserMessages(MSGTYPE::MSG_SYS);//系统消息
    slot_addAboutUserMessages(MSGTYPE::MSG_NOR);//一般消息
    slot_addAboutUserMessages(MSGTYPE::MSG_REPLY);//回复消息
    slot_addAboutUserMessages(MSGTYPE::MSG_ABOUT);//@消息
    slot_addAboutUserMessages(MSGTYPE::MSG_LIKE);//点赞消息
}

void MainNotice::handleSignalsAndSlots()
{
    connect(m_buttonGroup1,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
//        qDebug() << button->text()<<button->objectName();
        button->setChecked(true);
        switchStackPageof_notice(button);
    });

    //消息设置---右键菜单
    connect(ui->pushButton_menu,&QPushButton::clicked,[=](){
        createSettingRmenu();
    });

//    connect(ui->lineEdit_send,&QLineEdit::textChanged,[=](const QString &content){
//        if(content.trimmed().isEmpty())
//            ui->pushButton_send_picture->setDisabled(true);
//        else
//            ui->pushButton_send_picture->setDisabled(false);
//    });

    //发送文本
    connect(ui->lineEdit_send,&QLineEdit::returnPressed,[=](){
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


    //发送表情
    connect(ui->pushButton_send_emoj,&QPushButton::clicked,[=](){
        const int x = ui->pushButton_send_emoj->parentWidget()->mapToGlobal(ui->pushButton_send_emoj->pos()).x();
        const int y = ui->pushButton_send_emoj->parentWidget()->mapToGlobal(ui->pushButton_send_emoj->pos()).y();
//            MyEmotionWindow *w1 = new MyEmotionWindow();
//            w1->showNormalEmotion(QPoint(x - w1->width() , y - w1->height()));
    });

    //发送图片
    connect(ui->pushButton_send_picture,&QPushButton::clicked,[=](){
        QStringList list =  QFileDialog::getOpenFileNames(this,//不指定父窗口，设置自己的样式
                                                     QString::fromLocal8Bit("选择文件"),
                                                     QString::fromLocal8Bit("/"),
                                                     QString::fromLocal8Bit("Images(*png *jpeg *gif)")
                                                     );

        QString datatime = QDateTime::currentDateTime().toString("MM-dd hh:mm");
        foreach (auto var, list) {
            switchToDetailMessage(NOTICETYPE::NOTICE_R,//己方消息
                                  QString(u8""),//头像
                                  datatime,//时间
                                  imgPathToHtml(var));//内容（图像）
        }
        ui->listWidget_details->scrollToBottom();//滚到最底部
        ui->lineEdit_send->clear();
    });

    connect(ui->pushButton_setting,&QPushButton::clicked,[=](){
        emit sig_sendSetting();
    });
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
        for(int i = 0; i < 1; i++)
        {
            CusItemMsg *itemWidget = new CusItemMsg(QString(u8":/images/bgpic/dieji.png"),
                                                    QString(u8"系统消息%1").arg(i+1),
                                                    QString(u8"从零基础学习UI设计，平面设计，更多资料，请联系作者"),
                                                    QString(u8"11月%1日").arg(i+1),
                                                    false);
            QListWidgetItem *item = new QListWidgetItem();
            item->setData(Qt::UserRole,QString(u8"系统消息%1").arg(i+1));
            item->setSizeHint(itemWidget->size());
            ui->listWidget_chat->addItem(item);
            ui->listWidget_chat->setItemWidget(item,itemWidget);
            msgCount[0]++;//系统消息+1
            //信号与槽函数
            connect(itemWidget,&CusItemMsg::sig_sendClicked,[=](){
                switchToDetailMessageList(NOTICETYPE::NOTICE_SYS,item->data(Qt::UserRole).toString());
                msgCount[0]--;//系统消息-1
//                ui->pushButton_chat->setText(QString(u8"聊天列表(%1)").arg(msgCount[0]));
            });
        }
//        ui->pushButton_chat->setText(QString(u8"聊天列表(%1)").arg(msgCount[0]));
    }
        break;
    case MSG_NOR://普通消息
    {
        for(int i = 0; i < 10; i++)
        {
            CusItemMsg *itemWidget = new CusItemMsg(QString(u8":/images/bgpic/dieji.png"),
                                                    QString(u8"普通消息%1").arg(i+1),
                                                    QString(u8"从零基础学习UI设计，平面设计，更多资料，请联系作者"),
                                                    QString(u8"11月%1日").arg(i+1),
                                                    false);
            QListWidgetItem *item = new QListWidgetItem();
            //item data 需要到时候请求查询，此处做假数据
            MSGBODY mbody;
            mbody.type = MSGTYPE::MSG_NOR;
            mbody.header = QString(u8":/images/bgpic/dieji.png");
            mbody.title = QString(u8"普通消息%1").arg(i+1);
            mbody.content = QString(u8"从零基础学习UI设计，平面设计，更多资料，请联系作者");
            mbody.date = QString(u8"11月%1日").arg(i+1);
            mbody.isTop = false;
            mbody.isDisturb = false;
            mbody.isPush = false;
            mbody.isBackList = false;
            QVariant var1;
            var1.setValue(mbody);
            item->setData(Qt::UserRole,var1);

            item->setSizeHint(itemWidget->size());
            ui->listWidget_chat->addItem(item);
            ui->listWidget_chat->setItemWidget(item,itemWidget);
            msgCount[0]++;//非系统消息+1
            //信号与槽函数（进入某一个详细的item）
            connect(itemWidget,&CusItemMsg::sig_sendClicked,[=](){
                switchToDetailMessageList(NOTICETYPE::NOTICE_R,mbody.title);
                ui->listWidget_chat->setCurrentItem(item);
                msgCount[0]--;//系统消息-1
//                ui->pushButton_chat->setText(QString(u8"聊天列表(%1)").arg(msgCount[0]));
            });
            //用户置顶（广播所有item可以实现倒序！！！）
//            connect(this,&MainNotice::sig_item_scroll_top,[=](){
//                qDebug() << QString(u8"收到置顶消息");
//                QListWidgetItem *item2 = new QListWidgetItem();
//                item2->setSizeHint(itemWidget->size());
//                ui->listWidget_chat->insertItem(0,item2);//头插入
//                ui->listWidget_chat->setItemWidget(item2,itemWidget);
//                delete item;//最后再删除
//                ui->listWidget_chat->scrollToItem(item,QAbstractItemView::PositionAtTop);
//            });
        }
//        ui->pushButton_chat->setText(QString(u8"聊天列表(%1)").arg(msgCount[0]));
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
            msgCount[1]++;//回复消息+1
            //信号与槽函数
            connect(itemWidget,&CusItemMsg::sig_sendDelete,[=](){
                itemWidget->deleteLater();
                ui->listWidget_reply->takeItem(ui->listWidget_reply->row(item));
                delete item;
                msgCount[1]--;//回复消息-1
//                ui->pushButton_reply->setText(QString(u8"回复我的(%1)").arg(msgCount[1]));
            });
            //阅读消息
            connect(itemWidget,&CusItemMsg::sig_read_reply,[=](){
                msgCount[1]--;//回复消息-1
//                ui->pushButton_reply->setText(QString(u8"回复我的(%1)").arg(msgCount[1]));
            });
        }
//        ui->pushButton_reply->setText(QString(u8"回复我的(%1)").arg(msgCount[1]));
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
            msgCount[2]++;//@我的消息+1

            //阅读消息
            connect(itemWidget,&CusItemMsg::sig_read_about,[=](){
                msgCount[2]--;//@消息-1
//                ui->pushButton_focus->setText(QString(u8"@我的(%1)").arg(msgCount[2]));
            });
        }
//        ui->pushButton_focus->setText(QString(u8"@我的(%1)").arg(msgCount[2]));
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
            msgCount[3]++;//点赞消息+1

            //阅读消息
            connect(itemWidget,&CusItemMsg::sig_read_like,[=](){
                msgCount[3]--;//点赞消息-1
//                ui->pushButton_like->setText(QString(u8"收到的赞(%1)").arg(msgCount[3]));
            });
        }
//        ui->pushButton_like->setText(QString(u8"收到的赞(%1)").arg(msgCount[3]));
    }
        break;
    default:
        break;
    }
}

void MainNotice::slot_message_setTop()
{
    qDebug() <<QString(u8"收到置顶设置");
    QVariant var = ui->listWidget_chat->currentItem()->data(Qt::UserRole);
    MSGBODY mbody = var.value<MSGBODY>();
    mbody.isTop = !mbody.isTop;//取反操作
    //根据标志位设置样式

    qDebug() << mbody.type;
    qDebug() << mbody.header;
    qDebug() << mbody.title;
    qDebug() << mbody.content;
    qDebug() << mbody.date;
    qDebug() << QString(u8"当前4个标志位值：") << endl;
    qDebug() << mbody.isTop << mbody.isDisturb << mbody.isPush <<mbody.isBackList;

    //确定修改
    QVariant var2;
    var2.setValue(mbody);
    QListWidgetItem *item = new QListWidgetItem();
    CusItemMsg *itemWidget = new CusItemMsg(mbody.header,
                                            mbody.title,
                                            mbody.content,
                                            mbody.date,
                                            true);
    item->setData(Qt::UserRole,var2);
    item->setSizeHint(itemWidget->size());
    ui->listWidget_chat->insertItem(0,item);//头插入
    ui->listWidget_chat->setItemWidget(item,itemWidget);
    ui->listWidget_chat->
    //信号与槽函数
    connect(itemWidget,&CusItemMsg::sig_sendClicked,[=](){
        switchToDetailMessageList(NOTICETYPE::NOTICE_R,mbody.title);
        ui->listWidget_chat->setCurrentItem(item);
        itemWidget->setReadStatus(true);

    });

    //根据标志位设置（置顶）样式
    QPushButton *topBtn = getItemButton(item,"pushButton_expand");
    topBtn->setProperty("top",mbody.isTop);
    topBtn->style()->polish(topBtn);

    //根据标志位设置（勿打扰）样式
    QPushButton *disturbBtn = getItemButton(item,"pushButton_disturb");
    disturbBtn->setProperty("disturb",mbody.isDisturb);
    disturbBtn->style()->polish(disturbBtn);

    //考虑插入是否会改变currentItem（）？
    delete  ui->listWidget_chat->itemWidget(ui->listWidget_chat->currentItem());
    delete ui->listWidget_chat->currentItem();//最后再删除
}

void MainNotice::slot_message_donotDisturb()
{
    QVariant var = ui->listWidget_chat->currentItem()->data(Qt::UserRole);
    MSGBODY mbody = var.value<MSGBODY>();
    mbody.isDisturb = !mbody.isDisturb;//取反操作

    QVariant var2;
    var2.setValue(mbody);
    ui->listWidget_chat->currentItem()->setData(Qt::UserRole,var2);
    emit sig_item_disturb();

    //根据标志位设置样式
    QPushButton *curBtn = getItemButton(ui->listWidget_chat->currentItem(),"pushButton_disturb");
    curBtn->setProperty("disturb",mbody.isDisturb);
    curBtn->style()->polish(curBtn);
}

void MainNotice::slot_message_closePush()
{
    QVariant var = ui->listWidget_chat->currentItem()->data(Qt::UserRole);
    MSGBODY mbody = var.value<MSGBODY>();
    mbody.isPush = !mbody.isPush;//取反操作
    QVariant var2;
    var2.setValue(mbody);
    ui->listWidget_chat->currentItem()->setData(Qt::UserRole,var2);
    emit sig_item_closepush();
}

void MainNotice::slot_message_addBlackList()
{
    QVariant var = ui->listWidget_chat->currentItem()->data(Qt::UserRole);
    MSGBODY mbody = var.value<MSGBODY>();
    mbody.isBackList = !mbody.isBackList;//取反操作
    QVariant var2;
    var2.setValue(mbody);
    ui->listWidget_chat->currentItem()->setData(Qt::UserRole,var2);
    emit sig_item_blacklist();
}

void MainNotice::slot_message_clearListContent()
{
    if(ui->listWidget_details->count() != 0)
        ui->listWidget_details->clear();
}

void MainNotice::slot_message_exposeCurUser()
{
    emit sig_item_exposeuser();
}

void MainNotice::createSettingRmenu()
{
    QVariant var = ui->listWidget_chat->currentItem()->data(Qt::UserRole);
    MSGBODY body = var.value<MSGBODY>();
    QMenu m_settingMenu;//加this和不加this位置有区别
    m_settingMenu.setWindowFlag(Qt::FramelessWindowHint);
    m_settingMenu.setAttribute(Qt::WA_TranslucentBackground);
    //在windows下，自带的阴影效果仍然是直角，还需设置去除阴影效果
    m_settingMenu.setWindowFlag(Qt::NoDropShadowWindowHint);

    m_settingMenu.setObjectName(QString::fromUtf8("m_setMenu_notice"));
    if(body.isTop == false)
        m_settingMenu.addAction(QString(u8"置顶"),this,SLOT(slot_message_setTop()));
        else
        m_settingMenu.addAction(QString(u8"取消置顶"),this,SLOT(slot_message_setTop()));

    if(body.isDisturb == false)
        m_settingMenu.addAction(QString(u8"消息免打扰"),this,SLOT(slot_message_donotDisturb()));
        else
        m_settingMenu.addAction(QString(u8"取消免打扰"),this,SLOT(slot_message_donotDisturb()));

    if(body.isPush == false)
        m_settingMenu.addAction(QString(u8"关闭内容推送"),this,SLOT(slot_message_closePush()));
        else
        m_settingMenu.addAction(QString(u8"允许内容推送"),this,SLOT(slot_message_closePush()));

    if(body.isBackList == false)
        m_settingMenu.addAction(QString(u8"加入黑名单"),this,SLOT(slot_message_addBlackList()));
    else
        m_settingMenu.addAction(QString(u8"移出黑名单"),this,SLOT(slot_message_addBlackList()));

    m_settingMenu.addAction(QString(u8"清除会话"),this,SLOT(slot_message_clearListContent()));
    m_settingMenu.addAction(QString(u8"举报该用户"),this,SLOT(slot_message_exposeCurUser()));
    m_settingMenu.setFixedSize(140,170);// 设置了固定size才可以参与计算，否则计算按照推荐size
    const int x = ui->pushButton_menu->parentWidget()->mapToGlobal(ui->pushButton_menu->pos()).x();
    const int y = ui->pushButton_menu->parentWidget()->mapToGlobal(ui->pushButton_menu->pos()).y();
    m_settingMenu.setGeometry(x-m_settingMenu.width()+ui->pushButton_menu->width(),
                              y+ui->pushButton_menu->height(),
                              m_settingMenu.width(),
                              m_settingMenu.height());
    m_settingMenu.exec();
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
                //内容了可以是html
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
    //信号与槽函数
    connect(itemWidget,&CusMessage::sig_item_delete,[=](){
        itemWidget->deleteLater();
        ui->listWidget_details->takeItem(ui->listWidget_details->row(item));
        delete item;
    });
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

QString& MainNotice::imgPathToHtml(QString &path)
{
    path = QString("<img width= %1 height= %2 src=\"%3\"/>").arg(260).arg(100).arg(path);
    return path;
}

QPushButton* MainNotice::getItemButton(QListWidgetItem *item, const QString &objName)
{
    QWidget* itemWidget = ui->listWidget_chat->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QPushButton *itemBtn = itemWidget->findChild<QPushButton*>(objName);//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != itemBtn)
        {
            qDebug() <<QString(u8"找到按钮：%1").arg(objName);
            return itemBtn;
        }
    }
}

