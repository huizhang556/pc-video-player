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

    ui->tabWidget->setCurrentWidget(ui->tab_history);
    ui->stackedWidget->setCurrentWidget(ui->page_otherusr);
    ui->stackedWidget_display->setCurrentWidget(ui->stack_produce);

    //作品列表
    ui->listWidget_produce->setViewMode(QListView::IconMode);
    ui->listWidget_produce->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_produce->setResizeMode(QListWidget::Adjust);
    ui->listWidget_produce->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_produce->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_produce->horizontalScrollBar()->setDisabled(true);
    //专辑列表
    ui->listWidget_zhuanji->setViewMode(QListView::IconMode);
    ui->listWidget_zhuanji->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_zhuanji->setResizeMode(QListWidget::Adjust);
    ui->listWidget_zhuanji->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_zhuanji->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_zhuanji->horizontalScrollBar()->setDisabled(true);
    //合集列表
    ui->listWidget_heji->setViewMode(QListView::IconMode);
    ui->listWidget_heji->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_heji->setResizeMode(QListWidget::Adjust);
    ui->listWidget_heji->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_heji->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_heji->horizontalScrollBar()->setDisabled(true);

    ui->toolButton_blank->setIcon(QIcon(":/images/bgpic/nothing.png"));
    ui->toolButton_blank->setIconSize(QSize(200,200));
    ui->toolButton_blank->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->pushButton_usrLevel->setIconSize(QSize(ui->pushButton_usrLevel->size()));

    m_stackBtnGroup = new QButtonGroup(this);
    m_stackBtnGroup->setExclusive(true);
    m_stackBtnGroup->addButton(ui->pushButton_produce,0);
    m_stackBtnGroup->addButton(ui->pushButton_album,1);
    m_stackBtnGroup->addButton(ui->pushButton_group,2);
    m_stackBtnGroup->addButton(ui->pushButton_dongtai,3);

    for(int i = 0; i < 4; i++)
    {
        m_stackBtnGroup->button(i)->setCheckable(true);
    }
    m_stackBtnGroup->button(0)->setChecked(true);
    ui->pushButton_return->hide();


}

void PersonFileForm::chandleSignalsAndSLots()
{
    //按钮选择
    connect(m_stackBtnGroup,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton *button){
        qDebug() << button->text();
        ui->pushButton_return->hide();
    });

    //获取所有作品
    connect(ui->pushButton_produce,&QPushButton::clicked,this,&PersonFileForm::slot_get_user_produces);

    //获取所有专辑
    connect(ui->pushButton_album,&QPushButton::clicked,this,&PersonFileForm::slot_get_user_albums);

    //获取所有合集
    connect(ui->pushButton_group,&QPushButton::clicked,this,&PersonFileForm::slot_get_user_groups);

    //获取所有动态
    connect(ui->pushButton_dongtai,&QPushButton::clicked,this,&PersonFileForm::slot_get_user_activities);

    //返回
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){
        if(ui->pushButton_return->text() == QString(u8"返回专辑列表"))
        {
            slot_get_user_albums();
            ui->pushButton_return->hide();
        }
        else if(ui->pushButton_return->text() == QString(u8"返回合集列表"))
        {
            slot_get_user_groups();
            ui->pushButton_return->hide();
        }
        else
        {
           qDebug(u8"返回按钮的其他情况！~~~");
        }
    });

    //网络请求头像
    connect(m_manager,&QNetworkAccessManager::finished,this,&PersonFileForm::slot_receivedUserHeader,Qt::UniqueConnection);


    //own user tab changed
    connect(ui->tabWidget,&QTabWidget::tabBarClicked,[=](int index){
        qDebug() << QString(u8"own user current tab text: ") << ui->tabWidget->tabText(index);

    });

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
void PersonFileForm::slot_setShowCurrentWidget(QObject *obj1, int index1, QObject *obj2, int index2)
{

}

/*重载槽函数2：*/
void PersonFileForm::slot_setShowCurrentWidget(QObject *obj1, QWidget *wdgt1, QObject *obj2, QWidget *wdgt2)
{

}

//获取所有作品
void PersonFileForm::slot_get_user_produces()
{
    //0.数据库请求
    QList<QVariant> list_var = dataBase::getInstance()->creator_getCurUserAllDramas(m_userId);

    //1.对情况进行判断
    if(list_var.count() == 0)
    {
        setBlankMessage(ui->stack_blank,QString(u8"该用户当前没有作品！"));
        return;
    }

    //2.加载所有作品
    setBlankMessage(ui->stack_blank,QString(u8"正在加载作品~~~"));
    slot_loading_produces(list_var);
    ui->stackedWidget_display->setCurrentWidget(ui->stack_produce);
}

