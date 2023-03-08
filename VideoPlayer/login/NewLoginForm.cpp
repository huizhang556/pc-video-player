#include "NewLoginForm.h"
#include "ui_NewLoginForm.h"

//#ifdef Q_OS_WIN
//#include <qt_windows.h>
//#include <Windows.h>
//#include <windowsx.h>
//#pragma comment (lib,"user32.lib")
//#endif


//类外初始化
NewLoginForm* NewLoginForm::m_pInstance = nullptr;

NewLoginForm::NewLoginForm(QWidget *parent):
    QDialog(parent),
    ui(new Ui::NewLoginForm)
{
    ui->setupUi(this);
    setFixedSize(720,465);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowMinMaxButtonsHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    initWorkUI();
    initAnimations();
    chandleSignalsAndSLots();
}

NewLoginForm::~NewLoginForm()
{
    delete ui;
//    if(ani_show != nullptr)
//    {
//        delete ani_show;
//        ani_show = nullptr;
//    }

//    if(ani_top_hide != nullptr)
//    {
//        delete ani_top_hide;
//        ani_top_hide = nullptr;
//    }

//    if(ani_bom_hide != nullptr)
//    {
//        delete ani_bom_hide;
//        ani_bom_hide = nullptr;
//    }

    if(ani_opacity != nullptr)
    {
        delete ani_opacity;
        ani_opacity = nullptr;
    }

    if(aniGroup != nullptr)
    {
        delete aniGroup;
        aniGroup = nullptr;
    }

    //删除创建的单例
    if(m_pInstance != nullptr)
        delete m_pInstance;
    m_pInstance = nullptr;
}

void NewLoginForm::initWorkUI()
{
//    this->setContentsMargins(15,15,15,15);//为阴影留出空间
//    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
//    shadow_effect->setOffset(0,0);//阴影往边外（下和右）移出的距离
//    shadow_effect->setColor(QColor(93, 95, 96));
//    shadow_effect->setBlurRadius(15);//阴影也是个矩形，需要圆角
//    this->setGraphicsEffect(shadow_effect);

    //登录部分
    m_actionShowPwd = new QAction(QIcon(":/images/icon/passwd_hide.png"),"");
    m_actionShowPwd->setObjectName(QString("m_actionShowPwd"));
    m_actionShowPwd->setCheckable(true);
    m_actionShowPwd->setChecked(false);
    ui->lineEdit_telNumber->setPlaceholderText(QString(u8"请输入手机号码"));
    ui->lineEdit_checkCode->setPlaceholderText(QString(u8"请输入验证码"));
    ui->lineEdit_account->setPlaceholderText(QString(u8"手机/邮箱/账户名"));
    ui->lineEdit_userpwd->setPlaceholderText(QString(u8"登陆密码"));
    ui->lineEdit_userpwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_userpwd->addAction(m_actionShowPwd,QLineEdit::TrailingPosition);

    //注册部分
    m_act_pwd = new QAction(QIcon(":/images/icon/passwd_hide.png"),"");
    m_act_pwd->setObjectName(QString("m_act_pwd"));
    m_act_pwd->setCheckable(true);
    m_act_pwd->setChecked(false);
    ui->lineEdit_regis_telNumber->setMaxLength(20);
    ui->lineEdit_regis_checkCode->setMaxLength(18);
    ui->lineEdit_regis_email->setMaxLength(26);
    ui->lineEdit_regis_telNumber->setPlaceholderText(QString(u8"请输入注册手机号码或账号"));
    ui->lineEdit_regis_checkCode->setPlaceholderText(QString(u8"请输入验证码或密码"));
    ui->lineEdit_regis_checkCode->setEchoMode(QLineEdit::Password);
    ui->lineEdit_regis_checkCode->addAction(m_act_pwd,QLineEdit::TrailingPosition);

    //正则限制输入内容
    QRegExp regExp_account(QString(u8"[a-zA-Z\u4e00-\u9fa5][a-zA-Z0-9\u4e00-\u9fa5]+"));//汉字+字母+数字，不限制长度
    ui->lineEdit_regis_telNumber->setValidator(new QRegExpValidator(regExp_account, this));

    QRegExp regExp_pwd(QString(u8"^([A-Z]|[a-z]|[0-9]|[,.@]){6,18}$"));//大小写字母+数字+特殊符号（,.@）
    ui->lineEdit_regis_checkCode->setValidator(new QRegExpValidator(regExp_pwd, this));

    QRegExp regExp_email(QString(u8"[\\w!#$%&'*+/=?^_`{|}~-]+(?:\\.[\\w!#$%&'*+/=?^_`{|}~-]+)*@(?:[\\w](?:[\\w-]*[\\w])?\\.)+[\\w](?:[\\w-]*[\\w])?"));
    ui->lineEdit_regis_email->setValidator(new QRegExpValidator(regExp_email, this));


    //重置部分
    ui->lineEdit_fpwd_account->setPlaceholderText(QString(u8"请输入账号"));
    ui->lineEdit_fpwd_checkCode->setPlaceholderText(QString(u8"请输入验证码"));
    ui->lineEdit_firstpwd->setPlaceholderText(QString(u8"请输入新的密码"));
    ui->lineEdit_secondpwd->setPlaceholderText(QString(u8"再次输入新的密码"));
    ui->lineEdit_firstpwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_secondpwd->setEchoMode(QLineEdit::Password);
    ui->stackedWidget_right->setCurrentIndex(0);
    //解决QLineEdit回车键退出
    ui->pushButton_close->setFocusPolicy(Qt::NoFocus);//默认具有焦点
    ui->pushButton_register->setFocusPolicy(Qt::NoFocus);//默认具有焦点

    //combobox弹框问题
    ui->comboBox_area->installEventFilter(this);
    ui->comboBox_area->setFocusPolicy(Qt::NoFocus);
    ui->comboBox_regis_area->installEventFilter(this);
    ui->comboBox_regis_area->setFocusPolicy(Qt::NoFocus);

    //勾选协议（默认勾选）
    ui->radioButton_check->setCheckable(true);
    ui->radioButton_check->setChecked(true);
    ui->radioButton_regis_check->setCheckable(true);
    ui->radioButton_regis_check->setChecked(true);

    ui->tabWidget_login->setCurrentIndex(0);

    ui->pushButton_updateQR->setText(QString(u8"刷新二维码"));

    //二维码(初始化更新)
    update_QRcode();

}

