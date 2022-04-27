#ifndef STACKITEMFORM_H
#define STACKITEMFORM_H
#include "mainwidget/StackItem.h"
#include <QWidget>
#include <QMap>
#include <QLabel>
#include <QBoxLayout>
#include <QListWidgetItem>
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
    void addCusWidgetToList();
private slots:
    void slot_switchPageToStackWidget(QListWidgetItem *item);

private:
    Ui::StackItemForm *ui;
    QMap<int,QLabel*>    m_mapLabel;
};

#endif // STACKITEMFORM_H
