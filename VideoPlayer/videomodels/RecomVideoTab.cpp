#include "RecomVideoTab.h"
#include "ui_RecomVideoTab.h"
#include "global/Global.h"
#include "videomodels/RecVideoItem.h"

#include <QListWidgetItem>
#include <QDebug>

RecomVideoTab::RecomVideoTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecomVideoTab),
    m_turnOnStatus(false)
{
    ui->setupUi(this);
    this->setFixedWidth(260);
    initWorkUI();
    handleSignalsAndSLots();

}

RecomVideoTab::~RecomVideoTab()
{
    delete ui;
}

void RecomVideoTab::initWorkUI()
{
//                  m_tempVideoList
//                  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/tempvideo/temp001.flv")
//                  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/tempvideo/temp002.flv")
//                  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/tempvideo/temp003.flv")
//                  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/tempvideo/temp004.flv")
//                  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/tempvideo/temp005.flv")
//                  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/tempvideo/temp006.flv")
//                  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/tempvideo/temp007.flv")
//                  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/tempvideo/temp008.flv")
//                  <<QString::fromLocal8Bit("http://82.156.175.81:8080/group1/tempvideo/temp009.flv")
//                  <<QString::fromLocal8Bit("http://82.1556.175.81:8080/group1/tempvideo/temp010.flv");

//                  m_tempInfoList
//                  <<QString::fromLocal8Bit("测试视频-剧集列表-赵本山改革春风吹满地，中国人民真争气")
//                  <<QString::fromLocal8Bit("测试视频-剧集列表-中国好声音-谁还能记得，匆匆往事")
//                  <<QString::fromLocal8Bit("测试视频-剧集列表-中国好声音-beyond-海阔天空")
//                  <<QString::fromLocal8Bit("测试视频-剧集列表-中国好声音-面筋哥-波澜不惊")
//                  <<QString::fromLocal8Bit("测试视频-剧集列表-小米-雷军-are you ok?")
//                  <<QString::fromLocal8Bit("测试视频-剧集列表-侯翠翠-团队后面的重要性")
//                  <<QString::fromLocal8Bit("测试视频-剧集列表-侯翠翠-谁拿上班当回事儿")
//                  <<QString::fromLocal8Bit("测试视频-剧集列表-面筋哥-让风儿自由的行走")
//                  <<QString::fromLocal8Bit("测试视频-剧集列表-面筋哥-努力自有回报一切都将会到来")
//                  <<QString::fromLocal8Bit("测试视频-剧集列表-侯翠翠-考什么研还不如躺平");


    ui->listWidget_recommend->setViewMode(QListView::ListMode);
    ui->listWidget_recommend->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_recommend->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    for(int i = 0; i < m_tempVideoList.size(); i++)
//    {
//        QString url     = m_tempVideoList[i];
//        QString path    = Global::appDirPath + QString("/pictures/videos/dramalist/temp_%1.png").arg(i+1);
//        QString time    = QString("11:56:38");
//        QString info    = m_tempInfoList[i];
//        QString count   = QString::fromLocal8Bit("6.%1万").arg(i+1);
//        MusicData musicData;
//        musicData.id        = i;
//        musicData.alias     = info;
//        musicData.url       = url;
//        musicData.duration  = time;
//        musicData.cover     = path;
//        musicData.uplove    = count;
//        QVariant musicVariant;//直接传递结构体也可以，不过有时候解析出来的有问题，最好加上一层壳
//        musicVariant.setValue(musicData);
//        slot_addRecVideoItem(musicVariant);
//        slot_addRecVideoItem(url,path,time,info,count);
//    }
}

void RecomVideoTab::handleSignalsAndSLots()
{
    //开关（连续推送）
    connect(ui->Btn_turn,&QPushButton::clicked,this,&RecomVideoTab::slots_switchTurn);
    //当前项改变（设置样式）
    connect(ui->listWidget_recommend,&QListWidget::currentItemChanged,[=](QListWidgetItem *current,QListWidgetItem *previous)
    {
        if(previous != nullptr)
        {
//            qDebug() << QString::fromLocal8Bit("先前的item：")<<previous->text();
            getListWidgetItemButton(previous,"pushButton_videoInfo")->setChecked(false);
        }
        if(current != nullptr)
        {
//            qDebug() << QString::fromLocal8Bit("现在的item:")<<current->text();
            getListWidgetItemButton(current,"pushButton_videoInfo")->setChecked(true);
        }


//        getListWidgetItemButton(current,"pushButton_videoInfo")->setStyleSheet("#pushButton_videoInfo{color: #ff4335;border:none;background-color:transparent;}");
//        getListWidgetItemButton(previous,"pushButton_videoInfo")->setStyleSheet("#pushButton_videoInfo{color: #e6e9f0;border:none;background-color:transparent;}");
    });
}

