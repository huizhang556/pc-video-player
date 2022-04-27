#ifndef STACKITEM_H
#define STACKITEM_H

#include <QWidget>

namespace Ui {
class StackItem;
}

class StackItem : public QWidget
{
    Q_OBJECT

public:
    explicit StackItem(QWidget *parent = nullptr);
    ~StackItem();
    void setlistBtn_NameText(QString text);
    void setlistBtn_IntroText(QString text);
    void setlistBtn_NameIcon(QString path);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
    Ui::StackItem *ui;
};

#endif // STACKITEM_H
