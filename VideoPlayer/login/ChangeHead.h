#ifndef CHANGEHEAD_H
#define CHANGEHEAD_H

#include "login/HeadLabel.h"
#include "database/dataBase.h"
#include "customer/BaseDialog.h"

#include <QDialog>
#include <QPixmap>
#include <QStyle>
#include <QTimer>
#include <QBitmap>
#include <QRegion>
#include <QThread>
#include <QDateTime>
#include <QScrollBar>
#include <QWheelEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QDebug>

namespace Ui {
class ChangeHead;
}

class ChangeHead : public BaseDialog
{
    Q_OBJECT
private:
    explicit ChangeHead(QWidget *parent = nullptr);

public:
    ~ChangeHead();
    void    initWorkUI();
    void    handleSignalsAndSlots();
    static  ChangeHead* getInstance();
    void    exec_();

public slots:
    void    slot_setCurViewHeader(const QString& pixmap);
    void    slot_setCurViewHeader(QPixmap pixmap);
    void    slot_addHeader_history(const QString& headers);//添加历史头像
    void    slot_addHeader_man(const QString& headers);//添加通用男头像
    void    slot_addHeader_woman(const QString& headers);//添加通用女头像
    void    slot_addHeader_gif(const QString& headers);//添加通用动态头像
protected:
    void    wheelEvent(QWheelEvent* event)override;

private:
    Ui::ChangeHead *ui;
    QGraphicsScene      *m_scence   =   nullptr;
    QGraphicsPixmapItem *m_pixItem  =   nullptr;
    QString             m_curPixPath;
    qreal               m_viewRotate = 0;//view 旋转角度
    static  ChangeHead* m_pInstance;

private:
    void    resetRotate();//场景恢复正常角度
    QPushButton* getDeleteButton(QListWidgetItem* item, const QString& objName);
};

#endif // CHANGEHEAD_H
