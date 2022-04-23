#ifndef MAINSHOWFORM_H
#define MAINSHOWFORM_H

#include "lunbotu/PictureWidget.h"
#include <QWidget>
#include <QBoxLayout>

namespace Ui {
class MainShowForm;
}

class MainShowForm : public QWidget
{
    Q_OBJECT

public:
    explicit MainShowForm(QWidget *parent = nullptr);
    ~MainShowForm();

    void initWorkUI();
    void chandleSignalsAndSlots();

private:
    QWidget             *m_widget1      =   nullptr;
    QVBoxLayout         *m_vHlayout1    =   nullptr;
    PictureWidget       *m_picWidget    =   nullptr;

};

#endif // MAINSHOWFORM_H