void NewLoginForm::initAnimations()
{
//    int x_global = QApplication::desktop()->width();
//    int y_global = QApplication::desktop()->height();

    //显示动画
//    ani_show = new QPropertyAnimation(this, "geometry",this);
//    ani_show->setDuration(1000);
//    ani_show->setStartValue(QRect((x_global - this->width())/2,
//                                   (y_global - this->height())/2,
//                                   this->width(),0));
//    ani_show->setEndValue(QRect((x_global - this->width())/2,
//                                 (y_global - this->height())/2,
//                                 this->width(),this->height()));
//    ani_show->start(QAbstractAnimation::DeleteWhenStopped);//如果动画设置这个参数，就不要关联信号与槽
//    connect(ani_show,&QPropertyAnimation::finished,[=](){
//        qDebug() << QString(u8"显示动画结束！");
//    });

    //透明度动画
    ani_opacity = new QPropertyAnimation(this, "windowOpacity",this);
    ani_opacity->setDuration(500);
    ani_opacity->setStartValue(1);
    ani_opacity->setEndValue(0);
    // ani_opacity->start(QAbstractAnimation::DeleteWhenStopped);//如果动画设置这个参数，就不要关联信号与槽


    //矩形界面消失动画(从上到中)
//    ani_top_hide = new QPropertyAnimation(this, "geometry",this);
//    ani_top_hide->setDuration(1000);
//    ani_top_hide->setKeyValueAt(0,QRect((x_global - this->width())/2,
//                                      (y_global - this->height())/2,
//                                      this->width(),this->height()));

//    ani_top_hide->setKeyValueAt(1,QRect((x_global - this->width())/2,
//                                    (y_global + this->height())/4,
//                                    this->width(),0));
//    ani_top_hide->setStartValue(QRect(this->geometry()));
//    ani_top_hide->setEndValue(QRect(this->x(),this->y()+this->height()/4-2,this->width(),4));

    //矩形界面消失动画(从底到中)
//    ani_bom_hide = new QPropertyAnimation(this, "geometry",this);
//    ani_bom_hide->setDuration(500);
//    ani_bom_hide->setStartValue(QRect((x_global - this->width())/2,
//                                      (y_global - this->height())/2,
//                                      this->width(),this->height()));

//    ani_bom_hide->setEndValue(QRect((x_global - this->width())/2,
//                                    (y_global - this->height())/2,
//                                    0,0));

    aniGroup = new QParallelAnimationGroup(this);
    aniGroup->addAnimation(ani_opacity);
    connect(aniGroup,&QParallelAnimationGroup::finished,[=](){
            this->close();
        this->setWindowOpacity(1);
        qDebug() << QString(u8"消失动画结束！");
    });
}

