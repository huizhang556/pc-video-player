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
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setAttribute(Qt::WA_Hover);
//    setAttribute(Qt::WA_DeleteOnClose);//程序关闭或其父窗口关闭时，自己自动close
    initWorkUI();
    initAnimations();
    handleSignalsAndSLots();
    setInstallEventFilter();
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

    delete m_userLists;

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
    //一些隐藏项
    ui->checkBox_rempwd->hide();
    ui->checkBox_rempwd->setChecked(false);

    //登录---验证码倒计时
    loginTimer = new QTimer(this);
    loginTimer->setInterval(1000);//倒计时间隔

    //注册---验证码倒计时
    regisTimer = new QTimer(this);
    regisTimer->setInterval(1000);//倒计时间隔

    //找回密码---验证码倒计时
    fpwdTimer = new QTimer(this);
    fpwdTimer->setInterval(1000);//倒计时间隔

    ui->label_userHeader->setToolTip(QString(u8"单击修改头像"));
//    this->setContentsMargins(15,15,15,15);//为阴影留出空间
//    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
//    shadow_effect->setOffset(0,0);//阴影往边外（下和右）移出的距离
//    shadow_effect->setColor(QColor(93, 95, 96));
//    shadow_effect->setBlurRadius(15);//阴影也是个矩形，需要圆角
//    this->setGraphicsEffect(shadow_effect);
    ui->pushButton_exitUser->setIcon(QIcon("://images/icon/login_exit.png"));
    ui->pushButton_exitUser->setIconSize(QSize(18,18));
    ui->pushButton_userGrade->setIconSize(QSize(18,18));
    ui->pushButton_userGrade->setLayoutDirection(Qt::RightToLeft);
    ui->pushButton_exitUser->setLayoutDirection(Qt::RightToLeft);

    ui->pushButton_switchUser->setIcon(QIcon("://images/icon/login_switch.png"));
    ui->pushButton_switchUser->setIconSize(QSize(14,18));
    ui->pushButton_switchUser->setLayoutDirection(Qt::RightToLeft);

//    ui->label_userHeader->setFixedSize(QSize(160,160));
//    QRegion maskRegion(ui->label_userHeader->rect(),QRegion::Ellipse);//创建圆形遮罩
//    ui->label_userHeader->setMask(maskRegion);//设置圆形遮罩
    ui->label_userHeader->setPadding(10);
    ui->label_userHeader->setBorderWidth(true,10);
    ui->stackedWidget_left->setCurrentWidget(ui->stackedpage_unlogin);

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
    ui->lineEdit_telNumber->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_checkCode->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_account->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_userpwd->setContextMenuPolicy(Qt::NoContextMenu);

    m_userLists = new UserList();
    m_userLists->setFixedWidth(326);//等宽度
    m_userLists->setFixedHeight(156);//3个user的高度
    m_userLists->setHidden(true);

    //注册部分
    m_act_pwd = new QAction(QIcon(":/images/icon/passwd_hide.png"),"");
    m_act_pwd->setObjectName(QString("m_act_pwd"));
    m_act_pwd->setCheckable(true);
    m_act_pwd->setChecked(false);

    ui->lineEdit_regis_telNumber->setMaxLength(20);
    ui->lineEdit_regis_pwd->setMaxLength(18);
    ui->lineEdit_regis_checkCode->setMaxLength(6);
    ui->lineEdit_regis_email->setMaxLength(26);

    ui->lineEdit_regis_telNumber->setPlaceholderText(QString(u8"请输入注册手机号码或账号"));
    ui->lineEdit_regis_pwd->setPlaceholderText(QString(u8"请输入注册密码"));
    ui->lineEdit_regis_email->setPlaceholderText(QString(u8"请输入注册邮箱"));
    ui->lineEdit_regis_checkCode->setPlaceholderText(QString(u8"请输入验证码"));

    ui->lineEdit_regis_pwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_regis_pwd->addAction(m_act_pwd,QLineEdit::TrailingPosition);

    ui->lineEdit_regis_telNumber->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_regis_pwd->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_regis_checkCode->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_regis_email->setContextMenuPolicy(Qt::NoContextMenu);


    //正则限制输入内容(账户名称限制)
    QRegExp regExp_account(QString(u8"[a-zA-Z\u4e00-\u9fa5][a-zA-Z0-9\u4e00-\u9fa5]+"));//汉字+字母+数字，不限制长度
    ui->lineEdit_regis_telNumber->setValidator(new QRegExpValidator(regExp_account, this));
    //密码限制
    QRegExp regExp_pwd(QString(u8"^([A-Z]|[a-z]|[0-9]|[,.@]){6,18}$"));//大小写字母+数字+特殊符号（,.@）
    ui->lineEdit_regis_pwd->setValidator(new QRegExpValidator(regExp_pwd, this));
    //邮箱格式限制
    QRegExp regExp_email(QString(u8"[\\w!#$%&'*+/=?^_`{|}~-]+(?:\\.[\\w!#$%&'*+/=?^_`{|}~-]+)*@(?:[\\w](?:[\\w-]*[\\w])?\\.)+[\\w](?:[\\w-]*[\\w])?"));
    ui->lineEdit_regis_email->setValidator(new QRegExpValidator(regExp_email, this));


    //重置部分
    ui->lineEdit_fpwd_account->setPlaceholderText(QString(u8"请输入预留邮箱"));
    ui->lineEdit_fpwd_checkCode->setPlaceholderText(QString(u8"请输入验证码"));
    ui->lineEdit_fpwd_checkCode->setMaxLength(6);//6位验证码
    ui->lineEdit_firstpwd->setPlaceholderText(QString(u8"请输入新的密码"));
    ui->lineEdit_secondpwd->setPlaceholderText(QString(u8"再次输入新的密码"));

    ui->lineEdit_firstpwd->setEchoMode(QLineEdit::Password);
    ui->lineEdit_secondpwd->setEchoMode(QLineEdit::Password);

    ui->lineEdit_fpwd_account->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_fpwd_checkCode->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_firstpwd->setContextMenuPolicy(Qt::NoContextMenu);
    ui->lineEdit_secondpwd->setContextMenuPolicy(Qt::NoContextMenu);
    //默认显示登录界面
    ui->stackedWidget_right->setCurrentWidget(ui->page_login);
    //解决QLineEdit回车键退出
    ui->pushButton_close->setFocusPolicy(Qt::NoFocus);//默认具有焦点
    ui->pushButton_register->setFocusPolicy(Qt::NoFocus);//默认具有焦点

    //combobox弹框问题
    ui->comboBox_area->installEventFilter(this);
    ui->comboBox_area->setFocusPolicy(Qt::NoFocus);
    ui->comboBox_area->setView(new QListView());
    ui->comboBox_regis_area->installEventFilter(this);
    ui->comboBox_regis_area->setFocusPolicy(Qt::NoFocus);
    ui->comboBox_regis_area->setView(new QListView());

    //勾选协议（默认勾选）
    ui->radioButton_check->setCheckable(true);
    ui->radioButton_check->setChecked(true);
    ui->radioButton_regis_check->setCheckable(true);
    ui->radioButton_regis_check->setChecked(false);

    ui->tabWidget_login->setCurrentIndex(0);

    ui->pushButton_updateQR->setText(QString(u8"刷新二维码"));

    ui->pushButton_questions->setIconSize(QSize(14,14));
    ui->pushButton_questions->setIcon(QIcon("://images/user/login_question_hover.png"));

    ui->scrollArea_questions->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_questions->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->textBrowser_protocol->setContextMenuPolicy(Qt::NoContextMenu);
    ui->textBrowser_privacy->setContextMenuPolicy(Qt::NoContextMenu);

    //问题解决
