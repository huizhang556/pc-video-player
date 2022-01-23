#include "VideoBlank.h"
#include "ui_VideoBlank.h"

VideoBlank::VideoBlank(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoBlank)
{
    ui->setupUi(this);
}

VideoBlank::~VideoBlank()
{
    delete ui;
}

void VideoBlank::on_Btn_blank_clicked()
{
    emit sig_openLocalFile();
}
