#include "Income.h"
#include "ui_Income.h"

Income::Income(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Income)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventer();
}

Income::~Income()
{
    delete ui;
    delete m_calendar;
    delete m_wgtAction;
    delete m_menuDataTime;
}

void Income::initWorkUI()
{

    //tableWidget_records
    ui->tableWidget_records->setColumnCount(5);//先设置列数
    ui->tableWidget_records->setHorizontalHeaderLabels(m_header);
    ui->tableWidget_records->verticalHeader()->setDefaultSectionSize(26);//垂直固定高度26
    ui->tableWidget_records->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);//垂直表头固定高度
    ui->tableWidget_records->setSelectionBehavior(QAbstractItemView::SelectRows);//只能行选择
    ui->tableWidget_records->setColumnWidth(0,220);
    ui->tableWidget_records->setColumnWidth(1,350);
    ui->tableWidget_records->setColumnWidth(2,150);
    ui->tableWidget_records->setColumnWidth(3,150);
    ui->tableWidget_records->setColumnWidth(4,150);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(3,QHeaderView::Fixed);
    ui->tableWidget_records->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Fixed);

    ui->stackedWidget_showType->setCurrentIndex(0);

    m_calendar = new CusCalendar();
    m_calendar->setObjectName(QString::fromUtf8("m_calendar"));
    m_menuDataTime = new QMenu();//不指定父亲，不继承父亲样式
    m_menuDataTime->setObjectName(QString::fromUtf8("m_menuDataTime"));
    m_wgtAction = new QWidgetAction(m_menuDataTime);
    m_wgtAction->setDefaultWidget(m_calendar);
    m_menuDataTime->addAction(m_wgtAction);
}

void Income::handleSignalsAndSlots()
{
    //显示日历
    connect(ui->pushButton_date1,&QPushButton::clicked,[=](){
        m_menuDataTime->exec(QCursor::pos());
    });

    connect(ui->pushButton_date2,&QPushButton::clicked,[=](){
        m_menuDataTime->exec(QCursor::pos());
    });

    //日期填充
    connect(m_calendar,&CusCalendar::sig_calendar1,[=](QDate date){
        ui->dateEdit_start->setDate(date);
    });

    connect(m_calendar,&CusCalendar::sig_calendar2,[=](QDate date){
        ui->dateEdit_end->setDate(date);
    });

    //结果显示方式选择
    connect(ui->comboBox_showType,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int index){
        ui->stackedWidget_showType->setCurrentIndex(index);
    });
}

void Income::setInstallEventer()
{
    m_menuDataTime->installEventFilter(this);
    ui->dateEdit_start->installEventFilter(this);
    ui->dateEdit_end->installEventFilter(this);
}