//    ui->treeWidget_questions->setHeaderLabel(QString(u8"常见问题"));//居中使用样式
//    QHeaderView *headView = new QHeaderView(Qt::Horizontal);
//    headView->setDefaultAlignment(Qt::AlignCenter);
//    ui->treeWidget_questions->setHeader(headView);
//    QTreeWidgetItem *treeItem0 = new QTreeWidgetItem(ui->treeWidget_questions,QStringList{QString(u8"常见问题")});
//    treeItem0->setTextAlignment(0,Qt::AlignCenter);
//    ui->treeWidget_questions->setHeaderItem(treeItem0);
//    ui->treeWidget_questions->setHeaderHidden(true);

//    QTreeWidgetItem *treeItem1 = new QTreeWidgetItem(ui->treeWidget_questions,QStringList{QString(u8"1.如何注册账户？")});
//    treeItem1->setFirstColumnSpanned(true);
//    QTreeWidgetItem *treeItem1_1 = new QTreeWidgetItem();
//    treeItem1->addChild(treeItem1_1);
//    QPlainTextEdit *plainEdit1 = new QPlainTextEdit(QString(u8"如何注册账户？"));
//    plainEdit1->setFixedHeight(100);
//    ui->treeWidget_questions->setItemWidget(treeItem1_1,0,plainEdit1);

//    QTreeWidgetItem *treeItem2 = new QTreeWidgetItem(ui->treeWidget_questions,QStringList{QString(u8"2.注册用户名、密码设置规则")});
//    QTreeWidgetItem *treeItem2_1 = new QTreeWidgetItem();
//    treeItem2->addChild(treeItem2_1);
//    QPlainTextEdit *plainEdit2 = new QPlainTextEdit(QString(u8"注册用户名、密码设置规则"));
//    plainEdit2->setFixedHeight(100);
//    ui->treeWidget_questions->setItemWidget(treeItem2_1,0,plainEdit2);

//    QTreeWidgetItem *treeItem3 = new QTreeWidgetItem(ui->treeWidget_questions,QStringList{QString(u8"3.用户隐私协议")});
//    QTreeWidgetItem *treeItem3_1 = new QTreeWidgetItem();
//    treeItem3->addChild(treeItem3_1);
//    QPlainTextEdit *plainEdit3 = new QPlainTextEdit(QString(u8"如何注册账户？"));
//    plainEdit3->setFixedHeight(100);
//    ui->treeWidget_questions->setItemWidget(treeItem3,0,plainEdit3);

//    QTreeWidgetItem *treeItem4 = new QTreeWidgetItem(ui->treeWidget_questions,QStringList{QString(u8"4.软件功能以及使用")});
//    QTreeWidgetItem *treeItem5 = new QTreeWidgetItem(ui->treeWidget_questions,QStringList{QString(u8"5.关于会员续费以及特权说明")});
//    QTreeWidgetItem *treeItem6 = new QTreeWidgetItem(ui->treeWidget_questions,QStringList{QString(u8"6.用户如何上传自己的作品？")});
//    QTreeWidgetItem *treeItem7 = new QTreeWidgetItem(ui->treeWidget_questions,QStringList{QString(u8"7.用户收益如何计算？")});
//    QTreeWidgetItem *treeItem8 = new QTreeWidgetItem(ui->treeWidget_questions,QStringList{QString(u8"8.常见使用问题集合")});
//    QTreeWidgetItem *treeItem9 = new QTreeWidgetItem(ui->treeWidget_questions,QStringList{QString(u8"9.多设备同一账号登录")});
//    QTreeWidgetItem *treeItem10 = new QTreeWidgetItem(ui->treeWidget_questions,QStringList{QString(u8"10.如何注销账户？")});
//    treeItem->setText(0,QString(u8"1.如何注册账户？"));
//    ui->treeWidget_questions->addTopLevelItem(treeItem);


    FAQitem *FAQ1  = new FAQitem(QString(u8"1.如何注册账户？"),QString(u8"点击本页面[注册]，按照提示进行注册即可；"));
    addUserQuestions(FAQ1);

    FAQitem *FAQ2  = new FAQitem(QString(u8"2.注册用户名、密码设置规则"),QString(u8"用户名规则：汉字+字母+数字；密码：字母+数字+特殊符号（,.@）;"));
    addUserQuestions(FAQ2);

    FAQitem *FAQ3  = new FAQitem(QString(u8"3.用户隐私协议"),QString(u8"协议详细见协议说明"));
    addUserQuestions(FAQ3);

    FAQitem *FAQ4  = new FAQitem(QString(u8"4.软件功能以及使用"),QString(u8"视频浏、下载览和视频上传发布。"));
    addUserQuestions(FAQ4);

    FAQitem *FAQ5  = new FAQitem(QString(u8"5.关于会员续费以及特权说明"),QString(u8"用户缴纳相应等级的会员费，开通会员，享受对应等级的会员权益。可任意时刻结束会员，结束之前的会员权益不受影响。"));
    addUserQuestions(FAQ5);

    FAQitem *FAQ6  = new FAQitem(QString(u8"6.用户如何上传自己的作品？"),QString(u8"在创作中心，点击[发布]，上传视频后一经审核通过，即可发布视频。"));
    addUserQuestions(FAQ6);

    FAQitem *FAQ7  = new FAQitem(QString(u8"7.用户收益如何计算？"),QString(u8"用户收益需严格按照计算标准产出收益，平台收取一定比例的手续费，用户可以进行现金提现。"));
    addUserQuestions(FAQ7);

    FAQitem *FAQ8  = new FAQitem(QString(u8"8.第三方授权登录说明"),QString(u8"所有第三方经过授权的应用均可使用本账号授权登录。"));
    addUserQuestions(FAQ8);

    FAQitem *FAQ9  = new FAQitem(QString(u8"9.多设备同一账号登录"),QString(u8"优酷账号无论在哪种设备上登录，同时不能超过3台设备。"));
    addUserQuestions(FAQ9);

    FAQitem *FAQ10 = new FAQitem(QString(u8"10.如何注销账户？"),QString(u8"打开优酷视频网页版，点击个人账户，点击[安全设置]-[账号注销],选择注销理由，进行注销！"));
    addUserQuestions(FAQ10);

    //二维码(初始化更新)
    update_QRcode();

    m_userLists->config_initUser();//初始化用户列表

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

