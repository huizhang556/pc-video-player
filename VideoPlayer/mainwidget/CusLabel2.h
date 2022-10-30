#ifndef CUSLABEL2_H
#define CUSLABEL2_H

#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>

namespace Ui {
class CusLabel2;
}

class CusLabel2 : public QLabel
{
    Q_OBJECT

public:
    explicit CusLabel2(QWidget *parent = nullptr);
    explicit CusLabel2(const QString& picpath, const QString& mainPic, const QString& topRightMark, const QString& playCounts, const bool play_on,QWidget *parent = nullptr);
    ~CusLabel2();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setItemPicture(const QString& path);
    void    setItemBGColor(const QColor& color);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;
    void    paintEvent(QPaintEvent *event) override;
private:
    Ui::CusLabel2 *ui;
    QString m_picPath;
    QColor  m_bgColor;
    bool    m_playOn;

signals:
    void    sig_buttonClicked();
};

#endif // CUSLABEL2_H