//获取所有专辑
void PersonFileForm::slot_get_user_albums()
{

    //0.数据库请求
    QList<QUrlQuery> list_querys = dataBase::getInstance()->creator_getCurUserAllAlbums(m_userId);
    //1.对情况进行判断
    if(list_querys.count() == 0)
    {
        setBlankMessage(ui->stack_blank,QString(u8"该用户当前没有专辑！"));
        return;
    }
    else
    {
        ui->listWidget_zhuanji->clear();
    }
    //2.加载专辑
    setBlankMessage(ui->stack_blank,QString(u8"正在加载专辑~~~"));
    for(int i = 0; i < list_querys.count(); i++)
    {
        slot_loading_albums(GROUPTYPE::G_DISPLAY,list_querys.at(i).queryItemValue(u8"album_name"),list_querys.at(i).queryItemValue(u8"album_pix"),list_querys.at(i).queryItemValue(u8"album_id"));
    }
    ui->stackedWidget_display->setCurrentWidget(ui->stack_zhuanji);
    qDebug("this page is zhuanji");
}

//获取所有合集
void PersonFileForm::slot_get_user_groups()
{
    //0.数据库请求
    QList<QUrlQuery> list_querys = dataBase::getInstance()->creator_getCurUserAllGroups(m_userId);
    //1.对数据进行解析
    if(list_querys.count() == 0)
    {
        setBlankMessage(ui->stack_blank,QString(u8"该用户当前没合集！"));
        return;
    }
    else
    {
        ui->listWidget_heji->clear();
    }
    //2.加载合集
    setBlankMessage(ui->stack_blank,QString(u8"正在加载合集~~~"));
    for(int i = 0; i < list_querys.count(); i++)
    {

        slot_loading_collections(GROUPTYPE::G_DISPLAY,list_querys.at(i).queryItemValue(u8"group_name"),list_querys.at(i).queryItemValue(u8"group_pix"),list_querys.at(i).queryItemValue(u8"group_id"));
    }
    ui->stackedWidget_display->setCurrentWidget(ui->stack_heji);
    qDebug("this page is collections");
}

//获取所有动态
void PersonFileForm::slot_get_user_activities()
{
    ui->stackedWidget_display->setCurrentWidget(ui->stack_dongtai);
    setBlankMessage(ui->stack_blank,QString(u8"该用户暂无动态！"));
    qDebug("this page is activities");
}

//返回标志
void PersonFileForm::slot_get_user_return()
{
    qDebug("return page");
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

void PersonFileForm::setBlankMessage(QWidget *page, const QString &message)
{
    ui->stackedWidget_display->setCurrentWidget(page);
    ui->toolButton_blank->setText(message);
}

//加载所有作品
void PersonFileForm::slot_loading_produces(QList<QVariant> &produces)
{
    ui->listWidget_produce->clear();
    for(int i = 0; i < produces.count(); i++)
    {
        fileBody body = produces.at(i).value<fileBody>();
        QListWidgetItem *item = new QListWidgetItem(body.fnick);//介绍
        item->setData(Qt::UserRole,body.furl);
        FilesItem *itemWidget = new FilesItem(FILEEDIT::DISPLAY,body.fid,body.furl,body.fsize,body.fcover);
        itemWidget->initFileItem(body);
        itemWidget->setFixedSize(QSize(200,150));//190,135
        item->setSizeHint(QSize(205,155));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
        ui->listWidget_produce->addItem(item);
        ui->listWidget_produce->setItemWidget(item,itemWidget);

        //播放
        connect(itemWidget,&FilesItem::sig_sendItem_play,[=](){
        QUrlQuery query;
        query.addQueryItem(u8"id",QString::number(body.fid));
        query.addQueryItem(u8"url",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"nick",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"pos","0");
        MultipPlayer::getInstance()->slot_addTempPlaylist(666,QStringList{item->data(Qt::UserRole).toString()},query);
        });
    }
}

//加载所有专辑
void PersonFileForm::slot_loading_albums(GROUPTYPE TYPE, const QString &name, const QString &pix_url, const QString &album_id)
{
    MediaGroup *itemWidget = new MediaGroup(TYPE,album_id,name,pix_url);
    itemWidget->setFixedSize(200,120);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole,album_id);
    item->setSizeHint(itemWidget->size() + QSize(10,10));
    ui->listWidget_zhuanji->addItem(item);
    ui->listWidget_zhuanji->setItemWidget(item,itemWidget);

    //关联信号与槽函数

    //专集点击重新展示专集下的items
    connect(itemWidget,&MediaGroup::sig_item_clicked,[=](){
        ui->pushButton_return->setText(QString(u8"返回专辑列表"));
        ui->pushButton_return->show();
        QList<QVariant>& list_var = dataBase::getInstance()->album_getCurUserOneAlbumAllMedias(album_id);
        if(list_var.count() == 0)
        {
            setBlankMessage(ui->stack_blank,QString(u8"该专辑下当前没有作品！"));
            return;
        }
        setBlankMessage(ui->stack_blank,QString(u8"正在加载专辑作品~~~"));
        slot_loading_album_items(list_var);
        ui->stackedWidget_display->setCurrentWidget(ui->stack_zhuanji);
    });
}

