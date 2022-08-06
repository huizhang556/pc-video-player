#include "StackItemForm.h"
#include "ui_StackItemForm.h"
#include <QDebug>
#include <QPixmap>

StackItemForm::StackItemForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StackItemForm)
{
    ui->setupUi(this);
    this->setFixedHeight(360);
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
        QString icon = QString::fromLocal8Bit("://images/icon/hot%1.png").arg(i);
        m_vecicon.insert(i,icon);
    }

    for(int i = 0; i < 10; i++)
    {
        QString title = QString::fromLocal8Bit("黑道往事之风云年%1").arg(i);
        QString intro = QString::fromLocal8Bit("贾玲张小斐联袂出演%1").arg(i);
        m_vectitle.insert(i,title);
        m_vecexplain.insert(i,intro);
    }

    for(int i = 0; i < 10; i++)
    {
        QLabel *label = new QLabel();//显示图片
        QString path = QString(Global::appDirPath +"/pictures/stackwall/stack%1.png").arg(i);
        QPixmap pix(path);
        label->setPixmap(pix);
        label->setScaledContents(true);//图片自适应
        m_mapLabel.insert(i, label);//将label控件放入map容器
    }
    addLabelToStackWidget();//从容其中添加label到stackwidget
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
        sitem->setlistBtn_NameIcon(m_vecicon[i]);
        sitem->setlistBtn_NameText(m_vectitle[i]);
        sitem->setlistBtn_IntroText(m_vecexplain[i]);
        item->setSizeHint(sitem->size());
        ui->listWidget_reclist->addItem(item);
        ui->listWidget_reclist->setItemWidget(item,sitem);
        connect(sitem,&StackItem::sig_currentHoverItem,[=](QString name){
            int index = getQMapKey(m_vectitle,name);
            ui->stackedWidget_itempic->setCurrentIndex(index);
        });
    }
}

void StackItemForm::slot_switchPageToStackWidget(QListWidgetItem *item)
{
    qDebug() << ui->listWidget_reclist->row(item);
    ui->stackedWidget_itempic->setCurrentIndex(ui->listWidget_reclist->row(item));
}

int StackItemForm::getQMapKey(QMap<int, QString> vector,QString text)
{
    for(QMap<int, QString>::iterator iter = vector.begin(); iter!= vector.end(); iter++)
    {
        if(iter.value() == text)
        {
            return iter.key();//找到，返回对应的key
        }
    }
    return -1;//没有找到，返回-1
}
