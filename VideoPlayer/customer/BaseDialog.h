#ifndef BASEDIALOG_H
#define BASEDIALOG_H

/***********自定义基础QDialog**********/
//功能：
//0.适配不同的操作系统（目前为:win和linux）
//1.自定义或保留系统标题栏
//2.自适应拖动改变大小或固定带小

#include <QDialog>


class BaseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BaseDialog(QWidget *parent = nullptr);
    ~BaseDialog();

private:

};

#endif // BASEDIALOG_H