void NewLoginForm::handleSignalsAndSLots()
{
//    connect(ui->pushButton_otherMethed1,&QPushButton::clicked,[=](){ui->stackedWidget_left->setCurrentWidget(ui->stackedpage_logined);});

    //修改头像
    connect(ui->label_userHeader,&RoundLab::sig_clicked,[=](){
//        ChangeHead::getInstance()->exec_(OPENTYPE::PER_HEAD);
    });

    //退出登录
    connect(ui->pushButton_exitUser,&QPushButton::clicked,[=](){
        ui->stackedWidget_left->setCurrentWidget(ui->stackedpage_unlogin);
        //数据库设置登录状态，并通知其他部分
    });

    //切换用户
    connect(ui->pushButton_switchUser,&QPushButton::clicked,[=](){
        ui->stackedWidget_left->setCurrentWidget(ui->stackedpage_unlogin);
        //数据库设置登录状态，并通知其他部分
    });

    //关闭
    connect(ui->pushButton_close,&QPushButton::clicked,[=](){
        aniGroup->start();
        qDebug() << this->geometry();
    });

    //跳转到注册
    connect(ui->pushButton_register,&QPushButton::clicked,[=](){
        ui->stackedWidget_right->setCurrentWidget(ui->page_regis);
        ui->pushButton_register->setText(QString(u8"注册"));
        qDebug() << QString(u8"注册按钮");
    });

    //登录---获取验证码
    connect(ui->pushButton_checkCode,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"登录获取验证码：");
        m_login_Random = generateRandomCode(6);
        //邮件发送验证码，进行判断（暂时不做）

        ui->pushButton_checkCode->setEnabled(false);
        loginTimer->start();
    });

    //登录验证码---倒计时
    connect(loginTimer,&QTimer::timeout,[=](){
        if(login_count-- == 1)
        {
            m_login_Random = "";
            login_count = 60;
            loginTimer->stop();
            ui->pushButton_checkCode->setEnabled(true);
            ui->lineEdit_checkCode->setPlaceholderText(QString(u8"请输入验证码"));
            return;
        }
        ui->lineEdit_checkCode->setPlaceholderText(QString(u8"验证码已发送%1s").arg(login_count));
    });

    //登录--校验验证码正确性
    connect(ui->lineEdit_checkCode,&QLineEdit::textEdited,[=](const QString &str1){
        if(str1.length() == 6)
        {
            const int result1 = str1.compare(m_login_Random,Qt::CaseSensitive);//字符敏感
            qDebug() << QString(u8"字符比较结果：") << result1;
            if(result1 == 0)//结果正确
            {
                setType(TipType::SUCCESS);
                showCText(ShowType::LoginWin_1,TipType::SUCCESS,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-250,100),QString(u8"验证码正确！"),ui->pushButton_login,ui->lineEdit_userpwd->rect(),2000);
            }
            else//匹配结果不一致
            {
                setType(TipType::FAILED);
                showCText(ShowType::LoginWin_1,TipType::SUCCESS,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-250,100),QString(u8"验证码错误！"),ui->pushButton_login,ui->lineEdit_userpwd->rect(),2000);
            }
        }
    });

    //注册---获取验证码
    connect(ui->pushButton_regis_checkCode,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"注册获取验证码：");
        m_regis_Random = generateRandomCode(6);
        //邮件发送验证码，进行判断
        bool ok = sendCheckCode(RegisWin,ui->lineEdit_regis_email->text().trimmed());
        if(ok)//发送成功
        {
            ui->pushButton_regis_checkCode->setEnabled(false);
            regisTimer->start();
        }
        else
        {
            qDebug(u8"注册：验证码发送失败！");
        }
    });

    //注册---验证码倒计时
    connect(regisTimer,&QTimer::timeout,[=](){
        if(regis_count-- == 1)
        {
            m_regis_Random = "";
            regis_count = 60;
            regisTimer->stop();
            ui->pushButton_regis_checkCode->setEnabled(true);
            ui->lineEdit_regis_checkCode->setPlaceholderText(QString(u8"请输入验证码"));
            return;
        }
        ui->lineEdit_regis_checkCode->setPlaceholderText(QString(u8"验证码已发送%1s").arg(regis_count));
    });

    //注册--校验验证码正确性
    connect(ui->lineEdit_regis_checkCode,&QLineEdit::textEdited,[=](const QString &str1){
        if(str1.length() == 6)
        {
            const int result1 = str1.compare(m_regis_Random,Qt::CaseSensitive);//字符敏感
            qDebug() << QString(u8"字符比较结果：") << result1;
            if(result1 == 0)//结果正确
            {
                setType(TipType::SUCCESS);
                showCText(ShowType::RegisWin,TipType::SUCCESS,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-250,61),QString(u8"验证码正确！"),ui->lineEdit_regis_checkCode,ui->lineEdit_regis_checkCode->rect(),2000);
            }
            else//匹配结果不一致
            {
                setType(TipType::FAILED);
                showCText(ShowType::RegisWin,TipType::FAILED,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-250,61),QString(u8"验证码错误！"),ui->lineEdit_regis_checkCode,ui->lineEdit_regis_checkCode->rect(),2000);
            }
        }
    });

    //重置密码---获取验证码
    connect(ui->pushButton_fpwd_checkCode,&QPushButton::clicked,[=](){
        qDebug() << QString(u8"重置密码获取验证码：");
        m_reset_Random = generateRandomCode(6);
        //邮件发送验证码，进行判断
        bool ok = sendCheckCode(ReSetWin,ui->lineEdit_fpwd_account->text().trimmed());
        if(ok)//发送成功
        {
            ui->pushButton_fpwd_checkCode->setEnabled(false);
            fpwdTimer->start();
        }
        else
        {
            qDebug(u8"重置密码：验证码发送失败！");
        }

    });

    //重置密码---验证码倒计时
    connect(fpwdTimer,&QTimer::timeout,[=](){
        if(fpwd_count-- == 1)
        {
            m_reset_Random = "";
            fpwd_count = 60;
            fpwdTimer->stop();
            ui->pushButton_fpwd_checkCode->setEnabled(true);
            ui->lineEdit_fpwd_checkCode->setPlaceholderText(QString(u8"请输入验证码"));
            return;
        }
        ui->lineEdit_fpwd_checkCode->setPlaceholderText(QString(u8"验证码已发送%1s").arg(fpwd_count));
    });

    //重置密码--校验验证码正确性
    connect(ui->lineEdit_fpwd_checkCode,&QLineEdit::textEdited,[=](const QString &str1){
        if(str1.length() == 6)
        {
            const int result1 = str1.compare(m_reset_Random,Qt::CaseSensitive);//字符敏感
            qDebug() << QString(u8"字符比较结果：") << result1;
            if(result1 == 0)//结果正确
            {
                setType(TipType::SUCCESS);
                showCText(ShowType::RegisWin,TipType::SUCCESS,ui->pushButton_fpwd_checkCode->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-0,15),QString(u8"验证码正确！"),ui->pushButton_fpwd_checkCode,ui->lineEdit_fpwd_checkCode->rect(),2000);
            }
            else//匹配结果不一致
            {
                setType(TipType::FAILED);
                showCText(ShowType::RegisWin,TipType::FAILED,ui->pushButton_fpwd_checkCode->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-0,15),QString(u8"验证码错误！"),ui->pushButton_fpwd_checkCode,ui->lineEdit_fpwd_checkCode->rect(),2000);
            }
        }
    });

    //重置密码
    connect(ui->pushButton_forgotPwd,&QPushButton::clicked,[=](){
        ui->stackedWidget_right->setCurrentWidget(ui->page_resetPwd);
        qDebug() << QString(u8"忘记密码");
    });

    //记住密码--勾选状态改变（默认是两态）
    connect(ui->checkBox_rempwd,&QCheckBox::toggled,[=](bool checked){
        qDebug() <<QString(u8"记住密码勾选状态：") <<checked;
        updateRemPwdStatus();
    });

    //扫码登录
    connect(ui->pushButton_scanCode,&QPushButton::clicked,[=](){
        ui->stackedWidget_right->setCurrentWidget(ui->page_login);//右侧变为扫码登录界面
        ui->pushButton_updateQR->click();//模拟点击刷新
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
            ui->lineEdit_regis_pwd->setEchoMode(QLineEdit::Normal);
            m_act_pwd->setChecked(true);
        }
        else
        {
            m_act_pwd->setIcon(QIcon(":/images/icon/passwd_hide.png"));
            ui->lineEdit_regis_pwd->setEchoMode(QLineEdit::Password);
            m_act_pwd->setChecked(false);
        }
    });

    //回车键---登录(模拟登陆按钮)
    connect(ui->lineEdit_userpwd,&QLineEdit::returnPressed,[=](){ui->pushButton_login->clicked();});
    //使用信号回调添加item（添加或者调整顺序需要判断）
    connect(this,&NewLoginForm::sig_sendToLoginedUser,[=](QString name,QString pwd,QString header){
         m_userLists->config_addNewUser(name,pwd,header);
    });

    //登录--协议勾选
    connect(ui->radioButton_check,&QRadioButton::clicked,[=](){

    });

    //注册--协议勾选
    connect(ui->radioButton_regis_check,&QRadioButton::clicked,[=](){

    });

    //用户登录
    connect(ui->pushButton_login,&QPushButton::clicked,[=](){
        //短信登录
        if(ui->tabWidget_login->currentIndex() == 0)
        {
            if(ui->lineEdit_telNumber->text().isEmpty())
            {
                setType(TipType::FAILED);
                showCText(ShowType::LoginWin_1,TipType::FAILED,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-240,100),QString(u8"手机号不能为空"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
            }
            else if(ui->lineEdit_checkCode->text().isEmpty())
            {
                setType(TipType::FAILED);
                showCText(ShowType::LoginWin_1,TipType::FAILED,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-240,100),QString(u8"验证码不能为空"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
            }
            else if(m_login_Random != ui->lineEdit_checkCode->text())
            {
                setType(TipType::FAILED);
                showCText(ShowType::LoginWin_1,TipType::FAILED,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-240,100),QString(u8"验证码错误！"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
            }
            else if(!ui->radioButton_check->isChecked())
            {
                setType(TipType::FAILED);
                showCText(ShowType::LoginWin_1,TipType::FAILED,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-240,100),QString(u8"协议未勾选！"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
            }
            else
            {
                setUser_login();
            }
        }//账号登录
        else if(ui->tabWidget_login->currentIndex() == 1)
        {
            if(ui->lineEdit_account->text().isEmpty())
            {
                setType(TipType::FAILED);
                showCText(ShowType::LoginWin_2,TipType::FAILED,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-225,100),QString(u8"登录账号不能为空"),ui->pushButton_login,ui->lineEdit_account->rect(),2000);
            }
            else if(ui->lineEdit_userpwd->text().isEmpty())
            {
                setType(TipType::FAILED);
                showCText(ShowType::LoginWin_2,TipType::FAILED,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-225,100),QString(u8"登录密码不能为空"),ui->pushButton_login,ui->lineEdit_userpwd->rect(),2000);
            }
            else if(!ui->radioButton_check->isChecked())
            {
                setType(TipType::FAILED);
                showCText(ShowType::LoginWin_1,TipType::FAILED,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-240,100),QString(u8"协议未勾选！"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
            }
            else
            {
                setUser_login();
            }
        }
    });

    //回车键---注册(模拟登陆按钮)
    connect(ui->lineEdit_regis_checkCode,&QLineEdit::returnPressed,[=](){ui->pushButton_regis->clicked();});

    //用户注册
    connect(ui->pushButton_regis,&QPushButton::clicked,[=](){
        if(ui->stackedWidget_right->currentIndex() == 1)//账号注册
        {
            if(ui->lineEdit_regis_telNumber->text().length() < 6)
            {
                setType(TipType::FAILED);
                showCText(ShowType::RegisWin,TipType::FAILED,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,181),QString(u8"设置账户长度过短"),ui->pushButton_regis,ui->lineEdit_regis_telNumber->rect(),2000);
            }
            else if(ui->lineEdit_regis_pwd->text().length() < 6)
            {
                setType(TipType::FAILED);
                showCText(ShowType::RegisWin,TipType::FAILED,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,141),QString(u8"设置密码长度过短"),ui->lineEdit_regis_pwd,ui->lineEdit_regis_pwd->rect(),2000);
            }
            else if(ui->lineEdit_regis_email->text().isEmpty())
            {
                setType(TipType::FAILED);
                showCText(ShowType::RegisWin,TipType::FAILED,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-230,101),QString(u8"注册邮箱不能为空"),ui->lineEdit_regis_email,ui->lineEdit_regis_email->rect(),2000);
            }
            else if(ui->lineEdit_regis_checkCode->text().isEmpty())
            {
                setType(TipType::FAILED);
                showCText(ShowType::RegisWin,TipType::FAILED,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-240,61),QString(u8"验证码不能为空"),ui->lineEdit_regis_checkCode,ui->lineEdit_regis_checkCode->rect(),2000);
            }
            else if(m_regis_Random != ui->lineEdit_regis_checkCode->text())
            {
                setType(TipType::FAILED);
                showCText(ShowType::RegisWin,TipType::FAILED,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-240,61),QString(u8"验证码错误！"),ui->lineEdit_regis_checkCode,ui->lineEdit_regis_checkCode->rect(),2000);
            }
            else if(!ui->radioButton_regis_check->isChecked())
            {
                setType(TipType::FAILED);
                showCText(ShowType::RegisWin,TipType::FAILED,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-240,61),QString(u8"协议未勾选！"),ui->lineEdit_regis_checkCode,ui->lineEdit_regis_checkCode->rect(),2000);
            }
            else
            {
                setUser_register();
            }
        }
    });

    //回车键模拟重置密码
    connect(ui->lineEdit_secondpwd,&QLineEdit::returnPressed,[=](){ui->pushButton_resetPwd->clicked();});

    //用户重置密码
    connect(ui->pushButton_resetPwd,&QPushButton::clicked,[=](){
        qDebug() <<QString(u8"重置密码！~~~");
        if(ui->stackedWidget_right->currentIndex() == 2)//账号密码重置
        {
            if(ui->lineEdit_fpwd_account->text().isEmpty())
            {
                setType(TipType::FAILED);
                showCText(ShowType::ReSetWin,TipType::FAILED,ui->pushButton_resetPwd->mapToGlobal(ui->pushButton_resetPwd->pos())- QPoint(-245,181),QString(u8"账户不能为空！"),ui->pushButton_resetPwd,ui->lineEdit_fpwd_account->rect(),2000);
            }
            else if(ui->lineEdit_fpwd_checkCode->text().isEmpty())
            {
                setType(TipType::FAILED);
                showCText(ShowType::ReSetWin,TipType::FAILED,ui->pushButton_resetPwd->mapToGlobal(ui->pushButton_resetPwd->pos())- QPoint(-235,146),QString(u8"验证码不能为空！"),ui->pushButton_resetPwd,ui->lineEdit_fpwd_account->rect(),2000);
            }
            else if(ui->lineEdit_firstpwd->text().isEmpty())
            {
                setType(TipType::FAILED);
                showCText(ShowType::ReSetWin,TipType::FAILED,ui->pushButton_resetPwd->mapToGlobal(ui->pushButton_resetPwd->pos())- QPoint(-245,101),QString(u8"密码不能为空！"),ui->pushButton_resetPwd,ui->lineEdit_fpwd_account->rect(),2000);
            }
            else if(ui->lineEdit_secondpwd->text().isEmpty())
            {
                setType(TipType::FAILED);
                showCText(ShowType::ReSetWin,TipType::FAILED,ui->pushButton_resetPwd->mapToGlobal(ui->pushButton_resetPwd->pos())- QPoint(-245,61),QString(u8"密码不能为空！"),ui->pushButton_resetPwd,ui->lineEdit_fpwd_account->rect(),2000);
            }
            else if(m_reset_Random != ui->lineEdit_fpwd_checkCode->text())
            {
                setType(TipType::FAILED);
                showCText(ShowType::ReSetWin,TipType::FAILED,ui->pushButton_resetPwd->mapToGlobal(ui->pushButton_resetPwd->pos())- QPoint(-245,146),QString(u8"验证码错误！"),ui->pushButton_resetPwd,ui->lineEdit_fpwd_account->rect(),2000);
            }
            else if(ui->lineEdit_firstpwd->text() != ui->lineEdit_secondpwd->text())
            {
                setType(TipType::FAILED);
                showCText(ShowType::ReSetWin,TipType::FAILED,ui->pushButton_resetPwd->mapToGlobal(ui->pushButton_resetPwd->pos())- QPoint(-245,61),QString(u8"密码不一致！"),ui->pushButton_resetPwd,ui->lineEdit_fpwd_account->rect(),2000);
            }
            else
            {
                setUser_resetPwd();
            }
        }
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

    //用户协议(登录)
    connect(ui->pushButton_login_argeement1,&QPushButton::clicked,[=](){
        ui->stackedWidget_right->setCurrentWidget(ui->page_aboutUser);
        ui->stackedWidget_protocol->setCurrentWidget(ui->page_protocol);
        ui->pushButton_register->setText(QString(u8"返回"));
    });
    //隐私政策（登录）
    connect(ui->pushButton_login_argeement2,&QPushButton::clicked,[=](){
        ui->stackedWidget_right->setCurrentWidget(ui->page_aboutUser);
        ui->stackedWidget_protocol->setCurrentWidget(ui->page_privacy);
        ui->pushButton_register->setText(QString(u8"返回"));
    });

    connect(ui->pushButton_regis_argeement1,&QPushButton::clicked,[=](){
        ui->pushButton_login_argeement1->clicked();
    });
    connect(ui->pushButton_regis_argeement2,&QPushButton::clicked,[=](){
        ui->pushButton_login_argeement2->clicked();
    });


    //问题集合
    connect(ui->pushButton_questions,&QPushButton::clicked,[=](){
        ui->stackedWidget_right->setCurrentWidget(ui->page_questions);
        ui->pushButton_register->setText(QString(u8"返回"));
    });

    //用户选择
    connect(m_userLists,&UserList::sig_list_username,[=](QString name){
        ui->lineEdit_account->setText(name);
        //是否记住密码
        if(ui->checkBox_rempwd->isChecked())
        {
            ui->lineEdit_userpwd->setText(m_userLists->config_getUserPwd(name));
        }
        //是否占据焦点
        if(m_userLists->hasFocus())
        {
            m_userLists->clearFocus();
        }
        m_userLists->hide();
    });

    //账户输入匹配当前用户
    connect(ui->lineEdit_account,&QLineEdit::textChanged,[=](const QString &name){
//        updateUserListGeomotry();
        m_userLists->slot_findUserListResult(name);
    });

}

void NewLoginForm::setInstallEventFilter()
{
    ui->lineEdit_account->installEventFilter(this);//移入移出
    ui->lineEdit_userpwd->installEventFilter(this);
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

void NewLoginForm::addProtocol()
{

}

void NewLoginForm::addUserQuestions(FAQitem* item)
{

    ui->addVerLayout->insertWidget(ui->addVerLayout->count()-1,item);
    //每个item关联信号与槽函数
    connect(item,&FAQitem::sig_item_expand,[=](bool checked){
        if(checked)
        {
            for(int i = 0; i < ui->addVerLayout->count()-1; i++)
            {
                QWidget* itemWgt = ui->addVerLayout->itemAt(i)->widget();
                if(itemWgt != nullptr && itemWgt != item)//除了自己以外的全部折叠
                {
//                    qDebug() <<QString(u8"找到itemWgt") << itemWgt;
                    FAQitem *newListItem = static_cast<FAQitem*>(itemWgt);
//                    newListItem->setFoldItem();
                    newListItem->hide();
//                    qDebug() <<QString(u8"找到了");
                }
            }
        }
        else
        {
            for(int i = 0; i < ui->addVerLayout->count()-1; i++)
            {
                QWidget* itemWgt = ui->addVerLayout->itemAt(i)->widget();
                if(itemWgt != nullptr && itemWgt != item)//除了自己以外的全部折叠
                {
//                    qDebug() <<QString(u8"找到itemWgt") << itemWgt;
                    FAQitem *newListItem = static_cast<FAQitem*>(itemWgt);
//                    newListItem->setShowItem();
                    newListItem->show();
//                    qDebug() <<QString(u8"找到了");
                }
            }
        }
    });
}

void NewLoginForm::addUserToLoginLists(int id_index)
{

}

void NewLoginForm::removeUserToLoginLists(int id_index)
{

}

void NewLoginForm::updateUserListGeomotry()
{
    const int g_x = ui->lineEdit_account->parentWidget()->mapToGlobal(ui->lineEdit_account->pos()).x();
    const int g_y = ui->lineEdit_account->parentWidget()->mapToGlobal(ui->lineEdit_account->pos()).y();
    m_userLists->setGeometry(g_x,g_y + ui->lineEdit_account->height()+8,m_userLists->width(),m_userLists->height());
//    m_userLists->setAttribute(Qt::WA_ShowWithoutActivating);//只弹出，不获得焦点
    m_userLists->show();
    ui->lineEdit_account->grabKeyboard();//获取键盘输入
}

bool NewLoginForm::updateRemPwdStatus()
{
    if(ui->checkBox_rempwd->isChecked())
    {
        m_actionShowPwd->setEnabled(false);//密码查看功能禁止
        return true;
    }
    else
    {
        m_actionShowPwd->setEnabled(true);
        ui->lineEdit_userpwd->clear();//清除密码
        return false;
    }
    ui->lineEdit_userpwd->setFocus();//将焦点设置回来
}

//发送验证码
bool NewLoginForm::sendCheckCode(ShowType type, const QString &receiver_email)
{
    QString subject = "";//主题
    QString content = "";//邮件内容

    switch (type) {
    case LoginWin_1://短信登录
    {
        subject = QString(u8"xx系统登录/登录验证码");
        content = QString(u8"尊敬的邮箱为%1用户，您好！本次账户登录操作的验证码为：%2，请在一分钟内进行账户登录操作，逾期验证码将失效！若无以上操作，请忽略。").arg(receiver_email).arg(m_login_Random);
    }
        break;
    case RegisWin://注册账户
    {
        subject = QString(u8"xx系统注册/注册验证码");
        content = QString(u8"尊敬的邮箱为%1用户，您好！本次账户注册操作的验证码为：%2，请在一分钟内进行账户注册操作，逾期验证码将失效！若无以上操作，请忽略。").arg(receiver_email).arg(m_regis_Random);
    }
        break;
    case ReSetWin://重置密码
    {
        subject = QString(u8"xx系统重置/重置验证码");
        content = QString(u8"尊敬的邮箱为%1用户，您好！本次密码重置操作的验证码为：%2，请在一分钟内进行重置密码操作，逾期验证码将失效！若无以上操作，请忽略。").arg(receiver_email).arg(m_reset_Random);
    }
        break;
    default:
        break;
    }
    Smtp smtp(QString(u8"2493920797@qq.com").toUtf8(),QString(u8"wnmctxmlgfeoebag").toUtf8());
    smtp.send(receiver_email.toUtf8(),subject.toUtf8(),content.toUtf8());
    //需要对发送结果进行判断，这里默认成功
    return true;
}

void NewLoginForm::receiveLoginAppClose()
{
    aniGroup->start();
}

void NewLoginForm::slot_switchWinType(ShowType type)
{
    bool login = checkCurUserLoginStatus();
    if(!login)//不在线
    {
        switch (type) {
        case ShowType::LoginWin_0://扫码登录
        {
            ui->tabWidget_login->setCurrentWidget(ui->tab_login1);
            ui->stackedWidget_right->setCurrentWidget(ui->page_login);
        }
            break;
        case ShowType::LoginWin_1://短信登录
        {
            ui->tabWidget_login->setCurrentWidget(ui->tab_login1);
            ui->stackedWidget_right->setCurrentWidget(ui->page_login);
            ui->lineEdit_telNumber->setFocus();
        }
            break;
        case ShowType::LoginWin_2://账号登录
        {
            ui->tabWidget_login->setCurrentWidget(ui->tab_login2);
            ui->stackedWidget_right->setCurrentWidget(ui->page_login);
            ui->lineEdit_account->setFocus();
        }
            break;
        case ShowType::RegisWin://注册账户窗口
        {
            ui->tabWidget_login->setCurrentWidget(ui->tab_login2);
            ui->stackedWidget_right->setCurrentWidget(ui->page_regis);
            ui->lineEdit_regis_telNumber->setFocus();
        }
            break;
        case ShowType::ReSetWin://重置密码窗口
        {
            ui->tabWidget_login->setCurrentWidget(ui->tab_login2);
            ui->stackedWidget_right->setCurrentWidget(ui->page_resetPwd);
            ui->lineEdit_fpwd_account->setFocus();
        }
            break;
        default:
            break;
        }

    }
    else//在线
    {
                switch (type)
                {
                case ShowType::LoginWin_0://扫码登录
                {
                    ui->stackedWidget_right->setCurrentWidget(ui->page_login);
                }
                    break;
                case ShowType::LoginWin_1://短信登录
                {
                    ui->stackedWidget_right->setCurrentWidget(ui->page_login);
                    ui->lineEdit_telNumber->setFocus();
                }
                    break;
                case ShowType::LoginWin_2://账号登录
                {
                    ui->stackedWidget_right->setCurrentWidget(ui->page_login);
                    ui->lineEdit_account->setFocus();
                }
                    break;
                case ShowType::ReSetWin://重置密码窗口
                {
                    ui->tabWidget_login->setCurrentWidget(ui->tab_login2);
                    ui->stackedWidget_right->setCurrentWidget(ui->page_resetPwd);
                    ui->lineEdit_fpwd_account->setFocus();
                }
                    break;
                default:
                    break;
            }

     }

        if(this->windowOpacity() == 0)
        {
            this->setWindowOpacity(1);
        }
        this->exec();//最后显示
}

//void NewLoginForm::paintEvent(QPaintEvent *event)
//{
//    Q_UNUSED(event)
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing,true);
//    painter.setPen(Qt::NoPen);
//    painter.setBrush(QColor(56, 67, 99,10));//rgba

//    QPainterPath drawPath;
//    drawPath.addRoundedRect(this->rect(),5,5);
//    drawPath.addRect(this->rect());
////    painter.fillPath(drawPath,Qt::black);//先绘图片再填充外部边缘（准确来说叫颜色压住覆盖）
//    painter.setClipPath(drawPath);
//}


bool NewLoginForm::eventFilter(QObject *obj, QEvent *ev)
{
    if(obj == ui->lineEdit_account)
    {
        if(ev->type() == QEvent::FocusIn)
        {
            ui->lineEdit_account->grabKeyboard();//获取键盘输入
        }
        else if(ev->type() == QEvent::FocusOut)
        {
//            qDebug() << QString(u8"释放键盘输入");
            ui->lineEdit_account->releaseKeyboard();//释放键盘输入
        }
        else if(ev->type() == QEvent::MouseButtonPress)
        {
            updateUserListGeomotry();
            setAttribute(Qt::WA_NoMouseReplay);//避免重复触发窗口外的鼠标点击事件
            m_userLists->clearFocus();
            ui->lineEdit_account->setFocus();
        }
    }
    if(obj == ui->lineEdit_userpwd)
    {
        if(ev->type() == QEvent::FocusIn)
        {
            m_userLists->close();
        }
    }
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

    //记住密码/非记住密码区别以下
    if(!ui->checkBox_rempwd->isChecked())//非记住密码（密码进行加密进行登录）
    {
        //密码加密操作(string->base64->hash)
        passwd = dataBase::getInstance()->code_qstring_To_Hash(dataBase::getInstance()->code_qstring_To_Base64(passwd));
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
        QString pwd      =  dataBase::getInstance()->getCurrentUserPawd();
        QString head     =  dataBase::getInstance()->getCurrentUserHead();
        int     grade    =  dataBase::getInstance()->getCurrentUserGrade();
        emit sig_sendLoginOK(nickname,head,grade);//向外界发送用户信息
        emit sig_sendToLoginedUser(nickname,pwd,head);//登陆列表写入用户信息
//        slot_addLoginHisUsers(account);
//        setType(TipType::SUCCESS);
//        showCText(LoginWin_2,TipType::SUCCESS,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-240,100),QString(u8"恭喜您，登陆成功！"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
        setStatusTips(LoginWin_2,TipType::SUCCESS,QString(u8"恭喜您，登陆成功！"));
        QTimer::singleShot(3000,0,[=](){
            slot_clearTempInputText();//清除输入信息
            this->close();
        });
    }
    else//信息核对失败！
    {
        qDebug() <<QString(u8"查无此人！");
        setType(TipType::FAILED);
        showCText(LoginWin_2,TipType::FAILED,ui->pushButton_login->mapToGlobal(ui->pushButton_login->pos())- QPoint(-226,100),QString(u8"用户信息不正确！"),ui->pushButton_login,ui->lineEdit_telNumber->rect(),2000);
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
       pwd     = ui->lineEdit_regis_pwd->text().trimmed();
       email   = ui->lineEdit_regis_email->text().trimmed();
    }
    //插入之前先判断邮箱是否被注册过
    bool valiable1 = dataBase::getInstance()->getUserEmailsExists("userinfo",email);
    if(valiable1)//邮箱已被注册
    {
        setType(TipType::FAILED);
        showCText(ShowType::RegisWin,TipType::FAILED,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-220,101),QString(u8"邮箱已被注册！"),ui->lineEdit_regis_email,ui->lineEdit_regis_email->rect(),2000);
        return;//直接返回
    }
    //邮箱没有被注册，再判断用户登录账号是否重名
    bool valiable2 = dataBase::getInstance()->getUserExists("userinfo",name);
    if(valiable2)
    {
        setType(TipType::FAILED);
        showCText(ShowType::RegisWin,TipType::FAILED,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-220,181),QString(u8"该账户名已被使用！"),ui->pushButton_regis,ui->lineEdit_regis_telNumber->rect(),2000);
        return;
    }


    //密码加密操作(string->base64->hash)
    pwd = dataBase::getInstance()->code_qstring_To_Hash(dataBase::getInstance()->code_qstring_To_Base64(pwd));
    //没有重命名
    bool isOK = dataBase::getInstance()->register_userInfo(name,pwd,email);//数据库插入用户信息
    if(isOK)//插入成功
    {
        setStatusTips(ShowType::RegisWin,TipType::SUCCESS,QString(u8"恭喜您，注册成功！"));
        QTimer::singleShot(3000,0,[=](){
            slot_clearTempInputText();
            ui->stackedWidget_right->setCurrentWidget(ui->page_login);//右侧变为扫码登录界面
            ui->pushButton_updateQR->click();//模拟点击刷新二维码
        });
    }
    else//插入失败
    {
        setType(TipType::FAILED);
        showCText(ShowType::RegisWin,TipType::FAILED,ui->pushButton_regis->mapToGlobal(ui->pushButton_regis->pos())- QPoint(-240,61),QString(u8"注册失败，请重新注册!"),ui->lineEdit_regis_checkCode,ui->lineEdit_regis_checkCode->rect(),2000);
    }
}

