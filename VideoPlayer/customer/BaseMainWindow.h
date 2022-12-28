#ifndef BASEMAINWINDOW_H
#define BASEMAINWINDOW_H


/***********自定义基础QMainWindow**********/
//功能：
//0.适配不同的操作系统（目前为:win和linux）
//1.自定义或保留系统标题栏
//2.自适应拖动改变大小或固定带小

#include <QMainWindow>


class BaseMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit BaseMainWindow(QWidget *parent = nullptr);
    ~BaseMainWindow();

private:

};

#endif // BASEMAINWINDOW_H
