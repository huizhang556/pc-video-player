#ifndef TAGSMENU_H
#define TAGSMENU_H

#include <QWidget>

namespace Ui {
class TagsMenu;
}

class TagsMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TagsMenu(QWidget *parent = nullptr);
    ~TagsMenu();

protected:
    void    leaveEvent(QEvent *event) override;
private:
    Ui::TagsMenu *ui;
};

#endif // TAGSMENU_H
