#include "SwitchButtons.h"
#include "ui_SwitchButtons.h"
#include "global/Global.h"

SwitchButtons::SwitchButtons(QWidget *parent) :
    QWidget(parent),
    m_allCounts(5),
    m_curIndex(0),
    ui(new Ui::SwitchButtons)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    initWorkUI();
    handleSignalsAndSlots();
    setInstallEventFilter();
}

SwitchButtons::~SwitchButtons()
{
    delete ui;
}

void SwitchButtons::initWorkUI()
{
    m_buttonGroup1 = new QButtonGroup(this);
    m_buttonGroup1->addButton(ui->pushButton_selet1,0);
    m_buttonGroup1->addButton(ui->pushButton_selet2,1);
    m_buttonGroup1->addButton(ui->pushButton_selet3,2);
    m_buttonGroup1->addButton(ui->pushButton_selet4,3);
    m_buttonGroup1->addButton(ui->pushButton_selet5,4);
    m_buttonGroup1->addButton(ui->pushButton_selet6,5);
    m_buttonGroup1->setExclusive(true);

}

void SwitchButtons::handleSignalsAndSlots()
{
    connect(m_buttonGroup1,QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),this,[&](QAbstractButton* button, bool status){
//        qDebug() << m_buttonGroup1->id(button);
    });

//    connect(m_buttonGroup1,QOverload<int, bool>::of(&QButtonGroup::buttonToggled),this,[&](int index, bool status){
//        slot_setCheckedButton(index);
//    });

    connect(Global::getInstance(),&Global::sig_sendGlobalTimeOut,[=](){
        m_curIndex++;
        if(m_curIndex  == m_allCounts)//等于最后一页，显示最后一页
        {
            slot_setCheckedButton(m_allCounts);
        }
        else if(m_curIndex  > m_allCounts)//大于最后一页，显示第一页
        {
            slot_setCheckedButton(0);
            m_curIndex = 0;
        }
        else
        {
            slot_setCheckedButton(m_curIndex);
        }
        emit sig_sendButtonNumber(m_curIndex);//对外发送信号
//        qDebug() <<QString(u8"计算过后的索引：%1").arg(m_curIndex);
    });
}

void SwitchButtons::setInstallEventFilter()
{
    for(int i = 0; i < 6; i++)
    {
        m_buttonGroup1->button(i)->setCheckable(true);
        m_buttonGroup1->button(i)->installEventFilter(this);
    }
    slot_setCheckedButton(0);//默认 选中第一个（索引为0）
}

void SwitchButtons::slot_setHoverButton(int index)
{
    emit sig_sendButtonNumber(index);//对外发送信号
    m_curIndex = index;
}

void SwitchButtons::slot_setCheckedButton(int index)
{
    m_buttonGroup1->button(index)->setChecked(true);
    m_buttonGroup1->button(index)->setFixedWidth(46);
    slot_setUNCheckedButton();
////  setSingleShot();//单次定时
//    m_countDownTimer->stop();//先暂停
//    m_countDownTimer->setInterval(3000);//重新填装定时
//    m_countDownTimer->start(); //再重启定时器
}

void SwitchButtons::slot_setUNCheckedButton()
{
    for(int i = 0; i < 6; i++)
    {
        if(!m_buttonGroup1->button(i)->isChecked())
        {
            m_buttonGroup1->button(i)->setFixedWidth(36);
        }
    }
}

bool SwitchButtons::eventFilter(QObject *watched, QEvent *event)
{
    for(int i = 0; i < 6; i++)
    {
        if(watched == m_buttonGroup1->button(i))
        {
            if(event->type() == QEvent::Enter)
            {
                int num = m_buttonGroup1->id(m_buttonGroup1->button(i));
//                qDebug() << QString(u8"第%1个按钮进入！").arg(num);
                slot_setHoverButton(num);
            }
            else if(event->type() == QEvent::Leave)
            {
                int num = m_buttonGroup1->id(m_buttonGroup1->button(i));
//                qDebug() << QString(u8"第%1个按钮离开！").arg(num);
                slot_setUNCheckedButton();
            }
            else if(event->type() == QEvent::MouseButtonPress)
            {
                int num = m_buttonGroup1->id(m_buttonGroup1->button(i));
                qDebug() << QString(u8"第%1个按钮选中！").arg(num);
                slot_setCheckedButton(num);
            }
        }
    }

    return QWidget::eventFilter(watched,event);
}
