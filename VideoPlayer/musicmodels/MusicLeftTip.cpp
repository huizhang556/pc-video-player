#include "MusicLeftTip.h"
#include "ui_MusicLeftTip.h"
#include "global/Global.h"
#include "musicmodels/FontColor.h"
#include <QScrollBar>
#include <QListWidgetItem>
#include <QDebug>

MusicLeftTip* MusicLeftTip::m_pInstance = nullptr;

MusicLeftTip::MusicLeftTip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicLeftTip)
{
    ui->setupUi(this);
    setFixedSize(200,360);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    initWorkUI();
    handleSinalsAndSlots();
}

MusicLeftTip::~MusicLeftTip()
{
    delete ui;

    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;

}

void MusicLeftTip::initWorkUI()
{
    this->installEventFilter(this);
    ui->listWidget_proSet->setMouseTracking(true);
    ui->listWidget_proSet->setViewMode(QListView::ListMode);
    ui->listWidget_proSet->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_proSet->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_proSet->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
    for(int i = 0; i < songList.count(); i++)
    {
//        QPushButton *itemButton = new QPushButton(songList.at(i));
//        itemButton->setFixedSize(QSize(196,36));
        QListWidgetItem *item = new QListWidgetItem(songList.at(i));
        item->setSizeHint(QSize(198,40));
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//居中显示
        ui->listWidget_proSet->addItem(item);
//        ui->listWidget_proSet->setItemWidget(item,itemButton);
    }
}

void MusicLeftTip::handleSinalsAndSlots()
{
    //关闭应该由本身去做，这里只管发信号
    connect(Global::getInstance(),&Global::sig_sendGlobalTimeOut,[=](){
        QRect rect = QRect(this->geometry().x(),
                           this->geometry().y(),
                           this->width(),
                           this->height());
        if(this && !rect.contains(mapFromGlobal(QCursor::pos())))//存在且不包含
        {
            //保证子菜关闭
            if(FontColor::getInstance()->isHidden())
                MusicLeftTip::getInstance()->hide();
        }
    });

    //鼠标点击(选择)
    connect(ui->listWidget_proSet,&QListWidget::itemClicked,[=](QListWidgetItem* item){
        if(item->text() == QString(u8"关闭歌词"))
        {
            emit sig_lyric_show(false);
            item->setText(u8"显示歌词");
        }
        else if(item->text() == QString(u8"显示歌词"))
        {
            emit sig_lyric_show(true);
            item->setText(u8"关闭歌词");
        }
        else if(item->text() == QString(u8"推荐评论"))
        {

        }
        else if(item->text() == QString(u8"MV"))
        {

        }
        else if(item->text() == QString(u8"动态频谱"))
        {

        }
        else if(item->text() == QString(u8"搜索歌词"))
        {

        }
        else if(item->text() == QString(u8"歌词设置"))
        {

        }
        else if(item->text() == QString(u8"固定底栏"))
        {

        }
    });

    //鼠标hover
    connect(ui->listWidget_proSet,&QListWidget::itemEntered,[=](QListWidgetItem* item){
        ui->listWidget_proSet->setCurrentItem(item);
        int x = this->mapToGlobal(this->pos()).x();
        int y = this->mapToGlobal(this->pos()).y();


        if(item->text() == QString(u8"字体颜色"))
        {
            FontColor::getInstance()->setCurrentStackWdtIndex(0);
            FontColor::getInstance()->setFixedSize(180,70);
            FontColor::getInstance()->setGeometry(x+width(),
                                                  y + FontColor::getInstance()->height()+20,
                                                  FontColor::getInstance()->width(),
                                                  FontColor::getInstance()->height());
            FontColor::getInstance()->show();
        }
        else if(item->text() == QString(u8"歌词背景"))
        {
            FontColor::getInstance()->setCurrentStackWdtIndex(1);
            FontColor::getInstance()->setFixedSize(180,40*3);//3个item
            FontColor::getInstance()->setGeometry(x+width(),
                                                  y + FontColor::getInstance()->height()-40,
                                                  FontColor::getInstance()->width(),
                                                  FontColor::getInstance()->height());
            FontColor::getInstance()->show();
        }
        else if(item->text() == QString(u8"动态频谱"))
        {
            FontColor::getInstance()->setCurrentStackWdtIndex(2);
            FontColor::getInstance()->setFixedSize(180,40*4);//4个item
            FontColor::getInstance()->setGeometry(x+width(),
                                                  y + FontColor::getInstance()->height()-120,
                                                  FontColor::getInstance()->width(),
                                                  FontColor::getInstance()->height());
            FontColor::getInstance()->show();
        }
        else
        {
            if(!FontColor::getInstance()->isHidden())
                FontColor::getInstance()->close();
        }
    });

    //item改变
    connect(ui->listWidget_proSet,&QListWidget::currentItemChanged,[=](QListWidgetItem *current, QListWidgetItem *previous){
        if(!FontColor::getInstance()->isHidden())
            FontColor::getInstance()->close();
    });
}

MusicLeftTip *MusicLeftTip::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new MusicLeftTip();
    }
    return m_pInstance;
}

bool MusicLeftTip::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this &&event->type() == QEvent::HoverLeave)
    {
        if(!FontColor::getInstance()->isHidden())
            FontColor::getInstance()->close();
    }
    return QWidget::eventFilter(watched,event);
}

void MusicLeftTip::slot_switchBgPicture_songer()
{
    qDebug() << QString(u8"歌手写真");
}

void MusicLeftTip::slot_switchBgPicture_skin()
{
    qDebug() << QString(u8"酷我皮肤");
}

void MusicLeftTip::slot_switchBgPicture_localPic()
{
    qDebug() << QString(u8"本地图片");
}
