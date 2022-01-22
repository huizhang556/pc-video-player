#include "MyHttp.h"
#include <QHostAddress>
#include <QString>
#include <string.h>

//http的表头文件
#define REQ " "

MyHttp::MyHttp()
{

}

/*获取网络文件列表 url 地址 端口*/
QString MyHttp::get_fileList(QString url, int port)
{
    QHostAddress serverIP;
    serverIP.setAddress(url);
    //链接到服务端
    connectToHost(serverIP,port);
    //等待数据连接
    waitForConnected();
   //获取http格式化的请求
    char buf[1024];
    memset(buf,0,sizeof(buf));
    //将格式化的字符串放在buf中 http表头文件+url地址
    sprintf(buf,REQ,url.toStdString().data());
    //阻塞式等待tcp写状态OK
    waitForBytesWritten();
    //将http请求发送到server端口
    write(buf,strlen(buf));
    //阻塞等待数据传输到本地
    waitForReadyRead();
    //保存从server端接收到的数据
    QString content;
    while(bytesAvailable() > 0)
    {
        memset(buf,0,sizeof(buf));
        read(buf,sizeof(buf));
        content += buf;
    }
    //等待阻塞断开完成
//    waitForDisconnected();
    //完成之后关闭socket
    close();
    //处理content数据 \r\n
    QStringList ls = content.split("\r\n");
//    return ls(ls.count()-1);
    return content;
}

/*通过http请求获取服务端mv*/
void MyHttp::get_file()
{

}

MyHttp::~MyHttp()
{

}
