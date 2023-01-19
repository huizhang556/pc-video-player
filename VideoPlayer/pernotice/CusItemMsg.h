#ifndef CUSITEMMSG_H
#define CUSITEMMSG_H
#include <QStyle>
#include <QWidget>
#include <QFontMetrics>
#include <QAbstractButton>
#include <QDebug>

namespace Ui {
class CusItemMsg;
}

class CusItemMsg : public QWidget
{
    Q_OBJECT

public:
    //chat list
    explicit CusItemMsg(const QString& header, const QString& author, const QString& Newcontent, const QString& datatime, const bool read, QWidget *parent = nullptr);
    //reply list
    explicit CusItemMsg(const QString& header,const QString& author,const QString& newContent,const QString& oldContent,const QString& datatime,QWidget *parent = nullptr);
    //@ list
//    explicit CusItemMsg(const QString& header, const QStringList& authors, const QString& oldContent, const QString& datatime, QWidget *parent = nullptr);
    //like list
    explicit CusItemMsg(const QString& header, const QStringList& authors, const QString& oldContent, const QString& datatime, QWidget *parent = nullptr);


    ~CusItemMsg();
    void        initWorkUI();
    void        handleSignalsAndSlots();
    void        setReadStatus(bool read);
    bool*       getArroy_ON_Mark();
private:
    Ui::CusItemMsg *ui;
    bool    array_on[4];//4个标志位

private:
    void    setMultiTextToElidedText(QAbstractButton *button, QString text,const int twidth);

signals:
    void    sig_sendClicked();
    void    sig_sendLike();
    void    sig_sendDelete();
};

#endif // CUSITEMMSG_H
