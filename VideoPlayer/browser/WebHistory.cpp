#include "WebHistory.h"
#include "ui_WebHistory.h"

#include "database/dataBase.h"
#include "browser/RecordItem.h"

#include <QDebug>
#include <QToolTip>

WebHistory::WebHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebHistory)
{
    ui->setupUi(this);
    initWorkUI();
    chandleSignalsAndSLots();
}

WebHistory::~WebHistory()
{
    delete ui;
}

void WebHistory::initWorkUI()
{
    ui->pushButton_delete->hide();
    ui->radioButton_broTime->setCheckable(true);
    ui->radioButton_broTime->setChecked(true);
    ui->radioButton_zhanDian->setCheckable(true);

    ui->listWidget_showHis->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
//    ui->listWidget_showHis->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->listWidget_showHis->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void WebHistory::chandleSignalsAndSLots()
{
    //返回按钮
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){emit sig_returnPage();});

    //搜索历史记录
    connect(ui->lineEdit_searchHis,&QLineEdit::textChanged,[=](QString str){
        if(str.simplified().isEmpty())
            findSearchRecordsHittories(str);
    });
    //搜索回车
    connect(ui->lineEdit_searchHis,&QLineEdit::returnPressed,[=](){
        findSearchRecordsHittories(ui->lineEdit_searchHis->text().trimmed());
    });
    //清除此页
    connect(ui->pushButton_clearPage,&QPushButton::clicked,[=](){
        ui->listWidget_showHis->clear();
        //数据库清除
        dataBase::browser_deleteAllHisRecordToList();
    });
    //搜索按钮
    connect(ui->pushButton_searchHis,&QPushButton::clicked,[=](){
        findSearchRecordsHittories(ui->lineEdit_searchHis->text().trimmed());
    });
    //清除上网痕迹
    connect(ui->pushButton_clearRecords,&QPushButton::clicked,[=](){
        slot_clearMarks();
        qDebug() << QString::fromLocal8Bit("已清除上网痕迹！");
    });
    //删除
    connect(ui->pushButton_delete,&QPushButton::clicked,[=](){});
}

void WebHistory::slot_addToListHistoryWidget(QUrl url)
{
    qDebug() << QString::fromLocal8Bit("历史记录接收到地址：")<<url.toDisplayString();
    slot_addToListHistoryWidget(url.toDisplayString());
}

//初始化历史记录
void WebHistory::slot_initHistoryRecordListWgt(const QString &text)
{
    if(text.isEmpty()) return;
    bool finded = judgeHistoryUrlExist(text);//存在则删除重建（or不存在）也删除重建
    qDebug() <<QString::fromLocal8Bit("历史记录存在状态")<<finded;
    RecordItem *itemWidget = new RecordItem(4,QIcon("://images/function/history_list_item_hover.png"),text);
    QListWidgetItem *item = new QListWidgetItem(text);
    item->setSizeHint(itemWidget->size()-QSize(170,0));
    ui->listWidget_showHis->insertItem(0,item);//头插法
    ui->listWidget_showHis->setItemWidget(item,itemWidget);

    //点击历史记录
    connect(itemWidget,&RecordItem::sig_item_record,[=](QString url){
        emit sig_sendItemText(url);//向外发送显示历史记录
        emit sig_returnPage();//显示浏览器页面
    });
    //删除item
    connect(itemWidget,&RecordItem::sig_item_delete,[=](){
        //00---数据库先操作
        dataBase::browser_deleteHisRecordToList(item->text());
        //删除前应该先断开信号与槽函数连接，防止最后一个item删除出现bug
        itemWidget->deleteLater();
        ui->listWidget_showHis->takeItem(ui->listWidget_showHis->row(item));
        delete item;
    });
}

bool WebHistory::judgeHistoryUrlExist(const QString &url)
{
    for(int i = 0; i < ui->listWidget_showHis->count(); i++)
    {
        if(ui->listWidget_showHis->item(i)->text() == url)
        {
            QListWidgetItem* deleteItem = ui->listWidget_showHis->takeItem(i);//删除原有的历史记录
            delete deleteItem;
            return true;//代表有
        }
    }
    return false;//代表无
}


void WebHistory::slot_addToListHistoryWidget(const QString &text)
{
    if(text.isEmpty()) return;
    bool finded = judgeHistoryUrlExist(text);//存在则删除重建（or不存在）也删除重建
    qDebug() <<QString::fromLocal8Bit("历史记录存在状态")<<finded;
    RecordItem *itemWidget = new RecordItem(4,QIcon("://images/function/history_list_item_hover.png"),text);
    QListWidgetItem *item = new QListWidgetItem(text);
    item->setSizeHint(itemWidget->size()-QSize(170,0));
    ui->listWidget_showHis->insertItem(0,item);//头插法
    ui->listWidget_showHis->setItemWidget(item,itemWidget);

    //数据库插入一条历史记录
    dataBase::browser_addHisRecordToList(item->text());

    //点击历史记录
    connect(itemWidget,&RecordItem::sig_item_record,[=](QString url){
        emit sig_sendItemText(url);//向外发送显示历史记录
        emit sig_returnPage();//显示浏览器页面
    });
    //删除item
    connect(itemWidget,&RecordItem::sig_item_delete,[=](){
        //00---数据库先操作
        dataBase::browser_deleteHisRecordToList(item->text());
        //删除前应该先断开信号与槽函数连接，防止最后一个item删除出现bug
        itemWidget->deleteLater();
        ui->listWidget_showHis->takeItem(ui->listWidget_showHis->row(item));
        delete item;
    });
}

void WebHistory::slot_clearMarks()
{
    for(int i = 0; i < ui->listWidget_showHis->count();i++)
    {
        QWidget *itemWidget = ui->listWidget_showHis->itemWidget(ui->listWidget_showHis->item(i));
        if(nullptr != itemWidget)
        {
            QPushButton *itemBtn = itemWidget->findChild<QPushButton*>("pushButton_record");
            if(nullptr != itemBtn)
                itemBtn->setStyleSheet("QPushButton"
                                       "{"
                                       "border:none;"
                                       "background-color:transparent;"
                                       "text-align:left;"
                                       "padding-left:8px;"
                                       "text-decoration:line-through;"
                                       "color:#cccccc;"
                                       "}"
                                       "QPushButton:hover"
                                       "{"
                                       "color:#2ba8fc;"
                                       "}"
                                       );
        }
    }
}

void WebHistory::findSearchRecordsHittories(QString name)
{
    name.remove(QRegExp("\\s"));
    if(name.isEmpty())
    {
        for(int i = 0; i < ui->listWidget_showHis->model()->rowCount(); i++)
            ui->listWidget_showHis->setRowHidden(i,false);

    }
    else
    {
        for(int i = 0; i <ui->listWidget_showHis->model()->rowCount(); i++)
        {
            ui->listWidget_showHis->setRowHidden(i,true);
            QString curname = "";
            QAbstractItemModel *model = ui->listWidget_showHis->model();
            QModelIndex index;
            for(int j = 0; j <ui->listWidget_showHis->model()->columnCount(); j++)
            {
                index = model->index(i,j);
                curname += model->data(index).toString();
            }
            curname.remove(QRegExp("\\s"));
            if(curname.contains(name,Qt::CaseInsensitive)) //CaseSensitive:敏感
               ui->listWidget_showHis->setRowHidden(i,false);
        }
    }
}

