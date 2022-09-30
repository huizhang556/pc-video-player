#ifndef NEWLOGINFORM_H
#define NEWLOGINFORM_H

#include <QPoint>
#include <QAction>
#include <QPainter>
#include <QPaintEvent>
#include <QDialog>

namespace Ui {
class NewLoginForm;
}

class NewLoginForm : public QDialog
{
    Q_OBJECT

public:
    ~NewLoginForm();
    void        initWorkUI();
    void        chandleSignalsAndSLots();
    static      NewLoginForm* getInstance();

protected:
    void        paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;


private:
    explicit NewLoginForm(QWidget *parent = nullptr);
    Ui::NewLoginForm *ui;
    QPoint  m_mvPos;
    QAction *m_actionShowPwd;//查看密码
    static  NewLoginForm* m_pInstance;
};

#endif // NEWLOGINFORM_H
