#include "CollectRecords.h"
#include "ui_CollectRecords.h"
#include "browser/WebMessageBox.h"

#include <QDebug>
int CollectRecords::m_singleCount = 37;//一页最大化  37 rows


CollectRecords::CollectRecords(QWidget *parent) :
    QWidget(parent),
    m_count(0),
    m_isFirst(true),
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

    //00- 加载历史收藏记录
    connect(dataBase::getInstance(),&dataBase::sig_sendRecordInfo,[=](QString nick, QString url){
        slot_initToRecordsListWidget(url,QIcon("://images/icon/engine.png"),nick);
    });

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
    connect(ui->pushButton_sure,&QPushButton::clicked,[=](){
        dataBase::getInstance()->browser_loadAllRecordsToList();
    });
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

/***********************对于findChild和findChildren说明************************/
//函数原型：T QObject::findChild(const QString &name = QString(), Qt::FindChildOptions options = Qt::FindChildrenRecursively) const
//函数原型：QList< T > QObject::findChildren(const QString &name = QString(), Qt::FindChildOptions options = Qt::FindChildrenRecursively) const
//Qt::FindDirectChildrenOnly（只查看对象的直接子对象），Qt::FindChildrenRecursively（查看对象的所有子对象，递归搜索）
//圆括号内不写明对象名，说明查找的是父对象下的所有子对象；写对象名，说明查找的是某一个特定的对象
//查找父类下objectName为button1的直接子对象
//QPushButton *button = parentWidget->findChild<QPushButton *>("button1", Qt::FindDirectChildrenOnly);
//查找父类下所有的直接子对象
//QListWidget *list = parentWidget->findChild<QListWidget *>(QString(), Qt::FindDirectChildrenOnly);
//findChildren 跟 findChild 区别是findChildren 返回的是list
/***********************对于findChild和findChildren说明************************/

/**根据按钮文字查找listwidgetitem文字**/
QString CollectRecords::getCurrentRecordItemText(QListWidget *listWidget, QString &text)
{
    for(int i = 0; i < listWidget->count(); i++)
    {
        QWidget *itemWidget = listWidget->itemWidget(listWidget->item(i));
        if(nullptr != itemWidget)
        {
            QPushButton *itemBtn = itemWidget->findChild<QPushButton*>("pushButton_record");//可以指定查找范围（最近一级的还是所有的）
            if(nullptr != itemBtn && itemBtn->text() == text)
                return listWidget->item(i)->text();
        }
    }
}

/**根据按钮文字查找listwidgetitem**/
QListWidgetItem *CollectRecords::getCurrentRecordParentItem(QListWidget *listWidget, QString &text)
{
    for(int i = 0; i < listWidget->count(); i++)
    {
        QWidget *itemWidget = listWidget->itemWidget(listWidget->item(i));
        if(nullptr != itemWidget)
        {
            QPushButton *itemBtn = itemWidget->findChild<QPushButton*>("pushButton_record");//可以指定查找范围（最近一级的还是所有的）
            if(nullptr != itemBtn && itemBtn->text() == text)
                return listWidget->item(i);
        }
    }
}

