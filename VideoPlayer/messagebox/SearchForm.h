#ifndef SEARCHFORM_H
#define SEARCHFORM_H

#include <QWidget>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>

/*******搜索框---热搜+历史记录*********/

enum SHOWTYPE
{
    HISHOT = 0,//历史记录+热推
    RESFIND = 1,//搜索结果显示
    NORMAL = 2 //正常显示
};

namespace Ui {
class SearchForm;
}

class SearchForm : public QWidget
{
    Q_OBJECT

public:
    explicit SearchForm(QWidget *parent = nullptr);
    ~SearchForm();

    void    initWorkUi();
    void    chandleSignalsAndSlot();
    void    showUI(SHOWTYPE type);

public slots:
    void    slot_addHotRecommendItems(const QStringList & str_list);
    void    slot_showSearchResult(const QString str);

protected:
    void leaveEvent(QEvent *event) override;
private:
    Ui::SearchForm *ui;
    QNetworkAccessManager   *m_manger = nullptr;

private slots:
    void clearHistoryList();

public slots:
    void addHistoryItem(QString his);

    void closeSearchForm();

signals:
    void    sig_SendToMoreHots();//更多热搜
};

#endif // SEARCHFORM_H
