#ifndef ADJUSTBRIGHT_H
#define ADJUSTBRIGHT_H

#include <QDialog>
#include <QCheckBox>
#include <QPaintEvent>
#include <QRadioButton>

namespace Ui {
class AdjustBright;
}

class AdjustBright : public QDialog
{
    Q_OBJECT

public:
    explicit AdjustBright(QWidget *parent = nullptr);
    ~AdjustBright();

protected:
//    void paintEvent(QPaintEvent *event) override;

    void leaveEvent(QEvent *event) override;

public slots:
    void slot_setProgressBarValue_brightness(int value);//亮度
    void slot_setProgressBarValue_contrast(int value);//对比度
    void slot_setProgressBarValue_saturation(int value);//饱和度
    void slot_setProgressBarValue_hue(int value);//色相

private slots:
    void setPlayRate();

    void setAspectRatioMode();

    void clearAllRateButtonChecked();

    void clearAllCheckBoxChecked();

    void selectPlayRate();//判断播放速率

    void selectPlaybackMode();//判断播放模式

    void selectaspectRatioMode();//判断屏幕比例

    void updatePlayRate();

signals:
    void valueChange_liangdu(int val);

    void valueChange_duibidu(int val);

    void valueChange_baohedu(int val);

    void valueChange_sediao(int val);

    void valueChange_playRate(qreal value);//倍速

    void valueChange_playBackMode(int value);//倍速

    void valueChange_aspectRatio(int index);//屏幕宽高比

private:
    Ui::AdjustBright *ui;

};

#endif // ADJUSTBRIGHT_H
