#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include <QWidget>
#include <QDialog>
#include <QPoint>
#include <QTimer>

namespace Ui {
class SystemSetting;
}

class SystemSetting : public QDialog
{
    Q_OBJECT

public:
    explicit SystemSetting(QWidget *parent = nullptr);
    ~SystemSetting();
    void initWorkUI();
    void chandleSignalAndSlot();

public slots:
    QString openLocalFileSystem();
    void setTitleWarningText(QString text = "",int msec = 50000);//默认参数
protected:
    void savesSettingConfigFile();//保存配置
    void loadDefaultConfig();//加载一些默认配置
    void setObjectShowTip(QObject *obj, QString &text);
private:
    Ui::SystemSetting *ui;
    QPoint      m_mvPos;
//    QTimer      *m_timer        =   nullptr;
};

#endif // SYSTEMSETTING_H
