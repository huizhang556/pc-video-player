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
    explicit MvType(const QString& title,const QString& leftpic, const QString& info1,const QString& info2, QWidget *parent = nullptr);
    ~MvType();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;


private:
    void    resizeListWidgetItemSize();
    void    setItemTitle();
    void    setItemLeftPicture();
    void    setItemInfo1();
    void    setItemInfo2();

private:
    Ui::MvType *ui;
    QString     m_title;
    QString     m_leftpic;
    QString     m_info1;
    QString     m_info2;
};

#endif // MVTYPE_H
