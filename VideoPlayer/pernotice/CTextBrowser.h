#ifndef CTEXTBROWSER_H
#define CTEXTBROWSER_H

#include <QTextBrowser>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

namespace Ui {
class CTextBrowser;
}

class CTextBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    explicit CTextBrowser(QWidget *parent = nullptr);
    ~CTextBrowser();

protected:
    void    paintEvent(QPaintEvent *event) override;

private:
    Ui::CTextBrowser *ui;
    int     m_startX;
    int     m_startY;
    int     m_triangleWidth;//小三角宽度
    int     m_triangleHeight;//小三角高度

};

#endif // CTEXTBROWSER_H
