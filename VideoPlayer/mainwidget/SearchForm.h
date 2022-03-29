#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QWidget>

/*******搜索框---热搜+历史记录*********/
namespace Ui {
class SearchForm;
}

class SearchForm : public QWidget
{
    Q_OBJECT

public:
    explicit SearchForm(QWidget *parent = nullptr);
    ~SearchForm();
protected:
    void leaveEvent(QEvent *event) override;
private:
    Ui::SearchForm *ui;
};

#endif // SEARCHFORM_H
