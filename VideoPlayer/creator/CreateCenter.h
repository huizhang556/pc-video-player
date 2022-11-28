/**用户创作中心**/
#ifndef CREATECENTER_H
#define CREATECENTER_H

#include <QWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class CreateCenter;
}

class CreateCenter : public QWidget
{
    Q_OBJECT

    explicit CreateCenter(QWidget *parent = nullptr);
public:
    ~CreateCenter();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventer();
    static  CreateCenter* getInstance();

protected:
    void    mousePressEvent(QMouseEvent *event)override;

private:
    Ui::CreateCenter *ui;
    static  CreateCenter* m_pInstance;
};

#endif // CREATECENTER_H
