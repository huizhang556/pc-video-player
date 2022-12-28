#include "CusListWidget.h"
#include "ui_CusListWidget.h"
#include <QScrollBar>
#include <QDebug>

CusListWidget::CusListWidget(QWidget *parent) :
    QListWidget(parent),
    ui(new Ui::CusListWidget)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    setButtonControl(true);//默认带有左右调节按钮

}

CusListWidget::~CusListWidget()
{
    delete ui;
}

void CusListWidget::initWorkUI()
{
    ui->pushButton_left->hide();
    ui->pushButton_right->hide();

    this->setFrameShape(QFrame::NoFrame);
    m_videoButton_L = new QPushButton("<",this);
    m_videoButton_L->setObjectName(QString::fromLocal8Bit("m_videoButton_L"));
    m_videoButton_L->setFixedSize(22,30);
    m_videoButton_L->hide();

    m_videoButton_R = new QPushButton(">",this);
    m_videoButton_R->setObjectName(QString::fromLocal8Bit("m_videoButton_R"));
    m_videoButton_R->setFixedSize(22,30);
    m_videoButton_R->hide();
}

void CusListWidget::handleSignalsAndSlots()
{
        connect(m_videoButton_L,&QPushButton::clicked,[=](){
            int step = this->horizontalScrollBar()->value();
                    this->horizontalScrollBar()->setValue(step - this->item(0)->sizeHint().width());
        });

        connect(m_videoButton_R,&QPushButton::clicked,[=](){
            int step = this->horizontalScrollBar()->value();
            this->horizontalScrollBar()->setValue(step + this->item(0)->sizeHint().width());
        });

//    connect(ui->pushButton_left,&QPushButton::clicked,[=](){
//        if(this->count() == 0) return;
//        int step = this->horizontalScrollBar()->value();
//        this->horizontalScrollBar()->setValue(step - this->item(0)->sizeHint().width());
//    });

//    connect(ui->pushButton_right,&QPushButton::clicked,[=](){
//        if(this->count() == 0) return;
//        int step = this->horizontalScrollBar()->value();
//        this->horizontalScrollBar()->setValue(step + this->item(0)->sizeHint().width());
//    });
}

void CusListWidget::setInstallEventFilter()
{
    //安装事件过滤器
    this->installEventFilter(this);
}

void CusListWidget::setButtonControl(bool enabled)
{
    if(enabled)
    {
        m_isShow = true;
    }
    else
    {
        m_isShow = false;
    }
}

void CusListWidget::setOffset(int itemwidth, int width_offset)
{
    m_itemWidth = itemwidth;
    m_widthOffset = width_offset;
}

bool CusListWidget::eventFilter(QObject *object, QEvent *event)
{
    if(object == this && event->type() == QEvent::Resize)
    {
        autoResizeListItemsSize();
        updataAdjustButton_LR();
    }
    return QWidget::eventFilter(object,event);
}

void CusListWidget::autoResizeListItemsSize()
{
    if(this->count() == 0)
        return;
    if(this->count() > 0)
    {
        int sizeHint_h = this->item(0)->sizeHint().height();//求默认宽度
        int avgWidth = calAvergeWidth();//求当前平均宽度
        if(avgWidth < m_itemWidth)//平均宽度不能小于默认的宽度
        {
            avgWidth = m_itemWidth;
        }
        if(avgWidth > (int)(m_itemWidth*1.5))
        {
            avgWidth = (int)(m_itemWidth*1.5);
        }
//        qDebug() << QString(u8"第一个ITEM默认高度：%1").arg(sizeHint_h);
//        qDebug() << QString(u8"第一个ITEM求得宽度：%1").arg(avgWidth);
        for(int i = 0; i < this->count(); i++)
        {
            this->item(i)->setSizeHint(QSize(avgWidth,sizeHint_h));
        }
    }
}

int CusListWidget::calAvergeWidth()
{
    int Width = (int)(this->width()-this->verticalScrollBar()->width() - m_widthOffset);
    int sizeHint_w = m_itemWidth;
//    qDebug() << QString(u8"第一个ITEM默认宽度：%1").arg(sizeHint_w);
    int avgWidth = 0;
    if(Width < sizeHint_w*3)//小于3个默认宽度，默认按2个宽度拉升
    {
        avgWidth = (int)(Width/2);
    }
    else if(Width < sizeHint_w*4)
    {
        avgWidth = (int)(Width/3);
    }
    else if(Width < sizeHint_w*5)
    {
        avgWidth = (int)(Width/4);
    }
    else if(Width < sizeHint_w*6)
    {
        avgWidth = (int)(Width/5);
    }
    else if(Width < sizeHint_w*7)
    {
        avgWidth = (int)(Width/6);
    }
    else if(Width < sizeHint_w*8)
    {
        avgWidth = (int)(Width/7);
    }
    else if(Width < sizeHint_w*9)
    {
        avgWidth = (int)(Width/8);
    }
    else if(Width < sizeHint_w*10)
    {
        avgWidth = (int)(Width/9);
    }
    else
    {
        avgWidth = sizeHint_w;
    }
    return avgWidth;
}

void CusListWidget::updataAdjustButton_LR()
{
    if(m_isShow)
    {
        m_videoButton_L->setGeometry(5,
                               this->height()/2 - m_videoButton_L->height()/2 - 45,
                               m_videoButton_L->width(),m_videoButton_L->height());

        m_videoButton_R->setGeometry(this->width()-m_videoButton_R->width(),
                                   this->height()/2 - m_videoButton_R->height()/2 - 45,
                                m_videoButton_R->width(),m_videoButton_R->height());
        m_videoButton_L->raise();
        m_videoButton_L->show();
        m_videoButton_R->raise();
        m_videoButton_R->show();
    }
}
