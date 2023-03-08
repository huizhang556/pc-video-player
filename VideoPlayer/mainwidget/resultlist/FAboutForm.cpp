#include "FAboutForm.h"
#include "ui_FAboutForm.h"

FAboutForm::FAboutForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FAboutForm)
{
    ui->setupUi(this);
    setFixedHeight(380);
    setMinimumWidth(740);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

FAboutForm::~FAboutForm()
{
    delete ui;
}

void FAboutForm::initWorkUI()
{
    ui->listWidget_fvitems->setViewMode(QListView::IconMode);
    ui->listWidget_fvitems->setMovement(QListView::Static);
    ui->listWidget_fvitems->setResizeMode(QListView::Adjust);
    ui->listWidget_fvitems->setWrapping(false);
    ui->listWidget_fvitems->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_fvitems->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_fvitems->horizontalScrollBar()->setDisabled(true);
    ui->listWidget_fvitems->setOffset(175,-100,8,5,20);
    ui->listWidget_fvitems->setZoomScale(1.1);

    for(int i = 0; i < 17; i++)
    {
        //精选视频列表
//        QString path1 = Global::appDirPath + QString("/pictures/mylike/videos_list2/list_intro%1.png").arg(i);
        QString path2 = Global::appDirPath + QString("/pictures/mylike/videos_list2/list_intro%1.jpg").arg(i);
        MemberVideoItem *itemWidget = new MemberVideoItem(path2,QString(u8"神探狄仁杰之%1").arg(i),QString(u8"再探武朝迷案"),QColor(37, 37, 43));
        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(QSize(175,320));
        ui->listWidget_fvitems->addItem(item);
        ui->listWidget_fvitems->setItemWidget(item,itemWidget);
    }
}

void FAboutForm::handleSignalsAndSlots()
{

}

void FAboutForm::setInstallEventFilter()
{

}