NewLoginForm *NewLoginForm::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new NewLoginForm();
    }
    return m_pInstance;
}

void NewLoginForm::chandleSignalsAndSLots()
{
    //关闭
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        aniGroup->start();
        qDebug() << this->geometry();
    });

    //跳转到注册
    connect(ui->pushButton_register,&QPushButton::clicked,[=](){
        ui->stackedWidget_right->setCurrentIndex(1);
        qDebug() << QString(u8"注册按钮");
    });
    //获取验证码
    connect(ui->pushButton_checkCode,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"获取验证码");
    });
    //忘记密码
    connect(ui->pushButton_forgotPwd,&QPushButton::clicked,[=](){
        ui->stackedWidget_right->setCurrentIndex(2);
        qDebug() << QString(u8"忘记密码");
    });
    //扫码登录
    connect(ui->pushButton_scanCode,&QPushButton::clicked,[=](){
        ui->stackedWidget_right->setCurrentIndex(0);//右侧变为扫码登录界面
        ui->pushButton_updateQR->click();//模拟点击刷新
    });
    //登录遇到问题
    connect(ui->pushButton_questions,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"遇到问题");
    });

    //查看密码（登录账户）
    connect(m_actionShowPwd,&QAction::triggered,[=](bool checked)
    {
        if(checked)
        {
            m_actionShowPwd->setIcon(QIcon(":/images/icon/passwd_show.png"));
            ui->lineEdit_userpwd->setEchoMode(QLineEdit::Normal);
            m_actionShowPwd->setChecked(true);
        }
        else
        {
            m_actionShowPwd->setIcon(QIcon(":/images/icon/passwd_hide.png"));
            ui->lineEdit_userpwd->setEchoMode(QLineEdit::Password);
            m_actionShowPwd->setChecked(false);
        }
    });

    //查看密码（注册账户）
    connect(m_act_pwd,&QAction::triggered,[=](bool checked)
    {
        if(checked)
        {
            m_act_pwd->setIcon(QIcon(":/images/icon/passwd_show.png"));
            ui->lineEdit_regis_checkCode->setEchoMode(QLineEdit::Normal);
            m_act_pwd->setChecked(true);
        }
        else
        {
            m_act_pwd->setIcon(QIcon(":/images/icon/passwd_hide.png"));
            ui->lineEdit_regis_checkCode->setEchoMode(QLineEdit::Password);
            m_act_pwd->setChecked(false);
        }
    });

    //回车键---登录(模拟登陆按钮)
    connect(ui->lineEdit_userpwd,&QLineEdit::returnPressed,[=](){ui->pushButton_login->clicked();});

    //用户登录
    connect(ui->pushButton_login,&QPushButton::clicked,[=](){
        if(ui->tabWidget_login->currentIndex() == 0)//短信登录
        {
            if(ui->lineEdit_telNumber->text().isEmpty())
            {
                setType(TipType::Error);
                showCText(TipType::Correct,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-230,70),QString(u8"手机号不能为空"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
            }
            else if(ui->lineEdit_checkCode->text().isEmpty())
            {
                setType(TipType::Error);
                showCText(TipType::Normal,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-230,70),QString(u8"验证码不能为空"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
            }
            else
            {
                setUser_login();
            }
        }
        else if(ui->tabWidget_login->currentIndex() == 1)//账号登录
        {
            if(ui->lineEdit_account->text().isEmpty())
            {
                setType(TipType::Error);
                showCText(TipType::Correct,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-230,70),QString(u8"登录账号不能为空"),ui->pushButton_login,ui->lineEdit_account->rect(),2000);
            }
            else if(ui->lineEdit_userpwd->text().isEmpty())
            {
                setType(TipType::Error);
                showCText(TipType::Normal,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-230,70),QString(u8"登录密码不能为空"),ui->pushButton_login,ui->lineEdit_userpwd->rect(),2000);
            }
            else
            {
                setUser_login();
            }
        }
    });

    //回车键---登录(模拟登陆按钮)
    connect(ui->lineEdit_regis_email,&QLineEdit::returnPressed,[=](){ui->pushButton_regis->clicked();});

    //用户注册
    connect(ui->pushButton_regis,&QPushButton::clicked,[=](){
        if(ui->stackedWidget_right->currentIndex() == 1)//账号注册
        {
            if(ui->lineEdit_regis_telNumber->text().length() < 6)
            {
                setType(TipType::Error);
                showCText(TipType::Normal,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,70),QString(u8"设置账户长度过短"),ui->pushButton_regis,ui->lineEdit_regis_telNumber->rect(),2000);
            }
            else if(ui->lineEdit_regis_checkCode->text().length() < 6)
            {
                setType(TipType::Error);
                showCText(TipType::Normal,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,70),QString(u8"设置密码长度过短"),ui->pushButton_regis,ui->lineEdit_regis_telNumber->rect(),2000);
            }
            else if(ui->lineEdit_regis_email->text().isEmpty())
            {
                setType(TipType::Error);
                showCText(TipType::Normal,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,70),QString(u8"注册邮箱不能为空"),ui->pushButton_regis,ui->lineEdit_regis_telNumber->rect(),2000);
            }
            else
            {
                setUser_register();
            }
        }
    });

    //用户重置密码
    connect(ui->pushButton_resetPwd,&QPushButton::clicked,[=](){
        qDebug() <<QString(u8"重置密码！~~~");
    });

    //点击按钮刷新二维码
    connect(ui->pushButton_updateQR,&QPushButton::clicked,[=](){
        if(!m_isEnabled)
        {
            ui->pushButton_updateQR->setText(QString(u8"请勿频繁刷新二维码！"));
            QTimer::singleShot(2*1000,0,[=](){
                ui->pushButton_updateQR->setText(QString(u8"刷新二维码"));
            });
        }
        else
        {
            update_QRcode();
        }
    });

    //点击图片刷新二维码
    connect(ui->label_QRcode,&MaskLabel::sig_item_clicked,[=](){
        ui->pushButton_updateQR->click();
    });
}

