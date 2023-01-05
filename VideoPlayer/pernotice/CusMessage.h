#ifndef CUSMESSAGE_H
#define CUSMESSAGE_H

#include <QWidget>
#include <QTextBrowser>
#include <QScrollBar>
#include <QDebug>

enum NEWSTYPE
{
    NEWS_LEFT,
    NEWS_RIGHT
};

namespace Ui {
class CusMessage;
}

class CusMessage : public QWidget
{
    Q_OBJECT

public:
    explicit CusMessage(const QString& title, const QString& datatime, const QString& content, QWidget *parent = nullptr);
    explicit CusMessage(NEWSTYPE type, const QString& header,const QString& datatime,const QString& cotent, QWidget *parent = nullptr);
    ~CusMessage();
    void        initWorkUI();
    void        handleSignalsAndSlots();

private:
    Ui::CusMessage *ui;

private:
    void    selectType(NEWSTYPE type,const QString& header,const QString& datatime,const QString& cotent);
    int     getDynamicHeight(const QTextBrowser* browser);
};

#endif // CUSMESSAGE_H
