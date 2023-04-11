#ifndef CHANGEHEAD_H
#define CHANGEHEAD_H
#include "creator/producer/UploadWork.h"
#include "login/HeadLabel.h"
#include "database/dataBase.h"
#include "customer/BaseDialog.h"
#include "login/Nationlity.h"

#include <QDialog>
#include <QBuffer>
#include <QPixmap>
#include <QStyle>
#include <QTimer>
#include <QImage>
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

//打开类型
enum OPENTYPE
{
    PER_INFO,
    PER_HEAD,
    GENERAL
};

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
    void    setInstallEventFilter();
    static  ChangeHead* getInstance();

public slots:
    void    exec_(OPENTYPE type);

public:
    //剪裁类型
    enum CLIPTYPE
    {
        CLIP_RECT,   //矩形
        CLIP_CIRCLE, //圆形
        CLIP_CUSTOM  //自定义
    };

public slots:
    void    slot_setCurViewHeader(const QString& pixmap);
    void    slot_setCurViewHeader(QPixmap pixmap);
    void    slot_addHeader_history(const QString &pixid, const QString& headers);//添加历史头像
    void    slot_addHeader_man(const QString& headers);//添加通用男头像
    void    slot_addHeader_woman(const QString& headers);//添加通用女头像
    void    slot_addHeader_gif(const QString& headers);//添加通用动态头像
    void    slot_inserHeadToDB(bool success, QString url, QString md5);

protected:
    void    wheelEvent(QWheelEvent* event)override;
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    Ui::ChangeHead *ui;
    QGraphicsScene      *m_scence   =   nullptr;
    QGraphicsPixmapItem *m_pixItem  =   nullptr;
    QString             m_curPixPath;
    qreal               m_viewRotate = 0;//view 旋转角度
    Nationlity          *m_nationlity   =   nullptr;
    QPushButton         *m_curRecBtn    =   nullptr;
    static  ChangeHead* m_pInstance;

private:
    void    resetRotate();//场景恢复正常角度
    void    setOperateTip(const QString&tip, const int duration);
    QPushButton* getDeleteButton(QListWidgetItem* item, const QString& objName);
    bool    uplaodUserCurHeader(const QByteArray &pic_bytedata);//上传头像

    void    setUserNick(const QString& nick);
    void    setUserVip(const int grade);
    void    setUserCreateTime(const QString& create);
    void    setUserLoginTime(const QString& login);
};

#endif // CHANGEHEAD_H
