#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include "database/dataBase.h"
#include "customer/BaseDialog.h"
#include "videomodels/MultipPlayer.h"
#include "creator/producer/FilesItem.h"
#include <QDialog>
#include <QEvent>
#include <QRect>
#include <QScrollBar>
#include <QCheckBox>
#include <QListWidgetItem>
#include <QDebug>

namespace Ui {
class SortDialog;
}

class SortDialog : public BaseDialog
{
    Q_OBJECT
private:
    explicit SortDialog(QWidget *parent = nullptr);

public:
    ~SortDialog();
    void        initWorkUI();
    void        handleSignalsAndSlots();
    void        setInstallEventFilter();
    static      SortDialog* getInstance();
    void        exec_(const QString& group_id);

protected:
    bool        eventFilter(QObject *watched, QEvent *event)override;

private:
    void        findKeyWordResult(QListWidget* listwidget, QString keyword);//关键字检索
    QCheckBox*  getItemCheckedButton(QListWidgetItem* item, const QString& objname);//获取QCheckBox
    FilesItem*  getItemWidget(QListWidgetItem* item, const QString& objname);//获取FilesItem

private slots:
    void        slot_initCurUserGroups();//添加当前用户下用户合集
    void        slot_addItemsTo_HJ(QList<QUrlQuery>& querys, const QString &g_id);//添加某个用户下所有合集(combobox展示)
    void        slot_addItemsTo_MEDIA(QList<QVariant>& medias);//添加某个用户下某个合集所有item
    void        slot_addItemsTo_SORTMEDIA(QList<QVariant>& medias);//添加某个用户下某个分类类型下所有items
    void        slot_addCheckedItemsFromSortToHJ_DB();//分类往对应合集数据库添加新的(已经勾选的)itmes，并刷新
    void        slot_removeItemsFromHJ_DB_UI();//从对应合集数据库删除所有勾选的item并更新UI
    void        slot_removeItemsFromSort_DB_UI();//从对应分类数据库删除所有勾选的item并更新UI
    void        slot_combobox_HJ_changed(int index);//响应合集改变
    void        slot_combobox_SORT_changed(int index);//响应分类改变

private:
    Ui::SortDialog *ui;
    QString     m_groupid;
    QString     m_curtype;
    bool        m_isMax = false;
    QRect       m_oldRect;//保存最大化之前的信息
    static      SortDialog* m_pInstance;

signals:
    void       sig_init();
    void       sig_HJ_batch();
    void       sig_HJ_batchexit();
    void       sig_HJ_selectall();
    void       sig_HJ_delete();
    void       sig_HJ_batchclear();
    void       sig_HJ_batchdownload();

};

#endif // SORTDIALOG_H
