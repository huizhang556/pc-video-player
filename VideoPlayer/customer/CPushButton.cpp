#include "CPushButton.h"

CPushButton::CPushButton(QWidget *parent):
    QPushButton(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    this->setFixedSize(DEFSIZE);
    leaveStyle();
}

CPushButton::~CPushButton()
{

}

void CPushButton::enterStyle()
{
    QString enter_qss = R"(QPushButton{
            background-color: rgba(255, 212, 128,1.0);
            background-image: url(:/images/icon/sousuo.png);
            background-repeat: no-repeat;
            background-position:left;
            background-origin:content;
            padding-left:-2px; /*图片相对于左边的偏移*/
            text-align:right;  /*文本的对齐方式*/
            padding-right:16px; /*文本相对于右边的偏移*/
            border-radius:16px;
            color:#00beff;
            font-family: \"Microsoft YaHei\";
            font-size: 14px;
            font-weight: bold;
        })";

    this->setStyleSheet(enter_qss);
    this->setText(u8"搜全网");
}

void CPushButton::leaveStyle()
{
    QString button_qss = R"(QPushButton{
            border-image: url(:/images/icon/sousuo.png);
            background-repeat: no-repeat;
            background-position: center;
            border-radius:16px;
            border: 0px solid transparent;
        })";
    this->setStyleSheet(button_qss);
    this->setText(u8"");
}

//void CPushButton::enterEvent(QEvent *event)
//{
//    Q_UNUSED(event)
//    QString enter_qss = R"(QPushButton{
//            background-color: rgba(255, 212, 128);
//            background-image: url(:/images/icon/sousuo.png);
//            background-repeat: no-repeat;
//            background-position:left;
//            background-origin:content;
//            padding-left:15px; /*图片相对于左边的偏移*/
//            text-align:right;  /*文本的对齐方式*/
//            padding-right:16px; /*文本相对于右边的偏移*/
//            border-radius:16px;
//            color:#FFFFFF;
//            font-family: \"Microsoft YaHei\";
//            font-size: 20px;
//        })";

//    this->setStyleSheet(enter_qss);
//    this->setText(u8"搜全网");
//}

//void CPushButton::leaveEvent(QEvent *event)
//{
//    Q_UNUSED(event)
//    normalStyle();
//}

//void CPushButton::normalStyle()
//{
//    QString button_qss = R"(QPushButton{
//            background-color:#148AFF;
//            background-image: url(:/images/icon/sousuo.png);
//            background-repeat: no-repeat;
//            background-position: center;
//            border-radius:16px;
//        })";
//    this->setStyleSheet(button_qss);
//    this->setText(u8"");
//}
