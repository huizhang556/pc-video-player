#include "SelectButtons.h"
#include "ui_SelectButtons.h"

#include <QDebug>

SelectButtons::SelectButtons(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectButtons)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
}

SelectButtons::~SelectButtons()
{
    delete ui;
}

void SelectButtons::initWorkUI()
{
    setFixedHeight(40);
    ui->pushButton_jingxuan->setCheckable(true);
    ui->pushButton_songer->setCheckable(true);
    ui->pushButton_ranking->setCheckable(true);
    ui->pushButton_listsort->setCheckable(true);
    ui->pushButton_zhubo->setCheckable(true);
    ui->pushButton_musiclive->setCheckable(true);
    ui->pushButton_viparea->setCheckable(true);
    ui->pushButton_jingxuan->setChecked(true);

    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->setObjectName(QString::fromLocal8Bit("m_buttonGroup"));
    m_buttonGroup->addButton(ui->pushButton_jingxuan,0);
    m_buttonGroup->addButton(ui->pushButton_songer,1);
    m_buttonGroup->addButton(ui->pushButton_ranking,2);
    m_buttonGroup->addButton(ui->pushButton_listsort,3);
    m_buttonGroup->addButton(ui->pushButton_zhubo,4);
    m_buttonGroup->addButton(ui->pushButton_musiclive,5);
    m_buttonGroup->addButton(ui->pushButton_viparea,6);
    m_buttonGroup->setExclusive(true);

    setSelectButtonText();
}

void SelectButtons::handleSignalsAndSlots()
{

    connect(m_buttonGroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_buttonGroupClicked(QAbstractButton*)));
}

void SelectButtons::setSelectButtonText()
{
    ui->pushButton_jingxuan->setText(QString::fromLocal8Bit("精选推荐"));
    ui->pushButton_songer->setText(QString::fromLocal8Bit("全球歌手"));
    ui->pushButton_ranking->setText(QString::fromLocal8Bit("排行榜"));
    ui->pushButton_listsort->setText(QString::fromLocal8Bit("歌单分类"));
    ui->pushButton_zhubo->setText(QString::fromLocal8Bit("主播电台"));
    ui->pushButton_musiclive->setText(QString::fromLocal8Bit("音乐现场"));
    ui->pushButton_viparea->setText(QString::fromLocal8Bit("会员专区"));
}

void SelectButtons::setSelectButton(int num)
{
    m_buttonGroup->button(num)->setChecked(true);

}

void SelectButtons::addPage()
{

}

void SelectButtons::subPage()
{

}

void SelectButtons::slot_buttonGroupClicked(QAbstractButton *button)
{
    m_curPageIndex = m_buttonGroup->id(button);//标题栏按钮点击也修改m_curPageIndex
    emit sig_buttonItemChanged(m_curPageIndex);
    emit sig_buttonItemChanged(m_buttonGroup->button(m_curPageIndex)->text());
    qDebug() << QString::fromLocal8Bit("当前选择按钮：")<<m_curPageIndex<<endl
             <<m_buttonGroup->button(m_curPageIndex)->text();
}
