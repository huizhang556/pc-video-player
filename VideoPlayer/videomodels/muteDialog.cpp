#include "muteDialog.h"
#include "ui_muteDialog.h"
#include <QDebug>
#include <QPainterPath>

//muteDialog* muteDialog::m_pInstance = NULL;

muteDialog::muteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::muteDialog)
{
    ui->setupUi(this);
    this->setFixedSize(40,180);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);//去掉标题栏
    this->setAttribute(Qt::WA_TranslucentBackground);    //重要
    ui->verticalSlider->setRange(0,100);
    ui->verticalSlider->setPageStep(5);
    ui->verticalSlider->setValue(10);
    ui->label_mute->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->label_mute->setText(QString::fromLocal8Bit("10%"));
    //值改变发出带参数信号
    connect(ui->verticalSlider,&QSlider::valueChanged,[=](int val){
        emit sig_SpliderValueChange(val);//player设置声音
    ui->label_mute->setText(QString::number(val)+QString::fromLocal8Bit("%"));
    });
}

muteDialog::~muteDialog()
{
    delete ui;
//    if(m_pInstance != NULL)
//    {
//        delete m_pInstance;
//    }
//    m_pInstance = NULL;
}

void muteDialog::setSpliderValue(int value)
{
    ui->verticalSlider->setValue(value);
}

void muteDialog::slot_setSoundValue(bool add)
{
    int value = ui->verticalSlider->value();
    if(add)
    {
        ui->verticalSlider->setValue(value+5);
    }
    else
    {
        ui->verticalSlider->setValue(value-5);
    }
}

int muteDialog::getSpliderValue()
{
    return ui->verticalSlider->value();
}

//muteDialog* muteDialog::getInstance()
//{
//    if(m_pInstance == NULL)
//    {
//        m_pInstance = new muteDialog();
//    }
//    return m_pInstance;
//}

void muteDialog::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
//    qDebug() << "voice ui leave";
    this->close();

}

/*点击空白消失界面*/
bool muteDialog::event(QEvent *event)
{
    if (event->type() == QEvent::ActivationChange)
        {
            if(QApplication::activeWindow() != this)
            {
                this->close();
            }
        }
    return QWidget::event(event);
}

//绘画
void muteDialog::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
//    QPainterPath path;
//    path.addRoundedRect(0,0,width(),height(),5,5);
//    painter.drawPath(path);
    painter.drawPixmap(0,0,this->width(),this->height()-5,QPixmap(":/images/bgpic/voice_bgpic.png"));//留出5px 三角距离底部的距离
//    QPainterPath path;
//    //设置圆角半径
//    const qreal radius = 10;
//    //设置起点为矩形左上圆角圆心
//    path.moveTo(this->rect().topLeft().x() + radius, this->rect().topLeft().y() + radius);
//    //绘制圆角 圆弧以外切圆的90度位置为起点，逆时针画圆弧运行90度结束（从12点钟方向 - 9点钟方向）
//    path.arcTo(QRect(this->rect().topLeft(), QSize(radius * 2, radius * 2)), 90, 90);
//    //画圆弧 (3点钟方向 - 12点钟方向)
//    path.arcTo(QRect(QPoint(this->rect().topRight().x() - (radius * 2), this->rect().topRight().y()), QSize(radius * 2, radius * 2)), 0, 90);
//    painter.drawPath(path);
//    painter.save();
}

