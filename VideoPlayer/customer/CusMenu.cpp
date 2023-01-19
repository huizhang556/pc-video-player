#include "CusMenu.h"

CusMenu::CusMenu(QWidget *parent) :
    QMenu(parent)
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

void CusMenu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPixmap px(this->size()); //Create pixmap with the same size of current widget
    px.fill(Qt::transparent); //Fill transparent
    QPainter p(&px);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern); //For fill
    p.setBrush(brush);
    p.drawRoundedRect(this->rect(), 15.0, 15.0); //Draw filled rounded rectangle on pixmap
    this->setMask(px.mask()); //The the mask for current widget.


}