void NewLoginForm::update_QRcode()
{

    ui->label_QRcode->slot_clearMask();//先清除遮罩
    QString content_account = ui->lineEdit_account->text();
    QString content_passwd = ui->lineEdit_userpwd->text();
    set_QRcode(QString(u8"%1%2").arg(content_account).arg(content_passwd));//生成二维码
    ui->pushButton_updateQR->setProperty("updated",true);
    ui->pushButton_updateQR->style()->polish(ui->pushButton_updateQR);
//    ui->pushButton_updateQR->setDisabled(true);
    m_isEnabled = false;
    ui->label_QRcode->setDisabled(true);
    QTimer::singleShot(1000*10,Qt::PreciseTimer,[=](){
        ui->label_QRcode->slot_setMask();
        ui->pushButton_updateQR->setProperty("updated",false);
        ui->pushButton_updateQR->style()->polish(ui->pushButton_updateQR);
//        ui->pushButton_updateQR->setDisabled(false);//刷新按钮在区间内不可调用
        m_isEnabled = true;
        ui->label_QRcode->setDisabled(false);//不能设置图片
    });
    qDebug() <<QString(u8"刷新二维码");
}

void NewLoginForm::set_QRcode(const QString &content)
{
    // Manual operation
    std::vector<QrSegment> segs = QrSegment::makeSegments(content.toUtf8());
    QrCode qr1 = QrCode::encodeSegments(
        segs, QrCode::Ecc::HIGH, 5, 10, 2, false);
    //创建二维码画布
    QImage QrCode_Image = QImage(qr1.getSize(),qr1.getSize(),QImage::Format_RGB888);

    for (int y = 0; y < qr1.getSize(); y++) {
        for (int x = 0; x < qr1.getSize(); x++) {
            if(qr1.getModule(x, y)==0)
                QrCode_Image.setPixel(x,y,qRgb(255,255,255));
            else
                QrCode_Image.setPixel(x,y,qRgb(0,0,0));
        }
    }

    //图像大小转换为适当的大小（根据label_QRcode显示二维码的宽高）
    QrCode_Image = QrCode_Image.scaled(QRSIZE,Qt::KeepAspectRatio);
    //转换为QPixmap在Label中显示
    ui->label_QRcode->setPixmap(QPixmap::fromImage(QrCode_Image));
    ui->label_QRcode->setContentsMargins(5,5,5,5);//内部边距
}

