/********************************************
 1. @ProjName:   04_20SubVideoPlayer
 2. @Author:     ZhangHui
 3. @Date:       2023-01-27
 4. @Brief:      继承QComboBox实现了一个显示磁盘剩余空间的功能
*********************************************/
#ifndef CCOMBOBOX_H
#define CCOMBOBOX_H

#include <QLabel>
#include <QWidget>
#include <QLayout>
#include <QComboBox>
#include <QFontMetrics>
#include <QStorageInfo>
#include <QDebug>

class CComboBox : public QComboBox
{
    Q_OBJECT

public:
    explicit CComboBox(QWidget *parent = nullptr);
    ~CComboBox();
    void    setDiskSpace(const QString& space);
    void    setCurrentText_(const QString& text);
    void    insertItem_(int index,const QString& text);
    void    insertItem_(int index, const QIcon &icon, const QString &text);

private:
    QString checkDiskStorageSpace(const QString& path);//获取磁盘剩余大小
    QString calSpaceSize(qint64 bytesTotal);//容量数值转换


private:
    QLabel  *label_space = nullptr;

};

#endif // CCOMBOBOX_H
