#include "CusStackWidget.h"
#include "global/Global.h"
#include <QDebug>


CusStackWidget::CusStackWidget(QWidget *parent) :
    QStackedWidget(parent)
{
    setMinimumWidth(1160);//布局撑不开
    setFixedHeight(360);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusStackWidget::~CusStackWidget()
{

}

void CusStackWidget::initWorkUI()
{
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->setExclusive(true);
    m_buttonAdd = new QPushButton(">>",this);
    m_buttonAdd->setObjectName(QString(u8"m_buttonAdd"));
    m_buttonSub = new QPushButton("<<",this);
    m_buttonSub->setObjectName(QString(u8"m_buttonSub"));
    m_buttonSub->setFixedSize(BUTTONSIZE);
    m_buttonAdd->setFixedSize(BUTTONSIZE);

    m_bottomFrame = new QFrame(this);
    m_bottomFrame->setFixedHeight(MINHEIGHT+20);
    m_bottomFrame->setObjectName(QString(u8"m_bottomFrame"));

    m_hbLayout = new QHBoxLayout();
    m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Fixed,QSizePolicy::Fixed));

    CusPushButton   *button0 = new CusPushButton(QString(u8"动漫"),0);
    CusPushButton   *button1 = new CusPushButton(QString(u8"综艺"),1);
    CusPushButton   *button2 = new CusPushButton(QString(u8"少儿"),2);
    CusPushButton   *button3 = new CusPushButton(QString(u8"影视"),3);
    CusPushButton   *button4 = new CusPushButton(QString(u8"相声"),4);
    CusPushButton   *button5 = new CusPushButton(QString(u8"音乐"),5);
    CusPushButton   *button6 = new CusPushButton(QString(u8"游戏"),6);
    CusPushButton   *button7 = new CusPushButton(QString(u8"直播"),7);
    CusPushButton   *button8 = new CusPushButton(QString(u8"戏曲"),8);
    CusPushButton   *button9 = new CusPushButton(QString(u8"评书"),9);

    connect(button0,SIGNAL(sig_buttonHover(int)),this,SLOT(slot_setCurrentIndex(int)));
    connect(button1,SIGNAL(sig_buttonHover(int)),this,SLOT(slot_setCurrentIndex(int)));
    connect(button2,SIGNAL(sig_buttonHover(int)),this,SLOT(slot_setCurrentIndex(int)));
    connect(button3,SIGNAL(sig_buttonHover(int)),this,SLOT(slot_setCurrentIndex(int)));
    connect(button4,SIGNAL(sig_buttonHover(int)),this,SLOT(slot_setCurrentIndex(int)));
    connect(button5,SIGNAL(sig_buttonHover(int)),this,SLOT(slot_setCurrentIndex(int)));
    connect(button6,SIGNAL(sig_buttonHover(int)),this,SLOT(slot_setCurrentIndex(int)));
    connect(button7,SIGNAL(sig_buttonHover(int)),this,SLOT(slot_setCurrentIndex(int)));
    connect(button8,SIGNAL(sig_buttonHover(int)),this,SLOT(slot_setCurrentIndex(int)));
    connect(button9,SIGNAL(sig_buttonHover(int)),this,SLOT(slot_setCurrentIndex(int)));

    m_buttonGroup->addButton(button0,0);//不写i,默认是负值增加 -1 -2 -3 ...
    m_buttonGroup->addButton(button1,1);
    m_buttonGroup->addButton(button2,2);
    m_buttonGroup->addButton(button3,3);
    m_buttonGroup->addButton(button4,4);
    m_buttonGroup->addButton(button5,5);
    m_buttonGroup->addButton(button6,6);
    m_buttonGroup->addButton(button7,7);
    m_buttonGroup->addButton(button8,8);
    m_buttonGroup->addButton(button9,9);
    m_buttonGroup->setExclusive(true);

    for(int i = 0; i < 10; i++)
    {
        m_buttonGroup->button(i)->setMinimumSize(85,40);
        m_buttonGroup->button(i)->setCheckable(true);
       m_hbLayout->addWidget(m_buttonGroup->button(i));
    }
    m_hbLayout->addSpacerItem(new QSpacerItem(10,20,QSizePolicy::Fixed,QSizePolicy::Fixed));
    m_bottomFrame->setLayout(m_hbLayout);

    for(int i = 0; i < 10; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall/stack%1.png").arg(i);
        m_pictureList.insert(i,path);
    }
    m_counts = m_pictureList.count();

    slot_addToStackPictures(m_pictureList,m_pictureList);
}