//初始化历史记录
void CollectRecords::slot_initToRecordsListWidget(const QString &url, QIcon icon, const QString &title)
{
    if(url.isEmpty()) return;
    MiniRecordItem *itemWidget1 = new MiniRecordItem(title,icon);
    QListWidgetItem *item1 = new QListWidgetItem(url); item1->setToolTip(url);
    item1->setSizeHint(itemWidget1->size());
    getCurrentListWidget()->addItem(item1);//注意这里获取的lisiwidget，只要additem了，couunt就+1，导致下面获得的count不准确，导致插入的lisiwidget不一致
    m_currentListWidget->setItemWidget(item1,itemWidget1);//这里的lisiwidget要与上面的lisiwidget一致（尤其最后一个的时候）

    RecordItem *itemWidget2 = new RecordItem(3,icon,title);
    QListWidgetItem *item2 = new QListWidgetItem(url);
    item2->setSizeHint(itemWidget1->size()-QSize(50,0));
    ui->listWidget_findResults->addItem(item2);
    ui->listWidget_findResults->setItemWidget(item2,itemWidget2);

    //数据库操作--插入记录
//    dataBase::browser_addRecordToList(title,url);//插入 别名 url

    /****************************信号与槽函数****************************************/
    //点击记录1 跳转
    connect(itemWidget1,&MiniRecordItem::sig_item_record,[=](QString text){
        emit sig_sendItemText(item1->text());//添加tab
        emit sig_returnPage();//返回浏览器
        qDebug() << QString::fromLocal8Bit("item1点击的存储名称：") << text<< QString::fromLocal8Bit("点击的存储url：") << item1->text();

    });
     //点击记录2 跳转
    connect(itemWidget2,&RecordItem::sig_item_record,[=](QString text){
        emit sig_sendItemText(item2->text());//添加tab
        emit sig_returnPage();//返回浏览器
        qDebug() << QString::fromLocal8Bit("item2点击的存储名称：") << text << QString::fromLocal8Bit("点击的存储url：") << item2->text();
    });

    //修改思路：01.自己修改 02.查找修改 （统一使用url查找，再修改）
    //修改1
    connect(itemWidget1,&MiniRecordItem::sig_item_modify,[=](QString text,QPushButton *curBtn){
        QString itemText = getCurrentRecordItemText(item1->listWidget(),text);
        slot_showWebMessageWindow(itemText,text);//url nickname
    });
    //修改2
    connect(itemWidget2,&RecordItem::sig_item_modify,[=](QString text,QPushButton *curBtn){
        QString itemText = getCurrentRecordItemText(ui->listWidget_findResults,text);
        slot_showWebMessageWindow(itemText,text);//url nickname
    });

    //修改生效
    connect(WebMessageBox::getInstance(),&WebMessageBox::sig_sendTitleChanged,[=](QString url, QString rename){
                slot_updateCurrentRecord_recordItem(item1,url,rename);
                slot_updateCurrentRecord_miniRecordItem(item2,url,rename);
                dataBase::browser_updateRecordToList(url,rename);
    });

    //删除思路：01.自己删除 02.查找删除 03.标题存储删除 （统一使用url）
    //删除1
    connect(itemWidget1,&MiniRecordItem::sig_item_delete,[=](){
        //04数据库
        dataBase::browser_deleteRecordToList(item1->text());//根据 url 删除

        //03-标题存储删除(先发信号)
        emit sig_sendDeleteItemUrl(item1->text());//标题栏自己删除
        qDebug() << QString::fromLocal8Bit("item1删除点击的存储url：") << item1->text();

        //01-自己删除
        itemWidget1->deleteLater();
        QListWidgetItem *t_item1 = item1->listWidget()->takeItem(item1->listWidget()->row(item1));
        delete t_item1;
        t_item1 = nullptr;

        //02-查找删除{
        itemWidget2->deleteLater();
        QListWidgetItem *t_item2 = ui->listWidget_findResults->takeItem(ui->listWidget_findResults->row(item2));
        delete t_item2;
        t_item2 = nullptr;

    });
    //删除2
    connect(itemWidget2,&RecordItem::sig_item_delete,[=](){
        //04数据库
        dataBase::browser_deleteRecordToList(item1->text());//根据 url 删除

        //03-标题存储删除(先发信号)
       emit sig_sendDeleteItemUrl(item1->text());//标题栏自己删除
       qDebug() << QString::fromLocal8Bit("item2删除点击的存储url：") << item2->text();

        //01-查找删除
        itemWidget2->deleteLater();
        QListWidgetItem *t_item2 = ui->listWidget_findResults->takeItem(ui->listWidget_findResults->row(item2));
        delete t_item2;
        t_item2 = nullptr;

        //02-自己删除
        itemWidget1->deleteLater();
        QListWidgetItem *t_item1 = item1->listWidget()->takeItem(item1->listWidget()->row(item1));
        delete t_item1;
        t_item1 = nullptr;
    });
    /****************************信号与槽函数****************************************/
}

