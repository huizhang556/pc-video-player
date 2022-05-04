#include "Global.h"
//类外初始化全局变量
//不同模式下选择不同的路径,可通过变换模式查看（变红）
#ifdef QT_DEBUG
        QString Global::appDirPath = QString("E:/QtProjects/000QtDemo_51ctodemo/04_20SubVideoPlayer/VideoPlayer");
#else
        QString Global::appDirPath = QCoreApplication::applicationDirPath();
#endif

Global::Global(QObject *parent) : QObject(parent)
{

}
