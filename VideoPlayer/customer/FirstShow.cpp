#include "FirstShow.h"
#include <QLayout>

FirstShow::FirstShow(QWidget *parent) :
    QWidget(parent)
{
    initUi();
    setRecomButtonText(QString::fromLocal8Bit("猜你喜欢"),QString::fromLocal8Bit("重磅推荐"));
    QStringList list;
    list << "1111111111" << "22222222222" <<"3333333333333" <<"444444444444444" << "66666666666666" << "555555555555" << "7777777777";
    setRecomListText(list);
}

FirstShow::~FirstShow()
{

}

void FirstShow::initUi()
{
    m_recomList = new QListWidget(this);
    m_recomList->setObjectName(QString::fromLocal8Bit("m_recomList"));

    m_recoBtn1 = new QPushButton(this);
    m_recoBtn1->setObjectName(QString::fromLocal8Bit("m_recoBtn1"));

    m_recoBtn2 = new QPushButton(this);
    m_recoBtn2->setObjectName(QString::fromLocal8Bit("m_recoBtn2"));

    m_slideShow = new Slideshow(this);
    m_slideShow->setObjectName(QString::fromLocal8Bit("m_slideShow"));

    QVBoxLayout *vbLayout1 = new QVBoxLayout();
    vbLayout1->addWidget(m_recoBtn1);
    vbLayout1->addWidget(m_recoBtn2);
    vbLayout1->addWidget(m_recomList);

    QHBoxLayout *hbLayout1 = new QHBoxLayout(this);
    hbLayout1->addWidget(m_slideShow);
    hbLayout1->addLayout(vbLayout1);
    this->setLayout(vbLayout1);
}

void FirstShow::setRecomButtonText(const QString text1, const QString text2)
{
    m_recoBtn1->setText(text1);
    m_recoBtn2->setText(text2);
}

void FirstShow::clearRecomButtonText()
{
    m_recoBtn1->setText("");
    m_recoBtn2->setText("");
}

void FirstShow::setRecomListText(QStringList list)
{
    foreach(QString const &arg,list)
    {
        m_recomList->addItem(arg);
    }
}