/*根据listwidgetitem文本查找按钮文本*/
QString CollectRecords::getCurrentRecordItemButtonText(QListWidgetItem *item)
{
    QWidget* itemWidget = ui->listWidget_findResults->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QPushButton *itemBtn = itemWidget->findChild<QPushButton*>("pushButton_record");//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != itemBtn)
        return itemBtn->text();
    }
}

QPushButton *CollectRecords::getCurrentRecordItemButton(QListWidgetItem *item)
{
    QWidget* itemWidget = item->listWidget()->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QPushButton *itemBtn = itemWidget->findChild<QPushButton*>("pushButton_record");//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != itemBtn)
        return itemBtn;
    }
}

//重载函数1：添加记录
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

void CollectRecords::slot_updateCurrentRecord_recordItem(QListWidgetItem *item, const QString &url, const QString &rename)
{
    //01 根据url（不变）找到listwidgetitem
    //02 根据找到的listwidgetitem，查找pushbutton
    //03 设置按钮文字
    if(item->text() == url)//群发性的，必须判断哪一个item符合，否则所有都会改变
    getCurrentRecordItemButton(item)->setText(rename);
}

void CollectRecords::slot_updateCurrentRecord_miniRecordItem(QListWidgetItem *item, const QString &url, const QString &rename)
{
    //01 根据url（不变）找到listwidgetitem
    //02 根据找到的listwidgetitem，查找pushbutton
    //03 设置按钮文字
    if(item->text() == url)//群发性的，必须判断哪一个item符合，否则所有都会改变
    getCurrentRecordItemButton(item)->setText(rename);
}

