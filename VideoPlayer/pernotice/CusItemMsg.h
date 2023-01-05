#ifndef CUSITEMMSG_H
#define CUSITEMMSG_H
#include <QStyle>
#include <QWidget>
#include <QDebug>

namespace Ui {
class CusItemMsg;
}

class CusItemMsg : public QWidget
{
    Q_OBJECT

public:
    //chat list
    explicit CusItemMsg(const QString& header,const QString& author,const QString& Newcontent,const QString& datatime, QWidget *parent = nullptr);
    //reply list
    explicit CusItemMsg(const QString& header,const QString& author,const QString& newContent,const QString& oldContent,const QString& datatime,QWidget *parent = nullptr);
    //@ list
//    explicit CusItemMsg(const QString& header, const QStringList& authors, const QString& oldContent, const QString& datatime, QWidget *parent = nullptr);
    //like list
    explicit CusItemMsg(const QString& header, const QStringList& authors, const QString& oldContent, const QString& datatime, QWidget *parent = nullptr);


    ~CusItemMsg();
    void        initWorkUI();
    void        handleSignalsAndSlots();

private:
    Ui::CusItemMsg *ui;

private:

signals:
    void    sig_sendClicked();
};

#endif // CUSITEMMSG_H