void CusStackWidget::handleSignalsAndSlots()
{
    connect(m_buttonGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_setCheckButton(QAbstractButton*)));

    //左移(向左减少)
    connect(m_buttonSub,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"当前索引：")<<m_currentIndex;
        if(--m_currentIndex < 0)
        {
            m_currentIndex = 0;
        }
        qDebug() << QString(u8"当前索引：")<<m_currentIndex;
        this->setCurrentIndex(m_currentIndex);
        m_buttonGroup->button(m_currentIndex)->setChecked(true);
        updateButtonGeometry();
    });

    //右移（向右增加）
    connect(m_buttonAdd,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"当前索引：")<<m_currentIndex;
        if(++m_currentIndex > 9)
        {
            m_currentIndex = 9;
        }
        m_buttonGroup->button(m_currentIndex)->setChecked(true);
        this->setCurrentIndex(m_currentIndex);
        updateButtonGeometry();
    });
}

void CusStackWidget::setInstallEventFilter()
{
    this->installEventFilter(this);
}

bool CusStackWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && event->type() == QEvent::Resize)
    {
        updateButtonGeometry();
    }
    else if(watched == this && event->type() == QEvent::Enter)
    {
        if(m_buttonAdd->isHidden()) m_buttonAdd->show();
        if(m_buttonSub->isHidden()) m_buttonSub->show();
    }
    else if(watched == this && event->type() == QEvent::Leave)
    {
        if(!m_buttonAdd->isHidden()) m_buttonAdd->hide();
        if(!m_buttonSub->isHidden()) m_buttonSub->hide();
    }
    return QWidget::eventFilter(watched,event);
}

void CusStackWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
}

void CusStackWidget::slot_addToStackPictures(const QStringList &introduce, const QStringList &list_pic)
{
    for(int i = 0; i < list_pic.count(); i++)
    {
        //添加图片
        QLabel *label_pic = new QLabel(this);//此处需用指针，临时对象不行
        label_pic->setPixmap(QPixmap(list_pic.at(i)));
        label_pic->setScaledContents(true);
        this->insertWidget(this->count(),label_pic);
    }
}

//点击设置
void CusStackWidget::slot_setCheckButton(QAbstractButton *button)
{
    button->setChecked(true);
    m_currentIndex = m_buttonGroup->id(button);
    this->setCurrentIndex(m_currentIndex);
    updateButtonGeometry();
    qDebug() << button->text()<<m_buttonGroup->id(button);
}

//hover设置
void CusStackWidget::slot_setCurrentIndex(int index)
{
    qDebug() << "button id ="<< index;
    m_currentIndex = index;
    m_buttonGroup->button(m_currentIndex)->setChecked(true);
    this->setCurrentIndex(m_currentIndex);
    updateButtonGeometry();
}

void CusStackWidget::updateButtonGeometry()
{
    m_buttonSub->setGeometry(BUTTONMARGIN,(height()/2 - m_buttonSub->height()/2),m_buttonSub->width(),m_buttonSub->height());
    m_buttonAdd->setGeometry(width()-m_buttonAdd->width()-BUTTONMARGIN,(height()/2 - m_buttonAdd->height()/2),m_buttonAdd->width(),m_buttonAdd->height());
    m_bottomFrame->setGeometry(0,height()-m_bottomFrame->height(),this->width(),m_bottomFrame->height());
    m_buttonSub->raise();
    m_buttonAdd->raise();
    m_bottomFrame->raise();
}
