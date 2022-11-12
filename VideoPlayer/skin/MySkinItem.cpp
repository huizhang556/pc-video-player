#include "MySkinItem.h"
#include "ui_MySkinItem.h"
#include <QDebug>

MySkinItem::MySkinItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MySkinItem)
{
    ui->setupUi(this);
}

MySkinItem::MySkinItem(int x, int y, int w, int h,int type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MySkinItem)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    this->setFixedSize(x,y);
    QIcon icon_close("://images/icon/closehover.png");
    m_closeBtn = new QPushButton(icon_close,"",this);
    m_closeBtn->setObjectName(QString::fromLocal8Bit("m_skinCloseBtn"));
    m_closeBtn->setFlat(true);
    setCloseButtonGeometry(m_closeBtn,x,y,w,h);
    m_closeBtn->hide();

    QIcon icon_check("://images/skin/myskin_checkbtn.png");
    m_checkedBtn = new QPushButton(QIcon(""),"",this);
    m_checkedBtn->setObjectName(QString::fromLocal8Bit("m_skinCheckedBtn"));
    m_checkedBtn->setFlat(true);
    m_checkedBtn->setCheckable(true);//可选
    m_checkedBtn->setChecked(false);
    setCheckedButtonGeometry(m_checkedBtn,x,y,w,h,type);
    m_checkedBtn->hide();//默认隐藏

    connect(m_closeBtn,&QPushButton::clicked,[=](){
        emit sig_closewindow();
        qDebug() << "emit sig_closewindow();";
    });

    connect(m_checkedBtn,&QPushButton::clicked,[=](){
        emit sig_checkedStatus();
    });
}


MySkinItem::~MySkinItem()
{
    delete ui;
    delete m_closeBtn;
    delete m_checkedBtn;
}

void MySkinItem::setSkinPicture(QString path)
{
    QPixmap pix(path);
    pix.scaled(this->width(),this->height(),Qt::KeepAspectRatio);//保持缩放比例
    ui->label_skin->setPixmap(pix);
    ui->label_skin->setScaledContents(true);//图片自适应
}


bool MySkinItem::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::Enter)
    {
        m_closeBtn->show();
        m_checkedBtn->show();
    }
    else if(event->type() == QEvent::Leave && !m_checkedBtn->isChecked())//如果没有checked,则hide
    {
        m_closeBtn->hide();
        m_checkedBtn->hide();
    }
    return QWidget::eventFilter(watched,event);
}

/*设置close按钮位置*/
bool MySkinItem::setCloseButtonGeometry(QPushButton *btn, int x, int y, int w, int h)
{
    btn->setGeometry(x-20,0,20,20);//固定大小
    return true;
}

/*设置checked按钮位置*/
bool MySkinItem::setCheckedButtonGeometry(QPushButton *btn, int x, int y, int w, int h, int type)
{
    //三种不同的位置
    if(type == 0)
    {
        btn->setGeometry(x/2 -w/2,y/2-h/2,w,h);//固定大小10
    }
    else if(type == 1)
    {
        btn->setGeometry(x-w-5,y-20-10,w,h);//固定大小20
    }
    else  if(type == 2)
    {
        btn->setGeometry(x-w-5,y-30-10,w,h);//固定大小30
    }
    return true;
}
