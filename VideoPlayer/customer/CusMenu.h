#ifndef CUSMENU_H
#define CUSMENU_H
#include <QPaintEvent>
#include <QBitmap>
#include <QPainter>
#include <QBrush>
#include <QMenu>
#include <QMap>

class CusMenu : public QMenu
{
    Q_OBJECT

public:
    explicit CusMenu(QWidget *parent = nullptr);
    ~CusMenu();

    void setCusMenuStyleSheet(const QString & style);

    void setCusMenuContent(QMap<QString,QIcon> &menulist);

    void insertCusMenuAction(int index);

    void removeCusMenuAction(int index);

    void setCusMenuHidden(bool hide);

protected:
    void    paintEvent(QPaintEvent* event);

private:

};

#endif // CUSMENU_H
