#include "MainWidget.h"
#include <QMenu>
#include <QSqlQuery>

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    m_winMax(false)
{
    setMinimumSize(1240,800);
    setMouseTracking(true);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setWindowTitle(QString::fromLocal8Bit("Qt简易视频播放器主界面"));
    initOtherWidgetUi();//初始化界面
    setStackedWidgetPage();//设置StackedWidget布局每个page界面
    chandleSignalAndSlots();//处理所有的信号与槽函数
}

//初始化界面
void MainWidget::initOtherWidgetUi()
{
    m_titleBar = new TitleBar(this);
    m_titleBar->setFixedHeight(50);
    m_titleBar->setObjectName(QString::fromLatin1("m_titleBar"));

    m_leftSideBar = new LeftSideBar(this);
    m_leftSideBar->setObjectName(QString::fromLatin1("m_leftSideBar"));

    m_stackWidget = new QStackedWidget(this);
    m_stackWidget->setCurrentIndex(0);//默认显示第一个page页
    m_stackWidget->setObjectName(QString::fromLatin1("m_stackWidget"));

    m_mainWin = new MainWindow(m_stackWidget);
    m_mainWin->setObjectName(QString::fromLatin1("m_mainWin"));

    m_musicList = new MusicPlaylist(m_stackWidget);
    m_musicList->setObjectName(QString::fromLatin1("m_musicList"));

    m_musicShow = new MusicPlayShow(m_stackWidget);
    m_musicShow->setObjectName(QString::fromLatin1("m_musicShow"));

    m_tabWidget = new CusTabWidget(m_stackWidget);
    m_tabWidget->setObjectName(QString::fromLatin1("m_tabWidget"));

    m_videoWidget = new CusVideoWidget(m_stackWidget);
    m_videoWidget->setObjectName(QString::fromLatin1("m_videoWidget"));

    m_webBrowser = new CusWebBrowser(m_stackWidget);
    m_webBrowser->setObjectName(QString::fromLatin1("m_webBrowser"));

    //弹出对话框
    m_pExitDlg = new ExitDialog(this);
    m_pExitDlg->setObjectName(QString::fromLatin1("m_pExitDlg"));
    //登录
    m_login = new Login(this);
    m_login->setObjectName(QString::fromLatin1("m_login"));
    m_login->setHidden(true);//首次应该隐藏，否则弹出界面

    m_vblayout = new QVBoxLayout(this);
    m_hblayout = new QHBoxLayout(this);
    //侧边栏+QStackedWidget--->水平布局
    m_hblayout->addWidget(m_leftSideBar,0,Qt::AlignLeft);
    m_hblayout->addWidget(m_stackWidget,1,Qt::AlignCenter);
    m_hblayout->setSpacing(0);
    m_hblayout->setContentsMargins(0,0,0,0);
    //标题栏+水平布局--->垂直布局
    m_vblayout->addWidget(m_titleBar,0,Qt::AlignTop);
    m_vblayout->addLayout(m_hblayout,1);
    m_vblayout->setContentsMargins(3,3,3,3);//左 上 右 下
    m_vblayout->setSpacing(0);
    this->setLayout(m_vblayout);
    loadAllUIQss();//加载界面样式
}

//处理信号与槽函数
void MainWidget::chandleSignalAndSlots()
{
    //标题栏有关信号与槽函数处理
    connect(m_titleBar,&TitleBar::sig_winClose,this,&MainWidget::close);//转到重写事件
    connect(m_titleBar,&TitleBar::sig_winNormal,this,&MainWidget::chandleRestoreWindow);//根据不同状态处理窗口
    connect(m_titleBar,&TitleBar::sig_winMinimum,[=](){this->showMinimized();});
    connect(m_titleBar,&TitleBar::sig_doubleClick,[=](){chandleRestoreWindow();});
    //收到主窗口关闭信号
    connect(m_pExitDlg,&ExitDialog::sig_SendcloseMain,[=](){m_isClose = true;});
    //没收到主窗口关闭信号
    connect(m_pExitDlg,&ExitDialog::sig_SendNotcloseMain,[=](){m_isClose = false;});

    //关闭主窗口，通知登录窗口也关闭
    connect(this,&MainWidget::sig_startCloseAppliction,m_login,&Login::receiveMainWinCloseAppSignal);
    //侧边栏有关信号与槽函数处理
    connect(m_leftSideBar,SIGNAL(sig_sidebarItemChange(int)),this,SLOT(chandleCenterWinShowUi(int)));
    connect(this,SIGNAL(sig_winStatus(bool)),m_titleBar,SLOT(chandleMainWinStatus(bool)));//标题栏处理不同状态下样式

}

