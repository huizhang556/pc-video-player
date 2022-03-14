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
public slots:
    void setTitleStackWidgetPage(int index);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private slots:
    void chandleVMainWinStatus(bool status);
    void setTitleText(const QString & text);
    void clearTitleText();

private:
    Ui::VideoTitleBar *ui;

signals:
    void sig_winVClose();
    void sig_winVMinimum();
    void sig_winVRestore();
    void sig_doubleClick();
    void sig_returnMainUi();
    void sig_inputSourceUrl(QString url);
};

#endif // VIDEOTITLEBAR_H
