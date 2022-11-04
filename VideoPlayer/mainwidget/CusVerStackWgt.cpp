#include "CusVerStackWgt.h"
#include "global/Global.h"

#include <QListWidgetItem>


CusVerStackWgt::CusVerStackWgt(QWidget *parent) :
    QStackedWidget(parent)
{
    setMinimumWidth(1160);//布局撑不开
    setFixedHeight(360);
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
    m_rightListWidget->setFixedWidth(260);
    m_rightListWidget->setFixedHeight(320);//必须指定固定大小，否则无法计算准确位置
    m_rightListWidget->setObjectName(QString::fromUtf8("m_rightListWidget"));

    for(int i = 0; i < 6; i++)
    {
        QString path = Global::appDirPath + QString("/pictures/stackwall/stack%1.png").arg(i);
        m_pictureList.insert(i,path);
        QListWidgetItem *item = new QListWidgetItem(QString(u8"长津湖%1水门桥").arg(i+1));
        item->setSizeHint(QSize(258,53));//320/6
        item->setTextAlignment(Qt::AlignLeft | Qt::AlignCenter);
        m_rightListWidget->addItem(item);
    }
//    slot_addToStackPictures(m_pictureList,m_pictureList);
    m_rightListWidget->setCurrentRow(0);
//    updateGeometry();
}

void CusVerStackWgt::handleSignalsAndSlots()
{
    connect(m_rightListWidget,&QListWidget::itemEntered,[=](QListWidgetItem *current){
        m_rightListWidget->setCurrentItem(current);
        this->setCurrentIndex(m_rightListWidget->row(current));
        updateListWidgetGeometry();
    });
//    connect(m_rightListWidget,&QListWidget::currentItemChanged,[=](QListWidgetItem *current,QListWidgetItem *previous){
//        if(previous != nullptr)
//        {
//            qDebug() << QString::fromLocal8Bit("先前的item：")<<previous->text();
//            current->setSizeHint(QSize(300,30));
//        }
//        if(current != nullptr)
//        {
//            qDebug() << QString::fromLocal8Bit("现在的item:")<<current->text();
//            current->setSizeHint(QSize(300,80));
//        }
//    });
}

void CusVerStackWgt::setInstallEventFilter()
{
    this->installEventFilter(this);
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
        qDebug() << "cusVerstackedwidget resized";
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
