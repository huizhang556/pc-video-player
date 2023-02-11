#include "MaskLabel.h"
#include "ui_MaskLabel.h"

MaskLabel::MaskLabel(QWidget *parent) :
    QLabel(parent),
    m_isMask(false),
    ui(new Ui::MaskLabel)
{
    ui->setupUi(this);
    ui->widget_mask->installEventFilter(this);
}

MaskLabel::~MaskLabel()
{
    delete ui;
}

void MaskLabel::slot_setMask()
{
    m_isMask = true;
    ui->widget_mask->setStyleSheet("background-color: rgba(113, 200, 15,0.8);"
                                   "border-image: url(:/images/bgpic/update_QR.png);");
}

void MaskLabel::slot_clearMask()
{
    m_isMask = false;
    ui->widget_mask->setStyleSheet("background-color: rgba(113, 200, 15,0.0);");
}

bool MaskLabel::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->widget_mask && event->type() == QEvent::MouseButtonPress)
        emit sig_item_clicked();
    return QWidget::eventFilter(watched,event);
}

//void MaskLabel::paintEvent(QPaintEvent *event)
//{

//}

