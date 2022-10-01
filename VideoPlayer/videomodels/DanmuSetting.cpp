#include "DanmuSetting.h"
#include "ui_DanmuSetting.h"

DanmuSetting::DanmuSetting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DanmuSetting)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint | Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setFixedSize(280,340);
}

DanmuSetting::~DanmuSetting()
{
    delete ui;
}

void DanmuSetting::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->close();
}
