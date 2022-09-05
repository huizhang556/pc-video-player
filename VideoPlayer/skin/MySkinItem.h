#ifndef MYSKINITEM_H
#define MYSKINITEM_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class MySkinItem;
}

class MySkinItem : public QWidget
{
    Q_OBJECT

public:
    explicit MySkinItem(QWidget *parent = nullptr);
    explicit MySkinItem(int x, int y, int w, int h, int type, QWidget *parent = nullptr);
    ~MySkinItem();

public slots:
    void        setSkinPicture(QString path);
    void        setCheckButtonText(QString text);
    void        setcheckedStatus();
    void        setUnCheckedStatus();
    void        setCheckButtonStatus();
    void        setCloseButtonStyleSheet();
    void        setCheckedButtonStyleSheet();

protected:
    bool        eventFilter(QObject *watched, QEvent *event) override;

private slots:
    bool        setCloseButtonGeometry(QPushButton *btn,int x,int y, int w, int h);
    bool        setCheckedButtonGeometry(QPushButton *btn, int x, int y, int w, int h, int type);

private:
    Ui::MySkinItem *ui;
    QPushButton         *m_closeBtn         =   nullptr;
    QPushButton         *m_checkedBtn       =   nullptr;
    bool                m_status;

signals:
    void        sig_closewindow();
    void        sig_checkedStatus(bool status);
};

#endif // MYSKINITEM_H
