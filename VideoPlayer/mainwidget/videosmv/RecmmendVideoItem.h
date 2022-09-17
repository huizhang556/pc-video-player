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
};

#endif // RECMMENDVIDEOITEM_H
