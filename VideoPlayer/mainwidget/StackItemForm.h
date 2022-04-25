#ifndef STACKITEMFORM_H
#define STACKITEMFORM_H

#include <QWidget>
#include <QMap>
#include <QLabel>

namespace Ui {
class StackItemForm;
}

class StackItemForm : public QWidget
{
    Q_OBJECT

public:
    explicit StackItemForm(QWidget *parent = nullptr);
    ~StackItemForm();
    void initWorkUI();
    void chandleSignalsAndSlots();
    void addLabelToStackWidget();

private:
    Ui::StackItemForm *ui;
    QMap<int,QLabel*>    m_mapLabel;
};

#endif // STACKITEMFORM_H
