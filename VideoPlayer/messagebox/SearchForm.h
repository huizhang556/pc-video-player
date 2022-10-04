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

    void initWorkUi();
    void chandleSignalsAndSlot();

public slots:
    void    slot_addHotRecommendItems(const QStringList & str_list);

protected:
    void leaveEvent(QEvent *event) override;
private:
    Ui::SearchForm *ui;

private slots:
    void clearHistoryList();
public slots:
    void addHistoryItem(QString his);

    void closeSearchForm();
};

#endif // SEARCHFORM_H
