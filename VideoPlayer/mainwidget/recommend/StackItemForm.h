#ifndef STACKITEMFORM_H
#define STACKITEMFORM_H
#include "global/Global.h"
#include "mainwidget/recommend/StackItem.h"
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
    int getQMapKey(QMap<int, QString> vector, QString text);
private:
    Ui::StackItemForm *ui;
    QMap<int,QLabel*>        m_mapLabel;
    QMap<int,QString>        m_vectitle;
    QMap<int,QString>        m_vecexplain;
    QMap<int,QString>        m_vecicon;
};

#endif // STACKITEMFORM_H
