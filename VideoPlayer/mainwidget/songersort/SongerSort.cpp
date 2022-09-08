#include "SongerSort.h"
#include "ui_SongerSort.h"
#include "mainwidget/songersort/SongItem.h"


#include <QAbstractButton>
#include <QListWidgetItem>
#include <QDebug>

SongerSort::SongerSort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SongerSort)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();

    for(int i = 0; i < 50; i++)
    {
        slot_addSongItem("","",QString::fromLocal8Bit("凤凰传奇"),"1000+");
    }
}

SongerSort::~SongerSort()
{
    delete ui;
}

void SongerSort::initWorkUI()
{
    m_buttonGroup1 = new QButtonGroup(this);
    m_buttonGroup2 = new QButtonGroup(this);
    m_buttonGroup3 = new QButtonGroup(this);
    m_buttonGroup4 = new QButtonGroup(this);

    m_buttonGroup1->addButton(ui->pushButton_all0,0);
    m_buttonGroup1->addButton(ui->pushButton_huayu,1);
    m_buttonGroup1->addButton(ui->pushButton_oumei,2);
    m_buttonGroup1->addButton(ui->pushButton_hanguo,3);
    m_buttonGroup1->addButton(ui->pushButton_riben,4);
    m_buttonGroup1->setExclusive(true);
    for(int i = 0; i < 5; i++)
    {
        m_buttonGroup1->button(i)->setCheckable(true);
    }
    ui->pushButton_all0->setChecked(true);

    m_buttonGroup2->addButton(ui->pushButton_all1,0);
    m_buttonGroup2->addButton(ui->pushButton_man,1);
    m_buttonGroup2->addButton(ui->pushButton_woman,2);
    m_buttonGroup2->addButton(ui->pushButton_zuhe,3);
    m_buttonGroup2->setExclusive(true);
    for(int i = 0; i < 4; i++)
    {
        m_buttonGroup2->button(i)->setCheckable(true);
    }
    ui->pushButton_all1->setChecked(true);

    m_buttonGroup3->addButton(ui->pushButton_all2,0);
    m_buttonGroup3->addButton(ui->pushButton_liuxing,1);
    m_buttonGroup3->addButton(ui->pushButton_dianzi,2);
    m_buttonGroup3->addButton(ui->pushButton_yaogun,3);
    m_buttonGroup3->addButton(ui->pushButton_xiha,4);
    m_buttonGroup3->addButton(ui->pushButton_rock,5);
    m_buttonGroup3->addButton(ui->pushButton_minyao,6);
    m_buttonGroup3->addButton(ui->pushButton_jueshi,7);
    m_buttonGroup3->addButton(ui->pushButton_gudian,8);
    m_buttonGroup3->addButton(ui->pushButton_lading,9);
    m_buttonGroup3->addButton(ui->pushButton_qinyingyue,10);
    m_buttonGroup3->addButton(ui->pushButton_xiangcun,11);
    m_buttonGroup3->addButton(ui->pushButton_landiao,12);
    m_buttonGroup3->setExclusive(true);
    for(int i = 0; i < 13; i++)
    {
        m_buttonGroup3->button(i)->setCheckable(true);
    }
    ui->pushButton_all2->setChecked(true);

    m_buttonGroup4->addButton(ui->pushButton_all3,0);
    m_buttonGroup4->addButton(ui->pushButton_a,1);
    m_buttonGroup4->addButton(ui->pushButton_b,2);
    m_buttonGroup4->addButton(ui->pushButton_c,3);
    m_buttonGroup4->addButton(ui->pushButton_d,4);
    m_buttonGroup4->addButton(ui->pushButton_e,5);
    m_buttonGroup4->addButton(ui->pushButton_f,6);
    m_buttonGroup4->addButton(ui->pushButton_g,7);
    m_buttonGroup4->addButton(ui->pushButton_h,8);
    m_buttonGroup4->addButton(ui->pushButton_i,9);
    m_buttonGroup4->addButton(ui->pushButton_j,10);
    m_buttonGroup4->addButton(ui->pushButton_k,11);
    m_buttonGroup4->addButton(ui->pushButton_l,12);
    m_buttonGroup4->addButton(ui->pushButton_m,13);
    m_buttonGroup4->addButton(ui->pushButton_n,14);
    m_buttonGroup4->addButton(ui->pushButton_o,15);
    m_buttonGroup4->addButton(ui->pushButton_p,16);
    m_buttonGroup4->addButton(ui->pushButton_q,17);
    m_buttonGroup4->addButton(ui->pushButton_r,18);
    m_buttonGroup4->addButton(ui->pushButton_s,19);
    m_buttonGroup4->addButton(ui->pushButton_t,20);
    m_buttonGroup4->addButton(ui->pushButton_u,21);
    m_buttonGroup4->addButton(ui->pushButton_v,22);
    m_buttonGroup4->addButton(ui->pushButton_w,23);
    m_buttonGroup4->addButton(ui->pushButton_x,24);
    m_buttonGroup4->addButton(ui->pushButton_y,25);
    m_buttonGroup4->addButton(ui->pushButton_z,26);
    m_buttonGroup4->addButton(ui->pushButton_other,27);
    m_buttonGroup4->setExclusive(true);
    for(int i = 0; i < 28; i++)
    {
        m_buttonGroup4->button(i)->setCheckable(true);
    }
    ui->pushButton_all3->setChecked(true);

    ui->pushButton_fasthot->setCheckable(true);
    ui->pushButton_fasthot->setChecked(true);

    ui->listWidget_songers->setViewMode(QListView::IconMode);
    ui->listWidget_songers->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_songers->setResizeMode(QListWidget::Adjust);
    ui->listWidget_songers->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_songers->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

}

