#ifndef SYSTEMSETTING_H
#define SYSTEMSETTING_H

#include <QWidget>
#include <QDialog>
#include <QPoint>

namespace Ui {
class SystemSetting;
}

class SystemSetting : public QDialog
{
    Q_OBJECT

public:
    explicit SystemSetting(QWidget *parent = nullptr);
    ~SystemSetting();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void savesSettingConfigFile();//保存配置
    void loadDefaultConfig();//加载一些默认配置

private:
    Ui::SystemSetting *ui;
    QPoint      m_mvPos;
};

#endif // SYSTEMSETTING_H
