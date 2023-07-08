#include "UserList.h"
#include "ui_UserList.h"

UserList::UserList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserList)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);//鼠标点击外部，界面自动隐藏
    setAttribute(Qt::WA_TranslucentBackground);
    setFocusPolicy(Qt::NoFocus);
    initWorkUI();
    installEventFilter(this);
}

UserList::~UserList()
{
    delete ui;
}

void UserList::initWorkUI()
{
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->stackedWidget_results->setCurrentWidget(ui->page_resulits);

    //加载本地配置文件
//    config_initUser();
}



void UserList::slot_addItem(UITEMACT TYPE, const QString& user_nick, const QString& user_pwd, const QString& user_header)
{
    UserItem *item = new UserItem(user_nick,user_pwd,user_header);
    if(TYPE == UITEMACT::ITEM_ADD)
    {
        ui->verAddLayout->insertWidget(0,item);
    }
    else if(TYPE == UITEMACT::ITEM_ADJ)
    {
        ui->verAddLayout->insertWidget(ui->verAddLayout->count()-1,item);
    }

   //1.移除item
    connect(item,&UserItem::sig_item_remove,[=](QString user_nick){
        ui->verAddLayout->removeWidget(item);
        item->deleteLater();
        config_removeUser(user_nick);
    });

    //2.点击显示用户名
    connect(item,&UserItem::sig_item_clicked,[=](QString name){
        emit sig_list_username(name);
        m_curWidget = item;//定位当前的对象
    });
}

void UserList::slot_removeItem(const QString& userName)
{

}

void UserList::slot_findUserListResult(const QString &name)
{
    getItemNameButton("pushButton_name",name);
}

const QString UserList::config_getUserPwd(const QString &user_nick)
{
    QFile file(Global::appDirPath + "/config/users_list.json");
    if(!file.open(QFile::ReadOnly | QFile::Truncate))
    {
        qDebug() <<QString(u8"打开文件失败！");
        return "";
    }
    //打开成功
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString json = stream.readAll();
    file.close();

    //报错类
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8(),&jsonError);
    //首先确保文档不为null,然后报错类型不为：NoError 说明有错误！
    if(jsonError.error != QJsonParseError::NoError && !doc.isNull())
    {
        qDebug() << "Json格式错误！" << jsonError.error;
        return "";
    }

    //获取根对象{ }
    QJsonObject rootObj = doc.object();
    //获取对象数组
    QJsonValue loginValue = rootObj.value(u8"login");
    if(loginValue.type() == QJsonValue::Array)//是数组
    {
        QJsonArray login_array = loginValue.toArray();//QJsonValue 转换为对象数组
        //先查找数组中对应的key的index
        for(int i = 0; i < login_array.count(); i++)
        {
            if(login_array.at(i).toObject().value(u8"user_nick").toString() == user_nick)
            {
                QString user_pwd = login_array.at(i).toObject().value(u8"user_pwd").toString();
                qDebug() << QString(u8"找到了用户：%1 的加密密码为：%2").arg(user_nick).arg(user_pwd);
                return user_pwd;
            }
        }
        //能走到这一步，说明遍历完以后也没找到对应用户密码
        qDebug() << QString(u8"没有找到用户：%1 的加密密码！").arg(user_nick);
    }
}

bool UserList::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this && event->type() == QEvent::Leave)
    {
        this->close();
    }
    return  QWidget::eventFilter(watched,event);
}

QPushButton *UserList::getItemNameButton(const QString &objName, const QString &userName)
{
    for(int i = 0; i < ui->verAddLayout->count(); i++)
    {
        QWidget *itemWidget = ui->verAddLayout->itemAt(i)->widget();
        if(itemWidget != nullptr)
        {
            QPushButton* nameBtn = itemWidget->findChild<QPushButton*>(objName);
            if(nameBtn != nullptr && nameBtn->text().contains(userName))
            {
                itemWidget->show();
//                qDebug() << QString(u8"找到按钮,显示对应item");

            }
            else
            {
                itemWidget->hide();
//                qDebug() << QString(u8"没找到按钮,隐藏对应item");
            }
        }
    }
    return nullptr;
}

