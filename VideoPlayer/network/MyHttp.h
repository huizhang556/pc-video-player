#ifndef MYHTTP_H
#define MYHTTP_H

#include <QTcpSocket>

class MyHttp : public QTcpSocket
{
public:
    MyHttp();

    QString get_fileList(QString url, int port);//获取网络文件列表 url 地址 端口

    void get_file();

    ~MyHttp();
};

#endif // MYHTTP_H
