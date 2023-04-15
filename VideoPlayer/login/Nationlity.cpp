#include "Nationlity.h"
#include "ui_Nationlity.h"

//类外初始化
//Nationlity* Nationlity::m_pInstance = nullptr;

Nationlity::Nationlity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Nationlity)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);//鼠标点击外部，界面自动隐藏
    setFocusPolicy(Qt::NoFocus);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

Nationlity::~Nationlity()
{
    delete ui;
//    //删除创建的单例
//    if(m_pInstance != nullptr)
//        delete m_pInstance;
//    m_pInstance = nullptr;
}

void Nationlity::initWorkUI()
{
    ui->listWidget_country->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_province->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_city->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_country->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_province->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_city->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->listWidget_country->setContextMenuPolicy(Qt::NoContextMenu);
    ui->listWidget_province->setContextMenuPolicy(Qt::NoContextMenu);
    ui->listWidget_city->setContextMenuPolicy(Qt::NoContextMenu);

    ui->lineEdit_country->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_province->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_city->setContextMenuPolicy(Qt::NoContextMenu);

    ui->lineEdit_country->setPlaceholderText(QString(u8"国家名"));
    ui->lineEdit_province->setPlaceholderText(QString(u8"省名"));
    ui->lineEdit_city->setPlaceholderText(QString(u8"市名"));

//    ui->lineEdit_country->setInputMethodHints(Qt::ImhNoPredictiveText);
//    ui->lineEdit_province->setInputMethodHints(Qt::ImhNoPredictiveText);
//    ui->lineEdit_city->setInputMethodHints(Qt::ImhNoPredictiveText);

    //解析xml文件
    disposeXML();
    ui->listWidget_city->clear();
    ui->listWidget_province->clear();

    //添加国家
    ui->listWidget_country->clear();
    ui->listWidget_country->addItems(getCountryName());

    ui->stackedWidget_country->setCurrentIndex(0);
    ui->stackedWidget_province->setCurrentIndex(0);
    ui->stackedWidget_city->setCurrentIndex(0);
}

void Nationlity::handleSignalsAndSlots()
{
    connect(ui->pushButton_country,&QPushButton::clicked,[=](){
        ui->stackedWidget_country->setCurrentIndex(1);
        // 以下两句解决焦点+不能输入中文的问题
        ui->lineEdit_country->setFocus();
        ui->lineEdit_country->activateWindow();
    });

    connect(ui->pushButton_province,&QPushButton::clicked,[=](){
        ui->stackedWidget_province->setCurrentIndex(1);
        // 以下两句解决焦点+不能输入中文的问题
        ui->lineEdit_province->setFocus();
        ui->lineEdit_province->activateWindow();
    });

    connect(ui->pushButton_city,&QPushButton::clicked,[=](){
        ui->stackedWidget_city->setCurrentIndex(1);
        // 以下两句解决焦点+不能输入中文的问题
        ui->lineEdit_city->setFocus();
        ui->lineEdit_city->activateWindow();
    });


    connect(ui->listWidget_country,&QListWidget::itemClicked,[=](QListWidgetItem *item){
        m_country = item->text();
        emit sig_send_selectedtext(m_country.append("-"));
        ui->lineEdit_country->clear();
        //获取对应的国家下面的省、自治区列表
        slot_countryChanged(item->text());

    });

    //省-变化
    connect(ui->listWidget_province,&QListWidget::itemClicked,[=](QListWidgetItem *item){
        m_province = item->text();
        m_province.append("-");
        emit sig_send_selectedtext(m_country + m_province);
        ui->lineEdit_province->clear();
        //获取对应的省下面的城市列表
        slot_provinceChanged(item->text());

    });

    //市-变化
    connect(ui->listWidget_city,&QListWidget::itemClicked,[=](QListWidgetItem *item){
        m_city = item->text();
        emit sig_send_selectedtext(m_country + m_province + m_city);
        ui->lineEdit_city->clear();
    });

    //国家---关键字检索
    connect(ui->lineEdit_country,&QLineEdit::textChanged,[=](const QString &text){
        qDebug() <<QString(u8"当前国家检索关键字为：%1").arg(text);
        findKeyWordResults(ui->listWidget_country,text);
    });

    //省---关键字检索
    connect(ui->lineEdit_province,&QLineEdit::textChanged,[=](const QString &text){
        qDebug() <<QString(u8"当前省检索关键字为：%1").arg(text);
        findKeyWordResults(ui->listWidget_province,text);
    });

    //市---关键字检索
    connect(ui->lineEdit_city,&QLineEdit::textChanged,[=](const QString &text){
        qDebug() <<QString(u8"当前市检索关键字为：%1").arg(text);
        findKeyWordResults(ui->listWidget_city,text);
    });
}

void Nationlity::setInstallEventFilter()
{
    this->installEventFilter(this);
    ui->lineEdit_country->installEventFilter(this);
    ui->lineEdit_province->installEventFilter(this);
    ui->lineEdit_city->installEventFilter(this);
}


//Nationlity *Nationlity::getInstance()
//{
//    if(m_pInstance == nullptr)
//    {
//        m_pInstance = new Nationlity();
//    }
//    return m_pInstance;
//}

