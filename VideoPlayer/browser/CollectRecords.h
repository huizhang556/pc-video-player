#ifndef COLLECTRECORDS_H
#define COLLECTRECORDS_H

#include <QWidget>

namespace Ui {
class CollectRecords;
}

class CollectRecords : public QWidget
{
    Q_OBJECT

public:
    explicit CollectRecords(QWidget *parent = nullptr);
    ~CollectRecords();
    void    chandleSignalsAndSlots();

private:
    Ui::CollectRecords *ui;

signals:
    void    sig_returnPage();
};

#endif // COLLECTRECORDS_H