void NewLoginForm::setUser_resetPwd()
{
    QString email  = "";
    QString passwd = "";

    if(ui->stackedWidget_right->currentIndex() == 2)//重置密码界面
    {
       email      = ui->lineEdit_fpwd_account->text().trimmed();
       passwd     = ui->lineEdit_secondpwd->text().trimmed();
    }
    //重置前，先查询邮箱是否为用户邮箱
    bool valiable = dataBase::getInstance()->getUserEmailsExists("userinfo",email);
    if(!valiable)//邮箱不存在
    {
        setType(TipType::FAILED);
        showCText(ShowType::ReSetWin,TipType::FAILED,ui->pushButton_resetPwd->mapToGlobal(ui->pushButton_resetPwd->pos())- QPoint(-245,181),QString(u8"邮箱未注册！"),ui->pushButton_resetPwd,ui->lineEdit_fpwd_account->rect(),2000);
        slot_clearTempInputText();
        return;//直接返回
    }
    //如果存在，则进行密码重置，数据库更新数据
    //密码加密操作(string->base64->hash)
    passwd = dataBase::getInstance()->code_qstring_To_Hash(dataBase::getInstance()->code_qstring_To_Base64(passwd));
    //没有重命名
    bool isOK = dataBase::getInstance()->fpwd_reset_userPasswd(email,passwd);//数据库更新用户密码
    if(isOK)//密码重置成功
    {
        setStatusTips(ShowType::ReSetWin,TipType::SUCCESS,QString(u8"恭喜您，密码重置成功！"));
        QTimer::singleShot(3000,0,[=](){
            slot_clearTempInputText();
            ui->stackedWidget_right->setCurrentWidget(ui->page_login);//右侧变为扫码登录界面
            ui->pushButton_updateQR->click();//模拟点击刷新二维码
        });
    }
    else//插入失败
    {
        setType(TipType::FAILED);
        showCText(ShowType::ReSetWin,TipType::FAILED,ui->pushButton_resetPwd->mapToGlobal(ui->pushButton_resetPwd->pos())- QPoint(-245,61),QString(u8"密码重置失败！"),ui->pushButton_resetPwd,ui->lineEdit_fpwd_account->rect(),2000);
    }
}


