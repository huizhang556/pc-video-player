#ifndef SONGITEM_H
#define SONGITEM_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>

namespace Ui {
class SongItem;
}

class SongItem : public QWidget
{
    Q_OBJECT

public:
    explicit SongItem(QWidget *parent = nullptr);
    explicit SongItem(const QString& picture,const QString& name,const QString& counts, int alignFlag, QWidget *parent = nullptr);
    ~SongItem();

    void        setInstallEventFilter();
    void        handleSignalsAndSlots();

public slots:
    void        slot_setHeadPicture(const QString& path);
    void        slot_setSongerName(const QString& name);
    void        slot_setSongerCounts(const QString& counts);
    void        slot_setAlignText(int index);

protected:
    bool        eventFilter(QObject *watched, QEvent *event) override;
    void        paintEvent(QPaintEvent *event) override;

private:
    Ui::SongItem *ui;
    QString     m_path;
    QString     m_name;
    QString     m_counts;

signals:
    void        sig_sendSonger(QString);
};

#endif // SONGITEM_H
