#include "SynopsisForm.h"
#include "ui_SynopsisForm.h"

SynopsisForm::SynopsisForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SynopsisForm)
{
    ui->setupUi(this);
    setFixedHeight(285);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

SynopsisForm::~SynopsisForm()
{
    delete ui;
}

void SynopsisForm::initWorkUI()
{
    ui->listWidget_dramalist->setViewMode(QListView::IconMode);
    ui->listWidget_dramalist->setMovement(QListView::Static);
    ui->listWidget_dramalist->setResizeMode(QListView::Adjust);
    ui->listWidget_dramalist->setWrapping(true);
    ui->listWidget_dramalist->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget_dramalist->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->textBrowser_intro->setContextMenuPolicy(Qt::NoContextMenu);
    ui->textBrowser_intro->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textBrowser_intro->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for(int i = 0; i < 30; i++)
    {
        QListWidgetItem *item = new QListWidgetItem(QString(u8"%1集").arg(i+1));
        item->setSizeHint(QSize(50,50));
        ui->listWidget_dramalist->addItem(item);
    }
}

void SynopsisForm::handleSignalsAndSlots()
{

}

void SynopsisForm::setInstallEventFilter()
{

}
