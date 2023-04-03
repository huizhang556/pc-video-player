#ifndef EXITDIALOG_H
#define EXITDIALOG_H
#define FIXSIZE QSize(320,260)
#include "global/Global.h"
#include <QDialog>
#include <QPoint>
#include <QDir>
#include <QPixmap>
#include <QCursor>
#include <QSettings>
#include <QMouseEvent>
#include <QButtonGroup>
#include <QGraphicsDropShadowEffect>
#include <QDebug>

//关闭窗口类型
enum CLOSE_TYPE
{
    _HIDE,//隐藏到托盘
    _CLOSE//直接关闭
};

namespace Ui {
class ExitDialog;
}

class ExitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExitDialog(QWidget *parent = nullptr);
    explicit ExitDialog(const QString title,const QString warn,QWidget *parent = nullptr);

    ~ExitDialog();
    void    initWorkUI();
    void    handleSignalsAndSlots();

    QString readIni() const;
    void    setIni();
    void    setCloseType();
    bool    getCloseType();

public:
    void    setCloseText(QString waring);

    bool   isShow;//必须为公有成员

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void sig_SendNotcloseMain();

    void sig_SendcloseMain(bool);//带个状态， 0 隐藏 1 关闭
private:
    Ui::ExitDialog      *ui;
    QButtonGroup        *m_buttonGroup  =  nullptr;
    QPoint              m_mvPoint;
    QString             m_iniPath;
    bool                m_closeType;

};

#endif // EXITDIALOG_H
