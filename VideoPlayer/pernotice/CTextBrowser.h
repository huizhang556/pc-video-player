#ifndef CTEXTBROWSER_H
#define CTEXTBROWSER_H

#include <QTextBrowser>

namespace Ui {
class CTextBrowser;
}

class CTextBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    explicit CTextBrowser(QWidget *parent = nullptr);
    ~CTextBrowser();

private:
    Ui::CTextBrowser *ui;
};

#endif // CTEXTBROWSER_H
