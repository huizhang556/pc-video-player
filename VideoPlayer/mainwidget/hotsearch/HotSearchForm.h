#ifndef HOTSEARCHFORM_H
#define HOTSEARCHFORM_H

#include <QWidget>
#include <QTreeWidget>

namespace Ui {
class HotSearchForm;
}

class HotSearchForm : public QWidget
{
    Q_OBJECT

public:
    explicit HotSearchForm(QWidget *parent = nullptr);
    ~HotSearchForm();
    void        initWorkUI();
    void        handleSignalsAndSlots();

public slots:
    void     slot_addItemToTreeWgt(QTreeWidget *treeWgt,const QString& order,const QString& text,bool up);

private:
    Ui::HotSearchForm *ui;
    bool    m_up = true;
};

#endif // HOTSEARCHFORM_H
