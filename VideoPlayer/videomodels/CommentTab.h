#ifndef COMMENTTAB_H
#define COMMENTTAB_H
#define MAX_SIZE 30
#include <QWidget>
#include <QButtonGroup>
#include <QAction>
#include <QTimer>

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

public slots:
    void slot_insertNewCommentForm(QPixmap &pic, QString &nick, QString &date, QString &data, int count);//插入新的评论

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::CommentTab *ui;
    QAction             *m_publishAction=   nullptr;
    QButtonGroup        *m_btnGroup     =   nullptr;

private:
    void checkCommentsCounts();


};

#endif // COMMENTTAB_H
