#ifndef FAQITEM_H
#define FAQITEM_H
#include "global/Global.h"
#include <QWidget>

namespace Ui {
class FAQitem;
}

class FAQitem : public QWidget
{
    Q_OBJECT

public:
    explicit FAQitem(QWidget *parent = nullptr);
    explicit FAQitem(const QString& title, const QString& content, QWidget *parent = nullptr);
    ~FAQitem();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setFoldItem();
    void    setShowItem();

private:
    Ui::FAQitem *ui;
    bool    m_open = false;

signals:
    void    sig_item_expand(bool);
};

#endif // FAQITEM_H
