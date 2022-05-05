#include "Global.h"
//类外初始化全局变量
//不同模式下选择不同的路径,可通过变换模式查看（变红）
#ifdef QT_DEBUG
        QString Global::appDirPath = QString("E:/QtProjects/000QtDemo_51ctodemo/04_20SubVideoPlayer/VideoPlayer");
#else
        QString Global::appDirPath = QDir::currentPath();//release时使用
#endif
//QString Global::appDirPath = QDir::currentPath();//静态全局变量使用applicationDirPath();为空
Global::Global(QObject *parent) : QObject(parent)
{

}
