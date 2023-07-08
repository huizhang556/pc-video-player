#ifndef DANMUSETTING_H
#define DANMUSETTING_H
#include "videomodels/Danmu.h"
#include "videomodels/ForbiddenItem.h"
#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QScrollBar>
#include <QButtonGroup>
#include <QDebug>

namespace Ui {
class DanmuSetting;
}

class DanmuSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DanmuSetting(QWidget *parent = nullptr);
    ~DanmuSetting();
    void        initWorkUI();
    void        handSignalsAndSlots();
    void        setInstallEventFilter();

    ColorType   getColor();
    int         getFontSize();
    int         getFontWeight();
    double      getTransNumber();
    int         getRunTime();

    void        setColor(QString color);
    void        setFontSize(int size);
    void        setFontWeight(int size);
    void        setTransNumber(double trans);
    void        setRunTime(int time);
    bool        findMask(const QString& text);

protected:
    void        leaveEvent(QEvent *event) override;

private:
    Ui::DanmuSetting *ui;
    QButtonGroup    *m_buttonGroup;
    //弹幕设置
    ColorType   m_color;
    int         m_fontSize;
    int         m_fontWeight;
    double      m_transNum;
    int         m_runTime;

private:
    void    setDefaultCfg();//设置为默认配置
    void    updateStopWordCounts();


};

#endif // DANMUSETTING_H
