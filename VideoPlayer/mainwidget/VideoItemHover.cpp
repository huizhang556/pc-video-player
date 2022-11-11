#include "VideoItemHover.h"
#include "ui_VideoItemHover.h"

VideoItemHover::VideoItemHover(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoItemHover)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
}

VideoItemHover::~VideoItemHover()
{
    delete ui;
}

void VideoItemHover::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->close();
}
