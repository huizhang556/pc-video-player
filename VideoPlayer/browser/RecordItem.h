#ifndef RECORDITEM_H
#define RECORDITEM_H

#include <QWidget>
#include <QIcon>
#include <QDateTime>
#include <QPushButton>

namespace Ui {
class RecordItem;
}

class RecordItem : public QWidget
{
    Q_OBJECT

public:
    explicit RecordItem(QWidget *parent = nullptr);
    explicit RecordItem(int type,QIcon icon,QString text, QWidget *parent = nullptr);
    ~RecordItem();
    void        handleSignalAndSLots();

public slots:
    void        slot_setRecordButtonText(QString text);
    void        slot_setRecordCreatetime(const QString& time);
signals:
    void        sig_item_record(QString);
    void        sig_item_modify(QString,QPushButton*);
    void        sig_item_delete();
private:
    void        judgeType();

private:
    Ui::RecordItem *ui;
    int         m_type;
    QIcon       m_icon;
    QString     m_record;
    QString     m_dateTime;
};

#endif // RECORDITEM_H
