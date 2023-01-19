#include "SelectVideoType.h"
#include "ui_SelectVideoType.h"

SelectVideoType::SelectVideoType(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectVideoType)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground,true);
    resize(836,365);
    initWorkUI();
    handleSignalsAndSlots();
}

SelectVideoType::~SelectVideoType()
{
    delete ui;
}

void SelectVideoType::initWorkUI()
{
    ui->pushButton_expand->setToolTip(QString(u8"展开"));
    ui->pushButton_hiden->setToolTip(QString(u8"收起"));
    ui->widget_sort->hide();
    slot_addSelectTypeItemsToFrame(VSItemType::VIDEO_STYLE,list_videostyle);
    slot_addSelectTypeItemsToFrame(VSItemType::VIDEO_AREA,list_videoarea);
    slot_addSelectTypeItemsToFrame(VSItemType::VIDEO_TYPE,list_videotype);
    slot_addSelectTypeItemsToFrame(VSItemType::VIDEO_YEAR,list_videoyear);
    slot_addSelectTypeItemsToFrame(VSItemType::VIDEO_RANGE,list_videorange);
    slot_addSelectTypeItemsToFrame(VSItemType::VIDEO_FEETYPE,list_videofeetype);
    slot_addSelectTypeItemsToFrame(VSItemType::VIDEO_SORT,list_videosort);
}

void SelectVideoType::handleSignalsAndSlots()
{
    connect(m_buttonGroup0,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        if(!button->text().isEmpty())
        emit sig_selectResult(button->text());
        qDebug() << button->text();
    });

    connect(m_buttonGroup1,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        if(!button->text().isEmpty())
        emit sig_selectResult(button->text());
        qDebug() << button->text();
    });

    connect(m_buttonGroup2,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        if(!button->text().isEmpty())
        emit sig_selectResult(button->text());
        qDebug() << button->text();
    });

    connect(m_buttonGroup3,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        if(!button->text().isEmpty())
        emit sig_selectResult(button->text());
        qDebug() << button->text();
    });

    connect(m_buttonGroup4,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        if(!button->text().isEmpty())
        emit sig_selectResult(button->text());
        qDebug() << button->text();
    });

    connect(m_buttonGroup5,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        if(!button->text().isEmpty())
        emit sig_selectResult(button->text());
        qDebug() << button->text();
    });

    connect(m_buttonGroup6,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        if(!button->text().isEmpty())
        emit sig_selectResult(button->text());
        qDebug() << button->text();
    });

    connect(m_buttonGroup7,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        if(!button->text().isEmpty())
        emit sig_selectResult(button->text());
        qDebug() << button->text();
    });

    //展开按钮
    connect(ui->pushButton_expand,&QPushButton::clicked,[=](){
        slot_setSortHidden(true);
    });

    //收起按钮
    connect(ui->pushButton_hiden,&QPushButton::clicked,[=](){
        slot_setSortHidden(false);
    });
}

