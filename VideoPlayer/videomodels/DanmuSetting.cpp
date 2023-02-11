#include "DanmuSetting.h"
#include "ui_DanmuSetting.h"


DanmuSetting::DanmuSetting(QWidget *parent) :
    QDialog(parent),
    m_color(ColorType::VIPGolden),
    m_transNum(1.00),
    m_fontSize(12),
    m_fontWeight(400),
    m_runTime(15000),
    ui(new Ui::DanmuSetting)
{
    ui->setupUi(this);
    initWorkUI();
    handSignalsAndSlots();
    setInstallEventFilter();
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint | Qt::Popup);
    setAttribute(Qt::WA_TranslucentBackground,true);
    setFixedSize(280,340);
}

DanmuSetting::~DanmuSetting()
{
    delete ui;
}

void DanmuSetting::initWorkUI()
{
    m_buttonGroup = new  QButtonGroup(this);
    m_buttonGroup->addButton(ui->pushButton_vip1,0);
    m_buttonGroup->addButton(ui->pushButton_vip2,1);
    m_buttonGroup->addButton(ui->pushButton_vip3,2);
    m_buttonGroup->addButton(ui->pushButton_nvip1,3);
    m_buttonGroup->addButton(ui->pushButton_nvip2,4);
    m_buttonGroup->addButton(ui->pushButton_nvip3,5);
    m_buttonGroup->addButton(ui->pushButton_nvip4,6);
    m_buttonGroup->addButton(ui->pushButton_nvip5,7);
    m_buttonGroup->addButton(ui->pushButton_nvip6,8);
    m_buttonGroup->setExclusive(true);
     for(int i = 0; i < 9; i++)
     {
         m_buttonGroup->button(i)->setCheckable(true);
     }
     ui->pushButton_nvip1->setChecked(true);

    //默认值
    ui->horizontalSlider_trans->setRange(0,100);
    ui->horizontalSlider_trans->setValue(100);
    ui->label_trans->setText(QString(u8"100%"));

    ui->horizontalSlider_fontSize->setRange(0,100);
    ui->horizontalSlider_fontSize->setValue(12);
    ui->label_fontSize->setText(QString(u8"12%"));

    ui->horizontalSlider_fontWeight->setRange(0,100);
    ui->horizontalSlider_fontWeight->setValue(40);
    ui->label_fontWeight->setText(QString(u8"40%"));

    ui->horizontalSlider_speed->setRange(0,100);
    ui->horizontalSlider_speed->setValue(50);
    ui->label_speed->setText(QString(u8"50%"));
//    ui->horizontalSlider_speed->setTickPosition(QSlider::TicksBelow);//下方出现刻度
//    ui->horizontalSlider_speed->setSingleStep(50);//步长（焦点存在，左右键控制时候）
//    ui->horizontalSlider_speed->setTickInterval(50);//设置刻度间隔
//    ui->horizontalSlider_speed->setPageStep(50);

    //屏蔽词界面
    ui->lineEdit_mask->setPlaceholderText(QString(u8"输入屏蔽词，按回车键添加"));

    ui->tabWidget->setCurrentIndex(0);
}

void DanmuSetting::handSignalsAndSlots()
{
    //样式设置界面
    connect(m_buttonGroup,QOverload<QAbstractButton*>::of(&QButtonGroup::buttonClicked),this,[&](QAbstractButton* button){
        setColor(button->text());
    });
    //观看设置界面
    //透明度
    connect(ui->horizontalSlider_trans,&QSlider::valueChanged,[=](int value){
        //字符串保留两位小数QString::number(size, 'f', 2);
        double transNumber = double(value*1.0/100);
        qDebug() <<QString(u8"调节后的透明度：")<<transNumber;
        setTransNumber(transNumber);
        ui->label_trans->setText(QString::number(value)+"%");
    });
    //字大小
    connect(ui->horizontalSlider_fontSize,&QSlider::valueChanged,[=](int value){
            setFontSize(value);
            ui->label_fontSize->setText(QString::number(value)+"%");
    });
    //粗度
    connect(ui->horizontalSlider_fontWeight,&QSlider::valueChanged,[=](int value){
            setFontWeight(value*10);
            ui->label_fontWeight->setText(QString::number(value)+"%");
    });
    //速度
    connect(ui->horizontalSlider_speed,&QSlider::valueChanged,[=](int value){
            setRunTime(value);
            ui->label_speed->setText(QString::number(value)+"%");
    });
    //屏蔽词界面
    connect(ui->lineEdit_mask,&QLineEdit::returnPressed,[=](){
        QString content = ui->lineEdit_mask->text().trimmed();
        if(!content.remove(QRegExp("\\s")).isEmpty() && !findMask(content))
        {
            QListWidgetItem *item = new QListWidgetItem(content);
            ForbiddenItem *forbideWgt = new ForbiddenItem("://images/user/vtitle_mask.png",content);
            item->setSizeHint(QSize(ui->listWidget_maskList->width() - ui->listWidget_maskList->verticalScrollBar()->width()-1,30));
            ui->listWidget_maskList->addItem(item);
            ui->listWidget_maskList->setItemWidget(item,forbideWgt);
            ui->lineEdit_mask->clear();
            //关联信号与槽
            connect(forbideWgt,&ForbiddenItem::sig_send_remove,[=](){
                forbideWgt->disconnect();
                forbideWgt->deleteLater();
                delete item;
            });
        }
        else
        {
            if(!ui->lineEdit_mask->text().isEmpty())
            ui->lineEdit_mask->clear();
        }
    });

    //恢复默认配置
    connect(ui->pushButton_default,&QPushButton::clicked,[=](){setDefaultCfg();});
}

