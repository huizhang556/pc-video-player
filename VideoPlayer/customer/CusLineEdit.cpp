#include "CusLineEdit.h"
#include <QBoxLayout>

CusLineEdit::CusLineEdit(const QString &btnText, QWidget *parent) :
    QLineEdit(parent)
{
    m_button = new QPushButton(btnText);
    setTextButton();
    addButton();
}

CusLineEdit::CusLineEdit(const QIcon &icon, QWidget *parent)
{
    m_button = new QPushButton;
    m_button->setIcon(icon);
    setIconButton();
    addButton();
}

CusLineEdit::~CusLineEdit()
{

}

void CusLineEdit::setTextButton()
{
    if (!m_button) {
            return;
        }
        // 获得当前字体下文本内容的像素宽度
        auto width = QWidget::fontMetrics().width(m_button->text());
        setButtonSize(m_button, width);
}

void CusLineEdit::setIconButton()
{
    if (!m_button) {
            return;
        }

        // 获取图标的width简单得多
        auto width = m_button->iconSize().width();
        setButtonSize(m_button, width);
        // 设置背景和边框在非点击时不可见
        m_button->setFlat(true);
}

void CusLineEdit::addButton()
{
    // 按钮已经是edit的一部分了，不应该再能被单独聚焦，否则可能导致误触
    m_button->setFocusPolicy(Qt::NoFocus);
    // 设置鼠标，否则点击按钮时仍然会显示输入内容时的鼠标图标
    m_button->setCursor(Qt::ArrowCursor);

    auto btnLayout = new QHBoxLayout;
    btnLayout->addStretch();
    btnLayout->addWidget(m_button);
    // 设置组件右对齐，按钮会显示在edit的右侧
    btnLayout->setAlignment(Qt::AlignRight);
    btnLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(btnLayout);
    // 设置输入区域的范围，从edit的最左到按钮的最左(包含了按钮设置的buttonMargin)
    setTextMargins(0, 0, m_button->width(), 0);
}

void CusLineEdit::setButtonSize(QPushButton *button, int width)
{
    auto policy = button->sizePolicy();
    policy.setHorizontalPolicy(QSizePolicy::Fixed);
    button->setSizePolicy(policy);
    // 固定宽度，加上边距
    button->setFixedWidth((width+buttonMargin*2));
}
