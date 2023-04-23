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
    ui->listWidget_recommend->setViewMode(QListView::ListMode);
    ui->listWidget_recommend->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_recommend->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void RecomVideoTab::handleSignalsAndSLots()
{
    //开关（连续推送）
    connect(ui->Btn_turn,&QPushButton::clicked,[=](){
        slots_switchTurn();

    });
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
            m_fid = current->data(Qt::UserRole+1).toInt();
            qDebug() << QString(u8"当前推荐列表正在播放的文件的ID:") << m_fid;
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
    item->setData(Qt::UserRole+1,data.id);//id
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
        query.addQueryItem(u8"id",QString::number(data.id));
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
bool RecomVideoTab::slot_addRecVideoItem(int id,QString url, QString path, QString time, QString info, QString count)
{
    RecVideoItem *videoItem = new RecVideoItem(url,path,time,info,count);
    QListWidgetItem *item = new QListWidgetItem(url);
    item->setSizeHint(videoItem->size());//留出来1px的边框
    item->setData(Qt::UserRole,info);
    item->setData(Qt::UserRole+1,id);//id
    ui->listWidget_recommend->addItem(item);
    ui->listWidget_recommend->setItemWidget(item,videoItem);
    m_tempVideoList.append(url);
    m_tempInfoList.append(info);
    m_recplayList.append(url);

    //信号与槽函数
    connect(videoItem,&RecVideoItem::sig_sendVideoUrl,[=](){
        QUrlQuery query;
        query.addQueryItem(u8"id",QString::number(id));
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
    ui->listWidget_recommend->setCurrentItem(ui->listWidget_recommend->item(ui->listWidget_recommend->currentRow()));
}

int RecomVideoTab::slot_getCurrentItemMedia_ID()
{
    return m_fid;
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
    emit sig_sendPlayMode(m_turnOnStatus);//向外发送当前是否连播
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

