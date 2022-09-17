#ifndef MVSORTTYPE_H
#define MVSORTTYPE_H

#define MINSIZE QSize(360,270)
#define SCALE MINSIZE.height()/MINSIZE.width()

#include <QSize>
#include <QWidget>
#include <QButtonGroup>


namespace Ui {
class MVSortType;
}

class MVSortType : public QWidget
{
    Q_OBJECT

public:
    explicit MVSortType(QWidget *parent = nullptr);
    ~MVSortType();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void    slot_setButtonChecked(QAbstractButton* button);

private:
    void    resizeListWidgetItemSize();

private:
    Ui::MVSortType *ui;
    QButtonGroup    *m_buttonGroup;
};

#endif // MVSORTTYPE_H
