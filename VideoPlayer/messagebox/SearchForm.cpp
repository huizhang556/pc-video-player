#include "SearchForm.h"
#include "ui_SearchForm.h"
#include "messagebox/CMessageBox.h"
#include <QListWidgetItem>
#include <QDebug>

SearchForm::SearchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchForm)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::Popup);//无标题栏 无任务图标 鼠标单击空白自动hide()
    initWorkUi();
    chandleSignalsAndSlot();

}

SearchForm::~SearchForm()
{
    delete ui;
}

void SearchForm::initWorkUi()
{
    ui->listWidget_his1->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_his2->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_hot1->setFocusPolicy(Qt::NoFocus);
    ui->listWidget_hot2->setFocusPolicy(Qt::NoFocus);

    ui->btn_his_delete->setFlat(true);
    ui->btn_hot_more->setFlat(true);
    clearHistoryList();

    QStringList contentList =
    {
        QString(u8"1余生请多指教"),
        QString(u8"2王牌对王牌 第7季"),
        QString(u8"3斗罗大陆"),
        QString(u8"4猎罪图鉴"),
        QString(u8"5陈情令"),
        QString(u8"6中国机长"),
        QString(u8"7追爱家族"),
        QString(u8"8骨语2"),
        QString(u8"9才不要和老板谈恋爱"),
        QString(u8"10雪中悍刀行"),
    };
    slot_addHotRecommendItems(contentList);
}

void SearchForm::chandleSignalsAndSlot()
{
    connect(ui->btn_his_delete,&QPushButton::clicked,[=](){
       CMessageBox message(MessageType::CQuestion,QString(u8"清除提示"),QString(u8"您确定要清除吗？"),QString(u8"确定"),QString(u8"取消"));
       if(message.exec() == QDialog::Accepted)//1
        clearHistoryList();
    });

}


void SearchForm::slot_addHotRecommendItems(const QStringList &str_list)
{
    for(int i = 0; i < str_list.count(); i++)
    {

        if(i%2 == 0)//不是0就是1
        {
            QListWidgetItem *hotItem = new  QListWidgetItem(QIcon("://images/home/songlist_hot.png"),str_list.at(i));
            ui->listWidget_hot1->addItem(hotItem);
        }
        else
        {
            QListWidgetItem *hotItem = new  QListWidgetItem(QIcon("://images/home/songlist_new.png"),str_list.at(i));
            ui->listWidget_hot2->addItem(hotItem);
        }
    }
}

void SearchForm::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    this->hide();
}

void SearchForm::clearHistoryList()
{
    ui->listWidget_his1->clear();
    ui->listWidget_his2->clear();
}

void SearchForm::addHistoryItem(QString his)
{
    if(ui->listWidget_his2->count() > 4)
    {
        clearHistoryList();
    }
    qDebug() << his;
    QListWidgetItem *item =  new QListWidgetItem(his);
    if(ui->listWidget_his1->count() <= 4)
    {
//      item->setSizeHint(QSize());
        ui->listWidget_his1->addItem(item);
    }
    else
    {
        if((ui->listWidget_his2->count() <= 4))
        ui->listWidget_his2->addItem(item);
    }

}

void SearchForm::closeSearchForm()
{
    this->close();
}
