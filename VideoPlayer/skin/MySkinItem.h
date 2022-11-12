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

protected:
    bool        eventFilter(QObject *watched, QEvent *event) override;

private slots:
    bool        setCloseButtonGeometry(QPushButton *btn,int x,int y, int w, int h);
    bool        setCheckedButtonGeometry(QPushButton *btn, int x, int y, int w, int h, int type);

private:
    Ui::MySkinItem *ui;
    QPushButton         *m_closeBtn         =   nullptr;
    QPushButton         *m_checkedBtn       =   nullptr;

signals:
    void        sig_closewindow();
    void        sig_checkedStatus();
};

#endif // MYSKINITEM_H
