#ifndef VIDEOTITLEBAR_H
#define VIDEOTITLEBAR_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class VideoTitleBar;
}

class VideoTitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit VideoTitleBar(QWidget *parent = nullptr);
    ~VideoTitleBar();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private slots:
    void chandleVMainWinStatus(bool status);
    void setTitleText(const QString & text);

private:
    Ui::VideoTitleBar *ui;

signals:
    void sig_winVClose();
    void sig_winVMinimum();
    void sig_winVRestore();
    void sig_doubleClick();
    void sig_returnMainUi();
};

#endif // VIDEOTITLEBAR_H