void NewLoginForm::receiveLoginAppClose()
{
    aniGroup->start();
}

void NewLoginForm::slot_switchWinType(ShowType type)
{
    switch (type) {
    case ShowType::LoginWin_0://扫码登录
    {
        ui->tabWidget_login->setCurrentIndex(0);
        ui->stackedWidget_right->setCurrentIndex(0);
    }
        break;
    case ShowType::LoginWin_1://短信登录
    {
        ui->tabWidget_login->setCurrentIndex(0);
        ui->stackedWidget_right->setCurrentIndex(0);
        ui->lineEdit_telNumber->setFocus();
    }
        break;
    case ShowType::LoginWin_2://账号登录
    {
        ui->tabWidget_login->setCurrentIndex(1);
        ui->stackedWidget_right->setCurrentIndex(0);
        ui->lineEdit_account->setFocus();
    }
        break;
    case ShowType::RegisWin://注册窗口
    {
        ui->tabWidget_login->setCurrentIndex(1);
        ui->stackedWidget_right->setCurrentIndex(1);
        ui->lineEdit_regis_telNumber->setFocus();
    }
        break;
    case ShowType::ReSetWin://重置窗口
    {
        ui->tabWidget_login->setCurrentIndex(1);
        ui->stackedWidget_right->setCurrentIndex(2);
        ui->lineEdit_fpwd_account->setFocus();
    }
        break;
    default:
        break;
    }

    if(this->windowOpacity() == 0)
    {
        this->setWindowOpacity(1);
    }
    this->exec();
}

void NewLoginForm::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(56, 67, 99,10));//rgba

    QPainterPath drawPath;
    drawPath.addRoundedRect(this->rect(),5,5);
    drawPath.addRect(this->rect());
//    painter.fillPath(drawPath,Qt::black);//先绘图片再填充外部边缘（准确来说叫颜色压住覆盖）
    painter.setClipPath(drawPath);
}


bool NewLoginForm::eventFilter(QObject *obj, QEvent *ev)
{
    return QWidget::eventFilter(obj,ev);
}

//用户登陆校验
void NewLoginForm::setUser_login()
{
    QString account = "";
    QString passwd = "";
    if(ui->tabWidget_login->currentIndex() == 0)//短信登录
    {
        account = ui->lineEdit_telNumber->text().trimmed();
        passwd  = ui->lineEdit_checkCode->text().trimmed();
    }
    else if(ui->tabWidget_login->currentIndex() == 1)//账号登陆
    {
        account = ui->lineEdit_account->text().trimmed();
        passwd  = ui->lineEdit_userpwd->text().trimmed();
    }
    //查询数据库
    bool valiable = dataBase::getInstance()->login_checked_usernameAndPasswd(account,passwd);//核对账号是否存在
    if(valiable)//信息核对成功！
    {
        qDebug() <<QString(u8"查有此人！");
        //发送名称，头像连接, 等级
        emit sig_sendClearTempRecords();//清除临时记录（如果用户不登录，则切换用户时会用到）
        dataBase::getInstance()->login_verification(account,passwd);//将用户所有信息查询出来，并初始化
        QString nickname =  dataBase::getInstance()->getCurrentUserName();
        QString head     =  dataBase::getInstance()->getCurrentUserHead();
        int     grade    =  dataBase::getInstance()->getCurrentUserGrade();
        emit sig_sendLoginOK(nickname,head,grade);//向外界发送用户信息
//        slot_addLoginHisUsers(account);
        slot_clearTempInputText();//清除输入信息
        this->close();
    }
    else//信息核对失败！
    {
        qDebug() <<QString(u8"查无此人！");
        setType(TipType::Error);
        showCText(TipType::Normal,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-230,70),QString(u8"用户信息不正确！"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
        return;
    }
}

//用户注册
void NewLoginForm::setUser_register()
{
    QString name = "";
    QString pwd = "";
    QString email = "";
    if(ui->stackedWidget_right->currentIndex() == 1)//注册界面
    {
       name    = ui->lineEdit_regis_telNumber->text().trimmed();
       pwd     = ui->lineEdit_regis_checkCode->text().trimmed();
       email   = ui->lineEdit_regis_email->text().trimmed();
    }
    //插入之前先判断是否有重名用户
    bool valiable = dataBase::getInstance()->getUserExists("userinfo",name);
    if(valiable)//找到了重名用户
    {
        setType(TipType::Error);
        showCText(TipType::Normal,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,70),QString(u8"该账号已注册！"),ui->pushButton_regis,ui->lineEdit_regis_telNumber->rect(),2000);
        slot_clearTempInputText();
        return;//直接返回
    }
    bool isOK = dataBase::getInstance()->register_userInfo(name,pwd,email);//数据库插入用户信息
    if(isOK)//插入成功
    {
        QTimer::singleShot(0,0,[=](){
            slot_clearTempInputText();
            //showLoginWindow(0);
            setType(TipType::Correct);
            showCText(TipType::Normal,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,70),QString(u8"恭喜您，注册成功！"),ui->pushButton_regis,ui->lineEdit_regis_telNumber->rect(),2000);
            ui->stackedWidget_right->setCurrentIndex(0);//右侧变为扫码登录界面
            ui->pushButton_updateQR->click();//模拟点击刷新二维码
        });//转到登录界面
    }
    else//插入失败
    {
        setType(TipType::Error);
        showCText(TipType::Normal,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,70),QString(u8"注册失败，请重新注册！"),ui->pushButton_regis,ui->lineEdit_regis_telNumber->rect(),2000);
    }
}

