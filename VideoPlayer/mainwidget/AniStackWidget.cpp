#include "AniStackWidget.h"

AniStackWidget::AniStackWidget(QWidget *parent) :
    QStackedWidget(parent)
{
    setMinimumSize(MINWINSIZE);
    resize(RESIZESIZE);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

AniStackWidget::~AniStackWidget()
{

}

void AniStackWidget::initWorkUI()
{
    m_scroListWidget = new SCrollListWidget(this);
    m_scroListWidget->setObjectName(QString::fromUtf8("m_scroListWidget"));
}

void AniStackWidget::handleSignalsAndSlots()
{
    //全局定时器
    connect(Global::getInstance(),&Global::sig_sendGlobalTimeOut,[=](){
        if(++m_curIndex > this->count() - 1)
        {
            m_curIndex = 0;
        }
        this->setCurrentIndex(m_curIndex);
    });

    //小视图带大视图
    connect(m_scroListWidget,&SCrollListWidget::sig_sendCurIndex,[=](int index){
        //这里不判断index是否超出索引
        m_curIndex = index;
        this->setCurrentIndex(m_curIndex);
        autoResize_ScroListWidget_Geometry();//切换一个stack，就要更新
    });

    //大视图带小视图
    connect(this,&AniStackWidget::currentChanged,[=](int index){
        m_scroListWidget->slot_setCurrentItem(index);
        autoResize_ScroListWidget_Geometry();
    });

}

void AniStackWidget::setInstallEventFilter()
{
    this->installEventFilter(this);
}

void AniStackWidget::slot_addItemToCusVerStackWgt(const QString &picpath)
{
    //添加图片
    QLabel *label_pic = new QLabel(this);//此处需用指针，临时对象不行
    label_pic->setPixmap(QPixmap(picpath));
    label_pic->setScaledContents(true);
    this->insertWidget(this->count(),label_pic);
}

void AniStackWidget::slot_addItemToSmallList(const QString &picpath)
{
    m_scroListWidget->slot_addItemToList(picpath);
}

bool AniStackWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Resize)
        {
            update_W_H_scale();//图片宽高缩放
            autoResize_ScroListWidget_Geometry();//右下角小轮播图更新位置
            m_scroListWidget->slot_update_RL_ITEM_geometry(this->size());//右下角小轮播图自己更新宽高，左右箭头位置
        }
    }
    return  QWidget::eventFilter(watched,event);
}

void AniStackWidget::updateSelectedItemStyle()
{

}

void AniStackWidget::update_W_H_scale()
{
    //图片标准大小（1920,670）
    if(this->width() > SACLWIDTH)
    {
        this->setMinimumHeight((int)(this->width()*SCALSIZE));
    }
    else
    {
        this->setMinimumHeight(FIXEDHEIGHT);
    }
}

void AniStackWidget::autoResize_ScroListWidget_Geometry()
{
    m_scroListWidget->move(this->width() - m_scroListWidget->width() - 20,
                           this->height() - m_scroListWidget->height() - 15);
    m_scroListWidget->raise();
//    qDebug() << QString(u8"AniStackWidget自动调整！");
}
