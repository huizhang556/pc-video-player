#include "DataAnalysis.h"
#include "ui_DataAnalysis.h"

DataAnalysis::DataAnalysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataAnalysis)
{
    ui->setupUi(this);
    initWorkUI();
    setInstallEventer();
    handleSignalsAndSlots();
}

DataAnalysis::~DataAnalysis()
{
    delete ui;
}

void DataAnalysis::initWorkUI()
{

    ui->pushButton_myfans->setCheckable(true);
    ui->pushButton_myattention->setCheckable(true);
    ui->pushButton_mycollect->setCheckable(true);
    ui->pushButton_mycommit->setCheckable(true);
    ui->pushButton_myfans->setChecked(true);
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->addButton(ui->pushButton_myfans,0);
    m_buttonGroup->addButton(ui->pushButton_myattention,1);
    m_buttonGroup->addButton(ui->pushButton_mycollect,2);
    m_buttonGroup->addButton(ui->pushButton_mycommit,3);
    m_buttonGroup->setExclusive(true);
    ui->stackedWidget_contents->setCurrentWidget(ui->page_playcounts);

    m_searchAction = new QAction(QIcon(":/images/icon/sousuohover.png"),"");
    ui->lineEdit_search->addAction(m_searchAction,QLineEdit::TrailingPosition);
    ui->lineEdit_search->setPlaceholderText(QString(u8"请输入查找关键字"));

    //提示文字
    ui->toolButton_error->setIcon(QIcon(":/images/bgpic/nothing.png"));
    ui->toolButton_error->setIconSize(QSize(180,180));
    ui->toolButton_error->setText(QString(u8"暂无数据！"));
    ui->toolButton_error->setFixedSize(180,240);
    ui->toolButton_error->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
}

void DataAnalysis::handleSignalsAndSlots()
{
    connect(m_buttonGroup,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton *button){
        data_clearScrollAreaContents();
        if(button->objectName() == QString(u8"pushButton_myfans"))
        {
            data_setTypeTag(QString(u8"我的粉丝"));
            data_addUserData_myfans();
        }
        else if(button->objectName() == QString(u8"pushButton_myattention"))
        {
            data_setTypeTag(QString(u8"我的关注"));
            data_addUserData_myattention();
        }
        else if(button->objectName() == QString(u8"pushButton_mycollect"))
        {
            data_setTypeTag(QString(u8"我的收藏"));
            data_addUserData_mycollect();
        }
        else if(button->objectName() == QString(u8"pushButton_mycommit"))
        {
            data_setTypeTag(QString(u8"我的评论"));
            data_addUserData_mycommit();

        }
        data_checkContentBlank();
    });

    //详细数据
    connect(ui->pushButton_detail,&QPushButton::clicked,[=](){
        ui->frame_topage->hide();
        ui->stackedWidget_contents->setCurrentWidget(ui->page_detailsdata);
    });

    //返回
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){
        ui->stackedWidget_contents->setCurrentWidget(ui->page_playcounts);
        ui->frame_topage->show();
    });

    //数据检索
    connect(ui->lineEdit_search,&QLineEdit::textChanged,[=](const QString &text){
        data_findKeyWordsResults(text);
    });
}

void DataAnalysis::setInstallEventer()
{

}

void DataAnalysis::slot_addUserData(const QVariant &userData)
{

}

void DataAnalysis::data_addUserData_myfans()
{
    QList<QUrlQuery> list_fans = dataBase::getInstance()->user_getCurUserAllFans(dataBase::getInstance()->getCurrentUserID());
    for(int i = 0; i < list_fans.count(); ++i)
    {
        UserDataItem *dataItem = new UserDataItem(UserDataType::FANS,list_fans.at(i));
        dataItem->setFixedSize(800,110);
        ui->m_itemVerticalLayout->insertWidget(0,dataItem);
        ui->m_itemVerticalLayout->setAlignment(dataItem,Qt::AlignCenter);//一个ITEM设置一个布局
    }
}

void DataAnalysis::data_addUserData_myattention()
{
    QList<QUrlQuery> list_attentions = dataBase::getInstance()->user_getCurUserAllWatches(dataBase::getInstance()->getCurrentUserID());
    for(int i = 0; i < list_attentions.count(); ++i)
    {
        UserDataItem *dataItem = new UserDataItem(UserDataType::WATCHES,list_attentions.at(i));
        dataItem->setFixedSize(800,110);
        ui->m_itemVerticalLayout->insertWidget(0,dataItem);
        ui->m_itemVerticalLayout->setAlignment(dataItem,Qt::AlignCenter);//一个ITEM设置一个布局
    }
}

void DataAnalysis::data_addUserData_mycollect()
{
    QList<QUrlQuery> list_collections = dataBase::getInstance()->user_getCurUserAllCollections(dataBase::getInstance()->getCurrentUserID());
    for(int i = 0; i < list_collections.count(); ++i)
    {
        UserDataItem *dataItem = new UserDataItem(UserDataType::VIDEO,list_collections.at(i));
        dataItem->setFixedSize(800,110);
        ui->m_itemVerticalLayout->insertWidget(0,dataItem);
        ui->m_itemVerticalLayout->setAlignment(dataItem,Qt::AlignCenter);//一个ITEM设置一个布局
    }
}

void DataAnalysis::data_addUserData_mycommit()
{
    for(int i = 0; i < 20; ++i)
    {
        UserDataItem *dataItem = new UserDataItem();
        dataItem->setFixedSize(800,110);
        ui->m_itemVerticalLayout->insertWidget(0,dataItem);
        ui->m_itemVerticalLayout->setAlignment(dataItem,Qt::AlignCenter);//一个ITEM设置一个布局
    }
}

void DataAnalysis::data_setTypeTag(const QString &type)
{
    ui->label_typetags->setText(type);
}

void DataAnalysis::data_clearScrollAreaContents()
{
    QLayoutItem *child;
    while((child = ui->scrollArea_plays->widget()->layout()->takeAt(0)) != nullptr)
    {
        if (UserDataItem* itemWidget = qobject_cast<UserDataItem*>(child->widget()))
        {
            delete itemWidget;
        }
        delete child;
    }

    //清空容器后，添加一个弹簧，顶上去
    ui->m_itemVerticalLayout->addSpacerItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void DataAnalysis::data_findKeyWordsResults(QString keywords)
{
    for(int i = 0; i < ui->scrollArea_plays->widget()->layout()->count(); i++)
    {
        QWidget* itemWgt = ui->scrollArea_plays->widget()->layout()->itemAt(i)->widget();
        if(itemWgt != nullptr)//除了自己以外的全部折叠
        {
            UserDataItem *userItem = static_cast<UserDataItem*>(itemWgt);
            if(userItem->get_user_nick().contains(keywords,Qt::CaseInsensitive))
            {
                userItem->show();
            }
            else
            {
                userItem->hide();
            }
        }
    }

}

void DataAnalysis::data_setItemChecked()
{

}

void DataAnalysis::data_checkContentBlank()
{
    if(ui->scrollArea_plays->widget()->layout()->count() == 0)
    {
        ui->stackedWidget_contents->setCurrentWidget(ui->page_blank);
        qDebug(u8"无数据");
    }
    else
    {
        ui->stackedWidget_contents->setCurrentWidget(ui->page_playcounts);
        qDebug(u8"有数据");
    }
}

