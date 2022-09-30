#ifndef CUSLABEL2_H
#define CUSLABEL2_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class CusLabel2;
}

class CusLabel2 : public QLabel
{
    Q_OBJECT

public:
    explicit CusLabel2(QWidget *parent = nullptr);
    explicit CusLabel2(const QString& mainPic, const QString& topRightMark, const QString& playCounts, const bool play_on,QWidget *parent = nullptr);
    ~CusLabel2();
    void    initWorkUI();
    void    handleSignalsAndSlots();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::CusLabel2 *ui;
    bool    m_playOn;

signals:
    void    sig_buttonClicked();
};

#endif // CUSLABEL2_H
