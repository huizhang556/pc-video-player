#ifndef PERSONFILEFORM_H
#define PERSONFILEFORM_H

#include <QWidget>

namespace Ui {
class PersonFileForm;
}

class PersonFileForm : public QWidget
{
    Q_OBJECT

public:
    explicit PersonFileForm(QWidget *parent = nullptr);
    ~PersonFileForm();
    void initWorkUI();
    void chandleSignalsAndSLots();

private:
    Ui::PersonFileForm *ui;
};

#endif // PERSONFILEFORM_H