void NewLoginForm::slot_clearTempInputText()
{
    ui->lineEdit_telNumber->clear();
    ui->lineEdit_checkCode->clear();
    ui->lineEdit_regis_telNumber->clear();
    ui->lineEdit_regis_pwd->clear();
    ui->lineEdit_regis_checkCode->clear();
    ui->lineEdit_regis_email->clear();
    ui->lineEdit_account->clear();
    ui->lineEdit_userpwd->clear();
    ui->lineEdit_fpwd_account->clear();
    ui->lineEdit_fpwd_checkCode->clear();
    ui->lineEdit_firstpwd->clear();
    ui->lineEdit_secondpwd->clear();
}

//设置报错信息显示样式
void NewLoginForm::setType(TipType type)
{
    switch (type)
       {
       case TipType::SUCCESS://正常提示
       {
   //        QString st = "<b style=\"background:rgb(230, 92, 54);color:red;\">%1</b>";
   //        return st;
   //        QToolTip::setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
           setStyleSheet("QToolTip{min-height: 20px; background-color: #769b38; color: #ffffff;}");
       }
           break;
       case TipType::FAILED://错误提示
       {
   //        QString st = "<b style=\"background:rgb(230, 92, 54);color:red;\">%1</b>";
   //        return st;
   //        QToolTip::setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
           setStyleSheet("QToolTip{min-height: 20px; background-color: #9c2424; color: #ffffff;}");
       }
           break;
       case TipType::UNKMOW://成功提示
       {
   //        QString st = "<b style=\"background:rgb(246, 188, 63);color:green;\">%1</b>";
   //        return st;
   //        QToolTip::setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
           setStyleSheet("QToolTip{min-height: 20px; background-color: #f5e790; color: #ffffff;}");
       }
           break;
       default:
       {
   //        QString st = "<b style=\"background:rgb(255, 214, 22);color:white;\">%1</b>";
   //        return st;
   //        QToolTip::setPalette(QPalette(QColor(Qt::red),QColor(Qt::blue)));
           setStyleSheet("QToolTip{min-height: 20px; background-color: #f5e790; color: #ffffff;}");
       }
           break;
       }

}

