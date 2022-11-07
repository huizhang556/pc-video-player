#ifndef CUSSTACKWIDGET_H
#define CUSSTACKWIDGET_H
//主界面调节参数
#define SACLWIDTH   1200 //开始放大最小宽度1200
#define FIXEDHEIGHT 360  //小于放大宽度设置为固定高 360
#define SCALSIZE    0.28 //放大时 高/宽 比例
#define MINWINSIZE  QSize(830,FIXEDHEIGHT)  //界面最小size
#define RESIZESIZE  QSize(1160,360)     //默认加载是size（一般会被重置）

#define BUTTONSIZE  QSize(40,130)
#define MINWIDTH   85
#define MINHEIGHT   40
#define BUTTONMARGIN 10

#include "CusStackWidget.h"
#include "CusPushButton.h"

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
    void    setSelectType(int type);

protected:
    bool    eventFilter(QObject *watched, QEvent *event) override;
    void    paintEvent(QPaintEvent* event) override;

public slots:
    void    slot_addItemToStackWgt(const QString& list_pic);
    void    slot_addToStackPictures(const QStringList & introduce,const QStringList & list_pic);
    void    slot_setCheckButton(QAbstractButton* button);
    void    slot_setCurrentIndex(int index);

private:
    void    update_W_H_scale();
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
    bool                    m_button;
    bool                    m_frame;
    static  QString         m_appDir;
};

#endif // CUSSTACKWIDGET_H
