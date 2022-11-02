#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QWidget>

namespace Ui {
class MessageItem;
}

class MessageItem : public QWidget
{
    Q_OBJECT

public:
    explicit MessageItem(QWidget *parent = nullptr);
    explicit MessageItem(const QString& pic,const QString& nickname,const QString& datatime,const QString& message, QWidget *parent = nullptr);
    ~MessageItem();
    void    setInstallEventFilter();
    void    setItemPicture();
    void    setItemNickName();
    void    setItemTime();
    void    setItemMessage();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::MessageItem *ui;
    QString     m_picPath;
    QString     m_nickName;
    QString     m_dataTime;
    QString     m_message;

};

#endif // MESSAGEITEM_H