bool Nationlity::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && event->type() == QEvent::Leave)
    {
        this->close();
    }
    if(watched == ui->lineEdit_country)
    {
        if(event->type() == QEvent::FocusOut)
        {
            ui->stackedWidget_country->setCurrentIndex(0);
            ui->lineEdit_country->clearFocus();
            ui->lineEdit_country->releaseKeyboard();
        }
        else if(event->type() == QEvent::FocusIn)
        {
            ui->lineEdit_country->grabKeyboard();
        }
    }
    if(watched == ui->lineEdit_province)
    {
        if(event->type() == QEvent::FocusOut)
        {
            ui->stackedWidget_province->setCurrentIndex(0);
            ui->lineEdit_province->clearFocus();
            ui->lineEdit_province->releaseKeyboard();
        }
        else if(event->type() == QEvent::FocusIn)
        {
            ui->lineEdit_province->grabKeyboard();
        }
    }
    if(watched == ui->lineEdit_city)
    {
        if(event->type() == QEvent::FocusOut)
        {
            ui->stackedWidget_city->setCurrentIndex(0);
            ui->lineEdit_city->clearFocus();
            ui->lineEdit_city->releaseKeyboard();
        }
        else if(event->type() == QEvent::FocusIn)
        {
            ui->lineEdit_city->grabKeyboard();
        }
    }

    return QWidget::eventFilter(watched,event);
}

void Nationlity::disposeXML()
{
    QFile file(Global::appDirPath + u8"/config/LocList.xml");
    if (!file.open(QFile::ReadOnly))
    {
        qDebug() <<QString(u8"城市列表xml解析失败！");
        return;
    }
    qDebug() <<QString(u8"城市列表xml解析成功！");
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement rootElement = doc.documentElement();
    if (rootElement.tagName() != "Location")
        return;

    QDomElement chinaElement;
    QDomNodeList nodeLsit = rootElement.childNodes();
    for (int i = 0; i < nodeLsit.count(); ++i)
    {
        QDomElement element = nodeLsit.at(i).toElement();
        if (element.attribute("Name") == u8"中国")
        {
            chinaElement = element;
            break;
        }
    }

    if (chinaElement.isNull())
        return;

    QDomNodeList chinaNodeList = chinaElement.childNodes();
    for (int i = 0; i < chinaNodeList.count(); ++i)
    {
        // 解析省/直辖市
        QDomElement element = chinaNodeList.at(i).toElement();
        QString stateName = element.attribute("Name");
        QList<CityInfo> cityInfoList;
        cityInfoList.clear();

        // 解析城市
        QDomNodeList cityNodeList = element.childNodes();
        for (int j = 0; j < cityNodeList.count(); ++j)
        {
            QDomElement cityElement = cityNodeList.at(j).toElement();
            QString cityName = cityElement.attribute("Name");

            CityInfo cityInfo;
            cityInfo.cityName = cityName;
            QList<QString> regionNameList;
            regionNameList.clear();

//            // 解析区
//            QDomNodeList regionNodeList = cityElement.childNodes();
//            for (int k=0; k<regionNodeList.count(); ++k)
//            {
//                QDomElement regionElement = regionNodeList.at(k).toElement();

//                QString regionName = regionElement.attribute("Name");
//                regionNameList.push_back(regionName);
//            }

            cityInfo.regionName = regionNameList;
            cityInfoList.push_back(cityInfo);
        }

        m_ChinaCityInfo.insert(stateName, cityInfoList);
    }
}

//获取国家列表
QList<QString> Nationlity::getCountryName(void)
{
    QList<QString> countryNameList;
    countryNameList.clear();
    countryNameList.append(QString(u8"中国"));
    return countryNameList;
}

//获取省列表
QList<QString> Nationlity::getProvinceName(QString &province)
{
    QList<QString> provinceNameList;
       provinceNameList.clear();
       for (auto itor = m_ChinaCityInfo.begin(); itor != m_ChinaCityInfo.end(); ++itor)
       {
           provinceNameList.push_back(itor.key());
       }
       return provinceNameList;
}

//获取城市列表
QList<QString> Nationlity::getCityName(QString &province)
{
    auto itor = m_ChinaCityInfo.find(province);
        QList<CityInfo> cityList = itor.value();
        QList<QString> cityNameList;
        cityNameList.clear();
        for (int i = 0; i < cityList.count(); ++i)
        {
            cityNameList.push_back(cityList.at(i).cityName);
        }

        return cityNameList;
}

void Nationlity::findKeyWordResults(QListWidget *listwidget, QString keyword)
{
    if(listwidget->count() == 0) return;
    keyword.remove(QRegExp("\\s"));
    if(keyword.isEmpty())
    {
        for(int i = 0; i < listwidget->model()->rowCount(); i++)
            listwidget->setRowHidden(i,false);

    }
    else
    {
        for(int i = 0; i < listwidget->model()->rowCount(); i++)
        {
            listwidget->setRowHidden(i,true);
            QString curname = "";
            QAbstractItemModel *model = listwidget->model();
            QModelIndex index;
            for(int j = 0; j < listwidget->model()->columnCount(); j++)
            {
                index = model->index(i,j);
                curname += model->data(index).toString();
            }
            curname.remove(QRegExp("\\s"));
            if(curname.contains(keyword,Qt::CaseInsensitive)) //CaseSensitive:敏感
               listwidget->setRowHidden(i,false);
        }
    }
}

//获取对应的国家的对应省份
void Nationlity::slot_countryChanged(QString country)
{
    QList<QString> provinceNameList = getProvinceName(country);
    ui->listWidget_province->clear();
    ui->listWidget_province->addItems(provinceNameList);
}

//获取对应的国家的对应省份的对应城市
void Nationlity::slot_provinceChanged(QString province)
{
    QList<QString> cityNameList = getCityName(province);
    ui->listWidget_city->clear();
    ui->listWidget_city->addItems(cityNameList);
}

