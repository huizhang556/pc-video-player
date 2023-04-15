#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <QWidget>
#include <QButtonGroup>
#include <QDebug>

namespace Ui {
class DataAnalysis;
}

class DataAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit DataAnalysis(QWidget *parent = nullptr);
    ~DataAnalysis();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();

private:
    Ui::DataAnalysis *ui;
    QButtonGroup    *m_buttonGroup  =   nullptr;
};

#endif // DATAANALYSIS_H
