#ifndef TITLEBAR_H
#define TITLEBAR_H
#include "browser/CusWebBrowser.h"
#include <QTimer>
#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class TitleBar;
}

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();
    void initWorker();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    bool eventFilter(QObject *watched, QEvent *event) override;

//公有槽函数以公共接口的形式暴露在外面，外部任何客户可以直接访问
public slots:
    void isNecessaryShowSearch(int index);

//私有槽函数，外部不能直接访问
private slots:
    void chandleMainWinStatus(bool status);
    void getSystemTimeShow();
    void setLineEditAddress(const QUrl url);

private:
    void chandleSignalAndSLots();
    void setShowToolTip();

private:
    QTimer          *m_timer1       = nullptr;
    QTimer          *m_timer2       = nullptr;
    QTimer          *m_timer3       = nullptr;
    CusWebBrowser   *m_webrowser    = nullptr;
    Ui::TitleBar    *ui;

signals:
    void sig_winClose();
    void sig_winNormal();
    void sig_winMinimum();
    void sig_doubleClick();
    void sig_callLogin();
    void sig_historyDownload();
    void sig_settingHelp();
    void sig_sendNewUrl(QString url);
    void sig_sendUrlBack();
    void sig_sendUrlAdvance();
    void sig_sendUrlRefreshen();
    void sig_sendUrlHome();
};

#endif // TITLEBAR_H
