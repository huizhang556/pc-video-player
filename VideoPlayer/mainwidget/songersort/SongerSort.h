#ifndef SONGERSORT_H
#define SONGERSORT_H

#define MINSIZE QSize(152,204) //默认最小宽高，不能动态调整比这个值小
#define SCALE MINSIZE.height()/MINSIZE.width() // 高/宽 比例

#include <QWidget>
#include <QSize>
#include <QButtonGroup>

namespace Ui {
class SongerSort;
}

class SongerSort : public QWidget
{
    Q_OBJECT

public:
    explicit SongerSort(QWidget *parent = nullptr);
    ~SongerSort();
    void        initWorkUI();
    void        handleSignalsAndSlots();

public slots:
    void        slot_addSongItem(const QString& url,const QString&path, const QString& name, const QString& count);

protected:
    void        resizeEvent(QResizeEvent *event) override;
    bool        eventFilter(QObject *watched, QEvent *event) override;

private slots:

    void        slot_emitNationality(QAbstractButton *button);
    void        slot_emitSex(QAbstractButton *button);
    void        slot_emitStyle(QAbstractButton *button);
    void        slot_emitA_to_Z(QAbstractButton *button);

private:
    void        resizeListWidgetItemWidget();//动态更新item大小

private:
    Ui::SongerSort *ui;
    QButtonGroup        *m_buttonGroup1;
    QButtonGroup        *m_buttonGroup2; 
    QButtonGroup        *m_buttonGroup3;
    QButtonGroup        *m_buttonGroup4;

signals:
    void        sig_sendNationality(QString);
    void        sig_sendSex(QString);
    void        sig_sendStyle(QString);
    void        sig_sendA_to_Z(QString);
    void        sig_sendHot(bool);
    void        sig_sendSonger(QString);
};

#endif // SONGERSORT_H
