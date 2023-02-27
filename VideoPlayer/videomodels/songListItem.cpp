#include "songListItem.h"
#include "ui_songListItem.h"

songListItem::songListItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::songListItem)
{
    ui->setupUi(this);
    setFixedHeight(28);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

songListItem::songListItem(const QString &filepath, QWidget *parent):
    QWidget(parent),
    m_name(filepath),
    ui(new Ui::songListItem)
{
    ui->setupUi(this);
    setFixedHeight(28);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
    setItemName();

}

songListItem::~songListItem()
{
    delete ui;
}

void songListItem::initWorkUI()
{
    ui->pushButton_like->setCheckable(true);
    ui->pushButton_like->setChecked(false);
    ui->stackedWidget_add->setCurrentWidget(ui->pageadd2);
    ui->stackedWidget_ctrl->setCurrentWidget(ui->stack_page2);//默认显示2
}

void songListItem::handleSignalsAndSlots()
{
    connect(ui->pushButton_sname,&QPushButton::clicked,[=](){
        emit sig_item_selected(ui->pushButton_sname->text());
    });

    connect(ui->pushButton_like,&QPushButton::clicked,[=](bool checked){
        ui->pushButton_like->setChecked(checked);
    });

    connect(ui->pushButton_add,&QPushButton::clicked,[=](){
        emit sig_item_addtolist();
    });

}

void songListItem::setInstallEventFilter()
{
    this->installEventFilter(this);
}

bool songListItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Enter)
        {
            ui->stackedWidget_add->setCurrentWidget(ui->pageadd1);
            ui->stackedWidget_ctrl->setCurrentWidget(ui->stack_page1);
        }
        else if(event->type() == QEvent::Leave)
        {
            ui->stackedWidget_add->setCurrentWidget(ui->pageadd2);
            ui->stackedWidget_ctrl->setCurrentWidget(ui->stack_page2);
        }
    }
    return QWidget::eventFilter(watched,event);
}

void songListItem::setItemName()
{
    QString fileIcon;
    QFileInfo fileInfo(m_name);
    QString fileSuffix = fileInfo.suffix();//文件后缀
    QFontMetrics fontMetrisc(ui->pushButton_sname->font());
    QString text = fontMetrisc.elidedText(fileInfo.fileName(),Qt::ElideRight,110,0);
    ui->pushButton_sname->setText(text);
    ui->pushButton_sname->setToolTip(fileInfo.fileName());

    //判断一下文件类型，加载不同图标
    if(fileSuffix == "mp4")//返回的是mp4,而非 .mp4
    {
        fileIcon = QString(":/images/icon/video.png");//视频
    }
    else if(fileSuffix == "mp3")
    {
        fileIcon = QString(":/images/icon/mp3.png");//音乐
    }
    else if(fileSuffix == "flv")
    {
        fileIcon = QString(":/images/icon/video.png");//视频
    }
    else if(fileSuffix == "aac")
    {
        fileIcon = QString(":/images/icon/mp3.png");//音乐
    }
    else//后面有需要还可以添加文件类型判断
    {
        fileIcon = QString(":/images/icon/video.png");//视频
    }
    ui->label_type->setPixmap(QPixmap(fileIcon));
    ui->label_type->setScaledContents(true);
}
