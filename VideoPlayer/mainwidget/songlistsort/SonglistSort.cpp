#include "SonglistSort.h"
#include "ui_SonglistSort.h"
#include "global/Global.h"

#include <QListWidgetItem>
#include <QScrollBar>
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
    ui->listWidget_markItem->installEventFilter(this);
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

    ui->lineEdit_turnTo->setAlignment(Qt::AlignCenter);

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


    for(int i = 0; i < 100; i++)
    {
        QString path1 = QString(Global::appDirPath +"/pictures/musics/style/music%1.png").arg(i);
        slot_addSongItem("www.hao123.com",path1,QString::fromLocal8Bit("遥远的故事 | 远方的人儿"),QString::fromLocal8Bit("故事中的人%1").arg(i));
    }

    ui->listWidget_markItem->setViewMode(QListView::IconMode);
    ui->listWidget_markItem->setMovement(QListView::Static);//图标不可拖动
    ui->listWidget_markItem->setResizeMode(QListWidget::Adjust);
    ui->listWidget_markItem->setWrapping(true);//自动换行 所有itm在一行显示
    ui->listWidget_markItem->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listWidget_markItem->horizontalScrollBar()->setDisabled(true);
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

void SonglistSort::slot_resetSongListItemInfo(QListWidgetItem *item, const QString &url, const QString &path, const QString &tags, const QString &mark)
{
    TagsItem *itemWidget = (TagsItem*)(ui->listWidget_markItem->itemWidget(item));
    item->setText(url);
    itemWidget->slot_setHeadPicture(path);
    itemWidget->slot_setSongerTages(tags);
    itemWidget->slot_setSongerMark(mark);
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

    if(button->text() == QString::fromLocal8Bit("80后"))
    {
        for(int i = 0; i < 100; i++)
        {
            QListWidgetItem* item = ui->listWidget_markItem->item(i);
            QString path1 = QString(Global::appDirPath +"/pictures/musics/nearly/music%1.png").arg(i);
            slot_resetSongListItemInfo(item,"www.hao123.com",path1,QString::fromLocal8Bit("遥远的故事0 | 写首诗歌唱给远方的人"),QString::fromLocal8Bit("鞠婧祎的小跟班%1").arg(i));
        }
    }
    else if(button->text() == QString::fromLocal8Bit("运动"))
    {
        for(int i = 0; i < 100; i++)
        {
            QListWidgetItem* item = ui->listWidget_markItem->item(i);
            QString path1 = QString(Global::appDirPath +"/pictures/musics/recradio/music%1.png").arg(i);
            slot_resetSongListItemInfo(item,"www.hao123.com",path1,QString::fromLocal8Bit("遥远的故事1 | 写首诗歌唱给远方的人"),QString::fromLocal8Bit("鞠婧祎的小跟班%1").arg(i));
        }
    }
    else if(button->text() == QString::fromLocal8Bit("怀旧"))
    {
        for(int i = 0; i < 100; i++)
        {
            QListWidgetItem* item = ui->listWidget_markItem->item(i);
            QString path1 = QString(Global::appDirPath +"/pictures/musics/recommend/music%1.png").arg(i);
            slot_resetSongListItemInfo(item,"www.hao123.com",path1,QString::fromLocal8Bit("遥远的故事2 | 写首诗歌唱给远方的人"),QString::fromLocal8Bit("鞠婧祎的小跟班%1").arg(i));
        }
    }
    else if(button->text() == QString::fromLocal8Bit("伤感"))
    {
        for(int i = 0; i < 100; i++)
        {
            QListWidgetItem* item = ui->listWidget_markItem->item(i);
            QString path1 = QString(Global::appDirPath +"/pictures/musics/nearly/music%1.png").arg(i);
            slot_resetSongListItemInfo(item,"www.hao123.com",path1,QString::fromLocal8Bit("遥远的故事3 | 写首诗歌唱给远方的人"),QString::fromLocal8Bit("鞠婧祎的小跟班%1").arg(i));
        }
    }
    else if(button->text() == QString::fromLocal8Bit("古风"))
    {
        for(int i = 0; i < 100; i++)
        {
            QListWidgetItem* item = ui->listWidget_markItem->item(i);
            QString path1 = QString(Global::appDirPath +"/pictures/musics/recradio/music%1.png").arg(i);
            slot_resetSongListItemInfo(item,"www.hao123.com",path1,QString::fromLocal8Bit("遥远的故事4 | 写首诗歌唱给远方的人"),QString::fromLocal8Bit("鞠婧祎的小跟班%1").arg(i));
        }
    }
    else if(button->text() == QString::fromLocal8Bit("网络"))
    {
        for(int i = 0; i < 100; i++)
        {
            QListWidgetItem* item = ui->listWidget_markItem->item(i);
            QString path1 = QString(Global::appDirPath +"/pictures/musics/recommend/music%1.png").arg(i);
            slot_resetSongListItemInfo(item,"www.hao123.com",path1,QString::fromLocal8Bit("遥远的故事5 | 写首诗歌唱给远方的人"),QString::fromLocal8Bit("鞠婧祎的小跟班%1").arg(i));
        }
    }
    else
    {
        for(int i = 0; i < 100; i++)
        {
            QListWidgetItem* item = ui->listWidget_markItem->item(i);
            QString path1 = QString(Global::appDirPath +"/pictures/musics/new/music%1.png").arg(i);
            slot_resetSongListItemInfo(item,"www.hao123.com",path1,QString::fromLocal8Bit("遥远的故事6 | 写首诗歌唱给远方的人"),QString::fromLocal8Bit("鞠婧祎的小跟班%1").arg(i));
        }
    }
//    resize(this->width()+1,this->height()+1);//更新界面
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
            if(!ui->toolButton->geometry().contains(this->mapFromGlobal(QCursor::pos())))
            {
                if(ui->toolButton->isChecked())
                {
                    ui->toolButton->setIcon(QIcon("://images/home/toolbutton_next"));
                    ui->toolButton->setChecked(false);
                }
            }

        }
    }

    if(watched == ui->listWidget_markItem)
    {
        if(event->type() == QEvent::Resize)
        {
            resizeListWidgetItemWidget();
        }
    }

    return  QWidget::eventFilter(watched,event);
}

