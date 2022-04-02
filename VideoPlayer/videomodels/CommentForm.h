#ifndef COMMENTFORM_H
#define COMMENTFORM_H

#include <QWidget>

namespace Ui {
class CommentForm;
}

class CommentForm : public QWidget
{
    Q_OBJECT

public:
    explicit CommentForm(QWidget *parent = nullptr);
    ~CommentForm();
    void setUserPicture(QPixmap pix);

    void setUserNick(QString nick);

    void setUserCommitDataTime(QString datatime);

    void setCommentZanCount(int count);

private:
    Ui::CommentForm *ui;
};

#endif // COMMENTFORM_H