void NewLoginForm::setUser_reSet()
{

}

void NewLoginForm::setUser_findPwd()
{

}

void NewLoginForm::slot_clearTempInputText()
{
    ui->lineEdit_telNumber->clear();
    ui->lineEdit_checkCode->clear();
    ui->lineEdit_regis_telNumber->clear();
    ui->lineEdit_regis_checkCode->clear();
    ui->lineEdit_regis_email->clear();
    ui->lineEdit_account->clear();
    ui->lineEdit_userpwd->clear();
    ui->lineEdit_fpwd_account->clear();
    ui->lineEdit_fpwd_checkCode->clear();
    ui->lineEdit_firstpwd->clear();
    ui->lineEdit_secondpwd->clear();
}

void NewLoginForm::showTipContentLenRule(const QString &ruleText)
{
    setType(TipType::Error);
    showCText(TipType::Correct,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,70),ruleText,ui->pushButton_regis,ui->lineEdit_regis_telNumber->rect(),2000);
}


void NewLoginForm::showCText(TipType type, const QPoint &pos, const QString &text, QWidget *w, const QRect &rect, int msecShowTime)
{
    QToolTip::showText(pos,text,w,rect,msecShowTime);
}

void NewLoginForm::setType(TipType type)
{
    switch (type)
    {
    case TipType::Normal://正常提示
    {
//        QString st = "<b style=\"background:rgb(230, 92, 54);color:red;\">%1</b>";
//        return st;
//        QToolTip::setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
        setStyleSheet("QWidget{background-color: #2c2d36;}"
                      "QToolTip{min-height: 20px; background-color: #ffffbf; color: black;}");
    }
        break;
    case TipType::Error://错误提示
    {
//        QString st = "<b style=\"background:rgb(230, 92, 54);color:red;\">%1</b>";
//        return st;
//        QToolTip::setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
        setStyleSheet("QWidget{background-color: #2c2d36;}"
                      "QToolTip{min-height: 20px; background-color: #ffffbf; color: #00beff;}");
    }
        break;
    case TipType::Correct://成功提示
    {
//        QString st = "<b style=\"background:rgb(246, 188, 63);color:green;\">%1</b>";
//        return st;
//        QToolTip::setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
        setStyleSheet("QWidget{background-color: #2c2d36;}"
                      "QToolTip{min-height: 20px; background-color: #ffffbf; color: #1c9734;}");
    }
        break;
    default:
    {
//        QString st = "<b style=\"background:rgb(255, 214, 22);color:white;\">%1</b>";
//        return st;
//        QToolTip::setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
        setStyleSheet("QWidget{background-color: #2c2d36;}"
                      "QToolTip{min-height: 20px; background-color: #ffffbf; color: black;}");
    }
        break;
    }

//  pal.setColor(QPalette::ToolTipBase, Qt::red);
//  pal.setColor(QPalette::ToolTipText, Qt::green);
}
