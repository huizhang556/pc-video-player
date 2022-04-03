#ifndef COMMENTTAB_H
#define COMMENTTAB_H
#include <QWidget>
#include <QButtonGroup>
#include <QAction>

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
    void chandleSignalsAndSLots();
    void setLabelCommentCounts(int count);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::CommentTab *ui;
    QAction             *m_publishAction=   nullptr;
    QButtonGroup        *m_btnGroup     =   nullptr;

};

#endif // COMMENTTAB_H
