#include "CusVerStackWgt.h"
#include "global/Global.h"
#include "mainwidget/subunititems/CusListItem1.h"
#include <QScrollBar>
#include <QListWidgetItem>


CusVerStackWgt::CusVerStackWgt(QWidget *parent) :
    QStackedWidget(parent)
{
    setMinimumSize(MINWINSIZE);
    resize(RESIZESIZE);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

CusVerStackWgt::~CusVerStackWgt()
{

}

void CusVerStackWgt::initWorkUI()
{
    m_rightListWidget = new QListWidget(this);
    m_rightListWidget->setMouseTracking(true);//开启，才能使用itementer信号
    m_rightListWidget->setMinimumSize(RDEFSIZE);//必须指定固定大小，否则无法计算准确位置
    m_rightListWidget->setObjectName(QString::fromUtf8("m_rightListWidget"));

    for(int i = 0; i < 6; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall/stack%1.png").arg(i);
        m_pictureList.insert(i,path);
        CusListItem1 *itemWidget = new CusListItem1(m_itemsTextList.at(i),m_itemsInfoList.at(i));
        QListWidgetItem *item = new QListWidgetItem(m_itemsTextList.at(i));
        item->setSizeHint(QSize(258,53) + QSize(ITEMMARGIN));//留出 1px 探测enter leave
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignCenter);
        m_rightListWidget->addItem(item);
        m_rightListWidget->setItemWidget(item,itemWidget);
        //结合it
        connect(itemWidget,&CusListItem1::sig_itemEnter,[=](){
            m_rightListWidget->setCurrentItem(item);
            this->setCurrentIndex(m_rightListWidget->row(item));
            updateListWidgetGeometry();
        });

    }
//    slot_addToStackPictures(m_pictureList,m_pictureList);
    m_rightListWidget->setCurrentRow(0);//选中第一项
    getItemStackWgt(m_rightListWidget->item(0),"stackedWidget_switch")->setCurrentIndex(1);//切换到index = 1
//    updateGeometry();
}

void CusVerStackWgt::handleSignalsAndSlots()
{
//    connect(m_rightListWidget,&QListWidget::itemEntered,[=](QListWidgetItem *current){
//        qDebug() << QString(u8"右侧列表item进入：")<<current->text();
//        m_rightListWidget->setCurrentItem(current);
//        this->setCurrentIndex(m_rightListWidget->row(current));
//        updateListWidgetGeometry();
//    });


    connect(m_rightListWidget,&QListWidget::currentItemChanged,[=](QListWidgetItem *current,QListWidgetItem *previous){
        if(previous != nullptr)
        {
            qDebug() << QString::fromLocal8Bit("先前的item：")<<previous->text();
            getItemStackWgt(previous,"stackedWidget_switch")->setCurrentIndex(0);
        }
        if(current != nullptr)
        {
            qDebug() << QString::fromLocal8Bit("现在的item:")<<current->text();
            getItemStackWgt(current,"stackedWidget_switch")->setCurrentIndex(1);
        }
    });
}

void CusVerStackWgt::setInstallEventFilter()
{
    this->installEventFilter(this);
    m_rightListWidget->installEventFilter(this);
}

void CusVerStackWgt::slot_addItemToCusVerStackWgt(const QString &picpath)
{
    //添加图片
    QLabel *label_pic = new QLabel(this);//此处需用指针，临时对象不行
    label_pic->setPixmap(QPixmap(picpath));
    label_pic->setScaledContents(true);
    this->insertWidget(this->count(),label_pic);
}

void CusVerStackWgt::slot_addToStackPictures(const QStringList &introduce, const QStringList &list_pic)
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

bool CusVerStackWgt::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && event->type() == QEvent::Resize)
    {
        update_W_H_scale();
        updateListWidgetGeometry();
    }

    return QWidget::eventFilter(watched,event);
}

void CusVerStackWgt::updateListWidgetGeometry()
{
    m_rightListWidget->setGeometry(width()-m_rightListWidget->width()-30,(height()/2 - m_rightListWidget->height()/2),
                                   m_rightListWidget->width(),m_rightListWidget->height());
    m_rightListWidget->raise();
}

void CusVerStackWgt::update_W_H_scale()
{
    if(this->width() > SACLWIDTH)
    {
        this->setMinimumHeight((int)(this->width()*SCALSIZE));
        m_rightListWidget->setFixedSize(QSize((int)(this->width()*RSACLE_W),(int)(this->height()*RSACLE_H)));
        for(int i = 0; i <m_rightListWidget->count(); i++)
        {
            m_rightListWidget->item(i)->setSizeHint(QSize(
                                                    m_rightListWidget->width()-m_rightListWidget->verticalScrollBar()->width()-1,
                                                    (int)((m_rightListWidget->height()-m_rightListWidget->horizontalScrollBar()->height()-1)/6))
                                                    + QSize(ITEMMARGIN)
                                                    );
        }
    }
    else
    {
        this->setMinimumHeight(FIXEDHEIGHT);
        m_rightListWidget->setFixedSize(RDEFSIZE);
        for(int i = 0; i < m_rightListWidget->count(); i++)
        {
            m_rightListWidget->item(i)->setSizeHint(QSize(258,53)+ QSize(ITEMMARGIN));//320/6
        }
    }
}

QStackedWidget *CusVerStackWgt::getItemStackWgt(QListWidgetItem* item, const QString &objname)
{
    QWidget* itemWidget = item->listWidget()->itemWidget(item);
    if(nullptr != itemWidget)
    {
        QStackedWidget *itemStack = itemWidget->findChild<QStackedWidget*>(objname);//可以指定查找范围（最近一级的还是所有的）
        if(nullptr != itemStack)
        return itemStack;
    }
}
