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

public slots:
    void    slot_addRecordToListWgt_history();//添加一条收藏记录

private:
    Ui::CollectRecords *ui;

signals:
    void    sig_returnPage();
    void    sig_changeRecord();
};

#endif // COLLECTRECORDS_H