QStringList RecomVideoTab::slot_getDramaList()
{
    return m_tempVideoList;
}

void RecomVideoTab::slot_setCurrentVideoPicture(const QString &path)
{
    QPixmap pix(path);
    ui->label_currentPic->setPixmap(pix);
    ui->label_currentPic->setScaledContents(true);
}

//设置视频介绍
void RecomVideoTab::slot_setCurrentVideoInfo(QString info)
{
    ui->pushButton_currentText->setText(info);
}

//重载函数1（添加推荐视频）
bool RecomVideoTab::slot_addRecVideoItem(QVariant& musicVariant)
{
    MusicData data = musicVariant.value<MusicData>();// 通用类型转为专用类型
    RecVideoItem *videoItem = new RecVideoItem(data.url,data.cover,data.duration,data.alias,data.uplove);
    QListWidgetItem *item = new QListWidgetItem(data.url);
    item->setData(Qt::UserRole,data.alias);//介绍
    item->setSizeHint(videoItem->size());//留出来1px的边框
    ui->listWidget_recommend->addItem(item);
    ui->listWidget_recommend->setItemWidget(item,videoItem);
    m_tempVideoList.append(data.url);
    m_tempInfoList.append(data.alias);
    m_recplayList.append(data.url);

    //信号与槽函数
    connect(videoItem,&RecVideoItem::sig_sendVideoUrl,[=](){
//        emit sig_sendVideoUrl(item->text());
        QUrlQuery query;
        query.addQueryItem(u8"url",item->text());
        query.addQueryItem(u8"nick",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"pos",u8"0");
        emit sig_recom_playlist(888,m_recplayList,query);
        ui->listWidget_recommend->setCurrentItem(item);//实现选种样式
        qDebug() <<QString::fromLocal8Bit("已发送临时播放连接url:")<<item->text();
    });
    return true;
}

//重载函数2（添加推荐视频）
bool RecomVideoTab::slot_addRecVideoItem(QString url, QString path, QString time, QString info, QString count)
{
    RecVideoItem *videoItem = new RecVideoItem(url,path,time,info,count);
    QListWidgetItem *item = new QListWidgetItem(url);
    item->setSizeHint(videoItem->size());//留出来1px的边框
    item->setData(Qt::UserRole,info);
    ui->listWidget_recommend->addItem(item);
    ui->listWidget_recommend->setItemWidget(item,videoItem);
    m_tempVideoList.append(url);
    m_tempInfoList.append(info);
    m_recplayList.append(url);

    //信号与槽函数
    connect(videoItem,&RecVideoItem::sig_sendVideoUrl,[=](){
//        emit sig_sendVideoUrl(item->text());
        QUrlQuery query;
        query.addQueryItem(u8"url",item->text());
        query.addQueryItem(u8"nick",item->data(Qt::UserRole).toString());
        query.addQueryItem(u8"pos",u8"0");
        emit sig_recom_playlist(888,m_recplayList,query);
        ui->listWidget_recommend->setCurrentItem(item);//实现选种样式
        qDebug() <<QString::fromLocal8Bit("已发送临时播放连接url:")<<item->text();
    });
    return true;
}

void RecomVideoTab::slot_setListWidgetCurrentIndex(int index)
{
    ui->listWidget_recommend->setCurrentRow(index);
}

void RecomVideoTab::slot_clearRecLists()
{
//    if(ui->listWidget_recommend->count() != 0)
//    ui->listWidget_recommend->clear();
}

void RecomVideoTab::slots_switchTurn()
{
    if(!m_turnOnStatus)
    {
        qDebug() << "!m_turnOnStatus";
        ui->Btn_turn->setStyleSheet("#Btn_turn{"
                                           "border-image: url(:/images/icon/turn_on.png);"
                                           "}");
    }
    else
    {
        qDebug() << "m_turnOnStatus";
        ui->Btn_turn->setStyleSheet("#Btn_turn{"
                                           "border-image: url(:/images/icon/turn_off.png);"
                                           "}");
    }
    m_turnOnStatus = !m_turnOnStatus;
}

QPushButton *RecomVideoTab::getListWidgetItemButton(QListWidgetItem* item, QString objname)
{
    QWidget* itemWidget = ui->listWidget_recommend->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QPushButton *itemBtn = itemWidget->findChild<QPushButton*>(objname);//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != itemBtn)
        return itemBtn;
    }
}

