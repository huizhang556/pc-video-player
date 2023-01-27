#include "CComboBox.h"

CComboBox::CComboBox(QWidget *parent) :
    QComboBox(parent)
{
    label_space = new QLabel(this);
    label_space->setObjectName(QString::fromUtf8("label_space"));
    label_space->setFixedWidth(90);
    label_space->setFixedHeight(this->height());
    label_space->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//居中
    QHBoxLayout* pHlay = new QHBoxLayout(this);
    pHlay->setSpacing(0);
    pHlay->setContentsMargins(0,0,20,0);
    pHlay->addStretch();
    pHlay->addWidget(label_space);
    label_space->setStyleSheet("#label_space{"
                               "background-color: transparent;"
                               "font-size: 14px;"
                               "color: #23b7ac;"
                               "border: 0px solid #404040;"
                               "}");

    //路径变化，就重新计算容量
    connect(this,&CComboBox::currentTextChanged,[=](const QString& text){
        setDiskSpace(QString(u8"剩余:%1").arg(checkDiskStorageSpace(text)));
    });
}

CComboBox::~CComboBox()
{
}

void CComboBox::setDiskSpace(const QString &space)
{
    label_space->setText(space);
}

void CComboBox::setCurrentText_(const QString &text)
{
    this->setCurrentText(text);
    this->setToolTip(text);
}

void CComboBox::insertItem_(int index, const QString &text)
{
    this->insertItem(index,text);
    this->setToolTip(text);
}

QString CComboBox::checkDiskStorageSpace(const QString &path)
{
    if(!path.isEmpty())
    {
        QDir dir(path);
        QStorageInfo storage(dir);
        if (storage.isValid() && storage.isReady())
            return  calSpaceSize(storage.bytesFree());
    }
}

QString CComboBox::calSpaceSize(qint64 bytesTotal)
{
    int integer = 0;  //整数位
    int decimal = 0;  //小数位，保留三位
    char unit ='B';
    qint64 standardSize = bytesTotal;//qint64 long long int
    qint64 curSize = bytesTotal;

    if(standardSize > 1024) {
        curSize = standardSize * 1000;//目的是扩大为整数求取小数部分好计算
        curSize /= 1024;//curSize = curSize/1024 curSize单位为（B）
        integer = curSize / 1000;//变为B大小后，求整数部分
        decimal = curSize % 1000;//求余数mod()
        standardSize /= 1024;//整正的大小 standardSize
        unit = 'K';
        if(standardSize > 1024) {//KB大大小大于1024
            curSize = standardSize * 1000;
            curSize /= 1024;
            integer = curSize / 1000;
            decimal = curSize % 1000;
            standardSize /= 1024;
            unit = 'M';
            if(standardSize > 1024) {
                curSize = standardSize * 1000;
                curSize /= 1024;
                integer = curSize / 1000;
                decimal = curSize % 1000;
                unit = 'G';
            }
        }
    }

    QString dec = "0";
    if (0 <= decimal && decimal <= 9) {
        dec = dec + dec + QString::number(decimal);
    }

    if (10 <= decimal && decimal <= 99) {
        dec = "0" + QString::number(decimal);
    }

    if (100 <= decimal && decimal <= 999) {
        dec = QString::number(decimal);
    }

    return QString::number(integer) + "." + dec + unit;
}
