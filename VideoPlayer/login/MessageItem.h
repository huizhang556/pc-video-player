#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QWidget>

namespace Ui {
class MessageItem;
}

class MessageItem : public QWidget
{
    Q_OBJECT

public:
    explicit MessageItem(QWidget *parent = nullptr);
    ~MessageItem();

private:
    Ui::MessageItem *ui;
};

#endif // MESSAGEITEM_H
