#include "ResultLists.h"
#include "ui_ResultLists.h"

ResultLists::ResultLists(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultLists)
{
    ui->setupUi(this);
    initWorkUI();
    setMinimumSize(QSize(1160,680));
    resize(QSize(1160,680));
    handleSignalsAndSlots();
    setInstallEventFilter();
}

ResultLists::~ResultLists()
{
    delete ui;
}

void ResultLists::initWorkUI()
{
    ui->frame_select->hide();
    ui->pushButton_f_all->setCheckable(true);
    ui->pushButton_f_all->setChecked(true);
    ui->pushButton_f_user->setCheckable(true);
    ui->pushButton_f_user->setChecked(false);
    ui->pushButton_f_filter->setCheckable(true);
    ui->pushButton_f_filter->setChecked(false);

    ui->pushButton_f_filter->setIcon(QIcon("://images/icon/filter_up.png"));
    ui->pushButton_f_filter->setIconSize(QSize(12,12));

    ui->scrollArea_result->setFrameShape(QFrame::NoFrame);//去边框
    ui->scrollArea_user->setFrameShape(QFrame::NoFrame);
    ui->scrollArea_result->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_result->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_user->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_user->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_searchAction = new QAction(QIcon(":/images/icon/sousuohover.png"),"");
    ui->lineEdit_find->setPlaceholderText(u8"请输入搜索内容^_^");
    ui->lineEdit_find->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_find->addAction(m_searchAction,QLineEdit::TrailingPosition);

    m_btnGroup1 = new   QButtonGroup(this);
    m_btnGroup1->addButton(ui->pushButton_f_all,0);
    m_btnGroup1->addButton(ui->pushButton_f_user,1);

    m_btnGroup2 = new   QButtonGroup(this);
    m_btnGroup2->addButton(ui->pushButton_type_zh,0);
    m_btnGroup2->addButton(ui->pushButton_type_new,1);
    m_btnGroup2->addButton(ui->pushButton_type_most,2);
    for(int i = 0; i < 3; i++)
    {
        m_btnGroup2->button(i)->setCheckable(true);
    }
    m_btnGroup2->button(0)->setChecked(true);

    m_btnGroup3 = new   QButtonGroup(this);
    m_btnGroup3->addButton(ui->pushButton_time_all,0);
    m_btnGroup3->addButton(ui->pushButton_time_ten,1);
    m_btnGroup3->addButton(ui->pushButton_time_thirty,2);
    m_btnGroup3->addButton(ui->pushButton_time_sixty,3);
    m_btnGroup3->addButton(ui->pushButton_time_more,4);
    for(int i = 0; i < 5; i++)
    {
        m_btnGroup3->button(i)->setCheckable(true);
    }
    m_btnGroup3->button(0)->setChecked(true);

    m_btnGroup4 = new   QButtonGroup(this);
    m_btnGroup4->addButton(ui->pushButton_day_all,0);
    m_btnGroup4->addButton(ui->pushButton_day_one,1);
    m_btnGroup4->addButton(ui->pushButton_day_week,2);
    m_btnGroup4->addButton(ui->pushButton_day_week_two,3);
    m_btnGroup4->addButton(ui->pushButton_day_month,4);
    for(int i = 0; i < 5; i++)
    {
        m_btnGroup4->button(i)->setCheckable(true);
    }
    m_btnGroup4->button(0)->setChecked(true);

    m_btnGroup5 = new   QButtonGroup(this);
    m_btnGroup5->addButton(ui->pushButton_clarity_all,0);
    m_btnGroup5->addButton(ui->pushButton_clarity_hight,1);
    m_btnGroup5->addButton(ui->pushButton_clarity_moreHight,2);
    m_btnGroup5->addButton(ui->pushButton_clarity_bluehight,3);
    for(int i = 0; i < 4; i++)
    {
        m_btnGroup5->button(i)->setCheckable(true);
    }
    m_btnGroup5->button(0)->setChecked(true);


    for(int i = 0; i < 10; i++)
    {
        ui->verLayout_all->addWidget(new SynopsisForm());
        ui->verLayout_all->addWidget(new FAboutForm());
        ui->verLayout_user->addWidget(new SynopsisForm());
        ui->verLayout_user->addWidget(new FUserForm());
    }

    ui->stackedWidget_switch->setCurrentWidget(ui->page_allresults);
}

void ResultLists::handleSignalsAndSlots()
{
    connect(ui->pushButton_return,&QPushButton::clicked,[=](){
        emit sig_return_home();
    });

    connect(m_searchAction,&QAction::triggered,[=](){
        qDebug() <<QString(u8"搜索的内容：") << ui->lineEdit_find->text();
    });

    connect(ui->lineEdit_find,&QLineEdit::returnPressed,[=](){
         m_searchAction->trigger();
    });

    connect(ui->pushButton_f_all,&QPushButton::clicked,[=](){
        ui->pushButton_f_filter->show();
        ui->frame_select->hide();
        ui->pushButton_f_filter->setChecked(false);
        ui->stackedWidget_switch->setCurrentWidget(ui->page_allresults);
    });

    connect(ui->pushButton_f_user,&QPushButton::clicked,[=](){
        ui->pushButton_f_filter->hide();
        ui->frame_select->hide();
        ui->pushButton_f_filter->setChecked(false);
        ui->stackedWidget_switch->setCurrentWidget(ui->page_users);
    });

    connect(ui->pushButton_f_filter,&QPushButton::clicked,[=](bool checked){
        if(checked)
        {
            ui->pushButton_f_filter->setIcon(QIcon("://images/icon/filter_up.png"));
            ui->frame_select->show();
        }
        else
        {
            ui->pushButton_f_filter->setIcon(QIcon("://images/icon/filter_down.png"));
            ui->frame_select->hide();
        }
    });
}

void ResultLists::setInstallEventFilter()
{

}
