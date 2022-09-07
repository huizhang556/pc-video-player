#include "TagsMenu.h"
#include "ui_TagsMenu.h"

TagsMenu::TagsMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagsMenu)
{
    ui->setupUi(this);
    setFixedSize(735,360);
}

TagsMenu::~TagsMenu()
{
    delete ui;
}

void TagsMenu::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->close();
}