void SongerSort::handleSignalsAndSlots()
{
    //拉姆达表达式使用传达 信号的时候，信号必须无重载，否则就是用qt4方式
    //地区选择
    connect(m_buttonGroup1,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_emitNationality(QAbstractButton*)));

    //性别选择
    connect(m_buttonGroup2,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_emitSex(QAbstractButton*)));

    //风格选择
    connect(m_buttonGroup3,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_emitStyle(QAbstractButton*)));

    //字母检索
    connect(m_buttonGroup4,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_emitA_to_Z(QAbstractButton*)));

    // 热门
    connect(ui->pushButton_fasthot,&QPushButton::clicked,[=](){
        emit sig_sendHot(ui->pushButton_fasthot->isChecked());
        qDebug() << QString::fromLocal8Bit("飙升/热门当前选择状态：")<<ui->pushButton_fasthot->isChecked();
    });
}

void SongerSort::slot_addSongItem(const QString &url, const QString &path, const QString &name, const QString &count)
{
    SongItem *itemWidget = new SongItem(path,name,count,1);
    QListWidgetItem *item = new QListWidgetItem(url);
    item->setSizeHint(itemWidget->size());
    ui->listWidget_songers->addItem(item);
    ui->listWidget_songers->setItemWidget(item,itemWidget);

    //信号与槽
    connect(itemWidget,&SongItem::sig_sendSonger,[=](){
        emit sig_sendSonger(url);
        qDebug() << QString::fromLocal8Bit("已发送url==>%1").arg(url);
    });
}

void SongerSort::slot_emitNationality(QAbstractButton *button)
{
    emit sig_sendNationality(button->text());
    qDebug() <<QString::fromLocal8Bit("当前选择的国籍：%1").arg(button->text());
}

void SongerSort::slot_emitSex(QAbstractButton *button)
{
    emit sig_sendSex(button->text());
    qDebug() <<QString::fromLocal8Bit("当前选择的性别：%1").arg(button->text());
}

void SongerSort::slot_emitStyle(QAbstractButton *button)
{
    emit sig_sendStyle(button->text());
    qDebug() <<QString::fromLocal8Bit("当前选择的风格：%1").arg(button->text());
}

void SongerSort::slot_emitA_to_Z(QAbstractButton *button)
{
    emit sig_sendA_to_Z(button->text());
    qDebug() <<QString::fromLocal8Bit("当前选择的字母：%1").arg(button->text());
}
