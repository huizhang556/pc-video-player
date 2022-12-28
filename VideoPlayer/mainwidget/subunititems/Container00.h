#ifndef CONTAINER00_H
#define CONTAINER00_H

#include <QWidget>
#include <QEvent>
#include <QPushButton>
#include <QScrollBar>
#include <QScroller>
#include <QListWidgetItem>
#include <QDebug>

namespace Ui {
class Container00;
}

class Container00 : public QWidget
{
    Q_OBJECT

public:
    explicit Container00(QWidget *parent = nullptr);
    explicit Container00(const QString& titleText,QWidget *parent = nullptr);
    ~Container00();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:
    void    slot_addItemToListWidget(const QString& url, const QString& picpath,const QString& info1,const QString& info2);

protected:
//    bool    eventFilter(QObject *watched, QEvent *event) override;
//    void    resizeEvent(QResizeEvent *event) override;

private:
    Ui::Container00 *ui;

//    QPushButton     *m_videoButton_L   =   nullptr;
//    QPushButton     *m_videoButton_R   =   nullptr;

private:
//    void updataAdjustButton_LR();//随着窗口变化调节左右按钮的位置
};

#endif // CONTAINER00_H
