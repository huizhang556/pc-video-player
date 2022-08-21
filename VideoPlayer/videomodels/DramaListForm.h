#ifndef DRAMALISTFORM_H
#define DRAMALISTFORM_H

#include <QWidget>

namespace Ui {
class DramaListForm;
}

class DramaListForm : public QWidget
{
    Q_OBJECT

public:
    explicit DramaListForm(QWidget *parent = nullptr);
    ~DramaListForm();
    void initWorkUI();
    void chandleSignalsAndSLots();
    void setDramaName(QString name);
    void setDramaCommentGrade(double grade);
    void setDramaSetCounts(int count);
    void setDramaPlayCounts(int count);
    void setCommentCheckabelCounts(int num);
    void setCommentStarts(int starts);

private:
    Ui::DramaListForm *ui;
};

#endif // DRAMALISTFORM_H
