#ifndef COMMENTFORM_H
#define COMMENTFORM_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class CommentForm;
}

class CommentForm : public QWidget
{
    Q_OBJECT

public:
    explicit CommentForm(QWidget *parent = nullptr);
    ~CommentForm();
    void initWorkUI();
    void chandleSignalsAndSLots();

    void setUserPicture(QPixmap &pix);//评论者头像

    void setUserNick(QString &nick);//评论者昵称

    void setUserCommitDataTime(QString &datatime);//评论者评论时间

    void setUserCommentData(QString &data);//评论内容

    void setCommentZanCount(int count);//评论点赞数
public slots:


private:
    Ui::CommentForm *ui;
};

#endif // COMMENTFORM_H
