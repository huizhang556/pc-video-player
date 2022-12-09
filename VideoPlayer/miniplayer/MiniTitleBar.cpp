#include "MiniTitleBar.h"
#include "ui_MiniTitleBar.h"

MiniTitleBar::MiniTitleBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MiniTitleBar)
{
    ui->setupUi(this);
}

MiniTitleBar::~MiniTitleBar()
{
    delete ui;
}

void MiniTitleBar::slot_setCurrentTitle(const QString &title)
{

}

void MiniTitleBar::slot_clearTitle()
{

}
