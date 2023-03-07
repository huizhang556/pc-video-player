#include "FUserForm.h"
#include "ui_FUserForm.h"

FUserForm::FUserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FUserForm)
{
    ui->setupUi(this);
    setFixedHeight(285);
    setMinimumWidth(740);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

FUserForm::~FUserForm()
{
    delete ui;
}

void FUserForm::initWorkUI()
{
    ui->listWidget_fitems->setViewMode(QListView::IconMode);
    ui->listWidget_fitems->setMovement(QListView::Static);
    ui->listWidget_fitems->setResizeMode(QListView::Adjust);
    ui->listWidget_fitems->setWrapping(false);
    ui->listWidget_fitems->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_fitems->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_fitems->horizontalScrollBar()->setDisabled(true);
    ui->listWidget_fitems->setOffset(140,-100,5,8,35);
    ui->listWidget_fitems->setZoomScale(1.2);

    ui->pushButton_watched->setCheckable(true);
    ui->pushButton_watched->setChecked(false);
    ui->pushButton_watched->setText(QString(u8"关注"));

    for(int i = 0; i < 10; i++)
    {
        QString path1 = QString(Global::appDirPath +"/pictures/cusvideoitem/cusvideoitem%1.png").arg(i);
        slot_addItemToListWidget("www.hao123.com",path1,QString(u8"森林音乐会%1").arg(i+1),QString(u8"天王天后组团踢馆%1").arg(i+1));
    }

}

void FUserForm::handleSignalsAndSlots()
{
    connect(ui->pushButton_watched,&QPushButton::clicked,[=](bool checked){
        if(checked)
        {
            ui->pushButton_watched->setChecked(true);
            ui->pushButton_watched->setText(QString(u8"已关注"));
        }
        else
        {
            ui->pushButton_watched->setChecked(false);
            ui->pushButton_watched->setText(QString(u8"关注"));
        }

    });
}

void FUserForm::setInstallEventFilter()
{

}

void FUserForm::slot_addItemToListWidget(const QString &url, const QString &picpath, const QString &info1, const QString &info2)
{
    SubModules *itemWidget = new SubModules(picpath,info1,info2);
    QListWidgetItem *item = new QListWidgetItem(url);
    item->setSizeHint(QSize(140,150));
    ui->listWidget_fitems->addItem(item);
    ui->listWidget_fitems->setItemWidget(item,itemWidget);
}