void DanmuSetting::setInstallEventFilter()
{

}

ColorType DanmuSetting::getColor()
{
    return m_color;
}

int DanmuSetting::getFontSize()
{
    qDebug() << QString(u8"获取到的字体大小值：")<< m_fontSize;
    return m_fontSize;
}

int DanmuSetting::getFontWeight()
{
    qDebug() << QString(u8"获取到的字体粗度值：")<< m_fontWeight;
    return m_fontWeight;
}

double DanmuSetting::getTransNumber()
{
    qDebug() << QString(u8"获取到的透明度值：")<< m_transNum;
    return m_transNum;
}

int DanmuSetting::getRunTime()
{
    qDebug() << QString(u8"获取到的速度值：")<< m_runTime;
    return m_runTime;
}

void DanmuSetting::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    this->close();
}

void DanmuSetting::setDefaultCfg()
{
    //默认值
    ui->horizontalSlider_trans->setValue(100);
    ui->label_trans->setText(QString(u8"100%"));
    m_transNum = 1.00;

    ui->horizontalSlider_fontSize->setValue(12);
    ui->label_fontSize->setText(QString(u8"12%"));
    m_fontSize = 12;

    ui->horizontalSlider_fontWeight->setValue(40);
    ui->label_fontWeight->setText(QString(u8"40%"));
    m_fontWeight = 400;

    ui->horizontalSlider_speed->setValue(50);
    ui->label_speed->setText(QString(u8"50%"));
    m_runTime = 15000;
}

bool DanmuSetting::findMask(const QString &text)
{
    for(int i = 0; i <ui->listWidget_maskList->count(); i++)
    {
        //判断 是否有敏感字符串在内（两方面都判断）
        if(ui->listWidget_maskList->item(i)->text().contains(text,Qt::CaseInsensitive))//大小写不敏感
        {
            return true;
        }
        else if(text.contains(ui->listWidget_maskList->item(i)->text(),Qt::CaseInsensitive))
        {
            return true;
        }
    }
    return false;
}

void DanmuSetting::setColor(QString color)
{
    if(color == QString(u8"尊贵蓝"))
    {
        m_color = ColorType::VIPBlue;
    }
    else if(color == QString(u8"尊贵金"))
    {
        m_color = ColorType::VIPGolden;
    }
    else if(color == QString(u8"尊贵粉"))
    {
        m_color = ColorType::VIPPink;
    }
    else if(color == QString(u8"默认"))
    {
        m_color = ColorType::NVIPDefault;
    }
    else if(color == QString(u8"青草绿"))
    {
        m_color = ColorType::NVIPGreen;
    }
    else if(color == QString(u8"香菇蓝"))
    {
        m_color = ColorType::NVIPBlue;
    }
    else if(color == QString(u8"暖阳橙"))
    {
        m_color = ColorType::NVIPOrange;
    }
    else if(color == QString(u8"喜庆红"))
    {
        m_color = ColorType::NVIPRed;
    }
    else if(color == QString(u8"销魂紫"))
    {
        m_color = ColorType::NVIPViolet;
    }
}

void DanmuSetting::setFontSize(int size)
{
    m_fontSize = size;
}

void DanmuSetting::setFontWeight(int size)
{
//    if(size < 100)
//    {
//        size = 100;
//    }
//    else if(size < 200)
//    {
//        size = 200;
//    }
//    else if(size < 300)
//    {
//        size = 300;
//    }
//    else if(size < 400)
//    {
//        size = 400;
//    }
//    else if(size < 500)
//    {
//        size = 500;
//    }
//    else if(size < 600)
//    {
//        size = 600;
//    }
//    else if(size < 700)
//    {
//        size = 700;
//    }
//    else if(size < 800)
//    {
//        size = 800;
//    }
//    else if(size < 900)
//    {
//        size = 900;
//    }
//    else if(size < 1001)
//    {
//        size = 1000;
//    }
    m_fontWeight = size;
}

void DanmuSetting::setTransNumber(double trans)
{
    m_transNum = trans;
}

void DanmuSetting::setRunTime(int time)
{
    double ratio = double(time*1.0/100);
    qDebug() <<QString(u8"速度比例：")<<ratio;
    m_runTime = 15000*ratio;
    qDebug() <<QString(u8"调节后速度：")<<m_runTime;
}
