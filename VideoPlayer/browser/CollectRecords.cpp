#include "CollectRecords.h"
#include "ui_CollectRecords.h"
#include "browser/RecordItem.h"
#include "browser/WebMessageBox.h"
#include "browser/MiniRecordItem.h"

int CollectRecords::m_singleCount = 40;
#include <QDebug>

CollectRecords::CollectRecords(QWidget *parent) :
    QWidget(parent),
    m_count(0),
    ui(new Ui::CollectRecords)
{
    ui->setupUi(this);
    initWorkUI();
    chandleSignalsAndSlots();
}

CollectRecords::~CollectRecords()
{
    delete ui;
}

void CollectRecords::initWorkUI()
{
    ui->stackedWidget->setCurrentIndex(0);

    ui->listWidget_record1->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
    ui->listWidget_record1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_record1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_record2->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
    ui->listWidget_record2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_record2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_record3->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
    ui->listWidget_record3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_record3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_record4->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
    ui->listWidget_record4->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_record4->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_record5->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
    ui->listWidget_record5->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_record5->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_record6->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
    ui->listWidget_record6->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_record6->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_findResults->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);//像素滚动
    ui->listWidget_findResults->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_findResults->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void CollectRecords::chandleSignalsAndSlots()
{
    //01 导入导出收藏夹
    connect(ui->pushButton_export,&QPushButton::clicked,[=](){ui->stackedWidget->setCurrentIndex(1);});
    //02 撤回
    connect(ui->pushButton_undo,&QPushButton::clicked,[=](){ui->stackedWidget->setCurrentIndex(0);});
    //03 删除
    connect(ui->pushButton_delete,&QPushButton::clicked,[=](){});
    //04 修改记录
    connect(ui->pushButton_change,&QPushButton::clicked,[=](){
        WebMessageBox::getInstance()->exec();
        emit sig_changeRecord();
    });
    //05 确定
    connect(ui->pushButton_sure,&QPushButton::clicked,[=](){});
    //06 返回主页
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){emit sig_returnPage();});

    //记录查询
    connect(ui->lineEdit_search,&QLineEdit::textChanged,[=](QString text){
        if(!text.simplified().isEmpty())//去除空格
        {
            ui->stackedWidget->setCurrentIndex(1);
            findSearchCollectRecords(text);
        }
        else
        {
            ui->stackedWidget->setCurrentIndex(0);
        }
    });
}

QString CollectRecords::getCurrentRecordItemText(QListWidget *listWidget, QString &text)
{
    for(int i = 0; i < listWidget->count(); i++)
    {
        QWidget *itemWidget = listWidget->itemWidget(listWidget->item(i));
        if(nullptr != itemWidget)
        {
            QPushButton *itemBtn = itemWidget->findChild<QPushButton*>("pushButton_record");
            if(nullptr != itemBtn && itemBtn->text() == text)
                return listWidget->item(i)->text();
        }
    }
}

void CollectRecords::slot_addToRecordsListWidget(QUrl url)
{
    qDebug() << QString::fromLocal8Bit("历史记录接收到地址：")<<url.toDisplayString();
    slot_addToRecordsListWidget(url.toDisplayString(),QIcon(""),"");
}

void CollectRecords::slot_showWebMessageWindow(QString url, QString name)
{
    WebMessageBox::getInstance()->setWebMessageInforation(url,name);
    WebMessageBox::getInstance()->exec();
}