//加载某个专辑下的所有items
void PersonFileForm::slot_loading_album_items(QList<QVariant> &albums)
{
    ui->listWidget_zhuanji->clear();
    for(int i = 0; i < albums.count(); i++)
    {
        fileBody body = albums.at(i).value<fileBody>();
        QListWidgetItem *item = new QListWidgetItem(body.fnick);//介绍
        item->setData(Qt::UserRole,body.furl);
        FilesItem *itemWidget = new FilesItem(FILEEDIT::DISPLAY,body.fid,body.furl,body.fsize,body.fcover);
        itemWidget->initFileItem(body);
        itemWidget->setFixedSize(QSize(200,150));
        item->setSizeHint(QSize(205,155));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
        ui->listWidget_zhuanji->addItem(item);
        ui->listWidget_zhuanji->setItemWidget(item,itemWidget);

        //播放
        connect(itemWidget,&FilesItem::sig_sendItem_play,[=](){
        QUrlQuery query;
        query.addQueryItem(u8"id",QString::number(body.fid));
        query.addQueryItem(u8"url",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"nick",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"pos","0");
        MultipPlayer::getInstance()->slot_addTempPlaylist(666,QStringList{item->data(Qt::UserRole).toString()},query);
        });
    }
}

//加载所有合集
void PersonFileForm::slot_loading_collections(GROUPTYPE TYPE, const QString &name, const QString &pix_url, const QString &group_id)
{
    MediaGroup *itemWidget = new MediaGroup(TYPE,group_id,name,pix_url);
    itemWidget->setFixedSize(200,120);
    QListWidgetItem *item = new QListWidgetItem();
    item->setData(Qt::UserRole,group_id);
    item->setSizeHint(itemWidget->size() + QSize(10,10));
    ui->listWidget_heji->addItem(item);
    ui->listWidget_heji->setItemWidget(item,itemWidget);

    //关联信号与槽函数

    //专集点击重新展示专集下的items
    connect(itemWidget,&MediaGroup::sig_item_clicked,[=](){
        ui->pushButton_return->setText(QString(u8"返回合集列表"));
        ui->pushButton_return->show();
        QList<QVariant>& list_var = dataBase::getInstance()->group_getCurUserOneGroupAllMedias(group_id);
        if(list_var.count() == 0)
        {
            setBlankMessage(ui->stack_blank,QString(u8"该合集下当前没有作品！"));
            return;
        }
        setBlankMessage(ui->stack_blank,QString(u8"正在加载合集视频~~~"));
        slot_loading_collection_items(list_var);
        ui->stackedWidget_display->setCurrentWidget(ui->stack_heji);
    });
}

//加载某个合集下的所有items
void PersonFileForm::slot_loading_collection_items(QList<QVariant> &collections)
{
    ui->listWidget_heji->clear();
    for(int i = 0; i < collections.count(); i++)
    {
        fileBody body = collections.at(i).value<fileBody>();
        QListWidgetItem *item = new QListWidgetItem(body.fnick);//介绍
        item->setData(Qt::UserRole,body.furl);
        FilesItem *itemWidget = new FilesItem(FILEEDIT::DISPLAY,body.fid,body.furl,body.fsize,body.fcover);
        itemWidget->initFileItem(body);
        itemWidget->setFixedSize(QSize(200,150));
        item->setSizeHint(QSize(205,155));
        item->setTextAlignment(Qt::AlignRight | Qt::AlignCenter);
        ui->listWidget_heji->addItem(item);
        ui->listWidget_heji->setItemWidget(item,itemWidget);

        //播放
        connect(itemWidget,&FilesItem::sig_sendItem_play,[=](){
        QUrlQuery query;
        query.addQueryItem(u8"id",QString::number(body.fid));
        query.addQueryItem(u8"url",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"nick",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"pos","0");
        MultipPlayer::getInstance()->slot_addTempPlaylist(666,QStringList{item->data(Qt::UserRole).toString()},query);
        });
    }
}

//加载所有动态
void PersonFileForm::slot_loading_activities(QList<QVariant> &medias)
{

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

QCheckBox *PersonFileForm::getItemCheckedButton(QListWidgetItem *item, const QString &objname)
{
    QWidget* itemWidget = item->listWidget()->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QCheckBox *itemBtn = itemWidget->findChild<QCheckBox*>(objname);//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != itemBtn)
        {
//            qDebug() << QString(u8"找到checkedbox");
            return itemBtn;
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
}

FilesItem *PersonFileForm::getItemWidget(QListWidgetItem *item, const QString &objname)
{
    QWidget* itemWidget = item->listWidget()->itemWidget(item);
    if(nullptr != itemWidget)
    {
//        qDebug() << QString(u8"找到FilesItem");
        return qobject_cast<FilesItem*>(itemWidget);
    }
    else
    {
        return nullptr;
    }
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
                m_userId        =   quer_user.queryItemValue(u8"userid");
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
    ui->stackedWidget_display->setCurrentWidget(ui->stack_produce);
    ui->pushButton_produce->click();//默认加载所有作品
    qDebug() <<QString(u8"当前用id户为：") << userid;
}


