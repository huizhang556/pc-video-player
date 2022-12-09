#include "UploadWork.h"

UploadWork::UploadWork(QObject *parent) : QObject(parent)
{

}

UploadWork::~UploadWork()
{
    delete m_file;
    delete m_manager;
}

void UploadWork::slot_receiveData_accept(const QUrl &media_url)
{
    //00---打开文件
    QString filePath = QDir::toNativeSeparators(media_url.toString());//移除第一个/ 重点：MSVC编译器一定要把文件路径转换正确
    if(filePath.isNull() || filePath.isEmpty()) return;
    m_file = new QFile(filePath);
    QString fileNamee = m_file->fileName();
    qDebug() << "file-->filename(loginname) = "<< fileNamee;
    QFileInfo  info(filePath);
    QString fileName = info.fileName();
    qDebug() << "info-->filename(name) = "<< fileName;
    QString suffix  = info.suffix();
    qDebug() << "file suffix = "<< suffix;//flv mp3 mp4
    m_file->open(QIODevice::ReadOnly);

    //01---构造json文本部分
    //上传格式
    //http://10.1.50.90:8080/group/upload
    //参数：
    //file:上传的文件
    //scene:场景
    //output:输出
    //path:自定义路径
//    QJsonObject jsonObj;
//    jsonObj.insert("file",file);//请求键值对
//    jsonObj.insert("scene","default");
//    jsonObj.insert("output","json");
//    jsonObj.insert("path","videos");

//    QJsonDocument jsonDoc = QJsonDocument(jsonObj);//构造方式的一种
//    QByteArray post_data = jsonDoc.toJson(QJsonDocument::Compact);//两种格式
//    QHttpPart dataPart;
//    dataPart.setHeader(QNetworkRequest::ContentDispositionHeader,QVariant());
//    dataPart.setBody(post_data);

    QHttpPart namePart;
    namePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"filename\""));
    namePart.setBody(fileName.toUtf8());//qstring--->qbytearray  自定义名称

    QHttpPart scenePart;
    scenePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"scene\""));
    scenePart.setBody("default");//自定义场景

    QHttpPart outputPart;
    outputPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"output\""));
    outputPart.setBody("json");//指定输出格式

    QHttpPart pathPart;
    pathPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"path\""));
    pathPart.setBody(QString("cusmedias").toUtf8());//自定义存储路径

    //02---构造文件部分
    QHttpPart filePart;
    //判断文件类型
    QString cth_suffix  = getContentTypeHeader(suffix);
    filePart.setHeader(QNetworkRequest::ContentTypeHeader,QVariant(cth_suffix));//不同文件传输的时候，只需要修改ContentTypeHeader类型，如果不加这句，不返回文件信息
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader,QVariant(QString("form-data; name=\"file\";filename=\"%1\";").arg(fileName)));
    filePart.setBodyDevice(m_file);//大文件上传

    //03---组合成QHttpMultiPart
    QHttpMultiPart *multipPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);//必须指定格式
    multipPart->append(namePart);
    multipPart->append(scenePart);
    multipPart->append(outputPart);
    multipPart->append(pathPart);
    multipPart->append(filePart);


    //04---post请求数据
    m_manager = new QNetworkAccessManager();
    QNetworkRequest request_post;
    request_post.setUrl(QUrl("http://43.143.226.251:8080/group1/upload"));
//    request_post.setHeader(QNetworkRequest::ContentTypeHeader,"multipart/form-data; boundary=------WebKitFormBoundary88asdgewtgewx");
     m_reply = m_manager->post(request_post,multipPart);

    //05---接收QNetworkReply返回数据
     connect(m_manager,&QNetworkAccessManager::finished,this,&UploadWork::finshedSlot);
     connect(m_reply,&QNetworkReply::uploadProgress,[=](qint64 bytesSent, qint64 bytesTotal){
         if(bytesSent > 0)
         {
             emit sig_work_uploadprogress(bytesSent,bytesTotal);
         }
     });
}