void CollectRecords::slot_addToRecordsListWidget(const QString &url = "", QIcon icon = QIcon(""), const QString &title = "")//默认参数
{
    if(url.isEmpty()) return;
    MiniRecordItem *itemWidget1 = new MiniRecordItem(title,icon);
    QListWidgetItem *item1 = new QListWidgetItem(url); item1->setToolTip(url);
    item1->setSizeHint(itemWidget1->size());
    getCurrentListWidget()->addItem(item1);//尾插法
    getCurrentListWidget()->setItemWidget(item1,itemWidget1);

    RecordItem *itemWidget2 = new RecordItem(3,icon,title);
    QListWidgetItem *item2 = new QListWidgetItem(url);
    item2->setSizeHint(itemWidget1->size()-QSize(50,0));
    ui->listWidget_findResults->addItem(item2);
    ui->listWidget_findResults->setItemWidget(item2,itemWidget2);
    //信号与槽函数
    //点击记录
    connect(itemWidget1,&MiniRecordItem::sig_item_record,[=](QString text){
        QWidget *parentListWgt = itemWidget1->nativeParentWidget();
        qDebug() <<parentListWgt->objectName();
//        QString itemText = getCurrentRecordItemText( text);
    });
    connect(itemWidget2,&RecordItem::sig_item_record,[=](QString text){

    });
    //修改
    connect(itemWidget1,&MiniRecordItem::sig_item_modify,[=](QString text){

    });
    connect(itemWidget2,&RecordItem::sig_item_modify,[=](QString text){
        QString itemText = getCurrentRecordItemText(ui->listWidget_findResults,text);
        slot_showWebMessageWindow(itemText,text);
    });
    //删除
    connect(itemWidget1,&MiniRecordItem::sig_item_delete,[=](){
        itemWidget1->deleteLater();
    });
    connect(itemWidget2,&RecordItem::sig_item_delete,[=](){
        itemWidget2->deleteLater();
        QListWidgetItem *item = ui->listWidget_findResults->takeItem(ui->listWidget_findResults->row(item2));
        delete item;
    });
}

void CollectRecords::findSearchCollectRecords(QString name)
{
    name.remove(QRegExp("\\s"));
    if(name.isEmpty())
    {
        for(int i = 0; i < ui->listWidget_findResults->model()->rowCount(); i++)
            ui->listWidget_findResults->setRowHidden(i,false);//字符为空，全部不隐藏

    }
    else//字符不为空
    {
        for(int i = 0; i <ui->listWidget_findResults->model()->rowCount(); i++)
        {
            ui->listWidget_findResults->setRowHidden(i,true);//先全部隐藏
            QString curname = "";
            QAbstractItemModel *model = ui->listWidget_findResults->model();
            QModelIndex index;//索引是一种特殊的数据结构，需要row 和 col 表述出来
            for(int j = 0; j <ui->listWidget_findResults->model()->columnCount(); j++)
            {
                index = model->index(i,j);
                curname += model->data(index).toString();//具体的item内容
            }
            curname.remove(QRegExp("\\s"));
            if(curname.contains(name,Qt::CaseInsensitive)) //CaseSensitive:敏感，如果item内容包含搜索的name
               ui->listWidget_findResults->setRowHidden(i,false);//在隐藏的item中有符合的，再显示出来
        }
    }
}

bool CollectRecords::judgeCollectRecordsUrlExist(const QString &url)
{
    for(int i = 0; i < ui->listWidget_findResults->count(); i++)
    {
        if(ui->listWidget_findResults->item(i)->text() == url)
        {
            return true;//代表有
        }
    }
    return false;//代表无
}

QListWidget *CollectRecords::getCurrentListWidget()
{
    int counts = getCurrentRecordsCounts();
    qDebug() <<QString::fromLocal8Bit("当前存储的标签数：")<<counts;
    if((counts < m_singleCount)) //小于SINGLECOUNTS条
    {
        m_currentListWidget = ui->listWidget_record1;
    }
    else if((counts < m_singleCount*2))// [4,2)
    {
        m_currentListWidget = ui->listWidget_record2;
    }
    else if((counts < m_singleCount*3))
    {
        m_currentListWidget = ui->listWidget_record3;
    }

    else if((counts < m_singleCount*4))
    {
        m_currentListWidget = ui->listWidget_record4;
    }
    else if((counts < m_singleCount*5))
    {
        m_currentListWidget = ui->listWidget_record5;
    }
    else if((counts < m_singleCount*6))
    {
        m_currentListWidget = ui->listWidget_record6;
    }
    else
    {
        qDebug() << QString::fromLocal8Bit("超过%1条收藏记录！").arg(m_singleCount*2);
    }
    qDebug() << QString::fromLocal8Bit("当前需要填充的QListWidget是:")<<m_currentListWidget->objectName();
    return m_currentListWidget;
}

int CollectRecords::getCurrentRecordsCounts()
{
    m_count =   ui->listWidget_record1->count() +
                ui->listWidget_record2->count() +
                ui->listWidget_record3->count() +
                ui->listWidget_record4->count() +
                ui->listWidget_record5->count() +
                ui->listWidget_record6->count();
    return m_count;
}