void SelectVideoType::slot_addSelectTypeItemsToFrame(VSItemType itemType, const QStringList &list)
{
    switch (itemType) {
    //分类
    case VSItemType::VIDEO_STYLE:
    {
        m_buttonGroup0 = new QButtonGroup(this);
        m_buttonGroup0->setExclusive(true);
        m_buttonGroup1 = new QButtonGroup(this);
        m_buttonGroup1->setExclusive(true);
        QHBoxLayout *m_hbLayout0 = new QHBoxLayout();
        m_hbLayout0->setSpacing(6);
        m_hbLayout0->setContentsMargins(0,0,0,0);
        m_hbLayout0->setMargin(0);
        m_hbLayout0->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Fixed,QSizePolicy::Fixed));

        QHBoxLayout *m_hbLayout1 = new QHBoxLayout();
        m_hbLayout1->setSpacing(6);
        m_hbLayout1->setContentsMargins(0,0,0,0);
        m_hbLayout1->setMargin(0);
        m_hbLayout1->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Fixed,QSizePolicy::Fixed));
        for(int i = 0; i < list.count(); i++)
        {
            QPushButton *button0 = new QPushButton(list.at(i));
            QPushButton *button1 = new QPushButton(list.at(i));

            button0->setFixedSize(BTNSIZE);
            button0->setCheckable(true);

            button1->setFixedSize(BTNSIZE);
            button1->setCheckable(true);

            m_buttonGroup0->addButton(button0,i);
            m_buttonGroup1->addButton(button1,i);

            m_hbLayout0->addWidget(button0);
            m_hbLayout1->addWidget(button1);
        }
        m_hbLayout0->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Expanding,QSizePolicy::Fixed));
        m_hbLayout1->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Expanding,QSizePolicy::Fixed));

        m_buttonGroup0->button(0)->setChecked(true);
        m_buttonGroup1->button(0)->setChecked(true);
        ui->frame_top->setLayout(m_hbLayout0);
        ui->frame_style->setLayout(m_hbLayout1);
    }
        break;
        //全部地区
    case VSItemType::VIDEO_AREA:
    {
        m_buttonGroup2 = new QButtonGroup(this);
        m_buttonGroup2->setExclusive(true);
        QHBoxLayout *m_hbLayout = new QHBoxLayout();
        m_hbLayout->setSpacing(6);
        m_hbLayout->setContentsMargins(0,0,0,0);
        m_hbLayout->setMargin(0);
        m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Fixed,QSizePolicy::Fixed));
        for(int i = 0; i < list.count(); i++)
        {
            QPushButton *button = new QPushButton(list.at(i));
            button->setFixedSize(BTNSIZE);
            button->setCheckable(true);
            m_buttonGroup2->addButton(button,i);
            m_hbLayout->addWidget(button);
        }
        m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Expanding,QSizePolicy::Fixed));
        m_buttonGroup2->button(0)->setChecked(true);
        ui->frame_area->setLayout(m_hbLayout);
    }
        break;
        //全部类型
    case VSItemType::VIDEO_TYPE:
    {
        m_buttonGroup3 = new QButtonGroup(this);
        m_buttonGroup3->setExclusive(true);
        QHBoxLayout *m_hbLayout = new QHBoxLayout();
        m_hbLayout->setSpacing(6);
        m_hbLayout->setContentsMargins(0,0,0,0);
        m_hbLayout->setMargin(0);
        m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Fixed,QSizePolicy::Fixed));
        for(int i = 0; i < list.count(); i++)
        {
            QPushButton *button = new QPushButton(list.at(i));
            button->setFixedSize(BTNSIZE);
            button->setCheckable(true);
            m_buttonGroup3->addButton(button,i);
            m_hbLayout->addWidget(button);
        }
        m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Expanding,QSizePolicy::Fixed));
        m_buttonGroup3->button(0)->setChecked(true);
        ui->frame_type->setLayout(m_hbLayout);
    }
        break;
        //全部年份
    case VSItemType::VIDEO_YEAR:
    {
        m_buttonGroup4 = new QButtonGroup(this);
        m_buttonGroup4->setExclusive(true);
        QHBoxLayout *m_hbLayout = new QHBoxLayout();
        m_hbLayout->setSpacing(6);
        m_hbLayout->setContentsMargins(0,0,0,0);
        m_hbLayout->setMargin(0);
        m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Fixed,QSizePolicy::Fixed));
        for(int i = 0; i < list.count(); i++)
        {
            QPushButton *button = new QPushButton(list.at(i));
            button->setFixedSize(BTNSIZE);
            button->setCheckable(true);
            m_buttonGroup4->addButton(button,i);
            m_hbLayout->addWidget(button);
        }
        m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Expanding,QSizePolicy::Fixed));
        m_buttonGroup4->button(0)->setChecked(true);
        ui->frame_year->setLayout(m_hbLayout);
    }
        break;
        //全部规格
    case VSItemType::VIDEO_RANGE:
    {
        m_buttonGroup5 = new QButtonGroup(this);
        m_buttonGroup5->setExclusive(true);
        QHBoxLayout *m_hbLayout = new QHBoxLayout();
        m_hbLayout->setSpacing(6);
        m_hbLayout->setContentsMargins(0,0,0,0);
        m_hbLayout->setMargin(0);
        m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Fixed,QSizePolicy::Fixed));
        for(int i = 0; i < list.count(); i++)
        {
            QPushButton *button = new QPushButton(list.at(i));
            button->setFixedSize(BTNSIZE);
            button->setCheckable(true);
            m_buttonGroup5->addButton(button,i);
            m_hbLayout->addWidget(button);
        }
        m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Expanding,QSizePolicy::Fixed));
        m_buttonGroup5->button(0)->setChecked(true);
        ui->frame_range->setLayout(m_hbLayout);
    }
        break;
        //付费类型
    case VSItemType::VIDEO_FEETYPE:
    {
        m_buttonGroup6 = new QButtonGroup(this);
        m_buttonGroup6->setExclusive(true);
        QHBoxLayout *m_hbLayout = new QHBoxLayout();
        m_hbLayout->setSpacing(6);
        m_hbLayout->setContentsMargins(0,0,0,0);
        m_hbLayout->setMargin(0);
        m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Fixed,QSizePolicy::Fixed));
        for(int i = 0; i < list.count(); i++)
        {
            QPushButton *button = new QPushButton(list.at(i));
            button->setFixedSize(BTNSIZE);
            button->setCheckable(true);
            m_buttonGroup6->addButton(button,i);
            m_hbLayout->addWidget(button);
        }
        m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Expanding,QSizePolicy::Fixed));
        m_buttonGroup6->button(0)->setChecked(true);
        ui->frame_payfor->setLayout(m_hbLayout);
    }
        break;
        //综合排序
    case VSItemType::VIDEO_SORT:
    {
        m_buttonGroup7 = new QButtonGroup(this);
        m_buttonGroup7->setExclusive(true);
        QHBoxLayout *m_hbLayout = new QHBoxLayout();
        m_hbLayout->setSpacing(6);
        m_hbLayout->setContentsMargins(0,0,0,0);
        m_hbLayout->setMargin(0);
        m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Fixed,QSizePolicy::Fixed));
        for(int i = 0; i < list.count(); i++)
        {
            QPushButton *button = new QPushButton(list.at(i));
            button->setFixedSize(BTNSIZE);
            button->setCheckable(true);
            m_buttonGroup7->addButton(button,i);
            m_hbLayout->addWidget(button);
        }
        m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Expanding,QSizePolicy::Fixed));
        m_buttonGroup7->button(0)->setChecked(true);
        ui->frame_sort->setLayout(m_hbLayout);
    }
        break;

    default:
        break;
    }
}

void SelectVideoType::slot_setSortHidden(bool hide)
{
    if(hide)//展开
    {
        ui->widget_sort->show();
        ui->frame_top->hide();
        ui->pushButton_expand->hide();
    }
    else//隐藏
    {
        ui->widget_sort->hide();
        ui->frame_top->show();
        ui->pushButton_expand->show();
    }
}