void UserList::checkedItemsCounts()
{
    if(ui->verticalLayout->count() < 2)
    {
        setFixedHeight(ui->verAddLayout->count()*48);
        qDebug() << QString(u8"三个及以下！");
    }
    else
    {
        setFixedHeight(156);
        qDebug() << QString(u8"三个以上！");
    }
}

//本地解析配置文件初始化用户登录列表
bool UserList::config_initUser()
{
    QFile file(Global::appDirPath + "/config/users_list.json");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Truncate))
    {
        qDebug() <<QString(u8"打开用户列表文件失败！");
        return false;
    }
    //打开成功
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString userslist_json = stream.readAll();
    file.close();

    //解析本地配置json
    QJsonParseError jsonError;
    QJsonDocument doc = QJsonDocument::fromJson(userslist_json.toUtf8(),&jsonError);
    //判断是否解析失败
    if(jsonError.error != QJsonParseError::NoError && !doc.isNull())
    {
        qDebug() << QString(u8"Json格式错误！%1").arg(jsonError.error);
        return false;
    }
    //获取{ }
    QJsonObject rootObj = doc.object();//获取根对象
    //获取数组对象
    QJsonValue loginedValue = rootObj.value(u8"login");
    if(loginedValue.type() == QJsonValue::Array)//判断是数组
    {
        QJsonArray logined_array = loginedValue.toArray();//转换为QJsonArray
        //遍历查找用户信息
        for(int i = 0; i < logined_array.count(); i++)
        {
            if(!logined_array.at(i).toObject().value(u8"user_nick").toString().isEmpty())//用户名不为空
            {
                //添加一条用户信息(先找到的先插入)
                slot_addItem(UITEMACT::ITEM_ADJ,logined_array.at(i).toObject().value(u8"user_nick").toString(),
                             logined_array.at(i).toObject().value(u8"user_pwd").toString(),
                             logined_array.at(i).toObject().value(u8"user_header").toString());
            }
        }
        return true;
    }
}

//配置文件添加一条用户信息
bool UserList::config_addNewUser(const QString user_nick, const QString user_pwd, const QString user_header)
{
    QFile file(Global::appDirPath + "/config/users_list.json");
    if(!file.open(QFile::ReadOnly | QFile::Truncate))
    {
        qDebug() <<QString(u8"打开文件失败！");
        return false;
    }
    //打开成功
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString json = stream.readAll();
    file.close();

    //报错类
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8(),&jsonError);
    //首先确保文档不为null,然后报错类型不为：NoError 说明有错误！
    if(jsonError.error != QJsonParseError::NoError && !doc.isNull())
    {
        qDebug() << "Json格式错误！" << jsonError.error;
        return false;
    }

    //正式插入(或者调整顺序)用户信息
    UITEMACT TYPE = config_addUserToJson(doc,user_nick,user_pwd,user_header);
    //是否添加item根据返回类型确定
    if(UITEMACT::ITEM_ADD == TYPE)
    {
        slot_addItem(TYPE,user_nick,user_pwd,user_header);
        qDebug() << QString(u8"本次操作：添加item");
    }
    else if(UITEMACT::ITEM_ADJ == TYPE)
    {
        //配置列表调整顺序，UI调整顺序
        if(m_curWidget != nullptr)
        {
            ui->verAddLayout->removeWidget(m_curWidget);
            ui->verAddLayout->insertWidget(0,m_curWidget);
        }
        qDebug() << QString(u8"本次操作：调整item顺序");
    }

    // 重写打开文件，覆盖原有文件，达到删除文件全部内容的效果
    QFile writeFile(Global::appDirPath + "/config/users_list.json");
    if (!writeFile.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << "can't open error!";
        return false;
    }

    // 将修改后的内容写入文件
    QTextStream wirteStream(&writeFile);
    wirteStream.setCodec("UTF-8");// 设置读取编码是UTF8
    wirteStream << doc.toJson();// 写入文件
    writeFile.close();

}