QString NewLoginForm::generateRandomCode(int length)
{
    QString code;
    static const QString characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    for (int i = 0; i < length; ++i) {
        int index = QRandomGenerator::global()->bounded(characters.length());
        code.append(characters.at(index));
    }
    qDebug() << QString(u8"生成的随机字符：") << code;
    return code;
}

bool NewLoginForm::checkCurUserLoginStatus()
{
    bool online = dataBase::getInstance()->getCurrentUserOnline();
    if(online)
    {
        ui->stackedWidget_left->setCurrentWidget(ui->stackedpage_logined);
        ui->label_userHeader->setPixmap_(dataBase::getInstance()->getCurrentUserHeadPix());
        ui->label_userHeader->setScaledContents(true);
        setCurUserLoginedInfo(dataBase::getInstance()->getCurrentUserGrade(),dataBase::getInstance()->getCurrentUserName());
        return true;
    }
    else
    {
        ui->stackedWidget_left->setCurrentWidget(ui->stackedpage_unlogin);
        ui->tabWidget_login->setCurrentWidget(ui->tab_login2);
        return false;
    }
}

void NewLoginForm::setCurUserLoginedInfo(int grade, const QString &nick)
{
    ui->pushButton_userName->setText(nick);
    switch (grade)
    {
    case 0:
    {
        ui->pushButton_userGrade->setIcon(QIcon("://images/user/user_visitor.png"));
        ui->pushButton_userGrade->setText(QString(u8"等级：普通游客"));
    }
        break;
    case 1:
    {
        ui->pushButton_userGrade->setIcon(QIcon("://images/user/user_vip.png"));
        ui->pushButton_userGrade->setText(QString(u8"等级：注册用户"));
    }
        break;
    case 2:
    {
        ui->pushButton_userGrade->setIcon(QIcon("://images/user/user_suvip.png"));
        ui->pushButton_userGrade->setText(QString(u8"等级：普通会员"));
    }
        break;
    case 3:
    {
        ui->pushButton_userGrade->setIcon(QIcon("://images/user/user_ssvip.png"));
        ui->pushButton_userGrade->setText(QString(u8"等级：超级会员"));
    }
        break;
    default:
        ui->pushButton_userGrade->setIcon(QIcon("://images/user/user_zhuye.png"));
        ui->pushButton_userGrade->setText(QString(u8"非注册用户"));
        break;
    }
}

