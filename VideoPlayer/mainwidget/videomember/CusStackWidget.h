#ifndef CUSSTACKWIDGET_H
#define CUSSTACKWIDGET_H
#define BUTTONSIZE  QSize(40,130)
#define MINWIDTH   85
#define MINHEIGHT   40
#define BUTTONMARGIN 10

#include "CusStackWidget.h"
#include <QSize>
#include <QLabel>
#include <QList>
#include <QWidget>
#include <QAction>
#include <QPainter>
#include <QLayout>
#include <QStringList>
#include <QPaintEvent>
#include <QPushButton>
#include <QButtonGroup>
#include <QStackedWidget>

namespace Ui {
class CusStackWidget;
}

class CusStackWidget : public QStackedWidget
{
    Q_OBJECT

public:
    explicit CusStackWidget(QWidget *parent = nullptr);
    ~CusStackWidget();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;
    void    paintEvent(QPaintEvent* event) override;

public slots:
    void    slot_addToStackPictures(const QStringList & introduce,const QStringList & list_pic);
    void    slot_setCheckButton(QAbstractButton* button);
    void    slot_setCurrentIndex(int index);
private:
    void    updateButtonGeometry();

private:
    QButtonGroup            *m_buttonGroup  =   nullptr;
    QPushButton             *m_buttonSub    =   nullptr;
    QPushButton             *m_buttonAdd    =   nullptr;
    QFrame                  *m_bottomFrame  =   nullptr;
    QHBoxLayout             *m_hbLayout     =   nullptr;
    QStringList             m_switchList;
    QStringList             m_pictureList;
    int                     m_counts = 0;
    int                     m_currentIndex = 0;
    QList<QPushButton*>     m_buttonActions;
    static  QString         m_appDir;
};

#endif // CUSSTACKWIDGET_H
