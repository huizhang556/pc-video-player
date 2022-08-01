#ifndef GLOBAL_H
#define GLOBAL_H
#include <QDir>
#include <QObject>
#include <QString>
#include <QProcess>
#include <QApplication>

class Global : public QObject
{
    Q_OBJECT
public:
    explicit Global(QObject *parent = nullptr);
    static void registerLAVplayer();//注册播放器

    //声明共有静态变量
    static QString appDirPath;
signals:

public slots:
};

#endif // GLOBAL_H
