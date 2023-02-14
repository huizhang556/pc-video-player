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
//    m_isMask = true;
//    this->setStyleSheet("border: 4px solid rgba(0, 255, 0,1.0);"
//                        "border-radius: 3px;");
//    ui->widget_mask->setStyleSheet("background-color: rgba(113, 200, 15,0.8);"
//                                   "border-image: url(:/images/bgpic/update_QR.png);");
//    this->setProperty("ismask",true);
//    this->style()->polish(this);
    ui->widget_mask->setProperty("ismask",true);
    ui->widget_mask->style()->polish(ui->widget_mask);
}

void MaskLabel::slot_clearMask()
{
//    m_isMask = false;
//    this->setStyleSheet("border: 4px solid rgba(54, 175, 251,0.5);"
//                        "border-radius: 3px;");
//    ui->widget_mask->setStyleSheet("background-color: rgba(113, 200, 15,0.0);");
//    this->setProperty("ismask",false);
//    this->style()->polish(this);
    ui->widget_mask->setProperty("ismask",false);
    ui->widget_mask->style()->polish(ui->widget_mask);
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

