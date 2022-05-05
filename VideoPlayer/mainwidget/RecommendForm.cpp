#include "RecommendForm.h"
#include "ui_RecommendForm.h"
#include <QListWidgetItem>
#include <QDebug>

RecommendForm::RecommendForm(QWidget *parent) :
    QWidget(parent),
    m_titleBtnIndex(0),
    m_curPageIndex(0),
    ui(new Ui::RecommendForm)
{
    ui->setupUi(this);
    this->setMinimumHeight(360);
    initWorkUI();
    chandleSignalsAndSlots();
    ui->stackedWidget_recommend->installEventFilter(this);//安装监听器
}

RecommendForm::~RecommendForm()
{
    delete ui;
}

void RecommendForm::initWorkUI()
{
    //左右调节按钮
    m_recLeftBtn = new QPushButton(ui->stackedWidget_recommend);//需要指定父亲
    m_recLeftBtn->setObjectName(QString::fromLocal8Bit("m_recLeftBtn"));
    m_recLeftBtn->setFixedSize(40,40);

    m_recRightBtn = new QPushButton(ui->stackedWidget_recommend);//需要指定父亲
    m_recRightBtn->setObjectName(QString::fromLocal8Bit("m_recRightBtn"));
    m_recRightBtn->setFixedSize(40,40);

    ui->pushButton_jingxuan->setCheckable(true);
    ui->pushButton_songer->setCheckable(true);
    ui->pushButton_ranking->setCheckable(true);
    ui->pushButton_listsort->setCheckable(true);
    ui->pushButton_zhubo->setCheckable(true);
    ui->pushButton_musiclive->setCheckable(true);
    ui->pushButton_viparea->setCheckable(true);
    ui->pushButton_jingxuan->setChecked(true);

    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->setObjectName(QString::fromLocal8Bit("m_buttonGroup"));
    m_buttonGroup->addButton(ui->pushButton_jingxuan,0);
    m_buttonGroup->addButton(ui->pushButton_songer,1);
    m_buttonGroup->addButton(ui->pushButton_ranking,2);
    m_buttonGroup->addButton(ui->pushButton_listsort,3);
    m_buttonGroup->addButton(ui->pushButton_zhubo,4);
    m_buttonGroup->addButton(ui->pushButton_musiclive,5);
    m_buttonGroup->addButton(ui->pushButton_viparea,6);
    m_buttonGroup->setExclusive(true);

    m_picWidget = new PictureWidget();
    m_picWidget->setObjectName(QString::fromLocal8Bit("m_picWidget"));

    addToStackWidgetPage();
    setSelectButtonText();
}

void RecommendForm::chandleSignalsAndSlots()
{
    connect(m_buttonGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_buttonGroupClicked(QAbstractButton*)));
    //标题按钮与stackWidget对应起来
    connect(ui->pushButton_jingxuan,&QPushButton::clicked,[=](){ui->stackedWidget_recommend->setCurrentIndex(0);updataAdjustButton_LR();});
    connect(ui->pushButton_songer,&QPushButton::clicked,[=](){ui->stackedWidget_recommend->setCurrentIndex(1);updataAdjustButton_LR();});
    connect(ui->pushButton_ranking,&QPushButton::clicked,[=](){ui->stackedWidget_recommend->setCurrentIndex(2);updataAdjustButton_LR();});
    connect(ui->pushButton_listsort,&QPushButton::clicked,[=](){ui->stackedWidget_recommend->setCurrentIndex(3);updataAdjustButton_LR();});
    connect(ui->pushButton_zhubo,&QPushButton::clicked,[=](){ui->stackedWidget_recommend->setCurrentIndex(4);updataAdjustButton_LR();});
    connect(ui->pushButton_musiclive,&QPushButton::clicked,[=](){ui->stackedWidget_recommend->setCurrentIndex(5);updataAdjustButton_LR();});
    connect(ui->pushButton_viparea,&QPushButton::clicked,[=](){ui->stackedWidget_recommend->setCurrentIndex(6);updataAdjustButton_LR();});

    //左右调节按钮与stackWidget对应起来
    connect(m_recLeftBtn,&QPushButton::clicked,[=](){qDebug() << "leftbtn";  subPage(); });
    connect(m_recRightBtn,&QPushButton::clicked,[=](){qDebug() << "rightbtn";  addPage(); });
}

