#include "ForbiddenItem.h"

ForbiddenItem::ForbiddenItem(QWidget *parent) :
    QWidget(parent)
{
    initWorkUI();
    handleSignalAndSlot();
    setInstallEventFilter();
}

ForbiddenItem::ForbiddenItem(const QString &icon, const QString &text, QWidget *parent):
    QWidget(parent)
{
    initWorkUI();
    handleSignalAndSlot();
    setInstallEventFilter();
    m_btn_text->setIcon(QIcon(icon));
    m_btn_text->setText(text);
}

ForbiddenItem::~ForbiddenItem()
{

}

void ForbiddenItem::initWorkUI()
{
    m_horLayout = new QHBoxLayout(this);//指定为顶层布局
    m_horLayout->setContentsMargins(2,2,2,2);
    m_horLayout->setSpacing(6);
    m_btn_text = new QPushButton();//图标+文字
    m_btn_text->setFixedSize(200,26);
    m_btn_text->setObjectName(QString::fromUtf8("m_forbidebtn_text"));
    m_btn_remove = new QPushButton();//移除按钮
    m_btn_remove->setFixedSize(26,26);
    m_btn_remove->setIcon(QIcon(":/images/icon/his_delete.png"));
    m_btn_remove->setObjectName(QString::fromUtf8("m_forbidebtn_remove"));
    m_horLayout->addWidget(m_btn_text);
    m_horLayout->addStretch();
    m_horLayout->addWidget(m_btn_remove);
}

void ForbiddenItem::handleSignalAndSlot()
{
    connect(m_btn_remove,&QPushButton::clicked,[=](){
        emit sig_send_remove();//发送删除信号
    });
}

void ForbiddenItem::setInstallEventFilter()
{
    this->installEventFilter(this);
}

bool ForbiddenItem::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
        {
        if(event->type() == QEvent::Enter)
        {
            m_btn_remove->setIcon(QIcon(":/images/icon/his_delete_hover.png"));
//            qDebug() <<QString(u8"forbiden item enter");
        }
        else if(event->type() == QEvent::Leave)
        {
            m_btn_remove->setIcon(QIcon(":/images/icon/his_delete.png"));
//            qDebug() <<QString(u8"forbiden item leave");
        }
    }
    return QWidget::eventFilter(watched,event);
}
