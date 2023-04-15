#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include "customer/BaseDialog.h"
#include "database/dataBase.h"
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
    void    initWorkUI();
    void    handleSignalsAndSlots();
    void    setInstallEventFilter();
    static  SortDialog* getInstance();
    void    exec_(const QString& group_id);

protected:
    bool    eventFilter(QObject *watched, QEvent *event)override;

private:
    void       findKeyWordResult(QListWidget* listwidget, QString keyword);//关键字检索
    QCheckBox* getItemCheckedButton(QListWidgetItem* item, const QString& objname);
    FilesItem* getItemWidget(QListWidgetItem* item, const QString& objname);

private slots:
    void    slot_initCurUserGroups();
    void    slot_addItemsTo_HJ(QList<QUrlQuery>& querys, const QString &g_id);
    void    slot_addItemsTo_MEDIA(QList<QVariant>& medias);
    void    slot_addItemsTo_SORTMEDIA(QList<QVariant>& medias);

private:
    Ui::SortDialog *ui;
    QString m_groupid;
    bool    m_isMax = false;
    QRect   m_oldRect;//保存最大化之前的信息
    static  SortDialog* m_pInstance;

signals:
    void    sig_init();
    void    sig_HJ_batch();
    void    sig_HJ_batchexit();
    void    sig_HJ_selectall();
    void    sig_HJ_delete();
    void    sig_HJ_batchclear();
    void    sig_HJ_batchdownload();

};

#endif // SORTDIALOG_H
