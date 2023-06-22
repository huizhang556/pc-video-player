#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H
#include "UserDataItem.h"

#include <QWidget>
#include <QAction>
#include <QLayout>
#include <QLayoutItem>
#include <QButtonGroup>
#include <QDebug>



namespace Ui {
class DataAnalysis;
}

class DataAnalysis : public QWidget
{
    Q_OBJECT

public:
    explicit DataAnalysis(QWidget *parent = nullptr);
    ~DataAnalysis();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();

public slots:
    void    slot_addUserData(const QVariant& userData);

private:
    void    data_addUserData_myfans();//加载本用户粉丝数据
    void    data_addUserData_myattention();//加载给本用户曾经点过赞数据
    void    data_addUserData_mycollect();//加载本用户视频播放数据
    void    data_addUserData_mycommit();//加载本用户视频收藏数据
    void    data_setTypeTag(const QString& type);
    void    data_clearScrollAreaContents();
    void    data_findKeyWordsResults(QString keywords);
    void    data_setItemChecked();
    void    data_checkContentBlank();

private:
    Ui::DataAnalysis *ui;

    QAction         *m_searchAction     =   nullptr;
    QButtonGroup    *m_buttonGroup      =   nullptr;
};

#endif // DATAANALYSIS_H
