#include "TagsMenuItem.h"
#include "ui_TagsMenuItem.h"

#include <QListWidgetItem>

#include <QDebug>

TagsMenuItem::TagsMenuItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagsMenuItem)
{
    ui->setupUi(this);
}

TagsMenuItem::TagsMenuItem(const QString &titleicon, const QString &title, const QStringList &items, QWidget *parent) :
    QWidget(parent),
    m_titleicon(titleicon),
    m_title(title),
    m_items(items),
    ui(new Ui::TagsMenuItem)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();

}

TagsMenuItem::~TagsMenuItem()
{
    delete ui;
}

void TagsMenuItem::initWorkUI()
{
//    ui->listWidget_tags->setViewMode(QListView::IconMode);
    ui->listWidget_tags->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_tags->setResizeMode(QListWidget::Adjust);
    ui->listWidget_tags->setLayoutDirection(Qt::LeftToRight);
    ui->listWidget_tags->setLayoutMode(QListView::SinglePass);
    ui->listWidget_tags->setFlow(QListView::LeftToRight);
    ui->listWidget_tags->setWrapping(true);//自动换行
//    ui->listWidget_tags->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->listWidget_tags->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_tags->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    slot_setTagMenuItemHead(m_titleicon,m_title);//左侧主题
    slot_addTagMenuItem(m_items);//右侧item
}

void TagsMenuItem::handleSignalsAndSlots()
{
    connect(ui->listWidget_tags,&QListWidget::currentTextChanged,[=](QString text){
        emit sig_sendItemTextChanged(text);
    });
}

void TagsMenuItem::slot_setTagMenuItemHead(const QString &iconpath, const QString &title)
{
    ui->pushButton->setIcon(QIcon(iconpath));
    ui->pushButton->setIconSize(QSize(32,32));
    ui->pushButton->setText(title);
//    qDebug() <<QString::fromLocal8Bit("当前主题：%1,当前图标：%2").arg(title).arg(iconpath);
}

void TagsMenuItem::slot_addTagMenuItem(const QStringList &list)
{
    foreach (QString item, list)
    {
        QListWidgetItem *pitem = new QListWidgetItem(QIcon("://images/icon/hot0.png"),item);
        pitem->setSizeHint(QSize(100,48));
        ui->listWidget_tags->addItem(pitem);//采用样式表中的宽高
        //说明：
        //代码不指定宽高，默认使用的是界面放置的宽高。如果后面设置了更大的值，界面会被撑大。
        //但是，设置的值比原来默认的值小，则保持默认值大小，不会被缩小。
    }
}

void TagsMenuItem::setMenuListWidgetHeight(int counts)
{
    int num0 = counts/6;//求商
    int num1 = counts%6;//求余数
    if(num1 == 0 )//整除
        num0 = num0;
    else
        num0 = num0+1;
//    qDebug() << QString::fromLocal8Bit("所占行数：") << num0;
    this->setMinimumHeight(num0*56 - 5);
    m_size = QSize(width(),num0*56 - 5);
}

QSize TagsMenuItem::getMenuListWidgetHeight()
{
    return m_size;
}

bool TagsMenuItem::eventFilter(QObject *watched, QEvent *event)
{
    return QWidget::eventFilter(watched,event);
}