void RecommendForm::addToStackWidgetPage()
{

    m_stackItem = new StackItemForm();
    m_stackItem->setObjectName(QString::fromLocal8Bit("m_stackItem"));

    QPushButton *btn2 = new QPushButton("012222222222222222",ui->stackedWidget_recommend);
    QPushButton *btn3 = new QPushButton("013333333333333333",ui->stackedWidget_recommend);
    QPushButton *btn4 = new QPushButton("014444444444444444",ui->stackedWidget_recommend);
    QPushButton *btn5 = new QPushButton("015555555555555555",ui->stackedWidget_recommend);
    QPushButton *btn6 = new QPushButton("016666666666666666",ui->stackedWidget_recommend);

    ui->stackedWidget_recommend->insertWidget(0,m_picWidget);
    ui->stackedWidget_recommend->insertWidget(1,m_stackItem);
    ui->stackedWidget_recommend->insertWidget(2,btn2);
    ui->stackedWidget_recommend->insertWidget(3,btn3);
    ui->stackedWidget_recommend->insertWidget(4,btn4);
    ui->stackedWidget_recommend->insertWidget(5,btn5);
    ui->stackedWidget_recommend->insertWidget(6,btn6);
    ui->stackedWidget_recommend->setCurrentIndex(0);//默认显示0页
}

void RecommendForm::setSelectButtonText()
{
    ui->pushButton_jingxuan->setText(QString::fromLocal8Bit("精选推荐"));
    ui->pushButton_songer->setText(QString::fromLocal8Bit("热播大剧"));
    ui->pushButton_ranking->setText(QString::fromLocal8Bit("排行榜"));
    ui->pushButton_listsort->setText(QString::fromLocal8Bit("歌单分类"));
    ui->pushButton_zhubo->setText(QString::fromLocal8Bit("主播电台"));
    ui->pushButton_musiclive->setText(QString::fromLocal8Bit("音乐现场"));
    ui->pushButton_viparea->setText(QString::fromLocal8Bit("会员专区"));
}

void RecommendForm::setSelectButton(int num)
{
    m_buttonGroup->button(num)->setChecked(true);
}

void RecommendForm::updataAdjustButton_LR()
{
    m_recLeftBtn->setGeometry(0+10,
                           ui->stackedWidget_recommend->height()/2 - m_recLeftBtn->height()/2,
                           m_recLeftBtn->width(),m_recLeftBtn->height());

    m_recRightBtn->setGeometry(ui->stackedWidget_recommend->width()-m_recRightBtn->width() - 10,
                               ui->stackedWidget_recommend->height()/2 - m_recRightBtn->height()/2,
                            m_recRightBtn->width(),m_recRightBtn->height());
    m_recLeftBtn->raise();
    m_recLeftBtn->show();
    m_recRightBtn->raise();
    m_recRightBtn->show();
}

void RecommendForm::slot_buttonGroupClicked(QAbstractButton *button)
{
    m_curPageIndex = m_buttonGroup->id(button);//标题栏按钮点击也修改m_curPageIndex
}

bool RecommendForm::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->stackedWidget_recommend)
    {
        if(event->type() == QEvent::Enter)
        {
            updataAdjustButton_LR();
            m_recLeftBtn->show();
            m_recRightBtn->show();
        }
        else if(event->type() == QEvent::Leave)
        {
            m_recLeftBtn->hide();
            m_recRightBtn->hide();
        }
    }
    return QWidget::eventFilter(watched,event);
}


void RecommendForm::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    updataAdjustButton_LR();//界面大小发生变化调节按钮位置
    emit sig_sizeChange(this->size());
}

void RecommendForm::moveEvent(QMoveEvent *event)
{
//    updataAdjustButton_LR();
}

/*加页数操作*/
void RecommendForm::addPage()
{
    if(++m_curPageIndex > 6)
    {
        m_curPageIndex = 6;
    }
    qDebug() <<"current page num =" << m_curPageIndex;
    showCurrentPage(m_curPageIndex);
    setSelectButton(m_curPageIndex);
    updataAdjustButton_LR();
}

/*减少页数操作*/
void RecommendForm::subPage()
{
    if(--m_curPageIndex < 0)
    {
         m_curPageIndex = 0;
    }
    qDebug() <<"current page num =" << m_curPageIndex;
    showCurrentPage(m_curPageIndex);
    setSelectButton(m_curPageIndex);
    updataAdjustButton_LR();
}

/*显示当前的page*/
void RecommendForm::showCurrentPage(int index)
{
    ui->stackedWidget_recommend->setCurrentIndex(index);
}

