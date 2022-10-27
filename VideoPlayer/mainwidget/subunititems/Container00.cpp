#include "Container00.h"
#include "ui_Container00.h"
#include "global/Global.h"
#include "mainwidget/subunititems/SubModules.h"

Container00::Container00(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Container00)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

Container00::Container00(const QString &titleText, QWidget *parent):
    QWidget(parent),
    ui(new Ui::Container00)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    if(!titleText.isEmpty())
        ui->pushButton_title->setText(titleText);
}

Container00::~Container00()
{
    delete ui;
}

void Container00::initWorkUI()
{
    ui->pushButton_left->hide();
    ui->pushButton_right->hide();

    m_videoButton_L = new QPushButton("<",ui->listWidget_container00);
    m_videoButton_L->setObjectName(QString::fromLocal8Bit("m_videoButton_L"));
    m_videoButton_L->setFixedSize(22,30);

    m_videoButton_R = new QPushButton(">",ui->listWidget_container00);
    m_videoButton_R->setObjectName(QString::fromLocal8Bit("m_videoButton_R"));
    m_videoButton_R->setFixedSize(22,30);

    ui->listWidget_container00->installEventFilter(this);
    ui->listWidget_container00->setViewMode(QListView::IconMode);
    ui->listWidget_container00->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_container00->setResizeMode(QListWidget::Adjust);
    ui->listWidget_container00->setWrapping(false);//自动换行 所有itm在一行显示
    ui->listWidget_container00->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_container00->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_container00->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    for(int i = 0; i < 10; i++)
    {
        QString path1 = QString(Global::appDirPath +"/pictures/cusvideoitem/cusvideoitem%1.png").arg(i);
        slot_addItemToListWidget("www.hao123.com",path1,QString(u8"奔跑吧，组团踢馆%1").arg(i+1),QString(u8"奥运冠军组团踢馆%1").arg(i+1));
    }

}

void Container00::handleSignalsAndSlots()
{
    connect(m_videoButton_L,&QPushButton::clicked,[=](){
        int step = ui->listWidget_container00->horizontalScrollBar()->value();
                ui->listWidget_container00->horizontalScrollBar()->setValue(step - ui->listWidget_container00->item(0)->sizeHint().width());
    });

    connect(m_videoButton_R,&QPushButton::clicked,[=](){
        int step = ui->listWidget_container00->horizontalScrollBar()->value();
        ui->listWidget_container00->horizontalScrollBar()->setValue(step + ui->listWidget_container00->item(0)->sizeHint().width());
    });
}

void Container00::slot_addItemToListWidget(const QString& url, const QString& picpath,const QString& info1,const QString& info2)
{
    SubModules *itemWidget = new SubModules(picpath,info1,info2);
    QListWidgetItem *item = new QListWidgetItem(url);
    item->setSizeHint(itemWidget->size());
    ui->listWidget_container00->addItem(item);
    ui->listWidget_container00->setItemWidget(item,itemWidget);

}

bool Container00::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->listWidget_container00)
    {
        if(event->type() == QEvent::Enter)
        {
            updataAdjustButton_LR();
            m_videoButton_L->show();
            m_videoButton_R->show();
        }
        else if(event->type() == QEvent::Enter)
        {
            updataAdjustButton_LR();
            m_videoButton_L->hide();
            m_videoButton_R->hide();
        }
    }
    return QWidget::eventFilter(watched,event);
}

void Container00::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    updataAdjustButton_LR();
}

void Container00::updataAdjustButton_LR()
{
    m_videoButton_L->setGeometry(5,
                           ui->listWidget_container00->height()/2 - m_videoButton_L->height()/2 - 45,
                           m_videoButton_L->width(),m_videoButton_L->height());

    m_videoButton_R->setGeometry(ui->listWidget_container00->width()-m_videoButton_R->width(),
                               ui->listWidget_container00->height()/2 - m_videoButton_R->height()/2 - 45,
                            m_videoButton_R->width(),m_videoButton_R->height());
    m_videoButton_L->raise();
    m_videoButton_L->show();
    m_videoButton_R->raise();
    m_videoButton_R->show();
}
