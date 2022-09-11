#ifndef TAGSITEM_H
#define TAGSITEM_H
#include "mainwidget/songlistsort/HoverMask.h"
#include <QWidget>
#include <QPushButton>

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
    void        initWorkUI();
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
    void        setHeadMask(bool mask);

private:
    Ui::TagsItem *ui;
    QString         m_path;
    QString         m_name;
    QString         m_counts;
    QPushButton     *m_playBtn;
    QPushButton     *m_countBtn;
    QPushButton     *m_tagBtn;


signals:
    void        sig_sendMarkItem();
};

#endif // TAGSITEM_H
