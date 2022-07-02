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
    //设置bar四个图标
    ui->tabWidget->tabBar()->setTabIcon(0,QIcon(":/images/icon/his_pic.png"));
    ui->tabWidget->tabBar()->setTabIcon(1,QIcon(":/images/icon/collect_video_hover.png"));
    ui->tabWidget->tabBar()->setTabIcon(2,QIcon(":/images/icon/dingyue_hover.png"));
    ui->tabWidget->tabBar()->setTabIcon(3,QIcon(":/images/icon/skin_hover.png"));
    ui->tabWidget->tabBar()->setTabIcon(4,QIcon(":/images/icon/download_video_hover.png"));
}

void PersonFileForm::chandleSignalsAndSLots()
{
    //返回页
    connect(ui->pushButton_returnpage,&QPushButton::clicked,[=](){});

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


