#ifndef MEMBERVIDEOITEM_H
#define MEMBERVIDEOITEM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class MemberVideoItem;
}

class MemberVideoItem : public QLabel
{
    Q_OBJECT

public:
    explicit MemberVideoItem(QWidget *parent = nullptr);
    explicit MemberVideoItem(const QString& picpath,const QString& name,const QString& author, QWidget *parent = nullptr);
    ~MemberVideoItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:
protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    void    slot_setItemPictures(const QString& picpath);

private:
    Ui::MemberVideoItem *ui;
    static  QString         m_appDir;
};

#endif // MEMBERVIDEOITEM_H