/*加载界面样式*/
void MainWidget::loadAllUIQss()
{
    QFile file(":/style/alluistyle.qss");
    file.open(QFile::ReadOnly | QFile::Text);
    if(!file.isOpen())
    {
        qDebug()<<"the style qss is unload!";
        return;
    }
    else
    {
        QString style = tr(file.readAll());
        qApp->setStyleSheet(style);
        qDebug()<<"the style is load successfull!";
    }
    file.close();
}

//设置StackedWidget布局每个page界面
void MainWidget::setStackedWidgetPage()
{
//    m_stackWidget->insertWidget(0,m_musicList);
//    m_stackWidget->insertWidget(1,m_musicList);
//    m_stackWidget->insertWidget(2,m_musicList);
//    m_stackWidget->insertWidget(3,m_musicShow);
//    m_stackWidget->insertWidget(4,m_tabWidget);
//    m_stackWidget->insertWidget(5,m_videoWidget);
//    m_stackWidget->insertWidget(6,m_webBrowser);
}


/*托盘菜单*/
void MainWidget::createTrayMenu()
{
    QMenu *pmenu = new QMenu(this);
    pmenu->setStyleSheet("font-size:12px;"
                         "background-color:#3d3d3d;"
                         "color:green;");//font:bold italic 18px "微软雅黑";
    pmenu->addAction(QString::fromLocal8Bit("显示主界面"),this,SLOT(showPlayerUi()));
    pmenu->addSeparator();
    pmenu->addAction(QString::fromLocal8Bit("显示播放列表"),this,SLOT(showPlayerList()));
    pmenu->addSeparator();
    pmenu->addAction(QString::fromLocal8Bit("上一首"),this,SLOT(on_pushButton_7_clicked()));
    pmenu->addSeparator();
    pmenu->addAction(QString::fromLocal8Bit("下一首"),this,SLOT(on_pushButton_8_clicked()));
    pmenu->addSeparator();
    pmenu->addAction(QString::fromLocal8Bit("暂停/播放"),this,SLOT(on_pushButton_4_clicked()));
    pmenu->addSeparator();
    pmenu->addAction(QString::fromLocal8Bit("退出"),this,SLOT(close()));//注意消息阻塞
    m_tray->setContextMenu(pmenu);
}

/*设置全局tooltip*/
void MainWidget::setGlobalToolTip()
{

}

/*处理窗口还原*/
void MainWidget::chandleRestoreWindow()
{
        if(!m_winMax)//非最大化
        {
            this->showMaximized();
            emit sig_winStatus(m_winMax);//向标题栏发送最大化状态信号


        }
        else
        {
            this->showNormal();
            emit sig_winStatus(m_winMax);//向窗口发送正常状态信号

        }
        m_winMax = !m_winMax;
}

/*槽函数 --- 处理中心显示内容*/
void MainWidget::chandleCenterWinShowUi(int index)
{
    m_stackWidget->setCurrentIndex(index);
}

MainWidget::~MainWidget()
{

}

