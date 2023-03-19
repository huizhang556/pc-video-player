#ifndef LABLOADING_H
#define LABLOADING_H

#include <QLabel>
#include <QTimer>
#include <QtMath>
#include <QPainter>

class LabLoading : public QLabel
{

    Q_OBJECT
    Q_PROPERTY(QColor BgColor READ getBgColor WRITE setBgColor)
    Q_PROPERTY(QColor TextColor READ getTextColor WRITE setTextColor)
    Q_PROPERTY(QColor BarColor READ getBarColor WRITE setBarColor)

public:
    explicit LabLoading(QWidget *parent = nullptr);
    ~LabLoading();
    QColor getBgColor()               const;    //获取背景颜色
    QColor getTextColor()             const;    //获取文本颜色
    QColor getBarColor()              const;    //获取进度条颜色

private:
    bool ProgressRun;   //进度条运行状态
    QColor BgColor;     //背景颜色
    QColor TextColor;   //文本颜色
    QColor BarColor;    //进度条颜色
    QVector<QColor> rColor; //进度条颜色区分数组
    int ProgressNum;    //进度
    QTimer *timerrun;   //定时器
    int startAngle;     //进度条开始角度

protected:
    void paintEvent(QPaintEvent *);
    void drawBar(QPainter *painter);    //绘制进度条
    void drawBg(QPainter *painter);     //绘制背景
    void drawText(QPainter *painter);   //绘制文字

signals:

public slots:
    void setBgColor(const QColor &BgColor);         //设置背景颜色
    void setTextColor(const QColor &TextColor);     //设置文本颜色
    void setBarColor(const QColor &BarColor);       //设置进度条颜色
    void setProgressNum(const int &ProgressNum);    //设置进度
    void prorun();
    void startRun();	//开始动态显示
    void stopRun();		//停止动态显示

};

#endif // LABLOADING_H
