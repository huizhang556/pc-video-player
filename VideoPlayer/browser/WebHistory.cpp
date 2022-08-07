#include "WebHistory.h"
#include "ui_WebHistory.h"
#include "browser/RecordItem.h"

#include <QDebug>

WebHistory::WebHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebHistory)
{
    ui->setupUi(this);
    chandleSignalsAndSLots();
}

WebHistory::~WebHistory()
{
    delete ui;
}

void WebHistory::chandleSignalsAndSLots()
{
    //返回按钮
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){emit sig_returnPage();});
    //历史记录选中回显----回显选择的历史记录到lineEdit
//    connect(ui->listWidget_showHis,&QListWidget::itemClicked,[=](QListWidgetItem *item)
//    {
//        if(item->text().isEmpty()) return;
//        emit sig_sendItemText(item->text());
//        qDebug() << QString::fromLocal8Bit("选中的item文本：")<<item->text();
//    });

    //搜索历史记录
    connect(ui->lineEdit_searchHis,&QLineEdit::textChanged,[=](QString str){findSearchRecordsHittories(str);});
    //清除此页
    connect(ui->pushButton_clearPage,&QPushButton::clicked,[=](){
        ui->listWidget_showHis->clear();
    });
    //清除上网痕迹
    connect(ui->pushButton_clearRecords,&QPushButton::clicked,[=](){
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

bool WebHistory::judgeHistoryUrlExist(const QString &url)
{
    for(int i = 0; i < ui->listWidget_showHis->count(); i++)
    {
        if(ui->listWidget_showHis->item(i)->text() == url)
            return true;//代表有
    }
    return false;//代表无
}


void WebHistory::slot_addToListHistoryWidget(const QString &text)
{
    if(text.isEmpty()) return;
    if(!judgeHistoryUrlExist(text))//没有找到才添加
    {
        RecordItem *itemWidget = new RecordItem(2,QIcon("://images/function/history_list_item_hover.png"),text);
        QListWidgetItem *item = new QListWidgetItem(text);
        item->setSizeHint(itemWidget->size());
        ui->listWidget_showHis->insertItem(0,item);//头插法
        ui->listWidget_showHis->setItemWidget(item,itemWidget);

        //点击历史记录
        connect(itemWidget,&RecordItem::sig_item_record,[=](QString url){
            emit sig_sendItemText(url);//向外发送显示历史记录
            emit sig_returnPage();//显示浏览器页面
        });
        //删除item
        connect(itemWidget,&RecordItem::sig_item_delete,[=](){
            itemWidget->deleteLater();
            ui->listWidget_showHis->takeItem(ui->listWidget_showHis->row(item));
            delete item;
        });
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

