#ifndef CONTAINER01_H
#define CONTAINER01_H

#include <QWidget>
#include <QScrollBar>
#include <QListWidgetItem>
#include <QDebug>

namespace Ui {
class Container01;
}

class Container01 : public QWidget
{
    Q_OBJECT

public:
    explicit Container01(QWidget *parent = nullptr);
    explicit Container01(const QString& titleText, const QString& leftPicPath, QWidget *parent = nullptr);
    ~Container01();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setItemLeftPicture();

public slots:
    void    slot_addItemToListWidget_top(const QString& url, const QString& picpath,const QString& info1,const QString& info2);
    void    slot_addItemToListWidget_bottom(const QString& url, const QString& picpath,const QString& info1,const QString& info2);

private:
    Ui::Container01 *ui;
    QString     m_leftPic;
};

#endif // CONTAINER01_H
