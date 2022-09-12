#include "HoverMask.h"
#include <QGraphicsOpacityEffect>


//类外初始化
//HoverMask* HoverMask::m_pInstance  = nullptr;

HoverMask::HoverMask(QWidget *parent) :
    QFrame(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    this->setPalette(Qt::black);
    this->setWindowOpacity(0.4);//设置窗口透明度
//    QGraphicsOpacityEffect *goe = new QGraphicsOpacityEffect();
//    goe->setOpacity(0.2);
//    this->setGraphicsEffect(goe);
//    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setAttribute(Qt::WA_TransparentForMouseEvents,true);//鼠标穿透
}

//HoverMask *HoverMask::getInstance()
//{
//    if(m_pInstance == nullptr)
//    {
//        m_pInstance = new HoverMask();
//    }
//    return m_pInstance;
//}

HoverMask::~HoverMask()
{
//    if(m_pInstance != nullptr)
//    {
//        delete m_pInstance;
//        m_pInstance = nullptr;
//    }
}

void HoverMask::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    emit sig_sendLeave();
}
