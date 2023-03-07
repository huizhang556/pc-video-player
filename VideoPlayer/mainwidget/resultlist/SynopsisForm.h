#ifndef SYNOPSISFORM_H
#define SYNOPSISFORM_H

#include <QWidget>
#include <QScrollBar>
#include <QListWidgetItem>
#include <QDebug>

namespace Ui {
class SynopsisForm;
}

class SynopsisForm : public QWidget
{
    Q_OBJECT

public:
    explicit SynopsisForm(QWidget *parent = nullptr);
    ~SynopsisForm();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

private:
    Ui::SynopsisForm *ui;
};

#endif // SYNOPSISFORM_H
