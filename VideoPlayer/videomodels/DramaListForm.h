#ifndef DRAMALISTFORM_H
#define DRAMALISTFORM_H

#include <QWidget>

namespace Ui {
class DramaListForm;
}

class DramaListForm : public QWidget
{
    Q_OBJECT

public:
    explicit DramaListForm(QWidget *parent = nullptr);
    ~DramaListForm();
    void initWorkUI();
    void chandleSignalsAndSLots();

private:
    Ui::DramaListForm *ui;
};

#endif // DRAMALISTFORM_H