QString UploadWork::getContentTypeHeader(const QString &suffix)
{
    //此处列举一些常用的类型，后续可以添加
    if( "flv" == suffix)
    {
        return  "video/flv";
    }
    else if("3gp" == suffix)
    {
        return "video/3gpp";
    }
    else if("wav" == suffix)
    {
        return "audio/x-wav";
    }
    else if("avi" == suffix)
    {
        return "video/x-msvideo";
    }
    else if("mp4" == suffix)
    {
        return "video/mp4";
    }
    else if("mp3" == suffix)
    {
        return "audio/x-mpeg";
    }
    else if("aac" == suffix)
    {
        return "audio/x-aac";
    }
    else if("png" == suffix)
    {
        return "image/png";
    }
    else if("gif" == suffix)
    {
        return "image/gif";
    }
    else if("jpg" == suffix)
    {
        return "image/jpeg";
    }
    else if("jpeg" == suffix)
    {
        return "image/jpeg";
    }
    else if("xml" == suffix)
    {
        return "text/plain";
    }
    else if("txt" == suffix)
    {
        return "text/plain";
    }
    else if("html" == suffix)
    {
        return "text/html";
    }
}

void UploadWork::getJson(QJsonObject &jsonObj)
{
    //    json返回格式
    //    {
    //      "url": "http://82.156.175.81:8080/group1/video0822/《青花瓷》.flv?name=%E3%80%8A%E9%9D%92%E8%8A%B1%E7%93%B7%E3%80%8B.flv&download=1",
    //      "md5": "50c9e31de3386c58ac2d50f3b0653a93",
    //      "path": "/group1/video0822/《青花瓷》.flv",
    //      "domain": "http://82.156.175.81:8080",
    //      "scene": "default",
    //      "size": 65497351,
    //      "mtime": 1661184028,
    //      "scenes": "default",
    //      "retmsg": "",
    //      "retcode": 0,
    //      "src": "/group1/video0822/《青花瓷》.flv"
    //    }
        qDebug() <<QString(u8"上传完成解析到的数据：");
        QString url     = jsonObj.value("url").toString();      qDebug() << url;
        QString md5     = jsonObj.value("md5").toString();      qDebug() << md5;
        QString path    = jsonObj.value("path").toString();     qDebug() << path;
        QString domain  = jsonObj.value("domain").toString();   qDebug() << domain;
        int     size    = jsonObj.value("size").toInt();        qDebug() << size;
        QString src     = jsonObj.value("src").toString();      qDebug() << src;
        int     pos     = url.indexOf("?");//以第一个？位置处截断
        QString savePath = url.left(pos);
        qDebug() << "really file savepath = " << savePath;
        //插入数据库
        if(!savePath.isEmpty() && !md5.isEmpty())
        {
            emit sig_work_finished(savePath,md5);
//            qDebug() << QString(u8"回传信息已发出！");
        }
}

void UploadWork::getStatusCode(QNetworkReply *reply)
{
    // 获取http状态码
    QVariant statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(statusCode.isValid())
        qDebug() << "status code=" << statusCode.toInt();//2xx 3xx 4xx 5xx

    QVariant reason = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    if(reason.isValid())
        qDebug() << "reason=" << reason.toString();

    QNetworkReply::NetworkError err = reply->error();
    if(err != QNetworkReply::NoError) {
        qDebug() << "Failed: " << reply->errorString();
    }
    else {
        // 获取返回内容
        QByteArray bytes = reply->readAll();
        qDebug() << reply->readAll();
        //001---static QJsonDocument fromRawData(const char *data, int size, DataValidation validation = Validate);
        //002---static QJsonDocument fromBinaryData(const QByteArray &data, DataValidation validation  = Validate);
        //003---static QJsonDocument fromVariant(const QVariant &variant);
        //004---static QJsonDocument fromJson(const QByteArray &json, QJsonParseError *error = nullptr);
        QJsonDocument jsonDoc = QJsonDocument::fromJson(bytes);//001---先转换为QJsonDocument
        QJsonObject jsonObj = jsonDoc.object();//002---再转换为QJsonObject
        getJson(jsonObj);//解析QJsonObject
    }
}

void UploadWork::finshedSlot(QNetworkReply *reply)
{
    getStatusCode(reply);
    reply->deleteLater();
    m_file->close();
}
