#ifndef PATHWIDGET_H
#define PATHWIDGET_H

#include <QDir>
#include <QList>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>

class PathWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PathWidget(QWidget *parent = nullptr);
    ~PathWidget();
    void setPath(const QString &path);
    void setCurrent(const QString &name);
    void addBreadcrumb(const QString &name, const QString &path);

private:
    QLabel          *m_label;
    QList<QLabel*>  m_breadcrumbs;

signals:


};

#endif // PATHWIDGET_H
