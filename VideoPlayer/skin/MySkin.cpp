#include "MySkin.h"
#include "ui_MySkin.h"
#include <QListWidgetItem>

MySkin::MySkin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MySkin)
{
    ui->setupUi(this);
    installEventFilter(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);//自动消失 Popup
    this->setFixedSize(751,500);//记得留出10px 的滚动条宽度
    initWorkUI();
    chandleSignalAndSlot();
}

MySkin::~MySkin()
{
    delete ui;
}

void MySkin::initWorkUI()
{
    ui->pushButton_desktopmusic->setCheckable(true);
    ui->pushButton_desktopmusic->setChecked(true);
    ui->pushButton_themeskin->setCheckable(true);
    ui->pushButton_bgskin->setCheckable(true);
    ui->pushButton_myselfskin->setCheckable(true);

    btngroup = new QButtonGroup(this);
    btngroup->addButton(ui->pushButton_desktopmusic,0);
    btngroup->addButton(ui->pushButton_themeskin,1);
    btngroup->addButton(ui->pushButton_bgskin,2);
    btngroup->addButton(ui->pushButton_myselfskin,3);
    btngroup->setExclusive(true);
    ui->stackedWidget_skin->setCurrentIndex(0);//显示第一个项目

    ui->listWidget_desktop->setViewMode(QListView::IconMode);//显示模式 图标模式
    ui->listWidget_desktop->setMovement(QListView::Static);//图标不可拖动
//    ui->listWidget_desktop->setIconSize(QSize(110,100));//icon 大小
//    ui->listWidget_desktop->setGridSize( QSize(110, 100));//网格大小
    ui->listWidget_desktop->setResizeMode(QListWidget::Adjust);//图标的调整模式，默认是固定的
    ui->listWidget_desktop->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_desktop->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->listWidget_desktop->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->listWidget_zhuti->setViewMode(QListView::IconMode);//显示模式 图标模式
    ui->listWidget_zhuti->setMovement(QListView::Static);//图标不可拖动
//    ui->listWidget_zhuti->setIconSize(QSize(110,100));//icon 大小
//    ui->listWidget_zhuti->setGridSize( QSize(110, 100));//网格大小
    ui->listWidget_zhuti->setResizeMode(QListWidget::Adjust);//图标的调整模式，默认是固定的
    ui->listWidget_zhuti->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_zhuti->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->listWidget_zhuti->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->listWidget_yuzhi->setViewMode(QListView::IconMode);//显示模式 图标模式
    ui->listWidget_yuzhi->setMovement(QListView::Static);//图标不可拖动
//    ui->listWidget_yuzhi->setIconSize(QSize(110,100));//icon 大小
//    ui->listWidget_yuzhi->setGridSize( QSize(320, 180));//网格大小
    ui->listWidget_yuzhi->setResizeMode(QListWidget::Adjust);//图标的调整模式，默认是固定的
    ui->listWidget_yuzhi->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_yuzhi->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->listWidget_yuzhi->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    ui->listWidget_custom->setViewMode(QListView::IconMode);//显示模式 图标模式
    ui->listWidget_custom->setMovement(QListView::Static);//图标不可拖动
//    ui->listWidget_custom->setIconSize(QSize(110,100));//icon 大小
//    ui->listWidget_custom->setGridSize( QSize(320, 180));//网格大小
    ui->listWidget_custom->setResizeMode(QListWidget::Adjust);//图标的调整模式，默认是固定的
    ui->listWidget_custom->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_custom->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->listWidget_custom->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);



    //桌面皮肤
    for(int i = 0; i < 10; i++)
    {
        MySkinItem *skitem = new MySkinItem(230,140,50,50,0,this);//整体 宽 高 右下角勾选 宽 高
        skitem->setSkinPicture(Global::appDirPath + QString::fromLocal8Bit("/pictures/skin/desktop/desktop%1.png").arg(i));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(250,160));
        ui->listWidget_desktop->addItem(item);
        ui->listWidget_desktop->setItemWidget(item,skitem);
    }

    //主题皮肤
    for(int i = 0; i < 10; i++)
    {
        MySkinItem *skitem = new MySkinItem(230,140,50,50,0,this);//整体 宽 高 右下角勾选 宽 高
        skitem->setSkinPicture(Global::appDirPath + QString::fromLocal8Bit("/pictures/skin/theme/theme%1.png").arg(i));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(250,160));//给skitem 宽高 留出位置20px
        ui->listWidget_zhuti->addItem(item);
        ui->listWidget_zhuti->setItemWidget(item,skitem);
    }

    //背景皮肤
    for(int i = 0; i < 10; i++)
    {
        MySkinItem *skitem = new MySkinItem(230,140,50,50,0,this);//整体 宽 高 右下角勾选 宽 高
        skitem->setSkinPicture(Global::appDirPath + QString::fromLocal8Bit("/pictures/skin/background/bkgd%1.png").arg(i));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(250,160));
        ui->listWidget_yuzhi->addItem(item);
        ui->listWidget_yuzhi->setItemWidget(item,skitem);
    }

    //自己皮肤
    for(int i = 0; i < 10; i++)
    {
        MySkinItem *skitem = new MySkinItem(230,140,50,50,0,this);//整体 宽 高 右下角勾选 宽 高
        skitem->setSkinPicture(Global::appDirPath + QString::fromLocal8Bit("/pictures/skin/myself/mylike%1.png").arg(i));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(250,160));
        ui->listWidget_custom->addItem(item);
        ui->listWidget_custom->setItemWidget(item,skitem);
    }
}

void MySkin::chandleSignalAndSlot()
{
    //遇到有重载（同名信号，参数不同）的信号，需要明确指出具体的参数
    connect(btngroup,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(switchButtonToStackWidget(QAbstractButton*)));
}


bool MySkin::eventFilter(QObject *watch, QEvent *event)
{
//    if(watch ==  this)
//    {
//        if(event->type() == QEvent::Leave)
//        {
//            this->close();
//        }
//    }

    return QDialog::eventFilter(watch,event);
}

void MySkin::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
   QPoint winPos = this->pos();//界面位置
    QPoint nowPos = event->globalPos();//鼠标位置
    m_mvPos = nowPos - winPos;
}

void MySkin::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    this->move(event->globalPos() - m_mvPos);
}

//关闭按钮
void MySkin::on_pushButton_close_clicked()
{
    this->close();
}

void MySkin::switchButtonToStackWidget(QAbstractButton *button)
{
    int num = btngroup->id(button);
    ui->stackedWidget_skin->setCurrentIndex(num);
}
