#ifndef EXITDIALOG_H
#define EXITDIALOG_H
#include "global/Global.h"
#include <QDialog>
#include <QPoint>

namespace Ui {
class ExitDialog;
}

class ExitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExitDialog(QWidget *parent = nullptr);
    explicit ExitDialog(QString title,QString warn,QWidget *parent = nullptr);

    ~ExitDialog();

    QString readIni() const;

    void setIni(); 

public:
    bool   isShow;//必须为公有成员

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void sig_SendNotcloseMain();

    void sig_SendcloseMain();
private:
    Ui::ExitDialog      *ui;
    QPoint              m_mvPoint;
    QString             m_iniPath;
    QPoint              winPos;
    QPoint              nowPos;

};

#endif // EXITDIALOG_H
