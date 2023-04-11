#ifndef NATIONLITY_H
#define NATIONLITY_H
#include "global/Global.h"
#include <QMap>
#include <QList>
#include <QWidget>
#include <QScrollBar>
#include <QListWidget>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNodeList>
#include <QDebug>

namespace Ui {
class Nationlity;
}

class Nationlity : public QWidget
{
    Q_OBJECT
private:

public:
    explicit Nationlity(QWidget *parent = nullptr);
    ~Nationlity();

    struct CityInfo
        {
            QString cityName;                   // 城市名字
            QList<QString> regionName;          // 城市下的区的名字
        };

    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

//    static  Nationlity* getInstance();

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::Nationlity *ui;
    QString     m_country   = "";
    QString     m_province  = "";
    QString     m_city      = "";
    QMap<QString, QList<CityInfo>> m_ChinaCityInfo;
//    static  Nationlity* m_pInstance;

private:
    void           disposeXML();
    QList<QString> getCountryName(void);
    QList<QString> getProvinceName(QString& country);
    QList<QString> getCityName(QString& province);
    void    findKeyWordResults(QListWidget *listwidget, QString keyword);//检索关键字

private slots:
    void    slot_countryChanged(QString country);
    void    slot_provinceChanged(QString province);

signals:
    void    sig_send_selectedtext(QString);
};

#endif // NATIONLITY_H
