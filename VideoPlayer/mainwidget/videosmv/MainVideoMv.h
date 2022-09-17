#ifndef VIDEOMV_H
#define VIDEOMV_H

#include <QWidget>
#include <QButtonGroup>

namespace Ui {
class VideoMv;
}

class VideoMv : public QWidget
{
    Q_OBJECT

public:
    explicit VideoMv(QWidget *parent = nullptr);
    ~VideoMv();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:
    void    slot_globalResize();

private slots:
    void    slot_setButtonChecked(QAbstractButton* button);

private:
    Ui::VideoMv *ui;
    QButtonGroup    *m_buttonGroup;
};

#endif // VIDEOMV_H
