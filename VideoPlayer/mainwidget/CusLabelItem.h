#ifndef CUSLABELITEM_H
#define CUSLABELITEM_H

#include <QLabel>
#include <QPainter>
#include <QPaintEvent>

namespace Ui {
class CusLabelItem;
}

class CusLabelItem : public QLabel
{
    Q_OBJECT

public:
    explicit CusLabelItem(QWidget *parent = nullptr);
    explicit CusLabelItem(const QString& hotPath,const QString& playcounts,bool hotOn, bool playOff1, bool playOff2, QWidget *parent = nullptr);
    ~CusLabelItem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setEventFilter();

    void    constructItem(const QString& hotPath,const QString& playcounts,bool hotOn, bool playOff1, bool playOff2);//参数初始化
    void    setItem_hotOn(bool on);
    void    setItemMainPlayerOn(bool on);
    void    setItemPlayerOn(bool on);

    void    setItem_hot(const QString& hot);
    void    setItem_playCounts(const QString& counts);
    void    setItem_mainPlayer(bool on);
    void    setItem_player(bool on);

protected:
    bool        eventFilter(QObject *watched, QEvent *event)override;
    void        paintEvent(QPaintEvent *event) override;
private:
    Ui::CusLabelItem *ui;
    QString     m_hot;
    QString     m_counts;

    bool        m_hotOn     =   false;
    bool        m_mainPlay  =   false;
    bool        m_play      =   false;

private:


signals:
    void    sig_sendPlayOn();
};

#endif // CUSLABELITEM_H