void MainWidget::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (event->button() == Qt::LeftButton)
    {
        this->_isleftpressed = true;
        QPoint temp = event->globalPos();
        _plast = temp;
        _curpos = countFlag(event->pos(), countRow(event->pos()));
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *event)
{
    //拖动之前判断是否串口处于最大化
    if(this->isMaximized())
    {
        return;
    }
    Q_UNUSED(event);
    if(this->isFullScreen()) return;	//窗口铺满全屏，直接返回，不做任何操作
    int poss = countFlag(event->pos(), countRow(event->pos()));
    setCursorType(poss);
    if (_isleftpressed)//是否左击
    {
        QPoint ptemp = event->globalPos();
        ptemp = ptemp - _plast;
        if (_curpos == 22)//移动窗口
        {
            ptemp = ptemp + pos();
            move(ptemp);
        }
        else
        {
            QRect wid = geometry();
            switch (_curpos)//改变窗口的大小
            {
            case 11:wid.setTopLeft(wid.topLeft() + ptemp); break;//左上角
            case 13:wid.setTopRight(wid.topRight() + ptemp); break;//右上角
            case 31:wid.setBottomLeft(wid.bottomLeft() + ptemp); break;//左下角
            case 33:wid.setBottomRight(wid.bottomRight() + ptemp); break;//右下角
            case 12:wid.setTop(wid.top() + ptemp.y()); break;//中上角
            case 21:wid.setLeft(wid.left() + ptemp.x()); break;//中左角
            case 23:wid.setRight(wid.right() + ptemp.x()); break;//中右角
            case 32:wid.setBottom(wid.bottom() + ptemp.y()); break;//中下角
            }
            setGeometry(wid);
        }
        _plast = event->globalPos();//更新位置
    }
}

void MainWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    if (_isleftpressed)
        _isleftpressed = false;
    setCursor(Qt::ArrowCursor);
}

void MainWidget::changeEvent(QEvent *event)
{
    switch (event->type())
        {
        case QEvent::WindowStateChange:
            {
                this->update();
                this->repaint();
                event->ignore();
                break;
            }
        default:
            break;
    }
}

/*界面卡顿*/
void MainWidget::showEvent(QShowEvent *event)
{
    this->setAttribute(Qt::WA_Mapped);
    QWidget::showEvent(event);
}

/*重写关闭事件---弹窗询问*/
void MainWidget::closeEvent(QCloseEvent *event)
{
    //重写关闭事件，就不需要关闭按钮的操作
    if(m_pExitDlg->isShow)
        m_pExitDlg->exec();
     if(!m_isClose)
     {
         event->ignore();
     }
     else
     {
         /*做一些数据保存*/
         emit sig_startCloseAppliction();
         m_pExitDlg->setIni();
         //此处最好做一个全局的通知信号
//         m_tray->hide();
//         m_login->close();
//         QSqlQuery query;
         //此处应该在数据库提供接口
//         query.exec("DROP TABLE IF EXISTS 'LocalMusic'");
//         query.exec("DROP TABLE IF EXISTS 'LoginInfo'");
//         qDebug()<<"LocalMusic,LoginInfo tables is drop!";
         event->accept();
     }
}

/*获取光标在窗口所在区域的 行   返回行数*/
int MainWidget::countRow(QPoint p)
{
    return (p.x()<MARGIN) ? 1 : (p.x()>(this->width() - MARGIN) ? 3 : 2);
}

/*获取光标在窗口所在区域的 列  返回行列坐标*/
int MainWidget::countFlag(QPoint p, int row)
{
    if(p.y()<MARGIN)
        return 10+row;
    else if(p.y()>this->height()-MARGIN)
        return 30+row;
    else
        return 20+row;
}

/*根据传入的坐标，设置光标样式*/
void MainWidget::setCursorType(int flag)
{
    switch(flag)
    {
    case 11:
    case 33:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case 13:
    case 31:
        setCursor(Qt::SizeBDiagCursor);break;
    case 21:
    case 23:
        setCursor(Qt::SizeHorCursor);break;
    case 12:
    case 32:
        setCursor(Qt::SizeVerCursor);break;
    case 22:
        setCursor(Qt::ArrowCursor);
        QApplication::restoreOverrideCursor();//恢复鼠标指针性状
        break;
    }
}

