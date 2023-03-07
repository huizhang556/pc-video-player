#include "CusLineEdit.h"
#include <QBoxLayout>

CusLineEdit::CusLineEdit(QWidget *parent):
    QLineEdit(parent)
{
    this->setAttribute(Qt::WA_StyledBackground);
    initWorkUI();
    handleSignalsAndSLots();
}

CusLineEdit::~CusLineEdit()
{

}

void CusLineEdit::initWorkUI()
{
    //原样式表中QLineEdit生效
    QString qss_lineEdit = R"(
            QLineEdit{
                background-color:#33373E;     /* 背景颜色 */
                border: 1px solid #33373E;      /* 边框宽度为1px，颜色为#A0A0A0 */
                border-radius: 18px;         /* 边框圆角 */
                padding-left: 10px;           /* 文本距离左边界有5px */
                color: #FFFFFF;     /* 文本颜色 */
                selection-background-color: #A0A0A0;     /* 选中文本的背景颜色 */
                selection-color: #F2F2F2;    /* 选中文本的颜色 */
                font-family: \"Microsoft YaHei\";    /* 文本字体族 */
                font-size:18px;    /* 文本字体大小 */
            }
        )";
//    this->setStyleSheet(qss_lineEdit);
    this->setPlaceholderText(u8"请输入搜索内容");
    this->setFixedHeight(36);
    this->setMinimumWidth(180);

    m_pBtn = new CPushButton(this);
    QHBoxLayout* pHlay = new QHBoxLayout(this);
    pHlay->addStretch();
    pHlay->addWidget(m_pBtn);
    pHlay->setContentsMargins(0,0,2,0);
    this->setTextMargins(10, 0, 32,0);//void setTextMargins(int left, int top, int right, int bottom);
}

void CusLineEdit::handleSignalsAndSLots()
{
    connect(m_pBtn, &CPushButton::clicked,[=]()
    {
        emit sig_Search(this->text());
    });
}

void CusLineEdit::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_pBtn->setFixedWidth(32);
    m_pBtn->leaveStyle();
    this->setTextMargins(10, 0, 32,0);
}

void CusLineEdit::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_pBtn->setFixedWidth(95);
    m_pBtn->enterStyle();
    this->setTextMargins(10, 0, 95,0);
    setCursor(Qt::ArrowCursor);
}

