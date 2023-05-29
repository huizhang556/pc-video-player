#include "PathWidget.h"

PathWidget::PathWidget(QWidget *parent) :
    QWidget(parent)
{
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    // 创建标签，并设置样式和初始文本
    m_label = new QLabel(this);
    m_label->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_label->setStyleSheet("color: gray; font-size: 12px;");
    m_label->setText("/");

//    // 将标签添加到布局中
    layout->addWidget(m_label);
}

PathWidget::~PathWidget()
{
}


// 设置当前目录路径
void PathWidget::setPath(const QString &path)
{
    QStringList parts = path.split(QDir::separator());
    qDebug() << parts;
    if (parts.isEmpty()) {
        return;
    }

    QString newPath;

    for (const QString &part : parts) {
        newPath += QDir::separator() + part;
        addBreadcrumb(part, newPath);//添加单个label
    }

//    setCurrent(newPath);
}

// 添加面包屑标签
void PathWidget::addBreadcrumb(const QString &name, const QString &path)
{
    QLabel *label = new QLabel(this);

    label->setText(QString("<a href=\"%1\">%2</a>").arg(path).arg(name));
    label->setStyleSheet("color: blue; font-size: 12px;");
    label->setOpenExternalLinks(false);

    connect(label, &QLabel::linkActivated, this, [this](const QString &link)
    {
        setCurrent(link.split(QDir::separator()).last());
    });

    m_breadcrumbs.append(label);
    layout()->addWidget(label);
}

// 设置当前目录标签
void PathWidget::setCurrent(const QString &name)
{
    for (QLabel *label : m_breadcrumbs)
    {
        if (label->text().contains(name))
        {
            label->setStyleSheet("color: gray; font-size: 12px;");
        }
        else
        {
            label->setStyleSheet("color: blue; font-size: 12px;");
        }
    }

    m_label->setText(QString("<a href=\"%1\">%2</a>").arg(QDir::toNativeSeparators(name)).arg(name));
}
