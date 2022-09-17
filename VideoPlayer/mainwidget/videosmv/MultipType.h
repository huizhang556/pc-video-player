#ifndef MVTYPE_H
#define MVTYPE_H

#define MINSIZE QSize(360,250)
#define SCALE MINSIZE.height()/MINSIZE.width()

#include <QWidget>
#include <QSize>

namespace Ui {
class MvType;
}

class MvType : public QWidget
{
    Q_OBJECT

public:
    explicit MvType(QWidget *parent = nullptr);
    ~MvType();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;


private:
    void    resizeListWidgetItemSize();

private:
    Ui::MvType *ui;
};

#endif // MVTYPE_H
