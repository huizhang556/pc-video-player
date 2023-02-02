#include "SearchForm.h"
#include "ui_SearchForm.h"
#include "messagebox/CMessageBox.h"
#include "titlebar/CusListItem.h"
#include <QListWidgetItem>
#include <QDebug>

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);
    this->setFixedHeight(385);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::Popup);//无标题栏 无任务图标 鼠标单击空白自动hide()
    initWorkUi();
    chandleSignalsAndSlot();

}

SearchForm::~SearchForm()
{
    delete ui;
}

void SearchForm::initWorkUi()
{
    m_manger=new QNetworkAccessManager(this);
    this->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_his1->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_his2->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_hot1->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_hot2->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_findresult->setFocusPolicy(Qt::NoFocus);

    ui->listWidget_his1->setViewMode(QListView::ListMode);
    ui->listWidget_his2->setViewMode(QListView::ListMode);
    ui->listWidget_hot1->setViewMode(QListView::ListMode);
    ui->listWidget_hot2->setViewMode(QListView::ListMode);
    ui->listWidget_findresult->setViewMode(QListView::ListMode);

    ui->listWidget_his1->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_his2->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_hot1->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_hot2->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_findresult->setMovement(QListView::Static);//图标不可拖动

    ui->listWidget_his1->setResizeMode(QListWidget::Adjust);
    ui->listWidget_his2->setResizeMode(QListWidget::Adjust);
    ui->listWidget_hot1->setResizeMode(QListWidget::Adjust);
    ui->listWidget_hot2->setResizeMode(QListWidget::Adjust);
    ui->listWidget_findresult->setResizeMode(QListWidget::Adjust);

    ui->listWidget_his1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_his1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_his1->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->listWidget_his2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_his2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_his2->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->listWidget_hot1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_hot1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_hot1->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->listWidget_hot2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_hot2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_hot2->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->listWidget_findresult->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_findresult->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_findresult->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->btn_his_delete->setFlat(true);
    ui->btn_hot_more->setFlat(true);
    clearHistoryList();

    QStringList contentList =
    {
        QString(u8"1余生请多指教"),
        QString(u8"2王牌对王牌 第7季"),
        QString(u8"3斗罗大陆"),
        QString(u8"4猎罪图鉴"),
        QString(u8"5陈情令"),
        QString(u8"6中国机长"),
        QString(u8"7追爱家族"),
        QString(u8"8骨语2"),
        QString(u8"9才不要和老板谈恋爱"),
        QString(u8"10雪中悍刀行"),
    };
    slot_addHotRecommendItems(contentList);
}

void SearchForm::chandleSignalsAndSlot()
{
    //清除历史记录
    connect(ui->btn_his_delete,&QPushButton::clicked,[=](){
       CMessageBox message(MessageType::CQuestion,QString(u8"清除提示"),QString(u8"您确定要清除吗？"),QString(u8"确定"),QString(u8"取消"));
       if(message.exec() == QDialog::Accepted)//1
        clearHistoryList();
       checkHisAutoHight();
    });

    connect(ui->listWidget_findresult,&QListWidget::itemClicked,[=](QListWidgetItem *item){
        if(item == nullptr)
        {
            return;
        }
    addHistoryItem(item->text());
    });

    //更多热搜
    connect(ui->btn_hot_more,&QPushButton::clicked,[=](){emit sig_SendToMoreHots();});

}

void SearchForm::showUI(SHOWTYPE type)
{
    switch (type)
    {
        case SHOWTYPE::HISHOT:
        {
            ui->stackedWidget_search->setCurrentWidget(ui->page_his);
        }
            break;
        case SHOWTYPE::RESFIND:
        {
        ui->stackedWidget_search->setCurrentWidget(ui->page_result);
        }
        case SHOWTYPE::NORMAL:
        {

        }
            break;
        default:
            break;
    }
    this->show();
}


void SearchForm::slot_addHotRecommendItems(const QStringList &str_list)
{
    for(int i = 0; i < str_list.count(); i++)
    {

        if(i%2 == 0)//不是0就是1
        {
            QListWidgetItem *hotItem = new  QListWidgetItem(QIcon("://images/home/songlist_hot.png"),str_list.at(i));
            ui->listWidget_hot1->addItem(hotItem);
        }
        else
        {
            QListWidgetItem *hotItem = new  QListWidgetItem(QIcon("://images/home/songlist_new.png"),str_list.at(i));
            ui->listWidget_hot2->addItem(hotItem);
        }
    }
}

