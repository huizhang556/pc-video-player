#ifndef WATCHRECORDS_H
#define WATCHRECORDS_H
#define ITEMSIZE QSize(290,85)
#include <QSize>
#include <QWidget>

namespace Ui {
class WatchRecords;
}

class WatchRecords : public QWidget
{
    Q_OBJECT

public:
    ~WatchRecords();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    static  WatchRecords* getInstance();

protected:
    void    paintEvent(QPaintEvent *event) override;
    void    leaveEvent(QEvent *event) override;

private:
    explicit WatchRecords(QWidget *parent = nullptr);
    Ui::WatchRecords *ui;
    static WatchRecords* m_pInstance;
    int     m_startX;
    int     m_startY;
    int     m_triangleWidth;//小三角宽度
    int     m_triangleHeight;//小三角高度

};

#endif // WATCHRECORDS_H
