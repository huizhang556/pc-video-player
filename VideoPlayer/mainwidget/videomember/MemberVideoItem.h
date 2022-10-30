#ifndef MEMBERVIDEOITEM_H
#define MEMBERVIDEOITEM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class MemberVideoItem;
}

class MemberVideoItem : public QWidget
{
    Q_OBJECT

public:
    explicit MemberVideoItem(QWidget *parent = nullptr);
    explicit MemberVideoItem(const QString& picpath,const QString& name,const QString& author,const QColor& bgcolor, QWidget *parent = nullptr);
    ~MemberVideoItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:
protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    void    slot_setItemPictures();
    void    slot_setItemBGColor();
    void    slot_setItemInfos();

private:
    Ui::MemberVideoItem *ui;
    QString     m_picPath;
    QColor      m_bgcolor;
    QString     m_info1;
    QString     m_info2;

};

#endif // MEMBERVIDEOITEM_H
