#ifndef VIDEOTITLEBAR_H
#define VIDEOTITLEBAR_H

#include <QLibrary>
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
    void        initUi();
    void        chandleSignalsAndSlots();
public slots:
    void        setTitleStackWidgetPage(int index);
    void        chandleVMainWinStatus(bool status);
    void        clearTitleText();
    void        setTitleText(const QString & text);
    void        slot_updateMiniWinStatus(bool mini);

protected:
    void        mouseDoubleClickEvent(QMouseEvent *event) override;
    bool        eventFilter(QObject *watched, QEvent *event) override;
//    void        mousePressEvent(QMouseEvent *event) override;

private slots:

private:
    Ui::VideoTitleBar *ui;

signals:
    void    sig_win_mini();
    void    sig_titlefix(bool);
    void    sig_winVClose();
    void    sig_winVMinimum();
    void    sig_winVRestore();
    void    sig_doubleClick();
    void    sig_returnMainUi();
    void    sig_videodownload();
    void    sig_videoCapture();//截图
    void    sig_inputSourceUrl(QString url);
};

#endif // VIDEOTITLEBAR_H
