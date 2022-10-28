#ifndef RECMMENDVIDEOITEM_H
#define RECMMENDVIDEOITEM_H

#define MINSIZE QSize(360,270)
#define SCALE MINSIZE.height()/MINSIZE.width()

#include <QWidget>
#include <QSize>
#include <QButtonGroup>

namespace Ui {
class RecmmendVideoItem;
}

class RecmmendVideoItem : public QWidget
{
    Q_OBJECT

public:
    explicit RecmmendVideoItem(QWidget *parent = nullptr);
    explicit RecmmendVideoItem(const QString& title, QWidget *parent = nullptr);
    ~RecmmendVideoItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    void    resizeListWidgetItemSize();

private slots:
    void    slot_setButtonChecked(QAbstractButton* button);

private:
    Ui::RecmmendVideoItem *ui;
    QButtonGroup        *m_buttonGroup;
    QString     m_title;
//    QString     m_type1;
//    QString     m_type2;
//    QString     m_type3;

private:
    void    setItemTitle();
//    void    setItemType1();
//    void    setItemType2();
//    void    setItemType3();
};

#endif // RECMMENDVIDEOITEM_H
