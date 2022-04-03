#ifndef INTRODUCEFORM_H
#define INTRODUCEFORM_H

#include <QWidget>

namespace Ui {
class IntroduceForm;
}

class IntroduceForm : public QWidget
{
    Q_OBJECT

public:
    explicit IntroduceForm(QWidget *parent = nullptr);
    ~IntroduceForm();

    void setDramaName(QString name);
    void setDramaCommentGrade(double grade);
    void setDramaSetCounts(int count);
    void setDramaPlayCounts(int count);
    void setCommentCheckabelCounts(int num);
    void setCommentStarts(int starts);
private:
    Ui::IntroduceForm *ui;
};

#endif // INTRODUCEFORM_H
