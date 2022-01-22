#ifndef CUSMENU_H
#define CUSMENU_H

#include <QWidget>
#include <QMap>

class CusMenu : public QWidget
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

private:

};

#endif // CUSMENU_H
