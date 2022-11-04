#ifndef CUSVERSTACKWGT_H
#define CUSVERSTACKWGT_H

#include <QWidget>
#include <QEvent>
#include <QLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QListWidget>
#include <QStringList>
#include <QDebug>

namespace Ui {
class CusVerStackWgt;
}

class CusVerStackWgt : public QStackedWidget
{
    Q_OBJECT

public:
    explicit CusVerStackWgt(QWidget *parent = nullptr);
    ~CusVerStackWgt();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

public slots:
    void    slot_addItemToCusVerStackWgt(const QString& picpath);
    void    slot_addToStackPictures(const QStringList & introduce,const QStringList & list_pic);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;

private:
    QListWidget             *m_rightListWidget  =   nullptr;
    QStringList             m_switchList;
    QStringList             m_pictureList;

   private:
    void    updateListWidgetGeometry();
};

#endif // CUSVERSTACKWGT_H
