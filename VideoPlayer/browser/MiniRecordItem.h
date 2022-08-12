#ifndef MINIRECORDITEM_H
#define MINIRECORDITEM_H

#include <QIcon>
#include <QWidget>
#include <QPushButton>

namespace Ui {
class MiniRecordItem;
}

class MiniRecordItem : public QWidget
{
    Q_OBJECT

public:
    explicit MiniRecordItem(QWidget *parent = nullptr);
    explicit MiniRecordItem(QString text,QIcon icon,QWidget *parent = nullptr);
    ~MiniRecordItem();
    void        chandleSignalAndSLots();

public slots:
    void        slot_setRecordButtonText(QString text);

private:
    Ui::MiniRecordItem *ui;
    QIcon       m_icon;
    QString     m_record;

signals:
    void        sig_item_record(QString);
    void        sig_item_modify(QString,QPushButton*);
    void        sig_item_delete();

};

#endif // MINIRECORDITEM_H