//判断类型（原有还是新添加）
const UITEMACT UserList::config_addUserToJson(QJsonDocument &doc, const QString user_nick, const QString user_pwd, const QString user_header)
{
    //获取根对象{ }
    QJsonObject rootObj = doc.object();
    //获取对象数组
    QJsonValue loginValue = rootObj.value(u8"login");
    if(loginValue.type() == QJsonValue::Array)//是数组
    {
        QJsonArray login_array = loginValue.toArray();//QJsonValue 转换为对象数组
        //先查找数组中对应的kery的index
        for(int i = 0; i < login_array.count(); i++)
        {
            //如果找到，应该往前调整顺序
            if(login_array.at(i).toObject().value(u8"user_nick").toString() == user_nick)
            {
                QJsonValue jsonVal = login_array.takeAt(i);
                login_array.insert(0,jsonVal);//调整为头一个
                qDebug() << QString(u8"找到了用户：%1 的信息！将其调整为第一个信息.").arg(user_nick);
                rootObj[u8"login"] = login_array;//修改要生效（注意要使用:u8）
                //重新设置doc为最新修改的内容
                doc.setObject(rootObj);
                return UITEMACT::ITEM_ADJ;//结束函数执行
            }
        }
        //能执行到此，说明没有跳出函数，就可以添加用户信息
        qDebug() << QString(u8"没有找到用户：%1 的信息！着手添加该用户信息：").arg(user_nick);
        QJsonObject logined_user;
        logined_user.insert(u8"user_nick",user_nick);
        logined_user.insert(u8"user_pwd",user_pwd);
        logined_user.insert(u8"user_header",user_header);
        login_array.insert(0,logined_user);//头插法

        rootObj[u8"login"] = login_array;//修改要生效（注意要使用:u8）
        //重新设置doc为最新修改的内容
        doc.setObject(rootObj);
        return UITEMACT::ITEM_ADD;//结束函数执行
    }
}

//配置文件移除一条用户信息
bool UserList::config_removeUser(const QString &user_nick)
{
    QFile file(Global::appDirPath + "/config/users_list.json");
    if(!file.open(QFile::ReadOnly | QFile::Truncate))
    {
        qDebug() <<QString(u8"打开文件失败！");
        return false;
    }
    //打开成功
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString json = stream.readAll();
    file.close();

    //报错类
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8(),&jsonError);
    //首先确保文档不为null,然后报错类型不为：NoError 说明有错误！
    if(jsonError.error != QJsonParseError::NoError && !doc.isNull())
    {
        qDebug() << "Json格式错误！" << jsonError.error;
        return false;
    }

    //获取根对象{ }
    QJsonObject rootObj = doc.object();
    //获取对象数组
    QJsonValue loginValue = rootObj.value(u8"login");
    if(loginValue.type() == QJsonValue::Array)//是数组
    {
        QJsonArray login_array = loginValue.toArray();//QJsonValue 转换为对象数组
        //先查找数组中对应的kery的index
        for(int i = 0; i < login_array.count(); i++)
        {
            if(login_array.at(i).toObject().value(u8"user_nick").toString() == user_nick)
            {
                login_array.removeAt(i);
                qDebug() << QString(u8"找到并删除了用户：%1 的信息！").arg(user_nick);
            }
            else
            {
                qDebug() << QString(u8"没有找到用户：%1 的信息！").arg(user_nick);
            }
        }

        rootObj[u8"login"] = login_array;//修改要生效（注意要使用:u8）
    }


    //重新设置doc为最新修改的内容
    doc.setObject(rootObj);

    // 重写打开文件，覆盖原有文件，达到删除文件全部内容的效果
    QFile writeFile(Global::appDirPath + "/config/users_list.json");
    if (!writeFile.open(QFile::WriteOnly | QFile::Truncate)) {
        qDebug() << "can't open error!";
        return false;
    }

    // 将修改后的内容写入文件
    QTextStream wirteStream(&writeFile);
    wirteStream.setCodec("UTF-8");// 设置读取编码是UTF8
    wirteStream << doc.toJson();// 写入文件
    writeFile.close();
}