//重载函数2：添加记录
void CollectRecords::slot_addToRecordsListWidget(const QString &url = "", QIcon icon = QIcon(""), const QString &title = "")//默认参数
{
    if(url.isEmpty()) return;
    MiniRecordItem *itemWidget1 = new MiniRecordItem(title,icon);
    QListWidgetItem *item1 = new QListWidgetItem(url); item1->setToolTip(url);
    item1->setSizeHint(itemWidget1->size());
    getCurrentListWidget()->addItem(item1);//注意这里获取的lisiwidget，只要additem了，couunt就+1，导致下面获得的count不准确，导致插入的lisiwidget不一致
    m_currentListWidget->setItemWidget(item1,itemWidget1);//这里的lisiwidget要与上面的lisiwidget一致（尤其最后一个的时候）

    RecordItem *itemWidget2 = new RecordItem(3,icon,title);
    QListWidgetItem *item2 = new QListWidgetItem(url);
    item2->setSizeHint(itemWidget1->size()-QSize(50,0));
    ui->listWidget_findResults->addItem(item2);
    ui->listWidget_findResults->setItemWidget(item2,itemWidget2);

    //数据库操作--插入记录
    dataBase::browser_addRecordToList(title,url);//插入 别名 url

    /****************************信号与槽函数****************************************/
    //点击记录1 跳转
    connect(itemWidget1,&MiniRecordItem::sig_item_record,[=](QString text){
        emit sig_sendItemText(item1->text());//添加tab
        emit sig_returnPage();//返回浏览器
        qDebug() << QString::fromLocal8Bit("item1点击的存储名称：") << text<< QString::fromLocal8Bit("点击的存储url：") << item1->text();

    });
     //点击记录2 跳转
    connect(itemWidget2,&RecordItem::sig_item_record,[=](QString text){
        emit sig_sendItemText(item2->text());//添加tab
        emit sig_returnPage();//返回浏览器
        qDebug() << QString::fromLocal8Bit("item2点击的存储名称：") << text << QString::fromLocal8Bit("点击的存储url：") << item2->text();
    });

    //修改思路：01.自己修改 02.查找修改 （统一使用url查找，再修改）
    //修改1
    connect(itemWidget1,&MiniRecordItem::sig_item_modify,[=](QString text,QPushButton *curBtn){
        QString itemText = getCurrentRecordItemText(item1->listWidget(),text);
        slot_showWebMessageWindow(itemText,text);//url nickname
    });
    //修改2
    connect(itemWidget2,&RecordItem::sig_item_modify,[=](QString text,QPushButton *curBtn){
        QString itemText = getCurrentRecordItemText(ui->listWidget_findResults,text);
        slot_showWebMessageWindow(itemText,text);//url nickname
    });

    //修改生效
    connect(WebMessageBox::getInstance(),&WebMessageBox::sig_sendTitleChanged,[=](QString url, QString rename){
                slot_updateCurrentRecord_recordItem(item1,url,rename);
                slot_updateCurrentRecord_miniRecordItem(item2,url,rename);
                dataBase::browser_updateRecordToList(url,rename);
    });

    //删除思路：01.自己删除 02.查找删除 03.标题存储删除 （统一使用url）
    //删除1
    connect(itemWidget1,&MiniRecordItem::sig_item_delete,[=](){
        //04数据库
        dataBase::browser_deleteRecordToList(item1->text());//根据 url 删除

        //03-标题存储删除(先发信号)
        emit sig_sendDeleteItemUrl(item1->text());//标题栏自己删除
        qDebug() << QString::fromLocal8Bit("item1删除点击的存储url：") << item1->text();

        //01-自己删除
        itemWidget1->deleteLater();
        QListWidgetItem *t_item1 = item1->listWidget()->takeItem(item1->listWidget()->row(item1));
        delete t_item1;
        t_item1 = nullptr;

        //02-查找删除{
        itemWidget2->deleteLater();
        QListWidgetItem *t_item2 = ui->listWidget_findResults->takeItem(ui->listWidget_findResults->row(item2));
        delete t_item2;
        t_item2 = nullptr;

    });
    //删除2
    connect(itemWidget2,&RecordItem::sig_item_delete,[=](){
        //04数据库
        dataBase::browser_deleteRecordToList(item1->text());//根据 url 删除

        //03-标题存储删除(先发信号)
       emit sig_sendDeleteItemUrl(item1->text());//标题栏自己删除
       qDebug() << QString::fromLocal8Bit("item2删除点击的存储url：") << item2->text();

        //01-查找删除
        itemWidget2->deleteLater();
        QListWidgetItem *t_item2 = ui->listWidget_findResults->takeItem(ui->listWidget_findResults->row(item2));
        delete t_item2;
        t_item2 = nullptr;

        //02-自己删除
        itemWidget1->deleteLater();
        QListWidgetItem *t_item1 = item1->listWidget()->takeItem(item1->listWidget()->row(item1));
        delete t_item1;
        t_item1 = nullptr;
    });
    /****************************信号与槽函数****************************************/
}

QString CollectRecords::slot_getCurrentRecordItemText(const QString &text)
{
    for(int i = 0; i < ui->listWidget_findResults->count(); i++)
    {
        QWidget *itemWidget = ui->listWidget_findResults->itemWidget(ui->listWidget_findResults->item(i));
        if(nullptr != itemWidget)
        {
            QPushButton *itemBtn = itemWidget->findChild<QPushButton*>("pushButton_record");//可以指定查找范围（最近一级的还是所有的）
            if(nullptr != itemBtn && itemBtn->text() == text)
                return ui->listWidget_findResults->item(i)->text();
        }
    }
}

void CollectRecords::findSearchCollectRecords(QString name)
{
    name.remove(QRegExp("\\s"));
    if(name.isEmpty())
    {
        for(int i = 0; i < ui->listWidget_findResults->count(); i++)
            ui->listWidget_findResults->setRowHidden(i,false);//字符为空，全部不隐藏

    }
    else//字符不为空
    {
        for(int i = 0; i <ui->listWidget_findResults->count(); i++)
        {
            ui->listWidget_findResults->setRowHidden(i,true);//先全部隐藏
            QString curname = getCurrentRecordItemButtonText(ui->listWidget_findResults->item(i));
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
    qDebug() <<QString::fromLocal8Bit("当前未插入前分开的单个的存储的标签数：")<<counts;
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
        qDebug() << QString::fromLocal8Bit("超过%1条收藏记录！").arg(m_singleCount*6);
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