void SonglistSort::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event)
    //    clearAllFocusWidgets();
}

void SonglistSort::resizeListWidgetItemWidget()
{
    int width = ui->listWidget_markItem->width();
    //滚动条宽度默认17
    //最小显示6个item,最大刚好显示10个item
    //6~7 1116~1302 7~8 1302~1488 8~9 1488~1674 9~10 1674~1860
    for(int i = 0; i < ui->listWidget_markItem->count(); i++)
    {
        int avgWidth = calculateItemWidth(width - ui->listWidget_markItem->verticalScrollBar()->width() - 1);
        ui->listWidget_markItem->item(i)->setSizeHint(QSize(avgWidth,avgWidth*SCALE));
//        qDebug() << QString::fromLocal8Bit("动态更新后的item大小：宽度%1，高度%2").arg(avgWidth).arg(avgWidth*SCALE);
    }
}

void SonglistSort::updateMenuGeometry()
{
        int x = ui->toolButton->mapToGlobal(ui->toolButton->pos()).x();
        int y = ui->toolButton->mapToGlobal(ui->toolButton->pos()).y();
        m_tags->setGeometry(x - 15,y + 20,m_tags->width(),m_tags->height());
}

int SonglistSort::calculateItemWidth(int width)
{
//    qDebug() << QString::fromLocal8Bit("传进来列表可用的宽度==") << width;
    //最小显示6个item,最大刚好显示10个item
    //6~7 1116~1302 7~8 1302~1488 8~9 1488~1674 9~10 1674~1860
    if(width < MINSIZE.width()*6)// 1116及其以下 显示6个
    {
        return  MINSIZE.width();
    }
    else if(width < MINSIZE.width()*7)//显示7个
    {
        return  (int)(width/6);
    }
    else if(width < MINSIZE.width()*8)//显示8个
    {
        return  (int)(width/7);
    }
    else if(width < MINSIZE.width()*9)//显示9个
    {
        return  (int)(width/8);
    }
    else if(width < MINSIZE.width()*10)//显示10个
    {
        return  (int)(width/9);
    }
    else if(width < MINSIZE.width()*11)//显示10个
    {
        return  (int)(width/10);
    }
}
