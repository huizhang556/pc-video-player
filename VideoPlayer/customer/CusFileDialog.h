#ifndef CUSFILEDIALOG_H
#define CUSFILEDIALOG_H

#include <QFileDialog>

namespace Ui {
class CusFileDialog;
}

class CusFileDialog : public QFileDialog
{
    Q_OBJECT

public:
    explicit CusFileDialog(QWidget *parent = nullptr);
    ~CusFileDialog();
    void initWorkUI();

    void chandleSignalsAndSLots();

private:
    Ui::CusFileDialog *ui;
};

#endif // CUSFILEDIALOG_H
