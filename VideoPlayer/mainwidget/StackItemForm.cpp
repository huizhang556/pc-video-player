#include "StackItemForm.h"
#include "ui_StackItemForm.h"
#include <QDebug>
#include <QPixmap>

StackItemForm::StackItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackItemForm)
{
    ui->setupUi(this);
    this->setFixedHeight(320);
    initWorkUI();
    chandleSignalsAndSlots();
}

StackItemForm::~StackItemForm()
{
    delete ui;
}

void StackItemForm::initWorkUI()
{
    ui->listWidget_reclist->setItemAlignment(Qt::AlignCenter);



    for(int i = 0; i < 10; i++)
    {
        QLabel *label = new QLabel();
        QString path = QString(Global::appDirPath +"/pictures/stackwall/stack%1.png").arg(i);
        QPixmap pix(path);
        label->setPixmap(pix);
        label->setScaledContents(true);//图片自适应
        m_mapLabel.insert(i, label);
    }
    addLabelToStackWidget();
    addCusWidgetToList();
    ui->listWidget_reclist->setCurrentRow(0);
    ui->stackedWidget_itempic->setCurrentIndex(0);//默认显示第一项
}

void StackItemForm::chandleSignalsAndSlots()
{
    //列表与qstackwidget联动
    ui->listWidget_reclist->setMouseTracking(true);//设置鼠标跟踪
    //鼠标进入/离开对应stackwidget切换
    connect(ui->listWidget_reclist,SIGNAL(itemEntered(QListWidgetItem*)),this,SLOT(slot_switchPageToStackWidget(QListWidgetItem*)));
}

void StackItemForm::addLabelToStackWidget()
{
    for(int i = 0; i < m_mapLabel.count(); i++)
    {
        ui->stackedWidget_itempic->insertWidget(i,m_mapLabel[i]);
    }
}

/*添加自定义内容*/
void StackItemForm::addCusWidgetToList()
{
    for(int i = 0; i < 10; i++)
    {
        QListWidgetItem *item = new QListWidgetItem();
        StackItem *sitem = new StackItem();
        sitem->setlistBtn_NameIcon(QString("://images/icon/hot%1.png").arg(i));
        sitem->setlistBtn_NameText(QString::fromLocal8Bit("雪中悍刀行%1").arg(i+1));
        sitem->setlistBtn_IntroText(QString::fromLocal8Bit("胡军联袂领衔主演%1").arg(i+1));
        item->setSizeHint(sitem->size());
        ui->listWidget_reclist->addItem(item);
        ui->listWidget_reclist->setItemWidget(item,sitem);
    }

}

void StackItemForm::slot_switchPageToStackWidget(QListWidgetItem *item)
{
    qDebug() << ui->listWidget_reclist->row(item);
    ui->stackedWidget_itempic->setCurrentIndex(ui->listWidget_reclist->row(item));
}
