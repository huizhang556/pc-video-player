#include "SonglistSort.h"
#include "ui_SonglistSort.h"

#include <QListWidgetItem>
#include <QDebug>

SonglistSort::SonglistSort(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SonglistSort)
{
    ui->setupUi(this);
    initWorkUI();
    handleSignalsAndSlots();
    this->installEventFilter(this);
    m_tags->installEventFilter(this);
}

SonglistSort::~SonglistSort()
{
    delete ui;
    delete m_tags;
}

void SonglistSort::initWorkUI()
{
//    m_menu = new QMenu(this);
//    m_menu->setWindowFlags(m_menu->windowFlags() | Qt::FramelessWindowHint);
//    m_menu->setAttribute(Qt::WA_TranslucentBackground,true);//去标题栏，背景透明，才能设置圆角
//    m_menu->setObjectName(QString::fromLocal8Bit("songerlist_menu"));
//    ui->toolButton->setMenu(m_menu);
    m_tags = new TagsMenu();
//    m_action = new QWidgetAction(m_menu);
//    m_action->setDefaultWidget(m_tags);
//    m_menu->addAction(m_action);

    ui->toolButton->setCheckable(true);
    ui->toolButton->setLayoutDirection(Qt::RightToLeft);
    ui->toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->toolButton->setText(QString::fromLocal8Bit("全部分类"));
    ui->toolButton->setIcon(QIcon("://images/home/toolbutton_next.png"));

    ui->pushButton_new->setCheckable(true);
    ui->pushButton_hot->setCheckable(true);
    ui->pushButton_new->setChecked(true);
    m_buttonGroup1 = new QButtonGroup(this);
    m_buttonGroup1->addButton(ui->pushButton_new,0);
    m_buttonGroup1->addButton(ui->pushButton_hot,1);
    m_buttonGroup1->setExclusive(true);

    m_buttonGroup2 = new QButtonGroup(this);
    m_buttonGroup2->addButton(ui->pushButton_mark1,0);
    m_buttonGroup2->addButton(ui->pushButton_mark2,1);
    m_buttonGroup2->addButton(ui->pushButton_mark3,2);
    m_buttonGroup2->addButton(ui->pushButton_mark4,3);
    m_buttonGroup2->addButton(ui->pushButton_mark5,4);
    m_buttonGroup2->addButton(ui->pushButton_mark6,5);
    m_buttonGroup2->setExclusive(true);

    for(int i = 0; i < 6; i++)
    {
        m_buttonGroup2->button(i)->setCheckable(true);
    }


    for(int i = 0; i < 50; i++)
    {
        slot_addSongItem("","",QString::fromLocal8Bit("遥远的故事 | 写首诗歌唱给远方的人"),QString::fromLocal8Bit("鞠婧祎的小跟班"));
    }

    ui->listWidget_markItem->setViewMode(QListView::IconMode);
    ui->listWidget_markItem->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_markItem->setResizeMode(QListWidget::Adjust);
    ui->listWidget_markItem->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_markItem->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
}

void SonglistSort::handleSignalsAndSlots()
{
    connect(m_buttonGroup1,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_emitHotAndNewTags(QAbstractButton*)));
    connect(m_buttonGroup2,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(slot_setCheckedButton(QAbstractButton*)));
    connect(ui->toolButton,&QToolButton::clicked,[=](bool checked){
        if(checked)
        {
            ui->toolButton->setIcon(QIcon("://images/home/toolbutton_up.png"));
            slot_showTagsMenu();
        }
        else
        {
            ui->toolButton->setIcon(QIcon("://images/home/toolbutton_next"));
        }
    });

    connect(m_tags,&TagsMenu::sig_sendCurrentItemText,[=](QString text){
        ui->toolButton->setText(text);
    });

}

void SonglistSort::clearAllFocusWidgets()
{

}

void SonglistSort::slot_addSongItem(const QString &url, const QString &path, const QString &tags, const QString &mark)
{
    TagsItem *itemWidget = new TagsItem(path,tags,mark);
    QListWidgetItem *item = new QListWidgetItem(url);
    item->setSizeHint(itemWidget->size());
    ui->listWidget_markItem->addItem(item);
    ui->listWidget_markItem->setItemWidget(item,itemWidget);

    //信号与槽
    connect(itemWidget,&TagsItem::sig_sendMarkItem,[=](){
        emit sig_sendTags(url);
        qDebug() << QString::fromLocal8Bit("已发送url==>%1").arg(tags);
    });
}

void SonglistSort::slot_emitHotAndNewTags(QAbstractButton *button)
{
    if(button->text() == QString::fromLocal8Bit("最新"))
    {

    }
    else if(button->text() == QString::fromLocal8Bit("最热"))
    {

    }
}

void SonglistSort::slot_setCheckedButton(QAbstractButton *button)
{
    ui->toolButton->setText(button->text());
    emit sig_sendSelectTags(button->text());
}

void SonglistSort::slot_showTagsMenu()
{
    updateMenuGeometry();
    m_tags->show();
}

bool SonglistSort::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == m_tags)
    {
        if(event->type() == QEvent::Hide)
        {
//            if(!ui->toolButton->geometry().contains(this->mapFromGlobal(QCursor::pos())))
//            {
//                emit sig_sendToolButtonFocusOut();
//                qDebug() <<QString::fromLocal8Bit("TOOLBUTTON失去焦点");
//            }
            if(ui->toolButton->isChecked())
            {
                ui->toolButton->setIcon(QIcon("://images/home/toolbutton_next"));
                ui->toolButton->setChecked(false);
            }
        }
    }

    return  QWidget::eventFilter(watched,event);
}

void SonglistSort::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
//    clearAllFocusWidgets();
}

void SonglistSort::updateMenuGeometry()
{
        int x = ui->toolButton->mapToGlobal(ui->toolButton->pos()).x();
        int y = ui->toolButton->mapToGlobal(ui->toolButton->pos()).y();
        m_tags->setGeometry(x - 10,y + 20,m_tags->width(),m_tags->height());
}