//显示账号规则
void NewLoginForm::showTipContentLenRule(const ShowType type, const QString &ruleText)
{

}


void NewLoginForm::showCText(ShowType stype, TipType type, const QPoint &pos, const QString &text, QWidget *w, const QRect &rect, int msecShowTime)
{
    switch (type) {
    case FAILED:
    {
        QToolTip::showText(pos,text,w,rect,msecShowTime);
    }
        break;
    case SUCCESS:
    {
        QToolTip::showText(pos,text,w,rect,msecShowTime);
    }
        break;
    case UNKMOW:
    {
        QToolTip::showText(pos,text,w,rect,msecShowTime);
    }
        break;
    default:
        break;
    }

}

void NewLoginForm::setStatusTips(ShowType stype, TipType type, const QString &text)
{
    switch (stype) {
    case RegisWin:
    {
        ui->label_regis_tips->setText(text);
        QTimer::singleShot(2000,0,[=](){
            ui->label_regis_tips->clear();
        });
    }
        break;
    case ReSetWin:
    {
        ui->label_reset_tips->setText(text);
        QTimer::singleShot(2000,0,[=](){
            ui->label_reset_tips->clear();
        });
    }
        break;
    case LoginWin_0:
    {
        ui->label_QR_tips->setText(text);
        QTimer::singleShot(2000,0,[=](){
            ui->label_QR_tips->clear();
        });
    }
        break;
    case LoginWin_1:
    {
        ui->label_login_tips->setText(text);
        QTimer::singleShot(2000,0,[=](){
            ui->label_login_tips->clear();
        });
    }
        break;
    case LoginWin_2:
    {
        ui->label_login_tips->setText(text);
        QTimer::singleShot(2000,0,[=](){
            ui->label_login_tips->clear();
        });
    }
        break;
    default:
        break;
    }
}

void NewLoginForm::show_c()
{
    checkCurUserLoginStatus();//先核对登陆状态
    this->exec();
}
