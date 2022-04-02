#ifndef COMMENTTAB_H
#define COMMENTTAB_H
#include <QWidget>
#include <QButtonGroup>
#include "videomodels/CommentForm.h"
namespace Ui {
class CommentTab;
}

class CommentTab : public QWidget
{
    Q_OBJECT

public:
    explicit CommentTab(QWidget *parent = nullptr);

    ~CommentTab();
    void initWorkUI();
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::CommentTab *ui;
    QButtonGroup        *m_btnGroup     =   nullptr;

};

#endif // COMMENTTAB_H
