#ifndef MYSKIN_H
#define MYSKIN_H
#include "MySkinItem.h"
#include "global/Global.h"

#include <QPoint>
#include <QDialog>
#include <QListWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <QButtonGroup>
#include <QAbstractButton>

namespace Ui {
class MySkin;
}

class MySkin : public QDialog
{
    Q_OBJECT

    explicit MySkin(QWidget *parent = nullptr);
public:
    ~MySkin();
    void initWorkUI();
    void chandleSignalAndSlot();
    static  MySkin* getInstance();

protected:
    bool eventFilter(QObject *watch, QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private slots:
    void on_pushButton_close_clicked();
    void switchButtonToStackWidget(QAbstractButton *button);

private:
    QPushButton*    getListWidgetItemButton(QListWidget* listWidget, QListWidgetItem* item, QString objname);//在item中查找指定按钮
    void            setItemChangedStyle(QListWidget* listWidget, QListWidgetItem *current,QListWidgetItem *previous);
private:
    Ui::MySkin *ui;
    QButtonGroup        *btngroup   = nullptr;
    QPoint              m_mvPos;
    static MySkin  *m_pInstance;
};

#endif // MYSKIN_H
