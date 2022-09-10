#ifndef TAGSITEM_H
#define TAGSITEM_H

#include <QWidget>

namespace Ui {
class TagsItem;
}

class TagsItem : public QWidget
{
    Q_OBJECT

public:
    explicit TagsItem(QWidget *parent = nullptr);
    explicit TagsItem(const QString& picture,const QString& name,const QString& counts,QWidget *parent = nullptr);
    ~TagsItem();
    void        handleSignalsAndSlots();
    void        setInstallEventFilter();

public slots:
    void        slot_setHeadPicture(const QString& path);
    void        slot_setSongerTages(const QString& name);
    void        slot_setSongerMark(const QString& counts);

protected:
    bool        eventFilter(QObject *watched, QEvent *event) override;
    void        resizeEvent(QResizeEvent *event) override;
private:
    void        setHeadPictureMskRegion();

private:
    Ui::TagsItem *ui;
    QString     m_path;
    QString     m_name;
    QString     m_counts;

signals:
    void        sig_sendMarkItem();
};

#endif // TAGSITEM_H
