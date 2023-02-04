#ifndef CUSLABEL1_H
#define CUSLABEL1_H

#include <QPainter>
#include <QLabel>
#include <QRegion>
#include <QBitmap>
#include <QDebug>


namespace Ui {
class CusLabel1;
}

class CusLabel1 : public QLabel
{
    Q_OBJECT

public:
    explicit CusLabel1(QWidget *parent = nullptr);
    explicit CusLabel1(const QString &picpath, const QColor& bgcolor, const int radius, const bool collect_on,QWidget *parent = nullptr);
    ~CusLabel1();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setItemPicture(const QString& path);
    void    setItemBGColor(const QColor& color);
    void    setItemColStatus(const bool& on);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;
    void    paintEvent(QPaintEvent *event) override;

private:
    Ui::CusLabel1 *ui;
    QString m_picPath;
    bool    m_collect;
    QColor  m_bgColor;
    int     m_radius;

signals:
    void    sig_item_click();
    void    sig_item_enter();
    void    sig_item_collect(bool);
};

#endif // CUSLABEL1_H