void SearchForm::slot_showSearchResult(const QString str)
{
    ui->listWidget_findresult->clear();
//       int count = ui->listWidget_findresult->count();
//       for(int i = 0; i < count; i++)
//       {
//          QListWidgetItem *item= ui->listWidget_findresult->takeItem(i);
//          delete item;
//       }
       QNetworkRequest request;
       request.setUrl(QUrl("http://i.y.qq.com/s.plcloud/fcgi-bin/smartbox_new.fcg?key="+str+"&utf8=1&is_json=1"));
       request.setRawHeader("Accept","*/*");
       request.setRawHeader("Accept-Language","zh-CN");
       request.setRawHeader("User-Agent","Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)");
       request.setRawHeader("Host","i.y.qq.com");
       request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
       request.setRawHeader("Accept-Encoding","deflate");
       request.setRawHeader("Cookie","qqmusic_fromtag=3; qqmusic_miniversion=57; qqmusic_version=12;");
       QNetworkReply *reply = m_manger->get(request);
       QEventLoop loop;
       connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));
       loop.exec();

       if(reply->error() == QNetworkReply::NoError)
       {
           QByteArray byt = reply->readAll();
           QJsonDocument doc = QJsonDocument::fromJson(byt);
           QJsonObject obj  = doc.object();
           QJsonObject obj1 = obj.value("data").toObject();
           QJsonObject obj2 = obj1.value("song").toObject();
           QJsonArray arry = obj2.value("itemlist").toArray();
           for(int i = 0; i < arry.count(); i++)
           {
               QJsonObject obj3   = arry.at(i).toObject();
               QString songname   = obj3.value("name").toString();
               QString songsinger = obj3.value("singer").toString();
               ui->listWidget_findresult->addItem(new QListWidgetItem(QString::number(ui->listWidget_findresult->count()+1) + " " + songsinger+ "-" + songname));
//               qDebug() << QString(u8"查询到的结果：")<<songsinger+"-"+songname;
           }
       }
       reply->deleteLater();
}

void SearchForm::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->hide();
}

void SearchForm::clearHistoryList()
{
    ui->listWidget_his1->clear();
    ui->listWidget_his2->clear();
}

void SearchForm::checkHisAutoHight()
{
    if(ui->listWidget_his1->count() == 0 && ui->listWidget_his2->count() == 0)
    {
        ui->frame_title_his->hide();
        ui->frame_histories->hide();
        this->setFixedHeight(200);
    }
    else
    {
        ui->frame_title_his->show();
        ui->frame_histories->show();
        this->setFixedHeight(385);
    }
}

void SearchForm::addHistoryItem(QString his)
{
    if(ui->listWidget_his2->count() > 4)
    {
        clearHistoryList();
    }
    qDebug() << his;
    QListWidgetItem *item =  new QListWidgetItem();
    if(ui->listWidget_his1->count() <= 4)
    {
        CusListItem *itemWidget1 = new CusListItem("://images/home/songlist_hot.png",his);
        ui->listWidget_his1->addItem(item);
        ui->listWidget_his1->setItemWidget(item,itemWidget1);
        connect(itemWidget1,&CusListItem::sig_sendItemClose,[=]()
        {
            qDebug() << QString(u8"his1接收到删除信号");
            itemWidget1->deleteLater();
//            ui->listWidget_his1->takeItem(ui->listWidget_his1->row(item));
            ui->listWidget_his1->removeItemWidget(item);
            delete item;
            checkHisAutoHight();
        });

        connect(itemWidget1,&CusListItem::sig_sendItemText,[=](QString text)
        {
            qDebug() << QString(u8"历史记录")<<text;
        });
    }
    else if((ui->listWidget_his2->count() <= 4))
    {
        CusListItem *itemWidget2 = new CusListItem("://images/home/songlist_new.png",his);
        ui->listWidget_his2->addItem(item);
        ui->listWidget_his2->setItemWidget(item,itemWidget2);
        connect(itemWidget2,&CusListItem::sig_sendItemClose,[=]()
        {
            qDebug() << QString(u8"his2接收到删除信号");
            itemWidget2->deleteLater();
//            ui->listWidget_his2->takeItem(ui->listWidget_his1->row(item));
            ui->listWidget_his2->removeItemWidget(item);
            delete item;
            checkHisAutoHight();
        });

        connect(itemWidget2,&CusListItem::sig_sendItemText,[=](QString text)
        {
            qDebug() << QString(u8"历史记录")<<text;
        });
    }
    checkHisAutoHight();
}

void SearchForm::closeSearchForm()
{
    this->close();
}
