#include "CusMenu.h"

CusMenu::CusMenu(QWidget *parent) :
    QWidget(parent)
{

}

CusMenu::~CusMenu()
{

}

void CusMenu::setCusMenuStyleSheet(const QString &style)
{
    Q_UNUSED(style);
}

void CusMenu::setCusMenuContent(QMap<QString, QIcon> &menulist)
{
    Q_UNUSED(menulist);
}

void CusMenu::insertCusMenuAction(int index)
{
    Q_UNUSED(index);
}

void CusMenu::removeCusMenuAction(int index)
{
    Q_UNUSED(index);
}

void CusMenu::setCusMenuHidden(bool hide)
{
    Q_UNUSED(hide);
}
