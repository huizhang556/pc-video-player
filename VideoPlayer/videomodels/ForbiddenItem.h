#ifndef FORBIDDENITEM_H
#define FORBIDDENITEM_H

#include <QWidget>
#include <QIcon>
#include <QEvent>
#include <QPushButton>
#include <QLayout>
#include <QDebug>

class ForbiddenItem : public QWidget
{
    Q_OBJECT

public:
    explicit ForbiddenItem(QWidget *parent = nullptr);
    explicit ForbiddenItem(const QString& icon, const QString& text, QWidget *parent = nullptr);
    ~ForbiddenItem();
    void    initWorkUI();
    void    handleSignalAndSlot();
    void    setInstallEventFilter();

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    QHBoxLayout      *m_horLayout    =   nullptr;
    QPushButton      *m_btn_text     =   nullptr;//图标+文字
    QPushButton      *m_btn_remove   =   nullptr;//移除按钮

signals:
    void    sig_send_remove();

};

#endif // FORBIDDENITEM_H
