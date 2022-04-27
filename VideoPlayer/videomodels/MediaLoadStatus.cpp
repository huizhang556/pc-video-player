#include "MediaLoadStatus.h"
#include "ui_MediaLoadStatus.h"

MediaLoadStatus::MediaLoadStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MediaLoadStatus)
{
    ui->setupUi(this);
}

MediaLoadStatus::~MediaLoadStatus()
{
    delete ui;
}
