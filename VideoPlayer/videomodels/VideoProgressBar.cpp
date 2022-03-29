#include "VideoProgressBar.h"
#include "ui_VideoProgressBar.h"

VideoProgressBar::VideoProgressBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoProgressBar)
{
    ui->setupUi(this);
}

VideoProgressBar::~VideoProgressBar()
{
    delete ui;
}
