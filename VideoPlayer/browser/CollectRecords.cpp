#include "CollectRecords.h"
#include "ui_CollectRecords.h"
#include "browser/RecordItem.h"

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
    connect(ui->pushButton_change,&QPushButton::clicked,[=](){emit sig_changeRecord();});
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

void CollectRecords::slot_addToRecordsListWidget(QUrl url)
{
    qDebug() << QString::fromLocal8Bit("历史记录接收到地址：")<<url.toDisplayString();
    slot_addToRecordsListWidget(url.toDisplayString(),QIcon(""));
}

void CollectRecords::slot_addToRecordsListWidget(const QString &text = "",QIcon icon = QIcon(""))//默认参数
{
    if(text.isEmpty()) return;
//    if(icon.isNull()) icon = QIcon("://images/icon/engine.png");//图片传不过来不及时
    RecordItem *itemWidget = new RecordItem(3,icon,text);
    QListWidgetItem *item1 = new QListWidgetItem(icon,text);
    item1->setToolTip(text);
    QListWidgetItem *item2 = new QListWidgetItem(text);
    item2->setSizeHint(itemWidget->size()-QSize(50,0));
    getCurrentListWidget()->addItem(item1);//尾插法
    ui->listWidget_findResults->addItem(item2);
    ui->listWidget_findResults->setItemWidget(item2,itemWidget);
}

void CollectRecords::findSearchCollectRecords(QString name)
{
    name.remove(QRegExp("\\s"));
    if(name.isEmpty())
    {
        for(int i = 0; i < ui->listWidget_findResults->model()->rowCount(); i++)
            ui->listWidget_findResults->setRowHidden(i,false);

    }
    else
    {
        for(int i = 0; i <ui->listWidget_findResults->model()->rowCount(); i++)
        {
            ui->listWidget_findResults->setRowHidden(i,true);
            QString curname = "";
            QAbstractItemModel *model = ui->listWidget_findResults->model();
            QModelIndex index;
            for(int j = 0; j <ui->listWidget_findResults->model()->columnCount(); j++)
            {
                index = model->index(i,j);
                curname += model->data(index).toString();
            }
            curname.remove(QRegExp("\\s"));
            if(curname.contains(name,Qt::CaseInsensitive)) //CaseSensitive:敏感
               ui->listWidget_findResults->setRowHidden(i,false);
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

