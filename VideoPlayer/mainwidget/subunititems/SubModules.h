#ifndef SUBMODULES_H
#define SUBMODULES_H

#include <QWidget>
#include <QEvent>
#include <QPixmap>
#include <QDebug>

namespace Ui {
class SubModules;
}

class SubModules : public QWidget
{
    Q_OBJECT

public:
    explicit SubModules(QWidget *parent = nullptr);
    explicit SubModules(const QString& picpath,const QString& info1,const QString& info2,  QWidget *parent = nullptr);
    ~SubModules();

protected:
    bool eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::SubModules *ui;
    QString     m_header;
    QString     m_info1;
    QString     m_info2;

private:
    void    setPicture();
    void    setInfo1();
    void    setInfo2();
};

#endif // SUBMODULES_H
